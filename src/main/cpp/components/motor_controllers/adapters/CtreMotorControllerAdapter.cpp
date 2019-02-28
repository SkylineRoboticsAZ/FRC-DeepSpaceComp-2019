#include "components/motor_controllers/adapters/CtreMotorControllerAdapter.hpp"

#include <ctre/phoenix/motorcontrol/IMotorController.h>


namespace skyline
{

CtreMotorControllerAdapter::CtreMotorControllerAdapter(std::unique_ptr<Motor> motor) :
mMotor(std::move(motor)) {}

void CtreMotorControllerAdapter::setPower(double percentPower)
{
    using ctre::phoenix::motorcontrol::ControlMode;
    mMotor->Set(ControlMode::PercentOutput, percentPower);
}

double CtreMotorControllerAdapter::getPower() const
{
    return mMotor->GetMotorOutputPercent();
}

void CtreMotorControllerAdapter::setInverted(bool isInverted)
{
    mMotor->SetInverted(isInverted);
}

bool CtreMotorControllerAdapter::getInverted() const
{
    return mMotor->GetInverted();
}

IPIDMotorController::Mode CtreMotorControllerAdapter::mode() const
{
    using ctre::phoenix::motorcontrol::ControlMode;
    switch (mMotor->GetControlMode()) {
        case ControlMode::Velocity:
            return Mode::Velocity;
        case ControlMode::Position:
            return Mode::Position;
        default:
            return Mode::PercentOutput;
    }
}

void CtreMotorControllerAdapter::set(Mode mode, double value)
{
    using ctre::phoenix::motorcontrol::ControlMode;
    switch (mode) {
        case Mode::PercentOutput:
            setPower(value);
            break;
        case Mode::Position:
            mMotor->Set(ControlMode::Position, value);
            break;
        case Mode::Velocity:
            mMotor->Set(ControlMode::Velocity, value);
            break;
    }
}

double CtreMotorControllerAdapter::sensorPosition() const
{
    return mMotor->GetSelectedSensorPosition();
}

double CtreMotorControllerAdapter::sensorVelocity() const
{
    return mMotor->GetSelectedSensorVelocity();
}

void CtreMotorControllerAdapter::reset()
{
    setPower(0);
    mMotor->SetIntegralAccumulator(0);
}

}