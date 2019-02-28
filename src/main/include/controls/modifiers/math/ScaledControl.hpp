#pragma once

#include "controls/modifiers/ModifiedControl.hpp"

#include <memory>


namespace skyline
{
namespace controls
{

/**
 * Scales an existing control by the provided scale factor. This is equivalent
 * to the original value multiplied by the scale factor.
 */
class ScaledControl : public ModifiedControl
{
public:
    ScaledControl(ControlPtr control, double scale);

    double modifyDouble(double original) const override;

private:
    const double mScale;
};

}
}