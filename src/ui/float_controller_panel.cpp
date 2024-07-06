//
// Created by RGAA on 4/07/2024.
//

#include "float_controller_panel.h"
#include "float_icon.h"
#include "tc_common_new/message_notifier.h"
#include "client_context.h"
#include "app_message.h"
#include "sized_msg_box.h"
#include "settings.h"
#include "no_margin_layout.h"
#include "background_widget.h"

namespace tc
{

    FloatControllerPanel::FloatControllerPanel(const std::shared_ptr<ClientContext>& ctx, QWidget* parent) : BaseWidget(ctx, parent) {
        this->setWindowFlags(Qt::FramelessWindowHint);
        this->setFixedSize(200, 250);
        this->setStyleSheet("background:#00000000;");
        auto root_layout = new QVBoxLayout();
        WidgetHelper::ClearMargin(root_layout);
        int border_spacing = 5;
        QSize btn_size = QSize(35, 35);
        root_layout->addSpacing(border_spacing);
        {
            auto layout = new QHBoxLayout();
            layout->addSpacing(20);
            WidgetHelper::ClearMargin(layout);
            {
                auto btn = new FloatIcon(ctx, this);
                btn->setFixedSize(btn_size);
                btn->SetIcons(":resources/image/ic_volume_on.svg", ":resources/image/ic_volume_off.svg");
                layout->addWidget(btn);

                auto settings = Settings::Instance();
                if (settings->IsAudioEnabled()) {
                    btn->SwitchToNormalState();
                } else {
                    btn->SwitchToSelectedState();
                }

                btn->SetOnClickListener([=, this](QWidget* w) {
                    if (settings->IsAudioEnabled()) {
                        btn->SwitchToSelectedState();
                        settings->SetTempAudioEnabled(false);
                    } else {
                        btn->SwitchToNormalState();
                        settings->SetTempAudioEnabled(true);
                    }
                });
            }
            {
                auto btn = new FloatIcon(ctx, this);
                btn->setFixedSize(btn_size);
                btn->SetIcons(":resources/image/ic_minimize.svg", "");
                layout->addSpacing(border_spacing);
                layout->addWidget(btn);
                btn->SetOnClickListener([=, this](QWidget* w) {
                    parent->showMinimized();
                });
            }
            {
                auto btn = new FloatIcon(ctx, this);
                btn->setFixedSize(btn_size);
                btn->SetIcons(":resources/image/ic_fullscreen.svg", ":resources/image/ic_fullscreen_exit.svg");
                layout->addSpacing(border_spacing);
                layout->addWidget(btn);
                btn->SetOnClickListener([=, this](QWidget* w) {
                    if (parent->isFullScreen()) {
                        parent->showNormal();
                        btn->SwitchToNormalState();
                    } else {
                        parent->showFullScreen();
                        btn->SwitchToSelectedState();
                    }
                    this->hide();
                });
            }
            {
                auto btn = new FloatIcon(ctx, this);
                btn->setFixedSize(btn_size);
                btn->SetIcons(":resources/image/ic_close.svg", "");
                layout->addSpacing(border_spacing);
                layout->addWidget(btn);
                btn->SetOnClickListener([=, this](QWidget* w) {
                    auto msg_box = SizedMessageBox::MakeOkCancelBox(tr("Stop"), tr("Do you want to STOP the control of remote PC ?"));
                    if (msg_box->exec() == 0) {
                        context_->SendAppMessage(ExitAppMessage {});
                    }
                });
            }
            layout->addStretch();
            root_layout->addLayout(layout);
        }

        auto icon_size = QSize(40, 40);
        int item_left_spacing = 10;
        // work mode
        {
            auto layout = new NoMarginHLayout();
            auto widget = new BackgroundWidget(ctx, this);
            widget->setFixedSize(this->width(), icon_size.height());
            widget->setLayout(layout);
            root_layout->addSpacing(border_spacing);

            auto icon = new QLabel(this);
            icon->setFixedSize(icon_size);
            icon->setStyleSheet(R"( background-image: url(:resources/image/ic_mode.svg);
                                    background-repeat:no-repeat;
                                    background-position: center center;)");
            layout->addSpacing(item_left_spacing);
            layout->addWidget(icon);

            auto text = new QLabel();
            text->setText(tr("Work Mode"));
            //layout->addSpacing(border_spacing);
            layout->addWidget(text);

            layout->addStretch();
            root_layout->addWidget(widget);
        }
        // control
        {
            auto layout = new NoMarginHLayout();
            auto widget = new BackgroundWidget(ctx, this);
            widget->setFixedSize(this->width(), icon_size.height());
            widget->setLayout(layout);

            auto icon = new QLabel(this);
            icon->setFixedSize(icon_size);
            icon->setStyleSheet(R"( background-image: url(:resources/image/ic_control.svg);
                                    background-repeat:no-repeat;
                                    background-position: center center;)");
            layout->addSpacing(item_left_spacing);
            layout->addWidget(icon);

            auto text = new QLabel();
            text->setText(tr("Control"));
            //layout->addSpacing(border_spacing);
            layout->addWidget(text);

            layout->addStretch();
            root_layout->addWidget(widget);
        }
        // Display
        {
            auto layout = new NoMarginHLayout();
            auto widget = new BackgroundWidget(ctx, this);
            widget->setFixedSize(this->width(), icon_size.height());
            widget->setLayout(layout);

            auto icon = new QLabel(this);
            icon->setFixedSize(icon_size);
            icon->setStyleSheet(R"( background-image: url(:resources/image/ic_desktop.svg);
                                    background-repeat:no-repeat;
                                    background-position: center center;)");
            layout->addSpacing(item_left_spacing);
            layout->addWidget(icon);

            auto text = new QLabel();
            text->setText(tr("Display"));
            //layout->addSpacing(border_spacing);
            layout->addWidget(text);

            layout->addStretch();
            root_layout->addWidget(widget);
        }
        // file transfer
        {
            auto layout = new NoMarginHLayout();
            auto widget = new BackgroundWidget(ctx, this);
            widget->setFixedSize(this->width(), icon_size.height());
            widget->setLayout(layout);

            auto icon = new QLabel(this);
            icon->setFixedSize(icon_size);
            icon->setStyleSheet(R"( background-image: url(:resources/image/ic_file_transfer.svg);
                                    background-repeat:no-repeat;
                                    background-position: center center;)");
            layout->addSpacing(item_left_spacing);
            layout->addWidget(icon);

            auto text = new QLabel();
            text->setText(tr("File Transfer"));
            //layout->addSpacing(border_spacing);
            layout->addWidget(text);

            layout->addStretch();
            root_layout->addWidget(widget);
        }
        // debug
        {
            auto layout = new NoMarginHLayout();
            auto widget = new BackgroundWidget(ctx, this);
            widget->setFixedSize(this->width(), icon_size.height());
            widget->setLayout(layout);

            auto icon = new QLabel(this);
            icon->setFixedSize(icon_size);
            icon->setStyleSheet(R"( background-image: url(:resources/image/ic_debug_off.svg);
                                    background-repeat:no-repeat;
                                    background-position: center center;)");
            layout->addSpacing(item_left_spacing);
            layout->addWidget(icon);

            auto text = new QLabel();
            text->setText(tr("Debug"));
            //layout->addSpacing(border_spacing);
            layout->addWidget(text);

            layout->addStretch();
            root_layout->addWidget(widget);
        }
        root_layout->addStretch();
        setLayout(root_layout);

        msg_listener_ = ctx->GetMessageNotifier()->CreateListener();
        msg_listener_->Listen<MousePressedMessage>([=, this](const MousePressedMessage& msg) {
            this->hide();
        });
    }

    void FloatControllerPanel::paintEvent(QPaintEvent *event) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::TextAntialiasing);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(0xffffff));
        int offset = 0;
        int radius = 5;
        painter.drawRoundedRect(offset, offset, this->width()-offset*2, this->height()-offset*2, radius, radius);
        BaseWidget::paintEvent(event);
    }
}