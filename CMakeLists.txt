cmake_minimum_required(VERSION 3.26)

## env settings
include(env_settings.cmake)

set(CMAKE_PREFIX_PATH ${QT_ROOT}/lib/cmake)
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
project(GammaRayPC)

set(CMAKE_CXX_STANDARD 20)

include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)

if (WIN32)
    link_directories(${VCPKG_ROOT}/installed/x64-windows/lib)
    include_directories(${VCPKG_ROOT}/installed/x64-windows/include)
elseif (APPLE)
    link_directories(${VCPKG_ROOT}/installed/x64-osx/lib)
    include_directories(${VCPKG_ROOT}/installed/x64-osx/include)
elseif (UNIX)

endif ()

if(MSVC)
    add_compile_options($<IF:$<CONFIG:Debug>,/MTd,/MT>)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem thread)
if(Boost_FOUND)
    MESSAGE(STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
    MESSAGE(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
    MESSAGE(STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")
endif()

## include directories
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/deps)
include_directories(${CMAKE_SOURCE_DIR}/deps/tc_3rdparty)
include_directories(${CMAKE_SOURCE_DIR}/deps/tc_3rdparty/eventbus/src)
include_directories(${CMAKE_SOURCE_DIR}/deps/tc_client_sdk_new)
include_directories(${CMAKE_SOURCE_DIR}/deps/tc_3rdparty/asio2/include)
include_directories(${CMAKE_SOURCE_DIR}/deps/tc_3rdparty/asio2/3rd)
include_directories(${CMAKE_SOURCE_DIR}/deps/tc_qt_widget)
include_directories(${CMAKE_BINARY_DIR}/deps/tc_message_new)
if (WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/deps/tc_3rdparty/ffmpeg/include)
    link_directories(${CMAKE_SOURCE_DIR}/deps/tc_3rdparty/ffmpeg/lib/x64)
    include_directories(${CMAKE_SOURCE_DIR}/deps/tc_3rdparty/webrtc/include)
    link_directories(${CMAKE_SOURCE_DIR}/deps/tc_3rdparty/webrtc/x64)
    include_directories(${CMAKE_SOURCE_DIR}/deps/tc_3rdparty/openssl/include)
    link_directories(${CMAKE_SOURCE_DIR}/deps/tc_3rdparty/openssl/x64/lib/VC)
endif ()
# 执行的时候就Copy一下，方便测试
#file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/settings.toml" DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(src)
add_subdirectory(deps)

add_custom_target(tc_build_all COMMENT "Build all targets")
add_dependencies(tc_build_all GammaRayClient tc_rtc GammaRayClientInner)
#add_custom_command(TARGET tc_build_all POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#            "${CMAKE_CURRENT_BINARY_DIR}/deps/tc_webrtc_client/tc_rtc.dll"
#            "${CMAKE_CURRENT_BINARY_DIR}/src/"
#)