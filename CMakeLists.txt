cmake_minimum_required(VERSION 3.20.0)

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.24.0)
    cmake_policy(SET CMP0135 OLD)
endif()

option(USE_CLANG "Build application with clang" OFF)

if (USE_CLANG)
    set(CMAKE_CXX_COMPILER /usr/bin/clang++)
    set(CMAKE_C_COMPILER /usr/bin/clang)
endif()

project(PluginInterface VERSION 0.1.0 LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    cubic-server
    GIT_REPOSITORY https://github.com/CubicMC/cubic-server.git
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
    GIT_TAG v0.2.0-beta
)

FetchContent_MakeAvailable(
    cubic-server
)

include_directories(${CMAKE_PROJECT_NAME} cubic-server)
include_directories(${CMAKE_PROJECT_NAME} plugin-interface)

add_library(${CMAKE_PROJECT_NAME} SHARED)

add_subdirectory(plugin-interface)
