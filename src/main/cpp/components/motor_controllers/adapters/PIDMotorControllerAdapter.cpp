#include "components/motor_controllers/adapters/PIDMotorControllerAdapter.hpp"

#include "components/sensors/IPIDSensor.hpp"

#include <frc/PIDController.h>
#include <algorithm>
#include <cmath>


namespace skyline
{

class PIDMotorControllerAdapter::RampedPIDOutput : public frc::PIDOutput
{
public:
    RampedPIDOutput(frc::PIDOutput *output, double loopPeriod, 
        double rampPeriod, double maxForwardOutput, 
        double maxReverseOutput) : mOutput(output), 
        mMaxRate(calcMaxRate(loopPeriod, rampPeriod)), 
        mMaxForwardOutput(fabs(maxForwardOutput)),
        mMaxReverseOutput(fabs(maxReverseOutput)) {}

    void PIDWrite(double output) 
    {
        double newOutput = output;

        if (mMaxRate != -1) {
            const double difference = output - mLastOutput;
            if (difference > mMaxRate)
                newOutput = mLastOutput + mMaxRate;
            else if (difference < -mMaxRate)
                newOutput = mLastOutput - mMaxRate;

            mLastOutput = newOutput;
        }

        if (newOutput >= 0) {
            mOutput->PIDWrite(std::min(newOutput, mMaxForwardOutput));
        } else {
            mOutput->PIDWrite(std::max(newOutput, -mMaxReverseOutput));
        }
    }

    double calcMaxRate(double loopPeriod, double rampPeriod) 
    {
        if (loopPeriod > 0 && rampPeriod > 0)
            return loopPeriod / rampPeriod;

        return -1;
    }

private:
    frc::PIDOutput *mOutput;
    const double mMaxRate;
    double mLastOutput = 0.0;
    const double mMaxForwardOutput, mMaxReverseOutput;
};

PIDMotorControllerAdapter::PIDMotorControllerAdapter(
    std::unique_ptr<IBasicMotorController> motor,
    std::shared_ptr<IPIDSensor> sensor, const PIDConfig &config) : 
    mMotor(std::move(motor)), mRampedOutput(std::make_unique<RampedPIDOutput>(
    mMotor.get(), config.loopPeriod, config.rampPeriod, 
    config.maxForwardOutput, config.maxReverseOutput)), mSensor(sensor), 
    mPIDController(std::make_unique<frc::PIDController>(config.kP, config.kI, 
    config.kD, config.kF, *mSensor, *mRampedOutput, config.loopPeriod))
{
    mPIDController->SetAbsoluteTolerance(config.allowableError);
}

PIDMotorControllerAdapter::~PIDMotorControllerAdapter() {}

IPIDMotorController::Mode PIDMotorControllerAdapter::mode() const
{
    if (mPIDController->IsEnabled()) {
        switch (mPIDController->GetPIDSourceType()) {
            case frc::PIDSourceType::kDisplacement:
                return Mode::Position;
            case frc::PIDSourceType::kRate:
                return Mode::Velocity;
        }
    }

    return Mode::PercentOutput;
}

void PIDMotorControllerAdapter::set(Mode mode, double value)
{
    switch (mode) {
        case Mode::PercentOutput:
            if (mPIDController->IsEnabled())
                mPIDController->Disable();
            mMotor->setPower(value);
            break;
        case Mode::Position:
            mPIDController->SetPIDSourceType(frc::PIDSourceType::kDisplacement);
            mPIDController->SetSetpoint(value);
            if (!mPIDController->IsEnabled())
                mPIDController->Enable();
            break;
        case Mode::Velocity:
            mPIDController->SetPIDSourceType(frc::PIDSourceType::kRate);
            mPIDController->SetSetpoint(value);
            if (!mPIDController->IsEnabled())
                mPIDController->Enable();
            break;
    }
}

double PIDMotorControllerAdapter::sensorPosition() const
{
    return mSensor->getDisplacement();
}

double PIDMotorControllerAdapter::sensorVelocity() const
{
    return mSensor->getRate();
}

void PIDMotorControllerAdapter::reset()
{
    mPIDController->Reset();
}

void PIDMotorControllerAdapter::setPower(double percentPower)
{
    set(Mode::PercentOutput, percentPower);
}

double PIDMotorControllerAdapter::getPower() const
{
    mMotor->getPower();
}

void PIDMotorControllerAdapter::setInverted(bool isInverted)
{
    mMotor->setInverted(isInverted);
}

bool PIDMotorControllerAdapter::getInverted() const
{
    return mMotor->getInverted();
}

}