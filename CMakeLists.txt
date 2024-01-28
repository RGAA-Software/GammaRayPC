cmake_minimum_required(VERSION 3.26)

## env settings
include(env_settings.cmake)

set(CMAKE_PREFIX_PATH ${QT_ROOT}/lib/cmake)
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
project(tc_client_pc)

set(CMAKE_CXX_STANDARD 20)

include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)

## Template
if (WIN32)
    link_directories(${VCPKG_ROOT}/installed/x64-windows/lib)
    include_directories(${VCPKG_ROOT}/installed/x64-windows/include)
elseif (APPLE)
    link_directories(${VCPKG_ROOT}/installed/x64-osx/lib)
    include_directories(${VCPKG_ROOT}/installed/x64-osx/include)
elseif (UNIX)

endif ()
## Template

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
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/deps)
include_directories(${CMAKE_SOURCE_DIR}/deps/tc_3rdparty)
include_directories(${CMAKE_SOURCE_DIR}/deps/tc_3rdparty/eventbus/src)
include_directories(${CMAKE_SOURCE_DIR}/deps/tc_client_sdk)

include_directories(${CMAKE_BINARY_DIR}/deps/tc_message)

# 执行的时候就Copy一下，方便测试
#file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/settings.toml" DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(src)
add_subdirectory(deps)