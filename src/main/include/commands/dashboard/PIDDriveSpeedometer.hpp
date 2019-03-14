#pragma once

#include <frc/commands/Command.h>


namespace skyline
{

namespace subsystems
{

class PIDDriveTrain;

}

namespace commands
{

class PIDDriveSpeedometer : public frc::Command
{
public:
    PIDDriveSpeedometer(const subsystems::PIDDriveTrain *driveTrain);

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;

private:
    const subsystems::PIDDriveTrain *mDriveTrain;
};

}
}
