#include "controls/modifiers/logic/ConditionalControl.hpp"


namespace skyline
{

namespace controls
{

ConditionalControl::ConditionalControl(ControlPtr conditional, 
    ControlPtr trueControl, ControlPtr falseControl) :
mConditional(conditional), mTrue(trueControl), mFalse(falseControl) {}

IControl::Type ConditionalControl::type() const
{
    return (mConditional->readBool() ? mTrue->type() : mFalse->type());
}

double ConditionalControl::readDouble() const
{
    return (mConditional->readBool() ? mTrue->readDouble() : mFalse->readDouble());
}

bool ConditionalControl::readBool() const
{
    return (mConditional->readBool() ? mTrue->readBool() : mFalse->readBool());
}

}

}