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
 * \brief This is the default structure used by TupleMemberSwapPolicyDecl<Tuple>
 * to produce a compile time error when the specialization does not exist for
 * the desired tuple members
 */
template<typename T, TupleMember member1, TupleMember member2>
struct UndefinedTupleMemberSwapPolicy
{
  //! This function should not compile if there is any attempt to instantiate!
  static inline void notDefined() { return T::this_type_is_missing_a_specialization(); }
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
template<typename T, TupleMember member1, TupleMember member2>
struct TupleMemberSwapPolicy
{  
  // Member types
  typedef typename T::desiredType1 tupleMemberType1;
  typedef typename T::desiredType2 tupleMemberType2;
  
  //! Swap the data between the two tuple members
  static inline void swap(T &tuple){ (void)UndefinedTupleMemberSwapPolicy<T,member1,member2>::notDefined(); return 0; }
};

} // end FACEMC namespace

#endif // end TUPLE_MEMBER_SWAP_POLICY_DECL.hpp

//---------------------------------------------------------------------------//
// end TupleMemberSwapPolicyDecl.hpp
//---------------------------------------------------------------------------//
