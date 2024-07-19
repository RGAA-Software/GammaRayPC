//
// Created by RGAA on 6/07/2024.
//

#include "notification_panel.h"
#include "no_margin_layout.h"
#include "notification_item.h"
#include "client_context.h"
#include "tc_common_new/message_notifier.h"

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

        list_ = new QListWidget(this);
        list_->setResizeMode(QListView::ResizeMode::Fixed);
        list_->setMovement(QListView::Movement::Static);
        list_->setFlow(QListView::Flow::TopToBottom);
        list_->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        list_->setStyleSheet("QListWidget::item:selected { background-color: transparent; }");

        auto root_layout = new NoMarginVLayout();
        root_layout->addWidget(list_);
        setLayout(root_layout);

        msg_listener_ = context_->ObtainMessageListener();
        msg_listener_->Listen<EvtFileTransferReady>([=, this](const EvtFileTransferReady& evt) {
            context_->PostUITask([=, this]() {
                AddItem(evt);
            });
        });

        for (int i = 0; i < 10; i++) {
            AddItem(EvtFileTransferReady{});
        }
    }

    void NotificationPanel::AddItem(const EvtFileTransferReady& evt) {
        auto widget = new NotificationItem(this);
        auto item = new QListWidgetItem();
        item->setSizeHint(QSize(this->width(), 90));
        list_->addItem(item);
        list_->setItemWidget(item, widget);
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