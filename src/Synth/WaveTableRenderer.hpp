#pragma once

#include "WaveBase.hpp"
#include "WaveTable.hpp"
#include "Interpolation/Linear.hpp"

#include <array>
#include <memory>

enum class InterpolationEnum
{
    None,
    Linear
};

namespace Synth
{

template<typename T, size_t Size, InterpolationEnum Interpolation_V = InterpolationEnum::None>
class WaveTableRenderer: public WaveBase<WaveTableRenderer<T,Size,Interpolation_V>>
{
public:
    template <typename U>
    constexpr explicit WaveTableRenderer(U&& sampleRate, std::shared_ptr<WaveTable<T,Size>> waveTable):
    m_sampleRate(std::forward<U>(sampleRate)),
    m_waveTable(std::move(waveTable))
    {}

    [[nodiscard]] constexpr T render(T frequency)
    {
        T out;

        if constexpr(Interpolation_V == InterpolationEnum::Linear)
        {
            auto low  = static_cast<int>(m_phase);
            auto high = static_cast<int>(m_phase)+1;
            if(high>=Size)
            {
                high=0;
            }
            auto ratio = m_phase-low;
            out = Interpolation::linear(ratio,m_waveTable.get()[0][low],m_waveTable.get()[0][high]);
        }
        else
        {
            out = m_waveTable.get()[0][static_cast<int>(m_phase)];
        }
        // TODO phase increment can be determined at construction
        m_phase += static_cast<T>(Size)*frequency/m_sampleRate;
        // TODO modulo -> implement templated modulo
        while(m_phase>=Size)
        {
            m_phase -= Size;
        }
    
        return out;
    }

    typedef T type;
private:
    T m_sampleRate;
    std::shared_ptr<WaveTable<T,Size>> m_waveTable;
    // TODO make render and wavetable render independent
    T m_phase = 0;
};

}