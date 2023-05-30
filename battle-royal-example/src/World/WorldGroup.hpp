#ifndef PLUGIN_WORLDGROUP_HPP
#define PLUGIN_WORLDGROUP_HPP

#include "WorldGroup.hpp"

class BattleRoyaleWorldGroup : public WorldGroup, public std::enable_shared_from_this<DefaultWorldGroup> {
public:
    BattleRoyaleWorldGroup(std::shared_ptr<Chat> chat);
    ~BattleRoyaleWorldGroup() override = default;
    void initialize() override;
};

#endif // PLUGIN_WORLDGROUP_HPP
