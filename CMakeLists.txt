cmake_minimum_required(VERSION 3.14.0)
project(PluginInterface)

set(CMAKE_CXX_STANDARD 20)

include_directories(src/Plugin)
include_directories(src/PluginInterface)

add_executable(
        plugin_interface
        src/Plugin/Plugin.cpp
        src/Plugin/Plugin.hpp
        src/PluginInterface/PluginInterface.cpp
        src/PluginInterface/PluginInterface.hpp
)