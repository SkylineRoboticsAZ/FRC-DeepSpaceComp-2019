#pragma once

#include "triggers/TriggerBase.hpp"

#include <memory>


namespace frc
{

class Command;

}

namespace skyline
{

namespace controls
{

enum class Input : unsigned int;

}

using controls::Input;

namespace triggers
{

class JoystickTrigger : public TriggerBase
{
public:
    typedef std::shared_ptr<frc::Command> CommandPtr;

    JoystickTrigger(Input input);
    ~JoystickTrigger();

    bool Get() override;

private:
    const Input mInput;
};

}

}