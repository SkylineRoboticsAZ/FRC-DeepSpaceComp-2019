#pragma once

#include "subsystems/SubsystemBase.hpp"
#include "subsystems/actuators/ActuatorBase.hpp"

#include <unordered_map>


namespace skyline
{

class IPIDMotorController;

namespace subsystems
{

/**
 * An elevator which moves to pre-defined positions and can also be
 * controlled by percent power to fine-tune the position. Additionally,
 * if the hold position feature is enabled, the elevator will automatically
 * hold its current height after setPower() is called with a value of 0.
 */
class Elevator : public ActuatorBase
{
public:
    enum class Position
    {
        Bottom, DiskBottom, BallBottom, DiskMiddle, 
        BallMiddle, DiskTop, BallTop
    };

    typedef std::unique_ptr<IPIDMotorController> Motor;
    typedef std::unordered_map<Position, double> Positions;

    Elevator(Motor motor, const Positions &positions, 
        const wpi::Twine &name = "Elevator");

    void setHoldPositionEnabled(bool isEnabled);
    bool isHoldPositionEnabled() const;

    void setTargetPosition(Position position);

    // Sets the percentage power for manual control of the elevator.
    // If the hold position feature is enabled, a power of 0% will
    // cause the elevator to use position PID control to hold its
    // current position. In this mode note that a call to setTargetPosition() 
    // will override holding the position, still allowing the elevator to 
    // move to the new target.
    void setPower(double percentPower) override;

private:
    Motor mMotor;
    const Positions mPositions;
    bool mHoldPositionEnabled = false;
    bool mIsHoldingPosition = false;
    double mPreviousPower = 0.0;

    void setTargetPosition(double position);
};

}
}