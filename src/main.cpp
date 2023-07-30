#include "FFT.hpp"
#include "FixedPoint.hpp"



#include <iostream>
#include <iomanip>
#include <fmt/ranges.h>

using namespace CTFFT;


consteval auto as_constant(auto val)
{
  return val;
}


int main() {

  const int point = 16;
  fixed<int,point> f(13.25438);

  fixed<int,point> fl(13.7);
  fixed<int,point> f2;
  f2 = fixed<int,point>::range();
  auto res = fl + f;

  std::cout<<f<<'\n';
  std::cout<<f.range()<<" "<<f.precision()<<'\n';
  std::cout<<std::fixed<<std::setprecision(5)<<static_cast<double>(-res + f2-f)<<'\n';

  constexpr std::array<std::complex<float>,4> data = {std::complex(1.0f,1.0f),std::complex(2.0f,2.0f),std::complex(3.0f,3.0f),std::complex(4.0f,4.0f)};
  constexpr std::array<std::complex<float>,4> fftout = FFT(data);

  //auto constFFT = as_constant(fftout);
  for(const std::complex<float>& fftVal: fftout)
  {
    std::cout<<fftVal.real()<<','<<fftVal.imag()<<"i\n";
  }
  
  return 0;
}
