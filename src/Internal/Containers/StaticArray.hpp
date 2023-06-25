#pragma once

#include "ContainerBase.hpp"

namespace internal
{
namespace containers
{

template<typename T,size_t Size, size_t Alignment>
class StaticArray;

template<typename T, size_t Size, size_t Alignment>
struct traits<StaticArray<T,Size,Alignment>>
{
    typedef T value_type;
};

//TODO include alignment
template<typename T,size_t Size, 
size_t Alignment = internal::SIMD::SIMDTraits::alignment>
class StaticArray: public ContainerBase<StaticArray<T,Size,Alignment>>
{
public:
    using value_type = T;
    typedef value_type*			      pointer;
    typedef const value_type*                       const_pointer;
    typedef value_type&                   	      reference;
    typedef const value_type&             	      const_reference;
    typedef value_type*          		      iterator;
    typedef const value_type*			      const_iterator;
    typedef std::size_t                    	      size_type;
    typedef std::ptrdiff_t                   	      difference_type;
    typedef std::reverse_iterator<iterator>	      reverse_iterator;
    typedef std::reverse_iterator<const_iterator>   const_reverse_iterator;

    StaticArray() = default;

    StaticArray(const std::array<T,Size>& in):
    arr(in)
    {}

    // Iterators.
    constexpr iterator begin() noexcept
    { 
        return arr.begin();
    }

    constexpr const_iterator begin() const noexcept
    {  
        return arr.begin();
    }

    constexpr iterator end() noexcept
    {
        return arr.end();
    }

    constexpr const_iterator end() const noexcept
    { 
        return arr.end();
    }

    // Capacity.
    constexpr size_type
    size() const noexcept 
    {  
        return arr.size();
    }

    constexpr size_type
    max_size() const noexcept 
    { 
        return arr.max_size();
    }

    [[nodiscard]] constexpr bool
    empty() const noexcept 
    { 
        return arr.empty();
    }


    // Element access.
    constexpr reference
    operator[](size_type __n) noexcept
    { 
        return arr[__n];
    }

    constexpr const_reference
    operator[](size_type __n) const noexcept
    { 
        return arr[__n];
    }

    constexpr reference
    at(size_type __n)
    { 
        return arr.at( __n);
    }

    constexpr const_reference
    at(size_type __n) const
    { 
        return arr.at( __n);
    }

    constexpr reference
    front() noexcept
    { 
        return arr.front();
    }

    constexpr const_reference
    front() const noexcept
    { 
        return arr.front();
    }

    constexpr reference
    back() noexcept
    { 
        return arr.back();
    }

    constexpr const_reference
    back() const noexcept
    { 
        return arr.back();
    }

    constexpr pointer
    data() noexcept
    { 
        return arr.data();
    }

    constexpr const_pointer
    data() const noexcept
    { 
        return arr.data();
    }

private:
    alignas(Alignment) std::array<T,Size> arr;
};

}
}