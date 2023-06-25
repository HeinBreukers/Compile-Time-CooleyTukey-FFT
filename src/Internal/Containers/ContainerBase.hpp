#pragma once

#include "../SIMD/Meta.hpp"



#include <cstddef>
#include <array>
#include <fmt/ranges.h>
namespace internal
{
namespace containers
{
template<typename T> struct traits;

template<typename Derived>
class ContainerBase
{
public:
    using value_type = typename traits<Derived>::value_type;
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

    constexpr Derived* derived()
    {
        return static_cast<Derived*>(this);
    }

    constexpr Derived* derived() const
    {
        return static_cast<const Derived*>(this);
    }

    // Iterators.
    constexpr iterator begin() noexcept
    { 
        return derived()->begin();
    }

    constexpr const_iterator begin() const noexcept
    {  
        return derived()->begin();
    }

    constexpr iterator end() noexcept
    {
        return derived()->end();
    }

    constexpr const_iterator end() const noexcept
    { 
        return derived()->end();
    }

    // Capacity.
    constexpr size_type
    size() const noexcept 
    {  
        return derived()->size();
    }

    constexpr size_type
    max_size() const noexcept 
    { 
        return derived()->max_size();
    }

    [[nodiscard]] constexpr bool
    empty() const noexcept 
    { 
        return derived()->empty();
    }

    // Element access.
    constexpr reference
    operator[](size_type __n) noexcept
    { 
        return derived()->operator[](__n);
    }

    constexpr const_reference
    operator[](size_type __n) const noexcept
    { 
        return derived()->operator[]( __n);
    }

    constexpr reference
    at(size_type __n)
    { 
        return derived()->at( __n);
    }

    constexpr const_reference
    at(size_type __n) const
    { 
        return derived()->at( __n);
    }

    constexpr reference
    front() noexcept
    { 
        return derived()->front();
    }

    constexpr const_reference
    front() const noexcept
    { 
        return derived()->front();
    }

    constexpr reference
    back() noexcept
    { 
        return derived()->back();
    }

    constexpr const_reference
    back() const noexcept
    { 
        return derived()->back();
    }

    constexpr pointer
    data() noexcept
    { 
        return derived()->data();
    }

    constexpr const_pointer
    data() const noexcept
    { 
        return derived()->data();
    }
};

}
}

