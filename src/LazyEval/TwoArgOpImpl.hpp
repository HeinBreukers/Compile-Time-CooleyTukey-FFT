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
class TwoArgOpImplBase
{
public:
    template<typename T>
    static auto operateScalar(T&& left, T&& right)
    {
        return Derived::operateScalar(std::forward<T>(left), std::forward<T>(right));
    }

    template<typename T>
    static auto operate(T&& left, T&& right)
    {
        return Derived::operate(std::forward<T>(left), std::forward<T>(right));
    }

};


// TODO move template to method?
template<typename T>
class OpImplSum: TwoArgOpImplBase<OpImplSum<T>>
{
public:

    template<typename LHS, typename RHS>
    using type = LHS::type;
    template<typename LHS, typename RHS>
    using returnType =  LHS;
    template<typename LHS, typename RHS>
    using evalType =  LHS;

    template<typename LHS, typename RHS>
    constexpr static size_t rows = LHS::rows;
    template<typename LHS, typename RHS>
    constexpr static size_t cols = LHS::cols;
    template<typename LHS, typename RHS>
    static constexpr size_t size = LHS::size;

    static constexpr bool evaluate = false;
     
    static auto operateScalar(const T& left,const T& right)
    {
        return left + right;
    }

    
    using SBase =  internal::SIMD::SIMDTraits::SIMDBaseType;
    using PacketType = internal::SIMD::SIMDTraits::PacketType<T>;

    static auto operate(const PacketType& left,const PacketType& right)
    {
        return SBase::add(left,right);
    }

};

// Hadamard product
template<typename T>
class OpImplSub: TwoArgOpImplBase<OpImplSub<T>>
{
public:
    template<typename LHS, typename RHS>
    using type = LHS::type;
    template<typename LHS, typename RHS>
    using returnType =  LHS;
    template<typename LHS, typename RHS>
    using evalType =  LHS;

    template<typename LHS, typename RHS>
    constexpr static size_t rows = LHS::rows;
    template<typename LHS, typename RHS>
    constexpr static size_t cols = LHS::cols;
    template<typename LHS, typename RHS>
    static constexpr size_t size = LHS::size;

    static constexpr bool evaluate = false;
     
    static auto operateScalar(const T& left,const T& right)
    {
        return left - right;
    }

    using SBase =  internal::SIMD::SIMDBase<internal::SIMD::SIMDTraits::type>;
    using PacketType = internal::SIMD::PacketTypeStruct<internal::SIMD::SIMDTraits::type,T>::type;

    static auto operate(const PacketType& left,const PacketType& right)
    {
        return SBase::sub(left,right);
    }

};


template<typename T>
class OpImplMul: TwoArgOpImplBase<OpImplMul<T>>
{
public:
    template<typename LHS, typename RHS>
    using type = LHS::type;
    template<typename LHS, typename RHS>
    using returnType =  LHS;
    template<typename LHS, typename RHS>
    using evalType =  LHS;

    template<typename LHS, typename RHS>
    constexpr static size_t rows = LHS::rows;
    template<typename LHS, typename RHS>
    constexpr static size_t cols = LHS::cols;
    template<typename LHS, typename RHS>
    static constexpr size_t size = LHS::size;

    static constexpr bool evaluate = false;
     
    static auto operateScalar(const T& left,const T& right)
    {
        return left * right;
    }

    using SBase =  internal::SIMD::SIMDBase<internal::SIMD::SIMDTraits::type>;
    using PacketType = internal::SIMD::PacketTypeStruct<internal::SIMD::SIMDTraits::type,T>::type;

    static auto operate(const PacketType& left,const PacketType& right)
    {
        return SBase::mul(left,right);
    }
};





}