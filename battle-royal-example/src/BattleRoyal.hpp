#ifndef PLUGIN_HPP_
#define PLUGIN_HPP_

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <ctime>

static const char identifier[] = "battleroyale";
static const char version[] = "1.0.0";
static const char name[] = "Battle Royale";

class BattleRoyale {
public:
    class Game {
    public:
        enum Status {
            Waiting = 1,
            Beginning = 2,
            Running = 3,
            Finished = 4,
            Closed = 0,
            Interrupted = -1
        };

    public:
        Game(const std::string &identifier, size_t maxPlayers);
        ~Game();

        // game identifier is the plugin identifier "battleroyale" + the room number
        const std::string &getIdentifier();

        // status fonctions, called according to the game's status
        void begin(void);
        void start(void);
        void finish(void);
        void close(void);

        // interrupt function, stops the game forcefully
        void interrupt(void);

        // add players
        void addPlayer(const std::string &player);
        void addSpectator(const std::string &spectator);

        // players 
        void playerLeave(const std::string &player);
        void playerDied(const std::string &player);

        const Status &getStatus(void) const noexcept;
    
        size_t getMaxPlayerNumber(void) const noexcept;
        size_t getPlayerNumber(void) const noexcept;
        void setMaxPlayerNumber(size_t nbr) noexcept;

        // set a player as ready, begin the game when all players are ready
        void setReady(const std::string &name, bool ready);

    private:
        const std::string _identifier;
        Status _status;
        size_t _maxPlayers;
        std::unordered_set<std::string> _players;
        std::unordered_set<std::string> _spectators;
        std::unordered_set<std::string> _readyPlayers;
        std::time_t _timestamp;
    };

public:
    BattleRoyale(size_t defaultMaxPlayers = 10);
    ~BattleRoyale() = default;

    static BattleRoyale &getInstance() {
        static BattleRoyale instance;

        return instance;
    }

    // add players to a game
    std::unique_ptr<BattleRoyale::Game> &join(const std::string &player);
    std::unique_ptr<BattleRoyale::Game> &join(const std::string &player, std::unique_ptr<BattleRoyale::Game> &game);
    std::unique_ptr<BattleRoyale::Game> &joinAsSpectator(const std::string &player, std::unique_ptr<BattleRoyale::Game> &game);
    
    // game creating and destroying
    std::unique_ptr<Game> &addGame();
    std::unique_ptr<Game> &addGame(size_t maxPlayers);
    void closeGame(const std::string &game);
    void closeGames(void);
    void forceCloseGames(void);

    bool hasGame(const std::string &identifier);
    std::unique_ptr<Game> &getGame(const std::string &identifier);
    std::unordered_map<std::string, std::unique_ptr<Game>> &getGames();
    void updateGames();

private:
    size_t _defaultMaxPlayers;
    std::unordered_map<std::string, std::unique_ptr<Game>> _games;
};

#endif // PLUGIN_HPP_
