//
// Created by hy on 17/08/2024.
//

#include "computer_icon.h"

namespace tc
{

    ComputerIcon::ComputerIcon(const std::shared_ptr<ClientContext>& ctx, int idx, QWidget* parent) : BaseWidget(ctx, parent) {
        QImage image;
        image.load(":resources/image/ic_computer.svg");
        pixmap_ = QPixmap::fromImage(image);
        index_ = idx;
    }

    void ComputerIcon::paintEvent(QPaintEvent *event) {
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
        painter.drawPixmap(this->rect(), pixmap_);
        QFont font = painter.font();
        font.setPointSize(9);
        painter.setFont(font);
        painter.drawText(QRect(rect().x(), rect().y() - 1, rect().width(), rect().height()), Qt::AlignCenter, std::to_string(index_).c_str());
    }

}