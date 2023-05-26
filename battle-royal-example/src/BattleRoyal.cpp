#include <iostream>

#include "BattleRoyal.hpp"
#include "PluginInterface.hpp"
#include "Plugin.hpp"

#include "Server.hpp"
#include "Player.hpp"

void initialize(PluginInterface *interface)
{
    std::cout << "par nous meme hein" << std::endl;
    std::cout << interface->server->isRunning() << std::endl;
}

void destroy(PluginInterface *interface)
{
    std::cout << "BattleRoyale - destroyed" << std::endl;
}

bool onPlayerJoin(PluginInterface *interface, Player *player)
{
    std::cout << "BattleRoyale - Player joined : " << std::endl;
    return (true);
}

bool onPlayerLeave(PluginInterface *interface, Player *player)
{
    std::cout << "BattleRoyale - Player leaved : " << std::endl;
    return (true);
}

bool onBlockPlace(PluginInterface *interface, Block *block, Vector3<int> *position)
{
    std::cout << "BattleRoyale - Block placed : " << *position << std::endl;
    return (true);
}

bool onBlockDestroy(PluginInterface *interface, Block *block, Vector3<int> *position)
{
    std::cout << "BattleRoyale - Block destroyed : " << *position << std::endl;
    return (true);
}