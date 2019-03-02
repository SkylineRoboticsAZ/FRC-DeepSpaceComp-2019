#pragma once

#include "components/sensors/IPIDSensor.hpp"

#include <frc/Encoder.h>

#include <memory>


namespace skyline
{

class PIDEncoder : public IPIDSensor
{
public:
    PIDEncoder(std::shared_ptr<frc::Encoder> encoder);

    void SetPIDSourceType(frc::PIDSourceType pidSource) override;
    frc::PIDSourceType GetPIDSourceType() const override;
    double PIDGet() override;

    double getDisplacement() const override;
    double getRate() const override;

private:
    std::shared_ptr<frc::Encoder> mEncoder;
};

}