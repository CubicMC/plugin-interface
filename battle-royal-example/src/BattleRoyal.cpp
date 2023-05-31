#include <unordered_map>
#include <memory>

#include "BattleRoyal.hpp"
#include "PluginInterface.hpp"
#include "Plugin.hpp"
#include "Player.hpp"
#include "WorldGroup.hpp"
#include "PlayerAttributes.hpp"
#include "logging/logging.hpp"

BattleRoyale::Challenger::Challenger(Player &player):
    player(player),
    ready(false),
    alive(true)
{}

BattleRoyale::BattleRoyale():
    _status(BattleRoyale::Waiting)
{}

BattleRoyale &BattleRoyale::getInstance()
{
    static BattleRoyale instance;

    return instance;
}

void BattleRoyale::setWorldGroup(WorldGroup *worldGroup) noexcept
{
    this->_group = worldGroup;
}

WorldGroup *BattleRoyale::getWorldGroup(void) noexcept
{
    return (this->_group);
}

bool BattleRoyale::isPlaying(const std::string &name) const noexcept
{
    return (this->_players.contains(name));
}

void BattleRoyale::join(Player &player)
{
    if (this->_status == BattleRoyale::Waiting || this->_status == BattleRoyale::Beginning) {
        this->_players[player.getUsername()] = std::make_unique<BattleRoyale::Challenger>(player);

        player.setGamemode(player_attributes::Gamemode::Adventure);
    } else
        this->spectate(player);
}

void BattleRoyale::spectate(Player &player)
{
    this->_spectators[player.getUsername()] = &player;
    player.setGamemode(player_attributes::Gamemode::Spectator);
}

void BattleRoyale::playerLeft(Player &player)
{
    if (isSpectating(player.getUsername())) {
        this->_spectators.erase(player.getUsername());
        return;
    }
    switch (this->_status)
    {
    case BattleRoyale::Waiting: // remove player from everything
        if (this->_players.contains(player.getUsername()))
            this->_players.erase(player.getUsername());
        break;
    case BattleRoyale::Beginning: // remove player from everything and reset timer
        if (this->_players.contains(player.getUsername()))
            this->_players.erase(player.getUsername());
        this->_timestamp = std::time(nullptr);
        break;
    case BattleRoyale::Running: // counts as a forfeit
        if (this->_players.contains(player.getUsername())) {
            this->_players.erase(player.getUsername());
            this->_group->getChat()->sendSystemMessage(player.getUsername() + " is eliminated!", *this->_group);
        }
        break;
    default:
        break;
    }
    // leaving in the Finished, Closed or Interrupted (unlikely) phase does not have any impact
}

void BattleRoyale::playerDied(Player &player)
{
    switch (this->_status)
    {
    case BattleRoyale::Waiting: // HOW ? kick him, that'll teach him
        // TODO: kick player
        break;
    case BattleRoyale::Beginning: // HOW ? kick him, that'll teach him
        // TODO: kick player
        break;
    case BattleRoyale::Running: // if running, counts as a forfeit
        if (this->_players.contains(player.getUsername())) {
            this->_players[player.getUsername()]->alive = false;
            player.setGamemode(player_attributes::Gamemode::Spectator);
            this->_group->getChat()->sendSystemMessage(player.getUsername() + " has died!", *this->_group);
        }
        break;
    default:
        break;
    }
    // dying in the Finished, Closed or Interrupted phase should not be possible and does not have any impact
}

int BattleRoyale::getAlivePlayerNumber(void)
{
    int count = 0;

    for (const auto &[_, player] : this->_players) {
        if (player->alive)
            count++;
    }
    return (count);
}

void BattleRoyale::begin()
{
    // if more than 1 player and all players are ready, go to the beginning phase
    for (const auto &[_, player] : this->_players) {
        if (player->ready == false)
            return;
    }
    this->_status = BattleRoyale::Beginning;
    this->_timestamp = std::time(nullptr);
}

void BattleRoyale::start()
{
    // if a player joins or a ready player cancels, go back to the waiting phase
    for (const auto &[_, player] : this->_players) {
        if (player->ready == false) {
            this->_status = BattleRoyale::Waiting;
            return;
        }
    }
    // if all players are ready and no player quit/join in for 5 seconds, go to the running phase
    if (std::time(nullptr) >= this->_timestamp + 5) {
        for (const auto &[_, player] : this->_players) {
            player->alive = true;
            player->player.setGamemode(player_attributes::Gamemode::Adventure);
            player->player.getWorldGroup()->getChat()->sendSystemMessage("Kill everyone to win. Good Luck.", player->player);
            // TODO: clear inventory and teleport players and spectators
        }
        this->_status = BattleRoyale::Running;
        this->_timestamp = std::time(nullptr);
    }
}

void BattleRoyale::finish()
{
    // one player remaining, go to the finishing phase
    if (this->_players.size() == 1) {
        this->_players[0]->player.getWorldGroup()->getChat()->sendSystemMessage(this->_players[0]->player.getUsername() + " won the match!", *this->_group);
        this->_status = BattleRoyale::Finished;
        this->_timestamp = std::time(nullptr);
        return;
    }
    // no player remaining (very rare), no winner, go to the finishing phase
    if (this->_players.size() == 0) {
        // TODO: notify players
        this->_status = BattleRoyale::Finished;
        this->_timestamp = std::time(nullptr);
        return;
    }
}

void BattleRoyale::close()
{
    // 8 seconds after the game is over
    if (std::time(nullptr) > this->_timestamp + 8) {
        this->_status = BattleRoyale::Closed;
        return;
    }
}

void BattleRoyale::reset()
{
    for (auto &[_, player] : this->_players) {
        player->ready = false;
        player->player.setGamemode(player_attributes::Gamemode::Adventure);
    }
    for (auto &[name, spectator] : this->_spectators) {
        this->join(*spectator);
        this->_spectators.erase(name);
    }
    this->_status = BattleRoyale::Waiting;
}

void BattleRoyale::interrupt() noexcept
{
    this->_status = BattleRoyale::Interrupted;
}

BattleRoyale::Status BattleRoyale::getStatus() const noexcept
{
    return (this->_status);
}

void BattleRoyale::setReady(Player &player, bool ready)
{
    if (this->_players.contains(player.getUsername())) {
        this->_players[player.getUsername()]->ready = ready;
    }
}

void BattleRoyale::update()
{
    switch (this->_status)
    {
    case BattleRoyale::Waiting: // waiting for players to be ready
        this->begin();
        break;
    case BattleRoyale::Beginning: // starting unless a player is not ready anymore
        this->start();
        break;
    case BattleRoyale::Running: // running, waiting for the last player
        this->finish();
        break;
    case BattleRoyale::Finished: // last player standing, anouncing victory
        this->close();
        break;
    case BattleRoyale::Closed: // closed, restart the server
        // TODO: restart the server
        break;
    case BattleRoyale::Interrupted: // game interrupted, stop the server
        // TODO: stop the server
        break;
    }
}
