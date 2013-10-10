//---------------------------------------------------------------------------//
//!
//! \file HDF5TypeTraits.hpp
//! \author Alex Robinson
//! \brief HDF5 Type Traits specializations
//!
//---------------------------------------------------------------------------//

#ifndef HDF5_TYPE_TRAITS_HPP
#define HDF5_TYPE_TRAITS_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "HDF5TypeTraitsDecl.hpp"

namespace FACEMC{

namespace Traits{
 
/*! \brief The specialization of the FACEMC::HDF5TypeTraits for double
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<double>
{
  //! Returns the HDF5 data type object corresponding to double
  static inline H5::PredType dataType() 
  { return H5::PredType::NATIVE_DOUBLE; }
  
  //! Returns the name of this type
  static inline std::string name() 
  { return "double"; }
  
  //! Returns the zero value for this type
  static inline double zero() 
  { return Teuchos::ScalarTraits<double>::zero(); }

  //! Returns the unity value for this type
  static inline double one()
  { return Teuchos::ScalarTraits<double>::one(); }
};

/*! \brief The specialization of the FACEMC::HDF5TypeTraits for float
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<float>
{
  //! Returns the HDF5 data type object corresponding to double
  static inline H5::PredType dataType() 
  { return H5::PredType::NATIVE_FLOAT; }
  
  //! Returns the name of this type
  static inline std::string name() 
  { return "double"; }
  
  //! Returns the zero value for this type
  static inline float zero() 
  { return Teuchos::ScalarTraits<float>::zero(); }

  //! Returns the unity value for this type
  static inline float one()
  { return Teuchos::ScalarTraits<float>::one(); }
};

/*! \brief The specialization of the FACEMC::HDF5TypeTraits for int
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<int>
{
  //! Returns the HDF5 data type object corresponding to int
  static inline H5::PredType dataType() 
  { return H5::PredType::NATIVE_INT; }

  //! Returns the name of this type
  static inline std::string name() 
  { return "int"; }

  //! Returns the zero value for this type
  static inline int zero()
  { return Teuchos::ScalarTraits<int>::zero(); }

  //! Returns the unity value for this type
  static inline int one()
  { return Teuchos::ScalarTraits<int>::one(); }
};

/*! \brief The specialization of the FACEMC::HDF5TypeTraits for unsigned int
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<unsigned int>
{
  //! Returns the HDF5 data type object corresponding to unsigned int
  static inline H5::PredType dataType() 
  { return H5::PredType::NATIVE_UINT; }
  
  //! Returns the name of the type
  static inline std::string name() 
  { return "unsigned int"; }
  
  //! Returns the zero value for this type
  static inline unsigned zero()
  { return Teuchos::ScalarTraits<unsigned>::zero(); }

  //! Returns the unity value for this type
  static inline unsigned one()
  { return Teuchos::ScalarTraits<unsigned>::one(); }
};

} // end Traits namespace

} // end FACEMC namespace

#endif // end HDF5_TYPE_TRAITS_HPP

//---------------------------------------------------------------------------//
// end HDF5TypeTraits.hpp
//---------------------------------------------------------------------------//
