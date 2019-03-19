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
    // Controller 1
    None,
    leftThrottle,
    rightThrottle,
    netThrottle,
    leftStickX,

    // Controller 2
    sLeftStickY,
    sRightStickY,
    sNetTriggers,
    sAButton,
    sXButton,
    sYButton,
    sBButton,
    sRbXButton,
    sRbYButton,
    sRbBButton
};

}
}