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
#include <type_traits>

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_ComparisonTraitsDecl.hpp"
#include "Utility_ComparisonPolicy.hpp"

namespace Utility{

namespace Details{

/*! Increment the right shift
 * \ingroup comparison_traits
 */
constexpr size_t incrementRightShift( const size_t right_shift )
{ return right_shift+2; }

/*! Default implementation of the createComparisonHeader method
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy,
         size_t RightShift,
         typename T,
         typename ExtraDataType>
inline std::string createComparisonHeaderImpl(
                                              const T& left_value,
                                              const std::string& left_name,
                                              const bool log_left_name,
                                              const T& right_value,
                                              const std::string& right_name,
                                              const bool log_right_name,
                                              const std::string& name_suffix,
                                              const ExtraDataType& extra_data )
{
  std::string comparison_header( RightShift, ' ' );

  comparison_header += ComparisonPolicy::createComparisonDetails(
                                       left_name, log_left_name, left_value,
                                       right_name, log_right_name, right_value,
                                       name_suffix, extra_data );
  comparison_header += ": ";

  return comparison_header;
}

/*! Default implementation of the compare method
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy,
         size_t RightShift,
         typename T,
         typename ExtraDataType>
inline bool compareImpl( const T& left_value,
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
  if( log_comparison_details )
  {
    log << Details::createComparisonHeaderImpl<ComparisonPolicy,RightShift>(
                                                                left_value,
                                                                left_name,
                                                                log_left_name,
                                                                right_value,
                                                                right_name,
                                                                log_right_name,
                                                                name_suffix,
                                                                extra_data );
  }

  // Conduct the comparison
  const bool success =
    ComparisonPolicy::compare( left_value, right_value, extra_data );

  if( log_comparison_details )
    Utility::reportComparisonPassFail( success, log );

  return success;
}
  
} // end Details namespace

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
template<typename ComparisonPolicy, size_t RightShift>
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
  return Details::compareImpl<ComparisonPolicy,RightShift>(
                                      left_value, left_name, log_left_name,
                                      right_value, right_name, log_right_name,
                                      name_suffix, log, log_comparison_details,
                                      extra_data );
};

/*! \brief The specialization of the Utility::ComparisonTraits for const and/or
 * volatile types.
 * \ingroup comparison_traits
 */
template<typename T>
struct ComparisonTraits<T,typename std::enable_if<std::is_const<T>::value || std::is_volatile<T>::value>::type> : public ComparisonTraits<typename std::remove_cv<T>::type>
{ /* ... */ };

namespace Details{

//! Create a detailed container name
template<typename Container>
static inline std::string createDetailedContainerName(
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
  template<size_t RightShift,
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
  template<size_t RightShift,
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
      log << ThisType::template createComparisonHeader<RightShift,LeftContainerIsDominant>(
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
        Utility::ComparisonTraits<size_t>::template compare<Policy,Details::incrementRightShift(RightShift)>(
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
          Utility::ComparisonTraits<ValueType>::template compare<Policy,Details::incrementRightShift(RightShift)>(
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
  template<size_t RightShift,
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
      log << ThisType::template createComparisonHeader<RightShift,LeftContainerIsDominant>(
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
      Utility::ComparisonTraits<size_t>::template compare<Policy,Details::incrementRightShift(RightShift)>(
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
          Utility::ComparisonTraits<ValueType>::template compare<Policy,Details::incrementRightShift(RightShift)>(
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

/*! The comparison policy helper for stl compliant associative containers
 * \ingroup comparison_traits
 */
template<typename Policy, typename STLCompliantAssociativeContainer, typename Enabled = void>
struct AssociativeContainerComparisonPolicyHelper
{
  /*! \brief Create the comparison header (this won't compile if this class is
   * not specialized for the comparison policy of interest).
   */
  static inline std::string createComparisonHeader(
       const STLCompliantAssociativeContainer& left_value,
       const std::string& left_name,
       const bool log_left_name,
       const STLCompliantAssociativeContainer& right_value,
       const std::string& right_name,
       const bool log_right_name,
       const std::string& name_suffix,
       const typename QuantityTraits<typename STLCompliantAssociativeContainer::value_type>::RawType& extra_data = 
       typename QuantityTraits<typename STLCompliantAssociativeContainer::value_type>::RawType() )
  { return Policy::cannotCompareAssociativeContainersWithThisPolicy(); }

  /*! \brief Compare two containers (this won't compile if this class is not
   * specialized for the comparison policy of interest).
   */
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
     const typename QuantityTraits<typename STLCompliantAssociativeContainer::value_type>::RawType& extra_data =
     typename QuantityTraits<typename STLCompliantAssociativeContainer::value_type>::RawType() )
  { return Policy::cannotCompareAssociativeContainersWithThisPolicy();  }
};

/*! \brief Partial specialization of AssociativeContainerComparisonPolicyHelper
 * for Utility::EqualityComparisonPolicy
 * \ingroup comparison_traits
 */
template<typename STLCompliantAssociativeContainer>
struct AssociativeContainerComparisonPolicyHelper<Utility::EqualityComparisonPolicy,STLCompliantAssociativeContainer>
{
  //! Create the comparison header
  static inline std::string createComparisonHeader(
       const STLCompliantAssociativeContainer& left_value,
       const std::string& left_name,
       const bool log_left_name,
       const STLCompliantAssociativeContainer& right_value,
       const std::string& right_name,
       const bool log_right_name,
       const std::string& name_suffix,
       const typename QuantityTraits<typename STLCompliantAssociativeContainer::value_type>::RawType& = 
       typename QuantityTraits<typename STLCompliantAssociativeContainer::value_type>::RawType() )
  {
    std::ostringstream oss;

    if( log_left_name )
    {
      oss << left_name;
    
      if( !name_suffix.empty() )
        oss << name_suffix;
    }
    else
      oss << Utility::toString( left_value );

    oss << " has the same contents as ";

    if( log_right_name )
    {
      oss << right_name;

      if( !name_suffix.empty() )
        oss << name_suffix;
    }
    else
      oss << Utility::toString( right_value );

    return oss.str();
  }

  //! Compare two containers
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
     const typename QuantityTraits<typename STLCompliantAssociativeContainer::value_type>::RawType& =
     typename QuantityTraits<typename STLCompliantAssociativeContainer::value_type>::RawType() )
  {
    std::ostringstream detailed_name_suffix;
    
    if( name_suffix.size() > 0 )
      detailed_name_suffix << name_suffix;

    detailed_name_suffix << " size";

    bool success =
      Utility::ComparisonTraits<size_t>::template compare<Utility::EqualityComparisonPolicy>(
                       std::distance( left_value.begin(), left_value.end() ),
                       left_name,
                       log_left_name,
                       std::distance( right_value.begin(), right_value.end() ),
                       right_name,
                       log_right_name,
                       detailed_name_suffix.str(),
                       log,
                       log_comparison_details );

    // Only test the individual container elements if the sizes are the same
    if( success )
    {
      typename STLCompliantAssociativeContainer::const_iterator left_it, left_end;
      left_it = left_value.begin();
      left_end = left_value.end();
      
      while( left_it != left_end )
      {
        if( name_suffix.size() > 0 )
          detailed_name_suffix.str( name_suffix );
        else
          detailed_name_suffix.str( "" );
        
        detailed_name_suffix.clear();

        detailed_name_suffix << ".contains("
                             << Utility::toString( *left_it ) << ")";
          
        bool local_success =
          Utility::ComparisonTraits<bool>::template compare<Utility::EqualityComparisonPolicy>(
               true,
               left_name,
               log_left_name,
               std::find( right_value.begin(), right_value.end(), *left_it ) !=
               right_value.end(),
               right_name,
               log_right_name,
               detailed_name_suffix.str(),
               log,
               log_comparison_details );
        
        if( !local_success )
          success = false;

        ++left_it;
      }
    }

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
  template<typename ComparisonPolicy, size_t RightShift>
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
    return SequenceContainerComparisonPolicyHelper<ComparisonPolicy>::template compare<RightShift,true>(
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
  template<typename ComparisonPolicy, size_t RightShift, typename T2>
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
    return SequenceContainerComparisonPolicyHelper<ComparisonPolicy>::template compare<RightShift,false>(
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
  template<typename ComparisonPolicy, size_t RightShift, typename T2>
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
    return SequenceContainerComparisonPolicyHelper<ComparisonPolicy>::template compare<RightShift,true>(
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
template<template<typename...> class STLCompliantAssociativeContainer,
         typename... Types>
struct ComparisonTraitsAssociativeContainerHelper
{
  //! Check if the comparison is allowed
  template<typename ComparisonPolicy>
  struct IsComparisonAllowed : public std::conditional<std::is_same<ComparisonPolicy,Utility::EqualityComparisonPolicy>::value, std::true_type, std::false_type>::type
  { /* ... */ };
  
  //! The extra data type (usually a comparison tolerance)
  typedef typename Utility::ComparisonTraits<typename STLCompliantAssociativeContainer<Types...>::value_type>::ExtraDataType ExtraDataType;

  //! Create a comparison header
  template<typename ComparisonPolicy>
  static std::string createComparisonHeader(
                 const STLCompliantAssociativeContainer<Types...>& left_value,
                 const std::string& left_name,
                 const bool log_left_name,
                 const STLCompliantAssociativeContainer<Types...>& right_value,
                 const std::string& right_name,
                 const bool log_right_name,
                 const std::string& name_suffix,
                 const ExtraDataType& = ExtraDataType() )
  {
    return AssociativeContainerComparisonPolicyHelper<ComparisonPolicy,STLCompliantAssociativeContainer<Types...> >::createComparisonHeader(
                                                                left_value,
                                                                left_name,
                                                                log_left_name,
                                                                right_value,
                                                                right_name,
                                                                log_right_name,
                                                                name_suffix );
  }

  //! Compare two associative containers
  template<typename ComparisonPolicy>
  static inline bool compare(
                 const STLCompliantAssociativeContainer<Types...>& left_value,
                 const std::string& left_name,
                 const bool log_left_name,
                 const STLCompliantAssociativeContainer<Types...>& right_value,
                 const std::string& right_name,
                 const bool log_right_name,
                 const std::string& name_suffix,
                 std::ostream& log,
                 const bool log_comparison_details = false,
                 const ExtraDataType& = ExtraDataType() )
  {
    return AssociativeContainerComparisonPolicyHelper<ComparisonPolicy,STLCompliantAssociativeContainer<Types...> >::compare(
                                                      left_value,
                                                      left_name,
                                                      log_left_name,
                                                      right_value,
                                                      right_name,
                                                      log_right_name,
                                                      name_suffix,
                                                      log_comparison_details );
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
template<typename ComparisonPolicy, size_t RightShift, typename T>
inline std::string createComparisonHeader(
                 const T& left_value,
                 const std::string& left_name,
                 const T& right_value,
                 const std::string& right_name,
                 const typename ComparisonTraits<T>::ExtraDataType& extra_data,
                 const std::string& name_suffix )
{
  return ComparisonTraits<T>::template createComparisonHeader<ComparisonPolicy,RightShift>(
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
template<typename ComparisonPolicy, size_t RightShift, typename T>
inline bool compare(
                 const T& left_value,
                 const std::string& left_name,
                 const T& right_value,
                 const std::string& right_name,
                 std::ostream& log,
                 const typename ComparisonTraits<T>::ExtraDataType& extra_data,
                 const bool log_comparison_details,
                 const std::string& name_suffix )
{
  return ComparisonTraits<T>::template compare<ComparisonPolicy,RightShift>(
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
template<typename ComparisonPolicy, size_t RightShift, typename T>
inline std::string createComparisonHeader(
                 T& left_value,
                 const std::string& left_name,
                 T& right_value,
                 const std::string& right_name,
                 const typename ComparisonTraits<T>::ExtraDataType& extra_data,
                 const std::string& name_suffix )
{
  return ComparisonTraits<T>::template createComparisonHeader<ComparisonPolicy,RightShift>(
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
template<typename ComparisonPolicy, size_t RightShift, typename T>
inline bool compare(
                 T& left_value,
                 const std::string& left_name,
                 T& right_value,
                 const std::string& right_name,
                 std::ostream& log,
                 const typename ComparisonTraits<T>::ExtraDataType& extra_data,
                 const bool log_comparison_details,
                 const std::string& name_suffix )
{
  return ComparisonTraits<T>::template compare<ComparisonPolicy,RightShift>(
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
template<typename ComparisonPolicy, size_t RightShift, typename T1, typename T2>
inline std::string createComparisonHeader(
                T1&& left_value,
                const std::string& left_name,
                const T2& right_value,
                const std::string& right_name,
                const typename ComparisonTraits<T2>::ExtraDataType& extra_data,
                const std::string& name_suffix )
{
  return ComparisonTraits<T2>::template createComparisonHeader<ComparisonPolicy,RightShift>(
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
template<typename ComparisonPolicy, size_t RightShift, typename T1, typename T2>
inline bool compare(
                T1&& left_value,
                const std::string& left_name,
                const T2& right_value,
                const std::string& right_name,
                std::ostream& log,
                const typename ComparisonTraits<T2>::ExtraDataType& extra_data,
                const bool log_comparison_details,
                const std::string& name_suffix )
{
  return ComparisonTraits<T2>::template compare<ComparisonPolicy,RightShift>(
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
template<typename ComparisonPolicy, size_t RightShift, typename Container, typename T>
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
template<typename ComparisonPolicy, size_t RightShift, typename Container, typename T>
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
  return ComparisonTraits<Container>::template compare<ComparisonPolicy,RightShift>(
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
template<typename ComparisonPolicy, size_t RightShift, typename T1, typename T2>
inline std::string createComparisonHeader(
                T1&& left_value,
                const std::string& left_name,
                T2& right_value,
                const std::string& right_name,
                const typename ComparisonTraits<T2>::ExtraDataType& extra_data,
                const std::string& name_suffix )
{
  return ComparisonTraits<T2>::template createComparisonHeader<ComparisonPolicy,RightShift>(
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
template<typename ComparisonPolicy, size_t RightShift, typename T1, typename T2>
inline bool compare(
                T1&& left_value,
                const std::string& left_name,
                T2& right_value,
                const std::string& right_name,
                std::ostream& log,
                const typename ComparisonTraits<T2>::ExtraDataType& extra_data,
                const bool log_comparison_details,
                const std::string& name_suffix )
{
  return ComparisonTraits<T2>::template compare<ComparisonPolicy,RightShift>(
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
template<typename ComparisonPolicy, size_t RightShift, typename Container, typename T>
std::string createComparisonHeader(
         std::initializer_list<T> left_value,
         const std::string& left_name,
         Container& right_value,
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
template<typename ComparisonPolicy, size_t RightShift, typename Container, typename T>
bool compare(
         std::initializer_list<T> left_value,
         const std::string& left_name,
         Container& right_value,
         const std::string& right_name,
         std::ostream& log,
         const typename ComparisonTraits<Container>::ExtraDataType& extra_data,
         const bool log_comparison_details,
         const std::string& name_suffix )
{
  return ComparisonTraits<Container>::template compare<ComparisonPolicy,RightShift>(
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
template<typename ComparisonPolicy, size_t RightShift, typename T1, typename T2>
inline std::string createComparisonHeader(
                const T1& left_value,
                const std::string& left_name,
                T2&& right_value,
                const std::string& right_name,
                const typename ComparisonTraits<T1>::ExtraDataType& extra_data,
                const std::string& name_suffix )
{
  return ComparisonTraits<T1>::template createComparisonHeader<ComparisonPolicy,RightShift>(
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
template<typename ComparisonPolicy, size_t RightShift, typename T1, typename T2>
inline bool compare(
                const T1& left_value,
                const std::string& left_name,
                T2&& right_value,
                const std::string& right_name,
                std::ostream& log,
                const typename ComparisonTraits<T1>::ExtraDataType& extra_data,
                const bool log_comparison_details,
                const std::string& name_suffix )
{
  return ComparisonTraits<T1>::template compare<ComparisonPolicy,RightShift>(
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

// Create a comparison header
template<typename ComparisonPolicy, size_t RightShift, typename Container, typename T>
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
template<typename ComparisonPolicy, size_t RightShift, typename Container, typename T>
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
  return ComparisonTraits<Container>::template compare<ComparisonPolicy,RightShift>(
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

// Create a comparison header
template<typename ComparisonPolicy, size_t RightShift, typename T1, typename T2>
inline std::string createComparisonHeader(
               T1& left_value,
               const std::string& left_name,
               T2&& right_value,
               const std::string& right_name,
               const typename ComparisonTraits<T1>::ExtraDataType& extra_data,
               const std::string& name_suffix )
{
  return ComparisonTraits<T1>::template createComparisonHeader<ComparisonPolicy,RightShift>(
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
template<typename ComparisonPolicy, size_t RightShift, typename T1, typename T2>
inline bool compare(
               T1& left_value,
               const std::string& left_name,
               T2&& right_value,
               const std::string& right_name,
               std::ostream& log,
               const typename ComparisonTraits<T1>::ExtraDataType& extra_data,
               const bool log_comparison_details,
               const std::string& name_suffix )
{
  return ComparisonTraits<T1>::template compare<ComparisonPolicy,RightShift>(
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

// Create a comparison header
template<typename ComparisonPolicy, size_t RightShift, typename Container, typename T>
std::string createComparisonHeader(
         Container& left_value,
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
template<typename ComparisonPolicy, size_t RightShift, typename Container, typename T>
bool compare(
         Container& left_value,
         const std::string& left_name,
         std::initializer_list<T> right_value,
         const std::string& right_name,
         std::ostream& log,
         const typename ComparisonTraits<Container>::ExtraDataType& extra_data,
         const bool log_comparison_details,
         const std::string& name_suffix )
{
  return ComparisonTraits<Container>::template compare<ComparisonPolicy,RightShift>(
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

// Create a comparison header
template<typename ComparisonPolicy, size_t RightShift, typename T>
inline std::string createComparisonHeader(
                 T&& left_value,
                 const std::string& left_name,
                 T&& right_value,
                 const std::string& right_name,
                 const typename ComparisonTraits<T>::ExtraDataType& extra_data,
                 const std::string& name_suffix )
{
  return ComparisonTraits<T>::template createComparisonHeader<ComparisonPolicy,RightShift>(
                                                                  left_value,
                                                                  left_name,
                                                                  false,
                                                                  right_value,
                                                                  right_name,
                                                                  false,
                                                                  name_suffix,
                                                                  extra_data );
}

// Compare two values and print the results (to the desired stream)
template<typename ComparisonPolicy, size_t RightShift, typename T>
inline bool compare(
                 T&& left_value,
                 const std::string& left_name,
                 T&& right_value,
                 const std::string& right_name,
                 std::ostream& log,
                 const typename ComparisonTraits<T>::ExtraDataType& extra_data,
                 const bool log_comparison_details,
                 const std::string& name_suffix )
{
  return ComparisonTraits<T>::template compare<ComparisonPolicy,RightShift>(
                                                        left_value,
                                                        left_name,
                                                        false,
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
