//
// Created by RGAA on 2023-12-26.
//

#ifndef TC_CLIENT_PC_WORKSPACE_H
#define TC_CLIENT_PC_WORKSPACE_H

#include <QWidget>

#include <memory>

namespace tc
{

    class Context;

    class Workspace : public QWidget {
    public:
        Workspace(const std::shared_ptr<Context>& ctx, QWidget* parent = nullptr);
        ~Workspace();


    private:

        std::shared_ptr<Context> context_ = nullptr;

    };

}


#endif //TC_CLIENT_PC_WORKSPACE_H
