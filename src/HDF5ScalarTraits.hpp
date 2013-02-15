//---------------------------------------------------------------------------//
// \file HDF5ScalarTraits.hpp
// \author Alex Robinson
// \brief HDF5 Scalar Traits specializations
//---------------------------------------------------------------------------//

#ifndef HDF5_SCALAR_TRAITS_HPP
#define HDF5_SCALAR_TRAITS_HPP

// FACEMC includes
#include "HDF5ScalarTraitsDecl.hpp"

namespace FACEMC{

template<>
struct HDF5ScalarTraits<double>
{
  static inline hid_t memoryType() { return H5T_NATIVE_DOUBLE }
  static inline hid_t fileTypeBE() { return H5T_IEEE_F64BE }
  static inline hid_t fileTypeLE() { return H5T_IEEE_F64LE }
  static inline std::string name() { return "double"; }
};

template<>
struct HDF5ScalarTraits<int>
{
  static inline hid_t memoryType() { return H5T_NATIVE_INT }
  static inline hid_t fileTypeBE() { return H5T_STD_I32BE }
  static inline hid_t fileTypeLE() { return H5T_STD_I32LE }
  static inline std::string name() { return "int"; }
};

template<>
struct HDF5ScalarTraits<unsigned int>
{
  static inline hid_t memoryType() { return H5T_NATIVE_UINT }
  static inline hid_t fileTypeBE() { return H5T_STD_U32BE }
  static inline hid_t fileTypeLE() { return H5T_STD_U32LE }
  static inline std::string name() { return "unsigned int"; }
};

} // end FACEMC namespace

#endif // end HDF5_SCALAR_TRAITS_HPP

//---------------------------------------------------------------------------//
// end HDF5ScalarTraits.hpp
//---------------------------------------------------------------------------//
