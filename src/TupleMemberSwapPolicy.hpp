//---------------------------------------------------------------------------//
// \file   TupleMemberSwapPolicy.hpp
// \author Alex Robinson
// \brief  Tuple member data swap policy specializations.
//---------------------------------------------------------------------------//

#ifndef TUPLE_MEMBER_SWAP_POLICY_HPP
#define TUPLE_MEMBER_SWAP_POLICY_HPP

// FACEMC Includes
#include "TupleMemberSwapPolicyDecl.hpp"
#include "Tuple.hpp"

namespace FACEMC{

template<typename T>
struct TupleMemberSwapPolicy<T,FIRST,SECOND>
{
  typedef typename T::firstType tupleMemberType1;
  typedef typename T::secondType tupleMemberType2;
  
  static inline void swap(T &tuple)
  {
    tupleMemberType1 copy = tuple.first;
    tuple.first = static_cast<tupleMemberType1>( tuple.second );
    tuple.second = static_cast<tupleMemberType2>( copy );
  }
};

template<typename T>
struct TupleMemberSwapPolicy<T,FIRST,THIRD>
{
  typedef typename T::firstType tupleMemberType1;
  typedef typename T::thirdType tupleMemberType2;

  static inline void swap(T &tuple)
  {
    tupleMemberType1 copy = tuple.first;
    tuple.first = static_cast<tupleMemberType1>( tuple.third );
    tuple.third = static_cast<tupleMemberType2>( copy );
  }
};

template<typename T>
struct TupleMemberSwapPolicy<T,FIRST,FOURTH>
{
  typedef typename T::firstType tupleMemberType1;
  typedef typename T::fourthType tupleMemberType2;

  static inline void swap(T &tuple)
  {
    tupleMemberType1 copy = tuple.first;
    tuple.first = static_cast<tupleMemberType1>( tuple.fourth );
    tuple.fourth = static_cast<tupleMemberTyp2>( copy );
  }
};

template<typename T>
struct TupleMemberSwapPolicy<T,SECOND,THIRD>
{
  typedef typename T::secondType tupleMemberType1;
  typedef typename T::thirdType tupleMemberType2;

  static inline void swap(T &tuple)
  {
    tupleMemberType1 copy = tuple.second;
    tuple.second = static_cast<tupleMemberType1>( tuple.third );
    tuple.third = static_cast<tupleMemberType2>( copy );
  }
};

template<typename T>
struct TupleMemberSwapPolicy<T,SECOND,FOURTH>
{
  typedef typename T::secondType tupleMemberType1;
  typedef typename T::fourthType tupleMemberType2;

  static inline void swap(T &tuple)
  {
    tupleMemberType1 copy = tuple.second;
    tuple.second = static_cast<tupleMemberType1>( tuple.fourth );
    tuple.fourth = static_cast<tupleMemberType2>( copy );
  }
};

template<typename T>
struct TupleMemberSwapPolicy<T,THIRD,FOURTH>
{
  typedef typename T::thirdType tupleMemberType1;
  typedef typename T::fourthType tupleMemberType2;

  static inline void swap(T &tuple)
  {
    tupleMemberType1 copy = tuple.third;
    tuple.third = static_cast<tupleMemberType1>( tuple.fourth );
    tuple.fourth = static_cast<tupleMemberTyp2>( copy );
  }
};

} // end FACEMC namespace

#endif // end TUPLE_MEMBER_SWAP_POLICY_HPP

//---------------------------------------------------------------------------//
// end TupleMemberSwapPolicy.hpp
//---------------------------------------------------------------------------//


