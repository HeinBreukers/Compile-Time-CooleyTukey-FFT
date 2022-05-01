#pragma once

#include "ConstexprMath.hpp"

#include <array>

template<typename T, std::size_t size_x, std::size_t size_y>
constexpr T IIR(std::array<T,size_x> in_x, std::array<T,size_x> weights_x,std::array<T,size_y> in_y, std::array<T,size_y> weights_y)
{
    in_x[0] = in_x[0]*weights_x[0];

    if constexpr (size_x<size_y)
    {
        for(int i=1;i<size_x;++i)
        {
            in_x[i] = in_x[i]*weights_x[i];
            in_y[i] = in_y[i]*weights_y[i];
        }
        for(int i=size_x;i<size_y;++i)
        {
            in_y[i] = in_y[i]*weights_y[i];
        }
    }
    else
    {
        for(int i=1;i<size_y;++i)
        {
            in_x[i] = in_x[i]*weights_x[i];
            in_y[i] = in_y[i]*weights_y[i];
        }
        for(int i=size_x;i<size_y;++i)
        {
            in_x[i] = in_x[i]*weights_x[i];
        }

    }
    return 1/weight_y[0]*(CTM::fastacc(in_x)-CTM::fastacc(in_y));
}


template<typename T, std::size_t size>
constexpr T IIR<T,size,size>(std::array<T,size> in_x, std::array<T,size> weights_x,std::array<T,size> in_y, std::array<T,size> weights_y)
{
    in_x[0] = in_x[0]*weights_x[0];
    for(int i=1;i<size;++i)
    {
        in_x[i] = in_x[i]*weights_x[i];
        in_y[i] = in_y[i]*weights_y[i];
    }
    return 1/weight_y[0]*(CTM::fastacc(in_x)-CTM::fastacc(in_y));
}