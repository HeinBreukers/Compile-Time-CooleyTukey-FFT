#include <gtest/gtest.h>
#include <memory>
#include <array>

#include "Matrix.hpp"
#include "Vector.hpp"

using namespace Lazy;

class MatrixTest : public ::testing::Test {
 protected:
  void SetUp() override {
    matrix = std::make_unique<Vector<double,12>>(std::array<double,12>{1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9,10.10,11.11,12.12});
  }

  std::unique_ptr<Vector<double,12>> matrix;
};

TEST_F(MatrixTest, getScalar) {
    auto assert = matrix->getScalar(0);
    EXPECT_EQ(1.1,assert);
    assert = matrix->getScalar(1);
    EXPECT_EQ(2.2,assert);
    assert = matrix->getScalar(10);
    EXPECT_EQ(11.11,assert);
    assert = matrix->getScalar(11);
    EXPECT_EQ(12.12,assert);
}

TEST_F(MatrixTest, getPacket) {
    auto assert = matrix->get(0);
    EXPECT_EQ(assert[0],1.1);
    EXPECT_EQ(assert[1],2.2);
    EXPECT_EQ(assert[2],3.3);
    EXPECT_EQ(assert[3],4.4);
}

TEST_F(MatrixTest, setScalar) {
    matrix->setScalar(0,100.001);
    auto assert = matrix->container()[0];
    EXPECT_EQ(100.001,assert);
}

/*
TEST_F(MatrixTest, setPacket) {
    using SBase =  internal::SIMD::SIMDTraits::SIMDBaseType;
    std::array<double,4> arr{100.001,200.002,300.003,400.004};
    auto packet = SBase::load<double,false>(&arr[0]);
    matrix->set(0,packet);
    auto assert = matrix->container()[0];
    EXPECT_EQ(100.001,assert);
    assert = matrix->container()[1];
    EXPECT_EQ(200.002,assert);
    assert = matrix->container()[2];
    EXPECT_EQ(300.003,assert);
    assert = matrix->container()[3];
    EXPECT_EQ(400.004,assert);

}
*/

//TODO write tests that make sure nothing is copied during forwarding when adding substracting etc
//TODO write tests that make sure that operations take variables as ref