#include "controls/modifiers/math/AveragedControl.hpp"


namespace skyline
{

namespace controls
{

AveragedControl::AveragedControl(ControlPtr controlOne, ControlPtr controlTwo)
{
    mControls.reserve(2);
    mControls.push_back(controlOne);
    mControls.push_back(controlTwo);
    mControls.shrink_to_fit();
}

AveragedControl::AveragedControl(const std::vector<ControlPtr> &controls) : 
mControls(controls) {}

IControl::Type AveragedControl::type() const
{
    return IControl::Double;
}

double AveragedControl::readDouble() const
{
    const size_t numberOfControls = mControls.size();

    if (numberOfControls > 0) {
        double sum = 0;
        for (ControlPtr control : mControls)
            sum += control->readDouble();

        return sum / mControls.size();
    }

    return 0;
}

bool AveragedControl::readBool() const
{
    return false;
}

}

}