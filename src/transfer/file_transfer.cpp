//
// Created by hy on 9/07/2024.
//

#include "file_transfer.h"
#include "client_context.h"
#include "tc_common_new/log.h"
#include "tc_common_new/thread.h"
#include "settings.h"
#include "send_file.h"

namespace tc
{
    FileTransferChannel::FileTransferChannel(const std::shared_ptr<ClientContext> &ctx) {
        context_ = ctx;
        sender_thread_ = Thread::Make("file transfer", 64);
        sender_thread_->Poll();
    }

    void FileTransferChannel::Start() {
        client_ = std::make_shared<asio2::ws_client>();
        client_->set_connect_timeout(std::chrono::seconds(5));
        client_->bind_init([&]() {
            client_->ws_stream().binary(true);
            client_->ws_stream().set_option(
                    websocket::stream_base::decorator([](websocket::request_type &req) {
                        req.set(http::field::authorization, "websocket-client_-authorization");
                    })
            );

        }).bind_connect([&]() {
            if (asio2::get_last_error()) {
                LOGE("connect failure: {}->{}", asio2::last_error_val(), asio2::last_error_msg().c_str());
            }
        }).bind_upgrade([&]() {
            if (asio2::get_last_error()) {
                LOGE("update failure: {}->{}", asio2::last_error_val(), asio2::last_error_msg().c_str());
            } else {
                LOGE("update success.");
            }
        }).bind_recv([&](std::string_view data) {

        });

        auto host = Settings::Instance()->remote_address_;
        auto port = Settings::Instance()->file_transfer_port_;
        auto path = Settings::Instance()->file_transfer_path_;
        if (!client_->start(host, port, path)) {
            LOGE("connect websocket server failure : {}->{}",
                   asio2::last_error_val(), asio2::last_error_msg().c_str());
        }
    }

    void FileTransferChannel::Exit() {
        if (client_) {
            client_->stop();
        }
    }

    bool FileTransferChannel::IsConnected() {
        return client_ && client_->is_started();
    }

    void FileTransferChannel::SendFiles(const std::vector<QString>& files_path) {
        sender_thread_->Post([=, this]() {
            std::queue<std::shared_ptr<SendFile>> file_queue;
            // 1. read file info
            for (const auto& path : files_path) {
                auto send_file = std::make_shared<SendFile>(path, 4096);
                file_queue.push(send_file);
            }

            // 2. send one by one
            while(!file_queue.empty() && !stop_sending_) {
                auto send_file = file_queue.front();
                file_queue.pop();
                // 2.1 request to send the file
                // 2.2 ready to send or error

                send_file->Send([=, this](const std::string& proto_msg, uint64_t total_size, uint64_t offset) {
                    // 2.3 sending
                    if (!IsConnected()) {
                        LOGE("Client disconnected when sending file.");
                        return;
                    }
                    auto send_size = client_->send(proto_msg);
                    LOGI("Send size: {}, msg size: {}", send_size, proto_msg.size());
                    // 2.4 checking

                });
            }
        });
    }

}
