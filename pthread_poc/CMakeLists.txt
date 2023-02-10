cmake_minimum_required(VERSION 3.0.0)
project(pthread_poc VERSION 0.1.0)

include(CTest)
enable_testing()
add_executable(pthread_poc main.cpp)
target_link_libraries(pthread_poc pthread)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
