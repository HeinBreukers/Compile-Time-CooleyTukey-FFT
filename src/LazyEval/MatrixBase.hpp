#pragma once

#include "Meta.hpp"
#include "Evaluator.hpp"
#include "TwoArgOpImpl.hpp"
#include "NoArgOperations.hpp"
#include "NoArgOpImpl.hpp"

#include "OneArgOperations.hpp"
#include "Accumulate.hpp"


#include <cstddef>
#include <array>
#include <type_traits>



namespace Lazy
{
template<typename Derived>
class MatrixBase
{
public:
    // underlying datatype i.e. double float int fixed
    using type = traits<Derived>::type;
    // return type of operations
    using evalType = traits<Derived>::evalType;

    // underlying return datatype of operations i.e. double float int fixed
    template<typename OtherDerived>
    using OpType = type;

    static constexpr size_t size = traits<Derived>::size;

    Derived derived()
    {
        return *static_cast<Derived*>(this);
    }

    Derived derived() const
    {
        return *static_cast<const Derived*>(this);
    }


    // MatrixBase wrapper around scalar variable
    template<typename T>
    using Scalar = NoArgOperation<NoArgOpImplScalar<T>,traits<Derived>::size>;

    template<typename OtherDerived>
    const ArithmeticOperation<OpImplSum<OpType<OtherDerived>>,Derived,OtherDerived> operator+(const MatrixBase<OtherDerived>& other) const;

    template<typename OtherDerived>
    const ArithmeticOperation<OpImplSub<OpType<OtherDerived>>,Derived,OtherDerived> operator-(const MatrixBase<OtherDerived>& other) const;

    template<typename OtherDerived>
    const ArithmeticOperation<OpImplMul<OpType<OtherDerived>>,Derived,OtherDerived> operator*(const MatrixBase<OtherDerived>& other) const;
    
    template<typename T> requires std::is_arithmetic_v<T>
    const ArithmeticOperation<OpImplMul<OpType<T>>,Derived,Scalar<T> > operator*(const T& scalar) const;

    template<typename T> requires std::is_arithmetic_v<T>
    friend 
    const ArithmeticOperation<OpImplMul<OpType<T>>,Scalar<T>,Derived> operator*(const T& scalar, const MatrixBase<Derived>& derived)
    {
        auto fnctr = NoArgOpImplScalar<T>(scalar);
        auto op = Scalar<T>(fnctr);
        return ArithmeticOperation<OpImplMul<T>,Scalar<T>,Derived>( op, *static_cast<const Derived*>(&derived));

    }

    template<size_t Start, size_t End> 
    auto subset() const
    {
        using Subset = NoArgOpImplSubset<Derived,Start,End>;
        auto fnctr = Subset(*static_cast<const Derived*>(this));
        return NoArgOperation<Subset,Subset::size>(fnctr);
    }

    type acc() const
    {
        type ret;
        Accumulate<type,traits<Derived>::size> acc;
        acc = *static_cast<const Derived*>(this);
        ret = acc.get();
        return ret; 
    }

    evalType eval() const
    {
        if constexpr(std::is_same_v<evalType,Derived>)
        {
            return this->derived();
        }
        evalType ret;
        Evaluator<evalType,Derived>::evaluate(ret,*static_cast<const Derived*>(this));
        return ret;
    }

    template<typename OtherDerived>
    Derived& operator=(const MatrixBase<OtherDerived>& other)
    {
        return evaluate(other);
    }

    template<typename OtherDerived>
    Derived& evaluate(const MatrixBase<OtherDerived>& other)
    {
        static_assert(OtherDerived::size == size, "Matrix sizes do not match, dst and src are of different sizes");
        Evaluator<Derived,OtherDerived>::evaluate(*static_cast<Derived*>(this),*static_cast<const OtherDerived*>(&other));
        return *static_cast<Derived*>(this);
    }
};

}