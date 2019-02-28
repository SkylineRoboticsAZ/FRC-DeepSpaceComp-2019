#pragma once

#include "controls/IControl.hpp"


namespace skyline
{

namespace controls
{

/**
 * Uses an existing control as a conditional to switch between the behavior of 
 * two other controls. If the readBool() value of the conditional control is
 * true, this control will act as a pass through for trueControl. Likewise if
 * the value is false, this control will act as a pass through for 
 * falseControl.
 */
class ConditionalControl : public IControl
{
public:
    ConditionalControl(ControlPtr conditional, ControlPtr trueControl, 
                       ControlPtr falseControl);

    IControl::Type type() const override;
    double readDouble() const override;
    bool readBool() const override;

private:
    ControlPtr mConditional;
    ControlPtr mTrue;
    ControlPtr mFalse;
};

}

}