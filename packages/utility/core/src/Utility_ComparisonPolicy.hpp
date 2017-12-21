//---------------------------------------------------------------------------//
//!
//! \file   Utility_ComparisonPolicy.hpp
//! \author Alex Robinson
//! \brief  Comparison policy class declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_COMPARISON_POLICY_HPP
#define UTILITY_COMPARISON_POLICY_HPP

// Std Lib Includes
#include <string>

// FRENSIE Includes
#include "Utility_QuantityTraits.hpp"

/*! \defgroup comparison_policies Comparison Policies
 * \ingroup policy
 * \ingroup testing
 */

namespace Utility{

/*! The base comparison policy class
 * \ingroup comparison_policies
 */
template<typename DerivedType>
struct ComparisonPolicy
{
  //! The comparison operator
  template<typename T>
  bool operator()( const T& left_value,
                   const T& right_value,
                   const typename QuantityTraits<T>::RawType& extra_data =
                   typename QuantityTraits<T>::RawType() ) const;
  
protected:

  // The base comparison policy
  typedef ComparisonPolicy<DerivedType> BaseComparisonPolicy;
  
  //! Create the comparison details (default implementation)
  template<typename T>
  static std::string createComparisonDetailsDefaultImpl(
                        const std::string& left_name,
                        const bool report_left_name,
                        const T& left_value,
                        const std::string& right_name,
                        const bool report_right_name,
                        const T& right_value,
                        const std::string& name_suffix,
                        const typename QuantityTraits<T>::RawType& extra_data =
                        typename QuantityTraits<T>::RawType() );
};

/*! The equality comparison policy class
 * \ingroup comparison_policies
 */
struct EqualityComparisonPolicy : public ComparisonPolicy<EqualityComparisonPolicy>
{
  //! Get the comparison operator name
  template<typename T>
  static std::string getOperatorName();

  //! Create the comparison details
  template<typename T>
  static std::string createComparisonDetails(
                            const std::string& left_name,
                            const bool report_left_name,
                            const T& left_value,
                            const std::string& right_name,
                            const bool report_right_name,
                            const T& right_value,
                            const std::string& name_suffix,
                            const typename QuantityTraits<T>::RawType& dummy =
                            typename QuantityTraits<T>::RawType() );
  
  //! Compare two values
  template<typename T>
  static bool compare( const T& left_value,
                       const T& right_value,
                       const typename QuantityTraits<T>::RawType& dummy =
                       typename QuantityTraits<T>::RawType() );
};

/*! The inequality comparison policy class
 * \ingroup comparison_policies
 */
struct InequalityComparisonPolicy : public ComparisonPolicy<InequalityComparisonPolicy>
{
  //! Get the comparison operator name
  template<typename T>
  static std::string getOperatorName();

  //! Create the comparison details
  template<typename T>
  static std::string createComparisonDetails(
                             const std::string& left_name,
                             const bool report_left_name,
                             const T& left_value,
                             const std::string& right_name,
                             const bool report_right_name,
                             const T& right_value,
                             const std::string& name_suffix,
                             const typename QuantityTraits<T>::RawType& dummy =
                             typename QuantityTraits<T>::RawType() );

  //! Compare two values
  template<typename T>
  static bool compare( const T& left_value,
                       const T& right_value,
                       const typename QuantityTraits<T>::RawType& dummy =
                       typename QuantityTraits<T>::RawType() );
};

/*! The greater-than comparison policy class
 * \ingroup comparison_policies
 */
struct GreaterThanComparisonPolicy : public ComparisonPolicy<GreaterThanComparisonPolicy>
{
  //! Get the comparison operator name
  template<typename T>
  static std::string getOperatorName();

  //! Create the comparison details
  template<typename T>
  static std::string createComparisonDetails(
                             const std::string& left_name,
                             const bool report_left_name,
                             const T& left_value,
                             const std::string& right_name,
                             const bool report_right_name,
                             const T& right_value,
                             const std::string& name_suffix,
                             const typename QuantityTraits<T>::RawType& dummy =
                             typename QuantityTraits<T>::RawType() );

  //! Compare two values
  template<typename T>
  static bool compare( const T& left_value,
                       const T& right_value,
                       const typename QuantityTraits<T>::RawType& dummy =
                       typename QuantityTraits<T>::RawType() );
};

/*! The greater-than-or-equal-to comparison policy class
 * \ingroup comparison_policies
 */
struct GreaterThanOrEqualToComparisonPolicy : public ComparisonPolicy<GreaterThanOrEqualToComparisonPolicy>
{
  //! Get the comparison operator name
  template<typename T>
  static std::string getOperatorName();

