#pragma once

#include <cstddef>
#include <type_traits>
#include <utility>

#include "SIMDForwardDeclare.hpp"

namespace internal
{
namespace SIMD
{
    template<typename Derived>
    class SIMDBase
    {
    public:
        template<typename T, bool aligned>
        static auto load(const T* ptr) 
        {
            return Derived::template load<T,aligned>(ptr);
        }

        template<typename T, bool aligned>
        static void store(T* ptr, const auto& simdRegister) 
        {
            Derived::template store<T,aligned>(ptr,simdRegister);
        }

        template<typename T>
        static auto set(T&& val)
        {
            return Derived::set(std::forward<T>(val));
        }

        static auto add(auto&& left, auto&& right)
        {
            return Derived::add(std::forward<decltype(left)>(left),std::forward<decltype(right)>(right));
        }

        static auto sub(auto&& left, auto&& right) 
        {
            return Derived::sub(std::forward<decltype(left)>(left),std::forward<decltype(right)>(right));
        }

        static auto mul(auto&& left, auto&& right) 
        {
            return Derived::mul(std::forward<decltype(left)>(left),std::forward<decltype(right)>(right));
        }

        template<typename T>
        static constexpr size_t RegisterWidth()
        {
            return Derived::template RegisterWidth<T>();
        }


    };



}
}