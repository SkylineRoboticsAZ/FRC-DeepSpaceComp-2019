#pragma once

#include "subsystems/SubsystemBase.hpp"
#include "subsystems/actuators/ActuatorBase.hpp"


namespace skyline
{

class IBasicMotorController;

namespace subsystems
{

/**
 * A simple actuator which moves using percent power output
 */
class SimpleActuator : public ActuatorBase
{
public:
    typedef std::unique_ptr<IBasicMotorController> Motor;

    SimpleActuator(Motor motor, const wpi::Twine &name = "SimpleActuator");

    void setPower(double percentPower) override;

private:
    Motor mMotor;
};

}
}