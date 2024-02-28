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

    class ClientContext : public QObject {
    public:

        explicit ClientContext(QObject* parent = nullptr);
        ~ClientContext() override;

        void PostTask(std::function<void()>&& task);
        void PostUITask(std::function<void()>&& task);

        std::shared_ptr<MessageNotifier> GetMessageNotifier();
        std::shared_ptr<MessageListener> ObtainMessageListener();

    private:

        std::shared_ptr<MessageNotifier> msg_notifier_ = nullptr;

    };

}

#endif //TC_CLIENT_PC_CLIENT_CONTEXT_H
