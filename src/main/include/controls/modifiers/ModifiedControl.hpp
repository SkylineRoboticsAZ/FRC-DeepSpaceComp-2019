#pragma once

#include "controls/IControl.hpp"

#include <memory>


namespace skyline
{

namespace controls
{

/**
 * Provides a base class for implementing modifiers for the control
 * system. To subclass, inherit this class and reimplement the necessary
 * protected virtual methods (options are modifyType, modifyDouble, and
 * modifyBool). The default implementation of these methods does not modify
 * the original value, allowing for only the needed methods to be overriden.
 */
class ModifiedControl : public IControl
{
public:
    ModifiedControl(ControlPtr baseControl);
    virtual ~ModifiedControl() {}

    IControl::Type type() const;
    double readDouble() const;
    bool readBool() const;

protected:
    virtual IControl::Type modifyType(IControl::Type original) const;
    virtual double modifyDouble(double original) const;
    virtual bool modifyBool(bool original) const;

private:
    ControlPtr mBaseControl;
};

}

}
