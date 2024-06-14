//
// Created by RGAA on 2023-12-26.
//

#include <QApplication>
#include <QSurfaceFormat>
#include <QFontDatabase>
#include <QMessageBox>

#include "thunder_sdk.h"
#include "client_context.h"
#include "workspace.h"
#include "application.h"
#include "gflags/gflags.h"
#include "tc_common_new/md5.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace tc;

DEFINE_string(host, "", "remote host");
DEFINE_int32(port, 0, "remote port");

int main(int argc, char** argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
#ifdef WIN32
    //CaptureDump();
#endif

#ifdef __APPLE__
    QSurfaceFormat fmt;
    fmt.setProfile(QSurfaceFormat::CoreProfile);
    fmt.setVersion(3, 3);
    fmt.setSwapInterval(1);
    QSurfaceFormat::setDefaultFormat(fmt);
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
#endif

    QApplication app(argc, argv);

    // font
#if 0
    auto id = QFontDatabase::addApplicationFont(":/resources/font/quixotic-1.otf");
    qDebug() << "font family : " << QFontDatabase::applicationFontFamilies(id) ;

    QFont font;
    font.setPointSize(10);
    qApp->setFont(font);
#endif

    auto host = FLAGS_host;
    auto port = FLAGS_port;
    if (host.empty() || port <= 0 || port >= 65535) {
        QMessageBox::critical(nullptr, "Error Params", "You must give HOST & PORT");
        return -1;
    }

    auto name = MD5::Hex(host).substr(0, 10);
    auto ctx = std::make_shared<ClientContext>(name);
    static Workspace ws(ctx, ThunderSdkParams {
            .ssl_ = false,
            .enable_audio_ = true,
            .enable_video_ = true,
            .enable_controller_ = false,
            .ip_ = host,
            .port_ = port,
            .req_path_ = "/media",
#if defined(WIN32)
            .client_type_ = ClientType::kWindows,
#elif defined(ANDROID)
            .client_type_ = ClientType::kAndroid,
#endif
    });
    ws.setWindowTitle(QMainWindow::tr("GammaRay Game Streamer"));
    ws.resize(1280, 768);
    ws.show();

    HHOOK keyboardHook = SetWindowsHookExA(WH_KEYBOARD_LL, [](int code, WPARAM wParam, LPARAM lParam) -> LRESULT {
        if (code >= 0 && ws.IsActiveNow()) {
            if (wParam == WM_KEYDOWN || wParam == WM_KEYUP) {
                // 检查按下的键是否是需要屏蔽的键
                auto kbdStruct = (KBDLLHOOKSTRUCT *)lParam;
                if (kbdStruct->vkCode == VK_LWIN || kbdStruct->vkCode == VK_RWIN) {
                    return 1;  // 不传递按键消息
                }
            }
        }
        return CallNextHookEx(nullptr, code, wParam, lParam);
    }, nullptr, 0);

    auto r = app.exec();
    UnhookWindowsHookEx(keyboardHook);
    return r;
}