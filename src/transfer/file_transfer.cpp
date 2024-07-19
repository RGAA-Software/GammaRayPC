//
// Created by hy on 9/07/2024.
//

#include "file_transfer.h"
#include "client_context.h"
#include "tc_common_new/log.h"
#include "tc_common_new/thread.h"
#include "tc_common_new/time_ext.h"
#include "settings.h"
#include "send_file.h"
#include "tc_message.pb.h"
#include "ui/sized_msg_box.h"
#include "file_transfer_events.h"

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

                if (!send_file->IsOpen()) {
                    ErrorDialog(std::format("Can't open file: {}", send_file->file_path_.toStdString()).c_str());
                    continue;
                }

                // 2.1 request to send the file
                this->RequestSendingFile(send_file);

                // 2.2 ready to send or error
                std::unique_lock<std::mutex> lk(send_mtx_);
                send_cv_.wait_for(lk, std::chrono::seconds(10));
                if (!continue_sending_) {
                    LOGW("Ignore sending : {}", send_file->file_path_.toStdString());
                    continue;
                }
                LOGI("Sending: {}, file size: {}", send_file->file_path_.toStdString(), send_file->file_size_);

                bool send_failed = false;
                send_file->Send([&](const std::string& proto_msg, uint64_t total_size, uint64_t offset) -> bool {
                    // 2.3 sending
                    if (!IsConnected()) {
                        LOGE("Client disconnected when sending file.");
                        // break the reading cycle
                        send_failed = true;
                        return true;
                    }
                    client_->async_send(proto_msg, [=](size_t send_size) {
                        if (send_size != proto_msg.size()) {
                            LOGE("Send failed, expect: {}, but only {} send", proto_msg.size(), send_size);
                        }
                    });
                    return false;
                });

                if (send_failed) {
                    ErrorDialog(std::format("Send file: {} failed, please check your network.", send_file->file_path_.toStdString()).c_str());
                } else {
                    CompleteSending(send_file);
                }
            }
        });
    }

    void FileTransferChannel::RequestSendingFile(const std::shared_ptr<SendFile>& file) {
        tc::Message msg;
        msg.set_type(MessageType::kFileTransfer);
        auto fs = msg.mutable_file_transfer();
        fs->set_id(file->id_);
        fs->set_state(FileTransfer::kRequestFileTransfer);
        fs->set_file_type(FileTransfer_FileType_kFile);
        fs->set_filename(file->file_->FileName());
        fs->set_filesize(file->file_size_);
        fs->set_local_filepath(file->file_path_.toStdString());
        auto proto_msg = msg.SerializeAsString();
        client_->async_send(proto_msg);

        LOGI("Send request file transfer.");
    }

    void FileTransferChannel::CompleteSending(const std::shared_ptr<SendFile>& file) {
        tc::Message msg;
        msg.set_type(MessageType::kFileTransfer);
        auto fs = msg.mutable_file_transfer();
        fs->set_id(file->id_);
        fs->set_state(FileTransfer::kTransferOver);
        fs->set_file_type(FileTransfer_FileType_kFile);
        fs->set_filename(file->file_->FileName());
        fs->set_filesize(file->file_size_);
        fs->set_local_filepath(file->file_path_.toStdString());
        auto proto_msg = msg.SerializeAsString();
        client_->async_send(proto_msg);

        LOGI("Complete sending.");
    }

    void FileTransferChannel::ParseRespMessage(std::string_view _data) {
        auto msg = std::make_shared<tc::Message>();
        std::string data(_data.data(), _data.size());
        if (!msg->ParseFromString(data)) {
            LOGE("Parse proto message failed!");
            return;
        }

        if (msg->type() == MessageType::kRespFileTransfer) {
            auto rft = msg->resp_file_transfer();
            if (rft.state() == RespFileTransfer::kTransferReady) {
                LOGI("Transfer ready for : {}, id: {}", rft.filename(), rft.id());
                continue_sending_ = true;
                send_cv_.notify_one();

                context_->SendAppMessage(EvtFileTransferReady {
                    .id_ = rft.id(),
                    .name_ = rft.filename(),
                    .path_ = rft.local_filepath(),
                    .total_size_ = rft.filesize(),
                    .timestamp_ = TimeExt::GetCurrentTimestamp(),
                });

            } else if (rft.state() == RespFileTransfer::kFileDeleteFailed) {
                ErrorDialog(std::format("Can't delete file: {} in remote!", rft.filename()).c_str());
                continue_sending_ = false;
                send_cv_.notify_one();

                context_->SendAppMessage(EvtFileTransferDeleteFailed {
                    .id_ = rft.id(),
                    .name_ = rft.filename(),
                    .path_ = rft.local_filepath(),
                    .timestamp_ = TimeExt::GetCurrentTimestamp(),
                });

            } else if (rft.state() == RespFileTransfer::kTransferSuccess) {
                LOGI("Transfer success: {}, id: {}", rft.filename(), rft.id());
                InfoDialog(std::format("Transfer file: {} success", rft.filename()).c_str());

                context_->SendAppMessage(EvtFileTransferSuccess {
                    .id_ = rft.id(),
                    .name_ = rft.filename(),
                    .path_ = rft.local_filepath(),
                    .timestamp_ = TimeExt::GetCurrentTimestamp(),
                });

            } else if (rft.state() == RespFileTransfer::kTransferFailed) {
                LOGE("Transfer failed: {}, id: {}", rft.filename(), rft.id());
                ErrorDialog(std::format("Transfer failed: {}", rft.filename()).c_str());

                context_->SendAppMessage(EvtFileTransferFailed {
                        .id_ = rft.id(),
                        .name_ = rft.filename(),
                        .path_ = rft.local_filepath(),
                        .timestamp_ = TimeExt::GetCurrentTimestamp(),
                });

            } else if (rft.state() == RespFileTransfer::kTransferring) {
                //LOGI("Transferring file {}, progress: {}, id: {}", rft.filename(), (int)(rft.progress()*100), rft.id());
                context_->SendAppMessage(EvtFileTransferring {
                        .id_ = rft.id(),
                        .name_ = rft.filename(),
                        .path_ = rft.local_filepath(),
                        .progress_ = rft.progress(),
                        .total_size_ = rft.filesize(),
                        .transferred_size_ = rft.transferred_size(),
                        .timestamp_ = TimeExt::GetCurrentTimestamp(),
                });
            }
        }
    }

    void FileTransferChannel::InfoDialog(const QString& msg) {
        context_->PostUITask([=]() {
            auto dialog = SizedMessageBox::MakeInfoOkBox("Info", msg);
            dialog->exec();
        });
    }

    void FileTransferChannel::ErrorDialog(const QString& msg) {
        context_->PostUITask([=]() {
            auto dialog = SizedMessageBox::MakeErrorOkBox("Error", msg);
            dialog->exec();
        });
    }
}