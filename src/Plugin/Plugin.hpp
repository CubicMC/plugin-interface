//
// Created by toma- on 03/04/2023.
//

#ifndef PLUGIN_HPP
#define PLUGIN_HPP

class PluginInterface;

class Player;
class Chat;
class Block;
class Item;
class Inventory;

class World;
class Dimension;
class Chunk

class Vector3;

// TODO: Add more events
void initialize(PluginInterface *interface);
void destroy(PluginInterface *interface);
void onPlayerJoin(PluginInterface *interface, Player *player);
void onPlayerLeave(PluginInterface *interface, Player *player);
void onPlayerChat(PluginInterface *interface, Player *player, Chat *chat, std::string message);
void onEntitySpawn(PluginInterface *interface, Entity *entity);
void onEntityMove(PluginInterface *interface, Entity *entity, Vector3 *from, Vector3 *to);
void onEntityRotate(PluginInterface *interface, Entity *entity, Vector3 *from, Vector3 *to);
void onEntityInteractEntity(PluginInterface *interface, Entity *source, Entity *target);
void onEntityInteractBlock(PluginInterface *interface, Entity *entity, Block *block);
void onEntityDamage(PluginInterface *interface, Entity *source, float amount);
void onEntityUse(PluginInterface *interface, Entity *entity, Item *item);
void onBlockPlace(PluginInterface *interface, Block *block, Vector3 *position);
void onBlockDestroy(PluginInterface *interface, Block *block, Vector3 *position
void onBlockInteract(PluginInterface *interface, Block *block, Vector3 *position, Entity *entity);
void onInventoryOpen(PluginInterface *interface, Player *player, Inventory *inventory);
void onInventoryClose(PluginInterface *interface, Player *player, Inventory *inventory);
void onInventoryChange(PluginInterface *interface, Inventory *inventory);
void onWorldLoad(PluginInterface *interface, World *world
void onDimensionLoad(PluginInterface *interface, Dimension *dimension);
void onChunkLoad(PluginInterface *interface, Chunk *chunk);

#endif //PLUGIN_INTERFACE_PLUGIN_HPP
