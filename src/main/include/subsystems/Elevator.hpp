#pragma once

#include "subsystems/SubsystemBase.hpp"
#include "subsystems/actuators/PIDActuator.hpp"

#include <unordered_map>


namespace skyline
{

class IPIDMotorController;

namespace subsystems
{

/**
 * An elevator which moves to pre-defined positions and can also be
 * controlled by percent power to fine-tune the position.
 */
class Elevator : public PIDActuator
{
public:
    enum class Position : unsigned int
    {
        Bottom, DiskBottom, BallBottom, DiskMiddle, 
        BallMiddle, DiskTop, BallTop
    };

    typedef std::unordered_map<Position, double> Positions;

    Elevator(Motor motor, const Positions &positions, 
        const wpi::Twine &name = "Elevator");

    void setTargetPosition(Position position);

private:
    const Positions mPositions;
};

}
}