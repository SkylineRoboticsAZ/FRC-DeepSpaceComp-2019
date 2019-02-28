#pragma once


namespace skyline
{

namespace controls
{

/**
 * A list of all the software outputs for the robot code. These outputs are
 * assigned to software inputs in the DriverStation class.
 * 
 * Outputs should be named according to their physical mapping on the controller.
 * 
 * For example, an appropriate set of outputs for a tank drive would be
 * leftThrottle, rightThrottle, primaryTrigger
 */
enum class Output : unsigned int
{
    None,
    leftThrottle,
    rightThrottle,
    netThrottle,
    leftStickX,
    rightStickY,
    aButton,
    xButton,
    yButton,
    bButton,
    rbXButton,
    rbYButton,
    rbBButton
};

}

}