#include "FFT.hpp"

#include <iostream>

using namespace CTFFT;

consteval auto as_constant(auto val)
{
  return val;
}

int main() {
  constexpr int size = 8;
  constexpr int stride = 1;
  constexpr std::array<Complex,size> in = {Complex(1,0),Complex(2,-1), Complex(0,-1), Complex(-1,2),Complex(1,0),Complex(2,-1), Complex(0,-1), Complex(-1,2)};

  constexpr auto out = as_constant(FFT(in,size,stride));
  for(auto comp:out)
  {
    std::cout<<comp.Real<<','<<comp.Imag<<"i\n";
  }
  return 0;
}
