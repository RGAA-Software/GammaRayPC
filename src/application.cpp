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
#if 0
        stream_content_->SetOnStartingStreamCallback([=, this](const StreamItem& item){
            StartStreaming(item);
        });

        clear_ws_task_id_ = context_->RegisterMessageTask(MessageTask::Make(kCodeClearWorkspace, [=, this](auto& msg) {
            context_->PostUITask([=]() {
                auto target_msg = std::dynamic_pointer_cast<ClearWorkspace>(msg);
                auto stream_id = target_msg->item_.stream_id;
                LOGI("CLEAR:The stream's id : {}, will be release.", stream_id);
                if (workspaces_.find(target_msg->item_.stream_id) != workspaces_.end()) {
                    LOGI("CLEAR: Find the ws, will release it : {}", stream_id);
                    auto ws = workspaces_[stream_id];
                    if (!ws->CloseWorkspace()) {
                        return;
                    }
                    workspaces_.erase(stream_id);
                    ws.reset();
                    LOGI("CLEAR: Workspace closed, stream id : {}", stream_id);
                }
            });
        }));

        close_ws_task_id_ = context_->RegisterMessageTask(MessageTask::Make(kCodeCloseWorkspace, [=, this](auto& msg) {
            context_->PostUITask([=]() {
                auto target_msg = std::dynamic_pointer_cast<CloseWorkspace>(msg);
                auto stream_id = target_msg->item_.stream_id;
                if (workspaces_.find(target_msg->item_.stream_id) != workspaces_.end()) {
                    LOGI("CLOSE: Find the ws, will release it : {}", stream_id);
                    auto ws = workspaces_[stream_id];
                    workspaces_.erase(stream_id);
                    ws.reset();
                    LOGI("CLOSE: Workspace closed, stream id : {}", stream_id);
                }
            });
        }));
#endif
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

    bool Application::HasWorkspace(const std::string &stream_id) {
        //return workspaces_.find(stream_id) != workspaces_.end();
        return false;
    }

    void Application::StartStreaming(const StreamItem& item) {
//        std::shared_ptr<Workspace> workspace = std::make_shared<Workspace>(context_, nullptr/*item*/);
//        //workspace->Run();
//        workspaces_.insert(std::make_pair(item.stream_id, workspace));
    }

}