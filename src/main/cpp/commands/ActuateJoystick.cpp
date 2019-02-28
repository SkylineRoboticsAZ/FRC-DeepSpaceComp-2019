#include "commands/ActuateJoystick.hpp"

#include "controls/DriverStation.hpp"

#include "subsystems/actuators/ActuatorBase.hpp"


namespace skyline
{
namespace commands
{

ActuateJoystick::ActuateJoystick(ActuatorBase *actuator, const Config &config) :
mActuator(actuator), mConfig(config)
{
    Requires(mActuator);
}

// Called just before this Command runs the first time
void ActuateJoystick::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ActuateJoystick::Execute() 
{
    using controls::DriverStation;
    const double value = DriverStation::getInstance()
                        .readDouble(mConfig.input);
    mActuator->setPower(value);
}

// Make this return true when this Command no longer needs to run execute()
bool ActuateJoystick::IsFinished() { return false; }

// Called once after isFinished returns true
void ActuateJoystick::End() {
    mActuator->setPower(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ActuateJoystick::Interrupted() { End(); }

}
}