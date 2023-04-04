#ifndef PLUGIN_INTERFACE_HPP
#define PLUGIN_INTERFACE_HPP

class Server;

class PluginInterface {
public:
    PluginInterface(Server &server);
    ~PluginInterface(void) = default;
   
};

#endif
