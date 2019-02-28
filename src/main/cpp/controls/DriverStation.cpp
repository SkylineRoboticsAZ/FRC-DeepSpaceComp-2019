#include "controls/DriverStation.hpp"

#include "controls/Inputs.hpp"
#include "controls/Outputs.hpp"
#include "controls/IControl.hpp"

#include "init/ControlInit.hpp"

#include <iostream>
#include <unordered_map>


namespace skyline
{
namespace controls
{

typedef IControl::ControlPtr ControlPtr;
typedef std::unordered_map<Input, Output> InputOutputMap;

class DriverStation::Impl
{
public:
    const OutputControlMap mOutputControlMap;
    InputOutputMap mInputOutputMap;

    Impl() : mOutputControlMap(initializeOutputs()) {}

    Output assignedOutput(Input input) const
    {
        auto iterator = mInputOutputMap.find(input);

        if (iterator != mInputOutputMap.end())
            return iterator->second;
        
        return Output::None;
    }

    const ControlPtr assignedControl(Output output)
    {
        auto iterator = mOutputControlMap.find(output);

        if (iterator != mOutputControlMap.end())
            return iterator->second;

        return nullptr;
    }

    const ControlPtr assignedControl(Input input)
    {
        const Output output = assignedOutput(input);
        const ControlPtr control = assignedControl(output);

        if (!control) {
            std::cout << "Warning: DriverStation output #" << 
            static_cast<unsigned int>(output) << 
            " has no assigned control!" << std::endl;
        }

        return control;
    }
};

DriverStation &DriverStation::getInstance()
{
    static DriverStation instance;
    return instance;
}

DriverStation::DriverStation() : mImpl(std::make_unique<Impl>()) {}

DriverStation::~DriverStation() = default;

double DriverStation::readDouble(Input input) const
{
    ControlPtr control = mImpl->assignedControl(input);

    if (control) {
        switch (control->type()) {
            case IControl::Type::Both:
            case IControl::Type::Double:
                return control->readDouble();
            case IControl::Type::Bool:
                return control->readBool() ? 1.0 : 0.0;
        }
    }

    control = mImpl->assignedControl(Output::None);

    if (control)
        return control->readDouble();

    std::cout << "Warning: DriverStation Output::None missing! \n"
                  "Using default value of " << mDefaultDoubleValue 
                  << " instead" << std::endl;

    return mDefaultDoubleValue;
}

bool DriverStation::readBoolean(Input input) const
{
    ControlPtr control = mImpl->assignedControl(input);

    if (control) {
        switch (control->type()) {
            case IControl::Type::Both:
            case IControl::Type::Bool:
                return control->readBool();
            case IControl::Type::Double:
                return control->readDouble() == 1.0;
        }
    }

    control = mImpl->assignedControl(Output::None);

    if (control)
        return control->readBool();

    std::cout << "Warning: DriverStation Output::None missing! \n"
                  "Using default value of " << mDefaultBoolValue 
                  << " instead" << std::endl;

    return mDefaultBoolValue;
}

bool DriverStation::isInputBoolean(Input input) const
{
    const ControlPtr control = mImpl->assignedControl(input);

    if (control)
        return control->type() == IControl::Bool;

    return false;
}

bool DriverStation::isInputDouble(Input input) const
{
    const ControlPtr control = mImpl->assignedControl(input);

    if (control)
        return control->type() == IControl::Double;

    return false;
}

Output DriverStation::assignedOutput(Input input) const
{
    return mImpl->assignedOutput(input);
}

void DriverStation::assignOutputToInput(Output output, Input input)
{
    mImpl->mInputOutputMap[input] = output;
}

}
}