//
// Created by hy on 17/08/2024.
//

#ifndef GAMMARAYPC_FLOAT_3RD_SCALE_PANEL_H
#define GAMMARAYPC_FLOAT_3RD_SCALE_PANEL_H

#include "base_widget.h"
#include <QPainter>
#include "settings.h"

namespace tc
{

    class Settings;
    class SwitchButton;

    class ThirdScalePanel : BaseWidget {
    public:
        explicit ThirdScalePanel(const std::shared_ptr<ClientContext>& ctx, QWidget* parent = nullptr);
        void paintEvent(QPaintEvent *event) override;

    private:
        void UpdateScaleMode(ScaleMode mode);

    private:
        Settings* settings_ = nullptr;
        SwitchButton* sb_keep_ratio_ = nullptr;
        SwitchButton* sb_fullscreen_ = nullptr;
        SwitchButton* sb_origin_size_ = nullptr;
    };

}

#endif
