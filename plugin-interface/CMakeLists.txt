include_directories(plugin-interface ../cubic-server)
include_directories(plugin-interface src)

add_library(plugin-interface SHARED src/PluginInterface.cpp)