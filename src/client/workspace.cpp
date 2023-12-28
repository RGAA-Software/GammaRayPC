//
// Created by RGAA on 2023-12-27.
//

#include "workspace.h"

#include "thunder_sdk.h"

namespace tc
{

    Workspace::Workspace(const std::shared_ptr<ClientContext>& ctx, QWidget* parent) {
        this->context_ = ctx;

        sdk_ = ThunderSdk::Make();
//        bool ssl_ = false;
//        std::string ip_;
//        int port_;
//        std::string req_path_;
        sdk_->Init(ThunderSdkParams {
            .ssl_ = false,
            .ip_ = "127.0.0.1",
            .port_ = 9002,
            .req_path_ = "/media",
        });
        sdk_->Start();

    }

    Workspace::~Workspace() {

    }



}