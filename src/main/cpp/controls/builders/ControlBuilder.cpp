#include "controls/builders/ControlBuilder.hpp"

#include "controls/producers/JoystickControl.hpp"
#include "controls/producers/ConstantControl.hpp"

#include "controls/modifiers/logic/DeadbandControl.hpp"
#include "controls/modifiers/logic/InvertedControl.hpp"

#include "controls/modifiers/math/ScaledControl.hpp"
#include "controls/modifiers/math/RoundedControl.hpp"
#include "controls/modifiers/math/PolarizedExponentialControl.hpp"

#include <memory>


namespace skyline
{

namespace controls
{

ControlBuilder::ControlBuilder(std::shared_ptr<IControl> control) : 
mControl(control) {}

ControlBuilder &ControlBuilder::joystick(frc::GenericHID *joystick, 
IControl::Type type, unsigned int index)
{
    mControl = std::make_shared<JoystickControl>(joystick, type, index);
    return *this;
}

ControlBuilder &ControlBuilder::constant(double doubleValue, bool boolValue)
{
    mControl = std::make_shared<ConstantControl>(doubleValue, boolValue);
    return *this;
}

ControlBuilder &ControlBuilder::deadband(double deadband)
{
    if (mControl)
        mControl = std::make_shared<DeadbandControl>(mControl, deadband);
    return *this;
}

ControlBuilder &ControlBuilder::invert()
{
    if (mControl)
        mControl = std::make_shared<InvertedControl>(mControl);
    return *this;
}

ControlBuilder &ControlBuilder::scale(double scaleFactor)
{
    if (mControl)
        mControl = std::make_shared<ScaledControl>(mControl, scaleFactor);
    return *this;
}

ControlBuilder &ControlBuilder::raise(double power)
{
    if (mControl)
        mControl = std::make_shared<PolarizedExponentialControl>(mControl, power);
    return *this;
}

ControlBuilder &ControlBuilder::round()
{
    if (mControl)
        mControl = std::make_unique<RoundedControl>(mControl);
    return *this;
}

IControl::ControlPtr ControlBuilder::build()
{
    return mControl;
}

}

}