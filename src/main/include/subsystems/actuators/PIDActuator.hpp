#pragma once

#include "subsystems/actuators/ActuatorBase.hpp"


namespace skyline
{

class IPIDMotorController;

namespace subsystems
{

/**
 * An actuator which uses PID control to move to a target position or
 * at a target velocity. Additionally, if the hold position feature is enabled, 
 * the actuator will automatically hold its current position after setPower() 
 * is called with a value of 0.
 */
class PIDActuator : public ActuatorBase
{
public:
    typedef std::unique_ptr<IPIDMotorController> Motor;

    PIDActuator(Motor motor, const wpi::Twine &name = "PIDActuator");
    virtual ~PIDActuator() = default;

    // Sets the percentage power for manual control of the actuator.
    // If the hold position feature is enabled, a power of 0% will
    // cause the actuator to use position PID control to hold its
    // current position. In this mode note that a call to setPosition() 
    // will override holding the position, still allowing the elevator to 
    // move to the new target.
    void setPower(double percentPower) override;
    void setPosition(double position);
    void setVelocity(double velocity);

    void setHoldPositionEnabled(bool isEnabled);
    bool isHoldPositionEnabled() const;

    void zeroPosition();

    double position() const;
    double velocity() const;
    double acceptableError() const;

private:
    Motor mMotor;
    bool mHoldPositionEnabled = false;
    bool mIsHoldingPosition = false;
};

}
}