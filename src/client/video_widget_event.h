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
		
		VideoWidgetEvent(const std::shared_ptr<ClientContext>& ctx, const std::shared_ptr<ThunderSdk>& sdk, int dup_idx);
		virtual ~VideoWidgetEvent();

		int GetMouseKey(QMouseEvent* e);
		void OnWidgetResize(int w, int h);
		
		void OnMouseMoveEvent(QMouseEvent*);
		void OnMousePressEvent(QMouseEvent*);
		void OnMouseReleaseEvent(QMouseEvent*);
		void OnMouseDoubleClickEvent(QMouseEvent*);
		void OnWheelEvent(QWheelEvent* event);
		void OnKeyPressEvent(QKeyEvent* event);
		void OnKeyReleaseEvent(QKeyEvent* event);

        void RegisterMouseKeyboardEventCallback(const OnMouseKeyboardEventCallback& cbk);

        void SetMultipleMonitors(bool multi);

    private:

        void SendCallback(const std::shared_ptr<NetMessage>& msg);

        float CalculateX(int x);

    protected:
		
		std::shared_ptr<ClientContext> context = nullptr;
        std::shared_ptr<QtKeyConverter> key_converter_ = nullptr;

		int width = 0;
		int height = 0;

		// mouse
		int invalid_position = -10002200;
		int last_cursor_x = invalid_position;
		int last_cursor_y = invalid_position;

        OnMouseKeyboardEventCallback event_cbk_;

        std::shared_ptr<ThunderSdk> sdk_ = nullptr;
        int dup_idx_ = 0;
        int screen_size_ = 0;

        bool is_multi_monitors_ = false;
	};

}