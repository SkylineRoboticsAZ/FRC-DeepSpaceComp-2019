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

class ControlBuilder
{
public:
    ControlBuilder() = default;
    ControlBuilder(std::shared_ptr<IControl> control);

    ControlBuilder &joystick(frc::GenericHID *joystick, IControl::Type type,
                             unsigned int index);
    ControlBuilder &constant(double doubleValue, bool boolValue);

    ControlBuilder &deadband(double deadband);
    ControlBuilder &invert();
    ControlBuilder &scale(double scaleFactor);
    ControlBuilder &raise(double power);
    ControlBuilder &round();

    IControl::ControlPtr build();

private:
    std::shared_ptr<IControl> mControl = nullptr;
};

}

}