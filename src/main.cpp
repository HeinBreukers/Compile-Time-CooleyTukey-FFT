#include "FFT.hpp"

#include <iostream>

using namespace CTFFT;

int main() {
  constexpr int size = 8;
  constexpr int stride = 1;
  constexpr ComplexArray<size> in = {Complex(1,0),Complex(2,-1), Complex(0,-1), Complex(-1,2),Complex(1,0),Complex(2,-1), Complex(0,-1), Complex(-1,2)};
  ComplexArray<size>  out= {};
  FFT<size,size,stride>(in,out,size,stride);
  for(auto comp:out.arr)
  {
    std::cout<<comp.Real<<','<<comp.Imag<<"i\n";
  }
  return 0;
}
