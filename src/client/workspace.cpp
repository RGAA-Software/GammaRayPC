//
// Created by RGAA on 2023-12-27.
//

#include <QHBoxLayout>
#include "workspace.h"

#include "thunder_sdk.h"
#include "opengl_video_widget.h"

namespace tc
{

    Workspace::Workspace(const std::shared_ptr<ClientContext>& ctx, QWidget* parent) {
        this->context_ = ctx;

        sdk_ = ThunderSdk::Make();
        sdk_->Init(ThunderSdkParams {
            .ssl_ = false,
            .ip_ = "127.0.0.1",
            .port_ = 9002,
            .req_path_ = "/media",
        });

        // ui
        auto root_layout = new QHBoxLayout();
        auto root_widget = new QWidget(this);
        root_widget->setLayout(root_layout);

        video_widget_ = new OpenGLVideoWidget(ctx, sdk_, 0, RawImageFormat::kI420, this);
        root_layout->addWidget(video_widget_);

        setCentralWidget(root_widget);

        //
        RegisterSdkMsgCallbacks();
        sdk_->Start();

    }

    Workspace::~Workspace() {

    }

    void Workspace::RegisterSdkMsgCallbacks() {
        sdk_->RegisterOnVideoFrameDecodedCallback([=, this](const std::shared_ptr<RawImage>& image) {
            video_widget_->RefreshI420Image(image);
        });
    }

}