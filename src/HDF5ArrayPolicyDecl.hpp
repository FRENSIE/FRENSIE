//---------------------------------------------------------------------------//
//!
//! \file   HDF5ArrayPolicyDecl.hpp
//! \author Alex Robinson
//! \brief  HDF5 Array Policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef HDF5_ARRAY_POLICY_DECL_HPP
#define HDF5_ARRAY_POLICY_DECL_HPP

/*! \defgroup hdf5_array_policy HDF5 Array Policy
 * \ingroup policies
 *
 * The FACEMC::HDF5FileHandler has many templated member functions 
 * with a template template parameter (Array). Because the Teuchos array 
 * classes have slightly different interfaces, a policy class is needed to 
 * homogenize the interfaces (bridge pattern). The FACEMC::HDF5ArrayPolicy is 
 * the struct that defines the interface. Because of the slightly different 
 * interfaces for each array type, the FACEMC::HDF5ArrayPolicy class must be 
 * specialized. Attempting to use the class without a specialization will 
 * result in a compile time error. The compile time error message is defined by 
 * the FACEMC::UndefinedArrayPolicy struct.
 */

namespace FACEMC{

/*! \brief Default structure used by FACEMC::ArrayPolicy to produce a compile 
 * time error when the specialization does not exist for array type Array.
 *
 * To use the FACEMC::HDF5ArrayPolicy struct a partial template specialization 
 * for the particular array must be written. When the type of array does not
 * have a partial specialization, the compiler will attempt to instantiate this
 * struct, which has a function notDefined() that attemts to access a 
 * non-existant Array member, causing a compile time error.
 * \ingroup hdf5_array_policy
 */
template<typename T, template<typename> class Array>
struct UndefinedArrayPolicy
{
  //! This function should not compile if there is any attempt to instantiate!
  static inline T notDefined() { return Array<T>::this_type_is_missing_a_specialization(); }
};

/*!\brief This structure defines the Array policy to be used in conjunction
 * with the FACEMC::HDF5FileHandler class member functions.
 *
 * This struct should allow use of any Teuchos::Array when dealing with the
 * HDF5 interface. Any other arrays will not be supported. The function in the 
 * templated base unspecialized struct are designed not to compile (giving a 
 * nice compile-time error message) and therefore specializations must be 
 * written for each array type. The design pattern that is implemented with this
 * templated class is the bridge pattern. Every array type has a slightly
 * different interface. This templated class homogenizes the interfaces so
 * that they can all be used inside of the other templated functions used
 * by FACEMC. 
 * \tparam T A data type that is stored in the Array
 * \tparam Array An array class with a single template parameter.
 * \note The default defined specializations are provided for Teuchos::Array,
 * Teuchos::ArrayRCP, Teuchos::ArrayView and Teuchos::TwoDArray.
 * \ingroup hdf5_array_policy
 */
template<typename T, template<typename> class Array>
struct HDF5ArrayPolicy
{
  //! Return a raw pointer to the head of the array
  static inline T* getRawPtr(Array<T> &array) { (void)UndefinedArrayPolicy<T,Array>::notDefined(); return 0; }
  //! Return a const raw pointer to the head of the array
  static inline const T* getRawPtr(const Array<T> &array) { (void)UndefinedArrayPolicy<T,Array>::notDefined(); return 0; }
  //! Resize the array
  static inline void resize(Array<T> &array, typename Array<T>::size_type n) { (void)UndefinedArrayPolicy<T,Array>::notDefined(); return 0; }
  //! Return the size of the array
  static inline typename Array<T>::size_type size(const Array<T> &array){ (void)UndefinedArrayPolicy<T,Array>::notDefined(); return 0; }
};

} // end FACEMC namespace

#endif // end HDF5_ARRAY_POLICY_DECL_HPP

//---------------------------------------------------------------------------//
// end HDF5ArrayPolicyDecl.hpp
//---------------------------------------------------------------------------//

