#pragma once

#include <fmt/ranges.h>
#include <array>
#include <vector>

namespace Synth
{

template<size_t Y>
class Graph
{
public:
    explicit Graph(double amplitude):
    ratio(static_cast<float>(amplitude*2)/static_cast<float>(Y-1))
    {
    }

    template<typename T,size_t X>
    void add(std::array<T,X> wave) noexcept
    {
        for(int i = 0; i<X;++i)
        {
            auto val = static_cast<int>(wave[i]/ratio);
            std::array<char,Y> waveRender;

            for(int j = 0; j<Y;++j)
            {
                waveRender[j] = ' '; 
            }
            waveRender[val+(Y-1)/2] = '*';
            matrix.push_back(waveRender);
        }
    }

    void render() noexcept
    {
        for(int i = Y-1; i>=0;--i)
        {
            for(int j = 0; j<matrix.size();++j)
            {
                fmt::print("{}", matrix[j][i]);
            }
            fmt::print("\n");
        }
    }


private:
    std::vector<std::array<char,Y>> matrix;
    float ratio;
};




    
}