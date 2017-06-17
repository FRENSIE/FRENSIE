//---------------------------------------------------------------------------//
//!
//! \file   Utility_IteratorTypeTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  Iterator type traits class declaration
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
template<typename T>
struct isConstIterator<T> : public UndefinedTraits<T>
{ /* ... */ };

/*! Get the const iterator associated with the iterator of interest
 * \ingroup iterator_type_traits
 */
template<typename T>
struct constIterator
{ 
  //! The const iterator type associated with iterator type T
  typedef UndefinedTraits<T>::DesiredTypeIsMissingSpecialization type;
};

/*! Get the iterator associated with the const iterator of interest
 * \ingroup iterator_type_traits
 */
template<typename T>
struct nonConstIterator
{
  //! The iterator type associated with iterator type T
  typedef UndefinedTraits<T>::DesiredTypeIsMissingSpecialization type;
};
  
} // end Utility namespace

#endif // end UTILITY_ITERATOR_TYPE_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_IteratorTypeTraitsDecl.hpp
//---------------------------------------------------------------------------//

