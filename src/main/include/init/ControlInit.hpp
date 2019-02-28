#pragma once

#include <memory>
#include <unordered_map>


namespace skyline
{
namespace controls
{

class IControl;
enum class Output : unsigned int;

typedef std::shared_ptr<IControl> ControlPtr;
typedef std::unordered_map<Output, ControlPtr> OutputControlMap;

OutputControlMap initializeOutputs();
void initControlBindings();

}
}