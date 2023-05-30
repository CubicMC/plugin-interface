#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "command_parser/commands/CommandBase.hpp"

namespace command_parser {
struct Ready : public CommandBase {
    Ready():
        CommandBase("ready", "/ready", false)
    {
    }

    ~Ready() = default;

    void autocomplete(std::vector<std::string> &args, Player *invoker) const override;
    void execute(std::vector<std::string> &args, Player *invoker) const override;
    void help(std::vector<std::string> &args, Player *invoker) const override;
};

struct NotReady : public CommandBase {
    NotReady():
        CommandBase("notready", "/notready", false)
    {
    }

    ~NotReady() = default;

    void autocomplete(std::vector<std::string> &args, Player *invoker) const override;
    void execute(std::vector<std::string> &args, Player *invoker) const override;
    void help(std::vector<std::string> &args, Player *invoker) const override;
};

struct Interrupt : public CommandBase {
    Interrupt():
        CommandBase("interrupt", "/interrupt", true)
    {
    }

    ~Interrupt() = default;

    void autocomplete(std::vector<std::string> &args, Player *invoker) const override;
    void execute(std::vector<std::string> &args, Player *invoker) const override;
    void help(std::vector<std::string> &args, Player *invoker) const override;
};

}

#endif // CUBICSERVER_COMMANDPARSER_COMMANDS_STOP_HPP
