//
// Created by RGAA on 2023/8/16.
//

#include "settings_content.h"

#include "switch_button.h"
#include "widget_helper.h"
#include "Settings.h"

namespace tc
{

    SettingsContent::SettingsContent(const std::shared_ptr<ClientContext>& ctx, QWidget* parent) : AppContent(ctx, parent) {
        settings_ = Settings::Instance();

        auto root_layout = new QVBoxLayout();
        root_layout->addSpacing(20);
        {
            auto layout = new QHBoxLayout();
            WidgetHelper::ClearMargin(layout);
            layout->addSpacing(50);

            auto label = new QLabel(this);
            label->setFixedSize(330, 40);
            label->setText(tr("fix the menu at top"));
            label->setStyleSheet("font-size:12pt;");
            layout->addWidget(label);

            auto switch_btn = new SwitchButton(this);
            switch_btn->setFixedSize(55, 25);
            switch_btn->SetClickCallback([this](bool selected) {
                ;
            });
            layout->addSpacing(30);
            layout->addWidget(switch_btn);
            layout->addStretch();

            root_layout->addLayout(layout);
        }
        {
            auto layout = new QHBoxLayout();
            WidgetHelper::ClearMargin(layout);
            layout->addSpacing(50);

            auto label = new QLabel(this);
            label->setFixedSize(330, 40);
            label->setText(tr("audio enabled"));
            label->setStyleSheet("font-size:12pt;");
            layout->addWidget(label);

            auto switch_btn = new SwitchButton(this);
            switch_btn->SetStatus(settings_->IsAudioEnabled());
            switch_btn->setFixedSize(55, 25);
            switch_btn->SetClickCallback([this](bool selected) {
                settings_->SetAudioEnabled(selected);
            });
            layout->addSpacing(30);
            layout->addWidget(switch_btn);
            layout->addStretch();

            root_layout->addLayout(layout);
        }
        {
            auto layout = new QHBoxLayout();
            WidgetHelper::ClearMargin(layout);
            layout->addSpacing(50);

            auto label = new QLabel(this);
            label->setFixedSize(330, 40);
            label->setText(tr("clipboard enabled"));
            label->setStyleSheet("font-size:12pt;");
            layout->addWidget(label);

            auto switch_btn = new SwitchButton(this);
            switch_btn->SetStatus(settings_->IsClipboardEnabled());
            switch_btn->setFixedSize(55, 25);
            switch_btn->SetClickCallback([=](bool selected) {
                settings_->SetClipboardEnabled(selected);
            });
            layout->addSpacing(30);
            layout->addWidget(switch_btn);
            layout->addStretch();

            root_layout->addLayout(layout);
        }
        {
            auto layout = new QHBoxLayout();
            WidgetHelper::ClearMargin(layout);
            layout->addSpacing(50);

            auto label = new QLabel(this);
            label->setFixedSize(330, 40);
            label->setText(tr("multiple monitors display mode"));
            label->setStyleSheet("font-size:12pt;");
            layout->addWidget(label);
            layout->addStretch();
            root_layout->addLayout(layout);
        }

        {
            root_layout->addSpacing(15);
            auto layout = new QHBoxLayout();
            WidgetHelper::ClearMargin(layout);
            layout->addSpacing(50);

#if 0
            // separated
            separated_ = new MultiDisplayModeWidget(MultiDisplayMode::kSeparated, this);
            separated_->SetSelected(settings_->GetMultiDisplayMode() == MultiDisplayMode::kSeparated);
            separated_->setFixedSize(250, 150);
            separated_->SetOnClickCallback([=]() {
                combined_->SetSelected(false);
                settings_->SetMultiDisplayMode(MultiDisplayMode::kSeparated);
            });
            layout->addWidget(separated_);

            layout->addSpacing(20);

            combined_ = new MultiDisplayModeWidget(MultiDisplayMode::kCombined, this);
            combined_->SetSelected(settings_->GetMultiDisplayMode() == MultiDisplayMode::kCombined);
            combined_->setFixedSize(250, 150);
            combined_->SetOnClickCallback([=]() {
                separated_->SetSelected(false);
                settings_->SetMultiDisplayMode(MultiDisplayMode::kCombined);
            });
            layout->addWidget(combined_);
#endif
            layout->addStretch();

            root_layout->addLayout(layout);
        }

        root_layout->addStretch();
        setLayout(root_layout);
    }

    SettingsContent::~SettingsContent() {

    }

    void SettingsContent::OnContentShow() {
        AppContent::OnContentShow();
    }

    void SettingsContent::OnContentHide() {
        AppContent::OnContentHide();
    }

}