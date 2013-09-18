//---------------------------------------------------------------------------//
//!
//! \file   ArrayTestingPolicyDecl.hpp
//! \author Alex Robinson
//! \brief  Policy for running tests on arrays
//!
//---------------------------------------------------------------------------//

#ifndef ARRAY_TESTING_POLICY_DECL_HPP
#define ARRAY_TESTING_POLICY_DECL_HPP

// Trilinos Includes
#include <Teuchos_ArrayView.hpp>

/*! \defgroup array_testing_policy Array Testing Policy
 * \ingroup policies
 * \ingroup testing
 *
 * To reduce the number of unit tests that need to be written, many have been
 * templated. To facilitate templated unit tests that deal with different
 * array types, a bridge pattern was implemented through the
 * FACEMC::ArrayTestingPolicy that homogenizes the different array interfaces.
 * Because of the slightly different interfaces for each array type, the 
 * FACEMC::ArrayTestingPolicy struct must be specialized. Attempting to use
 * the struct without a specialization will result in a compile time error.
 * The compile time error message is defined by the 
 * FACEMC::UndefinedArrayTestingPolicy struct.
 */

namespace FACEMC{

/*! \brief Default structure used by FACEMC::ArrayTestigPolicy to produce a 
 * compile time error when the specialization does not exist for array type 
 * Array.
 *
 * To use the FACEMC::HDF5ArrayTestingPolicy struct a partial template
 * specialization for the particular array must be written. When the type of
 * array does not have a partial specialization, the compiler will attempt to
 * instantiate this struct, which has a function notDefined() that attempts to
 * access a non-existant Array member, causing a compile time error.
 * \ingroup array_testing_policy
 */
template<typename T,template<typename> class Array>
struct UndefinedArrayTestingPolicy
{
  //! This function should not compile if there is any attempt to instantiate!
  static inline T notDefined() { return Array<T>::this_type_is_missing_a_specialization(); }
};

/*! \brief This structure defines the Array testing policy to be used while 
 * unit testing the code.
 *
 * This structure should allow use of any Teuchos::Array when dealing with
 * templated unit tests. Any other arrays will not be supported. The functions 
 * in the templated base unspecialized struct are designed not to compile 
 * (giving a nice compile-time error message) and therefore specializations 
 * must be written for each array type. The design pattern that is implemented
 * with this templated class is the bridge pattern. Every array type has a
 * slightly different interface. This templated class homogenizes the interface
 * so that they can all be used inside of the templated unit tests.
 * \tparam T A data type that is stored in the Array
 * \tparam Array An array class with a single template parameter.
 * \note The default defined specializations are provided for Teuchos::Array,
 * Teuchos::ArrayRCP, Teuchos::ArrayView and Teuchos::TwoDArray.
 * \ingroup array_testing_policy
 */
template<typename T,template<typename> class Array>
struct ArrayTestingPolicy
{
  //! Return a Teuchos::ArrayView corresponding to this array.
  static inline Teuchos::ArrayView<T> view( Array<T> &array ) { (void)UndefinedArrayTestingPolicy<T,Array>::notDefined(); }
  //! Return a const Teuchos::ArrayView corresponding to this array.
  static inline Teuchos::ArrayView<const T> view( const Array<T> &array ) { (void)UndefinedArrayTestingPolicy<T,Array>::notDefined(); }
  //! Create a new array from a Teuchos::ArrayView.
  static inline Array<T> createArrayFromView( const Teuchos::ArrayView<T> &array_view ) { (void)UndefinedArrayTestingPolicy<T,Array>::notDefined(); }
  //! Resize the array.
  static inline void resize( Array<T> &array, const typename Array<T>::size_type size ) { (void)UndefinedArrayTestingPolicy<T,Array>::notDefined(); }
  //! Return the size of the array.
  static inline typename Array<T>::size_type size( const Array<T> &array ) { (void)UndefinedArrayTestingPolicy<T,Array>::notDefined(); }
};

} // end FACEMC namespace

#endif // end ARRAY_TESTING_POLICY_DECL_HPP

//---------------------------------------------------------------------------//
// end ArrayTestingPolicyDecl.hpp
//---------------------------------------------------------------------------//

