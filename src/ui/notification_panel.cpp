//
// Created by RGAA on 6/07/2024.
//

#include "notification_panel.h"
#include <QGraphicsDropShadowEffect>

namespace tc
{

    NotificationPanel::NotificationPanel(const std::shared_ptr<ClientContext>& ctx, QWidget* parent) : BaseWidget(ctx, parent) {
        this->setStyleSheet(R"(background-color:#00000000;)");
        this->setFixedWidth(350);
        auto ps = new QGraphicsDropShadowEffect();
        ps->setBlurRadius(15);
        ps->setOffset(0, 0);
        ps->setColor(0x999999);
        this->setGraphicsEffect(ps);
    }

    void NotificationPanel::paintEvent(QPaintEvent *event) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(0xffffff));
        int border_radius = 7;
        painter.drawRoundedRect(this->rect(), border_radius, border_radius);
    }

}