#include "triggers/BoolTrigger.hpp"

#include "controls/DriverStation.hpp"

#include <frc/commands/Command.h>

#include <iostream>


namespace skyline
{

namespace triggers
{

BoolTrigger::BoolTrigger(Input input, bool targetValue) :
mInput(input), mTargetValue(targetValue) {}

BoolTrigger::~BoolTrigger() {}

bool BoolTrigger::Get()
{
    using controls::DriverStation;
    return DriverStation::getInstance().readBoolean(mInput) == mTargetValue;
}

}

}