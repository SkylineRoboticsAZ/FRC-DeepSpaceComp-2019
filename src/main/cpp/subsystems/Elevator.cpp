#include "subsystems/Elevator.hpp"

#include "components/motor_controllers/IPIDMotorController.hpp"

#include <iostream>


namespace skyline
{
namespace subsystems
{

Elevator::Elevator(Motor motor, const Positions &positions, 
        const wpi::Twine &name) : ActuatorBase(name), 
        mMotor(std::move(motor)), mPositions(positions) {}

void Elevator::setHoldPositionEnabled(bool isEnabled)
{
    mHoldPositionEnabled = isEnabled;
}

bool Elevator::isHoldPositionEnabled() const
{
    return mHoldPositionEnabled;
}

void Elevator::setTargetPosition(Position position)
{
    auto iterator = mPositions.find(position);
    if (iterator != mPositions.end()) {
        setTargetPosition(iterator->second);
        std::cout << "Setting Target Position: " << iterator->second << std::endl;
    }       
}

void Elevator::setPower(double power)
{
    if (mHoldPositionEnabled && power == 0) {
        if (!mIsHoldingPosition)
            setTargetPosition(mMotor->sensorPosition());
    }
    else {
        mMotor->set(IPIDMotorController::Mode::PercentOutput, power);
        mIsHoldingPosition = false;
    }
}

void Elevator::setTargetPosition(double position)
{
    mMotor->reset();
    mMotor->set(IPIDMotorController::Mode::Position, position);
    mIsHoldingPosition = true;
}

}
}