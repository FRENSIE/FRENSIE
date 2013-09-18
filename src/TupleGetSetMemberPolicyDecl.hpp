//---------------------------------------------------------------------------//
//!
//! \file   TupleGetSetMemberPolicy.hpp
//! \author Alex Robinson
//! \brief  Tuple get and set member policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef TUPLE_GET_SET_MEMBER_POLICY_DECL_HPP
#define TUPLE_GET_SET_MEMBER_POLICY_DECL_HPP

// FACEMC Includes
#include "Tuple.hpp"

/*! \defgroup tuple_gsm_policy Tuple Get-Set Member Policy
 * \ingroup policies
 *
 * The FACEMC::DataProcessor has many templated member functions
 * that operate on arrays of tuples (either FACEMC::Pair, FACEMC::Trip or
 * FACEMC::Quad). The FACEMC::TupleGetSetMemberPolicy allows these templated
 * functions to easily access members of a tuple in a generic way. Partial
 * specializations are provided for each tuple member enumeration. Attempting
 * to use the class without a specialization will result in a compile time
 * error. The compile time error message is defined by the 
 * FACEMC::UndefinedTupleGetSetMemberPolicy struct.
 */

namespace FACEMC{

/*! \brief Default structure used by FACEMC::TupleGetSetMemberPolicy
 * to produce a compile time error when the specialization does not exist for
 * the desired tuple member.
 *
 * To use the FACEMC::TupleGetSetMemberPolicy struct a partial template
 * specialization for the particular member enumeration must be written. When 
 * the type of member enumeration does not have a partial specialization, the
 * compiler will attempt to instantiate this struct, which has a function
 * notDefined() that attempts to access a non-existant member of class T,
 * causing a compile time error.
 * \ingroup tuple_gsm_policy
 */
template<typename T, TupleMember member>
struct UndefinedTupleGetSetMemberPolicy
{
  //! This function should not compile if there is any attempt to instantiate!
  static inline typename T::type notDefined() { return T::this_type_is_missing_a_specialization(); }
};

/*! This structure defines which member of the tuple will be read or set.
 * 
 * The functions in the templated base unspecialized struct are designed not to
 * compile (giving a nice compile-time error message) and therefore 
 * specializations must be written for each TupleMember enumeration.
 * \tparam T A tuple type (either FACEMC::Pair, FACEMC::Trip or FACEMC::Quad).
 * \tparam member A tuple member enumeration.
 * \note The default defined specializations are provided for FIRST, SECOND, 
 * THIRD and FOURTH
 * \ingroup tuple_gsm_policy
 */
template<typename T, TupleMember member>
struct TupleGetSetMemberPolicy
{
  //! The type of the desired tuple member
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
