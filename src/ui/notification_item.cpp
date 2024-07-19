//
// Created by RGAA on 17/07/2024.
//

#include"notification_item.h"
#include "no_margin_layout.h"

#include <QLabel>
#include <QGraphicsDropShadowEffect>

namespace tc
{

    NotificationItem::NotificationItem(QWidget* parent) : QWidget(parent) {
        auto ps = new QGraphicsDropShadowEffect();
        ps->setBlurRadius(5);
        ps->setOffset(0, 0);
        ps->setColor(0xbbbbbb);
        this->setGraphicsEffect(ps);

        auto root_layout = new NoMarginHLayout();
        root_layout->addSpacing(30);
        root_layout->setAlignment(Qt::AlignVCenter);
        {
            auto lbl = new QLabel(this);
            icon_ = lbl;
            lbl->setFixedSize(45, 45);
            lbl->setStyleSheet("background:#909090;");
            root_layout->addWidget(lbl);
        }
        {
            auto info_layout = new NoMarginVLayout();
            auto lbl = new QLabel(this);
            title_ = lbl;
            title_->setText("Title");
            title_->setFixedWidth(230);
            title_->setStyleSheet("background:transparent;font-size: 16px; font-weight:700;");
            info_layout->addSpacing(15);
            info_layout->addWidget(title_);

            progress_ = new QProgressBar();
            progress_->setMaximum(100);
            progress_->setValue(100);
            progress_->setFixedSize(200, 5);
            info_layout->addSpacing(20);
            info_layout->addWidget(progress_);

            info_layout->addStretch();
            root_layout->addSpacing(10);
            root_layout->addLayout(info_layout);
        }

        root_layout->addStretch();
        setLayout(root_layout);
    }

    void NotificationItem::paintEvent(QPaintEvent *event) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        if (pressed_) {
            painter.setBrush(QColor(0xefefff));
        } else if (enter_) {
            painter.setBrush(QColor(0xf2f2f2ff));
        } else {
            painter.setBrush(QColor(0xffffff));
        }
        painter.setPen(Qt::NoPen);
        int offset = 15;
        float radius = 7;
        painter.drawRoundedRect(offset-4, 0, this->width()-offset*2, this->height(), radius, radius);
    }

    void NotificationItem::enterEvent(QEnterEvent *event) {
        enter_ = true;
        repaint();
    }

    void NotificationItem::leaveEvent(QEvent *event) {
        enter_ = false;
        repaint();
    }

    void NotificationItem::mousePressEvent(QMouseEvent *event) {
        pressed_ = true;
        repaint();
    }

    void NotificationItem::mouseReleaseEvent(QMouseEvent *event) {
        pressed_ = false;
        repaint();
    }

}