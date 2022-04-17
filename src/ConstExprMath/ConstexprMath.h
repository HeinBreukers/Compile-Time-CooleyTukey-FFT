#pragma once

#include <type_traits>

template<typename X, typename N>
constexpr X pow(X in, N pow) requires std::is_integral_v<N>
{
    X out = 1;
    for(N i=0; i<pow; ++i)
    {
        out*=in;
    }
    return out;
}

template<typename X>
constexpr X factorial(X in) requires std::is_integral_v<X>
{
    X out = 1;
    while(in>1)
    {
        out*=in;
        --in;
    }
    return out;
}

template<typename T, std::size_t N>
struct cosstruct
{
    static constexpr T value(T in) requires std::is_floating_point_v<T>
    {
        if constexpr((N%2))
        {
            return cosstruct<T,N-1>::value(in)-pow(in,N*2)/factorial(N*2);
        }
        return cosstruct<T,N-1>::value(in)+pow(in,N*2)/factorial(N*2);
    }
};

template<typename T>
struct cosstruct<T,0>
{
    static constexpr T value(T in)
    {
        return 1;
    }
};

template<typename T, std::size_t N = 4>
constexpr auto cos = cosstruct<T,N>::value;


template<typename T, std::size_t N>
struct sinstruct 
{
    static constexpr T value(T in) requires std::is_floating_point_v<T>
    {
        if constexpr((N%2))
        {
            return sinstruct<T,N-1>::value(in)-pow(in,N*2+1)/factorial(N*2+1);
        }
        return sinstruct<T,N-1>::value(in)+pow(in,N*2+1)/factorial(N*2+1);
    }
};

template<typename T>
struct sinstruct<T,0>
{
    static constexpr T value(T in)
    {
        return in;
    }
};

template<typename T, std::size_t N = 4 >
constexpr auto sin = sinstruct<T,N>::value;


template<typename T, std::size_t N>
struct tanstruct 
{
    static constexpr T value(T in) requires std::is_floating_point_v<T>
    {
        return tanstruct<T,N-1>::value(in)+N*pow(in,N*2-1)/factorial(N*2+1);
    }
};

template<typename T>
struct tanstruct<T,0>
{
    static constexpr T value(T in)
    {
        return in;
    }
};

template<typename T,std::size_t N = 4 >
constexpr auto tan = tanstruct<T,N>::value;




