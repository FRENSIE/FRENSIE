//---------------------------------------------------------------------------//
//!
//! \file   Utility_ComparisonTraits.hpp
//! \author Alex Robinson
//! \brief  Comparison traits specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_COMPARISON_TRAITS_HPP
#define UTILITY_COMPARISON_TRAITS_HPP

// Std Lib Includes
#include <sstream>
#include <string>
#include <utility>
#include <iterator>
#include <functional>
#include <type_traits>

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_ComparisonTraitsDecl.hpp"
#include "Utility_ComparisonPolicy.hpp"

namespace Utility{

// Create a comparison header
template<typename T, typename Enabled>
template<typename ComparisonPolicy, size_t RightShift>
inline std::string ComparisonTraits<T,Enabled>::createComparisonHeader(
                                              const T& left_value,
                                              const std::string& left_name,
                                              const bool log_left_name,
                                              const T& right_value,
                                              const std::string& right_name,
                                              const bool log_right_name,
                                              const std::string& name_suffix,
                                              const ExtraDataType& extra_data )
{
  return Details::createComparisonHeaderImpl<ComparisonPolicy,RightShift>(
                                                                left_value,
                                                                left_name,
                                                                log_left_name,
                                                                right_value,
                                                                right_name,
                                                                log_right_name,
                                                                name_suffix,
                                                                extra_data );
}

// Compare two values of a type (default)
template<typename T, typename Enabled>
template<typename ComparisonPolicy,
         size_t HeaderRightShift,
         size_t>
inline bool ComparisonTraits<T,Enabled>::compare(
                                             const T& left_value,
                                             const std::string& left_name,
                                             const bool log_left_name,
                                             const T& right_value,
                                             const std::string& right_name,
                                             const bool log_right_name,
                                             const std::string& name_suffix,
                                             std::ostream& log,
                                             const bool log_comparison_details,
                                             const ExtraDataType& extra_data )
{
  return Details::compareImpl<ComparisonPolicy,HeaderRightShift>(
                                      left_value, left_name, log_left_name,
                                      right_value, right_name, log_right_name,
                                      name_suffix, log, log_comparison_details,
                                      extra_data );
};

/*! The specialization of the Utility::ComparisonTraits for std::string
 *
 * This specialization will be used to handle string literals, which are
 * not treated as rvalues due to the fact that they are arrays
 * \ingroup comparison_traits
 */
template<>
struct ComparisonTraits<std::string>
{
  //! Relative error and close comparisons are not allowed
  template<typename ComparisonPolicy>
  struct IsComparisonAllowed : public std::conditional<std::is_same<ComparisonPolicy,Utility::CloseComparisonPolicy>::value || std::is_same<ComparisonPolicy,Utility::RelativeErrorComparisonPolicy>::value, std::false_type, std::true_type>::type
  { /* ... */ };

  //! The extra data type
  typedef std::string ExtraDataType;

  //! Create the comparison header
  template<typename ComparisonPolicy,
           size_t RightShift = 0>
  static inline std::string createComparisonHeader(
                            const std::string& left_value,
                            const std::string& left_name,
                            const bool log_left_name,
                            const std::string& right_value,
                            const std::string& right_name,
                            const bool log_right_name,
                            const std::string& name_suffix,
                            const ExtraDataType& extra_data = ExtraDataType() )
  {
    return ComparisonTraits<std::string>::createComparisonHeaderWithExtraChecks<ComparisonPolicy,RightShift>(
                                left_value, left_name, log_left_name, false,
                                right_value, right_name, log_right_name, false,
                                name_suffix, extra_data );
  }

  //! Create the comparison header
  template<typename ComparisonPolicy,
           size_t RightShift = 0,
           size_t N>
  static inline std::string createComparisonHeader(
                            const char (&left_value)[N],
                            const std::string& left_name,
                            const bool log_left_name,
                            const std::string& right_value,
                            const std::string& right_name,
                            const bool log_right_name,
                            const std::string& name_suffix,
                            const ExtraDataType& extra_data = ExtraDataType() )
  {
    return ComparisonTraits<std::string>::createComparisonHeaderWithExtraChecks<ComparisonPolicy,RightShift>(
                                left_value, left_name, log_left_name, true,
                                right_value, right_name, log_right_name, false,
                                name_suffix, extra_data );
  }

  //! Create the comparison header
  template<typename ComparisonPolicy,
           size_t RightShift = 0,
           size_t N>
  static inline std::string createComparisonHeader(
                            const std::string& left_value,
                            const std::string& left_name,
                            const bool log_left_name,
                            const char (&right_value)[N],
                            const std::string& right_name,
                            const bool log_right_name,
                            const std::string& name_suffix,
                            const ExtraDataType& extra_data = ExtraDataType() )
  {
    return ComparisonTraits<std::string>::createComparisonHeaderWithExtraChecks<ComparisonPolicy,RightShift>(
                                left_value, left_name, log_left_name, false,
                                right_value, right_name, log_right_name, true,
                                name_suffix, extra_data );
  }

  //! Create the comparison header
  template<typename ComparisonPolicy,
           size_t RightShift = 0,
           size_t N,
           size_t M>
  static inline std::string createComparisonHeader(
                            const char (&left_value)[N],
                            const std::string& left_name,
                            const bool log_left_name,
                            const char (&right_value)[M],
                            const std::string& right_name,
                            const bool log_right_name,
                            const std::string& name_suffix,
                            const ExtraDataType& extra_data = ExtraDataType() )
  {
    return ComparisonTraits<std::string>::createComparisonHeaderWithExtraChecks<ComparisonPolicy,RightShift>(
                                left_value, left_name, log_left_name, true,
                                right_value, right_name, log_right_name, true,
                                name_suffix, extra_data );
  }

  //! Compare two strings
  template<typename ComparisonPolicy,
           size_t HeaderRightShift,
           size_t>
  static inline bool compare( const std::string& left_value,
                              const std::string& left_name,
                              const bool log_left_name,
                              const std::string& right_value,
                              const std::string& right_name,
                              const bool log_right_name,
                              const std::string& name_suffix,
                              std::ostream& log,
                              const bool log_comparison_details = false,
                              const ExtraDataType& extra_data = ExtraDataType() )
  {
    return ComparisonTraits<std::string>::compareWithExtraChecks<ComparisonPolicy,HeaderRightShift>(
                                left_value, left_name, log_left_name, false,
                                right_value, right_name, log_right_name, false,
                                name_suffix, log, log_comparison_details,
                                extra_data );
  }

  //! Compare two strings
  template<typename ComparisonPolicy,
           size_t HeaderRightShift,
           size_t,
           size_t N>
  static inline bool compare( const char (&left_value)[N],
                              const std::string& left_name,
                              const bool log_left_name,
                              const std::string& right_value,
                              const std::string& right_name,
                              const bool log_right_name,
                              const std::string& name_suffix,
                              std::ostream& log,
                              const bool log_comparison_details = false,
                              const ExtraDataType& extra_data = ExtraDataType() )
  {
    return ComparisonTraits<std::string>::compareWithExtraChecks<ComparisonPolicy,HeaderRightShift>(
                                left_value, left_name, log_left_name, true,
                                right_value, right_name, log_right_name, false,
                                name_suffix, log, log_comparison_details,
                                extra_data );
  }

  //! Compare two strings
  template<typename ComparisonPolicy,
           size_t HeaderRightShift,
           size_t,
           size_t N>
  static inline bool compare( const std::string& left_value,
                              const std::string& left_name,
                              const bool log_left_name,
                              const char (&right_value)[N],
                              const std::string& right_name,
                              const bool log_right_name,
                              const std::string& name_suffix,
                              std::ostream& log,
                              const bool log_comparison_details = false,
                              const ExtraDataType& extra_data = ExtraDataType() )
  {
    return ComparisonTraits<std::string>::compareWithExtraChecks<ComparisonPolicy,HeaderRightShift>(
                                left_value, left_name, log_left_name, false,
                                right_value, right_name, log_right_name, true,
                                name_suffix, log, log_comparison_details,
                                extra_data );
  }

