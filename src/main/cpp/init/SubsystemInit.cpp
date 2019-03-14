#include "RobotMap.hpp"

#include "init/SubsystemInit.hpp"

#include "commands/drive/DriveXBox.hpp"
#include "commands/ActuateJoystick.hpp"
#include "commands/CommandGroup.hpp"
#include "commands/dashboard/PIDDriveSpeedometer.hpp"

#include "subsystems/drive/PIDDriveTrain.hpp"
#include "subsystems/Elevator.hpp"
#include "subsystems/actuators/SimpleActuator.hpp"

#include "components/sensors/PIDEncoder.hpp"

#include "components/motor_controllers/IBasicMotorController.hpp"
#include "components/motor_controllers/groups/FollowableTalonSRX.hpp"
#include "components/motor_controllers/adapters/CtreMotorControllerAdapter.hpp"
#include "components/motor_controllers/adapters/WpiMotorControllerAdapter.hpp"
#include "components/motor_controllers/adapters/PIDMotorControllerAdapter.hpp"


namespace skyline
{
namespace subsystems
{

using controls::Input;
using skyline::adaptMotor;
using ctre::phoenix::motorcontrol::can::SlotConfiguration;
using ctre::phoenix::motorcontrol::can::TalonSRXConfiguration;
using ctre::phoenix::motorcontrol::IMotorController;

typedef std::unique_ptr<frc::Command> CommandPtr;
typedef std::unique_ptr<commands::CommandGroup> CommandGroupPtr;

SubsystemPtr initDriveTrain()
{
    using constants::ports::leftDriveMotors;
    using constants::ports::rightDriveMotors;

    if (leftDriveMotors.size() > 0 && rightDriveMotors.size() > 0) {
        TalonSRXPtr leftMotor = createTalonSRXGroup(leftDriveMotors, false, NeutralMode::Coast);
        IBasicMotorPtr rightMotor = adaptMotor(
            createTalonSRXGroup(rightDriveMotors, true, NeutralMode::Coast));

        TalonSRXConfiguration config;
        using ctre::phoenix::motorcontrol::VelocityMeasPeriod;
        config.velocityMeasurementPeriod = VelocityMeasPeriod::Period_20Ms;
        config.velocityMeasurementWindow = 4;

        leftMotor->ConfigAllSettings(config);
        leftMotor->SelectProfileSlot(0, 0);
        leftMotor->SetSensorPhase(true);

        IPIDMotorPtr leftPidMotor = adaptMotor(std::move(leftMotor));
        leftPidMotor->setAcceptableError(10);
        leftPidMotor->setF(.000526315789474);

        std::shared_ptr<frc::Encoder> rightEncoder = 
            std::make_shared<frc::Encoder>(2, 3, false, 
            frc::Encoder::EncodingType::k1X);

        std::shared_ptr<IPIDSensor> rightPidEncoder = 
            std::make_shared<PIDEncoder>(rightEncoder);

        IPIDMotorPtr rightPidMotor = 
            std::make_unique<PIDMotorControllerAdapter>(
                std::move(rightMotor), rightPidEncoder);
        rightPidMotor->setAcceptableError(10);
        rightPidMotor->setF(.000526315789474);

        std::unique_ptr<PIDDriveTrain> driveTrain = 
            std::make_unique<PIDDriveTrain>(
                std::move(leftPidMotor), std::move(rightPidMotor), 1900);

        CommandGroupPtr group = 
            std::make_unique<commands::CommandGroup>("DriveTrainCommandGroup");

        group->AddParallel(std::make_unique<commands::DriveXBox>(
            driveTrain.get(), commands::DriveXBox::Config()));
        group->AddParallel(std::make_unique<commands::PIDDriveSpeedometer>(
            driveTrain.get()));

        driveTrain->SetDefaultCommand(std::move(group));

        return std::move(driveTrain);
    }

    return nullptr;
}

SubsystemPtr initElevator()
{
    using constants::ports::elevatorMotors;

    FollowableTalonSRXPtr motor = createTalonSRXGroup(elevatorMotors, false, NeutralMode::Brake);

    if (motor) {
        TalonSRXConfiguration config;
        using ctre::phoenix::motorcontrol::VelocityMeasPeriod;
        config.velocityMeasurementPeriod = VelocityMeasPeriod::Period_20Ms;
        config.velocityMeasurementWindow = 4;
        config.clearPositionOnLimitF = true;

        motor->ConfigAllSettings(config);
        motor->SelectProfileSlot(0, 0);
        motor->SetSensorPhase(true);

        std::shared_ptr<IPIDSensor> pidEncoder = 
            std::make_shared<PIDEncoder>(2, 3, true, 
                frc::Encoder::EncodingType::k1X);

        IPIDMotorPtr pidMotor = std::make_unique<PIDMotorControllerAdapter>(
            adaptMotor(std::move(motor), 360), pidEncoder);

        pidMotor->setAcceptableError(10);
        pidMotor->setPIDMaxForwardOutput(.3);
        pidMotor->setPIDMaxReverseOutput(.3);
        pidMotor->setP(1);

        Elevator::Positions positions;
        positions[Elevator::Position::Bottom] = 0;
        positions[Elevator::Position::DiskBottom] = 500;
        positions[Elevator::Position::BallBottom] = 1000;
        positions[Elevator::Position::DiskMiddle] = 1500;
        positions[Elevator::Position::BallMiddle] = 2000;
        positions[Elevator::Position::DiskTop] = 2500;
        positions[Elevator::Position::BallTop] = 3000;

        std::unique_ptr<Elevator> elevator = 
            std::make_unique<Elevator>(std::move(pidMotor), positions);

        elevator->setHoldPositionEnabled(true);

        commands::ActuateJoystick::Config actuatorConfig;
        actuatorConfig.input = Input::elevator;

        elevator->SetDefaultCommand(
            std::make_unique<commands::ActuateJoystick>(elevator.get(), actuatorConfig));

        return std::move(elevator);
    }

    return nullptr;
}

SubsystemPtr initBallPickupPivot()
{
    using constants::ports::ballPivotMotors;

    FollowableTalonSRXPtr rollerMotor = 
        createTalonSRXGroup(ballPivotMotors, false, NeutralMode::Brake);

    if (rollerMotor) {
        rollerMotor->ConfigPeakOutputForward(1);
        rollerMotor->ConfigPeakOutputReverse(-1);

        std::unique_ptr<subsystems::SimpleActuator> actuator = 
            std::make_unique<subsystems::SimpleActuator>
            (adaptMotor(std::move(rollerMotor)), "BallPickupPivot");

        commands::ActuateJoystick::Config actuatorConfig;
        actuatorConfig.input = Input::elevator;

        actuator->SetDefaultCommand(
            std::make_unique<commands::ActuateJoystick>(
                actuator.get(), actuatorConfig));

        return std::move(actuator);
    }

    return nullptr;
}

SubsystemPtr initBallPickupRollers()
{
    using constants::ports::ballRollerMotors;

    FollowableTalonSRXPtr rollerMotor = 
        createTalonSRXGroup(ballRollerMotors, false, NeutralMode::Brake);

    if (rollerMotor) {
        rollerMotor->ConfigPeakOutputForward(1);
        rollerMotor->ConfigPeakOutputReverse(-1);

        std::unique_ptr<subsystems::SimpleActuator> actuator = 
            std::make_unique<subsystems::SimpleActuator>
            (adaptMotor(std::move(rollerMotor)), "BallPickupRollers");

        commands::ActuateJoystick::Config actuatorConfig;
        actuatorConfig.input = Input::elevator;

        actuator->SetDefaultCommand(
            std::make_unique<commands::ActuateJoystick>(
                actuator.get(), actuatorConfig));

        return std::move(actuator);
    }

    return nullptr;
}

SubsystemMap initSubsystems()
{
    SubsystemMap subsystems;
    subsystems[Subsystem::DriveTrain] = initDriveTrain();
    subsystems[Subsystem::Elevator] = initElevator();
    subsystems[Subsystem::BallPickupPivot] = initBallPickupPivot();
    subsystems[Subsystem::BallPickupRollers] = initBallPickupRollers();
    return std::move(subsystems);
}

}
}