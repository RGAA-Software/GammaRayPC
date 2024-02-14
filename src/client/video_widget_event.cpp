#include "video_widget_event.h"

#include "tc_message.pb.h"
#include "qt_key_converter.h"
#include "tc_common/log.h"
#include "tc_common/time_ext.h"
#include "tc_client_sdk/thunder_sdk.h"
#include "client_context.h"

#ifdef WIN32
#include <Windows.h>
#endif
#include <qdebug.h>

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

	void VideoWidgetEvent::OnMouseMoveEvent(QMouseEvent* event, int widget_width, int widget_height) {
        auto curr_pos = event->pos();
        MouseEventDesc mouse_event_desc;
        mouse_event_desc.buttons = 0;
        mouse_event_desc.buttons |= MOUSEEVENTF_MOVE;
        mouse_event_desc.x_ratio = ((float)curr_pos.x()) / ((float)(widget_width));
        mouse_event_desc.y_ratio = ((float)curr_pos.y()) / ((float)(widget_height));
        //qDebug() << "curr_pos = " << curr_pos << " width = " << widget_width << " height = " << widget_height ;

        last_cursor_x_ = curr_pos.x();
        last_cursor_y_ = curr_pos.y();

        SendMousewEvent(mouse_event_desc);
	}

	void VideoWidgetEvent::OnMousePressEvent(QMouseEvent* event, int widget_width, int widget_height) {
        // to do MOUSEEVENTF_LEFTDOWN 等标志 是 win32里面的，如果是其他平台，这里要改下
        auto curr_pos = event->pos();
        //qDebug() << "curr_pos = " << curr_pos << " width = " << widget_width << " height = " << widget_height ;
        MouseEventDesc mouse_event_desc;
        mouse_event_desc.buttons = 0;
        if(event->button() == Qt::LeftButton) {
            std::cout << "OnMousePressEvent LeftButton" << std::endl;
            mouse_event_desc.buttons |= MOUSEEVENTF_LEFTDOWN;
        } else if(event->button() == Qt::RightButton) {
            std::cout << "OnMousePressEvent RightButton" << std::endl;
            mouse_event_desc.buttons |= MOUSEEVENTF_RIGHTDOWN;
        } else if(event->button() == Qt::MiddleButton) {
            std::cout << "OnMousePressEvent MiddleButton" << std::endl;
            mouse_event_desc.buttons |= MOUSEEVENTF_MIDDLEDOWN;
        }
        mouse_event_desc.x_ratio = ((float)curr_pos.x()) / ((float)(widget_width));
        mouse_event_desc.y_ratio = ((float)curr_pos.y()) / ((float)(widget_height));
        SendMousewEvent(mouse_event_desc);
	}

	void VideoWidgetEvent::OnMouseReleaseEvent(QMouseEvent* event, int widget_width, int widget_height) {
        auto curr_pos = event->pos();
        //qDebug() << "curr_pos = " << curr_pos << " width = " << widget_width << " height = " << widget_height ;
        MouseEventDesc mouse_event_desc;
        mouse_event_desc.buttons = 0;
        if (event->button() == Qt::LeftButton) {
            std::cout << "OnMouseReleaseEvent LeftButton" << std::endl;
            mouse_event_desc.buttons |= MOUSEEVENTF_LEFTUP;
        } else if (event->button() == Qt::RightButton) {
            std::cout << "OnMouseReleaseEvent RightButton" << std::endl;
            mouse_event_desc.buttons |= MOUSEEVENTF_RIGHTUP;
        } else if (event->button() == Qt::MiddleButton) {
            std::cout << "OnMouseReleaseEvent MiddleButton" << std::endl;
            mouse_event_desc.buttons |= MOUSEEVENTF_MIDDLEUP;
        }
        mouse_event_desc.x_ratio = ((float)curr_pos.x()) / ((float)(widget_width));
        mouse_event_desc.y_ratio = ((float)curr_pos.y()) / ((float)(widget_height));
        SendMousewEvent(mouse_event_desc);
	}

	void VideoWidgetEvent::OnMouseDoubleClickEvent(QMouseEvent*) {
        std::cout << " OnMouseDoubleClickEvent " << std::endl;
	}

	void VideoWidgetEvent::OnWheelEvent(QWheelEvent* event, int widget_width, int widget_height) {
        MouseEventDesc mouse_event_desc;
        mouse_event_desc.buttons = 0;
        mouse_event_desc.x_ratio = ((float)last_cursor_x_) / ((float)(widget_width));
        mouse_event_desc.y_ratio = ((float)last_cursor_y_) / ((float)(widget_height));
        std::cout << " OnWheelEvent " << std::endl;
        qDebug() << "event->angleDelta() = " << event->angleDelta();
        QPoint angle_delta = event->angleDelta();
        QPoint numDegrees = event->angleDelta() / 8;
        qDebug() << "numDegrees = " << numDegrees;
        if (!numDegrees.isNull()) {
            QPoint numSteps = numDegrees / 15;
            qDebug() << "numSteps = " << numSteps;
            if(angle_delta.x() != 0) {
                mouse_event_desc.buttons |= MOUSEEVENTF_HWHEEL;
                mouse_event_desc.data = angle_delta.x();
                std::cout << "MOUSEEVENTF_WHEEL data = " << mouse_event_desc.data << std::endl;
            }
            if(angle_delta.y() != 0) {
                mouse_event_desc.buttons |= MOUSEEVENTF_WHEEL;
                mouse_event_desc.data = angle_delta.y();
            }
            SendMousewEvent(mouse_event_desc);
        }
        // event->angleDelta() =  QPoint(0,120)
        // numDegrees =  QPoint(0,15)
        // numSteps =  QPoint(0,1)
	}

	void VideoWidgetEvent::OnKeyPressEvent(QKeyEvent* e) {
#ifdef WIN32
        SendKeyEvent(e, true);
#endif
	}

	void VideoWidgetEvent::OnKeyReleaseEvent(QKeyEvent* e) {
#ifdef WIN32
        SendKeyEvent(e, false);
#endif
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

    void VideoWidgetEvent::SendKeyEvent(QKeyEvent* e, bool down) {
        int vk = key_converter_->ToVK(e->key());
        //LOGI("Key pressed , vk : {}", vk);
        std::cout << "vk = " << vk << std::endl;
        short num_lock_state = -1;
        if (vk >= VK_NUMPAD0 && vk <= VK_DIVIDE || vk == VK_NUMLOCK   // 17个键
            || vk == VK_HOME || vk == VK_END		// HOME(7) END(1)
            || vk == VK_PRIOR || vk == VK_NEXT	// PAGE_UP(9) PAGE_DOWN(3)
            || vk == VK_UP || vk == VK_DOWN || vk == VK_LEFT || vk == VK_RIGHT // UP(8) DOWN(2) LEFT(4) RIGHT(6)
            || vk == VK_INSERT || vk == VK_DELETE // INSERT(0) DELETE(.)
                ) {
            num_lock_state = GetKeyState(VK_NUMLOCK);
        }

        short caps_lock_state = -1;
        if (vk >= 0x41 && vk <= 0x5A) {
            caps_lock_state = GetKeyState(VK_CAPITAL);
            std::cout << "caps_lock_state = " << caps_lock_state << std::endl;
        }

        std::map<int, bool> sys_key_status = key_converter_->GetSysKeyStatus();
        auto msg = std::make_shared<Message>();
        msg->set_type(tc::kKeyEvent);
        auto key_event = new tc::KeyEvent();
        key_event->set_down(down);
        key_event->set_key_code(vk);
        key_event->set_num_lock_status(num_lock_state);
        key_event->set_caps_lock_status(caps_lock_state);
        if (num_lock_state != -1) {
            key_event->set_status_check(tc::KeyEvent::kCheckNumLock);
        }
        else if (caps_lock_state != -1) {
            key_event->set_status_check(tc::KeyEvent::kCheckCapsLock);
        }
        else {
            key_event->set_status_check(tc::KeyEvent::kDontCareLockKey);
        }
        auto cur_time = GetCurrentTime();
        key_event->set_timestamp(cur_time);
        msg->set_allocated_key_event(key_event);

        // to do 要判斷當前客戶端是否是主控
        if(this->sdk_) {
            this->sdk_->PostBinaryMessage(msg->SerializeAsString());
        }
    }

    void VideoWidgetEvent::SendMousewEvent(const MouseEventDesc& mouse_event_desc) {
        auto msg = std::make_shared<Message>();
        msg->set_type(tc::kMouseEvent);
        auto mouse_event = new tc::MouseEvent();
        mouse_event->set_x_ratio(mouse_event_desc.x_ratio);
        mouse_event->set_y_ratio(mouse_event_desc.y_ratio);
        mouse_event->set_button(mouse_event_desc.buttons);
        auto cur_time = GetCurrentTime();
        mouse_event->set_timestamp(cur_time);
        // to do 屏幕索引暂定为 0, 等后面兼容多屏模式
        mouse_event->set_monitor_index(0);
        mouse_event->set_data(mouse_event_desc.data);
        msg->set_allocated_mouse_event(mouse_event);
        // to do 要判斷當前客戶端是否是主控
        if(this->sdk_) {
            this->sdk_->PostBinaryMessage(msg->SerializeAsString());
        }
    }
}
