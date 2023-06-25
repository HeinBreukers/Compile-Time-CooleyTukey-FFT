#pragma once

#include "FilterBase.hpp"
#include <ratio>
#include <array>

namespace DSP
{

template<typename T, size_t Size>
class FIR: FilterBase<FIR>
{
public:

    filter(const std::array<T,Size>& in)
    {

    }
private:
    std::array<T,Size> m_coefficients;
};

}