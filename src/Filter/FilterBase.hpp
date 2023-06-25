#pragma once

//#include "MultiplyAcc/MultiplyAcc.hpp"
#include <ratio>
#include <array>

namespace DSP
{

template<typename Derived>
class FilterBase
{
public:

    template<typename U>
    auto filter(U&& frequency)
    {
        return static_cast<Derived*>(this)->filter(std::forward<U>(frequency));
    }

private:
    
};

}