//---------------------------------------------------------------------------//
// \file   TupleComparePolicyDecl.hpp
// \author Alex Robinson
// \brief  Tuple compare policy declaration
//---------------------------------------------------------------------------//

#ifndef TUPLE_COMPARE_POLICY_DECL_HPP
#define TUPLE_COMPARE_POLICY_DELC_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_FancyOStream.hpp>

namespace FACEMC{

/*!
 * \brief This is the default structure used by TupleComparePolicyDecl<Tuple>
 * to produce a compile time error when the specialization does not exist for
 * the desired tuple member.
 */
template<typename T>
struct UndefinedTupleComparePolicy
{
  static inline T notDefined() { return T::this_type_is_missing_a_specialization(); }
};

struct EmptyTupleStruct{};

/*!
 * \brief This structure defines if two tuples compare equal. The functions in
 * the templated base unspecialized struct are designed not to compile (giving
 * a nice compile-time error message) and therefore specializations must be
 * written for each Tuple type.
 */
template<typename T,
	 typename T2 = EmptyTupleStruct,
	 typename T3 = EmptyTupleStruct,
	 typename T4 = EmptyTupleStruct,
	 typename T5 = EmptyTupleStruct>
struct TupleComparePolicy
{
  static inline bool compare( const T &first_tuple, 
			      const std::string &first_name,
			      const T &second_tuple,
			      const std::string &second_name,
			      Teuchos::FancyOStream &out, 
			      const int index = -1, 
			      const double tol = 0.0 ) 
  { (void)UndefinedTupleComparePolicy<T>::notDefined(); }
};

} // end FACEMC namespace

#endif // end TUPLE_COMPARE_POLICY_DECL_HPP

//---------------------------------------------------------------------------//
// end TupleComparePolicyDecl.hpp
//---------------------------------------------------------------------------//