  //! Compare two strings
  template<typename ComparisonPolicy,
           size_t HeaderRightShift,
           size_t,
           size_t N,
           size_t M>
  static inline bool compare( const char (&left_value)[N],
                              const std::string& left_name,
                              const bool log_left_name,
                              const char (&right_value)[M],
                              const std::string& right_name,
                              const bool log_right_name,
                              const std::string& name_suffix,
                              std::ostream& log,
                              const bool log_comparison_details = false,
                              const ExtraDataType& extra_data = ExtraDataType() )
  {
    return ComparisonTraits<std::string>::compareWithExtraChecks<ComparisonPolicy,HeaderRightShift>(
                                left_value, left_name, log_left_name, true,
                                right_value, right_name, log_right_name, true,
                                name_suffix, log, log_comparison_details,
                                extra_data );
  }

private:

  // Compare two strings with extra checks
  template<typename ComparisonPolicy, size_t HeaderRightShift>
  static inline bool compareWithExtraChecks(
                                  const std::string& left_value,
                                  const std::string& left_name,
                                  const bool log_left_name,
                                  const bool check_if_left_value_is_a_literal,
                                  const std::string& right_value,
                                  const std::string& right_name,
                                  const bool log_right_name,
                                  const bool check_if_right_value_is_a_literal,
                                  const std::string& name_suffix,
                                  std::ostream& log,
                                  const bool log_comparison_details,
                                  const ExtraDataType& extra_data )
  {
    return Details::compareImpl<ComparisonPolicy,HeaderRightShift>(
                     left_value, left_name, log_left_name,
                     right_value, right_name, log_right_name,
                     name_suffix, log, log_comparison_details,
                     extra_data,
                     std::bind<std::string>( &ComparisonTraits<std::string>::createComparisonHeaderWithExtraChecks<ComparisonPolicy,HeaderRightShift>,
                                             std::placeholders::_1,
                                             std::placeholders::_2,
                                             std::placeholders::_3,
                                             check_if_left_value_is_a_literal,
                                             std::placeholders::_4,
                                             std::placeholders::_5,
                                             std::placeholders::_6,
                                             check_if_right_value_is_a_literal,
                                             std::placeholders::_7,
                                             std::placeholders::_8 ) );
  }

  // Create the comparison header with extra checks
  template<typename ComparisonPolicy, size_t RightShift>
  static inline std::string createComparisonHeaderWithExtraChecks(
                            const std::string& left_value,
                            const std::string& left_name,
                            const bool log_left_name,
                            const bool check_if_left_value_is_a_literal,
                            const std::string& right_value,
                            const std::string& right_name,
                            const bool log_right_name,
                            const bool check_if_right_value_is_a_literal,
                            const std::string& name_suffix,
                            const ExtraDataType& extra_data = ExtraDataType() )
  {
    bool log_left_name_override = log_left_name;

    if( log_left_name && check_if_left_value_is_a_literal )
    {
      if( ComparisonTraits<std::string>::isValueLikelyStringLiteral( left_name ) )
        log_left_name_override = false;
    }

    bool log_right_name_override = log_right_name;

    if( log_right_name && check_if_right_value_is_a_literal )
    {
      if( ComparisonTraits<std::string>::isValueLikelyStringLiteral( right_name ) )
        log_right_name_override = false;
    }
    
    return Details::createComparisonHeaderImpl<ComparisonPolicy,RightShift>(
                                                       left_value,
                                                       left_name,
                                                       log_left_name_override,
                                                       right_value,
                                                       right_name,
                                                       log_right_name_override,
                                                       name_suffix,
                                                       extra_data );
  }

  // Check if a value is likely a string literal
  static inline bool isValueLikelyStringLiteral( const std::string& value_name )
  {
    return value_name[0] == '"' ||
      (value_name[0] == 'L' && value_name[1] == '"');
  }
};

/*! \brief The specialization of the Utility::ComparisonTraits for char[]
 * \ingroup comparison_traits
 */
template<size_t _N>
struct ComparisonTraits<char[_N]> : public ComparisonTraits<std::string>
{ /* ... */ };

/*! \brief The specialization of the Utility::ComparisonTraits for char*
 * \ingroup comparison_traits
 */
template<>
struct ComparisonTraits<char*> : public ComparisonTraits<std::string>
{ /* ... */ };

/*! \brief The specialization of the Utility::ComparisonTraits for const and/or
 * volatile types.
 * \ingroup comparison_traits
 */
template<typename T>
struct ComparisonTraits<T,typename std::enable_if<std::is_const<T>::value || std::is_volatile<T>::value>::type> : public ComparisonTraits<typename std::remove_cv<T>::type>
{ /* ... */ };

namespace Details{

/*! Create a detailed container name
 * \ingroup comparison_traits
 */
template<typename Container>
inline std::string createDetailedContainerName(
                                               const Container& value,
                                               const std::string& name,
                                               const bool log_name,
                                               const std::string& name_suffix )
{
  std::ostringstream detailed_name;
  
  if( log_name )
  {
    detailed_name << name;
    
    if( !name_suffix.empty() )
      detailed_name << name_suffix;
  }
  else
    detailed_name << Utility::toString( value );
  
  return detailed_name.str();
}

/*! The comparison policy helper for stl compliant sequence containers
 * \ingroup comparison_traits
 */
template<typename Policy, typename Enabled = void>
struct SequenceContainerComparisonPolicyHelper
{
  /*! \brief Create the comparison header (this won't compile if this class is
   * not specialized for the comparison policy of interest).
   */
  template<size_t RightShift,
           bool LeftContainerIsDominant,
           typename LeftContainer,
           typename RightContainer,
           typename ExtraDataType>
  static inline std::string createComparisonHeader(
                                             const LeftContainer& left_value,
                                             const std::string& left_name,
                                             const bool log_left_name,
                                             const RightContainer& right_value,
                                             const std::string& right_name,
                                             const bool log_right_name,
                                             const std::string& name_suffix,
                                             const ExtraDataType& extra_data )
  { return Policy::cannotCompareSequenceContainersWithThisPolicy(); }

  /*! \brief Compare two containers (this won't compile if this class is not
   * specialized for the comparison policy of interest).
   */
  template<size_t HeaderRightShift,
           size_t DetailsRightShift,
           bool LeftContainerIsDominant,
           typename LeftContainer,
           typename RightContainer,
           typename ExtraDataType>
  static inline bool compare(
                            const LeftContainer& left_container,
                            const std::string& left_name,
                            const bool log_left_name,
                            const RightContainer& right_container,
                            const std::string& right_name,
                            const bool log_right_name,
                            const std::string& name_suffix,
                            std::ostream& log,
                            const bool log_comparison_details = false,
                            const ExtraDataType& extra_data = ExtraDataType() )
  { return Policy::cannotCompareSequenceContainersWithThisPolicy();  }
};

/*! \brief Partial specialization SequenceContainerComparisonPolicyHelper for 
 * Utility::EqualityComparisonPolicy, Utility::CloseComparisonPolicy and 
 * Utility::RelativeErrorComparisonPolicy
 * \ingroup comparison_traits
 */
template<typename Policy>
struct SequenceContainerComparisonPolicyHelper<Policy,typename std::enable_if<std::is_same<Policy,Utility::EqualityComparisonPolicy>::value || std::is_same<Policy,Utility::CloseComparisonPolicy>::value || std::is_same<Policy,Utility::RelativeErrorComparisonPolicy>::value>::type>
{
private:

