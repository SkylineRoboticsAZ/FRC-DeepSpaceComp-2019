#pragma once

#include "components/motor_controllers/IPIDMotorController.hpp"

#include <memory>


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
    struct PIDConfig
    {
        double kP = 0;
        double kI = 0;
        double kD = 0;
        double kF = 0;
        double allowableError = 0;
        double maxForwardOutput = 1;
        double maxReverseOutput = 1;
        double loopPeriod = .05;
        double rampPeriod = 0;
    };

    PIDMotorControllerAdapter(std::unique_ptr<IBasicMotorController> motor, 
        std::shared_ptr<IPIDSensor> sensor, const PIDConfig &config);
    ~PIDMotorControllerAdapter();

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
};

}