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
    enum Status {
        Waiting = 1,
        Beginning = 2,
        Running = 3,
        Finished = 4,
        Closed = 0,
        Interrupted = -1
    };

public:
    BattleRoyale() = default;
    ~BattleRoyale() = default;

    static BattleRoyale &getInstance();

    bool isPlaying(const std::string &name) const noexcept;
    bool isSpectating(const std::string &name) const noexcept;

    void join(const std::string &name);
    void spectate(const std::string &name);

    void playerLeft(const std::string &player);
    void playerDied(const std::string &player);

    void begin();
    void start();
    void finish();
    void close();

    void interrupt() noexcept;

    Status getStatus() const noexcept;

    void setReady(const std::string &name, bool ready);

    void update();

private:
    std::unordered_set<std::string> _players;
    std::unordered_set<std::string> _readyPlayers;
    Status _status;
    std::time_t _timestamp;
};

#endif // PLUGIN_HPP_
