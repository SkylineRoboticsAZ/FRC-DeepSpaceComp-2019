#pragma once

#include <memory>


namespace skyline
{
namespace controls
{

enum class Input : unsigned int;
enum class Output : unsigned int;

/**
 * Provides access to the driver station controls for the robot and
 * allows for runtime manipulation of the robot control scheme.
 * 
 * When reading inputs note that they will be adjusted to the correct
 * type based on which read function is called.
 * 
 * If an input is unassigned, it will return the default values of
 * false for readBoolean() and 0.00 for readDouble().
 */
class DriverStation
{
public:
    DriverStation(DriverStation const&)  = delete;
    void operator=(DriverStation const&)  = delete;

    static DriverStation &getInstance();

    /**
     * Reads the value of the given input (typically a joystick axis).
     * 
     * If the underlying type of the input is a boolean, a value of true 
     * will return 1.00 and a value of false will return 0.00.
     */
    double readDouble(Input input) const;

    /**
     * Reads the value of the given input (typically a button).
     * 
     * If the underlying type of the input is a double, a value of 1.00 
     * will return true and any other value will return false.
     */
    bool readBoolean(Input input) const;

    // Checks if the given input is of type boolean
    bool isInputBoolean(Input input) const;

    // Checks if the given input is of type double
    bool isInputDouble(Input input) const;

    // Get the currently assigned output for a given output
    Output assignedOutput(Input input) const;

    // Assigns the given output to the given input, overriding 
    // any previously assigned output
    void assignOutputToInput(Output output, Input input);

private:
    DriverStation();
    ~DriverStation();

    class Impl;
    std::unique_ptr<Impl> mImpl;

    const bool mDefaultBoolValue = false;
    const double mDefaultDoubleValue = 0;
};

}
}