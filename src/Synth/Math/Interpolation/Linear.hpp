#pragma once

namespace Interpolation
{
template<typename T>
T linear(T fraction, T left, T right)
{
    return (1-fraction)*left+fraction*right;
}


}