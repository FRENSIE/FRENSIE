//---------------------------------------------------------------------------//
// \file   TupleMemberSwapPolicyDecl.hpp
// \author Alex Robinson
// \brief  Tuple member data swap policy declaration
//---------------------------------------------------------------------------//

#ifndef TUPLE_MEMBER_SWAP_POLICY_DECL_HPP
#define TUPLE_MEMBER_SWAP_POLICY_DECL_HPP

// FACEMC Includes
#include "Tuple.hpp"

namespace FACEMC{

/*!
 * \brief This is the default structure used by TupleMemberSwapPolicyDecl
 * to produce a compile time error when the specialization does not exist for
 * the desired tuple members
 */
template<typename Tuple1,
	 typename Tuple2,
	 TupleMember member1, 
	 TupleMember member2>
struct UndefinedTupleMemberSwapPolicy
{
  //! This function should not compile if there is any attempt to instantiate!
  static inline void notDefined() { return Tuple1::this_type_is_missing_a_specialization(); }
};

/*!
 * \brief This structure defines which element of the tuple will be swapped.
 * The functions in the templated base unspecialized struct are designed not 
 * to compile (giving a nice compile-time error message) and therefore 
 * specializations must be written for each pair of TupleMember enumerations.
 * \note <ol>
 * <li> The default defined specializations are provided for \c FIRST-SECOND 
 * \c FIRST-THIRD, \c FIRST-FOURTH, \c SECOND-THIRD, \c SECOND-FOURTH,
 * \c THIRD-FOURTH
 * </ol>
 */
template<typename Tuple1,
	 typename Tuple2,
	 TupleMember member1, 
	 TupleMember member2>
struct TupleMemberSwapPolicy
{  
  // Member types
  typedef typename Tuple1::tupleType1 tupleMemberType1;
  typedef typename Tuple1::tupleType2 tupleMemberType2;
  typedef typename Tuple2::tupleType1 swapTupleMemberType1;
  typedef typename Tuple2::tupleType2 swapTupleMemberType2;
  
  //! Swap the data between the two tuple members
  static inline void swap(const Tuple1 &tuple, Tuple2 &swap_tuple){ (void)UndefinedTupleMemberSwapPolicy<Tuple1,Tuple2,member1,member2>::notDefined(); return 0; }
};

} // end FACEMC namespace

#endif // end TUPLE_MEMBER_SWAP_POLICY_DECL.hpp

//---------------------------------------------------------------------------//
// end TupleMemberSwapPolicyDecl.hpp
//---------------------------------------------------------------------------//
