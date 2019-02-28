/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/drive/SimpleDriveTrain.hpp"
#include "components/motor_controllers/IBasicMotorController.hpp"


namespace skyline
{

namespace subsystems
{

class SimpleDriveTrain::Impl
{
public:
    Impl(Motor leftSide, Motor rightSide) : 
    mLeftSide(std::move(leftSide)), mRightSide(std::move(rightSide)) {}

    Motor mLeftSide, mRightSide;
};

SimpleDriveTrain::SimpleDriveTrain(Motor leftSide, Motor rightSide) : 
SubsystemBase("SimpleDriveTrain"), mImpl(std::make_unique<Impl>(std::move(leftSide), std::move(rightSide))) 
{}

SimpleDriveTrain::~SimpleDriveTrain() {}

void SimpleDriveTrain::InitDefaultCommand() 
{
}

void SimpleDriveTrain::setLeftPower(double percentPower) 
{
    mImpl->mLeftSide->setPower(percentPower);
}

void SimpleDriveTrain::setRightPower(double percentPower) 
{
    mImpl->mRightSide->setPower(percentPower);
}

}

}