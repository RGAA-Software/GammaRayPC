//
// Created by RGAA on 2023-12-27.
//

#include "workspace.h"

namespace tc
{

    Workspace::Workspace(const std::shared_ptr<ClientContext>& ctx, QWidget* parent) {
        this->context_ = ctx;
    }

    Workspace::~Workspace() {

    }



}