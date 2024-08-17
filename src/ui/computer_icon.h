//
// Created by hy on 17/08/2024.
//

#ifndef GAMMARAYPC_COMPUTER_ICON_H
#define GAMMARAYPC_COMPUTER_ICON_H

#include "base_widget.h"

namespace tc
{

    class ComputerIcon : public BaseWidget {
    public:
        explicit ComputerIcon(const std::shared_ptr<ClientContext>& ctx, int idx, QWidget* parent = nullptr);
        void paintEvent(QPaintEvent *event) override;

    private:
        QPixmap pixmap_;
        int index_ = 0;
    };

}

#endif //GAMMARAYPC_COMPUTER_ICON_H
