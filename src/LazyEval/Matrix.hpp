#pragma once

#include "MatrixBase.hpp"
#include "StaticArray.hpp"
#include "RingBuffer.hpp"

#include <cstddef>
#include <array>
#include <fmt/core.h>
#include <iostream>
#include <algorithm>

namespace Lazy
{

template<typename T, size_t Cols, size_t Rows, template<typename,size_t> typename Container>
class traits<Matrix<T,Cols,Rows,Container>>
{
public:
    using type = T;
    using evalType = Matrix<T,Cols,Rows,Container>;
    constexpr static size_t rows = Rows;
    constexpr static size_t cols = Cols;
    static constexpr size_t size = Rows*Cols;

    static constexpr bool isRef = true;

    //static_assert((size%internal::SIMD::SIMDTraits::PacketWidth<T>)==0, "Matrix size not multiple of SIMD packet size");
};

template<typename T, size_t Cols, size_t Rows, template<typename,size_t> typename Container = internal::containers::StaticArray>
class Matrix: public MatrixBase<Matrix<T, Cols, Rows,Container>>
{
public:
    using Base =  MatrixBase<Matrix<T, Cols, Rows,Container>>;
    using SBase =  internal::SIMD::SIMDTraits::SIMDBaseType;
    using PacketType = internal::SIMD::SIMDTraits::PacketType<T>;

    Matrix(): Base()
    {
    }

    // TODO improve initialization
    explicit Matrix(const std::array<T,Rows*Cols>& t_value): Base(),
    value(t_value)
    {
    }

    template<typename U> requires std::is_same_v<U,std::array<T,Rows*Cols>>
    explicit Matrix(U&& t_value): Base(),
    value(std::forward<U>(t_value))
    {}

    template<typename OtherDerived>
    Matrix(const MatrixBase<OtherDerived>& other)
    {
        Base::evaluate(other);
    }

    template<typename OtherDerived>
    Matrix& operator=(const MatrixBase<OtherDerived>& other)
    {
        return Base::operator=(*static_cast<const OtherDerived*>(&other));
    }

    // TODO r/l value reference
    template<bool aligned = true>
    void set(size_t index, const PacketType& val)
    {
        SBase::store<T,aligned>(&value[index], val);
    }

    // TODO r/l value reference
    void setScalar(size_t index, const T& val)
    { 
        value[index]=val;
    }

    // TODO constexpr all the things
    template<bool aligned = true>
    [[nodiscard]] PacketType get(size_t index) const
    {
        fmt::print("load Aligned: {}\n",aligned);
        return SBase::load<T,aligned>(&value[index]);
    }

    [[nodiscard]] T getScalar(size_t index) const
    {
        return value[index];
    }

    static constexpr size_t size()
    {
        return Rows*Cols;
    }

    Container<T,Cols*Rows>& container()
    {
        return value;
    }
    
    Container<T,Cols*Rows>& container() const
    {
        return value;
    }
private:
    Container<T,Cols*Rows> value;
};

// TODO osstream
/*
template<typename T, size_t Cols, size_t Rows, template<typename,size_t> typename Container>
std::ostream& operator<<(std::ostream& os, const Matrix<T, Cols, Rows,Container>& dt)
{
    os << dt.value;
    return os;
}
*/


} // namespace Lazy