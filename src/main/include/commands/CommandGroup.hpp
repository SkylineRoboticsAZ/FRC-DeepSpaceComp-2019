#pragma once

#include <frc/commands/CommandGroup.h>


namespace skyline
{
namespace commands
{

class CommandGroup : public frc::CommandGroup
{
public:
    typedef std::unique_ptr<frc::Command> CommandPtr;
    typedef std::vector<CommandPtr> CommandPtrList;

    CommandGroup(const wpi::Twine &name);

    void AddSequential(CommandPtr command);
    void AddSequential(CommandPtr command, double timeout);

    void AddParallel(CommandPtr command);
    void AddParallel(CommandPtr command, double timeout);

private:
    CommandPtrList mCommands;
};

}
}