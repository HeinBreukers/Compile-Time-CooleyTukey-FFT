#pragma once


#include "MatrixBase.hpp"


namespace Lazy
{

template<typename LHS, typename RHS, size_t Index>
struct FIRHelper
{
    static auto run(const MatrixBase<LHS>& kernel,const MatrixBase<RHS>& data)
    {
        return FIRHelper<LHS,RHS,Index-1>::run(kernel,data) + kernel.derived().container().at(Index)*data.template subset<Index,traits<RHS>::size-traits<LHS>::size+Index+1>();
    }
};


template<typename LHS, typename RHS>
struct FIRHelper<LHS,RHS,0>
{
    static auto run(const MatrixBase<LHS>& kernel,const MatrixBase<RHS>& data)
    {
        return kernel.derived().container().at(0)*data.template subset<0,traits<RHS>::size-traits<LHS>::size+1>();
    }
};

template<typename LHS, typename RHS>
auto FIR(const MatrixBase<LHS>& kernel,const MatrixBase<RHS>& data)
{
    constexpr size_t kernelSize = traits<LHS>::size;
    return FIRHelper<typename LHS::evalType,typename RHS::evalType,kernelSize-1>::run(kernel, data);
}

template<typename LHS, typename RHS, typename LHSargType, typename RHSargType>
struct traits<FIROperation<LHS, RHS,LHSargType,RHSargType>>
{
    static_assert(std::is_same<typename LHS::type,typename RHS::type>::value, "incompatible datatypes");

    using type = LHS::type;
    using evalType = decltype(FIR(std::declval<LHSargType>(),std::declval<RHSargType>()))::evalType;
    static constexpr size_t size = traits<RHS>::size-traits<LHS>::size+1;
};


template<typename LHS, typename RHS,typename LHSargType = selectArgType<LHS,true>::type, typename RHSargType = selectArgType<RHS,true>::type>
class FIROperation: public MatrixBase<FIROperation<LHS,RHS,LHSargType,RHSargType>>
{
public:
    static constexpr bool evaluate = true;
    //using LHSargType = selectArgType<LHS,evaluate>::type;
    //using RHSargType = selectArgType<RHS,evaluate>::type;
    // TODO compile time type enforcing
    // TODO asserts, type checking + size checking
    FIROperation(const LHS& Lhs, const RHS& Rhs):
    m_Lhs(Lhs),
    m_Rhs(Rhs),
    m_Compound(FIR(m_Lhs,m_Rhs))
    {
    }

    auto get(size_t index) const
    {
        return m_Compound.get(index);
    }

    auto getScalar(size_t index) const
    {
        return m_Compound.getScalar(index);
    }

private:
    selectQualifier<LHSargType,false>::type m_Lhs;
    selectQualifier<RHSargType,false>::type m_Rhs;
    //LHSargType m_Lhs;
    //RHSargType m_Rhs;
    decltype(FIR(std::declval<LHSargType>(),std::declval<RHSargType>())) m_Compound;
};

}

