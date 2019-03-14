#include "subsystems/drive/PIDDriveTrain.hpp"

#include "components/motor_controllers/IPIDMotorController.hpp"


namespace skyline
{
namespace subsystems
{

PIDDriveTrain::PIDDriveTrain(Motor leftMotor, Motor rightMotor, 
    double maxVelocity, const wpi::Twine &name) :
    DriveTrainBase(name), mLeftMotor(std::move(leftMotor)), 
    mRightMotor(std::move(rightMotor)), mMaxVelocity(maxVelocity) {}

PIDDriveTrain::~PIDDriveTrain() {}

void PIDDriveTrain::setLeftPower(double percentPower)
{
    mLeftTarget = mMaxVelocity * percentPower;
    mLeftMotor->set(IPIDMotorController::Mode::Velocity, mLeftTarget);
}

void PIDDriveTrain::setRightPower(double percentPower)
{
    mRightTarget = mMaxVelocity * percentPower;
    mRightMotor->set(IPIDMotorController::Mode::Velocity, mRightTarget);
}

double PIDDriveTrain::velocityTarget() const
{
    return (mLeftTarget + mRightTarget) / 2;
}

double PIDDriveTrain::sensorVelocity() const
{
    return (mLeftMotor->sensorVelocity() + mRightMotor->sensorVelocity()) / 2;
}

}
}