//---------------------------------------------------------------------------//
//!
//! \file   Utility_TupleMemberTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  Tuple member traits class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TUPLE_MEMBER_TRAITS_DECL_HPP
#define UTILITY_TUPLE_MEMBER_TRAITS_DECL_HPP

// FRENSIE Includes
#include "Utility_Tuple.hpp"

/*! \defgroup tuple_member_traits Tuple Member Traits
 * \ingroup traits
 *
 * The Utility::DataProcessor has many templated member functions
 * that operate on arrays of tuples (either Utility::Pair, Utility::Trip or
 * Utility::Quad). The Utility::TupleMemberTraits allows these templated
 * functions to easily access members of a tuple in a generic way. Partial
 * specializations are provided for each tuple member enumeration. Attempting
 * to use the class without a specialization will result in a compile time
 * error. The compile time error message is defined by the 
 * Utility::UndefinedTraits struct.
 */

namespace Utility{

template<typename Tuple, TupleMember member>
struct UndefinedTupleMemberTraits
{
  //! This function should not compile if there is any attempt to instantiate
  static inline double notDefined() { return Tuple::desired_member_is_missing_specialization(); }
};

/*! This structure defines which member of the tuple will be read or set.
 * 
 * The functions in the templated base unspecialized struct are designed not to
 * compile (giving a nice compile-time error message) and therefore 
 * specializations must be written for each TupleMember enumeration.
 * \tparam T A tuple type (either Utility::Pair, Utility::Trip or 
 * Utility::Quad).
 * \tparam member A tuple member enumeration.
 * \note The default defined specializations are provided for FIRST, SECOND, 
 * THIRD and FOURTH
 * \ingroup tuple_member_traits
 */
template<typename Tuple, TupleMember member>
struct TupleMemberTraits
{
  //! The type of the desired tuple member
  typedef typename Tuple::type tupleMemberType;

  //! Get the value of the desired tuple member
  static inline tupleMemberType get(const Tuple &tuple)
  { (void)UndefinedTupleMemberTraits<Tuple,member>::notDefined(); return 0; }

  //! Set the value of the desired tuple member
  static inline void set(Tuple &tuple, const tupleMemberType &value)
  { (void)UndefinedTupleMemberTraits<Tuple,member>::notDefined(); return 0; }
};
  
/*! This function allows access to the get TupleMemberTraits function.
 *
 * This function is simply a more concise way to access the get static
 * member function associated with the TupleMemberTraits class. It simply 
 * forwards calls to get a member to the associated 
 * Utility::TupleMemberTraits class. It is important to note that the
 * tuple type will be deduced by the function. The Utility::TupleMember must be
 * specified manually (i.e. get<FIRST>( my_tuple ) ).
 * \ingroup tuple_member_traits
 */
template<TupleMember member, typename Tuple>
inline typename TupleMemberTraits<Tuple,member>::tupleMemberType
get( const Tuple &tuple )
{ return TupleMemberTraits<Tuple,member>::get( tuple ); }
  
/*! This function allows access to the set TupleMemberTraits function.
 *
 * This function is simply a more concise way to access the set static 
 * member function associated with the TupleMemberTraits class. It simply 
 * forwards calls to set a member to the associated 
 * Utility::TupleMemberTraits class. It is important to note that The
 * tuple type will be deduced by the function. The Utility::TupleMember must be
 * specified manually (i.e. set<SECOND>( my_tuple, desired_value ) ).
 * \ingroup tuple_member_traits
 */
template<TupleMember member, typename Tuple>
inline void
set( Tuple &tuple, 
     const typename TupleMemberTraits<Tuple,member>::tupleMemberType 
     &value )
{ TupleMemberTraits<Tuple,member>::set( tuple, value ); }

} // end Utility namespace

#endif // end UTILITY_TUPLE_MEMBER_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_TupleMemberTraitsDecl.hpp
//---------------------------------------------------------------------------//
