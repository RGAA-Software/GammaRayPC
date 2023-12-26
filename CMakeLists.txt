cmake_minimum_required(VERSION 3.26)

## env settings
include(env_settings.cmake)

set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
project(tc_client_pc)

## Template
if (WIN32)

elseif (APPLE)

elseif (UNIX)

endif ()
## Template

set(CMAKE_CXX_STANDARD 20)

include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
link_directories(${VCPKG_ROOT}/installed/x64-windows/lib)
include_directories(${VCPKG_ROOT}/installed/x64-windows/include)

##
add_definitions(-DUNICODE -D_UNICODE -DMT)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

## Boost
find_package(Boost REQUIRED COMPONENTS system filesystem thread random)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    MESSAGE(STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
    MESSAGE(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
    MESSAGE(STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")
endif()

find_package(OpenSSL REQUIRED)
find_package(SqliteOrm REQUIRED)

## include directories
include_directories(${CMAKE_SOURCE_DIR}/deps)
include_directories(${CMAKE_SOURCE_DIR}/deps/tc_3rdparty)
include_directories(${CMAKE_SOURCE_DIR}/deps/tc_3rdparty/eventbus/src)
include_directories(${CMAKE_SOURCE_DIR}/deps/tc_client_sdk)

include_directories(${CMAKE_BINARY_DIR}/deps/tc_message)

# 执行的时候就Copy一下，方便测试
#file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/settings.toml" DESTINATION ${CMAKE_BINARY_DIR})

set(SRCS main.cpp)

add_subdirectory(src)
add_subdirectory(deps)

add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} main)
target_link_libraries(${PROJECT_NAME} tc_common tc_message tc_sdk)
target_link_libraries(${PROJECT_NAME} sqlite_orm::sqlite_orm EasyHook64 jemalloc)

## Post build
#add_custom_command(TARGET tc_application POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/settings.toml"  "${CMAKE_BINARY_DIR}"
#        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/deps/tc_capture/tc_capture_library.dll"  "${CMAKE_BINARY_DIR}"
        #COMMAND ${CMAKE_COMMAND} -E copy_directory "${VLC_ROOT}/plugins"  "${CMAKE_BINARY_DIR}/plugins"
#)