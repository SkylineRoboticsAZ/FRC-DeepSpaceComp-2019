#include "components/motor_controllers/adapters/CtreMotorControllerAdapter.hpp"

#include <ctre/phoenix/motorcontrol/IMotorController.h>


namespace skyline
{

CtreMotorControllerAdapter::CtreMotorControllerAdapter(
    std::unique_ptr<Motor> motor, double sensorScaleFactor) :
    mMotor(std::move(motor)), mSensorScaleFactor(sensorScaleFactor) {}

void CtreMotorControllerAdapter::setP(double p)
{
    mMotor->Config_kP(0, unscalePIDF(p), mTimeoutMs);
}

void CtreMotorControllerAdapter::setI(double i)
{
    mMotor->Config_kI(0, unscalePIDF(i), mTimeoutMs);
}

void CtreMotorControllerAdapter::setD(double d)
{
    mMotor->Config_kD(0, unscalePIDF(d), mTimeoutMs);
}

void CtreMotorControllerAdapter::setF(double f)
{
    mMotor->Config_kF(0, unscalePIDF(f), mTimeoutMs);
}

void CtreMotorControllerAdapter::setRampingPeriod(double period)
{
    mMotor->ConfigClosedloopRamp(period, mTimeoutMs);
}

void CtreMotorControllerAdapter::setAcceptableError(double error)
{
    const double nativeError = error * mSensorScaleFactor;
    mMotor->ConfigAllowableClosedloopError(0, nativeError, mTimeoutMs);
}

void CtreMotorControllerAdapter::setPIDMaxForwardOutput(double percentPower)
{
    mMotor->ConfigClosedLoopPeakOutput(0, percentPower, mTimeoutMs);
}

void CtreMotorControllerAdapter::setPIDMaxReverseOutput(double percentPower)
{
    setPIDMaxForwardOutput(percentPower);
}

double CtreMotorControllerAdapter::p() const
{
    using ctre::phoenix::ParamEnum;
    return scalePIDF(mMotor->ConfigGetParameter(
        ParamEnum::eProfileParamSlot_P, 0, mTimeoutMs));
}

double CtreMotorControllerAdapter::i() const
{
    using ctre::phoenix::ParamEnum;
    return scalePIDF(mMotor->ConfigGetParameter(
        ParamEnum::eProfileParamSlot_I, 0, mTimeoutMs));
}

double CtreMotorControllerAdapter::d() const
{
    using ctre::phoenix::ParamEnum;
    return scalePIDF(mMotor->ConfigGetParameter(
        ParamEnum::eProfileParamSlot_D, 0, mTimeoutMs));
}

double CtreMotorControllerAdapter::f() const
{
    using ctre::phoenix::ParamEnum;
    return scalePIDF(mMotor->ConfigGetParameter(
        ParamEnum::eProfileParamSlot_F, 0, mTimeoutMs));
}

double CtreMotorControllerAdapter::rampingPeriod() const
{
    using ctre::phoenix::ParamEnum;
    return mMotor->ConfigGetParameter(
        ParamEnum::eClosedloopRamp, 0, mTimeoutMs);
}

double CtreMotorControllerAdapter::acceptableError() const
{
    using ctre::phoenix::ParamEnum;

    const double nativeError = mMotor->ConfigGetParameter(
        ParamEnum::eProfileParamSlot_AllowableErr, 0, mTimeoutMs);

    return nativeError / mSensorScaleFactor;
}

double CtreMotorControllerAdapter::PIDMaxForwardOutput()
{
    using ctre::phoenix::ParamEnum;
    return mMotor->ConfigGetParameter(
        ParamEnum::eProfileParamSlot_PeakOutput, 0, mTimeoutMs);
}

double CtreMotorControllerAdapter::PIDMaxReverseOutput()
{
    return PIDMaxForwardOutput();
}

IPIDMotorController::Mode CtreMotorControllerAdapter::mode() const
{
    using ctre::phoenix::motorcontrol::ControlMode;
    switch (mMotor->GetControlMode()) {
        case ControlMode::Velocity:
            return Mode::Velocity;
        case ControlMode::Position:
            return Mode::Position;
        default:
            return Mode::PercentOutput;
    }
}

void CtreMotorControllerAdapter::set(Mode mode, double value)
{
    using ctre::phoenix::motorcontrol::ControlMode;
    switch (mode) {
        case Mode::PercentOutput:
            setPower(value);
            break;
        case Mode::Position:
            mMotor->Set(ControlMode::Position, value);
            break;
        case Mode::Velocity:
            mMotor->Set(ControlMode::Velocity, value);
            break;
    }
}

double CtreMotorControllerAdapter::sensorPosition() const
{
    return mMotor->GetSelectedSensorPosition();
}

double CtreMotorControllerAdapter::sensorVelocity() const
{
    return mMotor->GetSelectedSensorVelocity();
}

void CtreMotorControllerAdapter::reset()
{
    setPower(0);
    mMotor->SetIntegralAccumulator(0);
}

void CtreMotorControllerAdapter::setPower(double percentPower)
{
    using ctre::phoenix::motorcontrol::ControlMode;
    mMotor->Set(ControlMode::PercentOutput, percentPower);
}

double CtreMotorControllerAdapter::getPower() const
{
    return mMotor->GetMotorOutputPercent();
}

void CtreMotorControllerAdapter::setInverted(bool isInverted)
{
    mMotor->SetInverted(isInverted);
}

bool CtreMotorControllerAdapter::getInverted() const
{
    return mMotor->GetInverted();
}

double CtreMotorControllerAdapter::scalePIDF(double unscaledValue) const
{
    return unscaledValue * (mSensorScaleFactor / mCtrePIDScale);
}

double CtreMotorControllerAdapter::unscalePIDF(double scaledValue) const
{
    return scaledValue * (mCtrePIDScale / mSensorScaleFactor);
}

IPIDMotorPtr adaptMotor(std::unique_ptr<IMotorController> motor, 
    double sensorScaleFactor)
{
    return std::make_unique<skyline::CtreMotorControllerAdapter>
        (std::move(motor), sensorScaleFactor);
}

}