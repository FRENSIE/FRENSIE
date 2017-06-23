//---------------------------------------------------------------------------//
//!
//! \file   Utility_TypeTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  General type traits class declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TYPE_TRAITS_DECL_HPP
#define UTILITY_TYPE_TRAITS_DECL_HPP

// FRENSIE Includes
#include "Utility_UndefinedTraits.hpp"

/*! \defgroup type_traits Type Traits
 * \ingroup traits
 */

namespace Utility{

/*! Check if the type is a pointer-to-const type
 * \ingroup type_traits
 */
template<typename T>
struct IsPointerToConst : public std::false_type
{ /* ... */ };

/*! Check if the type has a hash function defined
 *
 * If you create a new specialization of std::hash, specialize this class
 * with your type and inherit from std::true_type.
 * \ingroup type_traits
 */
template<typename T, typename Enabled = void>
struct IsHashable : public std::false_type
{ /* ... */ };
  
} // end Utility namespace

#endif // end UTILITY_TYPE_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_TypeTraitsDecl.hpp
//---------------------------------------------------------------------------//
