//---------------------------------------------------------------------------//
// \file   TypeTestingPolicyDecl.hpp
// \author Alex Robinson
// \brief  Policy for testing basic types
//---------------------------------------------------------------------------//

#ifndef TYPE_TESTING_POLICY_DECL_HPP
#define TYPE_TESTING_POLICY_DECL_HPP

namespace FACEMC{

/*!
 * \brief This is the default structure used by TypeTestingPolicyDecl<T>
 * to produce a compile time error when the specialization does not exist for
 * the desired type.
 */
template<typename T>
struct UndefinedTypeTestingPolicy
{
  static inline T notDefined() { return T::this_type_is_missing_a_specialization(); }
};

struct EmptyStruct{};

/*!
 * \brief This structure defines a useful interface for testing basic types
 * in the Teuchos Unit Test Harness. The functions in the templated base
 * unspecialized struct are designed not to compile (giving a nice compile-time
 * error message) and therefore specializations must be written for each type.
 */
  template<typename T,
	 typename T2 = EmptyStruct,
	 typename T3 = EmptyStruct,
	 typename T4 = EmptyStruct,
	 typename T5 = EmptyStruct>
struct TypeTestingPolicy
{
  static inline void initialize( T &data ) { (void)UndefinedTypeTestingPolicy<T>::notDefined(); }
  static inline void zero( T &data ) { (void)UndefinedTypeTestingPolicy<T>::notDefined(); }
};

} // end FACEMC namespace

#endif // end TYPE_TESTING_POLICY_DECL_HPP

//---------------------------------------------------------------------------//
// end TypeTestingPolicyDecl.hpp
//---------------------------------------------------------------------------//
