#pragma once

#include "controls/IControl.hpp"

#include <memory>
#include <vector>


namespace skyline
{

namespace controls
{

/**
 * Averages the values of two or more controls together to create a single 
 * control. This does not apply to boolean values (readBool() will always
 * return false for this control).
 */
class AveragedControl : public IControl
{
public:
    AveragedControl(ControlPtr controlOne, ControlPtr controlTwo);
    AveragedControl(const std::vector<ControlPtr> &controls);

    IControl::Type type() const override;
    double readDouble() const override;
    bool readBool() const override;

private:
    std::vector<ControlPtr> mControls;
};

}

}