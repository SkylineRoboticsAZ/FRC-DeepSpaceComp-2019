#include "controls/modifiers/math/PolarizedExponentialControl.hpp"

#include <math.h>


namespace skyline
{
namespace controls
{

PolarizedExponentialControl::PolarizedExponentialControl(ControlPtr control, 
    double power) : ModifiedControl(control), mPower(power) {}

double PolarizedExponentialControl::modifyDouble(double original) const
{
    return abs(pow(original, mPower)) * (original < 0 ? -1 : 1);
}

}
}