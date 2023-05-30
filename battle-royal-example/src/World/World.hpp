#ifndef PLUGIN_WORLD_HPP
#define PLUGIN_WORLD_HPP

#include "../World.hpp"
#include "WorldGroup.hpp"
#include "world_storage/Persistence.hpp"
#include <memory>

class BattleRoyaleWorld : public World {
public:
    BattleRoyaleWorld(std::shared_ptr<WorldGroup> worldGroup, std::string folder);
    ~BattleRoyaleWorld() override = default;
    void tick() override;
    void initialize() override;
    void stop() override;

    world_storage::Persistence persistence;
};

#endif // PLUGIN_WORLD_HPP
