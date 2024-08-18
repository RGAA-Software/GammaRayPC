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
        void enterEvent(QEnterEvent *event) override;
        void leaveEvent(QEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        void UpdateSelectedState(bool selected);

    private:
        QPixmap pixmap_;
        int index_ = 0;
        bool enter_ = false;
        bool pressed_ = false;
        int icon_size_ = 22;
        bool selected_ = false;
    };

}

#endif //GAMMARAYPC_COMPUTER_ICON_H
