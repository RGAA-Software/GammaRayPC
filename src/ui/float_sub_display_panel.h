//
// Created by hy on 17/08/2024.
//

#ifndef GAMMARAYPC_FLOAT_SUB_DISPLAY_PANEL_H
#define GAMMARAYPC_FLOAT_SUB_DISPLAY_PANEL_H

#include "base_widget.h"
#include <QPainter>

namespace tc
{

    enum SubDisplayType {
        kScale,
        kResolution,
    };

    class SubDisplayPanel : BaseWidget {
    public:
        explicit SubDisplayPanel(const std::shared_ptr<ClientContext>& ctx, QWidget* parent = nullptr);
        void paintEvent(QPaintEvent *event) override;
        void Show() override;
        void Hide() override;

    private:
        BaseWidget* GetSubPanel(const SubDisplayType& type);
        void HideAllSubPanels();

    private:
        std::map<SubDisplayType, BaseWidget*> sub_panels_;

    };

}

#endif
