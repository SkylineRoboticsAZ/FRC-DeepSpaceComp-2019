#pragma once

#include "subsystems/actuators/ActuatorBase.hpp"


namespace skyline
{

class IPIDMotorController;

namespace subsystems
{

/**
 * An actuator which uses PID control to move to a target position or
 * at a target velocity
 */
class PIDActuator : public ActuatorBase
{
public:
    typedef std::unique_ptr<IPIDMotorController> Motor;

    PIDActuator(Motor motor, const wpi::Twine &name = "PIDActuator");

    void setPower(double percentPower) override;
    void setPosition(double position);
    void setVelocity(double velocity);

    double position() const;
    double velocity() const;

private:
    Motor mMotor;
};

}
}