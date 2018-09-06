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
#include <utility>

// FRENSIE Includes
#include "Utility_ComparisonTraitsHelpers.hpp"
#include "Utility_UndefinedTraits.hpp"
#include "Utility_QuantityTraits.hpp"

/*! \defgroup comparison_traits Comparison Traits 
 * \ingroup traits
 * \ingroup testing
 *
 * The Utility::ComparisonTraits struct can be used to conduct a comparison
 * between two values of a generic type and, optionally, to report the results 
 * of that comparison. The FRENSIE unit test harness uses the struct for
 * both of these purposes. This struct can be specialized if certain
 * comparisons aren't allowed for a type and/or comparison details need to
 * be reported in a custom way. 
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
  //! Check if the comparison is allowed
  template<typename ComparisonPolicy>
  struct IsComparisonAllowed : public std::true_type
  { /* ... */ };
  
  //! The extra data type (usually a comparison tolerance)
  typedef typename QuantityTraits<T>::RawType ExtraDataType;

  //! Create a comparison header
  template<typename ComparisonPolicy, size_t RightShift = 0>
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
  template<typename ComparisonPolicy,
           size_t HeaderRightShift = 0,
           size_t DetailsRightShift = Details::incrementRightShift(HeaderRightShift)>
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
template<typename ComparisonPolicy,
         size_t RightShift,
         typename T1,
         typename T2>
std::string createComparisonHeader(
                const T1& left_value,
                const std::string& left_name,
                const T2& right_value,
                const std::string& right_name,
                const typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType& extra_data =
                typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType(),
                const std::string& name_suffix = "" );

