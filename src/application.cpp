//
// Created by hy on 2024/3/8.
//

#include "application.h"

#include "app_message.h"
#include <QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QElapsedTimer>
#include <QFile>
#include <QProcess>

#include "ui/app_menu.h"
#include "ui/app_stream_list.h"
#include "tc_common_new/log.h"
#include "tc_common_new/thread.h"
#include "ui/create_stream_dialog.h"
#include "client_context.h"
#include "ui/widget_helper.h"
#include "ui/stream_content.h"
#include "ui/settings_content.h"
#include "ui/about_content.h"

namespace tc
{

    Application::Application(const std::shared_ptr<ClientContext>& ctx, QWidget* parent) {
        context_ = ctx;
        resize(1515, 768);
        setWindowTitle(tr("GammaRay Client"));

        CreateLayout();
        Init();

        LoadStyle("");
    }

    Application::~Application() {

    }

    void Application::CreateLayout() {
        auto root_widget = new RoundRectWidget(0xffffff, 0, this);
        auto root_layout = new QHBoxLayout();
        WidgetHelper::ClearMargin(root_layout);
        int margin = 20;
        root_layout->setContentsMargins(0, margin, margin, margin);

        // 1. app menu
        content_widget_ = new QStackedWidget(this);
        content_widget_->setContentsMargins(0,0,0,0);
        content_widget_->setStyleSheet("border:none;background-color:#ffffff;");

        std::vector<AppItemDesc> menus = {
                {tr("GAMES"), ":/resources/image/ic_stream.svg"},
                {tr("SETTINGS"), ":/resources/image/ic_settings.svg"},
                {tr("ABOUT"), ":/resources/image/windows.svg"}
        };
        app_menu_ = new AppMenu(menus, this);
        app_menu_->SetOnItemClickedCallback([this](const QString& name, int idx) {
            content_widget_->setCurrentIndex(idx);
        });
        root_layout->addWidget(app_menu_);

//        CreateStreamDialog dialog(context_);
//        dialog.exec();

        // 2. stream list

        // streams
        auto stream_content = new StreamContent(context_, this);
        content_widget_->addWidget(stream_content);
        stream_content_ = stream_content;

        // settings
        auto settings_content = new SettingsContent(context_, this);
        content_widget_->addWidget(settings_content);

        // about
        auto about_content = new AboutContent(context_, this);
        content_widget_->addWidget(about_content);

        root_layout->addWidget(content_widget_);
        root_widget->setLayout(root_layout);
        setCentralWidget(root_widget);

        content_widget_->setCurrentIndex(0);
    }

    void Application::Init() {
        msg_listener_ = context_->ObtainMessageListener();
        msg_listener_->Listen<StreamItem>([=, this](const StreamItem& item) {
            StartStreaming(item);
        });
    }

    void Application::LoadStyle(const std::string& name) {
        auto qssFile = ":/qss/lightblue.css";
        QString qss;
        QFile file(qssFile);
        if (file.open(QFile::ReadOnly)) {
            QStringList list;
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line;
                in >> line;
                list << line;
            }

            file.close();
            qss = list.join("\n");
            QString paletteColor = qss.mid(20, 7);
            qApp->setPalette(QPalette(paletteColor));
            qApp->setStyleSheet(qss);
        }
    }

    void Application::StartStreaming(const StreamItem& item) {
        auto process = new QProcess(this);
        QStringList arguments;
        arguments << std::format("--host={}", item.stream_host).c_str()
            << std::format("--port={}", item.stream_port).c_str();
        qDebug() << "args: " << arguments;
        process->start("./tc_client_ws.exe", arguments);
    }

    void Application::changeEvent(QEvent* event) {
        if (event->type() == QEvent::ActivationChange) {
            qDebug() << "window state: " << isActiveWindow();
        }
    }

}