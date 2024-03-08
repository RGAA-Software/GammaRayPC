//
// Created by RGAA on 2023-12-27.
//

#ifndef TC_CLIENT_PC_CLIENT_CONTEXT_H
#define TC_CLIENT_PC_CLIENT_CONTEXT_H

#include <functional>

#include <QObject>
#include <QWidget>

namespace tc
{

    class MessageNotifier;
    class MessageListener;
    class StreamDBManager;
    class SharedPreference;
    class AppMessage;
    class Thread;

    class ClientContext : public QObject {
    public:

        explicit ClientContext(QObject* parent = nullptr);
        ~ClientContext() override;

        void PostTask(std::function<void()>&& task);
        void PostUITask(std::function<void()>&& task);

        std::shared_ptr<MessageNotifier> GetMessageNotifier();
        std::shared_ptr<MessageListener> ObtainMessageListener();

        std::shared_ptr<StreamDBManager> GetDBManager();
        void SendAppMessage(const std::shared_ptr<AppMessage>& msg);

    private:

        std::shared_ptr<MessageNotifier> msg_notifier_ = nullptr;
        std::shared_ptr<StreamDBManager> db_mgr_ = nullptr;
        std::shared_ptr<SharedPreference> sp_ = nullptr;
        std::shared_ptr<Thread> task_thread_ = nullptr;

    };

}

#endif //TC_CLIENT_PC_CLIENT_CONTEXT_H
