#include "controls/modifiers/math/RoundedControl.hpp"

#include <math.h>

namespace skyline
{
namespace controls
{

RoundedControl::RoundedControl(ControlPtr control) : 
ModifiedControl(control) {}

double RoundedControl::modifyDouble(double original) const
{
    return std::round(original);
}

}
}