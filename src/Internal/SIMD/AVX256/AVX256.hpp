#pragma once

#include "../SIMDForwardDeclare.hpp"
#include "../SIMDBase.hpp"

#include <immintrin.h>


namespace internal
{
namespace SIMD
{
    class AVX256: public SIMDBase<AVX256>
    {
    public:
        // TODO const ref arguments
        // TODO requires is_same_v<T,__m256>
        template<typename T>
        using PType = internal::SIMD::PacketTypeStruct<AVX256,T>::type;

        template<typename T, bool aligned, typename PacketType = PType<T>>
        static PacketType load(const T *address);

        template<typename T, bool aligned, typename PacketType = PType<T>>
        static void store(T *address, const PacketType &packet);

        template<typename T, typename PacketType = PType<T>, bool aligned = true>
        static PacketType set(T val);

        //TODO pass by ref or forward?
        static auto add(auto&& left, auto&& right);

        static auto sub(auto&&  left, auto&& right);

        static auto mul(auto&& left, auto&& right);

        template<typename T>
        static constexpr size_t RegisterWidth();
    };

    template<typename T>
    constexpr size_t AVX256::RegisterWidth() {
        constexpr size_t AVXRegisterSize = 256;

        if constexpr (std::is_same_v<T, double>) {
            constexpr size_t doubleSize = 64;
            return AVXRegisterSize / doubleSize;
        } else if constexpr (std::is_same_v<T, float>) {
            constexpr size_t floatSize = 32;
            return AVXRegisterSize / floatSize;
        }
        return 0;
    }
} // namespace SIMD
} // namespace Internal