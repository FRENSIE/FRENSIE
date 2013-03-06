//---------------------------------------------------------------------------//
// \file   TupleComparePolicy.hpp
// \author Alex Robinson
// \brief  Tuple Compare Policy declaration
//---------------------------------------------------------------------------//

#ifndef TUPLE_COMPARE_POLICY_DECL_HPP
#define TUPLE_COMPARE_POLICY_DECL_HPP

// FACEMC Includes
#include "Tuple.hpp"

namespace FACEMC{

/*!
 * \brief This is the default structure used by TupleComparePolicy<Tuple>
 * to produce a compile time error when the specialization does not exist for
 * the iterator type Iterator.
 */
template<typename T, TupleMember member>
struct UndefinedTupleComparePolicy
{
  //! This function should not compile if there is any attempt to instantiate!
  static inline typename T::type notDefined() { return T::this_type_is_missing_a_specialization(); }
};

/*!
 * \brief This structure defines which element of the tuple is used for
 * comparing a value to a tuple. The functions in the templated
 * base unspecialized struct are designed not to compile (giving a nice 
 * compile-time error message) and therefore specializations must be written
 * for each TupleMember enumeration.
 * \note <ol>
 * <li> The default defined specializations are provided for \c FIRST 
 * \c SECOND, \c THIRD, \c FOURTH
 * </ol>
 */
template<typename T, TupleMember member>
struct TupleComparePolicy
{
  //! Type of the desired tuple member
  typedef typename T::type tupleMemberType;
  
  //! Return the value of the desired tuple member
  static inline typename T::type value(T &tuple){ (void)UndefinedTupleComparePolicy<T,member>::notDefined(); return 0; }
};

} // end FACEMC namespace

#endif // end TUPLE_COMPARE_POLICY_DECL_HPP

//---------------------------------------------------------------------------//
// end TupleComparePolicyDecl.hpp
//---------------------------------------------------------------------------//
