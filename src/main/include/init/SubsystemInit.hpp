#pragma once

#include <memory>
#include <unordered_map>


namespace skyline
{
namespace subsystems
{

class SubsystemBase;
enum class Subsystem : unsigned int;

typedef std::unique_ptr<SubsystemBase> SubsystemPtr;
typedef std::unordered_map<Subsystem, SubsystemPtr> SubsystemMap;

SubsystemMap initSubsystems();

}
}