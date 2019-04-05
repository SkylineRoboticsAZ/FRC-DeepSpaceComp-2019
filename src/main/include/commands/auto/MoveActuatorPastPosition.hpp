#pragma once

#include <frc/commands/Command.h>


namespace skyline
{

namespace subsystems
{

class PIDActuator;

}

namespace commands
{

/**
 * Moves an actuator past a set position. The targetMode variable sets the
 * target direction as behind or in front of the given position. This is an
 * auto command and will not finish until the actuator has moved to the target
 * position. If the actuator is already in the correct region, this command
 * will finish immediately.
 */
class MoveActuatorPastPosition : public frc::Command 
{
public:
    enum class Mode : unsigned int
    {
        LessThanTarget, GreaterThanTarget
    };

    MoveActuatorPastPosition(subsystems::PIDActuator *actuator, 
        double position, Mode targetMode);

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;

private:
    subsystems::PIDActuator *mActuator;
    const double mTarget;
    const Mode mTargetMode;
    bool mIsFinished = false;

    bool isAtTarget() const;
};

}
}
