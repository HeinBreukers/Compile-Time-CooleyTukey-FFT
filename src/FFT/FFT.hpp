//
// Created by Hein Breukers
//
#pragma once

#include "Math.hpp"

#include <cstdint>
#include <array>
#include <complex>
#include <type_traits>
#include <iostream>

namespace CTFFT
{

constexpr double pi = 3.14159265358979323846;

// radix-2 Cooley-Tukey FFT 
template<typename T, size_t size, size_t size_over2 = size/2 >
constexpr std::array<std::complex<T>,size>  FFT(std::array<std::complex<T>,size> in) requires std::is_floating_point_v<T>
{
    if constexpr (size==1)
    {
        return in;
    }
    std::array<std::complex<T>,size_over2> even;
    std::array<std::complex<T>,size_over2> odd;
    for (size_t i = 0; 2UL * i < size; i++)
    {
        even[i] = in[2*i];
        odd[i] = in[2*i+1];
    }

    auto buffer = FFT(std::move(even));
    auto buffer2 = FFT(std::move(odd));

    
    for (size_t k=0; k<(size_over2); ++k)
    {
        const T twiddleComponent = 2*static_cast<T>(pi)/static_cast<T>(size)*static_cast<T>(k);       
        const std::complex<T> twiddleFactor(Internal::cos<T,6>(twiddleComponent), -Internal::sin<T,6>(twiddleComponent));
        auto p = buffer[k];  
        auto q = buffer2[k]*twiddleFactor;
        in[k] = p+q;
        in[k+size_over2] = p-q;
    }
    return in;
}

constexpr size_t log2(size_t n)
{
    return ( (n<2) ? 0 : 1+log2(n/2));
}

template<size_t size,size_t shift = log2(size-1)>
constexpr size_t BitReversal(size_t index)
{
    std::cout<<shift<<'\n';
    unsigned int b=index&0x01;
    b=b<<shift;
    index = index>>1;
    return index|b;
}

template<typename T, size_t size>
void Reorder(std::array<T,size>& in)
{
    for(size_t i=0; i<in.size();++i)
    {

    }
}



// radix-2 Cooley-Tukey FFT 
// TODO no auxilary space/in place -> pass by reference -> change loop index + increment
template<typename T, size_t size, size_t newsize = size, size_t stride = 1, size_t index = 0>
constexpr void  FFT2(std::array<std::complex<T>,size>& __restrict__ in, std::array<std::complex<T>,size>& __restrict__ out) requires std::is_floating_point_v<T>
{
    if constexpr(newsize==1)
    {
        out[index]=in[index];
    }
    else
    {
        FFT2<T,size, newsize/2, stride*2,index>(in,out);
        FFT2<T,size, newsize/2, stride*2,index+stride>(in,out);

        for (size_t k=0; k<newsize/2; ++k)
        {
            const T twiddleComponent = 2*static_cast<T>(pi)/static_cast<T>(newsize)*static_cast<T>(k);
            const std::complex<T> twiddleFactor(Internal::cos<T,6>(twiddleComponent), -Internal::sin<T,6>(twiddleComponent));
            auto p = out[k];
            auto q = out[k+stride]*twiddleFactor;
            out[k] = p+q;
            std::cout<<k<<"+"<<k+size/2<<"W"<<'\n';
            out[k+size/2] = p-q;
            std::cout<<k<<"-"<<k+size/2<<"W"<<'\n';
        }
    }
}
} //namespace CTFFT
