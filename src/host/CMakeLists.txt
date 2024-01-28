
project(tc_host VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core OpenGL OpenGLWidgets Multimedia)

set(SRCS
        main.cpp
        application.cpp
        host_main_window.cpp
        host_context.cpp
)

qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${SRCS}
)

if (APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            MACOSX_BUNDLE_GUI_IDENTIFIER com.tc.client.host
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

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()

## Post build
if (WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${QT_ROOT}/bin/windeployqt.exe $<TARGET_FILE:${PROJECT_NAME}> --no-translations
            #        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/settings.toml"  "${CMAKE_BINARY_DIR}"
            #        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/deps/tc_capture/tc_capture_library.dll"  "${CMAKE_BINARY_DIR}"
            #COMMAND ${CMAKE_COMMAND} -E copy_directory "${VLC_ROOT}/plugins"  "${CMAKE_BINARY_DIR}/plugins"
    )
elseif (APPLE)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${QT_ROOT}/bin/macdeployqt ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.app --no-translations
        )
elseif (UNIX)

endif ()