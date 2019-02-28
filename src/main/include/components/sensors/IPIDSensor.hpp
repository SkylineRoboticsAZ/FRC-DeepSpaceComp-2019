#pragma once

#include <frc/PIDSource.h>


namespace skyline
{

class IPIDSensor : public frc::PIDSource
{
public:
    virtual ~IPIDSensor() {}

    virtual void SetPIDSourceType(frc::PIDSourceType pidSource) = 0;
    virtual frc::PIDSourceType GetPIDSourceType() const = 0;
    virtual double PIDGet() = 0;

    virtual double getDisplacement() const = 0;
    virtual double getRate() const = 0;
};

}