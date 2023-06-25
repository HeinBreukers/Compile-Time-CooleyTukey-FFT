cmake_minimum_required(VERSION 3.2)

project(test)

include(FetchContent)
FetchContent_Declare(fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 8.1.1
        )

FetchContent_MakeAvailable(fmt)

include_directories(../src/FFT)
include_directories(../src/FIR)
include_directories(../src/IIR)
include_directories(../src/Internal)
include_directories(../src/Internal/Math)
include_directories(../src/Internal/FixedPoint)
include_directories(../src/Internal/SIMD)
include_directories(../src/Internal/SIMD/AVX256)
include_directories(../src/Internal/FixedPoint)
include_directories(../src/Internal/Containers)
include_directories(../src/LazyEval)

enable_testing()

add_executable(
  MatrixBaseTest
  LazyEval/MatrixBaseTest.cpp
  ${TEST_HEADERS}
)
target_link_libraries(
  MatrixBaseTest
  GTest::gtest_main
  fmt
)

add_executable(
  MatrixTest
  LazyEval/MatrixTest.cpp
  ${TEST_HEADERS}
)
target_link_libraries(
  MatrixTest
  GTest::gtest_main
  fmt
)

include(GoogleTest)
gtest_discover_tests(MatrixBaseTest)
