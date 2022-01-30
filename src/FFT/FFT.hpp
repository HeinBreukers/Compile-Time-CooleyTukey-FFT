//
// Created by Hein Breukers
//
#pragma once

#include <math.h>

namespace CTFFT
{
class Complex
{
public:
  Complex()=default;
  constexpr Complex(float real, float imag):Real(real),Imag(imag){}
  float Real = 0;
  float Imag = 0;
};


template<uint N>
struct ComplexArray {
  Complex arr[N];
};

Complex add(const Complex& in, const Complex& in2){return Complex(in.Real+in2.Real,in.Imag+in2.Imag);}
Complex sub(const Complex& in, const Complex& in2){return Complex(in.Real-in2.Real, in.Imag-in2.Imag);}
Complex multiply(const Complex& in, const Complex& in2){return Complex(in.Real*in2.Real-in.Imag*in2.Imag, in.Real*in2.Imag + in.Imag*in2.Real);}

constexpr float pi = 3.14159265;

// Cooley-Tukey FFT
template<uint size, uint cursize, uint stride>
constexpr void FFT(const ComplexArray<size>& in, ComplexArray<size>&  out, const int32_t sizea, const int32_t stridea, const int32_t begin = 0)
{
    if (cursize==1)
    {
      	out.arr[0] = in.arr[begin];
        return;
    }
    constexpr uint size_over2 = cursize/2;
    constexpr uint stride_times2 = stride*2;
    ComplexArray<size> buffer= {};
    ComplexArray<size> buffer2= {};
    FFT<size, size_over2,stride_times2>(in, buffer, size_over2, stride_times2, begin);
    FFT<size, size_over2,stride_times2>(in, buffer2, size_over2, stride_times2, begin +stride);

    
    for (int k =0; k<(size_over2); k+=stride)
    {
        const float calc = 2*pi/static_cast<float>(cursize)*static_cast<float>(k);       
        Complex t(cos(calc), -sin(calc));
        auto p = buffer.arr[k];  
        auto q = multiply(buffer2.arr[k],t);
        out.arr[k] = add(p,q);
        out.arr[k+size_over2] = sub(p,q);
    }
    return;
}
} //namespace end
