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
    mLeftMotor->set(IPIDMotorController::Mode::Velocity, 
                    mMaxVelocity * percentPower);
}

void PIDDriveTrain::setRightPower(double percentPower)
{
    mRightMotor->set(IPIDMotorController::Mode::Velocity, 
                     mMaxVelocity * percentPower);
}

}
}