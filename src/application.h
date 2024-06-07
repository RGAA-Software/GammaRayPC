//
// Created by hy on 2024/3/8.
//

#ifndef TC_CLIENT_PC_APPLICATION_H
#define TC_CLIENT_PC_APPLICATION_H

#include <QtWidgets/QMainWindow>
#include <QStackedWidget>

#include "db/stream_item.h"

namespace tc
{

    class AppMenu;
    class ClientContext;
    class StreamContent;
    class MessageListener;

    class Application : public QMainWindow {
    public:
        explicit Application(const std::shared_ptr<ClientContext>& ctx, QWidget* parent = nullptr);
        ~Application() override;

    private:
        void CreateLayout();
        void Init();
        static void LoadStyle(const std::string& name);
        void StartStreaming(const StreamItem& item);

    private:
        std::shared_ptr<ClientContext> context_ = nullptr;
        std::shared_ptr<MessageListener> msg_listener_ = nullptr;
        AppMenu* app_menu_ = nullptr;
        QStackedWidget* content_widget_ = nullptr;
        StreamContent* stream_content_ = nullptr;

    };

}

#endif //TC_CLIENT_PC_APPLICATION_H
