#pragma once

#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QResizeEvent>
#include <memory>
#include <map>

namespace tc
{

	class ClientContext;
    class NetMessage;
    class QtKeyConverter;
    class ThunderSdk;

    using OnMouseKeyboardEventCallback = std::function<void(int dup_idx, const std::shared_ptr<NetMessage>& msg)>;

	class VideoWidgetEvent {
	public:
        //描述鼠标状态
		struct MouseEventDesc {
            // to do 当前鼠标事件对应的屏幕索引，目前主要针对游戏，只有主屏，后面要兼容多屏
            int monitor_index = 0;
            // 当前鼠标x值，占窗口宽度的比值
            float x_ratio = 0.0f;
            // 当前鼠标y值，占窗口高度的比值
            float y_ratio = 0.0f;
            // 摁键掩码, 用来表示摁下,抬起了什么按键
            int buttons = 0;
            // 滚轮数据
            int data = 0;
            int dx = 0;
            int dy = 0;
            bool pressed = false;
            bool released = false;
        };
		VideoWidgetEvent(const std::shared_ptr<ClientContext>& ctx, const std::shared_ptr<ThunderSdk>& sdk, int dup_idx);
		virtual ~VideoWidgetEvent();

		int GetMouseKey(QMouseEvent* e);
		void OnWidgetResize(int w, int h);
		
		void OnMouseMoveEvent(QMouseEvent*, int widget_width, int widget_height);
		void OnMousePressEvent(QMouseEvent*, int widget_width, int widget_height);
		void OnMouseReleaseEvent(QMouseEvent*, int widget_width, int widget_height);
		void OnMouseDoubleClickEvent(QMouseEvent*);
		void OnWheelEvent(QWheelEvent* event, int widget_width, int widget_height);
		void OnKeyPressEvent(QKeyEvent* event);
		void OnKeyReleaseEvent(QKeyEvent* event);

        void RegisterMouseKeyboardEventCallback(const OnMouseKeyboardEventCallback& cbk);

        void SetMultipleMonitors(bool multi);

    private:

        void SendCallback(const std::shared_ptr<NetMessage>& msg);

        float CalculateX(int x);

        void SendKeyEvent(QKeyEvent* event, bool down);

        void SendMousewEvent(const MouseEventDesc& mouse_event);
    protected:
		
		std::shared_ptr<ClientContext> context = nullptr;
        std::shared_ptr<QtKeyConverter> key_converter_ = nullptr;

		int width = 0;
		int height = 0;

		// mouse
		int invalid_position = -10002200;
		int last_cursor_x_ = invalid_position;
		int last_cursor_y_ = invalid_position;

        OnMouseKeyboardEventCallback event_cbk_;

        std::shared_ptr<ThunderSdk> sdk_ = nullptr;
        int dup_idx_ = 0;
        int screen_size_ = 0;

        bool is_multi_monitors_ = false;
	};

}