cmake_minimum_required(VERSION 3.2)
project(CTFFT)

# --- Fetch KafkaWrapper --------------------------------------------------------------
include(FetchContent)


FetchContent_Declare(fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 8.1.1
        )

FetchContent_MakeAvailable(fmt)

include_directories(FFT)
include_directories(FIR)
include_directories(IIR)
include_directories(Internal)
include_directories(Internal/Math)
include_directories(Internal/FixedPoint)
include_directories(Internal/SIMD)
include_directories(Internal/SIMD/AVX256)
include_directories(Internal/FixedPoint)
include_directories(Internal/Containers)
include_directories(LazyEval)

set(SOURCE_FILES main.cpp)

set(FFT_FILES
    FFT/FFT.hpp
)

add_executable(divider ${SOURCE_FILES} ${FFT_FILES})
target_link_libraries(divider fmt)
#target_link_libraries(divider division)
#install(TARGETS divider DESTINATION ${DIVISIBLE_INSTALL_BIN_DIR})
