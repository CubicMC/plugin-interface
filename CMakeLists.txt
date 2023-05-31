cmake_minimum_required(VERSION 3.14.0)

project(plugin-interface VERSION 0.1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(plugin-interface)

install(TARGETS ${CMAKE_PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})