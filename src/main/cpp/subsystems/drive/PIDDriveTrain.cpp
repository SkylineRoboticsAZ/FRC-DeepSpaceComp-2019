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

void PIDDriveTrain::setMode(Mode mode)
{
    mMode = mode;
}

void PIDDriveTrain::setLeftPower(double percentPower)
{
    switch(mMode) {
        case Mode::PercentPower:
            mLeftMotor->set(IPIDMotorController::Mode::PercentOutput, percentPower);
            break;
        case Mode::Velocity:
            mLeftTarget = mMaxVelocity * percentPower;
            mLeftMotor->set(IPIDMotorController::Mode::Velocity, mLeftTarget);
            break;
    }
}

void PIDDriveTrain::setRightPower(double percentPower)
{
    switch(mMode) {
        case Mode::PercentPower:
            mRightMotor->set(IPIDMotorController::Mode::PercentOutput, percentPower);
            break;
        case Mode::Velocity:
            mRightTarget = mMaxVelocity * percentPower;
            mRightMotor->set(IPIDMotorController::Mode::Velocity, mLeftTarget);
            break;
    }
}

PIDDriveTrain::Mode PIDDriveTrain::mode() const
{
    return mMode;
}

double PIDDriveTrain::velocityTarget() const
{
    return (mLeftTarget + mRightTarget) / 2;
}

double PIDDriveTrain::sensorVelocity() const
{
    return (mLeftMotor->sensorVelocity() + mRightMotor->sensorVelocity()) / 2;
}

double PIDDriveTrain::leftVelocity() const
{
    return mLeftMotor->sensorVelocity();
}

double PIDDriveTrain::rightVelocity() const
{
    return mRightMotor->sensorVelocity();
}

}
}