#include "triggers/JoystickTrigger.hpp"

#include "controls/DriverStation.hpp"

#include <frc/commands/Command.h>


namespace skyline
{

namespace triggers
{

JoystickTrigger::JoystickTrigger(Input input) : mInput(input) {}
JoystickTrigger::~JoystickTrigger() {}

bool JoystickTrigger::Get()
{
    using controls::DriverStation;
    return DriverStation::getInstance().readDouble(mInput) != 0;
}

}

}