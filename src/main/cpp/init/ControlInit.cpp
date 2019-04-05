#include "init/ControlInit.hpp"

#include "RobotMap.hpp"

#include "controls/DriverStation.hpp"
#include "controls/Inputs.hpp"
#include "controls/Outputs.hpp"

#include "controls/builders/ControlBuilder.hpp"

#include "controls/modifiers/math/AveragedControl.hpp"
#include "controls/modifiers/logic/ConditionalControl.hpp"
#include "controls/modifiers/math/SumControl.hpp"

#include <frc/XboxController.h>

#include <iostream>


namespace skyline
{
namespace controls
{

typedef IControl::ControlPtr ControlPtr;

// Define your joysticks here
frc::XboxController kDriveJoystick(constants::ports::driveJoystick);
frc::XboxController kAuxJoystick(constants::ports::auxJoystick);

ControlPtr average(ControlPtr controlOne, ControlPtr controlTwo)
{
    return std::make_shared<AveragedControl>(controlOne, controlTwo);
}

ControlPtr conditional(ControlPtr conditional, ControlPtr trueControl, ControlPtr falseControl)
{
    return std::make_shared<ConditionalControl>(conditional, trueControl, falseControl);
}

ControlPtr add(ControlPtr controlOne, ControlPtr controlTwo)
{
    return std::make_unique<SumControl>(controlOne, controlTwo);
}

// Define all outputs here
OutputControlMap initializeOutputs()
{
    OutputControlMap controlMap;

    // Virtual
    ControlPtr none = ControlBuilder()
        .constant(0, false)
        .build();

    ControlPtr hatchHookEnabled = ControlBuilder()
        .constant(1, false)
        .build();

    // Controller 1
    /*ControlPtr leftThrottle = ControlBuilder()
        .joystick(&kDriveJoystick, IControl::Double, 2)
        .deadband(.02)
        .invert()
        .build();

    ControlPtr rightThrottle = ControlBuilder()
        .joystick(&kDriveJoystick, IControl::Double, 3)
        .deadband(.02)
        .build();*/

    ControlPtr netThrottle = ControlBuilder()
        .joystick(&kDriveJoystick, IControl::Double, 5)
        .deadband(.1)
        .raise(2)
        .invert()
        .build();

    /*ControlPtr netThrottle = ControlBuilder(
        average(
            ControlBuilder(leftThrottle)
                .invert()
                .build(), 
            rightThrottle)
        )
        .scale(.8)
        .raise(2)
        .build();*/

    ControlPtr leftStickX = ControlBuilder()
        .joystick(&kDriveJoystick, IControl::Double, 0)
        .deadband(.1)
        .scale(.7)
        .build();

    // Controller 2
    ControlPtr sLeftStickY = ControlBuilder()
        .joystick(&kAuxJoystick, IControl::Double, 1)
        .deadband(.15)
        .scale(.6)
        .invert()
        .build();

    ControlPtr sRightStickY = ControlBuilder()
        .joystick(&kAuxJoystick, IControl::Double, 5)
        .deadband(.2)
        .scale(.5)
        .build();

    ControlPtr modifier = ControlBuilder().joystick(&kAuxJoystick, IControl::Bool, 6).build();
    ControlPtr aButton = ControlBuilder().joystick(&kAuxJoystick, IControl::Bool, 1).build();
    ControlPtr bButton = ControlBuilder().joystick(&kAuxJoystick, IControl::Bool, 2).build();
    ControlPtr xButton = ControlBuilder().joystick(&kAuxJoystick, IControl::Bool, 3).build();
    ControlPtr yButton = ControlBuilder().joystick(&kAuxJoystick, IControl::Bool, 4).build();

    ControlPtr normalBButton = conditional(modifier, none, bButton);
    ControlPtr normalXButton = conditional(modifier, none, xButton);
    ControlPtr normalYButton = conditional(modifier, none, yButton);

    ControlPtr modifiedBButton = conditional(modifier, bButton, none);
    ControlPtr modifiedXButton = conditional(modifier, xButton, none);
    ControlPtr modifiedYButton = conditional(modifier, yButton, none);

    ControlPtr leftTriggerButton = ControlBuilder()
        .joystick(&kAuxJoystick, IControl::Double, 2)
        .round()
        .invert()
        .build();

    ControlPtr rightTriggerButton = ControlBuilder()
        .joystick(&kAuxJoystick, IControl::Double, 3)
        .round()
        .build();

    /*ControlPtr netTriggers = average(
        ControlBuilder(leftTriggerButton).invert().build(), rightTriggerButton);*/

    ControlPtr netTriggers = add(leftTriggerButton, rightTriggerButton);

    ControlPtr hatchHookTrigger = ControlBuilder()
        .joystick(&kAuxJoystick, IControl::Bool, 5)
        .build();

    // Controller 1
    /*controlMap[Output::leftThrottle] = leftThrottle;
    controlMap[Output::rightThrottle] = rightThrottle;*/
    controlMap[Output::netThrottle] = netThrottle;
    controlMap[Output::leftStickX] = leftStickX;

    // Controller 2
    controlMap[Output::sRightStickY] = sRightStickY;
    controlMap[Output::sAButton] = aButton;
    controlMap[Output::sBButton] = normalBButton;
    controlMap[Output::sXButton] = normalXButton;
    controlMap[Output::sYButton] = normalYButton;
    controlMap[Output::sRbBButton] = modifiedBButton;
    controlMap[Output::sRbXButton] = modifiedXButton;
    controlMap[Output::sRbYButton] = modifiedYButton;
    controlMap[Output::sLeftStickY] = sLeftStickY;
    controlMap[Output::sNetTriggers] = netTriggers;
    controlMap[Output::sLbButton] = hatchHookTrigger;

    // Virtual
    controlMap[Output::None] = none;
    controlMap[Output::hatchHookEnabled] = hatchHookEnabled;
    
    return controlMap;
}

void initControlBindings()
{
    using controls::Input;
    using controls::Output;

    DriverStation &driverStation = DriverStation::getInstance();

    // Controller 1 
    driverStation.assignOutputToInput(Output::netThrottle, Input::throttle);
    driverStation.assignOutputToInput(Output::leftStickX, Input::turnFactor);

    // Controller 2
    driverStation.assignOutputToInput(Output::sRightStickY, Input::elevator);
    driverStation.assignOutputToInput(Output::sAButton, Input::elevatorBottom);

    driverStation.assignOutputToInput(Output::sRbXButton, Input::elevatorDiskBottom);
    driverStation.assignOutputToInput(Output::sXButton, Input::elevatorBallBottom);
    driverStation.assignOutputToInput(Output::sRbYButton, Input::elevatorDiskMiddle);
    driverStation.assignOutputToInput(Output::sYButton, Input::elevatorBallMiddle);
    driverStation.assignOutputToInput(Output::sRbBButton, Input::elevatorDiskTop);
    driverStation.assignOutputToInput(Output::sBButton, Input::elevatorBallTop);
    driverStation.assignOutputToInput(Output::sLeftStickY, Input::ballPickupPivot);
    driverStation.assignOutputToInput(Output::sNetTriggers, Input::ballPickupRollers);
    driverStation.assignOutputToInput(Output::sLbButton, Input::hatchHookTrigger);

    // Virtual
    driverStation.assignOutputToInput(Output::hatchHookEnabled, Input::hatchHook);
}

}
}