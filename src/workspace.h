//
// Created by RGAA on 2023-12-27.
//

#ifndef TC_CLIENT_PC_WORKSPACE_H
#define TC_CLIENT_PC_WORKSPACE_H

#include <QWidget>
#include <QMainWindow>
#include "thunder_sdk.h"
#include "theme/QtAdvancedStylesheet.h"

namespace tc
{

    class ClientContext;
    class ThunderSdk;
    class OpenGLVideoWidget;
    class AudioPlayer;
    class FloatController;
    class FloatControllerPanel;
    class MessageListener;
    class Settings;

    class Workspace : public QMainWindow {
    public:

        explicit Workspace(const std::shared_ptr<ClientContext>& ctx, const ThunderSdkParams& params, QWidget* parent = nullptr);
        ~Workspace() override;

        void closeEvent(QCloseEvent *event) override;
        void changeEvent(QEvent* event) override;
        [[nodiscard]] bool IsActiveNow() const;

    private:
        void RegisterSdkMsgCallbacks();
        void Exit();

    private:
        std::shared_ptr<ClientContext> context_ = nullptr;
        std::shared_ptr<ThunderSdk> sdk_ = nullptr;
        std::shared_ptr<AudioPlayer> audio_player_ = nullptr;
        OpenGLVideoWidget* video_widget_ = nullptr;
        FloatController* float_controller_ = nullptr;
        FloatControllerPanel* controller_panel_ = nullptr;
        bool is_window_active_ = false;
        acss::QtAdvancedStylesheet* theme_{};
        std::shared_ptr<MessageListener> msg_listener_ = nullptr;
        Settings* settings_ = nullptr;
    };

}

#endif //TC_CLIENT_PC_WORKSPACE_H
