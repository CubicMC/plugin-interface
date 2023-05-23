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

void onPlayerJoin(PluginInterface *interface, Player *player)
{
    std::cout << "BattleRoyale - Player joined : " << std::endl;
}

void onPlayerLeave(PluginInterface *interface, Player *player)
{
    std::cout << "BattleRoyale - Player leaved : " << std::endl;
}

void onBlockPlace(PluginInterface *interface, Block *block, Vector3<int> *position)
{
    std::cout << "BattleRoyale - Block placed : " << *position << std::endl;
}

void onBlockDestroy(PluginInterface *interface, Block *block, Vector3<int> *position)
{
    std::cout << "BattleRoyale - Block destroyed : " << *position << std::endl;
}