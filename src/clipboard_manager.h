//
// Created by RGAA on 16/08/2024.
//

#ifndef GAMMARAYPC_CLIPBOARD_H
#define GAMMARAYPC_CLIPBOARD_H

#include <memory>
#include <QObject>

namespace tc
{

    class ClientContext;

    class ClipboardManager : public QObject {
    public:
        explicit ClipboardManager(const std::shared_ptr<ClientContext>& ctx);
        void Monitor();

    private:
        std::shared_ptr<ClientContext> context_ = nullptr;
    };

}

#endif //GAMMARAYPC_CLIPBOARD_H
