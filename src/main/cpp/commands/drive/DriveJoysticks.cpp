#include "commands/drive/DriveJoysticks.hpp"

#include "controls/DriverStation.hpp"


namespace skyline
{

namespace commands
{

DriveJoysticks::DriveJoysticks(subsystems::SimpleDriveTrain *driveTrain, const Config &config) :
mDriveTrain(driveTrain), mConfig(config)
{
    Requires(mDriveTrain);
}

// Called just before this Command runs the first time
void DriveJoysticks::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DriveJoysticks::Execute() 
{
    using controls::DriverStation;
    double leftValue = DriverStation::getInstance().readDouble(mConfig.leftDrive);
    double rightValue = DriverStation::getInstance().readDouble(mConfig.rightDrive);

    mDriveTrain->setLeftPower(leftValue);
    mDriveTrain->setRightPower(rightValue);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveJoysticks::IsFinished() { return false; }

// Called once after isFinished returns true
void DriveJoysticks::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveJoysticks::Interrupted() {}

}

}
