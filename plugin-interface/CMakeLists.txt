cmake_minimum_required(VERSION 3.14.0)

project(plugin_interface VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/../cubic-server)
include_directories(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src)

add_library(${CMAKE_PROJECT_NAME} SHARED ${CMAKE_SOURCE_DIR}/src/PluginInterface.cpp)

install(TARGETS ${CMAKE_PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
