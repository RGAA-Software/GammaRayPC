//
// Created by hy on 9/07/2024.
//

#include "file_transfer.h"
#include "client_context.h"
#include "tc_common_new/log.h"
#include "tc_common_new/thread.h"
#include "settings.h"
#include "send_file.h"
#include "tc_message.pb.h"

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
        client_->set_auto_reconnect(true);
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
            } else {
                LOGI("connect success.");
            }
        }).bind_disconnect([&]() {
            LOGE("Disconnect!!!");

        }).bind_upgrade([&]() {
            if (asio2::get_last_error()) {
                LOGE("update failure: {}->{}", asio2::last_error_val(), asio2::last_error_msg().c_str());
            } else {
                LOGI("update success.");
            }
        }).bind_recv([=, this](std::string_view data) {
            this->ParseRespMessage(data);
        });

        auto host = Settings::Instance()->remote_address_;
        auto port = Settings::Instance()->file_transfer_port_;
        auto path = Settings::Instance()->file_transfer_path_;
        if (!client_->async_start(host, port, path)) {
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
                this->RequestSendingFile(send_file);

                // 2.2 ready to send or error
                std::unique_lock<std::mutex> lk(send_mtx_);
//                send_cv_.wait(lk);
//                if (!continue_sending_) {
//                    LOGW("Ignore sending : {}", send_file->file_path_.toStdString());
//                    continue;
//                }
                LOGI("Sending: {}, file size: {}", send_file->file_path_.toStdString(), send_file->file_size_);

                send_file->Send([=, this](const std::string& proto_msg, uint64_t total_size, uint64_t offset) {
                    // 2.3 sending
                    if (!IsConnected()) {
                        LOGE("Client disconnected when sending file.");
                        return;
                    }
                    client_->async_send(proto_msg);
                    // 2.4 checking
//                    if (send_size != proto_msg.size()) {
//                        LOGE("Send failed, send_size({}) != proto_msg.size({})", send_size, proto_msg.size());
//                    }
                });
            }
        });
    }

    void FileTransferChannel::RequestSendingFile(const std::shared_ptr<SendFile>& file) {
        tc::Message msg;
        msg.set_type(MessageType::kFileTransfer);
        auto fs = msg.mutable_file_transfer();
        fs->set_state(FileTransfer_FileTransferState_kRequestFileTransfer);
        fs->set_file_type(FileTransfer_FileType_kFile);
        fs->set_relative_path("");
        fs->set_filename(file->file_->FileName());
        fs->set_data("");
        fs->set_filesize(file->file_size_);
        fs->set_transferred_size(0);
        fs->set_file_md5("");
        auto proto_msg = msg.SerializeAsString();
        client_->async_send(proto_msg);

        LOGI("Send request file transfer.");
    }

    void FileTransferChannel::ParseRespMessage(std::string_view _data) {
        auto msg = std::make_shared<tc::Message>();
        std::string data(_data.data(), _data.size());
        if (!msg->ParseFromString(data)) {
            LOGE("Parse proto message failed!");
            return;
        }

        LOGI("Resp type: {}", (int)msg->type());
        if (msg->type() == MessageType::kRespFileTransfer) {
            auto rft = msg->resp_file_transfer();
            if (rft.state() == RespFileTransfer_FileTransferRespState_kTransferReady) {
                continue_sending_ = true;
                LOGI("Continue to send file");
            }
            send_cv_.notify_one();
        }
    }

}
