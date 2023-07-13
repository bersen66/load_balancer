cmake_minimum_required(VERSION 3.21)
project(proxy)

include(cmake/setup_boost.cmake)
include(cmake/setup_yamlcpp.cmake)
include(cmake/copy_configs.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(proxy)
