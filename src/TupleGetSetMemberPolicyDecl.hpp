//---------------------------------------------------------------------------//
// \file   TupleGetSetMemberPolicy.hpp
// \author Alex Robinson
// \brief  Tuple get and set member policy declaration
//---------------------------------------------------------------------------//

#ifndef TUPLE_GET_SET_MEMBER_POLICY_DECL_HPP
#define TUPLE_GET_SET_MEMBER_POLICY_DECL_HPP

// FACEMC Includes
#include "Tuple.hpp"

namespace FACEMC{

/*!
 * \brief This is the default structure used by 
 * TupleGetSetMemberPolicy<Tuple,TupleMember>
 * to produce a compile time error when the specialization does not exist for
 * the desired tuple member.
 */
template<typename T, TupleMember member>
struct UndefinedTupleGetSetMemberPolicy
{
  //! This function should not compile if there is any attempt to instantiate!
  static inline typename T::type notDefined() { return T::this_type_is_missing_a_specialization(); }
};

/*!
 * \brief This structure defines which element of the tuple is used for
 * getting a value from a tuple member or setting the value of a tuple member. 
 * The functions in the templated base unspecialized struct are designed not to
 * compile (giving a nice compile-time error message) and therefore 
 * specializations must be written for each TupleMember enumeration.
 * \note <ol>
 * <li> The default defined specializations are provided for \c FIRST 
 * \c SECOND, \c THIRD, \c FOURTH
 * </ol>
 */
template<typename T, TupleMember member>
struct TupleGetSetMemberPolicy
{
  //! Type of the desired tuple member
  typedef typename T::type tupleMemberType;
  
  //! Get the value of the desired tuple member
  static inline typename T::type get(const T &tuple){ (void)UndefinedTupleGetSetMemberPolicy<T,member>::notDefined(); return 0; }

  //! Set the value of the desired tuple member
  static inline void set(T &tuple, tupleMemberType value){ (void)UndefinedTupleGetSetMemberPolicy<T,member>::notDefined(); return 0; }
};

} // end FACEMC namespace

#endif // end TUPLE_GET_SET_MEMBER_POLICY_DECL_HPP

//---------------------------------------------------------------------------//
// end TupleGetSetMemberPolicyDecl.hpp
//---------------------------------------------------------------------------//
