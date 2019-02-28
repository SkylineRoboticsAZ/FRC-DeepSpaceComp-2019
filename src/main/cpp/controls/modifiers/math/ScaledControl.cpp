#include "controls/modifiers/math/ScaledControl.hpp"


namespace skyline
{
namespace controls
{

ScaledControl::ScaledControl(ControlPtr control, double scale) :
ModifiedControl(control), mScale(scale) {}

double ScaledControl::modifyDouble(double original) const
{
    return original * mScale;
}

}
}