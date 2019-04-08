#pragma once

#include "controls/Inputs.hpp"

#include <frc/commands/Command.h>
#include <fstream>


namespace skyline
{

namespace subsystems
{

class PIDDriveTrain;

}

namespace commands
{

class LogVelocity : public frc::Command 
{
public:
    typedef subsystems::PIDDriveTrain PIDDriveTrain;

    LogVelocity(PIDDriveTrain *driveTrain, const std::string &fileName);

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;

private:
    PIDDriveTrain *mDriveTrain;
    const std::string mFileName;
    std::fstream mFile;
};

}

}
