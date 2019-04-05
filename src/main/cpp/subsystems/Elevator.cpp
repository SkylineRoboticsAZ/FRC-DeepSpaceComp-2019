#include "subsystems/Elevator.hpp"

#include "components/motor_controllers/IPIDMotorController.hpp"

#include <iostream>


namespace skyline
{
namespace subsystems
{

Elevator::Elevator(Motor motor, const Positions &positions, 
        const wpi::Twine &name) : PIDActuator(std::move(motor), name), 
        mPositions(positions) {}

void Elevator::setTargetPosition(Position position)
{
    auto iterator = mPositions.find(position);
    if (iterator != mPositions.end())
        setPosition(iterator->second);
}

}
}