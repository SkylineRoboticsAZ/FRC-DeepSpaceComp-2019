/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <vector>


namespace skyline
{
namespace constants
{
    namespace ports
    {
        const int driveJoystick = 0;

        const std::vector<int> leftDriveMotors({});
        const std::vector<int> rightDriveMotors({8, 9});
        const std::vector<int> elevatorMotors({4, 5});
    }
}
}
