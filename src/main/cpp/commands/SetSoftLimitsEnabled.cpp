#include "commands/SetSoftLimitsEnabled.hpp"

#include "subsystems/actuators/PIDActuator.hpp"

namespace skyline
{
namespace commands
{

SetSoftLimitsEnabled::SetSoftLimitsEnabled(PIDActuator *actuator, Mode mode, bool isEnabled) :
mActuator(actuator), mMode(mode), mIsEnabled(isEnabled)
{
    Requires(mActuator);
}

// Called just before this Command runs the first time
void SetSoftLimitsEnabled::Initialize() 
{
    switch (mMode) {
        case Mode::Forward:
            mActuator->setForwardSoftLimitEnabled(mIsEnabled);
            break;
        case Mode::Reverse:
            mActuator->setReverseSoftLimitEnabled(mIsEnabled);
            break;
        case Mode::Both:
            mActuator->setForwardSoftLimitEnabled(mIsEnabled);
            mActuator->setReverseSoftLimitEnabled(mIsEnabled);
            break;
    }
}

// Called repeatedly when this Command is scheduled to run
void SetSoftLimitsEnabled::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool SetSoftLimitsEnabled::IsFinished() { return true; }

// Called once after isFinished returns true
void SetSoftLimitsEnabled::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetSoftLimitsEnabled::Interrupted() {}

}
}