#include "triggers/TriggerBase.hpp"

#include <frc/commands/Command.h>


namespace skyline
{
namespace triggers
{

TriggerBase::TriggerBase() {}
TriggerBase::~TriggerBase() {}

void TriggerBase::WhenActive(CommandPtr command)
{
    Trigger::WhenActive(command.get());
    mWhenActiveCommands.push_back(std::move(command));
}

void TriggerBase::WhileActive(CommandPtr command)
{
    Trigger::WhileActive(command.get());
    mWhileActiveCommands.push_back(std::move(command));
}

void TriggerBase::WhenInactive(CommandPtr command)
{
    Trigger::WhenInactive(command.get());
    mWhenInactiveCommands.push_back(std::move(command));
}

void TriggerBase::CancelWhenActive(CommandPtr command)
{
    Trigger::CancelWhenActive(command.get());
    mCancelWhenActiveCommands.push_back(std::move(command));
}

void TriggerBase::ToggleWhenActive(CommandPtr command)
{
    Trigger::ToggleWhenActive(command.get());
    mToggleWhenActiveCommands.push_back(std::move(command));
}

}
}