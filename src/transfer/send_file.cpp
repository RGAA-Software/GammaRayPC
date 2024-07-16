//
// Created by RGAA on 10/07/2024.
//

#include "send_file.h"
#include "tc_common_new/file.h"
#include "tc_message.pb.h"

namespace tc
{

    SendFile::SendFile(const QString& file_path, int read_block_size) {
        this->file_ = File::OpenForReadB(file_path.toStdString());
        this->read_block_size_ = read_block_size;
        this->file_path_ = file_path;
        if (this->file_->IsOpen()) {
            this->file_size_ = this->file_->Size();
            this->file_name_ = QString::fromStdString(this->file_->FileName());
        }
    }

    bool SendFile::Send(SendTask&& task) {
        if (!this->file_->IsOpen()) {
            return false;
        }
        this->file_->ReadAll([=, this](uint64_t offset, DataPtr&& data) -> bool {
            auto msg = MakeTransferMessage(offset, std::move(data));
            return task(msg, this->file_size_, offset);
        });
        return true;
    }

    bool SendFile::IsOpen() const {
        return file_ && file_->IsOpen();
    }

    std::string SendFile::MakeTransferMessage(uint64_t offset, std::shared_ptr<Data>&& data) const {
        tc::Message msg;
        msg.set_type(MessageType::kFileTransfer);
        auto fs = msg.mutable_file_transfer();
        fs->set_state(FileTransfer_FileTransferState_kTransferring);
        fs->set_file_type(FileTransfer_FileType_kFile);
        fs->set_relative_path("");
        fs->set_filename(this->file_->FileName());
        fs->set_data(data->AsString());
        fs->set_filesize(this->file_size_);
        fs->set_transferred_size(offset);
        fs->set_file_md5("");
        return msg.SerializeAsString();
    }

}