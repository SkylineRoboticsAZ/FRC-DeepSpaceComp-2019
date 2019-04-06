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
    RampedPIDOutput(frc::PIDOutput *output, 
        const std::atomic<double> &maxForwardOutput, 
        const std::atomic<double> &maxReverseOutput,
        const std::atomic<double> &maxRate) : mOutput(output), 
        mMaxForwardOutput(maxForwardOutput), 
        mMaxReverseOutput(maxReverseOutput), mMaxRate(maxRate) {}

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

        if (newOutput >= 0)
            mOutput->PIDWrite(std::min(newOutput, mMaxForwardOutput.load()));
        else
            mOutput->PIDWrite(std::max(newOutput, -mMaxReverseOutput.load()));
    }

private:
    frc::PIDOutput *mOutput;
    double mLastOutput = 0.0;
    const std::atomic<double> &mMaxForwardOutput, &mMaxReverseOutput, &mMaxRate;
};

PIDMotorControllerAdapter::PIDMotorControllerAdapter(
    std::unique_ptr<IBasicMotorController> motor,
    std::shared_ptr<IPIDSensor> sensor, double loopPeriod) : 
    mMotor(std::move(motor)), mRampedOutput(std::make_unique<RampedPIDOutput>(
    mMotor.get(), mMaxForwardOutput, mMaxReverseOutput, mMaxRate)), 
    mSensor(sensor), mPIDController(std::make_unique<frc::PIDController>(
        0, 0, 0, *mSensor, *mRampedOutput, loopPeriod)), 
    mMaxForwardOutput(1), mMaxReverseOutput(1), mMaxRate(-1), mLoopPeriod(loopPeriod) 
{
    mPIDController->SetAbsoluteTolerance(mAbsoluteTolerance);
}

PIDMotorControllerAdapter::~PIDMotorControllerAdapter() {}

void PIDMotorControllerAdapter::setP(double p)
{
    mPIDController->SetP(p);
}

void PIDMotorControllerAdapter::setI(double i)
{
    mPIDController->SetI(i);
}

void PIDMotorControllerAdapter::setD(double d)
{
    mPIDController->SetD(d);
}

void PIDMotorControllerAdapter::setF(double f)
{
    mPIDController->SetF(f);
}

void PIDMotorControllerAdapter::setRampingPeriod(double period)
{
    if (mLoopPeriod > 0 && period > 0)
        mMaxRate = mLoopPeriod / period;
    else
        mMaxRate = -1;
}

void PIDMotorControllerAdapter::setAcceptableError(double error)
{
    mAbsoluteTolerance = error;
    mPIDController->SetAbsoluteTolerance(error);
}

void PIDMotorControllerAdapter::setPIDMaxForwardOutput(double percentPower)
{
    mMaxForwardOutput = fabs(percentPower);
}

void PIDMotorControllerAdapter::setPIDMaxReverseOutput(double percentPower)
{
    mMaxReverseOutput = fabs(percentPower);
}

bool PIDMotorControllerAdapter::isAtTarget() const
{
    switch (mode()) {
        case Mode::PercentOutput:
            return true;
        case Mode::Position:
        case Mode::Velocity:
            return mPIDController->OnTarget();
    }
}

void PIDMotorControllerAdapter::setForwardSoftLimit(double limit)
{
    
}

void PIDMotorControllerAdapter::setReverseSoftLimit(double limit)
{

}

void PIDMotorControllerAdapter::setForwardLimitEnabled(bool enabled)
{

}

void PIDMotorControllerAdapter::setReverseLimitEnabled(bool enabled)
{

}

void PIDMotorControllerAdapter::zeroSensorPosition() 
{
    mSensor->reset();
}

double PIDMotorControllerAdapter::p() const
{
    return mPIDController->GetP();
}

double PIDMotorControllerAdapter::i() const
{
    return mPIDController->GetI();
}

double PIDMotorControllerAdapter::d() const
{
    return mPIDController->GetD();
}

double PIDMotorControllerAdapter::f() const
{
    return mPIDController->GetF();
}

double PIDMotorControllerAdapter::rampingPeriod() const
{
    if (mMaxRate != -1)
        return mLoopPeriod / mMaxRate;

    return 0;
}

double PIDMotorControllerAdapter::acceptableError() const
{
    return mAbsoluteTolerance;
}

double PIDMotorControllerAdapter::PIDMaxForwardOutput() const
{
    return mMaxForwardOutput;
}

double PIDMotorControllerAdapter::PIDMaxReverseOutput() const
{
    return mMaxReverseOutput;
}

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