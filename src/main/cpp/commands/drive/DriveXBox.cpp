#include "commands/drive/DriveXBox.hpp"

#include "controls/DriverStation.hpp"

#include <iostream>

namespace skyline
{

namespace commands
{

DriveXBox::DriveXBox(subsystems::SimpleDriveTrain *driveTrain, const Config &config) :
mDriveTrain(driveTrain), mConfig(config)
{
    Requires(driveTrain);
}

void DriveXBox::Initialize()
{
}

void DriveXBox::Execute()
{
    using controls::DriverStation;
    double throttle = DriverStation::getInstance().readDouble(mConfig.throttle);
    double turnFactor = DriverStation::getInstance().readDouble(mConfig.turnFactor);

    mDriveTrain->setLeftPower(throttle + turnFactor);
    mDriveTrain->setRightPower(throttle - turnFactor);
}

bool DriveXBox::IsFinished()
{
    return false;
}

void DriveXBox::End()
{

}

void DriveXBox::Interrupted()
{

}

}

}