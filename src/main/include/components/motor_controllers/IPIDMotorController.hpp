#pragma once

#include "components/motor_controllers/IBasicMotorController.hpp"


namespace skyline
{

/**
 * An interface for a motor controller with the ability to run 
 * position / velocity closed loop PID control.
 */
class IPIDMotorController : public IBasicMotorController
{
public:
    enum class Mode
    {
        PercentOutput, Position, Velocity
    };

    virtual ~IPIDMotorController() {}

    virtual Mode mode() const = 0;
    virtual void set(Mode mode, double value) = 0;  

    virtual double sensorPosition() const = 0;
    virtual double sensorVelocity() const = 0;

    virtual void reset() = 0;
};

}