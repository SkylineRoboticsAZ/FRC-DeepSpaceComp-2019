#pragma once

#include "controls/modifiers/ModifiedControl.hpp"


namespace skyline
{
namespace controls
{

/**
 * Inverts an exsiting control. For double values, this is equivalent to
 * the original value * -1. For boolean values, the value will be inverted
 * (true = false and false = true).
 */
class InvertedControl : public ModifiedControl
{
public:
    InvertedControl(ControlPtr control);

protected:
    double modifyDouble(double original) const override;
    bool modifyBool(bool original) const override;
};

}
}