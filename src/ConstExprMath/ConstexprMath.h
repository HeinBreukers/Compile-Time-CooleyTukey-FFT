#pragma once

constexpr double pow(double in, int pow)
{
    double out = in;
    for(int i=0; i<pow; ++i)
    {
        out*=in;
    }
    return out;
}

constexpr double factorial(double in)
{
    double out = in;
    while(in>1)
    {
        out*=(in-1);
        --in;
    }
    return out;
}

constexpr double cos(double in)
{
    return 1-pow(in,2)/factorial(2)+pow(in,4)/factorial(4)-pow(in,6)/factorial(6)+pow(in,8)/factorial(8);
}

constexpr double sin(double in)
{
    return in-pow(in,3)/factorial(3)+pow(in,5)/factorial(5)-pow(in,7)/factorial(7)+pow(in,9)/factorial(9);
}

