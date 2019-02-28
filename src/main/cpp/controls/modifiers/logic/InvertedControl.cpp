#include "controls/modifiers/logic/InvertedControl.hpp"


namespace skyline
{
namespace controls
{

InvertedControl::InvertedControl(ControlPtr control) :
ModifiedControl(control) {}

double InvertedControl::modifyDouble(double original) const
{
    return -original;
}

bool InvertedControl::modifyBool(bool original) const
{
    return !original;
}

}
}