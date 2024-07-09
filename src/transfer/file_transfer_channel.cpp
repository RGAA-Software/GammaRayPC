//
// Created by hy on 9/07/2024.
//

#include "file_transfer_channel.h"
#include "client_context.h"

namespace beast = boost::beast;
namespace websocket = beast::websocket;
using tcp = asio::ip::tcp;

namespace tc
{
    FileTransferChannel::FileTransferChannel(const std::shared_ptr<ClientContext>& ctx) {
        context_ = ctx;
    }

    void FileTransferChannel::Start(const std::string& host, int port, const std::string& path) {
        this->host_ = host;
        this->port_ = port;
        this->path_ = path;
        asio::co_spawn(*context_->GetBoostIoContext(), Connect(), asio::detached);
    }

    void FileTransferChannel::Exit() {
        stopped_ = true;
        if (ws_) {
            ws_->close(websocket::close_code::normal);
        }
    }

    asio::awaitable<void> FileTransferChannel::Connect() {
        auto executor = co_await asio::this_coro::executor;
        tcp::resolver resolver(executor);
        ws_ = std::make_unique<websocket::stream<beast::tcp_stream>>(executor);
        while (!stopped_) {
            bool should_retry = false;
            try {
                auto const results = co_await resolver.async_resolve(host_, std::to_string(port_), asio::use_awaitable);
                co_await ws_->next_layer().async_connect(results, asio::use_awaitable);
                co_await ws_->async_handshake(host_, path_, asio::use_awaitable);

                while (!stopped_) {
                    co_await ws_->async_write(asio::buffer("Jack sparrow"), asio::use_awaitable);
                    beast::flat_buffer buffer;
                    co_await ws_->async_read(buffer, asio::use_awaitable);
                    std::cout << "Received: " << beast::buffers_to_string(buffer.data()) << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                }

                co_await ws_->async_close(websocket::close_code::normal, asio::use_awaitable);
                break;

            } catch (std::exception const& e) {
                std::cerr << "Connection failed: " << e.what() << ", retrying..." << std::endl;
                should_retry = true;
            }

            // 在 catch 块外部处理重试逻辑
            if (should_retry) {
                std::cout << "will retry..." << std::endl;
                // 等待一段时间再重试
                co_await asio::steady_timer(executor, std::chrono::seconds(3)).async_wait(asio::use_awaitable);
                // 重新创建WebSocket stream对象
                ws_ = std::make_unique<websocket::stream<beast::tcp_stream>>(executor);
            }
        }
    }

}
