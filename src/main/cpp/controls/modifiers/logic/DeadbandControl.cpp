#include "controls/modifiers/logic/DeadbandControl.hpp"


namespace skyline
{
namespace controls
{

DeadbandControl::DeadbandControl(ControlPtr control, double deadband) : 
ModifiedControl(control), mDeadband(deadband) {}

double DeadbandControl::modifyDouble(double original) const
{
    if (original > mDeadband || original < -mDeadband)
        return original;

    return 0;
}

}
}