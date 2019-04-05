#pragma once

#include <memory>

#include <frc/commands/subsystem.h>
#include <frc/commands/command.h>


namespace skyline
{
namespace subsystems
{

class SubsystemBase : public frc::Subsystem
{
public:
    SubsystemBase(const wpi::Twine &name);
    virtual ~SubsystemBase() {}

    virtual void InitDefaultCommand() {};
    void SetDefaultCommand(std::shared_ptr<frc::Command> command);
private:
    std::shared_ptr<frc::Command> mDefaultCommand;
};

}
}