  // Typedef for this type
  typedef SequenceContainerComparisonPolicyHelper<Policy,typename std::enable_if<std::is_same<Policy,Utility::EqualityComparisonPolicy>::value || std::is_same<Policy,Utility::CloseComparisonPolicy>::value || std::is_same<Policy,Utility::RelativeErrorComparisonPolicy>::value>::type> ThisType;

 public:
  
  //! Create the comparison header
  template<size_t RightShift,
           bool LeftContainerIsDominant,
           typename LeftContainer,
           typename RightContainer,
           typename ExtraDataType>
  static inline std::string createComparisonHeader(
                                             const LeftContainer& left_value,
                                             const std::string& left_name,
                                             const bool log_left_name,
                                             const RightContainer& right_value,
                                             const std::string& right_name,
                                             const bool log_right_name,
                                             const std::string& name_suffix,
                                             const ExtraDataType& extra_data )
  {
    typedef typename std::conditional<LeftContainerIsDominant,typename LeftContainer::value_type,typename RightContainer::value_type>::type ValueType;
    
    std::string detailed_left_name =
      Details::createDetailedContainerName( left_value,
                                            left_name,
                                            log_left_name,
                                            name_suffix );
      
    std::string detailed_right_name =
      Details::createDetailedContainerName( right_value,
                                            right_name,
                                            log_right_name,
                                            name_suffix );
    
    std::ostringstream oss;

    oss << std::string( RightShift, ' ' )
        << detailed_left_name << ".size() == "
        << detailed_right_name << ".size() && "
        << "for every index i, "
        << detailed_left_name << "[i] "
        << Policy::template getOperatorName<ValueType>() << " "
        << detailed_right_name << "[i]: ";

    return oss.str();
  }

  //! Compare two containers
  template<size_t HeaderRightShift,
           size_t DetailsRightShift,
           bool LeftContainerIsDominant,
           typename LeftContainer,
           typename RightContainer,
           typename ExtraDataType>
  static inline bool compare(
                            const LeftContainer& left_container,
                            const std::string& left_name,
                            const bool log_left_name,
                            const RightContainer& right_container,
                            const std::string& right_name,
                            const bool log_right_name,
                            const std::string& name_suffix,
                            std::ostream& log,
                            const bool log_comparison_details = false,
                            const ExtraDataType& extra_data = ExtraDataType() )
  {
    typedef typename std::conditional<LeftContainerIsDominant,typename LeftContainer::value_type,typename RightContainer::value_type>::type ValueType;

    if( log_comparison_details )
    {
      log << ThisType::template createComparisonHeader<HeaderRightShift,LeftContainerIsDominant>(
                                                               left_container,
                                                               left_name,
                                                               log_left_name,
                                                               right_container,
                                                               right_name,
                                                               log_right_name,
                                                               name_suffix,
                                                               extra_data );
    }

    
    std::ostringstream local_log, detailed_name_suffix;

    if( log_comparison_details )
      detailed_name_suffix << name_suffix << ".size()";
        
    bool success =
      Utility::ComparisonTraits<size_t>::template compare<Policy,DetailsRightShift,Details::incrementRightShift(DetailsRightShift)>(
               std::distance( left_container.begin(), left_container.end() ),
               left_name,
               log_left_name,
               std::distance( right_container.begin(), right_container.end() ),
               right_name,
               log_right_name,
               (log_comparison_details ? detailed_name_suffix.str() : name_suffix),
               local_log,
               log_comparison_details );

    // Only test the individual container elements if the sizes are the same
    if( success )
    {
      std::ostringstream detailed_name_suffix;
      size_t index = 0;
      
      typename LeftContainer::const_iterator left_it, left_end;
      left_it = left_container.begin();
      left_end = left_container.end();

      typename RightContainer::const_iterator right_it, right_end;
      right_it = right_container.begin();
      right_end = right_container.end();
      
      while( left_it != left_end )
      {
        if( name_suffix.size() > 0 )
          detailed_name_suffix.str( name_suffix );
        else
          detailed_name_suffix.str( "" );
        
        detailed_name_suffix.clear();

        detailed_name_suffix << "[" << index << "]";
          
        bool local_success =
          Utility::ComparisonTraits<ValueType>::template compare<Policy,DetailsRightShift,Details::incrementRightShift(DetailsRightShift)>(
                                             static_cast<ValueType>(*left_it),
                                             left_name,
                                             log_left_name,
                                             static_cast<ValueType>(*right_it),
                                             right_name,
                                             log_right_name,
                                             detailed_name_suffix.str(),
                                             local_log,
                                             log_comparison_details,
                                             extra_data );
        if( !local_success )
          success = false;

        ++left_it;
        ++right_it;
        ++index;
      }
    }

    if( log_comparison_details )
    {
      Utility::reportComparisonPassFail( success, log );
      log << local_log.str();
    }

    return success;
  }
};

/*! \brief Partial specialization SequenceContainerComparisonPolicyHelper for 
 * Utility::InequalityComparisonPolicy
 * \ingroup comparison_traits
 */
template<typename Policy>
struct SequenceContainerComparisonPolicyHelper<Policy,typename std::enable_if<std::is_same<Policy,Utility::InequalityComparisonPolicy>::value>::type>
{
private:

  // Typedef for this type
  typedef SequenceContainerComparisonPolicyHelper<Policy,typename std::enable_if<std::is_same<Policy,Utility::InequalityComparisonPolicy>::value>::type> ThisType;

public:
  
  //! Create a comparison header
  template<size_t RightShift,
           bool LeftContainerIsDominant,
           typename LeftContainer,
           typename RightContainer,
           typename ExtraDataType>
  static inline std::string createComparisonHeader(
                                             const LeftContainer& left_value,
                                             const std::string& left_name,
                                             const bool log_left_name,
                                             const RightContainer& right_value,
                                             const std::string& right_name,
                                             const bool log_right_name,
                                             const std::string& name_suffix,
                                             const ExtraDataType& extra_data )
  {
    typedef typename std::conditional<LeftContainerIsDominant,typename LeftContainer::value_type,typename RightContainer::value_type>::type ValueType;

    std::string detailed_left_name =
      Details::createDetailedContainerName( left_value,
                                            left_name,
                                            log_left_name,
                                            name_suffix );
      
    std::string detailed_right_name =
      Details::createDetailedContainerName( right_value,
                                            right_name,
                                            log_right_name,
                                            name_suffix );

    std::ostringstream oss;

    oss << std::string( RightShift, ' ' )
        << detailed_left_name << ".size() "
        << Policy::template getOperatorName<size_t>() << " "
        << detailed_right_name << ".size() "
        << "|| there exists at least one index i such that "
        << detailed_left_name << "[i] "
        << Policy::template getOperatorName<ValueType>() << " "
        << detailed_right_name << "[i]: ";

    return oss.str();
  }

