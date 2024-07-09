add_definitions(-DSTEAM_RELEASE=1)

## Template
if (WIN32)

elseif (APPLE)

elseif (UNIX)

endif ()
## Template


if (WIN32)
    set(VCPKG_ROOT D:/source/GammaRay/deps/tc_3rdparty/vcpkg)
    set(QT_ROOT D:/Qt6.7/6.7.0/msvc2019_64)
    set(VK_SDK C:/VulkanSDK/1.3.275.0/Include)
elseif (APPLE)
    set(VCPKG_ROOT /Users/shark/source/vcpkg)
    set(QT_ROOT /Users/shark/Qt/6.4.3/macos)
elseif (UNIX)

endif ()
