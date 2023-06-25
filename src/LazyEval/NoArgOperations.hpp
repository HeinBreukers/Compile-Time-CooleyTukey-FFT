#pragma once


#include "MatrixBase.hpp"
#include "NoArgOpImpl.hpp"

#include <cstddef>
#include <array>
#include <type_traits>

namespace Lazy
{



template<typename NoArgDerivedOp, size_t Size>
struct traits<NoArgOperation<NoArgDerivedOp,Size>>
{
    using type = NoArgDerivedOp::type;
    using evalType = type;

    static constexpr size_t size = Size;
    static constexpr bool isRef = false;
    //static constexpr bool isRef =NoArgDerivedOp::isRef;
    //typedef LHS::type type;
};


template<typename NoArgDerivedOp, size_t Size>
class NoArgOperation: public MatrixBase<NoArgOperation<NoArgDerivedOp,Size>>
{
public:
    // TODO compile time type enforcing
    // TODO asserts, type checking + size checking
    NoArgOperation(const NoArgDerivedOp& functor):
    m_functor(functor)
    {}

    auto get(size_t index) const
    {
        return m_functor.operate(index);
    }

    auto getScalar(size_t index) const
    {
        return m_functor.operateScalar(index);
    }

private:
    NoArgDerivedOp m_functor;
};


}