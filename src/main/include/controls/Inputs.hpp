#pragma once


namespace skyline
{
namespace controls
{

/**
 * A list of all the software inputs for the robot code. These inputs are
 * requestable by commands and are assigned an appropriate output in the
 * DriverStation class.
 * 
 * Inputs should be named according to their role as opposed to their
 * physical mapping on the controller.
 * 
 * For example, an appropriate set of inputs for a tank drive would be
 * leftDrive, rightDrive, and driveStraightMode
 */
enum class Input : unsigned int
{
    throttle,
    turnFactor,
    elevator,
    elevatorBottom,
    elevatorDiskBottom,
    elevatorBallBottom,
    elevatorDiskMiddle,
    elevatorBallMiddle,
    elevatorDiskTop,
    elevatorBallTop,
    ballPickupPivot,
    ballPickupRollers
};

}
}