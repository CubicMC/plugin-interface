#include <list>
#include <memory>

#include "BattleRoyal.hpp"
#include "PluginInterface.hpp"
#include "Plugin.hpp"
#include "logging/Logger.hpp"

BattleRoyale &BattleRoyale::getInstance()
{
    static BattleRoyale instance;

    return instance;
}

bool BattleRoyale::isPlaying(const std::string &name) const noexcept
{
    return (this->_players.contains(name));
}

bool BattleRoyale::isSpectating(const std::string &name) const noexcept
{
    return (!this->isPlaying(name));
}

void BattleRoyale::join(const std::string &name)
{
    if (this->_status == BattleRoyale::Waiting || this->_status == BattleRoyale::Beginning) {
        this->_players.insert(name);
        // TODO: set gamemode to survival
    } else
        this->spectate(name);
}

void BattleRoyale::spectate(const std::string &name)
{
    // TODO: set gamemode to spectator
}

void BattleRoyale::playerLeft(const std::string &player)
{
    switch (this->_status)
    {
    case BattleRoyale::Waiting: // remove player from everything
        if (this->_players.contains(player))
            this->_players.erase(player);
        if (this->_readyPlayers.contains(player))
            this->_readyPlayers.erase(player);
        break;
    case BattleRoyale::Beginning: // remove player from everything and reset timer
        if (this->_players.contains(player))
            this->_players.erase(player);
        this->_timestamp = std::time(nullptr);
        break;
    case BattleRoyale::Running: // counts as a forfeit
        if (this->_players.contains(player)) {
            this->_players.erase(player);
            // TODO: notify player (forfeit)
        }
        break;
    }
    // leaving in the Finished, Closed or Interrupted (unlikely) phase does not have any impact
}

void BattleRoyale::playerDied(const std::string &player)
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
        if (this->_players.contains(player)) {
            this->_players.erase(player);
            // TODO: notify player (forfeit)
        }
        break;
    }
    // dying in the Finished, Closed or Interrupted phase should not be possible and does not have any impact
}

void BattleRoyale::begin()
{
    // if more than 1 player and all players are ready, go to the beginning phase
    if (this->_players.size() > 1 && this->_players.size() > this->_readyPlayers.size())
        return;
    this->_status = BattleRoyale::Beginning;
    this->_timestamp = std::time(nullptr);
}

void BattleRoyale::start()
{
    // if a player joins or a ready player cancels, go back to the waiting phase
    if (this->_players.size() < 2 || this->_players.size() > this->_readyPlayers.size()) {
        this->_status = BattleRoyale::Waiting;
        return;
    }
    // if all players are ready and no player quit/join in for 5 seconds, go to the running phase
    if (std::time(nullptr) >= this->_timestamp + 5) {
        this->_status = BattleRoyale::Running;
        this->_timestamp = std::time(nullptr);
        // TODO: update gamemode, clear inventory and teleport players and spectators
        return;
    }
}

void BattleRoyale::finish()
{
    // one player remaining, go to the finishing phase
    if (this->_players.size() == 1) {
        // TODO: notify players
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
    // 8 seconds after the game is over, kick players and destroy the game
    if (std::time(nullptr) > this->_timestamp + 8) {
        // TODO: kick players
        this->_status = BattleRoyale::Closed;
        return;
    }
}

void BattleRoyale::interrupt() noexcept
{
    this->_status = BattleRoyale::Interrupted;
}

BattleRoyale::Status BattleRoyale::getStatus() const noexcept
{
    return (this->_status);
}

void BattleRoyale::setReady(const std::string &name, bool ready)
{
    if (ready == true)
        this->_readyPlayers.insert(name);
    else
        this->_readyPlayers.erase(name);
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
