//
// Created by RGAA on 2023-12-26.
//

#ifndef TC_CLIENT_PC_HOST_MAIN_WINDOW_H
#define TC_CLIENT_PC_HOST_MAIN_WINDOW_H

#include <QWidget>

#include <memory>

namespace tc
{

    class HostContext;

    class HostMainWindow : public QWidget {
    public:
        HostMainWindow(const std::shared_ptr<HostContext>& ctx, QWidget* parent = nullptr);
        ~HostMainWindow();


    private:

        std::shared_ptr<HostContext> context_ = nullptr;

    };

}


#endif //TC_CLIENT_PC_HOST_MAIN_WINDOW_H