  //! Compare two containers
  template<size_t HeaderRightShift,
           size_t DetailsRightShift,
           bool LeftContainerIsDominant,
           typename LeftContainer,
           typename RightContainer,
           typename ExtraDataType>
  static inline bool compare(
                            const LeftContainer& left_container,
                            const std::string& left_name,
                            const bool log_left_name,
                            const RightContainer& right_container,
                            const std::string& right_name,
                            const bool log_right_name,
                            const std::string& name_suffix,
                            std::ostream& log,
                            const bool log_comparison_details = false,
                            const ExtraDataType& extra_data = ExtraDataType() )
  {
    typedef typename std::conditional<LeftContainerIsDominant,typename LeftContainer::value_type,typename RightContainer::value_type>::type ValueType;

    if( log_comparison_details )
    {
      log << ThisType::template createComparisonHeader<HeaderRightShift,LeftContainerIsDominant>(
                                                               left_container,
                                                               left_name,
                                                               log_left_name,
                                                               right_container,
                                                               right_name,
                                                               log_right_name,
                                                               name_suffix,
                                                               extra_data );
    }

    bool success =
      Utility::ComparisonTraits<size_t>::template compare<Policy,DetailsRightShift,Details::incrementRightShift(DetailsRightShift)>(
               std::distance( left_container.begin(), left_container.end() ),
               left_name,
               false,
               std::distance( right_container.begin(), right_container.end() ),
               right_name,
               false,
               name_suffix,
               log,
               false );

    // Only test the individual container elements if the sizes are the same
    if( !success )
    {
      typename LeftContainer::const_iterator left_it, left_end;
      left_it = left_container.begin();
      left_end = left_container.end();

      typename RightContainer::const_iterator right_it, right_end;
      right_it = right_container.begin();
      right_end = right_container.end();
      
      while( left_it != left_end )
      {
        bool local_success =
          Utility::ComparisonTraits<ValueType>::template compare<Policy,DetailsRightShift,Details::incrementRightShift(DetailsRightShift)>(
                                             static_cast<ValueType>(*left_it),
                                             left_name,
                                             false,
                                             static_cast<ValueType>(*right_it),
                                             right_name,
                                             false,
                                             name_suffix,
                                             log,
                                             false,
                                             extra_data );
        
        if( local_success )
        {
          success = true;
          break;
        }

        ++left_it;
        ++right_it;
      }
    }

    if( log_comparison_details )
      Utility::reportComparisonPassFail( success, log );

    return success;
  }
};

/*! The associative container element comparison helper
 * \ingroup comparison_traits
 */
template<bool LeftContainerIsDominant>
struct STLCompliantAssociativeContainerElementComparisonHelper
{
  template<size_t RightShift,
           typename LeftContainer,
           typename RightContainer,
           typename ExtraDataType>
  static inline bool compareElements(
                            const LeftContainer& left_container,
                            const std::string& left_name,
                            const bool log_left_name,
                            const RightContainer& right_container,
                            const std::string& right_name,
                            const bool log_right_name,
                            const std::string& name_suffix,
                            std::ostream& log,
                            const bool log_comparison_details = false,
                            const ExtraDataType& extra_data = ExtraDataType() )
  {
    typename LeftContainer::const_iterator left_it, left_end;
    left_it = left_container.begin();
    left_end = left_container.end();

    bool success = true;
    std::ostringstream detailed_name_suffix;
      
    while( left_it != left_end )
    {
      if( name_suffix.size() > 0 )
        detailed_name_suffix.str( name_suffix );
      else
        detailed_name_suffix.str( "" );
      
      detailed_name_suffix.clear();

      detailed_name_suffix << " contains " << Utility::toString( *left_it );

      const bool right_container_has_value =
        std::find( right_container.begin(), right_container.end(), *left_it ) != right_container.end();
          
      bool local_success =
        Utility::ComparisonTraits<bool>::template compare<Utility::EqualityComparisonPolicy,RightShift>(
                                                    true,
                                                    left_name,
                                                    true,
                                                    right_container_has_value,
                                                    right_name,
                                                    true,
                                                    detailed_name_suffix.str(),
                                                    log,
                                                    log_comparison_details );
        
      if( !local_success )
        success = false;

      ++left_it;
    }

    return success;
  }
};

/*! \brief Specialization of the 
 * STLCompliantAssociativeContainerElementComparisonHelper for dominant
 * right containers.
 * \ingroup comparison_traits
 */
template<>
struct STLCompliantAssociativeContainerElementComparisonHelper<false>
{
  template<size_t RightShift,
           typename LeftContainer,
           typename RightContainer,
           typename ExtraDataType>
  static inline bool compareElements(
                            const LeftContainer& left_container,
                            const std::string& left_name,
                            const bool log_left_name,
                            const RightContainer& right_container,
                            const std::string& right_name,
                            const bool log_right_name,
                            const std::string& name_suffix,
                            std::ostream& log,
                            const bool log_comparison_details = false,
                            const ExtraDataType& extra_data = ExtraDataType() )
  {
    typename RightContainer::const_iterator right_it, right_end;
    right_it = right_container.begin();
    right_end = right_container.end();

    bool success = true;
    std::ostringstream detailed_name_suffix;
      
    while( right_it != right_end )
    {
      if( name_suffix.size() > 0 )
        detailed_name_suffix.str( name_suffix );
      else
        detailed_name_suffix.str( "" );
      
      detailed_name_suffix.clear();

      detailed_name_suffix << " contains " << Utility::toString( *right_it );

      const bool left_container_has_value =
        std::find( left_container.begin(), left_container.end(), *right_it ) != left_container.end();
          
      bool local_success =
        Utility::ComparisonTraits<bool>::template compare<Utility::EqualityComparisonPolicy,RightShift,Details::incrementRightShift(RightShift)>(
                                                    left_container_has_value,
                                                    left_name,
                                                    true,
                                                    true,
                                                    right_name,
                                                    true,
                                                    detailed_name_suffix.str(),
                                                    log,
                                                    log_comparison_details );
        
      if( !local_success )
        success = false;

      ++right_it;
    }

    return success;
  }
};

/*! The comparison policy helper for stl compliant associative containers
 * \ingroup comparison_traits
 */
template<typename Policy, typename Enabled = void>
struct AssociativeContainerComparisonPolicyHelper
{
  /*! \brief Create the comparison header (this won't compile if this class is
   * not specialized for the comparison policy of interest).
   */
  template<size_t RightShift,
           bool LeftContainerIsDominant,
           typename LeftContainer,
           typename RightContainer,
           typename ExtraDataType>
  static inline std::string createComparisonHeader(
                            const LeftContainer& left_value,
                            const std::string& left_name,
                            const bool log_left_name,
                            const RightContainer& right_value,
                            const std::string& right_name,
                            const bool log_right_name,
                            const std::string& name_suffix,
                            const ExtraDataType& extra_data = ExtraDataType() )
  { return Policy::cannotCompareAssociativeContainersWithThisPolicy(); }

  /*! \brief Compare two containers (this won't compile if this class is not
   * specialized for the comparison policy of interest).
   */
  template<size_t HeaderRightShift,
           size_t DetailsRightShift,
           bool LeftContainerIsDominant,
           typename LeftContainer,
           typename RightContainer,
           typename ExtraDataType>
  static inline bool compare(
                            const LeftContainer& left_value,
                            const std::string& left_name,
                            const bool log_left_name,
                            const RightContainer& right_value,
                            const std::string& right_name,
                            const bool log_right_name,
                            const std::string& name_suffix,
                            std::ostream& log,
                            const bool log_comparison_details = false,
                            const ExtraDataType& extra_data = ExtraDataType() )
  { return Policy::cannotCompareAssociativeContainersWithThisPolicy();  }
};

/*! \brief Partial specialization of AssociativeContainerComparisonPolicyHelper
 * for Utility::EqualityComparisonPolicy
 * \ingroup comparison_traits
 */
template<typename Policy>
struct AssociativeContainerComparisonPolicyHelper<Policy,typename std::enable_if<std::is_same<Policy,Utility::EqualityComparisonPolicy>::value>::type>
{
private:

  // Typedef of this type
  typedef AssociativeContainerComparisonPolicyHelper<Policy,typename std::enable_if<std::is_same<Policy,Utility::EqualityComparisonPolicy>::value>::type> ThisType;

public:
  
  //! Create the comparison header
  template<size_t RightShift,
           bool LeftContainerIsDominant,
           typename LeftContainer,
           typename RightContainer,
           typename ExtraDataType>
  static inline std::string createComparisonHeader(
                            const LeftContainer& left_value,
                            const std::string& left_name,
                            const bool log_left_name,
                            const RightContainer& right_value,
                            const std::string& right_name,
                            const bool log_right_name,
                            const std::string& name_suffix,
                            const ExtraDataType& extra_data = ExtraDataType() )
  {
    typedef typename std::conditional<LeftContainerIsDominant,typename LeftContainer::value_type,typename RightContainer::value_type>::type ValueType;
    
    std::string detailed_left_name =
      Details::createDetailedContainerName( left_value,
                                            left_name,
                                            log_left_name,
                                            name_suffix );

    std::string detailed_right_name =
      Details::createDetailedContainerName( right_value,
                                            right_name,
                                            log_right_name,
                                            name_suffix );

    std::ostringstream oss;

    oss << std::string( RightShift, ' ' )
        << detailed_left_name << " has the same contents as "
        << detailed_right_name << ": ";

    return oss.str();
  }

