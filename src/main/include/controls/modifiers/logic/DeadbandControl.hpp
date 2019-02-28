#pragma once

#include "controls/modifiers/ModifiedControl.hpp"


namespace skyline
{
namespace controls
{

/**
 * Provides a deadband around an existing control. If the value of the
 * original control is not outside the deadband, it will be zeroed.
 */
class DeadbandControl : public ModifiedControl
{
public:
    DeadbandControl(ControlPtr control, double deadband);

protected:
    double modifyDouble(double original) const override;

private:
    const double mDeadband;
};

}
}