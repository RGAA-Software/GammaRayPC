//
// Created by RGAA on 2023-08-17.
//

#ifndef SAILFISH_CLIENT_PC_APPMESSAGE_H
#define SAILFISH_CLIENT_PC_APPMESSAGE_H

#include <utility>
#include <memory>

#include "db/stream_item.h"

namespace tc
{

    constexpr int kCodeTimeout1S = 0x1001;
    constexpr int kCodeStreamAdded = 0x1002;
    constexpr int kCodeCloseWorkspace = 0x1003;
    constexpr int kCodeClearWorkspace = 0x1004;
    constexpr int kCodeClipboard = 0x1005;
    constexpr int kCodeStreamUpdated = 0x1006;
    constexpr int kCodeMousePressed = 0x1007;
    constexpr int kCodeFullscreen = 0x1008;
    constexpr int kCodeExitFullscreen = 0x1009;
    constexpr int kCodeClipboardStatus = 0x1010;
    constexpr int kCodeAudioStatus = 0x1011;

    /////
    constexpr int kCodeExit = -1;

    class AppMessage {
    public:

        explicit AppMessage(int c) : code(c) {

        }
        virtual ~AppMessage() {}

        int code {0};


    };

    class ExitMessage : public AppMessage {
    public:

        explicit ExitMessage(int c) : AppMessage(c) {}

        static std::shared_ptr<ExitMessage> Make() {
            return std::make_shared<ExitMessage>(kCodeExit);
        }

    };
    ////

    class Timeout1S : public AppMessage {
    public:
        static std::shared_ptr<Timeout1S> Make() {
            return std::make_shared<Timeout1S>(kCodeTimeout1S);
        }
        explicit Timeout1S(int c) : AppMessage(c) {}
    };

    // Stream item will be added in to database
    class StreamItemAdded : public AppMessage {
    public:
        static std::shared_ptr<StreamItemAdded> Make(const StreamItem& item) {
            return std::make_shared<StreamItemAdded>(item);
        }

        explicit StreamItemAdded(const StreamItem& item) : AppMessage(kCodeStreamAdded) {
            this->item_ = item;
        }

    public:

        StreamItem item_;
    };

    // Stream will be updated
    class StreamItemUpdated : public AppMessage {
    public:
        static std::shared_ptr<StreamItemUpdated> Make(const StreamItem& item) {
            return std::make_shared<StreamItemUpdated>(item);
        }

        explicit StreamItemUpdated(const StreamItem& item) : AppMessage(kCodeStreamUpdated) {
            this->item_ = item;
        }

    public:

        StreamItem item_;
    };

    // Close workspace, close -> clear, with dialog
    class CloseWorkspace : public AppMessage {
    public:
        static std::shared_ptr<CloseWorkspace> Make(const StreamItem& item) {
            return std::make_shared<CloseWorkspace>(item);
        }
        explicit CloseWorkspace(const StreamItem& item) : AppMessage(kCodeCloseWorkspace) {
            this->item_ = item;
        }

    public:
        StreamItem item_;
    };

    // Close workspace
    class ClearWorkspace : public AppMessage {
    public:
        static std::shared_ptr<ClearWorkspace> Make(const StreamItem& item) {
            return std::make_shared<ClearWorkspace>(item);
        }
        explicit ClearWorkspace(const StreamItem& item) : AppMessage(kCodeClearWorkspace) {
            this->item_ = item;
        }

    public:
        StreamItem item_;
    };

    // Clipboard
    class ClipboardMessage : public AppMessage {
    public:
        static std::shared_ptr<ClipboardMessage> Make(const std::string& msg) {
            return std::make_shared<ClipboardMessage>(msg);
        }

        explicit ClipboardMessage(std::string  msg) : AppMessage(kCodeClipboard), msg_(std::move(msg)) {}

    public:
        std::string msg_;
    };

    // Mouse pressed
    class MousePressedMessage : public AppMessage {
    public:
        static std::shared_ptr<MousePressedMessage> Make() {
            return std::make_shared<MousePressedMessage>();
        }

        explicit MousePressedMessage() : AppMessage(kCodeMousePressed) {}
    };

    // Fullscreen
    class FullscreenMessage : public AppMessage {
    public:
        static std::shared_ptr<FullscreenMessage> Make() {
            return std::make_shared<FullscreenMessage>();
        }

        explicit FullscreenMessage() : AppMessage(kCodeFullscreen) {}
    };

    // Exit fullscreen
    class ExitFullscreenMessage : public AppMessage {
    public:
        static std::shared_ptr<ExitFullscreenMessage> Make() {
            return std::make_shared<ExitFullscreenMessage>();
        }

        explicit ExitFullscreenMessage() : AppMessage(kCodeExitFullscreen) {}
    };

    // Change clipboard status
    class ClipboardStatusMessage : public AppMessage {
    public:

        static std::shared_ptr<ClipboardStatusMessage> Make(bool on) {
            return std::make_shared<ClipboardStatusMessage>(on);
        }

        explicit ClipboardStatusMessage(bool on) : AppMessage (kCodeClipboardStatus) {
            this->on = on;
        };

        bool on = false;
    };

    // Change audio status
    class AudioStatusMessage : public AppMessage {
    public:

        static std::shared_ptr<AudioStatusMessage> Make(bool on) {
            return std::make_shared<AudioStatusMessage>(on);
        }

        explicit AudioStatusMessage(bool on) : AppMessage(kCodeAudioStatus) {
            this->on = on;
        }

        bool on = false;
    };

}

#endif //SAILFISH_CLIENT_PC_APPMESSAGE_H
