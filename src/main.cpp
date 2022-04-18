#include "FFT.hpp"

#include <iostream>

using namespace CTFFT;

consteval auto as_constant(auto val)
{
  return val;
}

int main() {
  constexpr int size = 8;
  //constexpr int stride = 1;
  constexpr std::array<std::complex<double>,size> in = {std::complex<double>(1,0),std::complex<double>(2,-1), std::complex<double>(0,-1), std::complex<double>(-1,2),std::complex<double>(1,0),std::complex<double>(2,-1), std::complex<double>(0,-1), std::complex<double>(-1,2)};

  const auto out = as_constant(FFT(in));
  for(auto comp:out)
  {
    std::cout<<comp.real()<<','<<comp.imag()<<"i\n";
  }
  return 0;
}
