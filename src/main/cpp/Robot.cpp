/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.hpp"

#include "init/SubsystemInit.hpp"
#include "init/TriggerInit.hpp"
#include "init/ControlInit.hpp"

#include "subsystems/Subsystems.hpp"
#include "subsystems/SubsystemBase.hpp"

#include "commands/Commands.hpp"

#include <frc/commands/Scheduler.h>
#include <frc/buttons/Trigger.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include <cameraserver/CameraServer.h>


#include <iostream>


namespace skyline
{

subsystems::SubsystemMap Robot::kSubsystems;

Robot::Robot() {}

Robot::~Robot() {}

subsystems::SubsystemBase *Robot::getSubsystem(subsystems::Subsystem subsystem)
{
    auto iterator = kSubsystems.find(subsystem);

    if (iterator != kSubsystems.end())
        return iterator->second.get();

    return nullptr;
}

void Robot::RobotInit()
{
    kSubsystems = subsystems::initSubsystems();
    triggers::initTriggers();
    controls::initControlBindings();

    frc::CameraServer::GetInstance()->StartAutomaticCapture(0).SetFPS(15);
    frc::CameraServer::GetInstance()->StartAutomaticCapture(1).SetFPS(15);
}

void Robot::RobotPeriodic()
{
}

void Robot::DisabledInit()
{
}

void Robot::DisabledPeriodic()
{
    frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit()
{
}

void Robot::AutonomousPeriodic()
{
    frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit()
{
}

void Robot::TeleopPeriodic()
{
    frc::Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic()
{
}

}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<skyline::Robot>(); }
#endif
