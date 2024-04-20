//
// Created by RGAA on 2023/8/19.
//

#ifndef SAILFISH_CLIENT_PC_STREAMITEMWIDGET_H
#define SAILFISH_CLIENT_PC_STREAMITEMWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPen>
#include <QBrush>
#include <QPaintEvent>
#include <QPixmap>

namespace tc
{

    class StreamItemWidget : public QWidget {
    public:

        explicit StreamItemWidget(int bg_color, QWidget* parent = nullptr);
        ~StreamItemWidget() override;

        void paintEvent(QPaintEvent *event) override;
        void enterEvent(QEnterEvent *event) override;
        void leaveEvent(QEvent *event) override;

    private:

        int bg_color_ = 0;
        bool enter_ = false;

        QPixmap icon_;
        QPixmap bg_image_;
        QBitmap mask_;
        int radius_;

    };

}

#endif //SAILFISH_CLIENT_PC_STREAMITEMWIDGET_H
