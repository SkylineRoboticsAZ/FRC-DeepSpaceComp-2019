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
        const int auxJoystick = 1;

        const std::vector<int> ballPivotMotors({4});
        const std::vector<int> ballRollerMotors({5});
        const std::vector<int> leftDriveMotors({7, 8, 9});//{4, 5});
        const std::vector<int> rightDriveMotors({10, 11, 12});//{8, 9});
        const std::vector<int> elevatorMotors({2, 3});
    }
}
}
