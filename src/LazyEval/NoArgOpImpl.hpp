#pragma once

#include "Meta.hpp"
#include "../Internal/SIMD/Meta.hpp"

//#include "Scalar.hpp"

#include <cstddef>
#include <array>
#include <type_traits>
#include <fmt/core.h>

namespace Lazy
{


template<typename Derived>
class NoArgOpImplBase
{
public:

    template<typename T>
    static auto operateScalar()
    {
        return Derived::operateScalar();
    }

    template<typename T>
    static auto operate()
    {
        return Derived::operate();
    }

};

template<typename T>
class NoArgOpImplScalar: NoArgOpImplBase<OpImplMul<T>>
{
public:
    using type = T;
    static constexpr bool isRef = false;

    explicit NoArgOpImplScalar(const T& val) : m_val(val) {}

    auto operateScalar([[maybe_unused]] size_t index) const
    {
        return m_val;
    }

    using SBase =  internal::SIMD::SIMDBase<internal::SIMD::SIMDTraits::type>;
    using PacketType = internal::SIMD::PacketTypeStruct<internal::SIMD::SIMDTraits::type,T>::type;

    // TODO look into reducing set operation but instead return vector register? what is more efficient load vs set
    auto operate([[maybe_unused]] size_t index) const
    {
        return SBase::set(m_val);
    }

  const T m_val;
};

template<typename Derived,size_t Start, size_t End>
class NoArgOpImplSubset: NoArgOpImplBase<NoArgOpImplSubset<Derived, Start, End>>
{
public:
    using type = traits<Derived>::type;
    using returnType =  Derived;
    using evalType =  Derived;

    static constexpr size_t rows = traits<Derived>::rows;
    static constexpr size_t cols = traits<Derived>::cols;
    static constexpr size_t size = End-Start;
    static constexpr bool isRef = false;
    static constexpr bool allignedAccess = false;

    explicit NoArgOpImplSubset(const Derived& der) : derived(der) {}

    auto operateScalar([[maybe_unused]] size_t index) const
    {
        return derived.getScalar(index+Start);
    }

    auto operate([[maybe_unused]] size_t index) const
    {
        return derived.template get<allignedAccess>(index+Start);
    }
private:
    selectQualifier<Derived,traits<Derived>::isRef>::type derived;
};

}