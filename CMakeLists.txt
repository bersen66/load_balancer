cmake_minimum_required(VERSION 3.21)
project(proxy)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

include(cmake/setup_boost.cmake)
include(cmake/setup_yamlcpp.cmake)
include(cmake/setup_fmt.cmake)

include(cmake/copy_configs.cmake)

include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(proxy)
