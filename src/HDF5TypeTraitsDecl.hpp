//---------------------------------------------------------------------------//
// \file HDF5TypeTraitsDecl.hpp
// \author Alex Robinson
// \brief HDF5 Type Traits declaration.
//---------------------------------------------------------------------------//

#ifndef HDF5_TYPE_TRAITS_DECL_HPP
#define HDF5_TYPE_TRAITS_DECL_HPP

// HDF5 Includes
#include <H5Cpp.h>

namespace FACEMC{

/*!
 * \brief This is the default structure used by HDF5TypeTraits<T> to produce
 * a compile time error when the specialization does not exist for type T
 */
template<typename T>
struct UndefinedTypeTraits
{
  //! This function should not compile if there is any attempt to instantiate!
  static inline T notDefined() { return T::this_type_is_missing_a_specialization(); }
};

/*!
 * \brief This is an empty class used for default template parameters in
 * the HDF5TypeTraits struct
 */
struct Empty{};

/*!
 * \brief This structure defines some basic traits for types to be used in 
 * HDF5. The HDF5 C++ API function calls request a DataType object 
 * corresponding to the type to write to an HDF5 file. A C++ type will map to 
 * the desired HDF5 DataType object using this HDF5TypeTraits struct. The 
 * functions in the templated base unspecialized struct are designed not to 
 * compile (giving a nice compile-time error message) and therefore 
 * specializations must be written for each type to be written to HDF5
 * \note <ol>
 * <li> The defualt defined specializations are provided for \c int, \c uint, 
 * \c double
 * </ol>
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
