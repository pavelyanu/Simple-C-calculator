cmake_minimum_required(VERSION 3.0.0)
project(Calculator VERSION 0.1.0)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(apps)
add_subdirectory(src)
add_subdirectory(tests)