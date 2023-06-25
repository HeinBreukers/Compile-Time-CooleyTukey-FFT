#pragma once

#include "../SIMDForwardDeclare.hpp"
#include "AVX256.hpp"

#include <fmt/core.h>

namespace internal
{
namespace SIMD
{
    template<typename T, bool aligned, typename PacketType>
    PacketType AVX256::load(const T *address) {
        if constexpr (aligned) {
            if constexpr (std::is_integral_v<T>) {
                return _mm256_load_si256(address);
            }
            if constexpr (std::is_same_v<T, float>) {
                return _mm256_load_ps(address);
            }
            if constexpr (std::is_same_v<T, double>) {
                return _mm256_load_pd(address);
            }
        } else {
            if constexpr (std::is_integral_v<T>) {
                return _mm256_loadu_si256(address);
            }
            if constexpr (std::is_same_v<T, float>) {
                return _mm256_loadu_ps(address);
            }
            if constexpr (std::is_same_v<T, double>) {
                return _mm256_loadu_pd(address);
            }
        }
    }

    template<typename T, bool aligned, typename PacketType>
    void AVX256::store(T *address, const PacketType& packet) {
        if constexpr (aligned) {
            if constexpr (std::is_integral_v<T>) {
                _mm256_store_si256(address, packet);
            } else if constexpr (std::is_same_v<T, float>) {
                _mm256_store_ps(address, packet);
            } else if constexpr (std::is_same_v<T, double>) {
                _mm256_store_pd(address, packet);
            }
        } else {
            if constexpr (std::is_integral_v<T>) {
                _mm256_storeu_si256(address, packet);
            } else if constexpr (std::is_same_v<T, float>) {
                _mm256_storeu_ps(address, packet);
            } else if constexpr (std::is_same_v<T, double>) {
                _mm256_storeu_pd(address, packet);
            }
        }
    }

    template<typename T, typename PacketType, bool aligned>
    PacketType AVX256::set(T val){
        if constexpr (std::is_same_v<T, float>) {
            return _mm256_set1_ps(val);
        }
        if constexpr (std::is_same_v<T, double>) {
            return _mm256_set1_pd(val);
        }
    }
}
}