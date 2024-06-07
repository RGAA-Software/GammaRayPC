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

    ClientContext::ClientContext(const std::string& name, QObject* parent) : QObject(parent) {
        this->name_ = name;
        this->msg_notifier_ = std::make_shared<MessageNotifier>();
        sp_ = std::make_shared<SharedPreference>();
        sp_->Init("", std::format("app.{}.dat", name));

        auto settings = Settings::Instance();
        settings->SetSharedPreference(sp_);
        settings->LoadSettings();

        db_mgr_ = std::make_shared<StreamDBManager>();

        task_thread_ = Thread::Make("context_thread", 128);
        task_thread_->Poll();
    }

    ClientContext::~ClientContext() {
        Exit();
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

    void ClientContext::Exit() {
        if (task_thread_ && task_thread_->IsJoinable()) {
            task_thread_->Exit();
        }
    }

}