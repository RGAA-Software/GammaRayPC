//
// Created by RGAA on 2023-12-27.
//

#include <QHBoxLayout>
#include <QApplication>
#include <QGraphicsDropShadowEffect>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QTimer>
#include "workspace.h"
#include "thunder_sdk.h"
#include "opengl_video_widget.h"
#include "client_context.h"
#include "tc_common_new/data.h"
#include "tc_common_new/log.h"
#include "tc_common_new/message_notifier.h"
#include "audio_player.h"
#include "ui/float_controller.h"
#include "ui/float_controller_panel.h"
#include "app_message.h"
#include "settings.h"
#include "ui/float_notification_handle.h"
#include "ui/notification_panel.h"
#include "transfer/file_transfer.h"
#include "ui/sized_msg_box.h"

namespace tc
{

    Workspace::Workspace(const std::shared_ptr<ClientContext>& ctx, const ThunderSdkParams& params, QWidget* parent) {
        this->context_ = ctx;
        this->settings_ = Settings::Instance();
        setAcceptDrops(true);
        QString app_dir = qApp->applicationDirPath();
        QString style_dir = app_dir + "/resources/";
        theme_ = new acss::QtAdvancedStylesheet(this);
        theme_->setStylesDirPath(style_dir);
        theme_->setOutputDirPath(app_dir + "/output");
        theme_->setCurrentStyle("qt_material");
        theme_->setCurrentTheme("light_blue");
        theme_->updateStylesheet();
        setWindowIcon(theme_->styleIcon());
        qApp->setStyleSheet(theme_->styleSheet());

        sdk_ = ThunderSdk::Make(ctx->GetMessageNotifier());
        sdk_->Init(params, nullptr, DecoderRenderType::kFFmpegI420);

        // ui
        auto root_layout = new QHBoxLayout();
        root_layout->setSpacing(0);
        root_layout->setContentsMargins(0,0,0,0);
        auto root_widget = new QWidget(this);
        root_widget->setLayout(root_layout);

        video_widget_ = new OpenGLVideoWidget(ctx, sdk_, 0, RawImageFormat::kI420, this);
        root_layout->addWidget(video_widget_);

        setCentralWidget(root_widget);

        // float controller
        float_controller_ = new FloatController(ctx, this);
        float_controller_->setFixedSize(55, 55);
        int shadow_color = 0x999999;
        auto shadow = new QGraphicsDropShadowEffect();
        shadow->setBlurRadius(15);
        shadow->setOffset(0, 0);
        shadow->setColor(shadow_color);
        float_controller_->setGraphicsEffect(shadow);
        float_controller_->SetOnClickListener([=, this]() {
            if (!controller_panel_) {
                controller_panel_ = new FloatControllerPanel(ctx, this);
                auto ps = new QGraphicsDropShadowEffect();
                ps->setBlurRadius(15);
                ps->setOffset(0, 0);
                ps->setColor(shadow_color);
                controller_panel_->setGraphicsEffect(ps);
            }
            QPoint point = float_controller_->mapToGlobal(QPoint(0, 0));
            point.setX(float_controller_->pos().x() + float_controller_->width() + 10);
            point.setY(float_controller_->pos().y());
            controller_panel_->move(point);
            if (controller_panel_->isHidden()) {
                if (!float_controller_->HasMoved()) {
                    controller_panel_->show();
                }
            } else {
                controller_panel_->hide();
            }
        });
        float_controller_->SetOnMoveListener([=, this]() {
            if (!controller_panel_) {
                return;
            }
            controller_panel_->hide();
        });

        // notification handle
        notification_handler_ = new FloatNotificationHandle(context_, this);
        notification_handler_->SetPixmap(":resources/image/ic_mail.svg");
        notification_handler_->SetOnClickListener([=, this](QWidget* w) {
            if (notification_panel_->isHidden()) {
                notification_panel_->show();
            } else {
                notification_panel_->hide();
            }
            UpdateNotificationHandlePosition();
        });

        // notification panel
        notification_panel_ = new NotificationPanel(ctx, this);
        notification_panel_->hide();

        // sdk
        RegisterSdkMsgCallbacks();
        sdk_->Start();

        msg_listener_ = context_->GetMessageNotifier()->CreateListener();
        msg_listener_->Listen<ExitAppMessage>([=, this](const ExitAppMessage& msg) {
            this->Exit();
        });

        QTimer::singleShot(100, [=, this](){
            file_transfer_ = std::make_shared<FileTransferChannel>(context_);
            file_transfer_->Start();
        });
    }

