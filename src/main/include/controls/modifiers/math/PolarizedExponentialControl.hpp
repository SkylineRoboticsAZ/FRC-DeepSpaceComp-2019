#pragma once

#include "controls/modifiers/ModifiedControl.hpp"


namespace skyline
{
namespace controls
{

/*
 * Raises the given control to the given power, retaining
 * the existing polarity. For example, a value of -.5 raised to the
 * power of 2 will be -.25
 */
class PolarizedExponentialControl : public ModifiedControl
{
public:
    PolarizedExponentialControl(ControlPtr control, double power);

    double modifyDouble(double original) const override;

private:
    const double mPower;
};

}
}