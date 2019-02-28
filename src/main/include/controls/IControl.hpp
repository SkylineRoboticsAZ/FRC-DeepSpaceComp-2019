#pragma once

#include <memory>


namespace skyline
{

namespace controls
{

class IControl
{
public:
    typedef std::shared_ptr<IControl> ControlPtr;

    enum Type
    {
        Bool, Double, Both
    };

    virtual ~IControl() {}
    virtual IControl::Type type() const = 0;
    virtual double readDouble() const = 0;
    virtual bool readBool() const = 0;
};

}

}
