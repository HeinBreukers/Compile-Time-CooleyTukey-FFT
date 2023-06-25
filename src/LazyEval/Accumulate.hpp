#pragma once

#include "Meta.hpp"
#include "../Internal/SIMD/Meta.hpp"

#include <cstddef>
#include <array>
#include <fmt/core.h>
#include <iostream>
#include <algorithm>

namespace Lazy
{

template<typename T,size_t Size>
class traits<Accumulate<T,Size>>
{
public:
    using type = T;
    using evalType = Accumulate<T,Size>;
    static constexpr size_t size = Size;
    static constexpr bool isRef = false;
};

template<typename T,size_t Size>
class Accumulate: public MatrixBase<Accumulate<T,Size>>
{
public:
    using Base =  MatrixBase<Accumulate<T,Size>>;
    using SBase =  internal::SIMD::SIMDTraits::SIMDBaseType;
    using PacketType = internal::SIMD::SIMDTraits::PacketType<T>;
    static constexpr size_t packetWidth = internal::SIMD::SIMDTraits::PacketWidth<T>;

    Accumulate(): Base()
    {
        
    }

    // TODO implement acc in SIMD header
    T get()
    {
        T ret = 0;
        for (size_t i = 0; i < packetWidth; ++i) {
                ret += sum[i];
        }
        return ret;
    }


    template<typename OtherDerived>
    Accumulate(const MatrixBase<OtherDerived>& other) = delete;

    template<typename OtherDerived>
    Accumulate& operator=(const MatrixBase<OtherDerived>& other)
    {
        return Base::operator=(*static_cast<const OtherDerived*>(&other));
    }

    //TODO determine l/r/forward
    void set([[maybe_unused]] size_t index,  const PacketType& val)
    {
        sum = SBase::add(sum,val);
    }

    void setScalar([[maybe_unused]] size_t index, const T& val)
    { 
        sum[0] += val;
    }
private:
    //TODO proper value set instead of static cast
    PacketType sum = SBase::set(static_cast<T>(0));

};



} // namespace Lazy