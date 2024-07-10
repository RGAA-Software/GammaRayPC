//
// Created by hy on 9/07/2024.
//

#ifndef GAMMARAYPC_FILE_TRANSFER_H
#define GAMMARAYPC_FILE_TRANSFER_H

#include <memory>
#include <iostream>
#include <chrono>
#include <memory>
#include <asio2/websocket/ws_client.hpp>
#include <QString>

namespace tc
{

    class Thread;
    class ClientContext;

    class FileTransferChannel {
    public:
        explicit FileTransferChannel(const std::shared_ptr<ClientContext>& ctx);
        void Start();
        void Exit();

        void SendFiles(const std::vector<QString>& files);

    private:
        std::shared_ptr<ClientContext> context_ = nullptr;
        std::shared_ptr<asio2::ws_client> client_ = nullptr;
        std::shared_ptr<Thread> sender_thread_ = nullptr;
    };

}

#endif //GAMMARAYPC_FILE_TRANSFER_H
