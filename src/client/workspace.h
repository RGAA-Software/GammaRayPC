//
// Created by RGAA on 2023-12-27.
//

#ifndef TC_CLIENT_PC_WORKSPACE_H
#define TC_CLIENT_PC_WORKSPACE_H

#include <QWidget>
#include <QMainWindow>

namespace tc
{

    class ClientContext;
    class ThunderSdk;
    class OpenGLVideoWidget;

    class Workspace : public QMainWindow {
    public:

        explicit Workspace(const std::shared_ptr<ClientContext>& ctx, QWidget* parent = nullptr);
        ~Workspace() override;

    private:

        void RegisterSdkMsgCallbacks();

    private:

        std::shared_ptr<ClientContext> context_ = nullptr;
        std::shared_ptr<ThunderSdk> sdk_ = nullptr;

        OpenGLVideoWidget* video_widget_ = nullptr;

    };

}

#endif //TC_CLIENT_PC_WORKSPACE_H
