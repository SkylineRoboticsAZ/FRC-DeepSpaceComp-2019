#include "subsystems/SubsystemBase.hpp"

#include <frc/commands/command.h>


namespace skyline
{

namespace subsystems
{

SubsystemBase::SubsystemBase(const wpi::Twine &name) : frc::Subsystem(name)
{
}

void SubsystemBase::SetDefaultCommand(std::shared_ptr<frc::Command> command)
{
    mDefaultCommand = command;
    frc::Subsystem::SetDefaultCommand(mDefaultCommand.get());
}

}

}