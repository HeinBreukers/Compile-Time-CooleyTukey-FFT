#pragma once


#include "MatrixBase.hpp"
#include "OneArgOpImpl.hpp"

#include <cstddef>
#include <array>
#include <type_traits>

namespace Lazy
{

template<typename DerivedOp, typename T>
struct traits<OneArgOperation<DerivedOp, T>>
{
    using type = T;
    using returnType = typename DerivedOp::type;

    using evalType = typename DerivedOp::type;
    //typedef LHS::type type;
};

template<typename OneArgDerivedOp, typename T>
class OneArgOperation: public MatrixBase<OneArgOperation<OneArgDerivedOp,T>>
{
public:
    // TODO compile time type enforcing
    // TODO asserts, type checking + size checking
    OneArgOperation(const T& val, const OneArgDerivedOp& functor = OneArgDerivedOp()):
    m_val(val),
    m_functor(functor)
    {
        // Per op set evaluate or lazy evaluate flag
        // if evaluate then call MatrixBase::evaluate and make sure r value is returned to parent operation for example:
        //              sum
        //              / \
        //         eval&&  lazy&
        //
        // else do nothing
    }


    auto get(size_t index) const
    {
        return m_functor.operate(m_val.get(index));
    }

    auto getScalar(size_t index) const
    {
        return m_functor.operateScalar(m_val.getScalar(index));
    }
private:
    OneArgDerivedOp m_functor;
    typename selectQualifier<T,traits<T>::isRef>::type m_val;
};
}