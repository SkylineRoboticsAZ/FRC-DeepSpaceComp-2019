/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <memory>
#include <unordered_map>

#include <frc/TimedRobot.h>

namespace frc
{

class Trigger;

}

namespace skyline
{

namespace subsystems
{

class SubsystemBase;
enum class Subsystem : unsigned int;

}

typedef std::unique_ptr<subsystems::SubsystemBase> SubsystemPtr;
typedef std::unique_ptr<frc::Trigger> TriggerPtr;

class Robot : public frc::TimedRobot
{
public:
    Robot();
    ~Robot();

    static subsystems::SubsystemBase *getSubsystem(subsystems::Subsystem subsystem);

    void RobotInit() override;
    void RobotPeriodic() override;
    void DisabledInit() override;
    void DisabledPeriodic() override;
    void AutonomousInit() override;
    void AutonomousPeriodic() override;
    void TeleopInit() override;
    void TeleopPeriodic() override;
    void TestPeriodic() override;

private:
    Robot(const Robot &other);
    const Robot &operator=(const Robot &other);

    void initControlAssignments();

    static std::unordered_map<subsystems::Subsystem, SubsystemPtr> kSubsystems;
};

}
