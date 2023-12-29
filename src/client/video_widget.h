#pragma once

#include <QWidget>
#include <QMouseEvent>
#include "tc_message.pb.h"
#include <memory>
#include <atomic>

namespace rgaa
{

	class RawImage;
    class ThunderSdk;

	class VideoWidget : public QWidget {
	public:
		
		VideoWidget(const std::shared_ptr<ThunderSdk>& sdk, int dup_idx, QWidget* parent = nullptr);
		~VideoWidget() override;

        virtual void Exit() {
            exit_ = true;
        }

        int GetDupIdx();

	protected:

		virtual void RefreshNV12Image(const std::shared_ptr<RawImage>& image);
		virtual void RefreshNV12Buffer(const char* y_buf, int y_buf_size, const char* uv_buf, int uv_buf_size, int width, int height);
		virtual void RefreshRGBImage(const std::shared_ptr<RawImage>& image);
		virtual void RefreshRGBBuffer(const char* buf, int width, int height, int channel);
		virtual void RefreshI420Image(const std::shared_ptr<RawImage>& image);
		virtual void RefreshI420Buffer(const char* y_buf, int y_buf_size, const char* u_buf, int u_buf_size, const char* v_buf, int v_buf_size, int width, int height);

    protected:

        std::atomic_bool exit_ = false;

        int dup_idx_ = -1;

        std::shared_ptr<ThunderSdk> sdk_ = nullptr;

	};

}