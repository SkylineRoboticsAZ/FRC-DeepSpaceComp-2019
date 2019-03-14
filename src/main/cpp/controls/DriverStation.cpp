#include "controls/DriverStation.hpp"

#include "controls/Inputs.hpp"
#include "controls/Outputs.hpp"
#include "controls/IControl.hpp"

#include "init/ControlInit.hpp"

#include <iostream>
#include <unordered_map>
#include <frc/smartdashboard/SmartDashboard.h>


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
    double value;

    ControlPtr control = mImpl->assignedControl(input);

    if (control) {
        switch (control->type()) {
            case IControl::Type::Both:
            case IControl::Type::Double:
                value = control->readDouble();
                break;
            case IControl::Type::Bool:
                value = control->readBool() ? 1.0 : 0.0;
                break;
        }
    } else {
        control = mImpl->assignedControl(Output::None);

        if (control) {
            value = control->readDouble();
        } else {
            std::cout << "Warning: DriverStation Output::None missing! \n"
                    "Using default value of " << mDefaultDoubleValue 
                    << " instead" << std::endl;

            value = mDefaultDoubleValue;
        }
    }

    std::string inputString = "Double Input #";
    inputString += std::to_string(static_cast<unsigned int>(input));
    inputString += " ";

    frc::SmartDashboard::PutNumber(inputString, value);

    return value;
}

bool DriverStation::readBoolean(Input input) const
{
    bool value;

    ControlPtr control = mImpl->assignedControl(input);

    if (control) {
        switch (control->type()) {
            case IControl::Type::Both:
            case IControl::Type::Bool:
                value = control->readBool();
                break;
            case IControl::Type::Double:
                value = control->readDouble() == 1.0;
                break;
        }
    } else {
        control = mImpl->assignedControl(Output::None);

        if (control) {
            value = control->readBool();
        } else {
            std::cout << "Warning: DriverStation Output::None missing! \n"
                    "Using default value of " << mDefaultBoolValue 
                    << " instead" << std::endl;

            value = mDefaultBoolValue;
        }
    }

    std::string inputString = "Boolean Input #";
    inputString += std::to_string(static_cast<unsigned int>(input));
    inputString += " ";

    frc::SmartDashboard::PutBoolean(inputString, value);

    return value;
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