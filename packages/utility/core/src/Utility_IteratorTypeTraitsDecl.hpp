//---------------------------------------------------------------------------//
//!
//! \file   Utility_IteratorTypeTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  Iterator type traits class declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ITERATOR_TYPE_TRAITS_DECL_HPP
#define UTILITY_ITERATOR_TYPE_TRAITS_DECL_HPP

// Std Lib Includes
#include <type_traits>

// FRENSIE Includes
#include "Utility_UndefinedTraits.hpp"

/*! \defgroup iterator_type_traits Iterator Type Traits
 * \ingroup traits
 */

namespace Utility{

/*! Check if an iterator is a const iterator
 * \ingroup iterator_type_traits
 */
template<typename T, typename Enabled = void>
struct IsConstIterator;

/*! Get the const iterator associated with the iterator of interest
 * \ingroup iterator_type_traits
 */
template<typename T, typename Enabled = void>
struct ConstIterator;

/*! Get the iterator associated with the const iterator of interest
 * \ingroup iterator_type_traits
 */
template<typename T, typename Enabled = void>
struct NonConstIterator;
  
} // end Utility namespace

#endif // end UTILITY_ITERATOR_TYPE_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_IteratorTypeTraitsDecl.hpp
//---------------------------------------------------------------------------//

