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
        IBasicMotorPtr leftMotor = adaptMotor(
            createTalonSRXGroup(leftDriveMotors, false, NeutralMode::Coast));
        IBasicMotorPtr rightMotor = adaptMotor(
            createTalonSRXGroup(rightDriveMotors, true, NeutralMode::Coast));

        std::shared_ptr<frc::Encoder> leftEncoder =
            std::make_shared<frc::Encoder>(0, 1, true, 
            frc::Encoder::EncodingType::k1X);

        leftEncoder->SetDistancePerPulse(1.0/360);

        std::shared_ptr<IPIDSensor> leftPidEncoder = 
            std::make_shared<PIDEncoder>(leftEncoder);

        IPIDMotorPtr leftPidMotor = 
            std::make_unique<PIDMotorControllerAdapter>(
                std::move(leftMotor), leftPidEncoder);
        leftPidMotor->setAcceptableError(.1);
        leftPidMotor->setF(0.349065850399);

        std::shared_ptr<frc::Encoder> rightEncoder =
            std::make_shared<frc::Encoder>(2, 3, false, 
            frc::Encoder::EncodingType::k1X);

        rightEncoder->SetDistancePerPulse(1.0/360);

        std::shared_ptr<IPIDSensor> rightPidEncoder = 
            std::make_shared<PIDEncoder>(rightEncoder);

        IPIDMotorPtr rightPidMotor = 
            std::make_unique<PIDMotorControllerAdapter>(
                std::move(rightMotor), rightPidEncoder);
        rightPidMotor->setAcceptableError(.1);
        rightPidMotor->setF(.349065850399);

        std::unique_ptr<PIDDriveTrain> driveTrain = 
            std::make_unique<PIDDriveTrain>(
                std::move(leftPidMotor), std::move(rightPidMotor), 2.846);

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
        config.peakOutputForward = .5;
        config.peakOutputReverse = -.5;

        motor->ConfigAllSettings(config);
        motor->SelectProfileSlot(0, 0);
        motor->SetSensorPhase(true);

        IPIDMotorPtr pidMotor = adaptMotor(std::move(motor), 360);

        pidMotor->setAcceptableError(.1);
        pidMotor->setPIDMaxForwardOutput(.5);
        pidMotor->setPIDMaxReverseOutput(.5);
        pidMotor->setP(1);
        pidMotor->setD(50);

        Elevator::Positions positions;
        positions[Elevator::Position::Bottom] = 0;
        positions[Elevator::Position::DiskBottom] = -8.47778;
        positions[Elevator::Position::BallBottom] = -1.71111;
        positions[Elevator::Position::DiskMiddle] = -28.2417;
        positions[Elevator::Position::BallMiddle] = -20.2944;
        positions[Elevator::Position::DiskTop] = -44.0611;
        positions[Elevator::Position::BallTop] = -40.3917;

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
        createTalonSRXGroup(ballPivotMotors, true, NeutralMode::Brake);

    if (rollerMotor) {
        rollerMotor->ConfigPeakOutputForward(.3);
        rollerMotor->ConfigPeakOutputReverse(-.3);

        std::unique_ptr<subsystems::SimpleActuator> actuator = 
            std::make_unique<subsystems::SimpleActuator>
            (adaptMotor(std::move(rollerMotor)), "BallPickupPivot");

        commands::ActuateJoystick::Config actuatorConfig;
        actuatorConfig.input = Input::ballPickupPivot;

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
        actuatorConfig.input = Input::ballPickupRollers;

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