//
// Created by RGAA on 2023-12-27.
//

#ifndef TC_CLIENT_PC_WORKSPACE_H
#define TC_CLIENT_PC_WORKSPACE_H

#include <QWidget>

namespace tc
{

    class ClientContext;

    class Workspace : public QWidget {
    public:

        explicit Workspace(const std::shared_ptr<ClientContext>& ctx, QWidget* parent = nullptr);
        ~Workspace() override;

    private:

        std::shared_ptr<ClientContext> context_ = nullptr;

    };

}

#endif //TC_CLIENT_PC_WORKSPACE_H
