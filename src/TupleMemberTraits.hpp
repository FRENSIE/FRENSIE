//---------------------------------------------------------------------------//
//!
//! \file   TupleMemberTraits.hpp
//! \author Alex Robinson
//! \brief  Tuple member traits class specializations
//---------------------------------------------------------------------------//

#ifndef TUPLE_MEMBER_TRAITS_HPP
#define TUPLE_MEMBER_TRAITS_HPP

// FACEMC Includes
#include "TupleMemberTraitsDecl.hpp"
#include "Tuple.hpp"

namespace FACEMC{

namespace Traits{

/*! The partial specialization of the TupleMemberTraits for FIRST
 * \ingroup tuple_member_traits
 */
template<typename Tuple>
struct TupleMemberTraits<Tuple,FIRST>
{
  typedef typename Tuple::firstType tupleMemberType;
  static inline tupleMemberType get( const Tuple &tuple )
  { return tuple.first; }
  static inline void set( Tuple &tuple, const tupleMemberType &value )
  { tuple.first = value; }
};

/*! The partial specialization of the TupleMemberTraits for SECOND
 * \ingroup tuple_member_traits
 */
template<typename Tuple>
struct TupleMemberTraits<Tuple,SECOND>
{
  typedef typename Tuple::secondType tupleMemberType;
  static inline tupleMemberType get( const Tuple &tuple )
  { return tuple.second; }
  static inline void set( Tuple &tuple, const tupleMemberType &value )
  { tuple.second = value; }
};

/*! The partial specialization of the TupleMemberTraits for THIRD
 * \ingroup tuple_member_traits
 */
template<typename Tuple>
struct TupleMemberTraits<Tuple,THIRD>
{
  typedef typename Tuple::thirdType tupleMemberType;
  static inline tupleMemberType get( const Tuple &tuple )
  { return tuple.third; }
  static inline void set( Tuple &tuple, const tupleMemberType &value )
  { tuple.third = value; }
};

/*! The partial specialization of the TupleMemberTraits for FOURTH
 * \ingroup tuple_member_traits
 */
template<typename Tuple>
struct TupleMemberTraits<Tuple,FOURTH>
{
  typedef typename Tuple::fourthType tupleMemberType;
  static inline tupleMemberType get( const Tuple &tuple )
  { return tuple.fourth; }
  static inline void set( Tuple &tuple, const tupleMemberType &value )
  { tuple.fourth = value; }
};

} // end Traits namespace

} // end FACEMC namespace

#endif // end TUPLE_MEMBER_TRAITS_HPP

//---------------------------------------------------------------------------//
// end TupleMemberTraits.hpp
//---------------------------------------------------------------------------//


