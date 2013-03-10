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

template<typename Tuple1, typename Tuple2>
struct TupleMemberSwapPolicy<Tuple1,Tuple2,FIRST,FIRST>
{
  typedef typename Tuple1::firstType tupleMemberType1;
  typedef typename Tuple1::firstType tupleMemberType2;
  typedef typename Tuple2::firstType swapTupleMemberType1;
  typedef typename Tuple2::firstType swapTupleMemberType2;
  
  static inline void swap(const Tuple1 &tuple, Tuple2 &swap_tuple)
  {
    swap_tuple.first = static_cast<swapTupleMemberType1>( tuple.first );
  }
};

template<typename Tuple1, typename Tuple2>
struct TupleMemberSwapPolicy<Tuple1,Tuple2,FIRST,SECOND>
{
  typedef typename Tuple1::firstType tupleMemberType1;
  typedef typename Tuple1::secondType tupleMemberType2;
  typedef typename Tuple2::firstType swapTupleMemberType1;
  typedef typename Tuple2::secondType swapTupleMemberType2;
  
  static inline void swap(const Tuple1 &tuple, Tuple2 &swap_tuple)
  {
    tupleMemberType1 copy = tuple.first;
    swap_tuple.first = static_cast<swapTupleMemberType1>( tuple.second );
    swap_tuple.second = static_cast<swapTupleMemberType2>( copy );
  }
};

template<typename Tuple1, typename Tuple2>
struct TupleMemberSwapPolicy<Tuple1,Tuple2,FIRST,THIRD>
{
  typedef typename Tuple1::firstType tupleMemberType1;
  typedef typename Tuple1::thirdType tupleMemberType2;
  typedef typename Tuple2::firstType swapTupleMemberType1;
  typedef typename Tuple2::thirdType swapTupleMemberType2;

  static inline void swap(const Tuple1 &tuple, Tuple2 &swap_tuple)
  {
    tupleMemberType1 copy = tuple.first;
    swap_tuple.first = static_cast<swapTupleMemberType1>( tuple.third );
    swap_tuple.third = static_cast<swapTupleMemberType2>( copy );
  }
};

template<typename Tuple1, typename Tuple2>
struct TupleMemberSwapPolicy<Tuple1,Tuple2,FIRST,FOURTH>
{
  typedef typename Tuple1::firstType tupleMemberType1;
  typedef typename Tuple1::fourthType tupleMemberType2;
  typedef typename Tuple2::firstType swapTupleMemberType1;
  typedef typename Tuple2::fourthType swapTupleMemberType2;

  static inline void swap(const Tuple1 &tuple, Tuple2 &swap_tuple )
  {
    tupleMemberType1 copy = tuple.first;
    swap_tuple.first = static_cast<swapTupleMemberType1>( tuple.fourth );
    swap_tuple.fourth = static_cast<swapTupleMemberType2>( copy );
  }
};

template<typename Tuple1, typename Tuple2>
struct TupleMemberSwapPolicy<Tuple1,Tuple2,SECOND,SECOND>
{
  typedef typename Tuple1::secondType tupleMemberType1;
  typedef typename Tuple1::secondType tupleMemberType2;
  typedef typename Tuple2::secondType swapTupleMemberType1;
  typedef typename Tuple2::secondType swapTupleMemberType2;
  
  static inline void swap(const Tuple1 &tuple, Tuple2 &swap_tuple)
  {
    swap_tuple.second = static_cast<swapTupleMemberType1>( tuple.second );
  }
};

template<typename Tuple1, typename Tuple2>
struct TupleMemberSwapPolicy<Tuple1,Tuple2,SECOND,THIRD>
{
  typedef typename Tuple1::secondType tupleMemberType1;
  typedef typename Tuple1::thirdType tupleMemberType2;
  typedef typename Tuple2::secondType swapTupleMemberType1;
  typedef typename Tuple2::thirdType swapTupleMemberType2;

  static inline void swap(const Tuple1 &tuple, Tuple2 &swap_tuple)
  {
    tupleMemberType1 copy = tuple.second;
    swap_tuple.second = static_cast<swapTupleMemberType1>( tuple.third );
    swap_tuple.third = static_cast<swapTupleMemberType2>( copy );
  }
};

template<typename Tuple1, typename Tuple2>
struct TupleMemberSwapPolicy<Tuple1,Tuple2,SECOND,FOURTH>
{
  typedef typename Tuple1::secondType tupleMemberType1;
  typedef typename Tuple1::fourthType tupleMemberType2;
  typedef typename Tuple2::secondType swapTupleMemberType1;
  typedef typename Tuple2::fourthType swapTupleMemberType2;

  static inline void swap(const Tuple1 &tuple, Tuple2 &swap_tuple)
  {
    tupleMemberType1 copy = tuple.second;
    swap_tuple.second = static_cast<swapTupleMemberType1>( tuple.fourth );
    swap_tuple.fourth = static_cast<swapTupleMemberType2>( copy );
  }
};

template<typename Tuple1, typename Tuple2>
struct TupleMemberSwapPolicy<Tuple1,Tuple2,THIRD,THIRD>
{
  typedef typename Tuple1::thirdType tupleMemberType1;
  typedef typename Tuple1::thirdType tupleMemberType2;
  typedef typename Tuple2::thirdType swapTupleMemberType1;
  typedef typename Tuple2::thirdType swapTupleMemberType2;
  
  static inline void swap(const Tuple1 &tuple, Tuple2 &swap_tuple)
  {
    swap_tuple.third = static_cast<swapTupleMemberType1>( tuple.third );
  }
};

template<typename Tuple1, typename Tuple2>
struct TupleMemberSwapPolicy<Tuple1,Tuple2,THIRD,FOURTH>
{
  typedef typename Tuple1::thirdType tupleMemberType1;
  typedef typename Tuple1::fourthType tupleMemberType2;
  typedef typename Tuple2::thirdType swapTupleMemberType1;
  typedef typename Tuple2::fourthType swapTupleMemberType2;

  static inline void swap(const Tuple1 &tuple, Tuple2 &swap_tuple)
  {
    tupleMemberType1 copy = tuple.third;
    swap_tuple.third = static_cast<swapTupleMemberType1>( tuple.fourth );
    swap_tuple.fourth = static_cast<swapTupleMemberType2>( copy );
  }
};

template<typename Tuple1, typename Tuple2>
struct TupleMemberSwapPolicy<Tuple1,Tuple2,FOURTH,FOURTH>
{
  typedef typename Tuple1::fourthType tupleMemberType1;
  typedef typename Tuple1::fourthType tupleMemberType2;
  typedef typename Tuple2::fourthType swapTupleMemberType1;
  typedef typename Tuple2::fourthType swapTupleMemberType2;
  
  static inline void swap(const Tuple1 &tuple, Tuple2 &swap_tuple)
  {
    swap_tuple.fourth = static_cast<swapTupleMemberType1>( tuple.fourth );
  }
};

} // end FACEMC namespace

#endif // end TUPLE_MEMBER_SWAP_POLICY_HPP

//---------------------------------------------------------------------------//
// end TupleMemberSwapPolicy.hpp
//---------------------------------------------------------------------------//


