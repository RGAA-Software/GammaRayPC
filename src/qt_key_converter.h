#pragma once

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#include <QWidget>
#include <QObject>

#include <QMap>
#include <map>

namespace tc
{
	//VK : https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes

    class QtKeyConverter {
    public:

        QtKeyConverter();

        // deprecated
        // int ToVK(int qt_key);

        static std::map<int, bool> GetSysKeyStatus();

    private:

        QMap<int, int> key_mapping_;

    };

}
