### GammaRay Client for PC platform

#### How to build
#### 1. Clone the repo
```c++
    git clone --recursive ...
```

#### 2. Install dependences by VCPKG *OR* use the libraries in [GammaRay]()
##### 2.1 Install in this repo, please see [GammaRay]()
```c++
    cd {your-project-folder}/deps/tc_3rdparty/vcpkg
```
##### 2.2 Use exists in env_settings.cmake
```cmake
    set(VCPKG_ROOT D:/source/GammaRay/deps/tc_3rdparty/vcpkg)
```
##### 2.3 Set all env values
```cmake
    set(VCPKG_ROOT D:/source/GammaRay/deps/tc_3rdparty/vcpkg)
    set(QT_ROOT D:/Qt6.7/6.7.0/msvc2019_64)
    set(VK_SDK C:/VulkanSDK/1.3.275.0/Include)
```
