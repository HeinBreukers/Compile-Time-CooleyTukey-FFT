#pragma once


#include "MatrixBase.hpp"
#include "TwoArgOpImpl.hpp"

#include <cstddef>
#include <array>
#include <type_traits>

namespace Lazy
{

template<typename DerivedOp, typename LHS, typename RHS>
struct traits<ArithmeticOperation<DerivedOp, LHS, RHS>>
{
    static_assert(std::is_same<typename LHS::type,typename RHS::type>::value, "incompatible datatypes");
    
    // TODO proper return type deduction (based on LHS, RHS, DerivedOp)

    static constexpr bool evaluate = DerivedOp::evaluate;
    static constexpr bool isRef = false;

    using type = typename DerivedOp::type<LHS,RHS>;
    using returnType = typename DerivedOp::returnType<LHS,RHS>;
    using evalType = typename DerivedOp::evalType<LHS,RHS>;
    using LHSargType = selectArgType<LHS,evaluate>::type;
    using RHSargType = selectArgType<LHS,evaluate>::type;


    //TODO proper size checking (based on LHS, RHS, DerivedOp)
    //static_assert(DerivedOp::SizeCondition<LHS,RHS>, "incompatible sizes");
    

    constexpr static size_t rows =  RHS::rows;
    constexpr static size_t cols =  RHS::cols;
    static constexpr size_t size = traits<RHS>::size;

    // TODO proper reference type deduction
    
    
};

template<typename DerivedOp, typename LHS, typename RHS>
class ArithmeticOperation: public MatrixBase<ArithmeticOperation<DerivedOp,LHS,RHS>>
{
public:
    static constexpr bool evaluate = DerivedOp::evaluate;
    using LHSargType = selectArgType<LHS,evaluate>::type;
    using RHSargType = selectArgType<RHS,evaluate>::type;
    // TODO compile time type enforcing
    // TODO asserts, type checking + size checking
    ArithmeticOperation(const LHS& Lhs, const RHS& Rhs, const DerivedOp& functor = DerivedOp()):
    m_Lhs(Lhs),
    m_Rhs(Rhs),
    m_functor(functor)
    {
    }

    auto get(size_t index) const
    {
        return m_functor.operate(m_Lhs.get(index),m_Rhs.get(index));
    }

    auto getScalar(size_t index) const
    {
        return m_functor.operateScalar(m_Lhs.getScalar(index),m_Rhs.getScalar(index));
    }

private:
    selectQualifier<LHSargType,traits<LHSargType>::isRef>::type m_Lhs;
    selectQualifier<RHSargType,traits<RHSargType>::isRef>::type m_Rhs;
    DerivedOp m_functor;
};

template<typename LHS>
template<typename RHS>
inline const ArithmeticOperation<OpImplSum<typename MatrixBase<LHS>::OpType<RHS>>,LHS,RHS> MatrixBase<LHS>::operator+(const MatrixBase<RHS>& other) const 
{
    return ArithmeticOperation<OpImplSum<MatrixBase<LHS>::type>,LHS,RHS>(*static_cast<const LHS*>(this), *static_cast<const RHS*>(&other));
}

template<typename LHS>
template<typename RHS>
inline const ArithmeticOperation<OpImplSub<typename MatrixBase<LHS>::OpType<RHS>>,LHS,RHS> MatrixBase<LHS>::operator-(const MatrixBase<RHS>& other) const 
{
    return ArithmeticOperation<OpImplSub<MatrixBase<LHS>::type>,LHS,RHS>(*static_cast<const LHS*>(this), *static_cast<const RHS*>(&other));
}

template<typename LHS>
template<typename RHS>
inline const ArithmeticOperation<OpImplMul<typename MatrixBase<LHS>::OpType<RHS>>,LHS,RHS> MatrixBase<LHS>::operator*(const MatrixBase<RHS>& other) const 
{
    return ArithmeticOperation<OpImplMul<MatrixBase<LHS>::type>,LHS,RHS>(*static_cast<const LHS*>(this), *static_cast<const RHS*>(&other));
}

template<typename LHS>
template<typename T> requires std::is_arithmetic_v<T>
inline const ArithmeticOperation<OpImplMul<typename MatrixBase<LHS>::OpType<T>>,LHS,NoArgOperation<NoArgOpImplScalar<T>,traits<LHS>::size>> MatrixBase<LHS>::operator*(const T& scalar) const
{
    auto fnctr = NoArgOpImplScalar<T>(scalar);
    auto op = NoArgOperation<NoArgOpImplScalar<T>,traits<LHS>::size>(fnctr);
    return ArithmeticOperation<OpImplMul<MatrixBase<LHS>::type>,LHS,NoArgOperation<NoArgOpImplScalar<T>,traits<LHS>::size>>(*static_cast<const LHS*>(this), op );
}

}