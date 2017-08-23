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
#include <iostream>
#include <string>
#include <cmath>
#include <type_traits>

// FRENSIE Includes
#include "Utility_UndefinedTraits.hpp"
#include "Utility_QuantityTraits.hpp"

/*! \defgroup comparison_traits Comparison Traits 
 * \ingroup traits
 * \ingroup testing
 *
 * The Utility::ComparisonTraits allows testing equality of td::tuple
 * and Utility::Tuple classes. The Utility::ComparisonTraits struct must be 
 * specialized in order to work properly. Attempting to use the struct without
 * a specialization will result in a compile time error. The compile time error
 * message is defined by the Utility::UndefinedTraits struct.
 */

namespace Utility{

/*! \brief This structure defines the comparison that can be used to compare
 * two values of arrays of values.
 *
 * The goal is to be able to test if the values of two generic types are equal.
 * The default ComparisonTraits class will be used unless a specialization is
 * made for your type. 
 * \tparam T A data type that will be tested.
 * \tparam Enabled A hidden data type that can be used with the std::enable_if
 * struct to help with template specializations (using SFINAE).
 * \ingroup comparison_traits
 */
template<typename T, typename Enabled = void>
struct ComparisonTraits
{
  //! The extra data type (usually a comparison tolerance)
  typedef typename QuantityTraits<T>::RawType ExtraDataType;

  //! Create a comparison header
  template<typename ComparisonPolicy>
  static std::string createComparisonHeader(
                           const T& left_value,
                           const std::string& left_name,
                           const bool log_left_name,
                           const T& right_value,
                           const std::string& right_name,
                           const bool log_right_name,
                           const std::string& name_suffix,
                           const ExtraDataType& extra_data = ExtraDataType() );
  
