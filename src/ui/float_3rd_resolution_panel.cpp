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
#include <QLabel>

namespace tc
{

    ThirdResolutionPanel::ThirdResolutionPanel(const std::shared_ptr<ClientContext>& ctx, QWidget* parent) : BaseWidget(ctx, parent) {
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
            lbl->setText(tr("1920x1080"));
            layout->addSpacing(border_spacing);
            layout->addWidget(lbl);
            layout->addStretch();
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
            lbl->setText(tr("1600x900"));
            layout->addSpacing(border_spacing);
            layout->addWidget(lbl);

            layout->addStretch();
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
            lbl->setText(tr("1280x720"));
            layout->addSpacing(border_spacing);
            layout->addWidget(lbl);

            layout->addStretch();
            layout->addSpacing(border_spacing);

            root_layout->addSpacing(5);
            root_layout->addWidget(widget);
        }

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

}