  //! Compare two containers
  template<size_t HeaderRightShift,
           size_t DetailsRightShift,
           bool LeftContainerIsDominant,
           typename LeftContainer,
           typename RightContainer,
           typename ExtraDataType>
  static inline bool compare(
                            const LeftContainer& left_container,
                            const std::string& left_name,
                            const bool log_left_name,
                            const RightContainer& right_container,
                            const std::string& right_name,
                            const bool log_right_name,
                            const std::string& name_suffix,
                            std::ostream& log,
                            const bool log_comparison_details = false,
                            const ExtraDataType& extra_data = ExtraDataType() )
  {
    typedef typename std::conditional<LeftContainerIsDominant,typename LeftContainer::value_type,typename RightContainer::value_type>::type ValueType;

    if( log_comparison_details )
    {
      log << ThisType::template createComparisonHeader<HeaderRightShift,LeftContainerIsDominant>(
                                                               left_container,
                                                               left_name,
                                                               log_left_name,
                                                               right_container,
                                                               right_name,
                                                               log_right_name,
                                                               name_suffix,
                                                               extra_data );
    }
    
    std::ostringstream local_log, detailed_name_suffix;
    
    if( log_comparison_details )
      detailed_name_suffix << name_suffix << ".size()";

    bool success =
      Utility::ComparisonTraits<size_t>::template compare<Policy,DetailsRightShift,Details::incrementRightShift(DetailsRightShift)>(
               std::distance( left_container.begin(), left_container.end() ),
               left_name,
               log_left_name,
               std::distance( right_container.begin(), right_container.end() ),
               right_name,
               log_right_name,
               (log_comparison_details ? detailed_name_suffix.str() : name_suffix),
               local_log,
               log_comparison_details );

    // Only test the individual container elements if the sizes are the same
    if( success )
    {
      success =
        STLCompliantAssociativeContainerElementComparisonHelper<LeftContainerIsDominant>::template compareElements<DetailsRightShift>(
                                                      left_container,
                                                      left_name,
                                                      log_left_name,
                                                      right_container,
                                                      right_name,
                                                      log_right_name,
                                                      name_suffix,
                                                      local_log,
                                                      log_comparison_details,
                                                      extra_data );
    }

    if( log_comparison_details )
    {
      Utility::reportComparisonPassFail( success, log );
      log << local_log.str();
    }

    return success;
  }
};

/*! \brief Partial specialization of AssociativeContainerComparisonPolicyHelper
 * for Utility::InequalityComparisonPolicy
 * \ingroup comparison_traits
 */
template<typename Policy>
struct AssociativeContainerComparisonPolicyHelper<Policy,typename std::enable_if<std::is_same<Policy,Utility::InequalityComparisonPolicy>::value>::type>
{
private:

  // Typedef of this type
  typedef AssociativeContainerComparisonPolicyHelper<Policy,typename std::enable_if<std::is_same<Policy,Utility::InequalityComparisonPolicy>::value>::type> ThisType;

public:
  
  //! Create the comparison header
  template<size_t RightShift,
           bool LeftContainerIsDominant,
           typename LeftContainer,
           typename RightContainer,
           typename ExtraDataType>
  static inline std::string createComparisonHeader(
                            const LeftContainer& left_value,
                            const std::string& left_name,
                            const bool log_left_name,
                            const RightContainer& right_value,
                            const std::string& right_name,
                            const bool log_right_name,
                            const std::string& name_suffix,
                            const ExtraDataType& extra_data = ExtraDataType() )
  {
    typedef typename std::conditional<LeftContainerIsDominant,typename LeftContainer::value_type,typename RightContainer::value_type>::type ValueType;
    
    std::string detailed_left_name =
      Details::createDetailedContainerName( left_value,
                                            left_name,
                                            log_left_name,
                                            name_suffix );

    std::string detailed_right_name =
      Details::createDetailedContainerName( right_value,
                                            right_name,
                                            log_right_name,
                                            name_suffix );

    std::ostringstream oss;

    oss << std::string( RightShift, ' ' )
        << detailed_left_name << " does not have the same contents as "
        << detailed_right_name << ": ";

    return oss.str();
  }

  //! Compare two containers
  template<size_t HeaderRightShift,
           size_t DetailsRightShift,
           bool LeftContainerIsDominant,
           typename LeftContainer,
           typename RightContainer,
           typename ExtraDataType>
  static inline bool compare(
                            const LeftContainer& left_container,
                            const std::string& left_name,
                            const bool log_left_name,
                            const RightContainer& right_container,
                            const std::string& right_name,
                            const bool log_right_name,
                            const std::string& name_suffix,
                            std::ostream& log,
                            const bool log_comparison_details = false,
                            const ExtraDataType& extra_data = ExtraDataType() )
  {
    typedef typename std::conditional<LeftContainerIsDominant,typename LeftContainer::value_type,typename RightContainer::value_type>::type ValueType;

    if( log_comparison_details )
    {
      log << ThisType::template createComparisonHeader<HeaderRightShift,LeftContainerIsDominant>(
                                                               left_container,
                                                               left_name,
                                                               log_left_name,
                                                               right_container,
                                                               right_name,
                                                               log_right_name,
                                                               name_suffix,
                                                               extra_data );
    }
    
    std::ostringstream local_log, detailed_name_suffix;
    
    if( log_comparison_details )
      detailed_name_suffix << name_suffix << ".size()";

    bool success =
      Utility::ComparisonTraits<size_t>::template compare<Policy,DetailsRightShift,Details::incrementRightShift(DetailsRightShift)>(
               std::distance( left_container.begin(), left_container.end() ),
               left_name,
               false,
               std::distance( right_container.begin(), right_container.end() ),
               right_name,
               false,
               name_suffix,
               log,
               false );

    // Only test the individual container elements if the sizes are the same
    if( !success )
    {
      typename LeftContainer::const_iterator left_it, left_end;
      left_it = left_container.begin();
      left_end = left_container.end();
      
      while( left_it != left_end )
      {
        if( std::find( right_container.begin(), right_container.end(), *left_it ) == right_container.end() )
        {
          success = true;
          break;
        }
       
        ++left_it;
      }
    }

    if( log_comparison_details )
      Utility::reportComparisonPassFail( success, log );
    
    return success;
  }
};

/*! The comparison traits helper for stl compliant sequence containers
 * \ingroup comparison_traits
 */
template<typename STLCompliantSequenceContainer>
struct ComparisonTraitsSequenceContainerHelper
{
private:
  
  // Typedef for this type
  typedef ComparisonTraitsSequenceContainerHelper<STLCompliantSequenceContainer> ThisType;

  // Typedef for is_convertible result
  template<typename T2>
  struct IsConvertible : public std::is_convertible<T2,typename STLCompliantSequenceContainer::value_type>
  { /* ... */ };

public:
  
  //! Check if the comparison is allowed
  template<typename ComparisonPolicy>
  struct IsComparisonAllowed : public std::conditional<std::is_same<ComparisonPolicy,Utility::EqualityComparisonPolicy>::value || std::is_same<ComparisonPolicy,Utility::CloseComparisonPolicy>::value || std::is_same<ComparisonPolicy,Utility::RelativeErrorComparisonPolicy>::value || std::is_same<ComparisonPolicy,Utility::InequalityComparisonPolicy>::value, std::true_type, std::false_type>::type
  { /* ... */ };
    
