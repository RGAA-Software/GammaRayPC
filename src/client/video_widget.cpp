#include "video_widget.h"

namespace rgaa
{

	VideoWidget::VideoWidget(const std::shared_ptr<ThunderSdk>& sdk, int dup_idx, QWidget* parent) : QWidget(parent) {
        this->sdk_ = sdk;
        this->dup_idx_ = dup_idx;
	}

	VideoWidget::~VideoWidget() {

	}

    int VideoWidget::GetDupIdx() {
        return dup_idx_;
    }

	void VideoWidget::RefreshNV12Image(const std::shared_ptr<RawImage>& image) {
					  
	}				  
					  
	void VideoWidget::RefreshNV12Buffer(const char* y_buf, int y_buf_size, const char* uv_buf, int uv_buf_size, int width, int height) {
					  
	}				  
					  
	void VideoWidget::RefreshRGBImage(const std::shared_ptr<RawImage>& image) {
					  
	}				  
					  
	void VideoWidget::RefreshRGBBuffer(const char* buf, int width, int height, int channel) {
					  
	}				  
					  
	void VideoWidget::RefreshI420Image(const std::shared_ptr<RawImage>& image) {
					  
	}				  
					  
	void VideoWidget::RefreshI420Buffer(const char* y_buf, int y_buf_size, const char* u_buf, int u_buf_size, const char* v_buf, int v_buf_size, int width, int height) {
	
	}

}