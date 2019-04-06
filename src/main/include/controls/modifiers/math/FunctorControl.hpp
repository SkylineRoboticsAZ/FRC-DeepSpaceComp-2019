#pragma once

#include "controls/modifiers/ModifiedControl.hpp"

#include <memory>


namespace skyline
{
namespace controls
{

/**
 * Modifies an existing control by passing its value through a
 * functor, lamdba or function pointer.
 */
template <typename Function>
class FunctionControl : public ModifiedControl
{
public:
    FunctionControl(ControlPtr control, Function function);

    double modifyDouble(double original) const override
    {
        return mFunction(original);
    }

    bool modifyBool(bool original) const override
    {
        return mFunction(original);
    }

private:
    Function mFunction;
};

}
}