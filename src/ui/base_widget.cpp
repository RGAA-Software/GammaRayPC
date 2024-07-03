//
// Created by hy on 3/07/2024.
//

#include "base_widget.h"

namespace tc
{

    BaseWidget::BaseWidget(const std::shared_ptr<ClientContext>& ctx, QWidget* parent) : QWidget(parent), context_(ctx) {

    }

}