    Workspace::~Workspace() {

    }

    void Workspace::RegisterSdkMsgCallbacks() {
        sdk_->SetOnVideoFrameDecodedCallback([=, this](const std::shared_ptr<RawImage>& image, const CaptureMonitorInfo& info) {
            video_widget_->RefreshCapturedMonitorInfo(info);
            video_widget_->RefreshI420Image(image);
        });

        sdk_->SetOnAudioFrameDecodedCallback([=, this](const std::shared_ptr<Data>& data, int samples, int channels, int bits) {
            LOGI("data size: {}, samples: {}, channel: {}, bits: {}, audio on: {}", data->Size(), samples, channels, bits, settings_->IsAudioEnabled());
            if (!settings_->IsAudioEnabled()) {
                return;
            }
            if (!audio_player_) {
                audio_player_ = std::make_shared<AudioPlayer>();
                context_->PostUITask([=, this]() {
                    audio_player_->Init(samples, channels);
                });
                return;
            }
            audio_player_->Write(data);
        });
    }

    void Workspace::changeEvent(QEvent* event) {
        is_window_active_ = isActiveWindow() && !(windowState() & Qt::WindowMinimized);
        qDebug() << "window state: " << is_window_active_;
    }

    bool Workspace::IsActiveNow() const {
        return is_window_active_;
    }

    void Workspace::closeEvent(QCloseEvent *event) {
        LOGI("closed event...");
        auto msg_box = SizedMessageBox::MakeOkCancelBox(tr("Stop"), tr("Do you want to STOP the control of remote PC ?"));
        if (msg_box->exec() == 0) {
            Exit();
        } else {
            event->ignore();
        }
    }

    void Workspace::dragEnterEvent(QDragEnterEvent *event) {
        LOGI("DragEnter...");
        event->accept();
        if (event->mimeData()->hasUrls()) {
            event->acceptProposedAction();
        }
    }

    void Workspace::dragMoveEvent(QDragMoveEvent *event) {
        event->accept();
    }

    void Workspace::dropEvent(QDropEvent *event) {
        QList<QUrl> urls = event->mimeData()->urls();
        if (urls.isEmpty()) {
            return;
        }
        std::vector<QString> files;
        for (const auto& url : urls) {
            files.push_back(url.toLocalFile());
        }
        if (file_transfer_) {
            file_transfer_->SendFiles(files);
        }
    }

    void Workspace::resizeEvent(QResizeEvent *event) {
        UpdateNotificationHandlePosition();
    }

    void Workspace::UpdateNotificationHandlePosition() {
        int notification_panel_width = 0;
        int offset_border = 8;
        int handle_offset = 0;
        if (!notification_panel_->isHidden()) {
            notification_panel_width = notification_panel_->width();
            handle_offset = offset_border;
        }
        notification_panel_->setGeometry(this->width()-notification_panel_->width() - offset_border, offset_border, notification_panel_->width(), this->height() - 2*offset_border);
        notification_handler_->setGeometry(this->width()-notification_handler_->width()/2 - notification_panel_width-handle_offset, 100, notification_handler_->width(), notification_handler_->height());
    }

    void Workspace::Exit() {
        if (sdk_) {
            sdk_->Exit();
            sdk_ = nullptr;
        }
        if (context_) {
            context_->Exit();
            context_ = nullptr;
        }
        if (file_transfer_) {
            file_transfer_->Exit();
        }
        qApp->exit(0);
    }

}