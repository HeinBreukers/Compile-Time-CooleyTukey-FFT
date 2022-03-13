cmake_minimum_required(VERSION 3.2)
project(CTFFT)

include_directories(FFT)
include_directories(ConstExprMath)

set(SOURCE_FILES main.cpp)

set(FFT_FILES
    FFT/FFT.hpp
)

add_executable(divider ${SOURCE_FILES} ${FFT_FILES})
#target_link_libraries(divider division)
#install(TARGETS divider DESTINATION ${DIVISIBLE_INSTALL_BIN_DIR})
