//
// Created by RGAA on 17/07/2024.
//

#include "notification_item.h"
#include <QGraphicsDropShadowEffect>

namespace tc
{

    NotificationItem::NotificationItem(QWidget* parent) : QWidget(parent) {
        auto ps = new QGraphicsDropShadowEffect();
        ps->setBlurRadius(15);
        ps->setOffset(0, 0);
        ps->setColor(0x999999);
        this->setGraphicsEffect(ps);
    }

    void NotificationItem::paintEvent(QPaintEvent *event) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(QColor(0xffffff));
        painter.setPen(Qt::NoPen);
        int offset = 15;
        float radius = 7;
        painter.drawRoundedRect(offset-4, 0, this->width()-offset*2, this->height(), radius, radius);
    }

}