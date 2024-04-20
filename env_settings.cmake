add_definitions(-DSTEAM_RELEASE=1)

## Template
if (WIN32)

elseif (APPLE)

elseif (UNIX)

endif ()
## Template


if (WIN32)
    set(VCPKG_ROOT C:/source/vcpkg)
    set(QT_ROOT D:/Qt6/6.7.0/msvc2019_64)
elseif (APPLE)
    set(VCPKG_ROOT /Users/shark/source/vcpkg)
    set(QT_ROOT /Users/shark/Qt/6.4.3/macos)
elseif (UNIX)

endif ()
