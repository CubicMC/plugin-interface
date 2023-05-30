//
// Created by toma- on 03/04/2023.
//

#ifndef PLUGIN_HPP
#define PLUGIN_HPP

class PluginInterface;

class Player;
class Entity;
class Chat;
class Block;
class Item;
class Inventory;

class World;
class Dimension;
class Chunk;

template<typename T>
class Vector3;

extern "C" {
    // TODO: Add more events
    bool initialize(PluginInterface *interface);
    bool destroy(PluginInterface *interface);
    bool onPlayerJoin(PluginInterface *interface, Player *player);
    bool onPlayerLeave(PluginInterface *interface, Player *player);
    bool onPlayerChat(PluginInterface *interface, Player *player, Chat *chat, std::string message);
    bool onEntitySpawn(PluginInterface *interface, Entity *entity);
    bool onEntityMove(PluginInterface *interface, Entity *entity, Vector3<double> from, Vector3<double> to);
    bool onEntityRotate(PluginInterface *interface, Entity *entity, Vector3<uint8_t> from, Vector3<uint8_t> to);
    bool onEntityInteractEntity(PluginInterface *interface, Entity *source, Entity *target);
    bool onEntityInteractBlock(PluginInterface *interface, Entity *entity, int32_t block_id);
    bool onEntityDamage(PluginInterface *interface, Entity *source, float amount);
    bool onEntityUse(PluginInterface *interface, Entity *entity, Item *item);
    bool onBlockPlace(PluginInterface *interface, int32_t block_id, Vector3<int> position);
    bool onBlockDestroy(PluginInterface *interface, int32_t block_id, Vector3<int> position);
    bool onBlockInteract(PluginInterface *interface, int32_t block_id, Vector3<int> position, Entity *entity);
    bool onInventoryOpen(PluginInterface *interface, Player *player, Inventory *inventory);
    bool onInventoryClose(PluginInterface *interface, Player *player, Inventory *inventory);
    bool onInventoryChange(PluginInterface *interface, Inventory *inventory);
    bool onWorldLoad(PluginInterface *interface, World *world);
    bool onDimensionLoad(PluginInterface *interface, Dimension *dimension);
    bool onChunkLoad(PluginInterface *interface, Chunk *chunk);
}

#endif //PLUGIN_INTERFACE_PLUGIN_HPP
