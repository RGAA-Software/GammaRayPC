//
// Created by RGAA on 2023-12-27.
//

#ifndef TC_CLIENT_PC_CLIENT_CONTEXT_H
#define TC_CLIENT_PC_CLIENT_CONTEXT_H

#include <functional>

#include <QObject>
#include <QWidget>
#include <boost/asio.hpp>
#include "tc_common_new/message_notifier.h"

namespace tc
{
    class AppMessage;
    class Thread;
    class StreamDBManager;
    class SharedPreference;

    class ClientContext : public QObject, public std::enable_shared_from_this<ClientContext> {
    public:

        explicit ClientContext(const std::string& name, QObject* parent = nullptr);
        ~ClientContext() override;
        void Init();
        void PostTask(std::function<void()>&& task);
        void PostUITask(std::function<void()>&& task);
        std::shared_ptr<MessageNotifier> GetMessageNotifier();
        std::shared_ptr<MessageListener> ObtainMessageListener();
        std::shared_ptr<StreamDBManager> GetDBManager();
        void SaveKeyValue(const std::string& k, const std::string& v);
        std::string GetValueByKey(const std::string& k);
        std::shared_ptr<boost::asio::io_context> GetBoostIoContext();

        template<class T>
        void SendAppMessage(const T& msg) {
            msg_notifier_->SendAppMessage(msg);
        }

        void Exit();

    private:
        std::shared_ptr<MessageNotifier> msg_notifier_ = nullptr;
        std::shared_ptr<StreamDBManager> db_mgr_ = nullptr;
        std::shared_ptr<SharedPreference> sp_ = nullptr;
        std::shared_ptr<Thread> task_thread_ = nullptr;
        std::string name_;
        std::shared_ptr<Thread> io_ctx_thread_ = nullptr;
        std::shared_ptr<boost::asio::io_context> boost_io_ctx_ = nullptr;
        std::unique_ptr<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>> work_guard_;
    };

}

#endif //TC_CLIENT_PC_CLIENT_CONTEXT_H
