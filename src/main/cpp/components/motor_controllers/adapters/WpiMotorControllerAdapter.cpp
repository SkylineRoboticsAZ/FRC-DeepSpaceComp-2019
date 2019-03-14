#include "components/motor_controllers/adapters/WpiMotorControllerAdapter.hpp"

#include <frc/SpeedController.h>

#include <math.h>


namespace skyline
{

WpiMotorControllerAdapter::WpiMotorControllerAdapter(std::unique_ptr<frc::SpeedController> motor) :
mMotor(std::move(motor)) {}

void WpiMotorControllerAdapter::setPower(double percentPower)
{
    mMotor->Set(percentPower);
}

double WpiMotorControllerAdapter::getPower() const
{
    return mMotor->Get();
}

void WpiMotorControllerAdapter::setInverted(bool isInverted)
{
    mMotor->SetInverted(isInverted);
}

bool WpiMotorControllerAdapter::getInverted() const
{
    return mMotor->GetInverted();
}

IBasicMotorPtr adaptMotor(std::unique_ptr<frc::SpeedController> motor)
{
    return std::make_unique<skyline::WpiMotorControllerAdapter>
        (std::move(motor));
}

}