  /*! Compare two values of a type (default)
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
  template<typename ComparisonPolicy>
  static bool compare( const T& left_value,
                       const std::string& left_name,
                       const bool log_left_name,
                       const T& right_value,
                       const std::string& right_name,
                       const bool log_right_name,
                       const std::string& name_suffix,
                       std::ostream& log,
                       const bool log_comparison_details = false,
                       const ExtraDataType& extra_data = ExtraDataType() );
};

/*! Create a comparison header
 *
 * This function provides a shortcut to the 
 * ComparisonTraits::createComparisonHeader method.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy, typename T>
std::string createComparisonHeader(
                const T& left_value,
                const std::string& left_name,
                const T& right_value,
                const std::string& right_name,
                const typename ComparisonTraits<T>::ExtraDataType& extra_data =
                typename ComparisonTraits<T>::ExtraDataType(),
                const std::string& name_suffix = "" );

/*! Compare two values and print the results (to the desired stream)
 *
 * This function provides a shortcut to the ComparisonTraits::compare method.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy, typename T>
bool compare( const T& left_value,
              const std::string& left_name,
              const T& right_value,
              const std::string& right_name,
              std::ostream& log,
              const typename ComparisonTraits<T>::ExtraDataType& extra_data =
              typename ComparisonTraits<T>::ExtraDataType(),
              const bool log_comparison_details = false,
              const std::string& name_suffix = "" );

/*! Create a comparison header
 *
 * This function provides a shortcut to the 
 * ComparisonTraits::createComparisonHeader method.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy, typename T>
std::string createComparisonHeader(
                T& left_value,
                const std::string& left_name,
                T& right_value,
                const std::string& right_name,
                const typename ComparisonTraits<T>::ExtraDataType& extra_data =
                typename ComparisonTraits<T>::ExtraDataType(),
                const std::string& name_suffix = "" );

/*! Compare two values and print the results (to the desired stream)
 *
 * This function provides a shortcut to the ComparisonTraits::compare method.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy, typename T>
bool compare( T& left_value,
              const std::string& left_name,
              T& right_value,
              const std::string& right_name,
              std::ostream& log,
              const typename ComparisonTraits<T>::ExtraDataType& extra_data =
              typename ComparisonTraits<T>::ExtraDataType(),
              const bool log_comparison_details = false,
              const std::string& name_suffix = "" );

/*! Create a comparison header
 *
 * This function provides a shortcut to the 
 * ComparisonTraits::createComparisonHeader method.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy, typename T1, typename T2>
std::string createComparisonHeader(
               T1&& left_value,
               const std::string& left_name,
               const T2& right_value,
               const std::string& right_name,
               const typename ComparisonTraits<T2>::ExtraDataType& extra_data =
               typename ComparisonTraits<T2>::ExtraDataType(),
               const std::string& name_suffix = "" );

/*! Compare two values and print the results (to the desired stream)
 *
 * This function provides a shortcut to the ComparisonTraits::compare method.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy, typename T1, typename T2>
bool compare( T1&& left_value,
              const std::string& left_name,
              const T2& right_value,
              const std::string& right_name,
              std::ostream& log,
              const typename ComparisonTraits<T2>::ExtraDataType& extra_data =
              typename ComparisonTraits<T2>::ExtraDataType(),
              const bool log_comparison_details = false,
              const std::string& name_suffix = "" );

/*! Create a comparison header
 *
 * This function provides a shortcut to the 
 * ComparisonTraits::createComparisonHeader method.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy, typename T1, typename T2>
std::string createComparisonHeader(
               T1&& left_value,
               const std::string& left_name,
               T2& right_value,
               const std::string& right_name,
               const typename ComparisonTraits<T2>::ExtraDataType& extra_data =
               typename ComparisonTraits<T2>::ExtraDataType(),
               const std::string& name_suffix = "" );

/*! Compare two values and print the results (to the desired stream)
 *
 * This function provides a shortcut to the ComparisonTraits::compare method.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy, typename T1, typename T2>
bool compare( T1&& left_value,
              const std::string& left_name,
              T2& right_value,
              const std::string& right_name,
              std::ostream& log,
              const typename ComparisonTraits<T2>::ExtraDataType& extra_data =
              typename ComparisonTraits<T2>::ExtraDataType(),
              const bool log_comparison_details = false,
              const std::string& name_suffix = "" );

/*! Create a comparison header
 *
 * This function provides a shortcut to the 
 * ComparisonTraits::createComparisonHeader method.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy, typename T1, typename T2>
std::string createComparisonHeader(
               const T1& left_value,
               const std::string& left_name,
               T2&& right_value,
               const std::string& right_name,
               const typename ComparisonTraits<T1>::ExtraDataType& extra_data =
               typename ComparisonTraits<T1>::ExtraDataType(),
               const std::string& name_suffix = "" );
  
/*! Compare two values and print the results (to the desired stream)
 *
 * This function provides a shortcut to the ComparisonTraits::compare method.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy, typename T1, typename T2>
bool compare( const T1& left_value,
              const std::string& left_name,
              T2&& right_value,
              const std::string& right_name,
              std::ostream& log,
              const typename ComparisonTraits<T1>::ExtraDataType& extra_data =
              typename ComparisonTraits<T1>::ExtraDataType(),
              const bool log_comparison_details = false,
              const std::string& name_suffix = "" );

/*! Create a comparison header
 *
 * This function provides a shortcut to the 
 * ComparisonTraits::createComparisonHeader method.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy, typename T1, typename T2>
std::string createComparisonHeader(
               T1& left_value,
               const std::string& left_name,
               T2&& right_value,
               const std::string& right_name,
               const typename ComparisonTraits<T1>::ExtraDataType& extra_data =
               typename ComparisonTraits<T1>::ExtraDataType(),
               const std::string& name_suffix = "" );
  
/*! Compare two values and print the results (to the desired stream)
 *
 * This function provides a shortcut to the ComparisonTraits::compare method.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy, typename T1, typename T2>
bool compare( T1& left_value,
              const std::string& left_name,
              T2&& right_value,
              const std::string& right_name,
              std::ostream& log,
              const typename ComparisonTraits<T1>::ExtraDataType& extra_data =
              typename ComparisonTraits<T1>::ExtraDataType(),
              const bool log_comparison_details = false,
              const std::string& name_suffix = "" );

/*! Create a comparison header
 *
 * This function provides a shortcut to the 
 * ComparisonTraits::createComparisonHeader method.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy, typename T>
std::string createComparisonHeader(
         T&& left_value,
         const std::string& left_name,
         T&& right_value,
         const std::string& right_name,
         const typename ComparisonTraits<T>::ExtraDataType& extra_data =
         typename ComparisonTraits<T>::ExtraDataType(),
         const std::string& name_suffix = "" );

/*! Compare two values and print the results (to the desired stream)
 *
 * This function provides a shortcut to the ComparisonTraits::compare method.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy, typename T>
bool compare( T&& left_value,
              const std::string& left_name,
              T&& right_value,
              const std::string& right_name,
              std::ostream& log,
              const typename ComparisonTraits<T>::ExtraDataType& extra_data =
              typename ComparisonTraits<T>::ExtraDataType(),
              const bool log_comparison_details = false,
              const std::string& name_suffix = "" );

/*! Check the comparison result and add "passed" or "failed!" to the log
 * \ingroup comparison_traits
 */
void reportComparisonPassFail( const bool result, std::ostream& log );

} // end Utility namespace

#endif // end UTILITY_COMPARISON_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_ComparisonTraitsDecl.hpp
//---------------------------------------------------------------------------//
