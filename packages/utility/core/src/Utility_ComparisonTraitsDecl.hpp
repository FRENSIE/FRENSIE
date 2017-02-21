//---------------------------------------------------------------------------//
//!
//! \file   Utility_ComparisonTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  Comparison traits declaration for all types
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_COMPARISON_TRAITS_DECL_HPP
#define UTILITY_COMPARISON_TRAITS_DECL_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_FancyOStream.hpp>

// FRENSIE Includes
#include "Utility_UndefinedTraits.hpp"

/*! \defgroup comparison_traits Comparison Traits 
 * \ingroup traits
 * \ingroup testing
 *
 * The <em> Teuchos Unit Test Harness </em> only supports testing of basic
 * types. The Utility::ComparisonTraits allows testing equality of std::tuple
 * and Utility::Tuple classes. The Utility::ComparisonTraits struct must be 
 * specialized in order to work properly. Attempting to use the struct without
 * a specialization will result in a compile time error. The compile time error
 * message is defined by the Utility::UndefinedTraits struct.
 */

namespace Utility{

/*! \brief This structure defines the comparison that can be used to compare
 * two values of arrays of values.
 *
 * The goal is to be able to test if the values of two generic types are equal
 * within the <em> Teuchos Unit Test Harness. </em> The functions in the
 * templated base unspecialized struct are designed not to compile (giving a
 * nice compile-time error message) and therefore specializations must be
 * written for each type that will be tested.
 * \tparam T A data type that will be tested.
 * \tparam Enabled A hidden data type that can be used with the std::enable_if
 * struct to help with template specializations (using SFINAE).
 * \ingroup comparison_traits
 */
template<typename T, typename Enabled = void>
struct ComparisonTraits
{
  //! Typdef for scalar type
  typedef typename UndefinedTraits<T>::DesiredTypeIsMissingSpecialization scalarType;

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
  static inline bool compare( const T& first_value,
			      const std::string& first_name,
			      const T& second_value,
			      const std::string& second_name,
			      Teuchos::FancyOStream& out,
			      const int index = -1,
			      const double tol = 0.0 )
  { (void)UndefinedTraits<T>::notDefined(); }
};

/*! Compare two values and print the results (to the desired stream)
 *
 * This function gives access to the ComparisonTraits::compare method.
 * \ingroup comparison_traits
 */
template<typename T>
inline bool compare( const T& first_value,
                     const std::string& first_name,
                     const T& second_value,
                     const std::string& second_name,
                     Teuchos::FancyOStream& out,
                     const int index = -1,
                     const double tol = 0.0 )
{
  return ComparisonTraits<T>::compare( first_value,
                                       first_name,
                                       second_value,
                                       second_name,
                                       out,
                                       index,
                                       tol );
}

/*! Relative error of two values
 *
 * This helper function is used in the implementation of the comparison traits
 * compare methods for many specializations. However, it can be used in
 * other contexts as well.
 * \ingroup comparison_traits
 */
template<typename ScalarType>
ScalarType relError( const ScalarType first_value,
		     const ScalarType second_value )
{
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typename ST::magnitudeType err;
  if( first_value != ST::zero() && second_value != ST::zero() )
  {
    err = ST::magnitude( first_value - second_value )/
      std::max( ST::magnitude( first_value ),
		ST::magnitude( second_value ) );
  }
  else
  {
    err = std::max( ST::magnitude( first_value ),
		    ST::magnitude( second_value ) );
  }

  return err;
}

} // end Utility namespace

#endif // end UTILITY_COMPARISON_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_ComparisonTraitsDecl.hpp
//---------------------------------------------------------------------------//
