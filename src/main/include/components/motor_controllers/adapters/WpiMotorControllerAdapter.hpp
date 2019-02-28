#pragma once

#include "components/motor_controllers/IBasicMotorController.hpp"

#include <memory>

namespace frc
{
    class SpeedController;
}

namespace skyline
{

/**
 * Wraps any motor controller that implements frc::SpeedController
 * so that it can work with objects that depend on IBasicMotorController
 * 
 * Ownership of the wrapped frc::SpeedController is transferred to this class
 */
class WpiMotorControllerAdapter : public IBasicMotorController
{
public:
    WpiMotorControllerAdapter(std::unique_ptr<frc::SpeedController> motor);

    void setPower(double percentPower) override;
    double getPower() const override;

    void setInverted(bool isInverted) override;
    bool getInverted() const override;

private:
    std::unique_ptr<frc::SpeedController> mMotor;
};

}