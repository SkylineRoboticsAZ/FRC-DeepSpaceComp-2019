/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "Subsystems.hpp"
#include "SubsystemBase.hpp"

#include <memory>


namespace frc
{

class Encoder;

}

namespace skyline
{

namespace subsystems
{

class IBasicMotorController;

/**
 * An advanced drive train which utilizes drive encoders to move
 * with improved consistency.
 */
class AdvancedDriveTrain : public SubsystemBase
{
public:
    typedef std::unique_ptr<IBasicMotorController> Motor;

    AdvancedDriveTrain(Motor leftMotor, Motor rightMotor, 
        frc::Encoder leftEncoder, frc::Encoder rightEncoder);
    ~AdvancedDriveTrain();
    void InitDefaultCommand() override;

    void setLeftPower(double percentPower);
    void setRightPower(double percentPower);

private:
    AdvancedDriveTrain(const AdvancedDriveTrain &other);
    const AdvancedDriveTrain &operator=(const AdvancedDriveTrain &other);

    class Impl;
    std::unique_ptr<Impl> mImpl;
};

}

}
