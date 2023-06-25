#include "FFT.hpp"
#include "FIR.hpp"
#include "FixedPoint.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include "TwoArgOperations.hpp"
#include "DotProduct.hpp"


#include <iostream>
#include <iomanip>
#include <fmt/ranges.h>

using namespace CTFFT;


consteval auto as_constant(auto val)
{
  return val;
}

struct test
{
    test(Lazy::Vector<double,10> vecF):
    m_vecF(vecF)
    {

    }
    Lazy::Vector<double,10> m_vecF;
};

int main()
{
    Lazy::Matrix<double,1,8> matA({1.0,2.0,3.0,4.0,1.0,2.0,3.0,4.0});
    Lazy::Matrix<double,1,8> matB({1.1,2.2,3.3,4.4,1.1,2.2,3.3,4.4});
    Lazy::Matrix<double,1,8> matC;

    Lazy::Vector<double,12,internal::containers::RingBuffer> vecA({1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9,10.10,11.11,12.12});
    Lazy::Vector<double,12> vecB({1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9,10.10,11.11,12.12});
    Lazy::Vector<double,12> vecC;

    fmt::print("vecA: {}\n", vecA.container());

    std::array<double,8> insert = {13.13,14.14,15.15,16.16,17.17,18.18,19.19,20.20};
    vecA.container().put(insert);

    fmt::print("vecA: {}\n", vecA.container());

    vecC =  2.0*vecA + vecB*0.5;

    fmt::print("vecC: {}\n", vecC.container());

    auto scalar = Lazy::dot(5.0*vecA , vecB*0.5);

    fmt::print("dot: {}\n", scalar);

    Lazy::Vector<double,10> vecD;
    vecD = 2.0*vecB.subset<2,12>()+vecB.subset<0,10>();
    fmt::print("vecD: {}\n", vecD.container());



    Lazy::Vector<double,4> kernel({1.1,2.2,3.3,4.4});
    Lazy::Vector<double,12> vecE({1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9,10.10,11.11,12.12});
    Lazy::Vector<double,9> vecF;

    vecF = Lazy::FIROperation(kernel,vecB+vecE*0.5);
    

    fmt::print("vecE: {}\n", vecE.container());
    fmt::print("vecF: {}\n", vecF.container());

    //test T(Lazy::FIR(kernel,vecE));
    //fmt::print("test.vecF: {}\n", T.m_vecF.container());

    //matC = matB + matB* matA;

    //fmt::print("matrix: {}\n", matC.value);
    return 0;
}


/*
int main() {

  const int point = 16;
  fixed<int,point> f(13.25438);

  fixed<int,point> fl(13.7);
  fixed<int,point> f2;
  f2 = fixed<int,point>::range();
  auto res = fl + f;
//  std::array<std::complex<float>,4> data = {std::complex(1.0f,1.0f),std::complex(2.0f,2.0f),std::complex(3.0f,3.0f),std::complex(4.0f,4.0f)};
//  std::array<std::complex<float>,4> fftout;

  std::cout<<f<<'\n';
  std::cout<<f.range()<<" "<<f.precision()<<'\n';
  std::cout<<std::fixed<<std::setprecision(5)<<static_cast<double>(-res + f2-f)<<'\n';
  return 0;
}
*/