//
// Created by RGAA on 2023/8/19.
//

#include "stream_item_widget.h"

#include <QPainter>

namespace tc
{

    StreamItemWidget::StreamItemWidget(int bg_color, QWidget* parent) : QWidget(parent) {
        this->bg_color_ = bg_color;
        icon_ = QPixmap::fromImage(QImage(":/resources/image/windows.svg"));
        icon_ = icon_.scaled(icon_.width()/3, icon_.height()/3, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    StreamItemWidget::~StreamItemWidget() {

    }

    void StreamItemWidget::paintEvent(QPaintEvent *event) {
        //QWidget::paintEvent(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::RenderHint::Antialiasing);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(0xEAF7FF));
        painter.drawRect(0, 0, QWidget::width(), QWidget::height());
        painter.setBrush(QBrush(QColor(bg_color_)));
        int radius = 12;
        painter.drawRoundedRect(0, 0, width(), height(), radius, radius);

        QPen pen;
        int border_width = 2;;
        if (enter_) {
            pen.setColor(QColor(0x38, 0x64, 0x87));
        }
        else {
            pen.setColor(QColor(0x38, 0x64, 0x87, 0x11));
        }
        pen.setWidth(border_width);
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);
        painter.drawRoundedRect(1, 1, width() - border_width, height() - border_width, radius, radius);

        int margin = 20;
        painter.drawPixmap(QWidget::width() - icon_.width() - margin, margin, icon_);

    }

    void StreamItemWidget::enterEvent(QEnterEvent *event) {
        enter_ = true;
        update();
    }

    void StreamItemWidget::leaveEvent(QEvent *event) {
        enter_ = false;
        update();
    }

}