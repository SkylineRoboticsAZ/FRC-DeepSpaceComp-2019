#pragma once

#include "controls/Inputs.hpp"

#include <frc/commands/Command.h>


namespace skyline
{

namespace subsystems
{

class ActuatorBase;

}

namespace commands
{

class ActuateJoystick : public frc::Command 
{
public:
    struct Config
    {
        controls::Input input;
    };

    typedef subsystems::ActuatorBase ActuatorBase;

    ActuateJoystick(ActuatorBase *actuator, const Config &config);

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;

private:
    const Config mConfig;
    ActuatorBase *mActuator;
};

}

}
