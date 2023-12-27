//
// Created by RGAA on 2023-12-27.
//

#ifndef TC_CLIENT_PC_CLIENT_CONTEXT_H
#define TC_CLIENT_PC_CLIENT_CONTEXT_H

#include <functional>

#include <QObject>
#include <QWidget>

namespace tc
{

    class ClientContext : public QObject {
    public:

        ClientContext(QObject* parent = nullptr);
        ~ClientContext();

        void PostTask(std::function<void()>&& task);
        void PostUITask(std::function<void()>&& task);
    };

}

#endif //TC_CLIENT_PC_CLIENT_CONTEXT_H
