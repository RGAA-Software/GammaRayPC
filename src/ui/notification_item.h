//
// Created by RGAA on 17/07/2024.
//

#ifndef GAMMARAYPC_NOTIFICATION_ITEM_H
#define GAMMARAYPC_NOTIFICATION_ITEM_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QProgressBar>

namespace tc
{

    class NotificationItem : public QWidget {
    public:
        NotificationItem(QWidget* parent = nullptr);

        void paintEvent(QPaintEvent *event) override;
        void enterEvent(QEnterEvent *event) override;
        void leaveEvent(QEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;

    private:
        bool enter_ = false;
        bool pressed_ = false;
        QLabel* icon_ = nullptr;
        QLabel* title_ = nullptr;
        QLabel* sub_title_ = nullptr;
        QProgressBar* progress_ = nullptr;
    };

}

#endif //GAMMARAYPC_NOTIFICATION_ITEM_H
