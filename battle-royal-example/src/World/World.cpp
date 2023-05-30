#include "World.hpp"

#include "Overworld.hpp"
#include "TheNether.hpp"
#include "world_storage/Persistence.hpp"
#include <memory>

BattleRoyaleWorld::BattleRoyaleWorld(std::shared_ptr<WorldGroup> worldGroup, std::string folder):
    World(worldGroup, folder),
    persistence(folder)
{
}

void BattleRoyaleWorld::tick() { World::tick(); }

void BattleRoyaleWorld::initialize()
{
    this->_dimensions.emplace("nether", std::make_shared<TheNether>(std::dynamic_pointer_cast<DefaultWorld>(shared_from_this())));
    this->_dimensions.emplace("overworld", std::make_shared<Overworld>(std::dynamic_pointer_cast<DefaultWorld>(shared_from_this())));

    World::initialize();
}

void BattleRoyaleWorld::stop() { World::stop(); }
