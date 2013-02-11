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
  typedef H5T_NATIVE_DOUBLE memoryType;
  typedef H5T_IEEE_F64BE fileTypeBE;
  typedef H5T_IEEE_F64LE fileTypeLE;

  static inline std::string name() { return "double"; }
};

template<>
struct HDF5ScalarTraits<int>
{
  typedef H5T_NATIVE_INT memoryType;
  typedef H5T_STD_I32BE fileTypeBE;
  typedef H5T_STD_I32LE fileTypeLE;
  
  static inline std::string name() { return "int"; }
};

template<>
struct HDF5ScalarTraits<unsigned int>
{
  typedef H5T_NATIVE_UINT memoryType;
  typedef H5T_STD_U32BE fileTypeBE;
  typedef H5T_STD_U32LE fileTypeLE;

  static inline std::string name() { return "unsigned int"; }
};

} // end FACEMC namespace

#endif // end HDF5_SCALAR_TRAITS_HPP

//---------------------------------------------------------------------------//
// end HDF5ScalarTraits.hpp
//---------------------------------------------------------------------------//
