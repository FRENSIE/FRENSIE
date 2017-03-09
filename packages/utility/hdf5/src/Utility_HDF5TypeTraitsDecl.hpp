//---------------------------------------------------------------------------//
//!
//! \file   Utility_HDF5TypeTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  HDF5 Type Traits declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HDF5_TYPE_TRAITS_DECL_HPP
#define UTILITY_HDF5_TYPE_TRAITS_DECL_HPP

// HDF5 Includes
#include <H5Cpp.h>

// FRENSIE Includes
#include "Utility_UndefinedTraits.hpp"

/*! \defgroup hdf5_type_traits HDF5 Type Traits
 * \ingroup traits
 *
 * The Utility::HDF5FileHandler has many templated member functions. To allow
 * these functions to read and write a variety of data types, a type traits
 * class is needed. The HDF5TypeTraits struct is the struct that defines the
 * type of traits that must be known (static members). To allow for both simple
 * and complex data types, the Utility::HDF5TypeTraits struct must be
 * specialized. Attempting to use the class without a specialization will
 * result in a compile time error. The compile time error message is defined by
 * the Utility::UndefinedTypeTraits struct.
 */

namespace Utility{

/*! \brief This structure defines the traits that are needed by the
 * Utility::HDF5FileHandler class member functions.
 *
 * This structure defines some basic traits for types to be used in
 * HDF5. The HDF5 C++ API function calls request a DataType object
 * corresponding to the type to write to an HDF5 file. A C++ type will map to
 * the desired HDF5 DataType object using this HDF5TypeTraits struct. The
 * functions in the templated base unspecialized struct are designed not to
 * compile (giving a nice compile-time error message) and therefore
 * specializations must be written for each type to be written to HDF5
 * \note The defualt defined specializations are provided for int, uint and
 * double. The tuple structs will also provide their own specializations.
 * \ingroup hdf5_type_traits
 */
template<typename T, typename Enabled = void>
struct HDF5TypeTraits
{
  //! Typedef for the raw type
  typedef T RawType;
  
  //! Returns the HDF5 data type object corresponding to the type
  static inline H5::DataType dataType()
  { (void)UndefinedTraits<T>::notDefined(); return 0; }

  //! Returns the name of this type
  static inline std::string name()
  { (void)UndefinedTraits<T>::notDefined(); return 0; }

  //! Returns the zero value for this type
  static inline RawType zero()
  { (void)UndefinedTraits<T>::notDefined(); return 0; }

  //! Returns the unity value for this type
  static inline RawType one()
  { (void)UndefinedTraits<T>::notDefined(); return 0; }
};

} // end Utility namespace

#endif // end UTILITY_HDF5_TYPE_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_HDF5TypeTraitsDecl.hpp
//---------------------------------------------------------------------------//
