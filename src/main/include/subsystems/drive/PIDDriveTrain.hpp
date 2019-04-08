/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "subsystems/drive/DriveTrainBase.hpp"

#include <memory>


namespace skyline
{

class IPIDMotorController;

namespace subsystems
{

/**
 * An advanced drive train which utilizes PID motor controllers
 * to move using velocity instead of percent voltage
 */
class PIDDriveTrain : public DriveTrainBase
{
public:
    typedef std::unique_ptr<IPIDMotorController> Motor;

    PIDDriveTrain(Motor leftMotor, Motor rightMotor, 
        double maxVelocity, const wpi::Twine &name = "PIDDriveTrain");
    ~PIDDriveTrain();

    enum class Mode
    {
        PercentPower, Velocity
    };

    void setMode(Mode mode);

    void setLeftPower(double percentPower) override;
    void setRightPower(double percentPower) override;

    Mode mode() const;
    double velocityTarget() const;
    double sensorVelocity() const;

    double leftVelocity() const;
    double rightVelocity() const;

private:
    Mode mMode = Mode::PercentPower;
    Motor mLeftMotor, mRightMotor;
    const double mMaxVelocity;
    double mLeftTarget = 0, 
           mRightTarget = 0;
};

}
}
