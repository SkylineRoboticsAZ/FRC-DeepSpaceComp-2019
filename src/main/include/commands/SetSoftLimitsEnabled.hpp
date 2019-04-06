#pragma once

#include "controls/Inputs.hpp"

#include <frc/commands/Command.h>


namespace skyline
{

namespace subsystems
{

class PIDActuator;

}

namespace commands
{

class SetSoftLimitsEnabled : public frc::Command 
{
public:
    typedef subsystems::PIDActuator PIDActuator;

    enum class Mode
    {
        Forward, Reverse, Both
    };

    SetSoftLimitsEnabled(PIDActuator *actuator, Mode mode, bool isEnabled);

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;

private:
    PIDActuator *mActuator;
    const Mode mMode;
    const bool mIsEnabled;
};

}
}