  //! Create the comparison details
  template<typename T>
  static std::string createComparisonDetails(
                             const std::string& left_name,
                             const bool report_left_name,
                             const T& left_value,
                             const std::string& right_name,
                             const bool report_right_name,
                             const T& right_value,
                             const std::string& name_suffix,
                             const typename QuantityTraits<T>::RawType& dummy =
                             typename QuantityTraits<T>::RawType() );

  //! Compare two values
  template<typename T>
  static bool compare( const T& left_value,
                       const T& right_value,
                       const typename QuantityTraits<T>::RawType& dummy =
                       typename QuantityTraits<T>::RawType() );
};

/*! The less-than comparison policy class
 * \ingroup comparison_policies
 */
struct LessThanComparisonPolicy : public ComparisonPolicy<LessThanComparisonPolicy>
{
  //! Get the comparison operator name
  template<typename T>
  static std::string getOperatorName();

  //! Create the comparison details
  template<typename T>
  static std::string createComparisonDetails(
                             const std::string& left_name,
                             const bool report_left_name,
                             const T& left_value,
                             const std::string& right_name,
                             const bool report_right_name,
                             const T& right_value,
                             const std::string& name_suffix,
                             const typename QuantityTraits<T>::RawType& dummy =
                             typename QuantityTraits<T>::RawType() );

  //! Compare two values
  template<typename T>
  static bool compare( const T& left_value,
                       const T& right_value,
                       const typename QuantityTraits<T>::RawType& dummy =
                       typename QuantityTraits<T>::RawType() );
};

/*! The less-than-or-equal-to comparison policy class
 * \ingroup comparison_policies
 */
struct LessThanOrEqualToComparisonPolicy : public ComparisonPolicy<LessThanOrEqualToComparisonPolicy>
{
  //! Get the comparison operator name
  template<typename T>
  static std::string getOperatorName();

  //! Create the comparison details
  template<typename T>
  static std::string createComparisonDetails(
                             const std::string& left_name,
                             const bool report_left_name,
                             const T& left_value,
                             const std::string& right_name,
                             const bool report_right_name,
                             const T& right_value,
                             const std::string& name_suffix,
                             const typename QuantityTraits<T>::RawType& dummy =
                             typename QuantityTraits<T>::RawType() );

  //! Compare two values
  template<typename T>
  static bool compare( const T& left_value,
                       const T& right_value,
                       const typename QuantityTraits<T>::RawType& dummy =
                       typename QuantityTraits<T>::RawType() );
};

/*! The close comparison policy class
 * \ingroup comparison_policies
 */
struct CloseComparisonPolicy : public ComparisonPolicy<CloseComparisonPolicy>
{
  //! Get the comparison operator name
  template<typename T>
  static std::string getOperatorName();

  //! Create the comparison details
  template<typename T>
  static std::string createComparisonDetails(
                const std::string& left_name,
                const bool report_left_name,
                const T& left_value,
                const std::string& right_name,
                const bool report_right_name,
                const T& right_value,
                const std::string& name_suffix,
                const typename QuantityTraits<T>::RawType& distance_tolerance =
                typename QuantityTraits<T>::RawType() );

  //! Compare two values
  template<typename T>
  static bool compare(
                const T& left_value,
                const T& right_value,
                const typename QuantityTraits<T>::RawType& distance_tolerance =
                typename QuantityTraits<T>::RawType() );

  //! Calculate the absolute distance between the two values
  template<typename T>
  static inline typename QuantityTraits<T>::RawType calculateDistance(
                                                        const T& left_value,
                                                        const T& right_value );
};

/*! The relative error comparison policy class
 * \ingroup comparison_policies
 */
struct RelativeErrorComparisonPolicy : public ComparisonPolicy<RelativeErrorComparisonPolicy>
{
  //! Get the comparison operator name
  template<typename T>
  static std::string getOperatorName();

  //! Create the comparison details
  template<typename T>
  static std::string createComparisonDetails(
          const std::string& left_name,
          const bool report_left_name,
          const T& left_value,
          const std::string& right_name,
          const bool report_right_name,
          const T& right_value,
          const std::string& name_suffix,
          const typename QuantityTraits<T>::RawType& relative_error_tolerance =
          typename QuantityTraits<T>::RawType() );

  //! Compare two values
  template<typename T>
  static bool compare(
          const T& left_value,
          const T& right_value,
          const typename QuantityTraits<T>::RawType& relative_error_tolerance =
          typename QuantityTraits<T>::RawType() );

  //! Calculate the relative error
  template<typename T>
  static typename QuantityTraits<T>::RawType calculateRelativeError(
                                                        const T& left_value,
                                                        const T& right_value );
};
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Utility_ComparisonPolicy_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_COMPARISON_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_ComparisonPolicy.hpp
//---------------------------------------------------------------------------//

