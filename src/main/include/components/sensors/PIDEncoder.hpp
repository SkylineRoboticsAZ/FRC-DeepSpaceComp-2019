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
    PIDEncoder(int aChannel, int bChannel, bool reverseDirection = false, 
               frc::Encoder::EncodingType encodingType = frc::Encoder::k4X);

    void SetPIDSourceType(frc::PIDSourceType pidSource) override;
    frc::PIDSourceType GetPIDSourceType() const override;
    double PIDGet() override;

    double getDisplacement() const override;
    double getRate() const override;

private:
    std::shared_ptr<frc::Encoder> mEncoder;
};

}