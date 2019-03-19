#pragma once

#include "controls/IControl.hpp"

#include <memory>
#include <vector>


namespace skyline
{

namespace controls
{

/**
 * Adds the values of two controls together. This does not apply to boolean 
 * values (readBool() will always return false for this control).
 */
class SumControl : public IControl
{
public:
    SumControl(ControlPtr controlOne, ControlPtr controlTwo);
    SumControl(const std::vector<ControlPtr> &controls);

    IControl::Type type() const override;
    double readDouble() const override;
    bool readBool() const override;

private:
    std::vector<ControlPtr> mControls;
};

}

}