add_definitions(-DSTEAM_RELEASE=1)

## Template
if (WIN32)

elseif (APPLE)

elseif (UNIX)

endif ()
## Template


if (WIN32)
    set(VCPKG_ROOT C:/source/vcpkg)
    set(QT_ROOT D:/Qt/6.6.1/msvc2019_64)
elseif (APPLE)
    set(VCPKG_ROOT /Users/shark/source/vcpkg)
    set(QT_ROOT /Users/shark/Qt/6.4.3/macos)
elseif (UNIX)

endif ()
