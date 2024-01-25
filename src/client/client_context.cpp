//
// Created by RGAA on 2023-12-27.
//

#include "client_context.h"

#include "tc_common/message_notifier.h"

namespace tc
{

    ClientContext::ClientContext(QObject* parent) : QObject(parent) {
        this->msg_notifier_ = std::make_shared<MessageNotifier>();
    }

    ClientContext::~ClientContext() {

    }

    void ClientContext::PostTask(std::function<void()>&& task) {
        //task_thread_->Post(SimpleThreadTask::Make(std::move(task)));
    }

    void ClientContext::PostUITask(std::function<void()>&& task) {
        QMetaObject::invokeMethod(this, [=, this]() {
            task();
        });
    }

    std::shared_ptr<MessageNotifier> ClientContext::GetMessageNotifier() {
        return msg_notifier_;
    }

    std::shared_ptr<MessageListener> ClientContext::ObtainMessageListener() {
        return msg_notifier_->CreateListener();
    }

}