  //! The extra data type (usually a comparison tolerance)
  typedef typename Utility::ComparisonTraits<typename STLCompliantSequenceContainer::value_type>::ExtraDataType ExtraDataType;
  
public:

  //! Create a comparison header
  template<typename ComparisonPolicy, size_t RightShift>
  static inline std::string createComparisonHeader(
                           const STLCompliantSequenceContainer& left_value,
                           const std::string& left_name,
                           const bool log_left_name,
                           const STLCompliantSequenceContainer& right_value,
                           const std::string& right_name,
                           const bool log_right_name,
                           const std::string& name_suffix,
                           const ExtraDataType& extra_data = ExtraDataType() )
  {
    return SequenceContainerComparisonPolicyHelper<ComparisonPolicy>::template createComparisonHeader<RightShift,true>(
                                                                left_value,
                                                                left_name,
                                                                log_left_name,
                                                                right_value,
                                                                right_name,
                                                                log_right_name,
                                                                name_suffix,
                                                                extra_data );
  }

  //! Create a comparison header
  template<typename ComparisonPolicy, size_t RightShift, typename T2>
  static inline typename std::enable_if<ThisType::IsConvertible<T2>::value,std::string>::type
  createComparisonHeader( std::initializer_list<T2> left_value,
                          const std::string& left_name,
                          const bool log_left_name,
                          const STLCompliantSequenceContainer& right_value,
                          const std::string& right_name,
                          const bool log_right_name,
                          const std::string& name_suffix,
                          const ExtraDataType& extra_data = ExtraDataType() )
  {
    return SequenceContainerComparisonPolicyHelper<ComparisonPolicy>::template createComparisonHeader<RightShift,false>(
                                                                left_value,
                                                                left_name,
                                                                log_left_name,
                                                                right_value,
                                                                right_name,
                                                                log_right_name,
                                                                name_suffix,
                                                                extra_data );
  }

  //! Create a comparison header
  template<typename ComparisonPolicy, size_t RightShift, typename T2>
  static inline typename std::enable_if<ThisType::IsConvertible<T2>::value,std::string>::type
  createComparisonHeader(
                           const STLCompliantSequenceContainer& left_value,
                           const std::string& left_name,
                           const bool log_left_name,
                           std::initializer_list<T2> right_value,
                           const std::string& right_name,
                           const bool log_right_name,
                           const std::string& name_suffix,
                           const ExtraDataType& extra_data = ExtraDataType() )
  {
    return SequenceContainerComparisonPolicyHelper<ComparisonPolicy>::template createComparisonHeader<RightShift,true>(
                                                                left_value,
                                                                left_name,
                                                                log_left_name,
                                                                right_value,
                                                                right_name,
                                                                log_right_name,
                                                                name_suffix,
                                                                extra_data );
  }
  
  //! Compare two sequence containers
  template<typename ComparisonPolicy,
           size_t HeaderRightShift,
           size_t DetailsRightShift>
  static inline bool compare(
                          const STLCompliantSequenceContainer& left_value,
                          const std::string& left_name,
                          const bool log_left_name,
                          const STLCompliantSequenceContainer& right_value,
                          const std::string& right_name,
                          const bool log_right_name,
                          const std::string& name_suffix,
                          std::ostream& log,
                          const bool log_comparison_details = false,
                          const ExtraDataType& extra_data = ExtraDataType() )
  {
    return SequenceContainerComparisonPolicyHelper<ComparisonPolicy>::template compare<HeaderRightShift,DetailsRightShift,true>(
                                                        left_value,
                                                        left_name,
                                                        log_left_name,
                                                        right_value,
                                                        right_name,
                                                        log_right_name,
                                                        name_suffix,
                                                        log,
                                                        log_comparison_details,
                                                        extra_data );
  }

  //! Compare two sequence containers
  template<typename ComparisonPolicy,
           size_t HeaderRightShift,
           size_t DetailsRightShift,
           typename T2>
  static inline typename std::enable_if<ThisType::IsConvertible<T2>::value,bool>::type
  compare( std::initializer_list<T2> left_value,
           const std::string& left_name,
           const bool log_left_name,
           const STLCompliantSequenceContainer& right_value,
           const std::string& right_name,
           const bool log_right_name,
           const std::string& name_suffix,
           std::ostream& log,
           const bool log_comparison_details = false,
           const ExtraDataType& extra_data = ExtraDataType() )
  {
    return SequenceContainerComparisonPolicyHelper<ComparisonPolicy>::template compare<HeaderRightShift,DetailsRightShift,false>(
                                                        left_value,
                                                        left_name,
                                                        log_left_name,
                                                        right_value,
                                                        right_name,
                                                        log_right_name,
                                                        name_suffix,
                                                        log,
                                                        log_comparison_details,
                                                        extra_data );
  }

  //! Compare two sequence containers
  template<typename ComparisonPolicy,
           size_t HeaderRightShift,
           size_t DetailsRightShift,
           typename T2>
  static inline typename std::enable_if<ThisType::IsConvertible<T2>::value,bool>::type
  compare( const STLCompliantSequenceContainer& left_value,
           const std::string& left_name,
           const bool log_left_name,
           std::initializer_list<T2> right_value,
           const std::string& right_name,
           const bool log_right_name,
           const std::string& name_suffix,
           std::ostream& log,
           const bool log_comparison_details = false,
           const ExtraDataType& extra_data = ExtraDataType() )
  {
    return SequenceContainerComparisonPolicyHelper<ComparisonPolicy>::template compare<HeaderRightShift,DetailsRightShift,true>(
                                                        left_value,
                                                        left_name,
                                                        log_left_name,
                                                        right_value,
                                                        right_name,
                                                        log_right_name,
                                                        name_suffix,
                                                        log,
                                                        log_comparison_details,
                                                        extra_data );
  }
};

//! The comparison traits helper for stl compliant associative containers
template<typename STLCompliantAssociativeContainer>
struct ComparisonTraitsAssociativeContainerHelper
{
private:

  // Typedef for this type
  typedef ComparisonTraitsAssociativeContainerHelper<STLCompliantAssociativeContainer> ThisType;

  // Typedef for is_convertible result
  template<typename T2>
  struct IsConvertible : public std::is_convertible<T2,typename STLCompliantAssociativeContainer::value_type>
  { /* ... */ };

public:
  
  //! Check if the comparison is allowed
  template<typename ComparisonPolicy>
  struct IsComparisonAllowed : public std::conditional<std::is_same<ComparisonPolicy,Utility::EqualityComparisonPolicy>::value || std::is_same<ComparisonPolicy,Utility::InequalityComparisonPolicy>::value, std::true_type, std::false_type>::type
  { /* ... */ };
  
  //! The extra data type (usually a comparison tolerance)
  typedef typename Utility::ComparisonTraits<typename STLCompliantAssociativeContainer::value_type>::ExtraDataType ExtraDataType;

  //! Create a comparison header
  template<typename ComparisonPolicy, size_t RightShift>
  static inline std::string createComparisonHeader(
                           const STLCompliantAssociativeContainer& left_value,
                           const std::string& left_name,
                           const bool log_left_name,
                           const STLCompliantAssociativeContainer& right_value,
                           const std::string& right_name,
                           const bool log_right_name,
                           const std::string& name_suffix,
                           const ExtraDataType& extra_data = ExtraDataType() )
  {
    return AssociativeContainerComparisonPolicyHelper<ComparisonPolicy>::template createComparisonHeader<RightShift,true>(
                                                                left_value,
                                                                left_name,
                                                                log_left_name,
                                                                right_value,
                                                                right_name,
                                                                log_right_name,
                                                                name_suffix,
                                                                extra_data );
  }

