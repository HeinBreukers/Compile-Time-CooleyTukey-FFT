#pragma once

#include "Meta.hpp"
#include "AVX256/AVX256.hpp"
#include "Arithmetic.hpp"
#include "LoadStore.hpp"


#include <type_traits>
#include <algorithm>

namespace internal
{
namespace SIMD
{
    template<>
    struct PacketTypeStruct<AVX256, float>
    {
        using type = __m256;
    };

    template<>
    struct PacketTypeStruct<AVX256, double>
    {
        using type = __m256d;
    };

    template<>
    struct PacketTypeStruct<AVX256, int>
    {
        using type = __m256i;
    };

    template<>
    struct alignmentStruct<AVX256>
    {
        static constexpr size_t size = 32;
    };

    struct SIMDTraits
    {
        using type = AVX256;
        using SIMDBaseType = SIMDBase<type>;
        template<typename T>
        using PacketType = typename PacketTypeStruct<type,T>::type;
        template<typename T>
        static constexpr size_t PacketWidth = type::RegisterWidth<T>();
        static constexpr size_t alignment = alignmentStruct<type>::size;
    };
}
}