#include "controls/producers/JoystickControl.hpp"

#include <frc/GenericHID.h>


namespace skyline
{

namespace controls
{

JoystickControl::JoystickControl(frc::GenericHID *joystick, IControl::Type type, 
                                 unsigned int index) : mJoystick(joystick),
                                 mType(type), mIndex(index) {}

IControl::Type JoystickControl::type() const
{
    return mType;
}

double JoystickControl::readDouble() const
{
    if (mType == IControl::Double)
        return mJoystick->GetRawAxis(mIndex);
    else
        return 0;
}

bool JoystickControl::readBool() const
{
    if (mType == IControl::Bool)
        return mJoystick->GetRawButton(mIndex);
    else
        return false;
}

}

}
