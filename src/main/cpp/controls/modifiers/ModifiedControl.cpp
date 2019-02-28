#include "controls/modifiers/ModifiedControl.hpp"


namespace skyline
{

namespace controls
{

ModifiedControl::ModifiedControl(ControlPtr baseControl) : 
mBaseControl(baseControl) {}

IControl::Type ModifiedControl::type() const
{
    return modifyType(mBaseControl->type());
}

double ModifiedControl::readDouble() const
{
    return modifyDouble(mBaseControl->readDouble());
}

bool ModifiedControl::readBool() const
{
    return modifyBool(mBaseControl->readBool());
}

IControl::Type ModifiedControl::modifyType(IControl::Type original) const
{
    return original;
}

double ModifiedControl::modifyDouble(double original) const
{
    return original;
}

bool ModifiedControl::modifyBool(bool original) const
{
    return original;
}

}

}