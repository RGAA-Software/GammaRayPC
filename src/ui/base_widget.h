//
// Created by hy on 3/07/2024.
//

#ifndef GAMMARAYPC_BASE_WIDGET_H
#define GAMMARAYPC_BASE_WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QPainter>
#include <QPixmap>
#include <memory>

namespace tc
{
    class ClientContext;

    class BaseWidget : public QWidget {
    public:
        explicit BaseWidget(const std::shared_ptr<ClientContext>& ctx, QWidget* parent = nullptr);

    protected:
        std::shared_ptr<ClientContext> context_ = nullptr;
    };
}

#endif //GAMMARAYPC_BASE_WIDGET_H
