#pragma once

#include <QOpenGLWidget>
#include <QOpenGLWindow>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLVersionFunctionsFactory>
#include <QOpenGLWindow>
#include <QResizeEvent>
#include <mutex>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QVBoxLayout>

#include "tc_client_sdk/gl/raw_image.h"
#include "tc_message.pb.h"
#include "video_widget_event.h"

namespace tc
{

	class Sprite;
	class RawImage;
	class Director;
	class ClientContext;
	class ShaderProgram;
	class Statistics;
    class ThunderSdk;

	class OpenGLVideoWidget : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core, public VideoWidgetEvent {
	public:

		explicit OpenGLVideoWidget(const std::shared_ptr<ClientContext>& ctx, const std::shared_ptr<ThunderSdk>& sdk, int dup_idx, RawImageFormat format, QWidget* parent = nullptr);
		~OpenGLVideoWidget() override;

		void RefreshRGBImage(const std::shared_ptr<RawImage>& image);
		void RefreshRGBBuffer(const char* buf, int width, int height, int channel);
		void RefreshI420Image(const std::shared_ptr<RawImage>& image);
		void RefreshI420Buffer(const char* y, int y_size, const char* u, int u_size, const char* v, int v_size, int width, int height);

        void RefreshCursor(int x, int y, int tex_left, int text_right, int hpx, int hpy, const std::shared_ptr<RawImage>& cursor);

        void Exit();

	protected:
		void resizeEvent(QResizeEvent* event) override;
		void initializeGL() override;
		void paintGL() override;
		void resizeGL(int width, int height) override;

		void mouseMoveEvent(QMouseEvent*) override;
		void mousePressEvent(QMouseEvent*) override;
		void mouseReleaseEvent(QMouseEvent*) override;
		void mouseDoubleClickEvent(QMouseEvent*) override;
		void wheelEvent(QWheelEvent* event) override;
		void keyPressEvent(QKeyEvent* event) override;
		void keyReleaseEvent(QKeyEvent* event) override;

	private:
		void InitRGBATexture();
		void InitI420Texture();

	private:

		std::shared_ptr<ClientContext> context;

		glm::mat4 model;
		std::shared_ptr<ShaderProgram> shader_program = nullptr;
		GLuint			vao{ 0 };
		GLuint			vbo{ 0 };
		GLuint			ibo{ 0 };

		char* y_buffer = nullptr;
		char* uv_buffer = nullptr;
		GLuint			y_texture_id = 0;
		GLuint			uv_texture_id = 0;
		bool		    need_create_texture = true;
		int				tex_width = 0;
		int				tex_height = 0;
		int				tex_channel;
		char* rgb_buffer = nullptr;
		GLuint			rgb_texture_id = 0;

		// I420
		char* u_buffer = nullptr;
		char* v_buffer = nullptr;
		GLuint			u_texture_id = 0;
		GLuint			v_texture_id = 0;

		std::mutex		buf_mtx;

		RawImageFormat  raw_image_format;

		std::shared_ptr<Director> director_ = nullptr;
		std::shared_ptr<Sprite> cursor_ = nullptr;

		int render_fps = 0;
		uint64_t last_update_fps_time = 0;

		Statistics* statistics = nullptr;

        int tex_rect_left_ = 0;
        int tex_rect_right_ = 0;
	};


    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

//    class OpenGLWidgetWrapper : public QWidget {
//    Q_OBJECT
//    public:
//
//        OpenGLWidgetWrapper(const std::shared_ptr<Context>& ctx, const std::shared_ptr<SailfishSDK>& sdk, const StreamItem& item, int dup_idx, RawImageFormat format, QWidget* parent) {
//            this->context_ = ctx;
//            this->item_ = item;
//            QString title = "Sailfish client window [ " + QString::number(dup_idx+1) + " ] [ " + item.stream_name.c_str() + " ]";
//            setWindowTitle(title);
//
//            auto layout = new QVBoxLayout();
//            layout->setSpacing(0);
//            layout->setContentsMargins(0,0,0,0);
//            widget_ = new OpenGLVideoWidget(ctx, sdk, dup_idx, format, this);
//            layout->addWidget(widget_);
//            setLayout(layout);
//
//            setAcceptDrops(true);
//        }
//
//    signals:
//
//        void OnCloseEvent();
//
//    protected:
//
//        void closeEvent(QCloseEvent *event) override;
//        void dragEnterEvent(QDragEnterEvent *event) override;
//        void dragLeaveEvent(QDragLeaveEvent *event) override;
//        void dropEvent(QDropEvent *event) override;
//
//    public:
//
//        OpenGLVideoWidget* widget_ = nullptr;
//        std::shared_ptr<Context> context_ = nullptr;
//
//        StreamItem item_;
//
//    };

}