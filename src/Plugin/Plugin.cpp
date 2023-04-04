//
// Created by toma- on 03/04/2023.
//

#include "Plugin.hpp"

void Plugin::setPluginInterface(std::shared_ptr<PluginInterface> interface)
{
    this->pluginInterface = interface;
}
