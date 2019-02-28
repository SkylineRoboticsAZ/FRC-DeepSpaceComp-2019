#include "init/TriggerInit.hpp"

#include "Robot.hpp"
#include "subsystems/Subsystems.hpp"
#include "subsystems/Elevator.hpp"

#include "commands/SetElevatorPosition.hpp"
#include "commands/ActuateJoystick.hpp"
#include "commands/SetElevatorPosition.hpp"

#include "controls/Inputs.hpp"

#include "triggers/BoolTrigger.hpp"
#include "triggers/JoystickTrigger.hpp"

#include <frc/buttons/Trigger.h>
#include <frc/commands/InstantCommand.h>


namespace skyline
{
namespace triggers
{

typedef std::unique_ptr<BoolTrigger> BoolTriggerPtr;
typedef std::unique_ptr<JoystickTrigger> JoystickTriggerPtr;

bool kHasRunInit = false;
std::vector<TriggerPtr> kTriggers;

void initTriggers()
{
    if (kHasRunInit)
        return;

    kHasRunInit = true;

    using subsystems::Elevator;
    using subsystems::Subsystem;
    using commands::SetElevatorPosition;

    Elevator *elevator = 
        static_cast<Elevator*>(Robot::getSubsystem(Subsystem::Elevator));

    if (elevator)
    {
        BoolTriggerPtr elevatorBottom = std::make_unique<BoolTrigger>(Input::elevatorBottom);
        elevatorBottom->WhenActive(std::make_unique<SetElevatorPosition>(elevator, Elevator::Position::Bottom));

        BoolTriggerPtr elevatorDiskBottom = std::make_unique<BoolTrigger>(Input::elevatorDiskBottom);
        elevatorDiskBottom->WhenActive(std::make_unique<SetElevatorPosition>(elevator, Elevator::Position::DiskBottom));

        BoolTriggerPtr elevatorBallBottom = std::make_unique<BoolTrigger>(Input::elevatorBallBottom);
        elevatorBallBottom->WhenActive(std::make_unique<SetElevatorPosition>(elevator, Elevator::Position::BallBottom));

        BoolTriggerPtr elevatorDiskMiddle = std::make_unique<BoolTrigger>(Input::elevatorDiskMiddle);
        elevatorDiskMiddle->WhenActive(std::make_unique<SetElevatorPosition>(elevator, Elevator::Position::DiskMiddle));

        BoolTriggerPtr elevatorBallMiddle = std::make_unique<BoolTrigger>(Input::elevatorBallMiddle);
        elevatorBallMiddle->WhenActive(std::make_unique<SetElevatorPosition>(elevator, Elevator::Position::BallMiddle));

        BoolTriggerPtr elevatorDiskTop = std::make_unique<BoolTrigger>(Input::elevatorDiskTop);
        elevatorDiskTop->WhenActive(std::make_unique<SetElevatorPosition>(elevator, Elevator::Position::DiskTop));
        
        BoolTriggerPtr elevatorBallTop = std::make_unique<BoolTrigger>(Input::elevatorBallTop);
        elevatorBallTop->WhenActive(std::make_unique<SetElevatorPosition>(elevator, Elevator::Position::BallTop));

        kTriggers.push_back(std::move(elevatorBottom));
        kTriggers.push_back(std::move(elevatorDiskBottom));
        kTriggers.push_back(std::move(elevatorBallBottom));
        kTriggers.push_back(std::move(elevatorDiskMiddle));
        kTriggers.push_back(std::move(elevatorBallMiddle));
        kTriggers.push_back(std::move(elevatorDiskTop));
        kTriggers.push_back(std::move(elevatorBallTop));
    }

    kTriggers.shrink_to_fit();
}

}
}