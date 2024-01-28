project(tc_client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core OpenGL OpenGLWidgets Multimedia)

set(SRCS
        main.cpp
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
)

qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION ${SRCS})
if (APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
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
target_link_libraries(${PROJECT_NAME} PRIVATE tc_common tc_message tc_sdk)
target_link_libraries(${PROJECT_NAME} PRIVATE sqlite_orm::sqlite_orm)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE jemalloc)
endif ()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()

if (WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${QT_ROOT}/bin/windeployqt.exe $<TARGET_FILE:${PROJECT_NAME}> --no-translations
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