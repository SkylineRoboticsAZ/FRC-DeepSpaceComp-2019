#include "RobotMap.hpp"

#include "init/SubsystemInit.hpp"

#include "commands/drive/DriveXBox.hpp"
#include "commands/ActuateJoystick.hpp"

#include "subsystems/drive/SimpleDriveTrain.hpp"
#include "subsystems/drive/PIDDriveTrain.hpp"
#include "subsystems/Elevator.hpp"

#include "components/sensors/PIDEncoder.hpp"

#include "components/motor_controllers/IBasicMotorController.hpp"
#include "components/motor_controllers/groups/MotorControllerGroup.hpp"
#include "components/motor_controllers/groups/FollowableTalonSRX.hpp"
#include "components/motor_controllers/adapters/CtreMotorControllerAdapter.hpp"
#include "components/motor_controllers/adapters/WpiMotorControllerAdapter.hpp"
#include "components/motor_controllers/adapters/PIDMotorControllerAdapter.hpp"

#include <frc/SpeedController.h>

#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>
#include <ctre/phoenix/motorcontrol/IMotorController.h>


namespace skyline
{
namespace subsystems
{

using controls::Input;
using ctre::phoenix::motorcontrol::NeutralMode;
using ctre::phoenix::motorcontrol::can::TalonSRX;
using ctre::phoenix::motorcontrol::can::SlotConfiguration;
using ctre::phoenix::motorcontrol::can::TalonSRXConfiguration;

typedef std::unique_ptr<TalonSRX> TalonSRXPtr;
typedef std::unique_ptr<IBasicMotorController> IBasicMotorPtr;
typedef std::unique_ptr<IPIDMotorController> IPIDMotorPtr;
typedef std::unique_ptr<FollowableTalonSRX> FollowableTalonSRXPtr;

std::unique_ptr<skyline::IBasicMotorController> adaptMotor(
    std::unique_ptr<frc::SpeedController> motor)
{
    return std::make_unique<skyline::WpiMotorControllerAdapter>(std::move(motor));
}

std::unique_ptr<skyline::IPIDMotorController> adaptMotor(
    std::unique_ptr<ctre::phoenix::motorcontrol::IMotorController> motor)
{
    return std::make_unique<skyline::CtreMotorControllerAdapter>(std::move(motor));
}

FollowableTalonSRXPtr createTalonSRXGroup(const std::vector<int> &ports, bool isInverted, NeutralMode mode)
{
    const size_t motorCount = ports.size();
    if (motorCount > 0) {
        FollowableTalonSRXPtr master = 
            std::make_unique<FollowableTalonSRX>(ports.at(0));
        master->SetNeutralMode(mode);
        master->SetInverted(isInverted);

        for (int i = 1; i < motorCount; i++) {
            TalonSRXPtr slave = std::make_unique<TalonSRX>(ports.at(i));
            slave->SetNeutralMode(mode);
            slave->SetInverted(isInverted);

            master->addFollower(std::move(slave));
        }

        return std::move(master);
    }

    return nullptr;
}

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

        SlotConfiguration pidConfig;
        pidConfig.allowableClosedloopError = 10;
        pidConfig.kF = .496120271581;
        pidConfig.kP = 0;
        pidConfig.kI = 0;
        pidConfig.kD = 0;

        config.slot0 = pidConfig;

        leftMotor->ConfigAllSettings(config);
        leftMotor->SelectProfileSlot(0, 0);
        leftMotor->SetSensorPhase(true);

        PIDMotorControllerAdapter::PIDConfig rightPidConfig;
        rightPidConfig.allowableError = 10;
        rightPidConfig.maxForwardOutput = 1;
        rightPidConfig.maxReverseOutput = 1;
        rightPidConfig.kF = .00048481368111;

        IPIDMotorPtr leftPidMotor = adaptMotor(std::move(leftMotor));

        std::shared_ptr<frc::Encoder> rightEncoder = 
            std::make_shared<frc::Encoder>(2, 3, true, 
                frc::Encoder::EncodingType::k1X);

        std::shared_ptr<IPIDSensor> rightPidEncoder = 
            std::make_shared<PIDEncoder>(rightEncoder);

        IPIDMotorPtr rightPidMotor = 
            std::make_unique<PIDMotorControllerAdapter>(
                std::move(rightMotor), rightPidEncoder, rightPidConfig);

        std::unique_ptr<PIDDriveTrain> driveTrain = 
            std::make_unique<PIDDriveTrain>(
                std::move(leftPidMotor), std::move(rightPidMotor), 2062.64806247);

        driveTrain->SetDefaultCommand(
            std::make_unique<commands::DriveXBox>(driveTrain.get(), commands::DriveXBox::Config()));

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
        /*config.peakOutputForward = .3;
        config.peakOutputReverse = -.3;*/
        config.clearPositionOnLimitF = true;

        SlotConfiguration pidConfig;
        pidConfig.closedLoopPeakOutput = .3;
        pidConfig.allowableClosedloopError = 20;
        pidConfig.kF = 0;
        pidConfig.kP = 2.84;
        pidConfig.kI = 0;
        pidConfig.kD = 0;

        config.slot0 = pidConfig;

        motor->ConfigAllSettings(config);
        motor->SelectProfileSlot(0, 0);
        motor->SetSensorPhase(true);

        PIDMotorControllerAdapter::PIDConfig softwarePidConfig;
        softwarePidConfig.maxForwardOutput = 1;
        softwarePidConfig.maxReverseOutput = 1;
        softwarePidConfig.kP = 1.0/360.0;
        softwarePidConfig.allowableError = 10;

        std::shared_ptr<frc::Encoder> encoder = 
            std::make_shared<frc::Encoder>(2, 3, true, 
                frc::Encoder::EncodingType::k1X);

        std::shared_ptr<IPIDSensor> pidEncoder = 
            std::make_shared<PIDEncoder>(encoder);

        IPIDMotorPtr pidMotor = std::make_unique<PIDMotorControllerAdapter>(
            adaptMotor(std::move(motor)), pidEncoder, softwarePidConfig);

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

SubsystemMap initSubsystems()
{
    SubsystemMap subsystems;
    subsystems[Subsystem::DriveTrain] = initDriveTrain();
    subsystems[Subsystem::Elevator] = initElevator();
    return std::move(subsystems);
}

}
}