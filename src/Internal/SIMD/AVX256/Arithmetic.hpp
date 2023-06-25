#pragma once

#include "../SIMDForwardDeclare.hpp"
#include "AVX256.hpp"

#include <type_traits>

namespace internal
{
namespace SIMD
{

    

    auto AVX256::add(auto&& left,auto&& right)
    {
        using Tleft = std::decay_t<decltype(left)>;
        using Tright = std::decay_t<decltype(right)>;
        static_assert(std::is_same_v<Tleft,Tright>, "incompatible datatypes");
        // Warning prevents avx types from being template parameters to enforce alignment/prevent alignment issues
        // i.e. std::vector<__m256> -> vector members arent necessarily correctly aligned
        // however here the type is used to deduce the correct avx function and no aligment issues will occur
        // thus warning can be safely ignored
        // TODO make warning ignore compiler agnostic + macro
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wignored-attributes"
        if constexpr(std::is_same_v<Tleft,__m256>)
        #pragma GCC diagnostic pop
        {
            return _mm256_add_ps(std::forward<decltype(left)>(left),std::forward<decltype(right)>(right));
        }
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wignored-attributes"
        if constexpr(std::is_same_v<Tleft,__m256d>)
        #pragma GCC diagnostic pop
        {
            return _mm256_add_pd(std::forward<decltype(left)>(left),std::forward<decltype(right)>(right));
        }

        // TODO make meta functions for asserts
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wignored-attributes"
        static_assert(std::is_same_v<Tleft,__m256d>||std::is_same_v<Tleft,__m256>,"type not supported");
        #pragma GCC diagnostic pop
    }

    auto AVX256::sub(auto&& left, auto&& right)
    {
        using Tleft = std::decay_t<decltype(left)>;
        using Tright = std::decay_t<decltype(right)>;
        static_assert(std::is_same_v<Tleft,Tright>, "incompatible datatypes");

        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wignored-attributes"
        if constexpr(std::is_same_v<Tleft,__m256>)
        #pragma GCC diagnostic pop
        {
            return _mm256_sub_ps(std::forward<decltype(left)>(left),std::forward<decltype(right)>(right));
        }
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wignored-attributes"
        if constexpr(std::is_same_v<Tleft,__m256d>)
        #pragma GCC diagnostic pop
        {
            return _mm256_sub_pd(std::forward<decltype(left)>(left),std::forward<decltype(right)>(right));
        }
    }

    auto AVX256::mul(auto&& left, auto&& right)
    {
        using Tleft = std::decay_t<decltype(left)>;
        using Tright = std::decay_t<decltype(right)>;
        static_assert(std::is_same_v<Tleft,Tright>, "incompatible datatypes");

        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wignored-attributes"
        if constexpr(std::is_same_v<Tleft,__m256>)
        #pragma GCC diagnostic pop
        {
            return _mm256_mul_ps(std::forward<decltype(left)>(left),std::forward<decltype(right)>(right));
        }
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wignored-attributes"
        if constexpr(std::is_same_v<Tleft,__m256d>)
        #pragma GCC diagnostic pop
        {
            return _mm256_mul_pd(std::forward<decltype(left)>(left),std::forward<decltype(right)>(right));
        }
    }

}
}