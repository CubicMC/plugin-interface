include_directories(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/cubic-server)
include_directories(${CMAKE_PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/src)

add_library(${CMAKE_PROJECT_NAME} SHARED ${CMAKE_CURRENT_LIST_DIR}/src/PluginInterface.cpp)