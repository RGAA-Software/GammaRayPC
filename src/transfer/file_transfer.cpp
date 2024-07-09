//
// Created by RGAA on 6/07/2024.
//

#include "file_transfer.h"
#include "file_transfer_channel.h"
#include "settings.h"

namespace tc
{

    FileTransfer::FileTransfer(const std::shared_ptr<ClientContext>& ctx) {
        context_ = ctx;
        settings_ = Settings::Instance();
        channel_ = std::make_shared<FileTransferChannel>(ctx);
    }

    void FileTransfer::Start() {
        channel_->Start("10.0.0.16", 8080, "/path");
    }

    void FileTransfer::Exit() {
        channel_->Exit();
    }

}
