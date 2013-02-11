//---------------------------------------------------------------------------//
// \file HDF5ScalarTraitsDecl.hpp
// \author Alex Robinson
// \brief HDF5 Scalar Traits declaration.
//---------------------------------------------------------------------------//

#ifndef HDF5_SCALAR_TRAITS_DECL_HPP
#define HDF5_SCALAR_TRAITS_DECL_HPP

// HDF5 includes
#include "hdf5.h"

namespace FACEMC{

/*!
 * \brief This is the default structure used by HDF5ScalarTraits<T> to produce
 * a compile time error when the specialization does not exist for type T
 */
template<typename T>
struct UndefinedScalarTraits
{
  //! This function should not compile if there is any attempt to instantiate!
  static inline T notDefined() { return T::this_type_is_missing_a_specialization(); }
};

/*!
 * \brief This structure defines some basic traits for HDF5 scalar types. The
 * two scalar types that HDF5 function calls request are the memory type
 * and the file type. The file type can be specified as Little Endian (LE) or
 * Big Endian (BE). A C++ type will map to both of these types using this
 * HDF5ScalarTraits struct. The functions in the templated base unspecialized
 * struct are designed not to compile (giving a nice compile-time error 
 * message) and therefore specializations must be written for each scalar
 * type actually used
 * \note <ol>
 * <li> The defualt defined specializations are provided for \c int, \c uint, 
 * \c double
 * </ol>
 */
template<typename T>
struct HDF5ScalarTraits
{ 
  typedef H5T_NATIVE_ memoryType;
  typedef H5T_BE_      fileTypeBE;
  typedef H5T_LE_      fileTypeLE;
  
  //! Returns the name of this scalar type
  static inline std::string name() { (void)UndefinedScalarTraits<T>::notDefined(); return 0 }
}

} // end FACEMC namespace

#endif // end HDF5_SCALAR_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end HDF5ScalarTraitsDecl.hpp
//---------------------------------------------------------------------------//
