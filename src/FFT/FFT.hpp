//
// Created by Hein Breukers
//
#pragma once

#include "ConstexprMath.h"
#include <cstdint>

namespace CTFFT
{
class Complex
{
public:
  Complex()=default;
  constexpr explicit Complex(double real, double imag):Real(real),Imag(imag){}
  double Real = 0;
  double Imag = 0;
};


template<unsigned int N>
struct ComplexArray {
  Complex arr[N];
};

constexpr Complex add(const Complex& in, const Complex& in2){return Complex(in.Real+in2.Real,in.Imag+in2.Imag);}
constexpr Complex sub(const Complex& in, const Complex& in2){return Complex(in.Real-in2.Real, in.Imag-in2.Imag);}
constexpr Complex multiply(const Complex& in, const Complex& in2){return Complex(in.Real*in2.Real-in.Imag*in2.Imag, in.Real*in2.Imag + in.Imag*in2.Real);}

constexpr double pi = 3.14159265;

// Cooley-Tukey FFT
template<unsigned int size>
constexpr ComplexArray<size> FFT(const ComplexArray<size>& in, const int32_t cursize, const int32_t stride, const int32_t begin = 0)
{
    ComplexArray<size> out;
    if (cursize==1)
    {
      	out.arr[0] = in.arr[begin];
        return out;
    }
    const unsigned int size_over2 = cursize>>1;
    const unsigned int stride_times2 = stride<<1;
    ComplexArray<size> buffer= {};
    ComplexArray<size> buffer2= {};
    buffer = FFT<size>(in, size_over2, stride_times2, begin);
    buffer2 = FFT<size>(in, size_over2, stride_times2, begin +stride);

    
    for (int k =0; k<(size_over2); k+=stride)
    {
        const double calc = 2*pi/static_cast<double>(cursize)*static_cast<double>(k);       
        Complex t(cos(calc), -sin(calc));
        auto p = buffer.arr[k];  
        auto q = multiply(buffer2.arr[k],t);
        out.arr[k] = add(p,q);
        out.arr[k+size_over2] = sub(p,q);
    }
    return out;
}
} //namespace end
