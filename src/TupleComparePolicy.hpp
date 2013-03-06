//---------------------------------------------------------------------------//
// \file   TupleComparePolicy.hpp
// \author Alex Robinson
// \brief  Tuple Compare Policy specializations
//---------------------------------------------------------------------------//

#ifndef TUPLE_COMPARE_POLICY_HPP
#define TUPLE_COMPARE_POLICY_HPP

// FACEMC Includes
#include "TupleComparePolicyDecl.hpp"
#include "Tuple.hpp"

namespace FACEMC{

template<typename T>
struct TupleComparePolicy<T,FIRST>
{
  typedef typename T::firstType tupleMemberType;
  static inline tupleMemberType value(T &tuple) { return tuple.first; }
};

template<typename T>
struct TupleComparePolicy<T,SECOND>
{
  typedef typename T::secondType tupleMemberType;
  static inline tupleMemberType value(T &tuple) { return tuple.second; }
};

template<typename T>
struct TupleComparePolicy<T,THIRD>
{
  typedef typename T::thirdType tupleMemberType;
  static inline tupleMemberType value(T &tuple) { return tuple.third; }
};

template<typename T>
struct TupleComparePolicy<T,FOURTH>
{
  typedef typename T::fourthType tupleMemberType;
  static inline tupleMemberType value(T &tuple) { return tuple.fourth; }
};
  
} // end FACEMC namespace

#endif // end TUPLE_COMPARE_POLICY_HPP

//---------------------------------------------------------------------------//
// end TupleComparePolicy.hpp
//---------------------------------------------------------------------------//
