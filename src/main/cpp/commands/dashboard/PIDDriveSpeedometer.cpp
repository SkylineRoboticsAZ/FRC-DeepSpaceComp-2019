#include "commands/dashboard/PIDDriveSpeedometer.hpp"

#include "subsystems/drive/PIDDriveTrain.hpp"

#include <frc/smartdashboard/SmartDashboard.h>


namespace skyline
{
namespace commands
{

PIDDriveSpeedometer::PIDDriveSpeedometer(
    const subsystems::PIDDriveTrain *driveTrain) : mDriveTrain(driveTrain) {}

// Called just before this Command runs the first time
void PIDDriveSpeedometer::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void PIDDriveSpeedometer::Execute() 
{
    std::string sensorVelocityKey = mDriveTrain->GetName();
    sensorVelocityKey += " Sensor Velocity ";

    frc::SmartDashboard::PutNumber(sensorVelocityKey, 
        mDriveTrain->sensorVelocity());

    std::string targetVelocityKey = mDriveTrain->GetName();
    targetVelocityKey += " Target Velocity ";

    frc::SmartDashboard::PutNumber(targetVelocityKey, 
        mDriveTrain->velocityTarget());
}

// Make this return true when this Command no longer needs to run execute()
bool PIDDriveSpeedometer::IsFinished() { return false; }

// Called once after isFinished returns true
void PIDDriveSpeedometer::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PIDDriveSpeedometer::Interrupted() {}

}
}
