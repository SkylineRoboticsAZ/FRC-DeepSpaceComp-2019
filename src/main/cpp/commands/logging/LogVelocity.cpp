#include "commands/logging/LogVelocity.hpp"

#include "subsystems/drive/PIDDriveTrain.hpp"

#include <iostream>


namespace skyline
{
namespace commands
{

LogVelocity::LogVelocity(PIDDriveTrain *driveTrain, const std::string &fileName) :
mDriveTrain(driveTrain), mFileName(fileName) {}

// Called just before this Command runs the first time
void LogVelocity::Initialize() 
{
    try {
        remove(mFileName.c_str());
        mFile.open(mFileName, std::fstream::out);
    } catch (...) {
        std::cout << "Error opening: " << mFileName << " for velocity log!" << std::endl;
        Cancel();
    }
}

// Called repeatedly when this Command is scheduled to run
void LogVelocity::Execute() 
{
    if (mFile.is_open())
        mFile << mDriveTrain->leftVelocity() << ',' << mDriveTrain->rightVelocity() << std::endl;
}

// Make this return true when this Command no longer needs to run execute()
bool LogVelocity::IsFinished() { return false; }

// Called once after isFinished returns true
void LogVelocity::End() 
{
    try {
        mFile.close();
    } catch (...) {
        std::cout << "Error closing: " << mFileName << " for velocity log!" << std::endl;
    }
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LogVelocity::Interrupted() { End(); }

}
}