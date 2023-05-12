#include "PluginInterface.hpp"
#include "Player.hpp"
#include "Client.hpp"

PluginInterface::PluginInterface()
{

}

PluginInterface::~PluginInterface()
{

}

void PluginInterface::load(Server *server) {
    this->server = server;
}

bool PluginInterface::player::isConnected(Player *player) const {
    return !player->getClient()->isDisconnected();
}

// TODO : Banned players
bool PluginInterface::player::isBanned(Player *player) const {
    return false;
}

// TODO : Advancements players
bool PluginInterface::player::hasAdvancement(Player *player) const {
    return false;
}

// TODO : Recipe players
bool PluginInterface::player::hasRecipe(Player *player) const {
    return false;
}

Player *PluginInterface::player::getByID(u128 uuid) {
    // std::vector<Player *> players = _intern->server->getWorldGroup("default")->getWorld("default")->getPlayers();

    // for (int i = 0; i < player->size();  i += 1) {
    //     if (players[i]->getUuid() == uuid) {
    //         return players[i];
    //     }
    // }
    return nullptr;
}

Player *PluginInterface::player::getByName(std::string name) {
    // std::vector<Player *> players = _intern->server->getWorldGroup("default")->getWorld("default")->getPlayers();

    // for (int i = 0; i < player->size();  i += 1) {
    //     if (players[i]->getUsername() == name) {
    //         return players[i];
    //     }
    // }
    return nullptr;
}

// TODO : Sounds player
void PluginInterface::player::playSound(Player *player) {
    return;
}

// TODO : should kick instead of disconnect
void PluginInterface::player::kick(Player *player) {
    // player->getClient()->disconnect();
}

// TODO : ban player
void PluginInterface::player::ban(Player *player) {
    return;
}

// TODO : give advancement to player
void PluginInterface::player::giveAdvancement(Player *player) {
    return;
}

// TODO : revoke advancement to player
void PluginInterface::player::revokeAdvancement(Player *player) {
    return;
}

// TODO : give recipe to player
void PluginInterface::player::giveRecipe(Player *player) {
    return;
}

// TODO : remove recipe to player
void PluginInterface::player::removeRecipe(Player *player) {
    return;
}

void PluginInterface::entity::kill(Entity *entity) {
    // LivingEntity *living = reinterpret_cast<LivingEntity *>(entity);

    // if (living != nullptr) {
    //     living->setHealth(0);
    // }
}

// TODO : despawn entity
void PluginInterface::entity::despawn(Entity *entity) {
    return;
}

void PluginInterface::entity::heal(Entity *entity, float amount) {
    // LivingEntity *living = reinterpret_cast<LivingEntity *>(entity);

    // if (living != nullptr) {
    //     living->setHealth(living->getHealth() + amount);
    // }
}

void PluginInterface::entity::damage(Entity *entity, float amount) {
    // LivingEntity *living = reinterpret_cast<LivingEntity *>(entity);

    // if (living != nullptr) {
    //     living->damage(amount);
    // }
}

// TODO : ride entity
void PluginInterface::entity::ride(Entity *entity) {
    return;
}

// TODO : unride entity
void PluginInterface::entity::unride(Entity *entity) {
    return;
}

// TODO : equip entity
void PluginInterface::entity::equip(Entity *entity) {
    return;
}

// TODO : unequip entity
void PluginInterface::entity::unequip(Entity *entity) {
    return;
}

// TODO : see if this should be implemented
void PluginInterface::block::getByID() {
    return;
}

void PluginInterface::block::getByPosition() {
    return;
}

void PluginInterface::block::destroy() {
    return;
}

void PluginInterface::block::place() {
    return;
}

Inventory *PluginInterface::inventory::getByID() {
    return nullptr;
}

// TODO : see if this is the right way to deal with chest inventories
Inventory *PluginInterface::inventory::getByPosition() {
    return nullptr;
}

void PluginInterface::inventory::addItem() {
    return;
}

void PluginInterface::inventory::removeItem() {
    return;
}

void PluginInterface::inventory::clear() {
    return;
}

Chat *PluginInterface::chat::get() {
    // return _intern->server->getWorldGroup("default")->getWorld("default")->getChat();
    return nullptr;
}

void PluginInterface::command::registerCommand() {
    return;
}

void PluginInterface::command::unregisterCommand() {
    return;
}

void PluginInterface::command::raw() {

}