//
// Created by Hein Breukers
//
#pragma once

#include "ConstexprMath.hpp"

#include <cstdint>
#include <array>
#include <complex>
#include <type_traits>

namespace CTFFT
{

constexpr double pi = 3.14159265358979323846;

// radix-2 Cooley-Tukey FFT 
template<typename T, std::size_t size>
constexpr std::array<std::complex<T>,size>  FFT(std::array<std::complex<T>,size> in) requires std::is_floating_point_v<T>
{
    if (size==1)
    {
        return in;
    }

    const int32_t size_over2 = size/2;

    std::array<std::complex<T>,size_over2> even;
    std::array<std::complex<T>,size_over2> odd;
    for (int i = 0; 2 * i < size; i++) 
    {
        even[i] = in[2*i];
        odd[i] = in[2*i+1];
    }

    auto buffer = FFT(std::move(even));
    auto buffer2 = FFT(std::move(odd));

    
    for (int k=0; k<(size_over2); ++k)
    {
        const T twiddleComponent = 2*static_cast<T>(pi)/static_cast<T>(size)*static_cast<T>(k);       
        const std::complex<T> twiddleFactor(CTM::cos<T,6>(twiddleComponent), -CTM::sin<T,6>(twiddleComponent));
        auto p = buffer[k];  
        auto q = buffer2[k]*twiddleFactor;
        in[k] = p+q;
        in[k+size_over2] = p-q;
    }
    return in;
}
} //namespace end
