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
 * Note: PID control features are provided through the motor controller 
 * (Not WPILib) and must be configured before the adapter is applied
 * using the IMotorController interface
 */
class CtreMotorControllerAdapter : public IPIDMotorController
{
    typedef ctre::phoenix::motorcontrol::IMotorController Motor;
public:
    CtreMotorControllerAdapter(std::unique_ptr<Motor> motor);

    void setPower(double percentPower) override;
    double getPower() const override;

    void setInverted(bool isInverted) override;
    bool getInverted() const override;

    Mode mode() const override;
    void set(Mode mode, double value) override;

    double sensorPosition() const override;
    double sensorVelocity() const override;

    void reset() override;

private:
    std::unique_ptr<Motor> mMotor;
};

}
