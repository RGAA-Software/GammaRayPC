//
// Created by hy on 12/08/2024.
//

#include "key_state_panel.h"
#include "no_margin_layout.h"

namespace tc
{
    constexpr int kBgNormalColor = 0xEEEEEE;
    constexpr int kBgPressedColor = 0xBB0000;
    constexpr int kFontNormalColor = 0x000000;
    constexpr int kFontPressedColor = 0xFFFFFF;

    KeyItem::KeyItem(const QString& txt, QWidget* parent) {
        txt_ = txt;
        setFixedSize(70, 30);
    }

    void KeyItem::paintEvent(QPaintEvent *event) {
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing| QPainter::TextAntialiasing);
        auto radius = 7;
        painter.setBrush(QBrush(pressed_? kBgPressedColor : kBgNormalColor));
        painter.drawRoundedRect(this->rect(), radius, radius);
        painter.setPen(QPen(pressed_? kFontPressedColor : kFontNormalColor));
        painter.drawText(this->rect(), Qt::AlignCenter, txt_);
    }

    void KeyItem::UpdateText(const QString& txt) {
        txt_ = txt;
    }

    void KeyItem::UpdateState(bool pressed) {
        pressed_ = pressed;
        update();
    }

    // panel
    KeyStatePanel::KeyStatePanel(const std::shared_ptr<ClientContext>& ctx, QWidget* parent) : BaseWidget(ctx, parent) {
        resize(220, 80);
        auto root_layout = new NoMarginVLayout();
        {
            auto layout = new NoMarginHLayout();
            {
                auto item = new KeyItem("ALT");
                alt_item_ = item;
                layout->addWidget(item);
            }
            root_layout->addLayout(layout);
        }
        root_layout->addSpacing(10);
        {

        }
        setLayout(root_layout);
    }
}
