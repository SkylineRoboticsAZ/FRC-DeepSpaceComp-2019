#include "commands/auto/MoveActuatorPastPosition.hpp"

#include "subsystems/actuators/PIDActuator.hpp"


namespace skyline
{
namespace commands
{

MoveActuatorPastPosition::MoveActuatorPastPosition(subsystems::PIDActuator *actuator, 
        double position, Mode targetMode) : mActuator(actuator), mTarget(position),
        mTargetMode(targetMode)
{
    Requires(mActuator);
    SetInterruptible(false);
}

// Called just before this Command runs the first time
void MoveActuatorPastPosition::Initialize() 
{
    if (isAtTarget()) {
        mIsFinished = true;
    } else {
        mIsFinished = false;
        mActuator->setPosition(mTarget);
    }
}

// Called repeatedly when this Command is scheduled to run
void MoveActuatorPastPosition::Execute() 
{
    if (isAtTarget())
        mIsFinished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool MoveActuatorPastPosition::IsFinished() { return mIsFinished; }

// Called once after isFinished returns true
void MoveActuatorPastPosition::End() {
    mActuator->setPower(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveActuatorPastPosition::Interrupted() { End(); }

bool MoveActuatorPastPosition::isAtTarget() const
{
    switch (mTargetMode) {
        case Mode::LessThanTarget:
            return mActuator->position() <= mTarget + mActuator->acceptableError();
        case Mode::GreaterThanTarget:
            return mActuator->position() >= mTarget - mActuator->acceptableError();
    }
}

}
}