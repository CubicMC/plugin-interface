#include "Commands.hpp"

#include "Chat.hpp"
#include "Dimension.hpp"
#include "Player.hpp"
#include "Server.hpp"
#include "World.hpp"
#include "logging/logging.hpp"
#include "BattleRoyal.hpp"

void command_parser::Ready::autocomplete(UNUSED std::vector<std::string> &args, Player *invoker) const
{
    if (invoker)
        return;
    else
        LINFO("autocomplete ready");
}

void command_parser::Ready::execute(UNUSED std::vector<std::string> &args, Player *invoker) const
{
    if (invoker) {
        BattleRoyale::getInstance().setReady(invoker->getUsername(), true);
        invoker->getDimension()->getWorld()->getChat()->sendSystemMessage(invoker->getUsername() + " is ready !", *invoker->getWorldGroup());
    }
}

void command_parser::Ready::help(UNUSED std::vector<std::string> &args, Player *invoker) const
{
    if (invoker) {
        invoker->getDimension()->getWorld()->getChat()->sendSystemMessage("/notready", *invoker);
    } else
        LINFO("/ready");
}

void command_parser::NotReady::autocomplete(UNUSED std::vector<std::string> &args, Player *invoker) const
{
    if (invoker)
        return;
    else
        LINFO("autocomplete notready");
}

void command_parser::NotReady::execute(UNUSED std::vector<std::string> &args, Player *invoker) const
{
    if (invoker) {
        BattleRoyale::getInstance().setReady(invoker->getUsername(), false);
        invoker->getDimension()->getWorld()->getChat()->sendSystemMessage(invoker->getUsername() + " is not ready...", *invoker->getWorldGroup());
    }
}

void command_parser::NotReady::help(UNUSED std::vector<std::string> &args, Player *invoker) const
{
    if (invoker) {
        invoker->getDimension()->getWorld()->getChat()->sendSystemMessage("/notready", *invoker);
    } else
        LINFO("/notready");
}

void command_parser::Interrupt::autocomplete(UNUSED std::vector<std::string> &args, Player *invoker) const
{
    if (invoker)
        return;
    else
        LINFO("autocomplete interrupt");
}

void command_parser::Interrupt::execute(UNUSED std::vector<std::string> &args, Player *invoker) const
{
    if (invoker) {
        if (invoker->isOperator()) {
            invoker->getDimension()->getWorld()->getChat()->sendSystemMessage("Stopping server...", *invoker->getWorldGroup());
            Server::getInstance()->stop();
        }
    } else
        Server::getInstance()->stop();
}

void command_parser::Interrupt::help(UNUSED std::vector<std::string> &args, Player *invoker) const
{
    if (invoker) {
        invoker->getDimension()->getWorld()->getChat()->sendSystemMessage("/notready", *invoker);
    } else
        LINFO("/interrupt");
}
