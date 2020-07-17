# JD_LOG

## jd_log目录结构
```
 * 源码结构
 * jd_log
 * |--jd_log
 * |  |--include/
 * |  |-- *.h
 * |  |-- *.cpp
 * |  |--CMakeLists.txt
 * |--demo
 * |  |--demo.cpp
 * |  |--CMakeLists.txt
 * |--CMakeLists.txt
 *
 * 生成目录
 * |--output
 * |  |--bin
 * |  |--sdk
```  

## CMake跨平台编译

* Windows VS 编译
  ```
    mkdir build && cd build
    cmake -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 14 2015" ..
    MSBuild.exe JDLOG.sln /p:configuration=Release
  ```

* Linux GCC 编译
  ```
    mkdir build && cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make
    make install
  ```