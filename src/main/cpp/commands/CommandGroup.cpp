#include "commands/CommandGroup.hpp"


namespace skyline
{
namespace commands
{

CommandGroup::CommandGroup(const wpi::Twine &name) : frc::CommandGroup(name) {}

void CommandGroup::AddSequential(CommandPtr command)
{
    frc::CommandGroup::AddSequential(command.get());
    mCommands.push_back(std::move(command));
}

void CommandGroup::AddSequential(CommandPtr command, double timeout)
{
    frc::CommandGroup::AddSequential(command.get(), timeout);
    mCommands.push_back(std::move(command));
}

void CommandGroup::AddParallel(CommandPtr command)
{
    frc::CommandGroup::AddParallel(command.get());
    mCommands.push_back(std::move(command));
}

void CommandGroup::AddParallel(CommandPtr command, double timeout)
{
    frc::CommandGroup::AddParallel(command.get(), timeout);
    mCommands.push_back(std::move(command));
}

}
}