cmake_minimum_required(VERSION 3.14.0)

set(PLUGIN_INTERFACE_PROJECT_NAME plugin-interface)

project(${PLUGIN_INTERFACE_PROJECT_NAME} VERSION 0.1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.11.0
)

FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
    GIT_TAG v2.9
)

FetchContent_MakeAvailable(
    json
    argparse
    spdlog
)

add_subdirectory(plugin-interface)

target_link_libraries (plugin-interface PRIVATE
    nlohmann_json::nlohmann_json
    argparse
    spdlog::spdlog
)

install(TARGETS ${PLUGIN_INTERFACE_TARGET_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})