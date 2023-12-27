//
// Created by RGAA on 2023-12-27.
//

#include "client_context.h"

namespace tc
{

    ClientContext::ClientContext(QObject* parent) : QObject(parent) {

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

}