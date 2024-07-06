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

        int GetWSWidth();
        int GetWSHeight();

        bool IsAudioEnabled();
        bool IsClipboardEnabled();
        bool IsFixAtTop();
        MultiDisplayMode GetMultiDisplayMode();
        VideoRenderType GetVideoRenderType();

        void SetAudioEnabled(bool enabled);
        void SetClipboardEnabled(bool enabled);
        void SetFixAtTop(bool fix);
        void SetMultiDisplayMode(MultiDisplayMode mode);

    private:
        int ws_width_ = 1280;
        int ws_height_ = 768;
        bool audio_on_ = false;
        bool clipboard_on_ = true;
        bool fix_at_top_ = true;
        MultiDisplayMode display_mode_ = MultiDisplayMode::kSeparated;
        VideoRenderType render_type_ = VideoRenderType::kOpenGL;
        std::shared_ptr<SharedPreference> sp_ = nullptr;

    };

}

#endif //SAILFISH_CLIENT_PC_SETTINGS_H