  //! Create a comparison header
  template<typename ComparisonPolicy, size_t RightShift, typename T2>
  static inline typename std::enable_if<ThisType::IsConvertible<T2>::value,std::string>::type
  createComparisonHeader( std::initializer_list<T2> left_value,
                          const std::string& left_name,
                          const bool log_left_name,
                          const STLCompliantAssociativeContainer& right_value,
                          const std::string& right_name,
                          const bool log_right_name,
                          const std::string& name_suffix,
                          const ExtraDataType& extra_data = ExtraDataType() )
  {
    return AssociativeContainerComparisonPolicyHelper<ComparisonPolicy>::template createComparisonHeader<RightShift,false>(
                                                                left_value,
                                                                left_name,
                                                                log_left_name,
                                                                right_value,
                                                                right_name,
                                                                log_right_name,
                                                                name_suffix,
                                                                extra_data );
  }

  //! Create a comparison header
  template<typename ComparisonPolicy, size_t RightShift, typename T2>
  static inline typename std::enable_if<ThisType::IsConvertible<T2>::value,std::string>::type
  createComparisonHeader(
                           const STLCompliantAssociativeContainer& left_value,
                           const std::string& left_name,
                           const bool log_left_name,
                           std::initializer_list<T2> right_value,
                           const std::string& right_name,
                           const bool log_right_name,
                           const std::string& name_suffix,
                           const ExtraDataType& extra_data = ExtraDataType() )
  {
    return AssociativeContainerComparisonPolicyHelper<ComparisonPolicy>::template createComparisonHeader<RightShift,true>(
                                                                left_value,
                                                                left_name,
                                                                log_left_name,
                                                                right_value,
                                                                right_name,
                                                                log_right_name,
                                                                name_suffix,
                                                                extra_data );
  }
  
  //! Compare two sequence containers
  template<typename ComparisonPolicy,
           size_t HeaderRightShift,
           size_t DetailsRightShift>
  static inline bool compare(
                          const STLCompliantAssociativeContainer& left_value,
                          const std::string& left_name,
                          const bool log_left_name,
                          const STLCompliantAssociativeContainer& right_value,
                          const std::string& right_name,
                          const bool log_right_name,
                          const std::string& name_suffix,
                          std::ostream& log,
                          const bool log_comparison_details = false,
                          const ExtraDataType& extra_data = ExtraDataType() )
  {
    return AssociativeContainerComparisonPolicyHelper<ComparisonPolicy>::template compare<HeaderRightShift,DetailsRightShift,true>(
                                                        left_value,
                                                        left_name,
                                                        log_left_name,
                                                        right_value,
                                                        right_name,
                                                        log_right_name,
                                                        name_suffix,
                                                        log,
                                                        log_comparison_details,
                                                        extra_data );
  }

  //! Compare two sequence containers
  template<typename ComparisonPolicy,
           size_t HeaderRightShift,
           size_t DetailsRightShift,
           typename T2>
  static inline typename std::enable_if<ThisType::IsConvertible<T2>::value,bool>::type
  compare( std::initializer_list<T2> left_value,
           const std::string& left_name,
           const bool log_left_name,
           const STLCompliantAssociativeContainer& right_value,
           const std::string& right_name,
           const bool log_right_name,
           const std::string& name_suffix,
           std::ostream& log,
           const bool log_comparison_details = false,
           const ExtraDataType& extra_data = ExtraDataType() )
  {
    return AssociativeContainerComparisonPolicyHelper<ComparisonPolicy>::template compare<HeaderRightShift,DetailsRightShift,false>(
                                                        left_value,
                                                        left_name,
                                                        log_left_name,
                                                        right_value,
                                                        right_name,
                                                        log_right_name,
                                                        name_suffix,
                                                        log,
                                                        log_comparison_details,
                                                        extra_data );
  }

