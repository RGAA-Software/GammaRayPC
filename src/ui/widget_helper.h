//
// Created by RGAA on 2024/3/8.
//

#ifndef TC_CLIENT_PC_WIDGET_HELPER_H
#define TC_CLIENT_PC_WIDGET_HELPER_H

#include <QLayout>

namespace tc
{

    class WidgetHelper {
    public:

        static void ClearMargin(QLayout* layout) {
            layout->setSpacing(0);
            layout->setContentsMargins(0,0,0,0);
        }

    };

}

#endif //TC_CLIENT_PC_WIDGET_HELPER_H
