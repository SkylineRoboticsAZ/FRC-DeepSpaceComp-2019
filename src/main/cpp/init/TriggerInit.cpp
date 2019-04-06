#include "init/TriggerInit.hpp"

#include "Robot.hpp"
#include "RobotMap.hpp"
#include "subsystems/Subsystems.hpp"
#include "subsystems/Elevator.hpp"
#include "subsystems/actuators/PIDActuator.hpp"
#include "subsystems/actuators/SimpleActuator.hpp"

#include "commands/auto/MoveActuatorPastPosition.hpp"
#include "commands/SetElevatorPosition.hpp"
#include "commands/ActuateJoystick.hpp"
#include "commands/CommandGroup.hpp"
#include "commands/SetSoftLimitsEnabled.hpp"

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
    using subsystems::PIDActuator;
    using subsystems::SimpleActuator;
    using commands::SetElevatorPosition;
    using commands::MoveActuatorPastPosition;
    using commands::SetSoftLimitsEnabled;
    using commands::ActuateJoystick;
    using commands::CommandGroup;

    Elevator *elevator = 
        static_cast<Elevator*>(Robot::getSubsystem(Subsystem::Elevator));

    PIDActuator *ballPickupPivot = 
        static_cast<PIDActuator*>(Robot::getSubsystem(Subsystem::BallPickupPivot));

    SimpleActuator *hatchHook =
        static_cast<SimpleActuator*>(Robot::getSubsystem(Subsystem::HatchHook));

    if (elevator)
    {
        typedef Elevator::Position Position;
        const Position positions[] = {Position::Bottom, Position::DiskBottom, 
            Position::BallBottom, Position::DiskMiddle, Position::BallMiddle, 
            Position::DiskTop, Position::BallTop};

        std::vector<std::shared_ptr<CommandGroup>> commands;
        for (int i = 0; i < 7; i++)
            commands.push_back(std::make_shared<CommandGroup>("ElevatorCommandGroup"));

        std::shared_ptr<CommandGroup> elevatorManualControlCommand =
            std::make_shared<CommandGroup>("ElevatorManualControl");

        // If the ballPickupPivot mechanism is present insert code for
        // kicking out the front arm before the elevator moves
        if (ballPickupPivot)
        {
            typedef MoveActuatorPastPosition::Mode PastPositionMode;

            for (std::shared_ptr<CommandGroup> &group : commands)
                group->AddSequential(std::make_shared<MoveActuatorPastPosition>
                (ballPickupPivot, constants::ballPickupPivot::kickoutPosition,
                 PastPositionMode::GreaterThanTarget));

            elevatorManualControlCommand->AddSequential(std::make_shared<MoveActuatorPastPosition>
                (ballPickupPivot, constants::ballPickupPivot::kickoutPosition,
                 PastPositionMode::GreaterThanTarget));

            BoolTriggerPtr disableLimits = 
                std::make_unique<BoolTrigger>(Input::ballPickupPivotDisableLimits);

            typedef SetSoftLimitsEnabled::Mode SoftLimitMode;

            disableLimits->WhenActive(std::make_shared<SetSoftLimitsEnabled>(
                ballPickupPivot, SoftLimitMode::Forward, false));
            disableLimits->WhenInactive(std::make_shared<SetSoftLimitsEnabled>(
                ballPickupPivot, SoftLimitMode::Forward, true));

            kTriggers.push_back(std::move(disableLimits));
        }

        for (int i = 0; i < 7; i++)
            commands[i]->AddSequential(
                std::make_shared<SetElevatorPosition>(elevator, positions[i]));

        const Input inputs[] = {Input::elevatorBottom, Input::elevatorDiskBottom, 
            Input::elevatorBallBottom, Input::elevatorDiskMiddle, 
            Input::elevatorBallMiddle, Input::elevatorDiskTop, 
            Input::elevatorBallTop};

        std::vector<BoolTriggerPtr> elevatorTriggers;

        for (int i = 0; i < 7; i++) {
            BoolTriggerPtr trigger = std::make_unique<BoolTrigger>(inputs[i]);
            trigger->WhenActive(commands[i]);
            kTriggers.push_back(std::move(trigger));
        }

        ActuateJoystick::Config elevatorActuateJoystickConfig;
        elevatorActuateJoystickConfig.input = Input::elevator;

        elevatorManualControlCommand->AddSequential(
            std::make_shared<ActuateJoystick>(elevator, 
            elevatorActuateJoystickConfig));

        JoystickTriggerPtr elevatorManualControlTrigger = 
            std::make_unique<JoystickTrigger>(Input::elevator);

        elevatorManualControlTrigger->WhileActive(elevatorManualControlCommand);

        kTriggers.push_back(std::move(elevatorManualControlTrigger));
    }

    if (hatchHook)
    {
        ActuateJoystick::Config actuateJoystickConfig;
        actuateJoystickConfig.input = Input::hatchHook;

        BoolTriggerPtr trigger = std::make_unique<BoolTrigger>(Input::hatchHookTrigger);
        trigger->ToggleWhenActive(std::make_shared<ActuateJoystick>(hatchHook, actuateJoystickConfig));

        kTriggers.push_back(std::move(trigger));
    }

    kTriggers.shrink_to_fit();
}

}
}