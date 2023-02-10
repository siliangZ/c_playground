cmake_minimum_required(VERSION 3.0.0)
project(epoll_poc VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(epoll_poc main.cpp)

add_compile_options(--Wall -Werror)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)