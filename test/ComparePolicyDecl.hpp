//---------------------------------------------------------------------------//
//!
//! \file   ComparePolicyDecl.hpp
//! \author Alex Robinson
//! \brief  Compare policy declaration for all types
//! 
//---------------------------------------------------------------------------//

#ifndef COMPARE_POLICY_DECL_HPP
#define COMPARE_POLICY_DECL_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_FancyOStream.hpp>

// FACEMC Includes
#include "Empty.hpp"

/*! \defgroup compare_policy Compare Policy
 * \ingroup policies
 * \ingroup testing
 *
 * The <em> Teuchos Unit Test Harness </em> only supports testing of basic
 * types. The FACEMC::ComparePolicy allows testing equality of tuple structs
 * as well (either FACEMC::Pair, FACEMC::Trip or FACEMC::Quad). The 
 * FACEMC::ComparePolicy struct must be specialized in order to work properly.
 * Attempting to use the struct without a specialization will result in a 
 * compile time error. The compile time error message is defined by the
 * FACEMC::UndefinedComparePolicy struct.
 */

namespace FACEMC{

/*! \brief Default structure used by FACEMC::ComparePolicy to produce a
 * compile time error when the specialization does not exist for type T.
 *
 * To use the FACEMC::ComparePolicy struct a template specialization for
 * the particular type must be written. When the type does not have a
 * partial specialization, the compiler will attempt to instantiate
 * this struct, which has a function notDefined() that attempts to
 * access a non-existant member, causing a compile time error. 
 * \ingroup compare_policy
 */
template<typename T>
struct UndefinedComparePolicy
{
  //! This function should not compile if there is any attempt to instantiate!
  static inline T notDefined() { return T::this_type_is_missing_a_specialization(); }
};

/*! \brief This structure defines the compare policy that will be used while
 * unit testing the code. 
 *
 * The goal is to be able to test if the values of two generic types are equal
 * within the <em> Teuchos Unit Test Harness. </em> The functions in the 
 * templated base unspecialized struct are designed not to compile (giving a 
 * nice compile-time error message) and therefore specializations must be 
 * written for each type that will be tested.   
 * \tparam T A data type that will be tested.
 * \tparam T2 A second data type that will be tested.
 * \tparam T3 A third data type that will be tested.
 * \tparam T4 A fourth data type that will be tested.
 * \note The default defined specializations are provided for double and
 * unsigned int. There are also partial specializations provided for 
 * FACEMC::Pair, FACEMC::Trip and FACEMC::Quad. 
 * \ingroup compare_policy
 */
template<typename T,
	 typename T2 = Empty,
	 typename T3 = Empty,
	 typename T4 = Empty>
struct ComparePolicy
{
  /*! Compare two values of a type.
   *
   * \details To provide detailed output, it must be known whether the
   * values are elements in an array. If so, the optional index parameter
   * should be used to indicate the index of the element in the array. When
   * testing floating point values it is often necessary to have a testing
   * tolerance, which can be set with the final parameter. 
   * \param[in] first_value The first value that will be tested.
   * \param[in] first_name The name given to the first value, which will be 
   * used to refer to the value if the test fails.
   * \param[in] second_value The second value that will be tested.
   * \param[in] second_name The name given to the second value, which will be 
   * used to refer to the value if the test fails.
   * \param[in,out] out The output stream that will be used to output the
   * results of the test.
   * \param[in] index The index in the array that corresponds to the values
   * being tested. An index of -1 indicates that the values are not part
   * of an array.
   * \param[in] tol The testing tolerance used to compare floating point
   * values. This will be ignored with integer comparisons.
   */
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
