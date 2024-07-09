//
// Created by hy on 9/07/2024.
//

#ifndef GAMMARAYPC_FILE_TRANSFER_CHANNEL_H
#define GAMMARAYPC_FILE_TRANSFER_CHANNEL_H

#include <memory>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <chrono>
#include <memory>

namespace asio = boost::asio;

namespace tc
{

    class ClientContext;

    class FileTransferChannel {
    public:
        explicit FileTransferChannel(const std::shared_ptr<ClientContext>& ctx);
        void Start(const std::string& host, int port, const std::string& path);
        void Exit();

    private:
        asio::awaitable<void> Connect();

    private:
        std::shared_ptr<ClientContext> context_ = nullptr;
        std::string host_;
        int port_;
        std::string path_;
        bool stopped_ = false;
        std::unique_ptr<boost::beast::websocket::stream<boost::beast::tcp_stream>> ws_ = nullptr;
    };

}

#endif //GAMMARAYPC_FILE_TRANSFER_CHANNEL_H
