#pragma once

namespace internal
{
namespace SIMD
{
    template<typename Derived> class SIMDBase;
    class AVX256;
    template<typename SIMDType, typename T> class PacketTypeStruct;
    template<typename SIMDType> class alignmentStruct;
}
}