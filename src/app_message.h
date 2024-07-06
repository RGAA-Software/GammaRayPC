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

    };

    class StreamItemAdded : public AppMessage {
    public:
        StreamItem item_;
    };

    class StreamItemUpdated : public AppMessage {
    public:
        StreamItem item_;
    };

    // Close workspace
    class ClearWorkspace : public AppMessage {
    public:
        StreamItem item_;
    };

    // Clipboard
    class ClipboardMessage : public AppMessage {
    public:
        std::string msg_;
    };

    // Mouse pressed
    class MousePressedMessage : public AppMessage {
    public:
        int global_x_;
        int global_y_;
    };

    // Fullscreen
    class FullscreenMessage : public AppMessage {
    public:
    };

    // Exit fullscreen
    class ExitFullscreenMessage : public AppMessage {
    public:
    };

    // Change clipboard status
    class ClipboardStatusMessage : public AppMessage {
    public:
        bool on_ = false;
    };

    // Change audio status
    class AudioStatusMessage : public AppMessage {
    public:
        bool on_ = false;
    };

    class ExitAppMessage : public AppMessage {

    };

}

#endif //SAILFISH_CLIENT_PC_APPMESSAGE_H
