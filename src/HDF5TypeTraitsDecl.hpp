//---------------------------------------------------------------------------//
//!
//! \file HDF5TypeTraitsDecl.hpp
//! \author Alex Robinson
//! \brief HDF5 Type Traits declaration.
//!
//---------------------------------------------------------------------------//

#ifndef HDF5_TYPE_TRAITS_DECL_HPP
#define HDF5_TYPE_TRAITS_DECL_HPP

// HDF5 Includes
#include <H5Cpp.h>

/*! \defgroup hdf5_type_traits HDF5 Type Traits
 *
 * The FACEMC::HDF5FileHandler has many templated member functions. To allow
 * these functions to read and write a variety of data types, a type traits
 * class is needed. The HDF5TypeTraits struct is the struct that defines the
 * type of traits that must be known (static members). To allow for both simple
 * and complex data types, the FACEMC::HDF5TypeTraits struct must be 
 * specialized. Attempting to use the class without a specialization will 
 * result in a compile time error. The compile time error message is defined by
 * the FACEMC::UndefinedTypeTraits struct.
 */

namespace FACEMC{

/*! \brief This is the default structure used by HDF5TypeTraits<T> to produce
 * a compile time error when the specialization does not exist for type T
 *
 * To use the FACEMC::HDF5TypeTraits struct a specialization for the 
 * particular type must be written. When the type does not have a
 * specialization, the compiler will attempt to instantiate this struct, which
 * has a function notDefined() that attempts to access a non-existant type
 * member, causing a compile time error. 
 * \ingroup hdf5_type_traits
 */
template<typename T>
struct UndefinedTypeTraits
{
  //! This function should not compile if there is any attempt to instantiate!
  static inline T notDefined() { return T::this_type_is_missing_a_specialization(); }
};

/*! \brief An empty class used for default template parameters in the 
 * HDF5TypeTraits struct.
 * \ingroup hdf5_type_traits
 */
struct Empty{};

/*! \brief This structure defines the traits that are needed by the 
 * FACEMC::HDF5FileHandler class member functions.
 *
 * This structure defines some basic traits for types to be used in 
 * HDF5. The HDF5 C++ API function calls request a DataType object 
 * corresponding to the type to write to an HDF5 file. A C++ type will map to 
 * the desired HDF5 DataType object using this HDF5TypeTraits struct. The 
 * functions in the templated base unspecialized struct are designed not to 
 * compile (giving a nice compile-time error message) and therefore 
 * specializations must be written for each type to be written to HDF5
 * \note 
 * The defualt defined specializations are provided for int, uint and
 * double. The tuple structs will also provide their own specializations.
 * \tparam T The primary type
 * \tparam T2 A template parameter for T.
 * \tparam T3 A template parameter for T.
 * \tparam T4 A template parameter for T.
 * \tparam T5 A template parameter for T.
 * \ingroup hdf5_type_traits
 */
template<typename T, 
	 typename T2 = Empty, 
	 typename T3 = Empty,
	 typename T4 = Empty,
	 typename T5 = Empty>
struct HDF5TypeTraits
{ 
  //! returns the data type object of the type
  static inline H5::DataType dataType() { (void)UndefinedTypeTraits<T>::notDefined(); return 0; }
  //! Returns the name of this scalar type
  static inline std::string name() { (void)UndefinedTypeTraits<T>::notDefined(); return 0; }
};

} // end FACEMC namespace

#endif // end HDF5_TYPE_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end HDF5TypeTraitsDecl.hpp
//---------------------------------------------------------------------------//
