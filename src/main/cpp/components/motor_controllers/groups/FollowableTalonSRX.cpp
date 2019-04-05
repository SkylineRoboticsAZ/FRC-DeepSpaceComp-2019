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

FollowableTalonSRXPtr createTalonSRXGroup(const std::vector<int> &ports, 
    bool isInverted, NeutralMode mode, double openLoopRamp)
{
    const size_t motorCount = ports.size();
    if (motorCount > 0) {
        FollowableTalonSRXPtr master = 
            std::make_unique<FollowableTalonSRX>(ports.at(0));
        master->SetNeutralMode(mode);
        master->SetInverted(isInverted);
        master->ConfigOpenloopRamp(openLoopRamp);

        for (int i = 1; i < motorCount; i++) {
            TalonSRXPtr slave = std::make_unique<TalonSRX>(ports.at(i));
            slave->SetNeutralMode(mode);
            slave->SetInverted(isInverted);
            slave->ConfigOpenloopRamp(openLoopRamp);

            master->addFollower(std::move(slave));
        }

        return std::move(master);
    }

    return nullptr;
}

}