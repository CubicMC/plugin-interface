#include <iostream>
#include <memory>

#include "logging/logging.hpp"

#include "BattleRoyal.hpp"
#include "PluginInterface.hpp"
#include "Plugin.hpp"

#include "Server.hpp"
#include "Player.hpp"

#include "Commands.hpp"

bool initialize(PluginInterface *interface)
{
    interface->server->addCommand(std::make_unique<command_parser::Ready>());
    interface->server->addCommand(std::make_unique<command_parser::NotReady>());
    interface->server->addCommand(std::make_unique<command_parser::Interrupt>());

    LINFO("Battle Royale initialized");
    return (false);
}

bool destroy(PluginInterface *interface)
{
    LINFO("Battle Royale destroyed");
    return (false);
}

bool onPlayerJoin(PluginInterface *interface, Player *player)
{
    BattleRoyale::getInstance().join(*player);
    return (false);
}

bool onPlayerLeave(PluginInterface *interface, Player *player)
{
    BattleRoyale::getInstance().playerLeft(*player);
    return (true);
}

bool onEntityDamage(PluginInterface *interface, Entity *source, float amount)
{
    switch (BattleRoyale::getInstance().getStatus())
    {
    case BattleRoyale::Waiting:
        return (true);
        break;
    case BattleRoyale::Beginning:
        return (true);
        break;
    case BattleRoyale::Running:
        return (false);
        break;
    case BattleRoyale::Finished:
        return (true);
        break;
    case BattleRoyale::Closed:
        return (true);
        break;
    case BattleRoyale::Interrupted:
        return (true);
        break;
    }
    return (true);
}

bool onBlockPlace(PluginInterface *interface, uint32_t block_id, Vector3<int> *position)
{
    switch (BattleRoyale::getInstance().getStatus())
    {
    case BattleRoyale::Waiting:
        return (true);
        break;
    case BattleRoyale::Beginning:
        return (true);
        break;
    case BattleRoyale::Running:
        return (false);
        break;
    case BattleRoyale::Finished:
        return (false);
        break;
    case BattleRoyale::Closed:
        return (false);
        break;
    case BattleRoyale::Interrupted:
        return (true);
        break;
    }
    return (true);
}

bool onBlockDestroy(PluginInterface *interface, uint32_t block_id, Vector3<int> *position)
{
    switch (BattleRoyale::getInstance().getStatus())
    {
    case BattleRoyale::Waiting:
        return (true);
        break;
    case BattleRoyale::Beginning:
        return (true);
        break;
    case BattleRoyale::Running:
        return (false);
        break;
    case BattleRoyale::Finished:
        return (false);
        break;
    case BattleRoyale::Closed:
        return (false);
        break;
    case BattleRoyale::Interrupted:
        return (true);
        break;
    }
    return (true);
}
