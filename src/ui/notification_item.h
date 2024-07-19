//
// Created by RGAA on 17/07/2024.
//

#ifndef GAMMARAYPC_NOTIFICATION_ITEM_H
#define GAMMARAYPC_NOTIFICATION_ITEM_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QProgressBar>
#include <string>
#include <QPixmap>

namespace tc
{

    class ClientContext;

    class NotificationItem : public QWidget {
    public:
        explicit NotificationItem(const std::shared_ptr<ClientContext>& ctx, const std::string& nid, const std::string& icon_path = "", QWidget* parent = nullptr);

        void paintEvent(QPaintEvent *event) override;
        void enterEvent(QEnterEvent *event) override;
        void leaveEvent(QEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;

        void UpdateTitle(const std::string& title);
        void UpdateProgress(int progress);

    private:
        std::shared_ptr<ClientContext> context_ = nullptr;
        bool enter_ = false;
        bool pressed_ = false;
        QLabel* icon_ = nullptr;
        QLabel* title_ = nullptr;
        QLabel* sub_title_ = nullptr;
        QLabel* progress_info_ = nullptr;
        QProgressBar* progress_ = nullptr;
        std::string nid_;
        QPixmap icon_pixmap_;
    };

}

#endif //GAMMARAYPC_NOTIFICATION_ITEM_H
