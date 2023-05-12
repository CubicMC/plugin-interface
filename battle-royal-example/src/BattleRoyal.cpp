#include <iostream>
#include "BattleRoyal.hpp"
#include "PluginInterface.hpp"
#include "Server.hpp"

void initialize(PluginInterface *interface)
{
    std::cout << "par nous meme hein" << std::endl;
    std::cout << interface->server->isRunning() << std::endl;
}