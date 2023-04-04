//
// Created by toma- on 03/04/2023.
//

#ifndef PLUGIN_HPP
#define PLUGIN_HPP

#include <memory>

class Plugin {
public:
    virtual Plugin(void) = 0;
    virtual ~Plugin(void) = 0;

    void setPluginInterface(std::shared_ptr<PluginInterface>) final;

    virtual void tick(void) = 0;

    virtual void onPlayerUse(Player &) = 0;
    virtual void onPlayerPunch(Player &) = 0;
    virtual void onPlayerAttack(Player &, Entity &) = 0;
    virtual void onPlayerMine(Player &) = 0;
    virtual void onPlayerBreak(Player &) = 0;
    virtual void onPlayerWalk(Player &) = 0;
    virtual void onPlayerSneak(Player &) = 0;
    virtual void onPlayerRun(Player &) = 0;
    virtual void onPlayerCrawl(Player &) = 0;
    virtual void onPlayerStand(Player &) = 0;
    virtual void onPlayerSwim(Player &) = 0;
    virtual void onPlayerFly(Player &) = 0;

    virtual void onPlayerFly(Player &) = 0;

private:
    std::shared_ptr<PluginInterface> pluginInterface;
};


#endif //PLUGIN_INTERFACE_PLUGIN_HPP
