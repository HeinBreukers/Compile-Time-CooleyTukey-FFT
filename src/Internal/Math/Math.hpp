#pragma once

#include <type_traits>
#include <array>

namespace Internal
{

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

// TODO set max N depending on max precision
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
    static constexpr T value([[maybe_unused]] T in)
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
struct fastaccstruct 
{
    static constexpr T value(std::array<T,N>  in)
    {
        std::array<T,N/2> intermediate;
        for(int i=0;i<N/2;++i)
        {
            intermediate[i] = in[i] + in[i+N/2];
        }
        return fastaccstruct<T,N/2>::value(std::move(intermediate));
    }
};

template<typename T>
struct fastaccstruct<T,1>
{
    static constexpr T value(std::array<T,1> in)
    {
        return in[0];
    }
};

// N has to be power of 2
template<typename T, std::size_t N>
constexpr T fastacc(std::array<T,N> in) 
{
    //TODO proper forwarding
    return fastaccstruct<T,N>::value(std::move(in));
}








}// namespace Internal
