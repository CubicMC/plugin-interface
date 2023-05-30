#ifndef PLUGIN_HPP_
#define PLUGIN_HPP_

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <ctime>

class Player;

static const char identifier[] = "battleroyale";
static const char version[] = "1.0.0";
static const char name[] = "Battle Royale";

class BattleRoyale {
public:
    enum Status {
        Waiting = 1,
        Beginning = 2,
        Running = 3,
        Finished = 4,
        Closed = 0,
        Interrupted = -1
    };

    struct Challenger {
        Challenger(Player &player);
        ~Challenger() = default;

        Player &player;
        bool ready;

        Challenger &operator=(const Challenger &other);
    };

public:
    BattleRoyale() = default;
    ~BattleRoyale() = default;

    static BattleRoyale &getInstance();

    bool isPlaying(const std::string &name) const noexcept;
    bool isSpectating(const std::string &name) const noexcept;

    void join(Player &player);
    void spectate(Player &player);

    void playerLeft(Player &player);
    void playerDied(Player &player);

    void begin();
    void start();
    void finish();
    void close();

    void interrupt() noexcept;

    Status getStatus() const noexcept;

    void setReady(Player &player, bool ready);

    void update();

private:
    std::unordered_map<std::string, std::unique_ptr<Challenger>> _players;
    std::unordered_set<std::string> _readyPlayers;
    Status _status;
    std::time_t _timestamp;
};

#endif // PLUGIN_HPP_
