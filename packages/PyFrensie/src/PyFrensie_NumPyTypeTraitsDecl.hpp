//---------------------------------------------------------------------------//
//!
//! \file   PyFrensie_NumPyTypeTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  The NumPy type traits class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef PYFRENSIE_NUMPY_TYPE_TRAITS_DECL_HPP
#define PYFRENSIE_NUMPY_TYPE_TRAITS_DECL_HPP

// FRENSIE includes
#include "Utility_UndefinedTraits.hpp"

/*! \defgroup numpy_type_traits NumPy Type Traits
 * \ingroup traits
 */

namespace PyFrensie{

/*! \brief  This structure defines the traits that are needed to map
 * C++ types to NumPy typecode.
 * \ingroup numpy_type_traits
 */
template<typename T>
struct NumPyTypeTraits
{
  //! Return the NumPy typecode corresponding to T
  static inline int typecode()
  { (void)Utility::UndefinedTraits<T>::notDefined(); return 0; }

  //! Return the NumPy typecode corresponding to an instance of T
  static inline int instanceTypecode( const T instance )
  { (void)Utility::UndefinedTraits<T>::notDefined(); return 0; }
};

/*! This function allows access to the instanceTypecode NumPyTypeTraits method.
 * \ingroup numpy_type_traits
 */
template<typename T>
inline int numpyTypecode( const T instance )
{ return NumPyTypeTraits<T>::instanceTypecode( instance ); }

} // end PyFrensie namespace

#endif // end PYFRENSIE_NUMPY_TYPE_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end PyFrensie_NumPyTraitsDecl.hpp
//---------------------------------------------------------------------------//
