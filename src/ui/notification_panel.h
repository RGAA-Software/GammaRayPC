//
// Created by RGAA on 6/07/2024.
//

#ifndef GAMMARAYPC_NOTIFICATION_PANEL_H
#define GAMMARAYPC_NOTIFICATION_PANEL_H

#include "base_widget.h"

namespace tc
{

    class ClientContext;

    class NotificationPanel : public BaseWidget {
    public:
        explicit NotificationPanel(const std::shared_ptr<ClientContext>& ctx, QWidget* parent = nullptr);
        void paintEvent(QPaintEvent *event) override;

    private:

    };

}

#endif //GAMMARAYPC_NOTIFICATION_PANEL_H