/*! Compare two values and print the results (to the desired stream)
 *
 * This function provides a shortcut to the ComparisonTraits::compare method.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy,
         size_t HeaderRightShift,
         size_t DetailsRightShift,
         typename T1,
         typename T2>
bool compare( const T1& left_value,
              const std::string& left_name,
              const T2& right_value,
              const std::string& right_name,
              std::ostream& log,
              const typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType& extra_data =
              typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType(),
              const bool log_comparison_details = false,
              const std::string& name_suffix = "" );

/*! Compare two values and print the results (to the desired stream)
 *
 * This function provides a shortcut to the ComparisonTraits::compare method.
 * A default details right shift is provided.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy,
         size_t HeaderRightShift,
         typename T1,
         typename T2>
inline bool compare( const T1& left_value,
                     const std::string& left_name,
                     const T2& right_value,
                     const std::string& right_name,
                     std::ostream& log,
                     const typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType& extra_data =
                     typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType(),
                     const bool log_comparison_details = false,
                     const std::string& name_suffix = "" )
{
  return Utility::compare<ComparisonPolicy,HeaderRightShift,Details::incrementRightShift(HeaderRightShift)>(
                                       left_value, left_name,
                                       right_value, right_name,
                                       log, extra_data, log_comparison_details,
                                       name_suffix );
}

/*! Create a comparison header
 *
 * This function provides a shortcut to the 
 * ComparisonTraits::createComparisonHeader method. The T1&& type is not
 * necessarily an rvalue reference. The standard allows this type to be
 * deduced as either an rvalue reference or an lvalue reference depending
 * on the type that is passed. When the type deduced is an lvalue reference
 * the left name will be logged.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy,
         size_t RightShift,
         typename T1,
         typename T2>
std::string createComparisonHeader(
                T1&& left_value,
                const std::string& left_name,
                const T2& right_value,
                const std::string& right_name,
                const typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType& extra_data =
                typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType(),
                const std::string& name_suffix = "" );

/*! Compare two values and print the results (to the desired stream)
 *
 * This function provides a shortcut to the ComparisonTraits::compare method.
 * The T1&& type is not necessarily an rvalue reference. The standard allows 
 * this type to be deduced as either an rvalue reference or an lvalue 
 * reference depending on the type that is passed. When the type deduced is an
 * lvalue reference the left name will be logged.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy,
         size_t HeaderRightShift,
         size_t DetailsRightShift,
         typename T1,
         typename T2>
bool compare( T1&& left_value,
              const std::string& left_name,
              const T2& right_value,
              const std::string& right_name,
              std::ostream& log,
              const typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType& extra_data =
              typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType(),
              const bool log_comparison_details = false,
              const std::string& name_suffix = "" );

/*! Compare two values and print the results (to the desired stream)
 *
 * This function provides a shortcut to the ComparisonTraits::compare method.
 * The T1&& type is not necessarily an rvalue reference. The standard allows 
 * this type to be deduced as either an rvalue reference or an lvalue 
 * reference depending on the type that is passed. When the type deduced is an
 * lvalue reference the left name will be logged. A default details right
 * shift will be provided.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy,
         size_t HeaderRightShift,
         typename T1,
         typename T2>
inline bool compare( T1&& left_value,
                     const std::string& left_name,
                     const T2& right_value,
                     const std::string& right_name,
                     std::ostream& log,
                     const typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType& extra_data =
                     typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType(),
                     const bool log_comparison_details = false,
                     const std::string& name_suffix = "" )
{
  return Utility::compare<ComparisonPolicy,HeaderRightShift,Details::incrementRightShift(HeaderRightShift)>(
                                       std::forward<T1>(left_value), left_name,
                                       right_value, right_name,
                                       log, extra_data, log_comparison_details,
                                       name_suffix );
}

/*! Create a comparison header
 *
 * This function provides a shortcut to the 
 * ComparisonTraits::createComparisonHeader method. The T2&& type is not
 * necessarily an rvalue reference. The standard allows this type to be
 * deduced as either an rvalue reference or an lvalue reference depending
 * on the type that is passed. When the type deduced is an lvalue reference
 * the right name will be logged.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy,
         size_t RightShift,
         typename T1,
         typename T2>
std::string createComparisonHeader(
                const T1& left_value,
                const std::string& left_name,
                T2&& right_value,
                const std::string& right_name,
                const typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType& extra_data =
                typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType(),
                const std::string& name_suffix = "" );

/*! Compare two values and print the results (to the desired stream)
 *
 * This function provides a shortcut to the ComparisonTraits::compare method.
 * The T2&& type is not necessarily an rvalue reference. The standard allows 
 * this type to be deduced as either an rvalue reference or an lvalue reference
 * depending on the type that is passed. When the type deduced is an lvalue 
 * reference the right name will be logged.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy,
         size_t HeaderRightShift,
         size_t DetailsRightShift,
         typename T1,
         typename T2>
bool compare( const T1& left_value,
              const std::string& left_name,
              T2&& right_value,
              const std::string& right_name,
              std::ostream& log,
              const typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType& extra_data =
              typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType(),
              const bool log_comparison_details = false,
              const std::string& name_suffix = "" );

/*! Compare two values and print the results (to the desired stream)
 *
 * This function provides a shortcut to the ComparisonTraits::compare method.
 * The T2&& type is not necessarily an rvalue reference. The standard allows 
 * this type to be deduced as either an rvalue reference or an lvalue reference
 * depending on the type that is passed. When the type deduced is an lvalue 
 * reference the right name will be logged. A default details right shift
 * will be provided
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy,
         size_t HeaderRightShift,
         typename T1,
         typename T2>
inline bool compare( const T1& left_value,
                     const std::string& left_name,
                     T2&& right_value,
                     const std::string& right_name,
                     std::ostream& log,
                     const typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType& extra_data =
                     typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType(),
                     const bool log_comparison_details = false,
                     const std::string& name_suffix = "" )
{
  return Utility::compare<ComparisonPolicy,HeaderRightShift,Details::incrementRightShift(HeaderRightShift)>(
                                     left_value, left_name,
                                     std::forward<T2>(right_value), right_name,
                                     log, extra_data, log_comparison_details,
                                     name_suffix );
}

/*! Create a comparison header
 *
 * This function provides a shortcut to the 
 * ComparisonTraits::createComparisonHeader method. The T1&& and T2&& types
 * are not necessarily an rvalue references. The standard allows each of them 
 * to be deduced as either an rvalue reference or an lvalue reference depending
 * on the types that are passed. When the type deduced for T1&& is an lvalue
 * reference the left name will be logged. When the type deduced for T2&& is an
 * lvalue reference the right name will be logged. 
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy,
         size_t RightShift,
         typename T1,
         typename T2>
std::string createComparisonHeader(
                T1&& left_value,
                const std::string& left_name,
                T2&& right_value,
                const std::string& right_name,
                const typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType& extra_data =
                typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType(),
                const std::string& name_suffix = "" );

/*! Compare two values and print the results (to the desired stream)
 *
 * This function provides a shortcut to the ComparisonTraits::compare method.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy,
         size_t HeaderRightShift,
         size_t DetailsRightShift,
         typename T1,
         typename T2>
bool compare( T1&& left_value,
              const std::string& left_name,
              T2&& right_value,
              const std::string& right_name,
              std::ostream& log,
              const typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType& extra_data =
              typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType(),
              const bool log_comparison_details = false,
              const std::string& name_suffix = "" );

/*! Compare two values and print the results (to the desired stream)
 *
 * This function provides a shortcut to the ComparisonTraits::compare method.
 * A default details right shift will be provided.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy,
         size_t HeaderRightShift,
         typename T1,
         typename T2>
inline bool compare( T1&& left_value,
                     const std::string& left_name,
                     T2&& right_value,
                     const std::string& right_name,
                     std::ostream& log,
                     const typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType& extra_data =
                     typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType(),
                     const bool log_comparison_details = false,
                     const std::string& name_suffix = "" )
{
  return Utility::compare<ComparisonPolicy,HeaderRightShift,Details::incrementRightShift(HeaderRightShift)>(
                                     std::forward<T1>(left_value), left_name,
                                     std::forward<T2>(right_value), right_name,
                                     log, extra_data, log_comparison_details,
                                     name_suffix );
}

/*! Create a comparison header
 *
 * This function provides a shortcut to the 
 * ComparisonTraits::createComparisonHeader method.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy,
         size_t RightShift,
         typename Container,
         typename T = typename Container::value_type>
std::string createComparisonHeader(
        std::initializer_list<T> left_value,
        const std::string& left_name,
        const Container& right_value,
        const std::string& right_name,
        const typename ComparisonTraits<Container>::ExtraDataType& extra_data =
        typename ComparisonTraits<Container>::ExtraDataType(),
        const std::string& name_suffix = "" );

/*! Compare two values and print the results (to the desired stream)
 *
 * This function provides a shortcut to the ComparisonTraits::compare method.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy,
         size_t HeaderRightShift,
         size_t DetailsRightShift,
         typename Container,
         typename T = typename Container::value_type>
bool compare(
        std::initializer_list<T> left_value,
        const std::string& left_name,
        const Container& right_value,
        const std::string& right_name,
        std::ostream& log,
        const typename ComparisonTraits<Container>::ExtraDataType& extra_data =
        typename ComparisonTraits<Container>::ExtraDataType(),
        const bool log_comparison_details = false,
        const std::string& name_suffix = "" );

/*! Compare two values and print the results (to the desired stream)
 *
 * This function provides a shortcut to the ComparisonTraits::compare method.
 * A default details right shift will be provided.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy,
         size_t HeaderRightShift,
         typename Container,
         typename T = typename Container::value_type>
inline bool compare(
        std::initializer_list<T> left_value,
        const std::string& left_name,
        const Container& right_value,
        const std::string& right_name,
        std::ostream& log,
        const typename ComparisonTraits<Container>::ExtraDataType& extra_data =
        typename ComparisonTraits<Container>::ExtraDataType(),
        const bool log_comparison_details = false,
        const std::string& name_suffix = "" )
{
  return Utility::compare<ComparisonPolicy,HeaderRightShift,Details::incrementRightShift(HeaderRightShift)>(
                                       left_value, left_name,
                                       right_value, right_name,
                                       log, extra_data, log_comparison_details,
                                       name_suffix );
}

/*! Create a comparison header
 *
 * This function provides a shortcut to the 
 * ComparisonTraits::createComparisonHeader method.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy,
         size_t RightShift,
         typename Container,
         typename T = typename Container::value_type>
std::string createComparisonHeader(
        const Container& left_value,
        const std::string& left_name,
        std::initializer_list<T> right_value,
        const std::string& right_name,
        const typename ComparisonTraits<Container>::ExtraDataType& extra_data =
        typename ComparisonTraits<Container>::ExtraDataType(),
        const std::string& name_suffix = "" );
  
/*! Compare two values and print the results (to the desired stream)
 *
 * This function provides a shortcut to the ComparisonTraits::compare method.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy,
         size_t HeaderRightShift,
         size_t DetailsRightShift,
         typename Container,
         typename T = typename Container::value_type>
bool compare(
        const Container& left_value,
        const std::string& left_name,
        std::initializer_list<T> right_value,
        const std::string& right_name,
        std::ostream& log,
        const typename ComparisonTraits<Container>::ExtraDataType& extra_data =
        typename ComparisonTraits<Container>::ExtraDataType(),
        const bool log_comparison_details = false,
        const std::string& name_suffix = "" );

/*! Compare two values and print the results (to the desired stream)
 *
 * This function provides a shortcut to the ComparisonTraits::compare method.
 * A default details right shift will be provided.
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy,
         size_t HeaderRightShift,
         typename Container,
         typename T = typename Container::value_type>
inline bool compare(
        const Container& left_value,
        const std::string& left_name,
        std::initializer_list<T> right_value,
        const std::string& right_name,
        std::ostream& log,
        const typename ComparisonTraits<Container>::ExtraDataType& extra_data =
        typename ComparisonTraits<Container>::ExtraDataType(),
        const bool log_comparison_details = false,
        const std::string& name_suffix = "" )
{
  return Utility::compare<ComparisonPolicy,HeaderRightShift,Details::incrementRightShift(HeaderRightShift)>(
                                       left_value, left_name,
                                       right_value, right_name,
                                       log, extra_data, log_comparison_details,
                                       name_suffix );
}

} // end Utility namespace

#endif // end UTILITY_COMPARISON_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_ComparisonTraitsDecl.hpp
//---------------------------------------------------------------------------//
