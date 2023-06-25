#pragma once

#include <array>
#include <type_traits>
#include <immintrin.h>

#include <fmt/ranges.h>

namespace Math
{

template<typename T>
constexpr size_t GetWidthAVX()
{
    constexpr size_t AVXRegisterSize = 256;

    if constexpr (std::is_same_v<T,double>)
    {
        constexpr size_t doubleSize = 64;
        return AVXRegisterSize/doubleSize;
    }
    else if constexpr (std::is_same_v<T,float>)
    {
        constexpr size_t floatSize = 32;
        return AVXRegisterSize/floatSize;
    }
    return 0;
}

template<typename T, size_t Size, size_t Width = GetWidthAVX<T>()> 
T multiplyAcc(const std::array<T,Size>& data, const std::array<T,Size>& coefficients)
{
    size_t i;
    T y = 0;
    
    if constexpr(std::is_same_v<T,double>)
    {
        __m256d sum = {0.0, 0.0, 0.0, 0.0};
        for (i = 0; i < Size; i += Width) {
                __m256d va = _mm256_load_pd(&data[i]);
                __m256d vb = _mm256_load_pd(&coefficients[i]);
                sum = _mm256_fmadd_pd (va, vb, sum);
        }
        
        for (i = 0; i < Width; i++) {
                y += sum[i];
        }
    }
    else if constexpr(std::is_same_v<T,float>)
    {
        __m256 sum = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};        
        for (i = 0; i < Size; i+=Width) {
                __m256 va = _mm256_load_ps(&data[i]);
                __m256 vb = _mm256_load_ps(&coefficients[i]);
                sum = _mm256_fmadd_ps (va, vb, sum);
        }
        
        for (i = 0; i < Width; i++) {
                y += sum[i];
        }
    }
    return y;
}

}