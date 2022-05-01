#pragma once

#include "ConstexprMath.hpp"

#include <array>

template<typename T, std::size_t size>
constexpr T FIR(std::array<T,size> in, std::array<T,size> weights)
{
    // (TODO) compile time multiplies -> immediate multiplies instead of register multiplies
    for(int i=0;i<size;++i)
    {
        in[i] = in[i]*weights[i];
    }

    return CTM::fastacc(in);
}
