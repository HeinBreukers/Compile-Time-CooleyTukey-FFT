#pragma once

#include "WaveBase.hpp"
#include "WaveTable.hpp"
#include "Interpolation/Linear.hpp"

#include <math.h>
#include <memory>
#include <array>



namespace Synth
{

template<typename T>
class SineWave: public WaveBase<SineWave<T>>
{
public:
    typedef T type;

    template<typename U>
    explicit constexpr SineWave(U&& sampleRate):
    m_sampleRate(std::forward<U>(sampleRate))
    {

    }

    [[nodiscard]] constexpr T render(T frequency)
    {
        T out;
        out=sin(m_phase);
        m_phase += 2.0*M_PI*frequency/m_sampleRate;
        if(m_phase>=2.0*M_PI)
        {
            m_phase -= 2.0*M_PI;
        }
    
        return out;
    }

    template<size_t Size>
    [[nodiscard]] static constexpr auto table()
    {
        std::array<T,Size> wt;
        T phase = 0;
        for(size_t i=0; i<Size;++i)
        {
            wt[i]=sin(phase);
            phase += 2.0*M_PI/static_cast<T>(Size);

        }
        return std::make_unique<WaveTable<T,Size>>(std::move(wt));
    }

private:
    T m_sampleRate;
    T m_phase = 0;
};



}