#pragma once

#include <frc/buttons/Trigger.h>

#include <memory>
#include <vector>


namespace frc
{

class Command;

}

namespace skyline
{
namespace triggers
{

class TriggerBase : public frc::Trigger
{
public:
    typedef std::unique_ptr<frc::Command> CommandPtr;
    typedef std::vector<CommandPtr> CommandPtrList;

    TriggerBase();
    virtual ~TriggerBase();

    virtual bool Get() = 0;

    void WhenActive(CommandPtr command);
    void WhileActive(CommandPtr command);
    void WhenInactive(CommandPtr command);
    void CancelWhenActive(CommandPtr command);
    void ToggleWhenActive(CommandPtr command);

private:
    CommandPtrList mWhenActiveCommands, mWhileActiveCommands, 
        mWhenInactiveCommands, mCancelWhenActiveCommands, 
        mToggleWhenActiveCommands;
};

}
}