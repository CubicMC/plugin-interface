#include "DefaultWorldGroup.hpp"

#include <utility>

#include "WorldGroup.hpp"
#include "World.hpp"
#include "Server.hpp"

BattleRoyaleWorldGroup::BattleRoyaleWorldGroup(std::shared_ptr<Chat> chat):
    WorldGroup(std::move(chat))
{
}

void BattleRoyaleWorldGroup::initialize()
{
    _worlds.emplace("default", std::make_shared<DefaultWorld>(shared_from_this(), CONFIG["level-name"].as<std::string>()));
    _worlds.at("default")->initialize();

    WorldGroup::initialize();
}
