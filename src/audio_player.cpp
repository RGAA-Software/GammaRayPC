//
// Created by RGAA on 2024/2/28.
//

#include "audio_player.h"

#include "audio_player.h"

#include "tc_common_new/data.h"
#include "tc_common_new/log.h"

namespace tc
{
    AudioPlayer::AudioPlayer() {

    }

    AudioPlayer::~AudioPlayer() {
//        io->close();
//        sink_->stop();
//        delete devices_;
//        delete sink_;
    }

    void AudioPlayer::Init(int samples, int channels) {
//        if (init) {
//            return;
//        }
//        devices_ = new QMediaDevices();
//        QAudioDevice outputDevice = QMediaDevices::defaultAudioOutput();
//        QAudioFormat format = outputDevice.preferredFormat();
//        format.setSampleRate(samples);
//        format.setChannelCount(channels);
//        format.setSampleFormat(QAudioFormat::Int16);
//        // ChannelConfigStereo is 2, Int16 is 2
//        LOGI("sampleRate: {}, channelCount: {}, sampleFormat: {}",
//             format.sampleRate(), format.channelCount(), (int)format.sampleFormat()
//        );
//
//        sink_ = new QAudioSink(outputDevice, format);
//        io = sink_->start();
//        init = true;
    }

    void AudioPlayer::Write(const char* data, int size) {
//        this->Write(Data::Make(data, size));
    }

    void AudioPlayer::Write(const std::shared_ptr<Data>& data) {
//        if (io) {
//            io->write(data->CStr(), data->Size());
//        }
    }
}