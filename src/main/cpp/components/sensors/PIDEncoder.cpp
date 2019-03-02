#include "components/sensors/PIDEncoder.hpp"


namespace skyline
{

PIDEncoder::PIDEncoder(std::shared_ptr<frc::Encoder> encoder) : 
mEncoder(encoder) {}

void PIDEncoder::SetPIDSourceType(frc::PIDSourceType pidSource)
{
    mEncoder->SetPIDSourceType(pidSource);
}

frc::PIDSourceType PIDEncoder::GetPIDSourceType() const
{
    return mEncoder->GetPIDSourceType();
}

double PIDEncoder::PIDGet()
{
    return mEncoder->PIDGet();
}

double PIDEncoder::getDisplacement() const
{
    return mEncoder->GetDistance();
}

double PIDEncoder::getRate() const
{
    return mEncoder->GetRate();
}

}