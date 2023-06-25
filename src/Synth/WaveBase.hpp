#pragma once

#include <math.h>
#include <ratio>
#include <array>

namespace Synth
{

template<typename Derived>
class WaveBase
{
public:

    template<typename U>
    auto render(U&& frequency)
    {
        return static_cast<Derived*>(this)->render(std::forward<U>(frequency));
    }

private:
    
};


// TODO include into WaveBase
template<typename T,size_t Size, typename Derived>
constexpr std::array<T,Size> BasicWaveBase(T frequency, WaveBase<Derived>& wave)
{
    std::array<T,Size> out;
    for(int i=0;i<Size;++i)
    {
        out[i] = wave.render(frequency);
    }
    return out;
}

template<size_t Size, typename Derived>
constexpr auto BasicWave(auto frequency, WaveBase<Derived>& wave)
{
    return BasicWaveBase<decltype(frequency),Size,Derived>(std::move(frequency),wave);
}

}