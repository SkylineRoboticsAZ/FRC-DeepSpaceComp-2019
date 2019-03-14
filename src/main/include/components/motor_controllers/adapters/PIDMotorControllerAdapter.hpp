#pragma once

#include "components/motor_controllers/IPIDMotorController.hpp"

#include <memory>
#include <atomic>


namespace frc
{

class PIDController;

}

namespace skyline
{

class IPIDSensor;

class PIDMotorControllerAdapter : public IPIDMotorController
{
public:
    PIDMotorControllerAdapter(std::unique_ptr<IBasicMotorController> motor, 
        std::shared_ptr<IPIDSensor> sensor, double loopPeriod = .05);
    ~PIDMotorControllerAdapter();

    void setP(double p) override;
    void setI(double i) override;
    void setD(double d) override;
    void setF(double f) override;
    void setRampingPeriod(double period) override;
    void setAcceptableError(double error) override;
    void setPIDMaxForwardOutput(double percentPower) override;
    void setPIDMaxReverseOutput(double percentPower) override;

    double p() const override;
    double i() const override;
    double d() const override;
    double f() const override;
    double rampingPeriod() const override;
    double acceptableError() const override;
    double PIDMaxForwardOutput() override;
    double PIDMaxReverseOutput() override;

    Mode mode() const override;
    void set(Mode mode, double value) override;

    double sensorPosition() const override;
    double sensorVelocity() const override;

    void reset() override;

    void setPower(double percentPower) override;
    double getPower() const override;

    void setInverted(bool isInverted) override;
    bool getInverted() const override;

private:
    class RampedPIDOutput;
    std::unique_ptr<IBasicMotorController> mMotor;
    std::unique_ptr<RampedPIDOutput> mRampedOutput;
    std::shared_ptr<IPIDSensor> mSensor;
    std::unique_ptr<frc::PIDController> mPIDController;
    std::atomic<double> mMaxForwardOutput, mMaxReverseOutput, mMaxRate;
    const double mLoopPeriod;
    double mAbsoluteTolerance = 0;
};

}