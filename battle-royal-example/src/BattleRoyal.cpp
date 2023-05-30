#include <list>
#include <memory>

#include "BattleRoyal.hpp"
#include "PluginInterface.hpp"
#include "Plugin.hpp"
#include "logging/Logger.hpp"

BattleRoyale::Game::Game(const std::string &name, size_t maxPlayers):
    _identifier(identifier),
    _status(BattleRoyale::Game::Waiting),
    _maxPlayers(maxPlayers),
    _timestamp(std::time(nullptr))
{
    LINFO("Battle Royale", this->_identifier, " created");
}

BattleRoyale::Game::~Game()
{
    LINFO("Battle Royale", this->_identifier, " destroyed");
}

const std::string &BattleRoyale::Game::getIdentifier()
{
    return (this->_identifier);
}

void BattleRoyale::Game::begin(void)
{
    // if more than 1 player and all players are ready, go to the beginning phase
    if (this->_players.size() > 1 && this->_players.size() > this->_readyPlayers.size())
        return;
    this->_status = BattleRoyale::Game::Beginning;
    this->_timestamp = std::time(nullptr);

}

void BattleRoyale::Game::start(void)
{
    // if a player joins or a ready player cancels, go back to the waiting phase
    if (this->_players.size() < 2 || this->_players.size() > this->_readyPlayers.size()) {
        this->_status = BattleRoyale::Game::Waiting;
        return;
    }
    // if all players are ready and no player quit/join in for 5 seconds, go to the running phase
    if (std::time(nullptr) >= this->_timestamp + 5) {
        this->_status = BattleRoyale::Game::Running;
        this->_timestamp = std::time(nullptr);
        // TODO: update gamemode, clear inventory and teleport players and spectators
        return;
    }
}

void BattleRoyale::Game::finish(void)
{
    // one player remaining, go to the finishing phase
    if (this->_players.size() == 1) {
        // TODO: notify players
        this->_status = BattleRoyale::Game::Finished;
        this->_timestamp = std::time(nullptr);
        return;
    }
}

void BattleRoyale::Game::close(void)
{
    // 8 seconds after the game is over, kick players and destroy the game
    if (std::time(nullptr) > this->_timestamp + 8) {
        // TODO: kick players
        this->_status = BattleRoyale::Game::Closed;
        return;
    }
}

void BattleRoyale::Game::interrupt(void)
{
    this->_status = BattleRoyale::Game::Interrupted;
}

void BattleRoyale::Game::addPlayer(const std::string &player)
{
    // if game already running or too much players, join as a spectator
    if ((this->_status != BattleRoyale::Game::Waiting && this->_status != BattleRoyale::Game::Beginning) || \
        this->_players.size() >= this->_maxPlayers) {
        this->addSpectator(player);
        return;
    }
    // TODO: update gamemode
    this->_timestamp = std::time(nullptr);
    this->_players.insert(player);
    LDEBUG(player, " joined ", this->_identifier);
}

void BattleRoyale::Game::addSpectator(const std::string &spectator)
{
    // TODO: update gamemode
    this->_spectators.insert(spectator);
    LDEBUG(spectator, " spectates ", this->_identifier);
}

void BattleRoyale::Game::playerLeave(const std::string &player)
{
    // never heard of that player, do nothing
    if (!this->_players.contains(player) && !this->_spectators.contains(player))
        return;
    // reset timer when game is beginning
    if (this->_status == BattleRoyale::Game::Beginning)
        this->_timestamp = std::time(nullptr);
    // remove player from game
    if (this->_readyPlayers.contains(player))
        this->_readyPlayers.erase(player);
    if (this->_players.contains(player))
        this->_players.erase(player);
    if (this->_spectators.contains(player))
        this->_spectators.erase(player);
    LDEBUG(player, " left ", this->_identifier);
}

void BattleRoyale::Game::playerDied(const std::string &player)
{
    // TODO: notify players, change player gamemode, respawn player
    this->_players.erase(player);
    this->_spectators.insert(player);
}

const BattleRoyale::Game::Status &BattleRoyale::Game::getStatus(void) const noexcept
{
    return (this->_status);
}

size_t BattleRoyale::Game::getMaxPlayerNumber(void) const noexcept
{
    return (this->_maxPlayers);
}