  //! Compare two sequence containers
  template<typename ComparisonPolicy,
           size_t HeaderRightShift,
           size_t DetailsRightShift,
           typename T2>
  static inline typename std::enable_if<ThisType::IsConvertible<T2>::value,bool>::type
  compare( const STLCompliantAssociativeContainer& left_value,
           const std::string& left_name,
           const bool log_left_name,
           std::initializer_list<T2> right_value,
           const std::string& right_name,
           const bool log_right_name,
           const std::string& name_suffix,
           std::ostream& log,
           const bool log_comparison_details = false,
           const ExtraDataType& extra_data = ExtraDataType() )
  {
    return AssociativeContainerComparisonPolicyHelper<ComparisonPolicy>::template compare<HeaderRightShift,DetailsRightShift,true>(
                                                        left_value,
                                                        left_name,
                                                        log_left_name,
                                                        right_value,
                                                        right_name,
                                                        log_right_name,
                                                        name_suffix,
                                                        log,
                                                        log_comparison_details,
                                                        extra_data );
  }
};
  
} // end Details namespace

/*! Partial specialization of ComparisonTraits for std::initializer_list
 * \ingroup comparison_traits
 */
template<typename T>
struct ComparisonTraits<std::initializer_list<T> > : public Details::ComparisonTraitsSequenceContainerHelper<std::initializer_list<T> >
{ /* ... */ };

// Create a comparison header
template<typename ComparisonPolicy,
         size_t RightShift,
         typename T1,
         typename T2>
inline std::string createComparisonHeader(
                 const T1& left_value,
                 const std::string& left_name,
                 const T2& right_value,
                 const std::string& right_name,
                 const typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType& extra_data,
                 const std::string& name_suffix )
{
  return ComparisonTraits<typename std::common_type<T1,T2>::type>::template createComparisonHeader<ComparisonPolicy,RightShift>(
                                                                left_value,
                                                                left_name,
                                                                true,
                                                                right_value,
                                                                right_name,
                                                                true,
                                                                name_suffix,
                                                                extra_data );
}

// Compare two values and print the results (to the desired stream)
template<typename ComparisonPolicy,
         size_t HeaderRightShift,
         size_t DetailsRightShift,
         typename T1,
         typename T2>
inline bool compare(
                 const T1& left_value,
                 const std::string& left_name,
                 const T2& right_value,
                 const std::string& right_name,
                 std::ostream& log,
                 const typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType& extra_data,
                 const bool log_comparison_details,
                 const std::string& name_suffix )
{
  return ComparisonTraits<typename std::common_type<T1,T2>::type>::template compare<ComparisonPolicy,HeaderRightShift,DetailsRightShift>(
                                                      left_value,
                                                      left_name,
                                                      true,
                                                      right_value,
                                                      right_name,
                                                      true,
                                                      name_suffix,
                                                      log,
                                                      log_comparison_details,
                                                      extra_data );
}

// Create a comparison header
template<typename ComparisonPolicy,
         size_t RightShift,
         typename T1,
         typename T2>
inline std::string createComparisonHeader(
                 T1&& left_value,
                 const std::string& left_name,
                 const T2& right_value,
                 const std::string& right_name,
                 const typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType& extra_data,
                 const std::string& name_suffix )
{
  typedef typename std::conditional<std::is_lvalue_reference<T1>::value,std::true_type,std::false_type>::type LeftDisplayBoolean;
  
  return ComparisonTraits<typename std::common_type<T1,T2>::type>::template createComparisonHeader<ComparisonPolicy,RightShift>(
                                                     left_value,
                                                     left_name,
                                                     LeftDisplayBoolean::value,
                                                     right_value,
                                                     right_name,
                                                     true,
                                                     name_suffix,
                                                     extra_data );
}

// Compare two values and print the results (to the desired stream)
template<typename ComparisonPolicy,
         size_t HeaderRightShift,
         size_t DetailsRightShift,
         typename T1,
         typename T2>
inline bool compare(
                 T1&& left_value,
                 const std::string& left_name,
                 const T2& right_value,
                 const std::string& right_name,
                 std::ostream& log,
                 const typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType& extra_data,
                 const bool log_comparison_details,
                 const std::string& name_suffix )
{
  typedef typename std::conditional<std::is_lvalue_reference<T1>::value,std::true_type,std::false_type>::type LeftDisplayBoolean;
  
  return ComparisonTraits<typename std::common_type<T1,T2>::type>::template compare<ComparisonPolicy,HeaderRightShift,DetailsRightShift>(
                                                     left_value,
                                                     left_name,
                                                     LeftDisplayBoolean::value,
                                                     right_value,
                                                     right_name,
                                                     true,
                                                     name_suffix,
                                                     log,
                                                     log_comparison_details,
                                                     extra_data );
}

// Create a comparison header
template<typename ComparisonPolicy,
         size_t RightShift,
         typename T1,
         typename T2>
inline std::string createComparisonHeader(
                 const T1& left_value,
                 const std::string& left_name,
                 T2&& right_value,
                 const std::string& right_name,
                 const typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType& extra_data,
                 const std::string& name_suffix )
{
  typedef typename std::conditional<std::is_lvalue_reference<T2>::value,std::true_type,std::false_type>::type RightDisplayBoolean;
  
  return ComparisonTraits<typename std::common_type<T1,T2>::type>::template createComparisonHeader<ComparisonPolicy,RightShift>(
                                                    left_value,
                                                    left_name,
                                                    true,
                                                    right_value,
                                                    right_name,
                                                    RightDisplayBoolean::value,
                                                    name_suffix,
                                                    extra_data );
}

// Compare two values and print the results (to the desired stream)
template<typename ComparisonPolicy,
         size_t HeaderRightShift,
         size_t DetailsRightShift,
         typename T1,
         typename T2>
inline bool compare(
                 const T1& left_value,
                 const std::string& left_name,
                 T2&& right_value,
                 const std::string& right_name,
                 std::ostream& log,
                 const typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType& extra_data,
                 const bool log_comparison_details,
                 const std::string& name_suffix )
{
  typedef typename std::conditional<std::is_lvalue_reference<T2>::value,std::true_type,std::false_type>::type RightDisplayBoolean;
  
  return ComparisonTraits<typename std::common_type<T1,T2>::type>::template compare<ComparisonPolicy,HeaderRightShift,DetailsRightShift>(
                                                    left_value,
                                                    left_name,
                                                    true,
                                                    right_value,
                                                    right_name,
                                                    RightDisplayBoolean::value,
                                                    name_suffix,
                                                    log,
                                                    log_comparison_details,
                                                    extra_data );
}

// Create a comparison header
template<typename ComparisonPolicy,
         size_t RightShift,
         typename T1,
         typename T2>
inline std::string createComparisonHeader(
                 T1&& left_value,
                 const std::string& left_name,
                 T2&& right_value,
                 const std::string& right_name,
                 const typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType& extra_data,
                 const std::string& name_suffix )
{
  typedef typename std::conditional<std::is_lvalue_reference<T1>::value,std::true_type,std::false_type>::type LeftDisplayBoolean;
  typedef typename std::conditional<std::is_lvalue_reference<T2>::value,std::true_type,std::false_type>::type RightDisplayBoolean;

  return ComparisonTraits<typename std::common_type<T1,T2>::type>::template createComparisonHeader<ComparisonPolicy,RightShift>(
                                                    left_value,
                                                    left_name,
                                                    LeftDisplayBoolean::value,
                                                    right_value,
                                                    right_name,
                                                    RightDisplayBoolean::value,
                                                    name_suffix,
                                                    extra_data );
}

// Compare two values and print the results (to the desired stream)
template<typename ComparisonPolicy,
         size_t HeaderRightShift,
         size_t DetailsRightShift,
         typename T1,
         typename T2>
inline bool compare(
                 T1&& left_value,
                 const std::string& left_name,
                 T2&& right_value,
                 const std::string& right_name,
                 std::ostream& log,
                 const typename ComparisonTraits<typename std::common_type<T1,T2>::type>::ExtraDataType& extra_data,
                 const bool log_comparison_details,
                 const std::string& name_suffix )
{
  typedef typename std::conditional<std::is_lvalue_reference<T1>::value,std::true_type,std::false_type>::type LeftDisplayBoolean;
  typedef typename std::conditional<std::is_lvalue_reference<T2>::value,std::true_type,std::false_type>::type RightDisplayBoolean;
  
  return ComparisonTraits<typename std::common_type<T1,T2>::type>::template compare<ComparisonPolicy,HeaderRightShift,DetailsRightShift>(
                                                    left_value,
                                                    left_name,
                                                    LeftDisplayBoolean::value,
                                                    right_value,
                                                    right_name,
                                                    RightDisplayBoolean::value,
                                                    name_suffix,
                                                    log,
                                                    log_comparison_details,
                                                    extra_data );
}

// Create a comparison header
template<typename ComparisonPolicy,
         size_t RightShift,
         typename Container,
         typename T>
std::string createComparisonHeader(
         std::initializer_list<T> left_value,
         const std::string& left_name,
         const Container& right_value,
         const std::string& right_name,
         const typename ComparisonTraits<Container>::ExtraDataType& extra_data,
         const std::string& name_suffix )
{
  return ComparisonTraits<Container>::template createComparisonHeader<ComparisonPolicy,RightShift>(
                                                                left_value,
                                                                left_name,
                                                                false,
                                                                right_value,
                                                                right_name,
                                                                true,
                                                                name_suffix,
                                                                extra_data );
}

// Compare two values and print the results (to the desired stream)
template<typename ComparisonPolicy,
         size_t HeaderRightShift,
         size_t DetailsRightShift,
         typename Container,
         typename T>
bool compare(
         std::initializer_list<T> left_value,
         const std::string& left_name,
         const Container& right_value,
         const std::string& right_name,
         std::ostream& log,
         const typename ComparisonTraits<Container>::ExtraDataType& extra_data,
         const bool log_comparison_details,
         const std::string& name_suffix )
{
  return ComparisonTraits<Container>::template compare<ComparisonPolicy,HeaderRightShift,DetailsRightShift>(
                                                       left_value,
                                                       left_name,
                                                       false,
                                                       right_value,
                                                       right_name,
                                                       true,
                                                       name_suffix,
                                                       log,
                                                       log_comparison_details,
                                                       extra_data );
}

// Create a comparison header
template<typename ComparisonPolicy,
         size_t RightShift,
         typename Container,
         typename T>
std::string createComparisonHeader(
         const Container& left_value,
         const std::string& left_name,
         std::initializer_list<T> right_value,
         const std::string& right_name,
         const typename ComparisonTraits<Container>::ExtraDataType& extra_data,
         const std::string& name_suffix )
{
  return ComparisonTraits<Container>::template createComparisonHeader<ComparisonPolicy,RightShift>(
                                                                left_value,
                                                                left_name,
                                                                true,
                                                                right_value,
                                                                right_name,
                                                                false,
                                                                name_suffix,
                                                                extra_data );
}
  
// Compare two values and print the results (to the desired stream)
template<typename ComparisonPolicy,
         size_t HeaderRightShift,
         size_t DetailsRightShift,
         typename Container,
         typename T>
bool compare(
         const Container& left_value,
         const std::string& left_name,
         std::initializer_list<T> right_value,
         const std::string& right_name,
         std::ostream& log,
         const typename ComparisonTraits<Container>::ExtraDataType& extra_data,
         const bool log_comparison_details,
         const std::string& name_suffix )
{
  return ComparisonTraits<Container>::template compare<ComparisonPolicy,HeaderRightShift,DetailsRightShift>(
                                                       left_value,
                                                       left_name,
                                                       true,
                                                       right_value,
                                                       right_name,
                                                       false,
                                                       name_suffix,
                                                       log,
                                                       log_comparison_details,
                                                       extra_data );
}

} // end Utility namespace

#endif // end UTILITY_COMPARISON_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_ComparisonTraits.hpp
//---------------------------------------------------------------------------//
