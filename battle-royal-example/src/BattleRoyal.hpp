#ifndef PLUGIN_HPP_
#define PLUGIN_HPP_

#include "Plugin.hpp"

class BattleRoyal
{
public:
    BattleRoyal() = default;
    ~BattleRoyal() = default;

    static BattleRoyal &getInstance() {
        static BattleRoyal instance;

        return instance;
    }
};

#endif