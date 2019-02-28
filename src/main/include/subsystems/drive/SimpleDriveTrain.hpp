/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "subsystems/SubsystemBase.hpp"

#include <memory>


namespace skyline
{

class IBasicMotorController;

namespace subsystems
{

/**
 * A simple drive train with left and right side motors
 * in a percentage power control mode
 */
class SimpleDriveTrain : public SubsystemBase
{
public:
    typedef std::unique_ptr<IBasicMotorController> Motor;

    SimpleDriveTrain(Motor leftSide, Motor rightSide);
    ~SimpleDriveTrain();
    void InitDefaultCommand() override;

    void setLeftPower(double percentPower);
    void setRightPower(double percentPower);

private:
    SimpleDriveTrain(const SimpleDriveTrain &other);
    const SimpleDriveTrain &operator=(const SimpleDriveTrain &other);

    class Impl;
    std::unique_ptr<Impl> mImpl;
};

}

}
