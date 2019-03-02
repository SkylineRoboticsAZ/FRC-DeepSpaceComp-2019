#pragma once

#include "subsystems/SubsystemBase.hpp"


namespace skyline
{
namespace subsystems
{

/**
 * A base class for a  drive train with left and right side motors
 * that operate in a percentage power control mode
 */
class DriveTrainBase : public SubsystemBase
{
public:
    DriveTrainBase(const wpi::Twine &name = "DriveTrain");
    virtual ~DriveTrainBase() {}
    void InitDefaultCommand() override {}

    virtual void setLeftPower(double percentPower) = 0;
    virtual void setRightPower(double percentPower) = 0;
};

}
}
