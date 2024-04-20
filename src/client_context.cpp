//
// Created by RGAA on 2023-12-27.
//

#include "client_context.h"

#include "settings.h"
#include "tc_common_new/message_notifier.h"
#include "tc_common_new/shared_preference.h"
#include "tc_common_new/thread.h"
#include "db/stream_db_manager.h"

namespace tc
{

    ClientContext::ClientContext(QObject* parent) : QObject(parent) {
        this->msg_notifier_ = std::make_shared<MessageNotifier>();

        sp_ = std::make_shared<SharedPreference>();
        sp_->Init("", "app.dat");

        auto settings = Settings::Instance();
        settings->SetSharedPreference(sp_);
        settings->LoadSettings();

        db_mgr_ = std::make_shared<StreamDBManager>();

        task_thread_ = Thread::Make("context_thread", 128);
        task_thread_->Poll();
    }

    ClientContext::~ClientContext() {

    }

    void ClientContext::PostTask(std::function<void()>&& task) {
        task_thread_->Post(SimpleThreadTask::Make(std::move(task)));
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

    std::shared_ptr<StreamDBManager> ClientContext::GetDBManager() {
        return db_mgr_;
    }

    void ClientContext::SendAppMessage(const std::shared_ptr<AppMessage>& msg) {

    }

}