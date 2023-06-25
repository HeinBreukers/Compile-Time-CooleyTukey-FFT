#pragma once

// Forward Declares
namespace Lazy
{

template<typename T> class traits;

template<typename Derived> class MatrixBase;
template<typename T, size_t Cols, size_t Rows, template<typename,size_t> typename Container> class Matrix;
template<typename T, size_t Size> class Accumulate;
//template<typename T> class Scalar;
template<typename DerivedOp, typename LHS, typename RHS> class ArithmeticOperation;
template<typename DerivedOp, typename T> class OneArgOperation;
template<typename NoArgDerivedOp, size_t Size> class NoArgOperation;
template<typename LHS, typename RHS, typename LHSargType, typename RHSargType> class FIROperation;
template<typename Derived, typename OtherDerived> class OperationImplementation;

template<typename T, bool isRef> struct selectQualifier;
template<typename T, bool evaluate> struct selectArgType;


template<typename T>
struct selectQualifier<T,true>
{
    using type = const T&;
};

template<typename T>
struct selectQualifier<T,false>
{
    using type = const T;
};


template<typename T>
struct selectArgType<T,true>
{
    using type = T::evalType;
};

template<typename T>
struct selectArgType<T,false>
{
    using type = T;
};





}