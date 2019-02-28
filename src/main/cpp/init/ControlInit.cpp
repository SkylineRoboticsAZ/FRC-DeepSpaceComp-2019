#include "init/ControlInit.hpp"

#include "RobotMap.hpp"

#include "controls/DriverStation.hpp"
#include "controls/Inputs.hpp"
#include "controls/Outputs.hpp"

#include "controls/builders/ControlBuilder.hpp"

#include "controls/modifiers/math/AveragedControl.hpp"
#include "controls/modifiers/logic/ConditionalControl.hpp"

#include <frc/XboxController.h>

#include <iostream>


namespace skyline
{
namespace controls
{

typedef IControl::ControlPtr ControlPtr;

// Define your joysticks here
frc::XboxController kDriveJoystick(constants::ports::driveJoystick);

ControlPtr average(ControlPtr controlOne, ControlPtr controlTwo)
{
    return std::make_shared<AveragedControl>(controlOne, controlTwo);
}

ControlPtr conditional(ControlPtr conditional, ControlPtr trueControl, ControlPtr falseControl)
{
    return std::make_shared<ConditionalControl>(conditional, trueControl, falseControl);
}

// Define all outputs here
OutputControlMap initializeOutputs()
{
    OutputControlMap controlMap;

    ControlPtr none = ControlBuilder()
        .constant(0, false)
        .build();

    ControlPtr leftThrottle = ControlBuilder()
        .joystick(&kDriveJoystick, IControl::Double, 2)
        .scale(2)
        .deadband(.05)
        .build();

    ControlPtr rightThrottle = ControlBuilder()
        .joystick(&kDriveJoystick, IControl::Double, 3)
        .scale(2)
        .deadband(.05)
        .build();

    ControlPtr netThrottle = ControlBuilder(
        average(
            ControlBuilder(leftThrottle)
                .invert()
                .build(), 
            rightThrottle)
        )
        .raise(2)
        .build();

    ControlPtr leftStickX = ControlBuilder()
        .joystick(&kDriveJoystick, IControl::Double, 0)
        .deadband(.15)
        .raise(2)
        .build();

    ControlPtr rightStickY = ControlBuilder()
        .joystick(&kDriveJoystick, IControl::Double, 5)
        .deadband(.15)
        .scale(.33)
        .build();

    ControlPtr modifier = ControlBuilder().joystick(&kDriveJoystick, IControl::Bool, 6).build();
    ControlPtr aButton = ControlBuilder().joystick(&kDriveJoystick, IControl::Bool, 1).build();
    ControlPtr bButton = ControlBuilder().joystick(&kDriveJoystick, IControl::Bool, 2).build();
    ControlPtr xButton = ControlBuilder().joystick(&kDriveJoystick, IControl::Bool, 3).build();
    ControlPtr yButton = ControlBuilder().joystick(&kDriveJoystick, IControl::Bool, 4).build();

    ControlPtr normalBButton = conditional(modifier, none, bButton);
    ControlPtr normalXButton = conditional(modifier, none, xButton);
    ControlPtr normalYButton = conditional(modifier, none, yButton);

    ControlPtr modifiedBButton = conditional(modifier, bButton, none);
    ControlPtr modifiedXButton = conditional(modifier, xButton, none);
    ControlPtr modifiedYButton = conditional(modifier, yButton, none);

    controlMap[Output::None] = none;
    controlMap[Output::leftThrottle] = leftThrottle;
    controlMap[Output::rightThrottle] = rightThrottle;
    controlMap[Output::netThrottle] = netThrottle;
    controlMap[Output::leftStickX] = leftStickX;
    controlMap[Output::rightStickY] = rightStickY;
    controlMap[Output::aButton] = aButton;
    controlMap[Output::bButton] = normalBButton;
    controlMap[Output::xButton] = normalXButton;
    controlMap[Output::yButton] = normalYButton;
    controlMap[Output::rbBButton] = modifiedBButton;
    controlMap[Output::rbXButton] = modifiedXButton;
    controlMap[Output::rbYButton] = modifiedYButton;
    
    return controlMap;
}

void initControlBindings()
{
    using controls::Input;
    using controls::Output;

    DriverStation &driverStation = DriverStation::getInstance();

    driverStation.assignOutputToInput(Output::netThrottle, Input::throttle);
    driverStation.assignOutputToInput(Output::leftStickX, Input::turnFactor);
    driverStation.assignOutputToInput(Output::rightStickY, Input::elevator);
    driverStation.assignOutputToInput(Output::aButton, Input::elevatorBottom);
    driverStation.assignOutputToInput(Output::xButton, Input::elevatorDiskBottom);
    driverStation.assignOutputToInput(Output::rbXButton, Input::elevatorBallBottom);
    driverStation.assignOutputToInput(Output::yButton, Input::elevatorDiskMiddle);
    driverStation.assignOutputToInput(Output::rbYButton, Input::elevatorBallMiddle);
    driverStation.assignOutputToInput(Output::bButton, Input::elevatorDiskTop);
    driverStation.assignOutputToInput(Output::rbBButton, Input::elevatorBallTop);   
}

}
}