#pragma once

#include "controls/IControl.hpp"

namespace frc
{
    class GenericHID;
}

namespace skyline
{

namespace controls
{

/**
 * Wraps a WPILib controller to provide an IControl producer.
 * The type parameter determines if the control reads a button
 * or an axis / trigger. (Buttons are boolean values and axis /
 * triggers are doubles). Index represents the specific button /
 * axis / trigger and can be found by looking at the driver station
 * software.
 */
class JoystickControl : public IControl
{
public:
    JoystickControl(frc::GenericHID *joystick, IControl::Type type, 
                    unsigned int index);

    IControl::Type type() const override;
    double readDouble() const override;
    bool readBool() const override;

private:
    const frc::GenericHID *mJoystick;
    const IControl::Type mType;
    const unsigned int mIndex;
};

}

}
