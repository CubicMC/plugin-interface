cmake_minimum_required(VERSION 3.14.0)

project(battle_royale VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_SHARED_LIBRARY_PREFIX "")

include_directories(${CMAKE_SOURCE_DIR}/../plugin-interface/src)
include_directories(${CMAKE_SOURCE_DIR}/../plugin)
include_directories(${CMAKE_SOURCE_DIR}/../cubic-server)
include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(${CMAKE_PROJECT_NAME} SHARED ${CMAKE_SOURCE_DIR}/src/BattleRoyal.cpp)
