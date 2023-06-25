#pragma once


#include "MatrixBase.hpp"

namespace Lazy
{

template<typename LHS, typename RHS>
auto dot(const MatrixBase<LHS>& lhs,const MatrixBase<RHS>& rhs)
{
    return (lhs*rhs).acc();
}

}