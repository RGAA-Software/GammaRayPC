//
// Created by RGAA on 2023-08-10.
//

#ifndef SAILFISH_CLIENT_PC_SETTINGS_H
#define SAILFISH_CLIENT_PC_SETTINGS_H

#include <memory>
#include <string>

namespace tc
{

    enum class VideoRenderType {
        kSDL,
        kOpenGL,
        kTestQPixmap,
    };

    enum class MultiDisplayMode {
        kSeparated,
        kCombined,
    };

    class SharedPreference;

    class Settings {
    public:

        static Settings* Instance() {
            static Settings sts;
            return &sts;
        }

        void SetSharedPreference(const std::shared_ptr<SharedPreference>& sp);
        void LoadSettings();

        bool IsAudioEnabled() const;
        bool IsClipboardEnabled() const;
        MultiDisplayMode GetMultiDisplayMode();
        VideoRenderType GetVideoRenderType();

        void SetAudioEnabled(bool enabled);
        void SetTempAudioEnabled(bool enabled);
        void SetClipboardEnabled(bool enabled);
        void SetMultiDisplayMode(MultiDisplayMode mode);

    public:
        std::string version_ = "V 1.1.3";
        bool audio_on_ = false;
        bool clipboard_on_ = true;
        MultiDisplayMode display_mode_ = MultiDisplayMode::kSeparated;
        VideoRenderType render_type_ = VideoRenderType::kOpenGL;
        std::shared_ptr<SharedPreference> sp_ = nullptr;
        std::string remote_address_;
        int file_transfer_port_ = 20372;
        std::string file_transfer_path_ = "/file/transfer";
    };

}

#endif //SAILFISH_CLIENT_PC_SETTINGS_H
