#include "components/motor_controllers/groups/FollowableTalonSRX.hpp"


namespace skyline
{

FollowableTalonSRX::FollowableTalonSRX(int port) : 
TalonSRX(port), BaseMotorController(port | 0x02040000) {}

void FollowableTalonSRX::addFollower(FollowerPtr follower)
{
    follower->Follow(*this);
    mFollowers.push_back(std::move(follower));
}

}