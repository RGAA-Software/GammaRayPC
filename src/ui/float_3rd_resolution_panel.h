//
// Created by hy on 17/08/2024.
//

#ifndef GAMMARAYPC_FLOAT_3RD_RESOLUTION_PANEL_H
#define GAMMARAYPC_FLOAT_3RD_RESOLUTION_PANEL_H

#include "base_widget.h"
#include <QPainter>

namespace tc
{

    class Settings;
    class SwitchButton;
    class SingleSelectedList;

    class ThirdResolutionPanel : BaseWidget {
    public:
        explicit ThirdResolutionPanel(const std::shared_ptr<ClientContext>& ctx, QWidget* parent = nullptr);
        void paintEvent(QPaintEvent *event) override;
        void Hide() override;
        void Show() override;
    private:
        void SelectCapturingMonitorSize();

    private:
        Settings* settings_ = nullptr;
        SingleSelectedList* listview_ = nullptr;
    };

}

#endif
