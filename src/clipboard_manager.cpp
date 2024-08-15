//
// Created by RGAA on 16/08/2024.
//

#include "clipboard_manager.h"
#include "client_context.h"
#include <QGuiApplication>
#include <QClipboard>
#include "tc_common_new/log.h"

namespace tc
{

    ClipboardManager::ClipboardManager(const std::shared_ptr<ClientContext> &ctx) : QObject(nullptr) {
        context_ = ctx;
    }

    void ClipboardManager::Monitor() {
        QClipboard *board = QGuiApplication::clipboard();
        connect(board, &QClipboard::dataChanged, this, [=]() {
            static bool finished = true;
            if (board->text() == "" || !finished) {
                return;
            }
            QString text = board->text();
            LOGI("===> new Text: {}", text.toStdString());

            finished = false;
            board->setText(text);
            finished = true;
        });
    }

}
