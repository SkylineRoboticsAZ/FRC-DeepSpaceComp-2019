#pragma once

#include "controls/Inputs.hpp"
#include "subsystems/Subsystems.hpp"
#include "subsystems/drive/DriveTrainBase.hpp"

#include <frc/commands/Command.h>


namespace skyline
{
namespace commands
{

class DriveXBox : public frc::Command 
{
public:
    struct Config
    {
        controls::Input throttle = controls::Input::throttle;
        controls::Input turnFactor = controls::Input::turnFactor;
    };

    DriveXBox(subsystems::DriveTrainBase *driveTrain, const Config &config);

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;

private:
    const Config mConfig;
    subsystems::DriveTrainBase *mDriveTrain;
};

}
}
