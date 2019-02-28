#pragma once

#include "subsystems/SubsystemBase.hpp"


namespace skyline
{
namespace subsystems
{

/**
 * Base class for actuator subsystems that have a percent power movement
 * feature.
 */
class ActuatorBase : public SubsystemBase
{
public:
    ActuatorBase(const wpi::Twine &name = "Actuator");
    virtual ~ActuatorBase() {}

    virtual void setPower(double percentPower) = 0;  
};

}
}