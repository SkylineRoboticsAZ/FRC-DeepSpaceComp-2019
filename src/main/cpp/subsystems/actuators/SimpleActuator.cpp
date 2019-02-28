#include "subsystems/actuators/SimpleActuator.hpp"

#include "components/motor_controllers/IBasicMotorController.hpp"


namespace skyline
{
namespace subsystems
{

SimpleActuator::SimpleActuator(Motor motor, const wpi::Twine &name) : 
ActuatorBase(name), mMotor(std::move(motor)) {}

void SimpleActuator::setPower(double percentPower)
{
    mMotor->setPower(percentPower);
}

}
}