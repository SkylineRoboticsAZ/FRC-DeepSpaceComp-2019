#include "subsystems/SubsystemBase.hpp"

#include <frc/commands/command.h>


namespace skyline
{

namespace subsystems
{

SubsystemBase::SubsystemBase(const wpi::Twine &name) : frc::Subsystem(name)
{
}

void SubsystemBase::SetDefaultCommand(std::unique_ptr<frc::Command> command)
{
    mDefaultCommand = std::move(command);
    frc::Subsystem::SetDefaultCommand(mDefaultCommand.get());
}

}

}