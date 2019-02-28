#pragma once

#include <frc/PIDOutput.h>


namespace skyline
{

/**
 * An interface for a simple percent power based
 * motor controller
 */
class IBasicMotorController : public frc::PIDOutput
{
public:
    virtual ~IBasicMotorController() {}

    // Accepted values are -1.0 to 1.0
    virtual void setPower(double percentPower) = 0;
    virtual double getPower() const = 0;

    // Inverts the power (forward is now backward)
    virtual void setInverted(bool isInverted) = 0;
    virtual bool getInverted() const = 0;

    void PIDWrite(double output) override { setPower(output); }
};
    
}
