//
// Created by hy on 17/08/2024.
//

#include "float_3rd_scale_panel.h"
#include "no_margin_layout.h"
#include "switch_button.h"
#include "background_widget.h"
#include "settings.h"
#include "client_context.h"
#include "app_message.h"
#include <QLabel>

namespace tc
{

    ThirdScalePanel::ThirdScalePanel(const std::shared_ptr<ClientContext>& ctx, QWidget* parent) : BaseWidget(ctx, parent) {
        this->setWindowFlags(Qt::FramelessWindowHint);
        this->setStyleSheet("background:#00000000;");
        setFixedSize(200, 130);
        auto item_height = 38;
        auto border_spacing = 10;
        auto item_size = QSize(this->width(), item_height);
        auto root_layout = new NoMarginVLayout();

        settings_ = Settings::Instance();

        {
            auto layout = new NoMarginHLayout();
            auto widget = new QWidget(this);
            widget->setLayout(layout);
            widget->setFixedSize(item_size);
            layout->addWidget(widget);

            auto lbl = new QLabel();
            lbl->setText(tr("Keep Aspect Ratio"));
            layout->addSpacing(border_spacing);
            layout->addWidget(lbl);

            layout->addStretch();

            auto sb = new SwitchButton(this);
            sb_keep_ratio_ = sb;
            sb->setFixedSize(35, 20);
            sb->SetStatus(settings_->scale_mode_ == ScaleMode::kKeepAspectRatio);
            layout->addWidget(sb);
            sb->SetClickCallback([=, this](bool enabled) {
                if (enabled) {
                    UpdateScaleMode(ScaleMode::kKeepAspectRatio);
                }
                context_->SendAppMessage(SwitchScaleModeMessage {
                    .mode_ = settings_->scale_mode_,
                });
            });

            layout->addSpacing(border_spacing);

            root_layout->addSpacing(5);
            root_layout->addWidget(widget);
        }
        {
            auto layout = new NoMarginHLayout();
            auto widget = new QWidget(this);
            widget->setLayout(layout);
            widget->setFixedSize(item_size);
            layout->addWidget(widget);

            auto lbl = new QLabel();
            lbl->setText(tr("Fullscreen"));
            layout->addSpacing(border_spacing);
            layout->addWidget(lbl);

            layout->addStretch();

            auto sb = new SwitchButton(this);
            sb_fullscreen_ = sb;
            sb->setFixedSize(35, 20);
            sb->SetStatus(settings_->scale_mode_ == ScaleMode::kFullscreen);
            layout->addWidget(sb);
            sb->SetClickCallback([=, this](bool enabled) {
                if (enabled) {
                    UpdateScaleMode(ScaleMode::kFullscreen);
                }
                context_->SendAppMessage(SwitchWorkModeMessage {
                    .mode_ = settings_->work_mode_,
                });
            });

            layout->addSpacing(border_spacing);

            root_layout->addSpacing(5);
            root_layout->addWidget(widget);
        }

        {
            auto layout = new NoMarginHLayout();
            auto widget = new QWidget(this);
            widget->setLayout(layout);
            widget->setFixedSize(item_size);
            layout->addWidget(widget);

            auto lbl = new QLabel();
            lbl->setText(tr("Origin Size"));
            layout->addSpacing(border_spacing);
            layout->addWidget(lbl);

            layout->addStretch();

            auto sb = new SwitchButton(this);
            sb_origin_size_ = sb;
            sb->setFixedSize(35, 20);
            sb->SetStatus(settings_->scale_mode_ == ScaleMode::kOriginSize);
            layout->addWidget(sb);
            sb->SetClickCallback([=, this](bool enabled) {
                if (enabled) {
                    UpdateScaleMode(ScaleMode::kOriginSize);
                }
                context_->SendAppMessage(SwitchScaleModeMessage {
                    .mode_ = settings_->scale_mode_,
                });
            });

            layout->addSpacing(border_spacing);

            root_layout->addSpacing(5);
            root_layout->addWidget(widget);
        }

        root_layout->addStretch();
        setLayout(root_layout);
    }

    void ThirdScalePanel::paintEvent(QPaintEvent *event) {
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

    void ThirdScalePanel::UpdateScaleMode(ScaleMode mode) {
        settings_->scale_mode_ = mode;
        if (mode == ScaleMode::kKeepAspectRatio) {
            sb_keep_ratio_->SetStatus(true);
            sb_fullscreen_->SetStatus(false);
            sb_origin_size_->SetStatus(false);
        } else if (mode == ScaleMode::kFullscreen) {
            sb_keep_ratio_->SetStatus(false);
            sb_fullscreen_->SetStatus(true);
            sb_origin_size_->SetStatus(true);
        } else if (mode == ScaleMode::kOriginSize) {
            sb_keep_ratio_->SetStatus(false);
            sb_fullscreen_->SetStatus(false);
            sb_origin_size_->SetStatus(true);
        }
    }

}