#include "video_widget_event.h"

#include "tc_message.pb.h"
#include "qt_key_converter.h"
#include "tc_common/log.h"
#include "tc_client_sdk/thunder_sdk.h"
#include "client_context.h"

#ifdef WIN32
#include <Windows.h>
#endif

namespace tc
{

	VideoWidgetEvent::VideoWidgetEvent(const std::shared_ptr<ClientContext>& ctx, const std::shared_ptr<ThunderSdk>& sdk, int dup_idx) {
		this->context = ctx;
        this->dup_idx_ = dup_idx;
        this->key_converter_ = std::make_shared<QtKeyConverter>();
        this->sdk_ = sdk;
//        auto config = sdk_->GetStreamConfig();
//        this->screen_size_ = config.screen_size;
	}

	VideoWidgetEvent::~VideoWidgetEvent() {

	}

	void VideoWidgetEvent::OnWidgetResize(int w, int h) {
		this->width = w;
		this->height = h;
	}

	int VideoWidgetEvent::GetMouseKey(QMouseEvent* e) {
//		MouseKey key = MouseKey::kLeft;
//		if (e->button() == Qt::LeftButton) {
//			key = MouseKey::kLeft;
//		}
//		else if (e->button() == Qt::RightButton) {
//			key = MouseKey::kRight;
//		}
//		else if (e->button() == Qt::MiddleButton) {
//			key = MouseKey::kMiddle;
//		}
//		return key;

        return -1;
    }

    float VideoWidgetEvent::CalculateX(int x) {
        // 2 monitors.
        float x_percent = 0.0f;
        if (is_multi_monitors_) {
            x_percent = dup_idx_ * 0.5f + (x * 1.0f / this->width) * 0.5;
        }
        else {
            x_percent = x * 1.0f / this->width;
        }
        LOGI("dup-idx: {}, is multi monitors: {}, x percent: {}", dup_idx_, is_multi_monitors_, x_percent);
        return x_percent;
    }

	void VideoWidgetEvent::OnMouseMoveEvent(QMouseEvent* e) {
//		if (width == 0 || height == 0) {
//			return;
//		}
//		float x = CalculateX(e->x()); // e->x() * 1.0 / width;
//		float y = e->y() * 1.0 / height;
//
//		float dx = 0;
//		float dy = 0;
//
//		if (last_cursor_x != invalid_position && last_cursor_y != invalid_position) {
//			dx = (e->x() - last_cursor_x) * 1.0 / width;
//			dy = (e->y() - last_cursor_y) * 1.0 / height;
//		}
//		last_cursor_x = e->x();
//		last_cursor_y = e->y();
//
//		auto key = (MouseKey)GetMouseKey(e);
//		auto mouse_msg = MessageMaker::MakeMouseInfo(key, false, false, x, y, dx, dy);
//        SendCallback(mouse_msg);
//        //LOGI("move: {} {} ", last_cursor_x, last_cursor_y);
	}

	void VideoWidgetEvent::OnMousePressEvent(QMouseEvent* e) {
//		float x = CalculateX(e->x()); //e->x() * 1.0 / width;
//		float y = e->y() * 1.0 / height;
//		auto key = (MouseKey)GetMouseKey(e);
//		auto mouse_msg = MessageMaker::MakeMouseInfo(key, true, false, x, y, 0, 0);
//        SendCallback(mouse_msg);
//
//        // app message
//        context->SendAppMessage(MousePressedMessage::Make());
	}

	void VideoWidgetEvent::OnMouseReleaseEvent(QMouseEvent* e) {
//		float x = CalculateX(e->x()); //e->x() * 1.0 / width;
//		float y = e->y() * 1.0 / height;
//		auto key = (MouseKey)GetMouseKey(e);
//
//		auto mouse_msg = MessageMaker::MakeMouseInfo(key, false, true, x, y, 0, 0);
//        SendCallback(mouse_msg);
	}

	void VideoWidgetEvent::OnMouseDoubleClickEvent(QMouseEvent*) {

	}

	void VideoWidgetEvent::OnWheelEvent(QWheelEvent* e) {
//		float x = e->position().x() * 1.0 / width;
//		float y = e->position().y() * 1.0 / height;
//
//		int scroll = e->angleDelta().y();
////		std::cout << "scroll : " << scroll << " x : " << x << " y : " << y << std::endl;
//		auto mouse_msg = MessageMaker::MakeWheelScrollMouseInfo(x, y, scroll);
//        SendCallback(mouse_msg);
	}

	void VideoWidgetEvent::OnKeyPressEvent(QKeyEvent* e) {
//        int vk = key_converter_->ToVK(e->key());
//        //LOGI("Key pressed , vk : {}", vk);
//        int num_lock_state;
//        int caps_lock_state;
//#ifdef WIN32
//        num_lock_state = GetKeyState(VK_NUMLOCK);
//        caps_lock_state = GetKeyState(VK_CAPITAL);
//
//        std::map<int, bool> sys_key_status = key_converter_->GetSysKeyStatus();
//
//#endif
//		auto keyboard_msg = MessageMaker::MakeKeyboardInfo(vk, true, 0, caps_lock_state, num_lock_state);
//        SendCallback(keyboard_msg);
	}

	void VideoWidgetEvent::OnKeyReleaseEvent(QKeyEvent* e) {
//		int vk = key_converter_->ToVK(e->key());
//		//LOGI("Key release , vk : {}", vk);
//        int num_lock_state;
//        int caps_lock_state;
//#ifdef WIN32
//        num_lock_state = GetKeyState(VK_NUMLOCK);
//        caps_lock_state = GetKeyState(VK_CAPITAL);
//#endif
//		auto keyboard_msg = MessageMaker::MakeKeyboardInfo(vk, false, 0, caps_lock_state, num_lock_state);
//        SendCallback(keyboard_msg);
	}

    void VideoWidgetEvent::RegisterMouseKeyboardEventCallback(const OnMouseKeyboardEventCallback& cbk) {
        event_cbk_ = cbk;
    }

    void VideoWidgetEvent::SendCallback(const std::shared_ptr<NetMessage>& msg) {
        if (event_cbk_) {
            event_cbk_(dup_idx_, msg);
        }
    }

    void VideoWidgetEvent::SetMultipleMonitors(bool multi) {
        is_multi_monitors_ = multi;
    }
}
