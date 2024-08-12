//
// Created by hy on 12/08/2024.
//

#include "debug_panel.h"
#include "key_state_panel.h"
#include "client_context.h"

namespace tc
{

    DebugPanel::DebugPanel(const std::shared_ptr<ClientContext>& ctx, QWidget* parent) : BaseWidget(ctx, parent) {
        key_state_panel_ = new KeyStatePanel(ctx, this);
    }

    void DebugPanel::resizeEvent(QResizeEvent *event) {

    }

    void DebugPanel::UpdateOnHeartBeat(const OnHeartBeat& hb) {
        context_->PostUITask([=, this]() {
            key_state_panel_->alt_item_->UpdateState(hb.alt_pressed());
        });
    }
}