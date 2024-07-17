//
// Created by RGAA on 17/07/2024.
//

#ifndef GAMMARAYPC_NOTIFICATION_ITEM_H
#define GAMMARAYPC_NOTIFICATION_ITEM_H

#include <QWidget>
#include <QPainter>

namespace tc
{

    class NotificationItem : public QWidget {
    public:
        NotificationItem(QWidget* parent = nullptr);

        void paintEvent(QPaintEvent *event) override;
    };

}

#endif //GAMMARAYPC_NOTIFICATION_ITEM_H
