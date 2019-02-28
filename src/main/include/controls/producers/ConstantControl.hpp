#pragma once

#include "controls/IControl.hpp"

#include <memory>


namespace skyline
{

namespace controls
{

/**
 * An IControl producer which simply returns a constant double and boolean
 * value. Useful in combination with other controls which may require a
 * specific constant as a parameter.
 */
class ConstantControl : public IControl
{
public:
    ConstantControl(double doubleValue, bool boolValue);

    IControl::Type type() const override;
    double readDouble() const override;
    bool readBool() const override;

private:
    const double mDoubleValue;
    const bool mBoolValue;
};

}

}