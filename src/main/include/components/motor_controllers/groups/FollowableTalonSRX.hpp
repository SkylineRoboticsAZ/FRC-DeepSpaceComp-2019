#pragma once

#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>

#include <memory>
#include <vector>


using ctre::phoenix::motorcontrol::IFollower;
using ctre::phoenix::motorcontrol::can::TalonSRX;
using ctre::phoenix::motorcontrol::can::BaseMotorController;

typedef std::unique_ptr<IFollower> FollowerPtr;

namespace skyline
{

class FollowableTalonSRX : public TalonSRX
{
public:
    FollowableTalonSRX(int port);

    void addFollower(FollowerPtr follower);

private:
    std::vector<FollowerPtr> mFollowers;
};

using ctre::phoenix::motorcontrol::NeutralMode;
using ctre::phoenix::motorcontrol::can::TalonSRX;

typedef std::unique_ptr<TalonSRX> TalonSRXPtr;
typedef std::unique_ptr<FollowableTalonSRX> FollowableTalonSRXPtr;

FollowableTalonSRXPtr createTalonSRXGroup(const std::vector<int> &ports, 
    bool isInverted, NeutralMode mode, double openLoopRamp = 0);

}