#pragma once

#include "Matrix.hpp"

namespace Lazy
{

template<typename T, size_t Cols, template<typename,size_t> typename Container = internal::containers::StaticArray>
using Vector = Matrix<T, Cols, 1, Container>;


} // namespace Lazy