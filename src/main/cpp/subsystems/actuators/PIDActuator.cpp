#include "subsystems/actuators/PIDActuator.hpp"

#include "components/motor_controllers/IPIDMotorController.hpp"

#include <iostream>


namespace skyline
{
namespace subsystems
{

PIDActuator::PIDActuator(Motor motor, const wpi::Twine &name) : 
ActuatorBase(name), mMotor(std::move(motor)) {}

void PIDActuator::setPower(double power)
{
    if (mHoldPositionEnabled && power == 0) {
        if (!mIsHoldingPosition)
            setPosition(mMotor->sensorPosition());
    }
    else {
        mMotor->set(IPIDMotorController::Mode::PercentOutput, power);
        mIsHoldingPosition = false;
    }
}

void PIDActuator::setPosition(double position)
{
    mMotor->reset();
    mMotor->set(IPIDMotorController::Mode::Position, position);
    mIsHoldingPosition = true;
    std::cout << "Setting Target Position: " << position << std::endl;
}

void PIDActuator::setVelocity(double velocity)
{
    mMotor->reset();
    mMotor->set(IPIDMotorController::Mode::Velocity, velocity);
}

void PIDActuator::setHoldPositionEnabled(bool isEnabled)
{
    mHoldPositionEnabled = isEnabled;
}

bool PIDActuator::isHoldPositionEnabled() const
{
    return mHoldPositionEnabled;
}

void PIDActuator::setForwardSoftLimit(double limit)
{
    mMotor->setForwardSoftLimit(limit);
}

void PIDActuator::setReverseSoftLimit(double limit)
{
    mMotor->setReverseSoftLimit(limit);
}

void PIDActuator::setForwardSoftLimitEnabled(bool enabled)
{
    mMotor->setForwardLimitEnabled(enabled);
}

void PIDActuator::setReverseSoftLimitEnabled(bool enabled)
{
    mMotor->setReverseLimitEnabled(enabled);
}

void PIDActuator::zeroPosition()
{
    mMotor->zeroSensorPosition();
}

double PIDActuator::position() const
{
    return mMotor->sensorPosition();
}

double PIDActuator::velocity() const
{
    return mMotor->sensorVelocity();
}

double PIDActuator::acceptableError() const
{
    return mMotor->acceptableError();
}

}
}