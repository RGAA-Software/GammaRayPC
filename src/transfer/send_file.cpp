//
// Created by RGAA on 10/07/2024.
//

#include "send_file.h"
#include "tc_common_new/file.h"

namespace tc
{

    SendFile::SendFile(const QString& file_path, int read_block_size) {
        this->file_ = File::OpenForReadB(file_path.toStdString());
        this->read_block_size_ = read_block_size;
        if (this->file_->IsOpen()) {
            this->file_size_ = this->file_->Size();
        }
    }

    bool SendFile::Send(SendTask&& task) {
        if (!this->file_->IsOpen()) {
            return false;
        }
        this->file_->ReadAll([=, this](uint64_t offset, DataPtr&& data) {

        });
        return true;
    }

}