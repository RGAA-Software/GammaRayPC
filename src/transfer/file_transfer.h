//
// Created by RGAA on 6/07/2024.
//

#ifndef GAMMARAYPC_FILE_TRANSFER_H
#define GAMMARAYPC_FILE_TRANSFER_H

#include <memory>
#include <functional>
#include <string>

namespace tc
{

    class ClientContext;
    class FileTransferChannel;
    class Settings;

    class FileTransfer {
    public:
        explicit FileTransfer(const std::shared_ptr<ClientContext>& ctx);
        void Start();
        void Exit();

    private:
        Settings* settings_ = nullptr;
        std::shared_ptr<ClientContext> context_ = nullptr;
        std::shared_ptr<FileTransferChannel> channel_ = nullptr;
    };

}

#endif //GAMMARAYPC_FILE_TRANSFER_H
