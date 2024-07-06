//
// Created by RGAA on 6/07/2024.
//

#include "notification_panel.h"

namespace tc
{

    NotificationPanel::NotificationPanel(const std::shared_ptr<ClientContext>& ctx, QWidget* parent) : BaseWidget(ctx, parent) {
        this->setFixedWidth(350);
    }

}