#pragma once

#include "subsystems/Elevator.hpp"

#include <frc/commands/Command.h>


namespace skyline
{

namespace commands
{

class SetElevatorPosition : public frc::Command
{
public:
    typedef subsystems::Elevator Elevator;
    SetElevatorPosition(Elevator *elevator, Elevator::Position position);

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;

private:
    Elevator *mElevator;
    const Elevator::Position mPosition;
};

}

}
