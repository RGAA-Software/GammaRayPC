project(tc_client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core OpenGL OpenGLWidgets Multimedia)
find_package(SqliteOrm CONFIG REQUIRED)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/client)

link_directories(${VCPKG_ROOT}/installed/x64-windows-static/lib)

set(RES resources/font.qrc resources/main.qrc resources/qss.qrc resources.qrc)
add_compile_options(/bigobj)
set(SRCS
        main.cpp
        client_context.cpp
        logo.rc ${RES}
        ui/switch_button.cpp
        ui/float_button.cpp
        ui/message_dialog.cpp
        ui/round_rect_widget.cpp
        ui/app_menu.cpp
        ui/app_stream_list.cpp
        ui/create_stream_dialog.cpp
        ui/app_color_theme.cpp
        ui/app_content.cpp
        ui/stream_item_widget.cpp
        ui/stream_content.cpp
        ui/settings_content.cpp
        db/stream_db_manager.cpp
        db/stream_item.cpp
        application.cpp
        settings.cpp
)

set(SRCS_WS
        main_ws.cpp
        client_context.cpp
        workspace.cpp
        director.cpp
        video_widget.cpp
        video_widget_event.cpp
        shader_program.cpp
        opengl_image_reader.cpp
        renderer.cpp
        sprite.cpp
        opengl_video_widget.cpp
        qt_key_converter.cpp
        audio_player.cpp
        logo.rc ${RES}
        ui/switch_button.cpp
        ui/float_button.cpp
        ui/message_dialog.cpp
        ui/round_rect_widget.cpp
        ui/app_menu.cpp
        ui/app_color_theme.cpp
        ui/app_content.cpp
        db/stream_db_manager.cpp
        db/stream_item.cpp
        settings.cpp
)


qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION ${SRCS})
qt_add_executable(${PROJECT_NAME}_ws MANUAL_FINALIZATION ${SRCS_WS})
if (APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            MACOSX_BUNDLE_GUI_IDENTIFIER com.tc.client.client
            MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
            MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
            MACOSX_BUNDLE TRUE
            WIN32_EXECUTABLE TRUE
    )
    set_target_properties(${PROJECT_NAME}_ws PROPERTIES
            MACOSX_BUNDLE_GUI_IDENTIFIER com.tc.client.client
            MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
            MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
            MACOSX_BUNDLE TRUE
            WIN32_EXECUTABLE TRUE
    )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets
        Qt6::Core
        Qt6::OpenGL
        Qt6::OpenGLWidgets
        Qt6::Multimedia
)
target_link_libraries(${PROJECT_NAME} PRIVATE tc_common_new tc_message tc_sdk tc_qt_widget)
target_link_libraries(${PROJECT_NAME} PRIVATE sqlite_orm::sqlite_orm)
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE jemalloc)
endif ()

target_link_libraries(${PROJECT_NAME}_ws PRIVATE Qt6::Widgets
        Qt6::Core
        Qt6::OpenGL
        Qt6::OpenGLWidgets
        Qt6::Multimedia
)
target_link_libraries(${PROJECT_NAME}_ws PRIVATE tc_common_new tc_message tc_sdk tc_qt_widget)
target_link_libraries(${PROJECT_NAME}_ws PRIVATE sqlite_orm::sqlite_orm)
if(WIN32)
    target_link_libraries(${PROJECT_NAME}_ws PRIVATE jemalloc)
endif ()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
    qt_finalize_executable(${PROJECT_NAME}_ws)
endif()

if (WIN32)
    add_custom_command(TARGET ${PROJECT_NAME}_ws POST_BUILD
            COMMAND ${QT_ROOT}/bin/windeployqt.exe $<TARGET_FILE:${PROJECT_NAME}_ws> --no-translations --release
            #        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/settings.toml"  "${CMAKE_BINARY_DIR}"
            #        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/deps/tc_capture/tc_capture_library.dll"  "${CMAKE_BINARY_DIR}"
            #COMMAND ${CMAKE_COMMAND} -E copy_directory "${VLC_ROOT}/plugins"  "${CMAKE_BINARY_DIR}/plugins"
    )
elseif (APPLE)
#    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#            COMMAND ${QT_ROOT}/bin/macdeployqt $<TARGET_FILE:${PROJECT_NAME}> --no-translations
#    )
elseif (UNIX)

endif ()