#include "controls/producers/ConstantControl.hpp"


namespace skyline
{

namespace controls
{

ConstantControl::ConstantControl(double doubleValue, bool boolValue) : 
mDoubleValue(doubleValue), mBoolValue(boolValue) {}

IControl::Type ConstantControl::type() const
{
    return IControl::Both;
}

double ConstantControl::readDouble() const
{
    return mDoubleValue;
}

bool ConstantControl::readBool() const
{
    return mBoolValue;
}

}

}