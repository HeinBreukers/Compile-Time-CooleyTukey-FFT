#include "FFT.hpp"
#include "FIR.hpp"
#include "FixedPoint.hpp"

#include <iostream>
#include <iomanip>
#include <chrono>
#include <numeric>

using namespace CTFFT;

consteval auto as_constant(auto val)
{
  return val;
}

int main() {

  const int point = 16;
  fixed<int,point> f(13.25438);

  fixed<int,point> fl(5.0);
  fixed<int,point> f2;
  f2 = fixed<int,point>::range();
  auto res = fl + f;

  std::cout<<f.range()<<" "<<f.precision()<<'\n';
  std::cout<<std::fixed<<std::setprecision(5)<<static_cast<double>(res + f2-f)<<'\n';
  return 0;
}
