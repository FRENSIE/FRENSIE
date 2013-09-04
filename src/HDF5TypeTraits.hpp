//---------------------------------------------------------------------------//
//!
//! \file HDF5TypeTraits.hpp
//! \author Alex Robinson
//! \brief HDF5 Type Traits specializations
//!
//---------------------------------------------------------------------------//

#ifndef HDF5_TYPE_TRAITS_HPP
#define HDF5_TYPE_TRAITS_HPP

// FACEMC Includes
#include "HDF5TypeTraitsDecl.hpp"

namespace FACEMC{
 
/*! \brief The specialization of the FACEMC::HDF5TypeTraits for double
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<double>
{
  static inline H5::PredType dataType() { return H5::PredType::NATIVE_DOUBLE; }
  static inline std::string name() { return "double"; }
};

/*! \brief The specialization of the FACEMC::HDF5TypeTraits for int
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<int>
{
  static inline H5::PredType dataType() { return H5::PredType::NATIVE_INT; }
  static inline std::string name() { return "int"; }
};

/*! \brief The specialization of the FACEMC::HDF5TypeTraits for unsigned int
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<unsigned int>
{
  static inline H5::PredType dataType() { return H5::PredType::NATIVE_UINT; }
  static inline std::string name() { return "unsigned int"; }
};

} // end FACEMC namespace

#endif // end HDF5_TYPE_TRAITS_HPP

//---------------------------------------------------------------------------//
// end HDF5TypeTraits.hpp
//---------------------------------------------------------------------------//
