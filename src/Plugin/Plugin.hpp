//
// Created by toma- on 03/04/2023.
//

#ifndef PLUGIN_HPP
#define PLUGIN_HPP

enum Event
{
    BlockMined = 0,
    ItemBroken = 1,
    ItemCrafted = 2,
    ItemUsed = 3,
    ItemPicked = 4,
    ItemDropped = 5,
    EntityKilled = 6,
    EntityDamaged = 7,
    EntitySpawned = 8,
    EntityDespawned = 9,
    PlayerJoin = 10,
    PlayerLeave = 11,
    PlayerMove = 12,
    PlayerChat = 13,
    PlayerDeath = 14,
    PlayerRespawn = 15,
    PlayerAttack = 16,
    PlayerInteract = 17,
    PlayerBreakBlock = 18,
    PlayerPlaceBlock = 19,

};

class Plugin {
public:
    Plugin();
    virtual ~Plugin();

    void load(PluginInterface *interface) final {
        this->interface = interface;
    };
    void registerEvent(Event::PlayerJoin, void (*callback)(void)) final {

    };
    virtual void initialize() = 0;
    virtual void tick() = 0;

protected:
    PluginInterface *interface;
};


#endif //PLUGIN_INTERFACE_PLUGIN_HPP
