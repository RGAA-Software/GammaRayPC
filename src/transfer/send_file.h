//
// Created by RGAA on 10/07/2024.
//

#ifndef GAMMARAYPC_SEND_FILE_H
#define GAMMARAYPC_SEND_FILE_H

#include "tc_common_new/file.h"

namespace tc
{
    class File;

    using SendTask = std::function<void(const std::string& proto_msg, uint64_t total_size, uint64_t offset_size)>;
    class SendFile {
    public:
        explicit SendFile(const QString& file_path, int read_block_size);
        bool Send(SendTask && task);

    public:
        std::shared_ptr<File> file_ = nullptr;
        int read_block_size_ = 0;
        uint64_t file_size_ = -1;
    };

}
#endif //GAMMARAYPC_SEND_FILE_H
