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

#include "tc_client_sdk_new/gl/raw_image.h"
#include "tc_message.pb.h"
#include "video_widget_event.h"
#include "sdk_messages.h"

namespace tc
{
    class Data;
    class Sprite;
    class RawImage;
    class Director;
    class ClientContext;
    class ShaderProgram;
    class Statistics;
    class ThunderSdk;

    class OpenGLVideoWidget : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core, public VideoWidgetEvent {
    public:

        explicit OpenGLVideoWidget(const std::shared_ptr<ClientContext> &ctx, const std::shared_ptr<ThunderSdk> &sdk,
                                   int dup_idx, RawImageFormat format, QWidget *parent = nullptr);
        ~OpenGLVideoWidget() override;
        void RefreshRGBImage(const std::shared_ptr<RawImage> &image);
        void RefreshRGBBuffer(const char *buf, int width, int height, int channel);
        void RefreshI420Image(const std::shared_ptr<RawImage> &image);
        void RefreshI420Buffer(const char *y, int y_size, const char *u, int u_size, const char *v, int v_size, int width, int height);
        void RefreshCursor(int x, int y, int tex_left, int text_right, int hpx, int hpy, const std::shared_ptr<RawImage> &cursor);
        void RefreshCapturedMonitorInfo(const CaptureMonitorInfo &mon_info);
        void Exit();

        int GetCapturingMonitorWidth();
        int GetCapturingMonitorHeight();

    protected:
        void resizeEvent(QResizeEvent *event) override;
        void initializeGL() override;
        void paintGL() override;
        void resizeGL(int width, int height) override;
        void mouseMoveEvent(QMouseEvent *) override;
        void mousePressEvent(QMouseEvent *) override;
        void mouseReleaseEvent(QMouseEvent *) override;
        void mouseDoubleClickEvent(QMouseEvent *) override;
        void wheelEvent(QWheelEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;
        void keyReleaseEvent(QKeyEvent *event) override;

    private:
        void InitRGBATexture();
        void InitI420Texture();

    private:
        std::shared_ptr<ClientContext> context;
        glm::mat4 model;
        std::shared_ptr<ShaderProgram> shader_program = nullptr;
        GLuint vao{0};
        GLuint vbo{0};
        GLuint ibo{0};

        std::shared_ptr<Data> y_buffer = nullptr;
        char *uv_buffer = nullptr;
        GLuint y_texture_id = 0;
        GLuint uv_texture_id = 0;
        bool need_create_texture = true;
        int tex_width = 0;
        int tex_height = 0;
        int tex_channel;
        char *rgb_buffer = nullptr;
        GLuint rgb_texture_id = 0;

        // I420
        std::shared_ptr<Data> u_buffer = nullptr;
        std::shared_ptr<Data> v_buffer = nullptr;
        GLuint u_texture_id = 0;
        GLuint v_texture_id = 0;

        std::mutex buf_mtx;
        RawImageFormat raw_image_format;

        std::shared_ptr<Director> director_ = nullptr;
        std::shared_ptr<Sprite> cursor_ = nullptr;

        int render_fps = 0;
        uint64_t last_update_fps_time = 0;

        Statistics *statistics = nullptr;

        int tex_rect_left_ = 0;
        int tex_rect_right_ = 0;

        CaptureMonitorInfo cap_mon_info_{};
    };
}