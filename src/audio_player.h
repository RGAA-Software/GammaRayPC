//
// Created by RGAA on 2024/2/28.
//

#ifndef TC_CLIENT_PC_AUDIO_PLAYER_H
#define TC_CLIENT_PC_AUDIO_PLAYER_H

#include <QMainWindow>
#include <QFile>
#include <QDebug>
#include <QIODevice>
#include <QMediaDevices>
#include <QAudioFormat>
#include <QAudioSink>

namespace tc
{

    class Data;

    class AudioPlayer {
    public:
        AudioPlayer();
        ~AudioPlayer();

        void Init(int samples, int channels);
        void Write(const char* data, int size);
        void Write(const std::shared_ptr<Data>& data);

    private:
        bool init = false;
        QIODevice* io = nullptr;

        QMediaDevices* devices_ = nullptr;
        QAudioSink* sink_ = nullptr;
    };
}

#endif //TC_CLIENT_PC_AUDIO_PLAYER_H
