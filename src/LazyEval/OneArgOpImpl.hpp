#pragma once

#include "Meta.hpp"
#include "../Internal/SIMD/Meta.hpp"

//#include "Scalar.hpp"

#include <cstddef>
#include <array>
#include <type_traits>
#include <fmt/core.h>

namespace Lazy
{

template<typename Derived>
class OneArgOpImplBase
{
public:
    template<typename T>
    static auto operateScalar(T&& val)
    {
        return Derived::operateScalar(std::forward<T>(val));
    }

    template<typename T>
    static auto operate(T&& val)
    {
        return Derived::operate(std::forward<T>(val));
    }

};

}
