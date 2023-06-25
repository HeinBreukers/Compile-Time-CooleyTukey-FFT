#pragma once

#include "Meta.hpp"
#include "../Internal/SIMD/Meta.hpp"
#include <fmt/core.h>

namespace Lazy {

template<typename Derived, typename OtherDerived>
class Evaluator
{
public:
    using type = typename traits<Derived>::type;
    using SBase =  internal::SIMD::SIMDTraits::SIMDBaseType;
    using PacketType = internal::SIMD::SIMDTraits::PacketType<type>;

    static void evaluate(Derived& dst, const OtherDerived& src)
    {
        // TODO proper size determination
        const size_t size = traits<OtherDerived>::size; //dst.size();
        const size_t width = SBase::template RegisterWidth<type>();
        // Doesnt work yet with ringbuffer, determine start from index matrix within OperationClass + set start index at first aligned start -> ie multiples of register with
        // Consider if its worth it to allow lazy evaluated ring buffer
        // or only allow aligned inserts into ringbuffer
        //const size_t start = dst.alignedStart(src);
        const size_t start =0;
        const size_t end = start + ((size-start)/width)*width;
        // TODO start and end scalar evaluation instead of simd -> ringbuffer start not multiple of width, or array size not multiple of width

        for(size_t index = 0; index < start; index++)
        {
            dst.setScalar(index, src.template getScalar(index));
        }
        
        for(size_t index = start; index < end; index += width)
        {
            dst.template set(index, src.template get(index));
        }

        for(size_t index = end; index < size; index++)
        {
            dst.setScalar(index, src.template getScalar(index));
        }
        
    }
};

}