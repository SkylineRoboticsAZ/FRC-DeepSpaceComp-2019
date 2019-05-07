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

typedef std::shared_ptr<frc::Command> CommandPtr;
typedef std::shared_ptr<commands::CommandGroup> CommandGroupPtr;

SubsystemPtr initDriveTrain()
{
    using constants::ports::leftDriveMotors;
    using constants::ports::rightDriveMotors;

    if (leftDriveMotors.size() > 0 && rightDriveMotors.size() > 0) {
        FollowableTalonSRXPtr leftTalon = 
            createTalonSRXGroup(leftDriveMotors, false, NeutralMode::Coast, .15);

        FollowableTalonSRXPtr rightTalon =
            createTalonSRXGroup(rightDriveMotors, true, NeutralMode::Coast, .15);

        IBasicMotorPtr leftMotor = adaptMotor(std::move(leftTalon));
        IBasicMotorPtr rightMotor = adaptMotor(std::move(rightTalon));

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
            std::make_shared<commands::CommandGroup>("DriveTrainCommandGroup");

        group->AddParallel(std::make_shared<commands::DriveXBox>(
            driveTrain.get(), commands::DriveXBox::Config()));
        group->AddParallel(std::make_shared<commands::PIDDriveSpeedometer>(
            driveTrain.get()));

        driveTrain->SetDefaultCommand(group);

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

        return std::move(elevator);
    }

    return nullptr;
}

SubsystemPtr initBallPickupPivot()
{
    using constants::ports::ballPivotMotors;

    FollowableTalonSRXPtr pivotMotor = 
        createTalonSRXGroup(ballPivotMotors, true, NeutralMode::Brake);

    if (pivotMotor) {
        TalonSRXConfiguration config;
        using ctre::phoenix::motorcontrol::VelocityMeasPeriod;
        using ctre::phoenix::motorcontrol::FeedbackDevice;
        config.velocityMeasurementPeriod = VelocityMeasPeriod::Period_20Ms;
        config.velocityMeasurementWindow = 4;
        config.peakOutputForward = .6;
        config.peakOutputReverse = -.6;

        pivotMotor->ConfigAllSettings(config);
        pivotMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute);

        IPIDMotorPtr pidPivotMotor = adaptMotor(std::move(pivotMotor), 4096);

        pidPivotMotor->setForwardSoftLimit(.95);
        pidPivotMotor->setReverseSoftLimit(0);
        pidPivotMotor->setForwardLimitEnabled(true);
        pidPivotMotor->setReverseLimitEnabled(true);

        pidPivotMotor->setAcceptableError(.02);
        pidPivotMotor->setPIDMaxForwardOutput(.3);
        pidPivotMotor->setP(2);
        pidPivotMotor->setD(20);

        std::unique_ptr<subsystems::PIDActuator> actuator = 
            std::make_unique<subsystems::PIDActuator>
            (std::move(pidPivotMotor), "BallPickupPivot");

        actuator->setHoldPositionEnabled(true);

        commands::ActuateJoystick::Config actuatorConfig;
        actuatorConfig.input = Input::ballPickupPivot;

        actuator->SetDefaultCommand(
            std::make_shared<commands::ActuateJoystick>(
                actuator.get(), actuatorConfig));

        return std::move(actuator);
    }

    return nullptr;
}

SubsystemPtr initBallPickupRollers()
{
    using constants::ports::ballRollerMotors;

    FollowableTalonSRXPtr pivotMotor = 
        createTalonSRXGroup(ballRollerMotors, true, NeutralMode::Brake);

    if (pivotMotor) {
        pivotMotor->ConfigPeakOutputForward(1);
        pivotMotor->ConfigPeakOutputReverse(-1);

        std::unique_ptr<subsystems::SimpleActuator> actuator = 
            std::make_unique<subsystems::SimpleActuator>
            (adaptMotor(std::move(pivotMotor)), "BallPickupRollers");

        commands::ActuateJoystick::Config actuatorConfig;
        actuatorConfig.input = Input::ballPickupRollers;

        actuator->SetDefaultCommand(
            std::make_shared<commands::ActuateJoystick>(
                actuator.get(), actuatorConfig));

        return std::move(actuator);
    }

    return nullptr;
}

SubsystemPtr initHatchHook()
{
    using constants::ports::hatchHookMotors;

    FollowableTalonSRXPtr hatchHookMotor = 
        createTalonSRXGroup(hatchHookMotors, false, NeutralMode::Brake);

    if (hatchHookMotor) {
        hatchHookMotor->ConfigPeakOutputForward(1);
        hatchHookMotor->ConfigPeakOutputReverse(-1);

        std::unique_ptr<subsystems::SimpleActuator> actuator = 
            std::make_unique<subsystems::SimpleActuator>
            (adaptMotor(std::move(hatchHookMotor)), "HatchHook");

        commands::ActuateJoystick::Config actuatorConfig;
        actuatorConfig.input = Input::hatchHook;

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
    subsystems[Subsystem::HatchHook] = initHatchHook();
    return std::move(subsystems);
}

}
}