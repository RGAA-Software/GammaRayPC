project(tc_client)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core OpenGL OpenGLWidgets Multimedia)

set(SRCS
        main.cpp
)

add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} Qt6::Widgets
        Qt6::Core
        Qt6::OpenGL
        Qt6::OpenGLWidgets
        Qt6::Multimedia
)
target_link_libraries(${PROJECT_NAME} tc_common tc_message tc_sdk)
target_link_libraries(${PROJECT_NAME} sqlite_orm::sqlite_orm EasyHook64 jemalloc)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${QT_ROOT}/bin/windeployqt.exe $<TARGET_FILE:${PROJECT_NAME}> --no-translations
        #        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/settings.toml"  "${CMAKE_BINARY_DIR}"
        #        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/deps/tc_capture/tc_capture_library.dll"  "${CMAKE_BINARY_DIR}"
        #COMMAND ${CMAKE_COMMAND} -E copy_directory "${VLC_ROOT}/plugins"  "${CMAKE_BINARY_DIR}/plugins"
)