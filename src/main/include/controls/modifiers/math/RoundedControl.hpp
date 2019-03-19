#pragma once

#include "controls/modifiers/ModifiedControl.hpp"

#include <memory>


namespace skyline
{
namespace controls
{

/**
 * Rounds an existing control using standard rounding conventions for math.
 * Ex. .4 is rounded to 0 and .5 is rounded to 1
 */
class RoundedControl : public ModifiedControl
{
public:
    RoundedControl(ControlPtr control);

    double modifyDouble(double original) const override;
};

}
}