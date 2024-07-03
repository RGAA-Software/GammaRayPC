//
// Created by RGAA on 2023-12-27.
//

#ifndef TC_CLIENT_PC_WORKSPACE_H
#define TC_CLIENT_PC_WORKSPACE_H

#include <QWidget>
#include <QMainWindow>
#include "thunder_sdk.h"

namespace tc
{

    class ClientContext;
    class ThunderSdk;
    class OpenGLVideoWidget;
    class AudioPlayer;
    class FloatController;

    class Workspace : public QMainWindow {
    public:

        explicit Workspace(const std::shared_ptr<ClientContext>& ctx, const ThunderSdkParams& params, QWidget* parent = nullptr);
        ~Workspace() override;

        void closeEvent(QCloseEvent *event) override;
        void changeEvent(QEvent* event);
        bool IsActiveNow();

    private:

        void RegisterSdkMsgCallbacks();

    private:

        std::shared_ptr<ClientContext> context_ = nullptr;
        std::shared_ptr<ThunderSdk> sdk_ = nullptr;
        std::shared_ptr<AudioPlayer> audio_player_ = nullptr;

        OpenGLVideoWidget* video_widget_ = nullptr;
        FloatController* float_controller_ = nullptr;
        bool is_window_active_ = false;

    };

}

#endif //TC_CLIENT_PC_WORKSPACE_H
