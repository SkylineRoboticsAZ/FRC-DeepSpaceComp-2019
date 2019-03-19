#include "controls/modifiers/math/SumControl.hpp"


namespace skyline
{

namespace controls
{

SumControl::SumControl(ControlPtr controlOne, ControlPtr controlTwo)
{
    mControls.reserve(2);
    mControls.push_back(controlOne);
    mControls.push_back(controlTwo);
    mControls.shrink_to_fit();
}

SumControl::SumControl(const std::vector<ControlPtr> &controls) : 
mControls(controls) {}

IControl::Type SumControl::type() const
{
    return IControl::Double;
}

double SumControl::readDouble() const
{
    double sum = 0;

    for (const ControlPtr &control : mControls)
        sum += control->readDouble();

    return sum;
}

bool SumControl::readBool() const
{
    return false;
}

}

}