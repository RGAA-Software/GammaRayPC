//
// Created by RGAA on 2023-08-10.
//

#include "Settings.h"

#include "tc_common/shared_preference.h"

namespace tc
{

    const std::string kKeyInit = "key_init";
    const std::string kKeyFixAtTop = "key_fix_at_top";
    const std::string kKeyDisplayMode = "key_display_mode";
    const std::string kKeyAudioStatus = "key_audio_status";
    const std::string kKeyClipboardStatus = "key_clipboard_status";

    void Settings::SetSharedPreference(const std::shared_ptr<SharedPreference>& sp) {
        sp_ = sp;
    }

    void Settings::LoadSettings() {
        auto init = sp_->Get(kKeyInit);
        if (init.empty()) {
            sp_->Put(kKeyInit, "inited");
            sp_->Put(kKeyFixAtTop, std::to_string(fix_at_top_));
            sp_->Put(kKeyAudioStatus, std::to_string(audio_on_));
            sp_->Put(kKeyClipboardStatus, std::to_string(clipboard_on_));
            sp_->Put(kKeyDisplayMode, std::to_string((int)display_mode_));
        }
        else {
            fix_at_top_ = std::atoi(sp_->Get(kKeyFixAtTop).c_str());
            audio_on_ = std::atoi(sp_->Get(kKeyAudioStatus).c_str());
            clipboard_on_ = std::atoi(sp_->Get(kKeyClipboardStatus).c_str());
            display_mode_ = (MultiDisplayMode)std::atoi(sp_->Get(kKeyDisplayMode).c_str());
        }
    }

    int Settings::GetWSWidth() {
        return ws_width_;
    }

    int Settings::GetWSHeight() {
        return ws_height_;
    }

    VideoRenderType Settings::GetVideoRenderType() {
        return render_type_;
    }

    bool Settings::IsAudioEnabled() {
        return audio_on_;
    }

    bool Settings::IsClipboardEnabled() {
        return clipboard_on_;
    }

    bool Settings::IsFixAtTop() {
        return fix_at_top_;
    }

    MultiDisplayMode Settings::GetMultiDisplayMode() {
        return display_mode_;
    }

    void Settings::SetAudioEnabled(bool enabled) {
        audio_on_ = enabled;
        sp_->Put(kKeyAudioStatus, std::to_string(enabled));
    }

    void Settings::SetClipboardEnabled(bool enabled) {
        clipboard_on_ = enabled;
        sp_->Put(kKeyClipboardStatus, std::to_string(enabled));
    }

    void Settings::SetFixAtTop(bool fix) {
        fix_at_top_ = fix;
        sp_->Put(kKeyFixAtTop, std::to_string(fix));
    }

    void Settings::SetMultiDisplayMode(MultiDisplayMode mode) {
        display_mode_ = mode;
        sp_->Put(kKeyDisplayMode, std::to_string((int)mode));
    }


}