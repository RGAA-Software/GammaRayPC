//
// Created by hy on 17/08/2024.
//

#include "float_3rd_resolution_panel.h"
#include "no_margin_layout.h"
#include "switch_button.h"
#include "background_widget.h"
#include "settings.h"
#include "client_context.h"
#include "app_message.h"
#include "single_selected_list.h"
#include "tc_common_new/log.h"
#include <QLabel>

namespace tc
{

    ThirdResolutionPanel::ThirdResolutionPanel(const std::shared_ptr<ClientContext>& ctx, QWidget* parent) : BaseWidget(ctx, parent) {
        this->setWindowFlags(Qt::FramelessWindowHint);
        this->setStyleSheet("background:#00000000;");
        setFixedSize(200, 350);
        auto item_height = 38;
        auto border_spacing = 10;
        auto item_size = QSize(this->width(), item_height);
        auto root_layout = new NoMarginVLayout();

        settings_ = Settings::Instance();

        listview_ = new SingleSelectedList(this);
        listview_->setFixedSize(this->size());
        listview_->UpdateItems({
           std::make_shared<SingleItem>(SingleItem { .name_ = "3840x2160", }),
           std::make_shared<SingleItem>(SingleItem { .name_ = "2560x1600", }),
           std::make_shared<SingleItem>(SingleItem { .name_ = "2560x1440", }),
           std::make_shared<SingleItem>(SingleItem { .name_ = "2560x1080", }),
           std::make_shared<SingleItem>(SingleItem { .name_ = "2048x1536", }),
           std::make_shared<SingleItem>(SingleItem { .name_ = "1920x1440", }),
           std::make_shared<SingleItem>(SingleItem { .name_ = "1920x1200", }),
           std::make_shared<SingleItem>(SingleItem { .name_ = "1920x1080", }),
           std::make_shared<SingleItem>(SingleItem { .name_ = "1680x1050", }),
           std::make_shared<SingleItem>(SingleItem { .name_ = "1600x1024", }),
           std::make_shared<SingleItem>(SingleItem { .name_ = "1600x900", }),
           std::make_shared<SingleItem>(SingleItem { .name_ = "1400x1080", }),
           std::make_shared<SingleItem>(SingleItem { .name_ = "1400x1050", }),
           std::make_shared<SingleItem>(SingleItem { .name_ = "1400x900", }),
           std::make_shared<SingleItem>(SingleItem { .name_ = "1366x768", }),
           std::make_shared<SingleItem>(SingleItem { .name_ = "1280x1024", }),
           std::make_shared<SingleItem>(SingleItem { .name_ = "1280x960", }),
           std::make_shared<SingleItem>(SingleItem { .name_ = "1280x800", }),
           std::make_shared<SingleItem>(SingleItem { .name_ = "1280x768", }),
           std::make_shared<SingleItem>(SingleItem { .name_ = "1280x720", }),
           std::make_shared<SingleItem>(SingleItem { .name_ = "1152x864", }),
           std::make_shared<SingleItem>(SingleItem { .name_ = "1024x768", }),
           std::make_shared<SingleItem>(SingleItem { .name_ = "800x600", }),
        });

        listview_->SetOnItemClickListener([=, this](int idx, QWidget*) {
            auto item = listview_->GetItems().at(idx);
            auto split_size = item->name_.split("x");
            if (split_size.size() < 2) {
                return;
            }
            int width = split_size.at(0).toInt();
            int height = split_size.at(1).toInt();
            if (width <= 0 || height <= 0) {
                LOGE("Error monitor resolution size: {}", item->name_.toStdString());
                return;
            }
            auto monitor_name = context_->GetCapturingMonitorInfo().mon_name_;
            if (monitor_name.empty()) {
                LOGE("Target monitor name is empty");
                return;
            }
            context_->SendAppMessage(MsgChangeMonitorResolution {
                .monitor_name_ = monitor_name,
                .width_ = width,
                .height_ = height,
            });
        });

        root_layout->addWidget(listview_);

        root_layout->addStretch();
        setLayout(root_layout);
    }

    void ThirdResolutionPanel::paintEvent(QPaintEvent *event) {
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

    void ThirdResolutionPanel::Hide() {
        BaseWidget::Hide();
    }

    void ThirdResolutionPanel::Show() {
        BaseWidget::Show();
        this->SelectCapturingMonitorSize();
    }

    void ThirdResolutionPanel::SelectCapturingMonitorSize() {
        auto monitor_info = context_->GetCapturingMonitorInfo();
        if (monitor_info.Width() <= 0 || monitor_info.Height() <= 0) {
            return;
        }
        listview_->SelectByName(std::format("{}x{}", monitor_info.Width(), monitor_info.Height()));
    }

}