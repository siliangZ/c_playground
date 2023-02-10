cmake_minimum_required(VERSION 3.0.0)
project(async_notify_test VERSION 0.1.0)
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)
SET(CMAKE_SYSTEM_PROCESSOR arm)

include(CTest)
enable_testing()

add_executable(async_notify_test main.cpp)

set(CMAKE_SYSROOT /opt/sysroots/aarch64-xilinx-linux/)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
