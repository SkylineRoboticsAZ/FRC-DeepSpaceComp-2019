#pragma once

#include "components/motor_controllers/IBasicMotorController.hpp"

#include <memory>

namespace skyline
{

/**
 * Allows for a group of IBasicMotorControllers to act as
 * a single IBasicMotorController. Useful when you have
 * multiple motors operating in sync.
 * 
 * Ownership of the added motors is transferred to this class
 */
class MotorControllerGroup : public IBasicMotorController
{
public:
    MotorControllerGroup();
    ~MotorControllerGroup();

    void addMotor(std::unique_ptr<IBasicMotorController> motor);

    void setPower(double percentPower) override;
    double getPower() const override;

    void setInverted(bool isInverted) override;
    bool getInverted() const override;

private:
    MotorControllerGroup(const MotorControllerGroup &other);
    const MotorControllerGroup &operator=(const MotorControllerGroup &other);

    class Impl;
    std::unique_ptr<Impl> mImpl;
};
}