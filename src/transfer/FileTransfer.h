//
// Created by RGAA on 6/07/2024.
//

#ifndef GAMMARAYPC_FILETRANSFER_H
#define GAMMARAYPC_FILETRANSFER_H

#include <memory>
#include <functional>
#include <string>

namespace tc
{

    class ClientContext;

    class FileTransfer {
    public:
        explicit FileTransfer(const std::shared_ptr<ClientContext>& ctx);

    private:
        std::shared_ptr<ClientContext> context_ = nullptr;

    };

}

#endif //GAMMARAYPC_FILETRANSFER_H
