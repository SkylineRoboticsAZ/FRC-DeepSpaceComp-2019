#pragma once

#include "triggers/TriggerBase.hpp"

#include <memory>


namespace frc
{

class Command;

}

namespace skyline
{

namespace controls
{

enum class Input : unsigned int;

}

using controls::Input;

namespace triggers
{

class BoolTrigger : public TriggerBase
{
public:
    typedef std::unique_ptr<frc::Command> CommandPtr;

    BoolTrigger(Input input, bool targetValue = true);
    ~BoolTrigger();

    bool Get() override;

private:
    const Input mInput;
    const bool mTargetValue;
};

}

}