//
// Created by Hein Breukers
//
#pragma once

#include "ConstexprMath.h"

#include <cstdint>
#include <array>
#include <complex>
#include <type_traits>

namespace CTFFT
{

constexpr double pi = 3.14159265358979323846;

/*
// radix-2 Cooley-Tukey FFT O(n log(n))
template<typename T, std::size_t size>
constexpr std::array<std::complex<T>,size> FFT(const std::array<std::complex<T>,size>& in, const int32_t cursize = size, const int32_t stride = 1, const int32_t begin = 0) requires std::is_floating_point_v<T>
{
    std::array<std::complex<T>,size> out;
    if (cursize==1)
    {
      	out[0] = in[begin];
        return out;
    }
    int32_t size_over2 = cursize>>1;
    int32_t stride_times2 = stride<<1;
    auto buffer = FFT(in, size_over2, stride_times2, begin);
    auto buffer2 = FFT(in, size_over2, stride_times2, begin +stride);

    
    for (int k =0; k<(size_over2); k+=stride)
    {
        const T twiddleComponent = 2*static_cast<T>(pi)/static_cast<T>(cursize)*static_cast<T>(k);       
        const std::complex<T> twiddleFactor(CTM::cos<T,5>(twiddleComponent), -CTM::sin<T,5>(twiddleComponent));
        auto p = buffer[k];  
        auto q = buffer2[k]*twiddleFactor;
        out[k] = p+q;
        out[k+size_over2] = p-q;
    }
    return out;
}
*/
// radix-2 Cooley-Tukey FFT O(n log(n))
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
        const std::complex<T> twiddleFactor(CTM::cos<T,5>(twiddleComponent), -CTM::sin<T,5>(twiddleComponent));
        auto p = buffer[k];  
        auto q = buffer2[k]*twiddleFactor;
        // reuse in array as output array
        in[k] = p+q;
        in[k+size_over2] = p-q;
    }
    return in;
}
} //namespace end
