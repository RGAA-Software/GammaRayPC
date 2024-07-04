//
// Created by RGAA on 2023-12-27.
//

#include <QHBoxLayout>
#include "workspace.h"

#include "thunder_sdk.h"
#include "opengl_video_widget.h"
#include "client_context.h"
#include "tc_common_new/data.h"
#include "tc_common_new/log.h"
#include "audio_player.h"
#include "ui/float_controller.h"
#include "ui/float_controller_panel.h"
#include <QGraphicsDropShadowEffect>

namespace tc
{

    Workspace::Workspace(const std::shared_ptr<ClientContext>& ctx, const ThunderSdkParams& params, QWidget* parent) {
        this->context_ = ctx;

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
            auto panel = new FloatControllerPanel(ctx, this);
            auto ps = new QGraphicsDropShadowEffect();
            ps->setBlurRadius(15);
            ps->setOffset(0, 0);
            ps->setColor(shadow_color);
            panel->setGraphicsEffect(ps);
            QPoint point = float_controller_->mapToGlobal(QPoint(0, 0));
            point.setX(float_controller_->pos().x() + float_controller_->width() + 10);
            point.setY(float_controller_->pos().y());
            panel->move(point);
            panel->show();
        });

        // sdk
        RegisterSdkMsgCallbacks();
        sdk_->Start();

    }

    Workspace::~Workspace() {

    }

    void Workspace::RegisterSdkMsgCallbacks() {
        sdk_->SetOnVideoFrameDecodedCallback([=, this](const std::shared_ptr<RawImage>& image, const CaptureMonitorInfo& info) {
            video_widget_->RefreshCapturedMonitorInfo(info);
            video_widget_->RefreshI420Image(image);
        });

        sdk_->SetOnAudioFrameDecodedCallback([=, this](const std::shared_ptr<Data>& data, int samples, int channels, int bits) {
            //LOGI("data size: {}, samples: {}, channel: {}, bits: {}", data->Size(), samples, channels, bits);
            if (!audio_player_) {
                audio_player_ = std::make_shared<AudioPlayer>();
                context_->PostUITask([=, this]() {
                    audio_player_->Init(samples, channels);
                });
                return;
            }
            context_->PostUITask([=, this]() {
                audio_player_->Write(data);
            });
        });
    }

    void Workspace::changeEvent(QEvent* event) {
        is_window_active_ = isActiveWindow() && !(windowState() & Qt::WindowMinimized);
        qDebug() << "window state: " << is_window_active_;
    }

    bool Workspace::IsActiveNow() {
        return is_window_active_;
    }

    void Workspace::closeEvent(QCloseEvent *event) {
        LOGI("closed event...");
        if (sdk_) {
            sdk_->Exit();
        }
        if (context_) {
            context_->Exit();
        }
    }

}