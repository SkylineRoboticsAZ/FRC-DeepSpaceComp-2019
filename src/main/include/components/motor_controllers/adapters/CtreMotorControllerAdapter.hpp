#pragma once

#include "components/motor_controllers/IPIDMotorController.hpp"

#include <memory>

namespace ctre
{
namespace phoenix 
{
namespace motorcontrol
{
    class IMotorController;
}
}
}

namespace skyline
{

/**
 * Wraps any motor controller that implements ctre::phoenix::motorcontrol::IMotorController
 * so that it can work with objects that depend on IPIDMotorController
 * 
 * Ownership of the wrapped ctre::phoenix::motorcontrol::IMotorController 
 * is transferred to this class
 * 
 * Sensor scale factor is the number of native sensor units in one software unit.
 * For example, if your PIDF variables are calculated using rotations as units and
 * your encoder has a CPR of 360, the sensor scale factor should be 360.
 */
class CtreMotorControllerAdapter : public IPIDMotorController
{
    typedef ctre::phoenix::motorcontrol::IMotorController Motor;
public:
    CtreMotorControllerAdapter(std::unique_ptr<Motor> motor, 
        double sensorScaleFactor = 1);

    void setP(double p) override;
    void setI(double i) override;
    void setD(double d) override;
    void setF(double f) override;
    void setRampingPeriod(double period) override;
    void setAcceptableError(double error) override;
    
    // IMotorControllers do not have separate values for forward and
    // reverse. Both of these functions set a magnitude which applies for
    // both directions.
    void setPIDMaxForwardOutput(double percentPower) override;
    void setPIDMaxReverseOutput(double percentPower) override;

    void zeroSensorPosition() override;

    double p() const override;
    double i() const override;
    double d() const override;
    double f() const override;
    double rampingPeriod() const override;
    double acceptableError() const override;
    double PIDMaxForwardOutput() const override;
    double PIDMaxReverseOutput() const override;
    bool isAtTarget() const override;

    void setForwardSoftLimit(double limit) override;
    void setReverseSoftLimit(double limit) override;
    void setForwardLimitEnabled(bool enabled) override;
    void setReverseLimitEnabled(bool enabled) override;

    Mode mode() const override;
    void set(Mode mode, double value) override;

    double sensorPosition() const override;
    double sensorVelocity() const override;

    void reset() override;

    void setPower(double percentPower) override;
    double getPower() const override;

    void setInverted(bool isInverted) override;
    bool getInverted() const override;

private:
    std::unique_ptr<Motor> mMotor;
    const double mCtrePIDScale = 1023;
    const double mTimeoutMs = 100;
    const double mSensorScaleFactor;

    double scalePIDF(double unscaledValue) const;
    double unscalePIDF(double scaledValue) const;
};

using ctre::phoenix::motorcontrol::IMotorController;

typedef std::unique_ptr<IPIDMotorController> IPIDMotorPtr;
IPIDMotorPtr adaptMotor(std::unique_ptr<IMotorController> motor, 
    double sensorScaleFactor = 1);

}
