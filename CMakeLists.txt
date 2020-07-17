cmake_minimum_required(VERSION 3.6)
project(JDLOG VERSION 1.0 LANGUAGES CXX)

# default built type is Release
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif (NOT CMAKE_BUILD_TYPE)

STRING(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_LOWER)

set(CMAKE_CXX_STANDARD 11)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11 -O3 -Werror=return-type")
endif ()

set(SDK_DIR ${CMAKE_SOURCE_DIR}/output/sdk)
set(INSTALL_DIR ${CMAKE_SOURCE_DIR}/output/bin)

include_directories(jd_log jd_log/include)

add_subdirectory(jd_log)
add_subdirectory(demo)
