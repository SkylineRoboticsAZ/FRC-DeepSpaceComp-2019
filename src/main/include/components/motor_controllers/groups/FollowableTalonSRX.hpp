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

}