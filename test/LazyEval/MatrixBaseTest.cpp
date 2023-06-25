#include <gtest/gtest.h>
#include <memory>
#include <type_traits>

#include "Meta.hpp"
#include "MatrixBase.hpp"

using namespace Lazy;

// forward declare
class MatrixBaseDerived;

template <>
class Lazy::traits<MatrixBaseDerived>
{
public:
    using type = float;
    using evalType = MatrixBaseDerived;
    constexpr static size_t rows = 1;
    constexpr static size_t cols = 1;
    static constexpr size_t size = 1;

    static constexpr bool isRef = true;

    //static_assert((size%internal::SIMD::SIMDTraits::PacketWidth<T>)==0, "Matrix size not multiple of SIMD packet size");
};

struct MatrixBaseDerived: MatrixBase<MatrixBaseDerived>
{
  
};

class MatrixBaseTest : public ::testing::Test {
 protected:
  void SetUp() override {
    matrixBaseDerived = std::make_unique<MatrixBaseDerived>();
  }

  std::unique_ptr<MatrixBase<MatrixBaseDerived>> matrixBaseDerived;
};


TEST_F(MatrixBaseTest, derivedType) {

  auto der = matrixBaseDerived->derived();
  bool assert = std::is_same_v<MatrixBaseDerived,decltype(der)>;
  ASSERT_TRUE(assert);
}
