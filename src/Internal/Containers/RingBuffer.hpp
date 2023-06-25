#pragma once

#include "ContainerBase.hpp"
#include <fmt/ranges.h>

namespace internal
{
namespace containers
{

template<typename T,size_t Size, size_t Alignment>
class RingBuffer;

template<typename T, size_t Size, size_t Alignment>
struct traits<RingBuffer<T,Size,Alignment>>
{
    typedef T value_type;
};


template<typename T,size_t Size, 
size_t Alignment = internal::SIMD::SIMDTraits::alignment>
class RingBuffer: public ContainerBase<RingBuffer<T,Size,Alignment>>
{
public:
    using value_type = T;
    using pointer = value_type*;
    typedef const value_type*                       const_pointer;
    typedef value_type&                   	      reference;
    typedef const value_type&             	      const_reference;
    typedef std::size_t                    	      size_type;
    typedef std::ptrdiff_t                   	      difference_type;
    

    class iterator: public std::iterator<
                        std::bidirectional_iterator_tag,   // iterator_category
                        value_type,                      // value_type
                        std::ptrdiff_t,                      // difference_type
                        const_pointer,               // pointer
                        reference                       // reference
                                      >{
        const_pointer m_ptr;
        const_pointer m_begin;
        const_pointer m_end;
        size_type m_index;
    public:
        explicit iterator(const_pointer ptr, const_pointer begin,const_pointer end, size_type index) : 
        m_ptr(ptr),m_begin(begin),m_end(end),m_index(index) {}

        const_reference operator*() const { return *m_ptr; }
        const_pointer operator->() { return m_ptr; }
        // Prefix increment
        iterator& operator++() 
        { 
            ++m_ptr;
            ++m_index;
            if(m_ptr==m_end)
            {
                m_ptr=m_begin;
            }
            return *this; 
        }  
        // Postfix increment
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
        // Prefix decrement
        iterator& operator--() 
        { 
            --m_ptr;
            --m_index;
            if(m_ptr==m_begin)
            {
                m_ptr=m_end;
            }
            return *this; 
        }  
        // Postfix decrement
        iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }
        bool operator==(iterator other) const {return m_ptr == other.m_ptr&&m_index=other.m_index;}
        bool operator!=(iterator other) const {return m_ptr != other.m_ptr||m_index!=other.m_index; }
    };

    typedef const iterator			      const_iterator;
    typedef std::reverse_iterator<iterator>	      reverse_iterator;
    typedef std::reverse_iterator<const_iterator>   const_reverse_iterator;

    using SBase =  internal::SIMD::SIMDTraits::SIMDBaseType;
    using PacketType = internal::SIMD::SIMDTraits::PacketType<value_type>;
    static constexpr size_t PacketWidth = internal::SIMD::SIMDTraits::PacketWidth<value_type>;

    RingBuffer() = default;

    RingBuffer(const std::array<T,Size>& in):
    arr(in)
    {}

    //begin and end pointer are the same in a ring buffer, therefore an index value is added to the iterator to differentiate between begin and end;
    iterator begin() {return iterator(&arr[startPtr],arr.begin(),arr.end(),0);}
    iterator end() { return iterator(&arr[startPtr],arr.begin(),arr.end(),arr.size());}

    constexpr const_iterator begin() const noexcept
    {  
        return iterator(&arr[startPtr],arr.begin(),arr.end(),0);
    }

    constexpr const_iterator end() const noexcept
    { 
        return iterator(&arr[startPtr],arr.begin(),arr.end(),arr.size());
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
    operator[](long int __n) noexcept
    { 
        return arr[calculateIndex(startPtr,__n)];
    }

    constexpr const_reference
    operator[](long int __n) const noexcept
    { 
        return arr[calculateIndex(startPtr,__n)];
    }

    constexpr reference
    at(long int __n)
    { 
        return arr.at(calculateIndex(startPtr,__n));
    }

    constexpr const_reference
    at(long int __n) const
    { 
        return arr.at( calculateIndex(startPtr,__n));
    }

    constexpr reference
    operator[](size_type __n) noexcept
    { 
        return arr[calculateIndex(startPtr,__n)];
    }

    constexpr const_reference
    operator[](size_type __n) const noexcept
    { 
        return arr[calculateIndex(startPtr,__n)];
    }

    constexpr reference
    at(size_type __n)
    { 
        return arr.at(calculateIndex(startPtr,__n));
    }

    constexpr const_reference
    at(size_type __n) const
    { 
        return arr.at( calculateIndex(startPtr,__n));
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

    void put(PacketType&& val)
    {
        SBase::store<T,false>(&arr[calculateIndex(startPtr,-static_cast<long>(PacketWidth))], val);
        startPtr = (startPtr+ Size-PacketWidth)%Size;
    }

    template<size_t inSize>
    void put(const std::array<T,inSize>& val)
    {
        static_assert(inSize<Size, "insertion does not fit into RingBuffer");
        static_assert((inSize%PacketWidth)==0, "insertion is not multiple of SIMD packetsize");
        for(int index = inSize - PacketWidth; index >= 0; index -= static_cast<int>(PacketWidth))
        {
            //TODO make aligned requirements
            put(SBase::load<T,false>(&val[static_cast<size_t>(index)]));
        }
    }

    static constexpr size_type calculateIndex(size_type ptr, long int index)
    {
        auto iptr = static_cast<long int>(ptr);
        auto iSize = static_cast<long int>(Size);
        long int ret = iptr + iSize + index;
        ret %= iSize;
        return static_cast<size_type>(ret);
    }

    static constexpr size_type calculateIndex(size_type ptr, size_type index)
    {
        size_type ret = ptr + index;
        ret %= Size;
        return ret;
    }


private:
    alignas(Alignment) std::array<T,Size> arr;
    std::array<T,PacketWidth> padding;

    size_t startPtr = 0;
};

}
}


