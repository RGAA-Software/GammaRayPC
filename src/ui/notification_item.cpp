//
// Created by RGAA on 17/07/2024.
//

#include"notification_item.h"
#include "no_margin_layout.h"
#include "client_context.h"
#include <QLabel>
#include <QGraphicsDropShadowEffect>

namespace tc
{

    NotificationItem::NotificationItem(const std::shared_ptr<ClientContext>& ctx, const std::string& nid, const std::string& icon_path, QWidget* parent) : QWidget(parent) {
        context_ = ctx;
        nid_ = nid;

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
            //lbl->setStyleSheet("background:#909090;");
            root_layout->addWidget(lbl);

            if (!icon_path.empty()) {
                QImage image;
                image.load(icon_path.c_str());
                icon_pixmap_ = QPixmap::fromImage(image);
                icon_pixmap_ = icon_pixmap_.scaled(lbl->width(), lbl->height());
                lbl->setPixmap(icon_pixmap_);
            }

        }
        {
            auto info_layout = new NoMarginVLayout();
            auto lbl = new QLabel(this);
            title_ = lbl;
            title_->setText("Title");
            title_->setFixedWidth(210);
            title_->setStyleSheet("background:transparent;font-size: 15px; font-weight:700;");
            info_layout->addSpacing(13);
            info_layout->addWidget(title_);

            progress_info_ = new QLabel(this);
            progress_info_->setAlignment(Qt::AlignRight);
            progress_info_->setFixedWidth(210);
            progress_info_->setText("0/100");
            info_layout->addSpacing(4);
            info_layout->addWidget(progress_info_);

            progress_ = new QProgressBar();
            progress_->setMaximum(100);
            progress_->setValue(0);
            progress_->setFixedSize(210, 5);
            info_layout->addSpacing(1);
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

    void NotificationItem::UpdateTitle(const std::string& title) {
        context_->PostUITask([=, this]() {
            title_->setText(title.c_str());
        });
    }

    void NotificationItem::UpdateProgress(int progress) {
        context_->PostUITask([=, this]() {
            progress_->setValue(progress);
            progress_info_->setText(std::format("{}/100", progress).c_str());
        });
    }

}