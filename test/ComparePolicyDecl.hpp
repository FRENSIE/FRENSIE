//---------------------------------------------------------------------------//
// \file   ComparePolicyDecl.hpp
// \author Alex Robinson
// \brief  Compare policy declaration for all types
//---------------------------------------------------------------------------//

#ifndef COMPARE_POLICY_DECL_HPP
#define COMPARE_POLICY_DECL_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_FancyOStream.hpp>

namespace FACEMC{

/*!
 * \brief This is the default structure used  by ComparePolicyDecl<T>
 * to produce a compile time error when the specialization does not exist for
 * the desired type T.
 */
template<typename T>
struct UndefinedComparePolicy
{
  static inline T notDefined() { return T::this_type_is_missing_a_specialization(); }
};

struct EmptyTypeStruct{};

/*!
 * \brief This structure defines if two values compare equal. The functions in
 * the templated base unsecialized struct are designed not to compile (giving a 
 * nice compile-time error message) and therefore specializations must be 
 * written for each Tuple type.
 */
template<typename T,
	 typename T2 = EmptyTypeStruct,
	 typename T3 = EmptyTypeStruct,
	 typename T4 = EmptyTypeStruct,
	 typename T5 = EmptyTypeStruct>
struct ComparePolicy
{
  static inline bool compare( const T &first_value,
			      const std::string &first_name,
			      const T &second_value,
			      const std::string &second_name,
			      Teuchos::FancyOStream &out,
			      const int index = -1,
			      const double tol = 0.0 )
  { (void)UndefinedComparePolicy<T>::notDefined(); }
};

} // end FACEMC namespace

#endif // end COMPARE_POLICY_DECL_HPP

//---------------------------------------------------------------------------//
// end ComparePolicyDecl.hpp
//---------------------------------------------------------------------------//
