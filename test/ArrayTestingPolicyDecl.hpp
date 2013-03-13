//---------------------------------------------------------------------------//
// \file   ArrayTestingPolicyDecl.hpp
// \author Alex Robinson
// \brief  Policy for running tests on arrays
//---------------------------------------------------------------------------//

#ifndef ARRAY_TESTING_POLICY_DECL_HPP
#define ARRAY_TESTING_POLICY_DECL_HPP

// Trilinos Includes
#include <Teuchos_ArrayView.hpp>

namespace FACEMC{

/*!
 * \brief This is the default structure used by ArrayTestigPolicyDecl<T,Array>
 * to produce a compile time error when the specialization does not exist for
 * the desired array.
 */
template<typename T,template<typename> class Array>
struct UndefinedArrayTestingPolicy
{
  static inline T notDefined() { return Array<T>::this_type_is_missing_a_specialization(); }
};

/*!
 * \brief This structure defines a useful interface for testing Teuchos array
 * containers. The functions in the templated base unspecialized struct are
 * designed not to compile (giving a nice compile-time error message) and 
 * therefore specializations must be written for each array type.
 */
template<typename T,template<typename> class Array>
struct ArrayTestingPolicy
{
  static inline Teuchos::ArrayView<T> view( Array<T> &array ) { (void)UndefinedArrayTestingPolicy<T,Array>::notDefined(); }
  static inline Teuchos::ArrayView<const T> view( const Array<T> &array ) { (void)UndefinedArrayTestingPolicy<T,Array>::notDefined(); }
  static inline void initialize( Array<T> &array ) { (void)UndefinedArrayTestingPolicy<T,Array>::notDefined(); }
  static inline void resize( Array<T> &array ) { (void)UndefinedArrayTestingPolicy<T,Array>::notDefined(); }
};

} // end FACEMC namespace

#endif // end ARRAY_TESTING_POLICY_DECL_HPP

//---------------------------------------------------------------------------//
// end ArrayTestingPolicyDecl.hpp
//---------------------------------------------------------------------------//

