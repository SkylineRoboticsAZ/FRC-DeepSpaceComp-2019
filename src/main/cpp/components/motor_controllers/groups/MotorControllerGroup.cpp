#include "components/motor_controllers/groups/MotorControllerGroup.hpp"

#include <memory>
#include <vector>

namespace skyline
{

class MotorControllerGroup::Impl
{
public:
    std::vector<std::unique_ptr<IBasicMotorController>> mMotors;
    bool mIsInverted = false;
    double mCurrentPower = 0;
};

MotorControllerGroup::MotorControllerGroup() : 
mImpl(std::make_unique<Impl>())
{

}

MotorControllerGroup::~MotorControllerGroup()
{
}

void MotorControllerGroup::addMotor(std::unique_ptr<IBasicMotorController> motor)
{
    motor->setPower(0);
    mImpl->mMotors.push_back(std::move(motor));
}

void MotorControllerGroup::setPower(double percentPower)
{
    mImpl->mCurrentPower = percentPower;
    for (std::unique_ptr<IBasicMotorController> &motor : mImpl->mMotors) 
    {
        motor->setPower(percentPower * (mImpl->mIsInverted ? -1 : 1));
    }
}

double MotorControllerGroup::getPower() const
{
    return mImpl->mCurrentPower;
}

void MotorControllerGroup::setInverted(bool isInverted)
{
    mImpl->mIsInverted = isInverted;
}

bool MotorControllerGroup::getInverted() const
{
    return mImpl->mIsInverted;
}

}