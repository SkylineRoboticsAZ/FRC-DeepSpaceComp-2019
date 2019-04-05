#pragma once

#include "components/motor_controllers/IBasicMotorController.hpp"


namespace skyline
{

/**
 * An interface for a motor controller with the ability to run 
 * position / velocity closed loop PID control. Note that the
 * PIDF variables should assume a maximum output of 1 from the PID
 * calculator.
 */
class IPIDMotorController : public IBasicMotorController
{
public:
    enum class Mode
    {
        PercentOutput, Position, Velocity
    };

    virtual ~IPIDMotorController() {}

    // PIDF variables assume a maximum PID output of 1
    virtual void setP(double p) = 0;
    virtual void setI(double i) = 0;
    virtual void setD(double d) = 0;
    virtual void setF(double f) = 0;

    // Ramping period is the amount of time it should take the motor
    // to go from 0% to 100% power. Similar functionality can be achieved
    // through the use of the I and D variables as an alternative
    virtual void setRampingPeriod(double period) = 0;
    virtual void setAcceptableError(double error) = 0;
    virtual void setPIDMaxForwardOutput(double percentPower) = 0;
    virtual void setPIDMaxReverseOutput(double percentPower) = 0;

    virtual void zeroSensorPosition() = 0;

    virtual double p() const = 0;
    virtual double i() const = 0;
    virtual double d() const = 0;
    virtual double f() const = 0;
    virtual double rampingPeriod() const = 0;
    virtual double acceptableError() const = 0;
    virtual double PIDMaxForwardOutput() const = 0;
    virtual double PIDMaxReverseOutput() const = 0;
    virtual bool isAtTarget() const = 0;

    virtual Mode mode() const = 0;
    virtual void set(Mode mode, double value) = 0;  

    virtual double sensorPosition() const = 0;
    virtual double sensorVelocity() const = 0;

    virtual void reset() = 0;
};

}