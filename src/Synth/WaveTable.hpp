#pragma once

#include <array>

namespace Synth
{

template<typename T, size_t Size>
class WaveTable
{
public:
    template <typename W>
    explicit constexpr WaveTable(W&& waveTable):
    m_waveTable(std::forward<W>(waveTable))
    {}

    T operator [](size_t index) const {return m_waveTable[index];}
    T& operator [](size_t index) {return m_waveTable[index];}

    constexpr size_t
      size() const noexcept { return Size; }

    typedef T type;
private:
    std::array<T,Size> m_waveTable;
};

}