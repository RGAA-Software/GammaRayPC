//
// Created by RGAA on 2023-12-27.
//

#include <QHBoxLayout>
#include "workspace.h"

#include "thunder_sdk.h"
#include "opengl_video_widget.h"
#include "client_context.h"
#include "tc_common/data.h"
#include "tc_common/log.h"
#include "audio_player.h"

namespace tc
{

    Workspace::Workspace(const std::shared_ptr<ClientContext>& ctx, QWidget* parent) {
        this->context_ = ctx;

        sdk_ = ThunderSdk::Make(ctx->GetMessageNotifier());
        sdk_->Init(ThunderSdkParams {
            .ssl_ = false,
            //.ip_ = "192.168.31.5",
            .ip_ = "10.0.0.241",
            .port_ = 9002,
            .req_path_ = "/media",
        }, nullptr, DecoderRenderType::kFFmpegI420);

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

        sdk_->RegisterOnAudioFrameDecodedCallback([=, this](const std::shared_ptr<Data>& data, int samples, int channels, int bits) {
            //LOGI("data size: {}, samples: {}, channel: {}, bits: {}", data->Size(), samples, channels, bits);
            if (!audio_player_) {
                audio_player_ = std::make_shared<AudioPlayer>();
                context_->PostUITask([=, this]() {
                    audio_player_->Init(samples, channels);
                });
                return;
            }
            context_->PostUITask([=, this]() {
                audio_player_->Write(data);
            });
        });
    }

}