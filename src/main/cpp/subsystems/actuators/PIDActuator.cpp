#include "subsystems/actuators/PIDActuator.hpp"

#include "components/motor_controllers/IPIDMotorController.hpp"


namespace skyline
{
namespace subsystems
{

PIDActuator::PIDActuator(Motor motor, const wpi::Twine &name) : 
ActuatorBase(name), mMotor(std::move(motor)) {}

void PIDActuator::setPower(double percentPower)
{
    mMotor->setPower(percentPower);
}

void PIDActuator::setPosition(double position)
{
    mMotor->reset();
    mMotor->set(IPIDMotorController::Mode::Position, position);
}

void PIDActuator::setVelocity(double velocity)
{
    mMotor->reset();
    mMotor->set(IPIDMotorController::Mode::Velocity, velocity);
}

double PIDActuator::position() const
{
    return mMotor->sensorPosition();
}

double PIDActuator::velocity() const
{
    return mMotor->sensorVelocity();
}

}
}