size_t BattleRoyale::Game::getPlayerNumber(void) const noexcept
{
    return (this->_players.size());
}

void BattleRoyale::Game::setMaxPlayerNumber(size_t nbr) noexcept
{
    this->_maxPlayers = nbr;
}

void BattleRoyale::Game::setReady(const std::string &name, bool ready)
{
    if (ready == true)
        this->_readyPlayers.insert(name);
    else
        this->_readyPlayers.erase(name);
}

BattleRoyale::BattleRoyale(size_t defaultMaxPlayers):
    _defaultMaxPlayers(defaultMaxPlayers)
{}

std::unique_ptr<BattleRoyale::Game> &BattleRoyale::join(const std::string &player)
{
    // looks for an unstarted game with enough place
    for (auto &[_, game] : this->_games) {
        if (game->getStatus() == BattleRoyale::Game::Waiting && game->getPlayerNumber() == game->getMaxPlayerNumber()) {
            game->addPlayer(player);
            return (game);
        }
    }

    // no game found: create a new one and join
    std::unique_ptr<BattleRoyale::Game> &newGame = this->addGame();

    newGame->addPlayer(player);
    return (newGame);
}

std::unique_ptr<BattleRoyale::Game> &join(const std::string &player, std::unique_ptr<BattleRoyale::Game> &game)
{
    if (game)
        game->addPlayer(player);
    return (game);
}

std::unique_ptr<BattleRoyale::Game> &joinAsSpectator(const std::string &player, std::unique_ptr<BattleRoyale::Game> &game)
{
    if (game)
        game->addSpectator(player);
    return (game);
}

std::unique_ptr<BattleRoyale::Game> &BattleRoyale::addGame()
{
    // get unique game number
    size_t number = 0;

    while (this->_games.contains(identifier + std::to_string(number))) {}

    // create and return a new game
    auto it = this->_games.insert({identifier + std::to_string(number), std::make_unique<BattleRoyale::Game>(identifier + std::to_string(number), this->_defaultMaxPlayers)});

    return ((*it.first).second);
}

std::unique_ptr<BattleRoyale::Game> &BattleRoyale::addGame(size_t maxPlayers)
{
    // get unique game number
    size_t number = 0;

    while (this->_games.contains(identifier + std::to_string(number))) {}

    // create and return a new game
    auto it = this->_games.insert({identifier + std::to_string(number), std::make_unique<BattleRoyale::Game>(identifier + std::to_string(number), maxPlayers)});

    return ((*it.first).second);
}

void BattleRoyale::closeGame(const std::string &game)
{
    if (this->_games.contains(game) && this->_games.at(game)->getStatus() == BattleRoyale::Game::Closed) {
        this->_games.erase(game);
    }
}

void BattleRoyale::closeGames(void)
{
    for (auto &[name, game] : this->_games) {
        this->closeGame(name);
    }
}

void BattleRoyale::forceCloseGames(void)
{
    for (auto &[name, game] : this->_games) {
        game->close();
        this->_games.erase(name);
    }
}

bool BattleRoyale::hasGame(const std::string &identifier)
{
    return (this->_games.contains(name));
}

std::unique_ptr<BattleRoyale::Game> &BattleRoyale::getGame(const std::string &identifier)
{
    return (this->_games.at(name));
}

std::unordered_map<std::string, std::unique_ptr<BattleRoyale::Game>> &BattleRoyale::getGames()
{
    return (this->_games);
}

void BattleRoyale::updateGames()
{
    for (auto &[identifier, game] : this->_games) {
        switch (game->getStatus())
        {
        case BattleRoyale::Game::Waiting: // game waiting for players to be ready
            game->begin();
            break;
        case BattleRoyale::Game::Beginning: // game starting unless a player is not ready anymore
            game->start();
            break;
        case BattleRoyale::Game::Running: // game running, waiting for the last player
            game->finish();
            break;
        case BattleRoyale::Game::Finished: // last player standing, anouncing victory
            game->close();
            break;
        case BattleRoyale::Game::Closed: // game closed, destroy it
            this->_games.erase(identifier);
            break;
        case BattleRoyale::Game::Interrupted: // game interrupted, destroy it
            this->_games.erase(identifier);
            break;
        }
    }
}
