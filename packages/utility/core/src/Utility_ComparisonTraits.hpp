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

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_ComparisonTraitsDecl.hpp"
#include "Utility_ComparisonPolicy.hpp"

namespace Utility{

// Create a comparison header
template<typename T, typename Enabled>
template<typename ComparisonPolicy>
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
  std::string comparison_header =
    ComparisonPolicy::createComparisonDetails( left_name,
                                               log_left_name,
                                               left_value,
                                               right_name,
                                               log_right_name,
                                               right_value,
                                               name_suffix,
                                               extra_data );
  comparison_header += ": ";

  return comparison_header;
}

// Compare two values of a type (default)
template<typename T, typename Enabled>
template<typename ComparisonPolicy>
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
                        const typename QuantityTraits<T>::RawType& extra_data )
{
  if( log_comparison_details )
  {
    log << ComparisonTraits<T,Enabled>::createComparisonHeader( left_value,
                                                                left_name,
                                                                log_left_name,
                                                                right_value,
                                                                right_name,
                                                                name_suffix,
                                                                extra_data )
        << std::endl;
  }

  // Conduct the comparison
  const bool success =
    ComparisonPolicy::compare( left_value, right_value, extra_data );

  if( log_comparison_details )
    Utility::reportComparisonPassFail( success, log );

  return success;
}


/*! The specialization of the Utility::ComparisonTraits for const types.
 * \ingroup comparison_traits
 */
template<typename T>
struct ComparisonTraits<T,typename std::enable_if<std::is_const<T>::value && !std::is_volatile<T>::value>::type> : public ComparisonTraits<typename std::remove_const<T>::type>
{ /* ... */ };

/*! The specialization of the Utility::ComparisonTraits for volatile types.
 * \ingroup comparison_traits
 */
template<typename T>
struct ComparisonTraits<T,typename std::enable_if<!std::is_const<T>::value && std::is_volatile<T>::value>::type> : public ComparisonTraits<typename std::remove_volatile<T>::type>
{ /* ... */ };

/*! \brief The specialization of the Utility::ComparisonTraits for const
 * volatile types.
 * \ingroup comparison_traits
 */
template<typename T>
struct ComparisonTraits<T,typename std::enable_if<std::is_const<T>::value && std::is_volatile<T>::value>::type> : public ComparisonTraits<typename std::remove_cv<T>::type>
{ /* ... */ };

namespace Details{

//! The comparison traits helper for stl compliant sequence containers
template<template<typename,typename...> class STLCompliantSequenceContainer,
         typename T>
struct ComparisonTraitsSequenceContainerHelper
{
  //! The extra data type (usually a comparison tolerance)
  typedef typename QuantityTraits<T>::RawType ExtraDataType;

  //! Create a comparison header
  template<typename ComparisonPolicy>
  static inline std::string createComparisonHeader(
                            const T& left_value,
                            const std::string& left_name,
                            const bool log_left_name,
                            const T& right_value,
                            const std::string& right_name,
                            const bool log_right_name,
                            const std::string& name_suffix,
                            const ExtraDataType& extra_data = ExtraDataType() )
  {
    std::string logged_left_name;

    if( log_left_name )
    {
      logged_left_name = left_name;
    
      if( !name_suffix.empty() )
        logged_left_name += name_suffix;
    }
    else
      logged_left_name = Utility::toString( left_value );

    std::string logged_right_name;

    if( log_right_name )
    {
      logged_right_name = right_name;

      if( !name_suffix.empty() )
        logged_right_name += name_suffix;
    }
    else
      logged_right_name = Utility::toString( right_value );
    
    std::ostringstream oss;

    oss << "size(" << logged_left_name << ") == size(" << logged_right_name
        << ") && for every index i, "
        << logged_left_name << "[i]" << ComparisonPolicy::getOperatorName()
        << logged_right_name << "[i]: ";

    return oss.str();
  }

  //! Compare two sequence containers
  template<typename ComparisonPolicy>
  static inline bool compare(
                          const STLCompliantSequenceContainer<T>& left_value,
                          const std::string& left_name,
                          const bool log_left_name,
                          const STLCompliantSequenceContainer<T>& right_value,
                          const std::string& right_name,
                          const bool log_right_name,
                          const std::string& name_suffix,
                          std::ostream& log,
                          const bool = false,
                          const ExtraDataType& extra_data = ExtraDataType() )
  {
    std::ostringstream detailed_name_suffix;
    detailed_name_suffix << name_suffix << " size";

    bool success =
      Utility::ComparisonTraits<size_t>::compare<ComparisonPolicy>(
                       std::distance( left_value.begin(), left_value.end() ),
                       left_name,
                       log_left_name,
                       std::distance( right_value.begin(), right_value.end() ),
                       right_name,
                       log_right_name,
                       detailed_name_suffix.str(),
                       log,
                       true,
                       extra_data );

    // Only test the individual container elements if the sizes are the same
    if( success )
    {
      typename STLCompliantSequenceContainer<T>::const_iterator left_it, left_end;
      left_it = left_value.begin();
      left_end = left_value.end();

      typename STLCompliantSequenceContainer<T>::const_iterator right_it, right_end;
      right_it = right_value.begin();
      right_end = right_value.end();

      size_t index = 0;
      
      while( left_it != left_end )
      {
        detailed_name_suffix.str( "" );
        detailed_name_suffix.clear();

        detailed_name_suffix << name_suffix << "[" << index << "]";
          
        bool local_success =
          Utility::ComparisonTraits<T>::compare( *left_it,
                                                 left_name,
                                                 log_left_name,
                                                 *right_it,
                                                 right_name,
                                                 log_right_name,
                                                 detailed_name_suffix.str(),
                                                 log,
                                                 true,
                                                 extra_data );
        if( !local_success )
          success = false;

        ++left_it;
        ++right_it;
        ++index;
      }
    }

    return success;
  }
};

//! The comparison traits helper for stl compliant associative containers
template<template<typename...> class STLCompliantAssociativeContainer,
         typename... Types>
struct ComparisonTraitsAssociativeContainerHelper
{
  //! The extra data type (usually a comparison tolerance)
  typedef typename STLCompliantAssociativeContainer<Types...>::value_type ExtraDataType;

  //! Create a comparison header
  template<typename DummyPolicy>
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

  //! Compare two associative containers
  template<typename DummyPolicy>
  static inline bool compare(
                 const STLCompliantAssociativeContainer<Types...>& left_value,
                 const std::string& left_name,
                 const bool log_left_name,
                 const STLCompliantAssociativeContainer<Types...>& right_value,
                 const std::string& right_name,
                 const bool log_right_name,
                 const std::string& name_suffix,
                 std::ostream& log,
                 const bool = false,
                 const ExtraDataType& = ExtraDataType() )
  {
    std::ostringstream detailed_name_suffix;
    detailed_name_suffix << name_suffix << " size";

    bool success =
      Utility::ComparisonTraits<size_t>::compare<EqualityComparisonPolicy>(
                       std::distance( left_value.begin(), left_value.end() ),
                       left_name,
                       log_left_name,
                       std::distance( right_value.begin(), right_value.end() ),
                       right_name,
                       log_right_name,
                       detailed_name_suffix.str(),
                       log,
                       true );

    // Only test the individual container elements if the sizes are the same
    if( success )
    {
      typename STLCompliantAssociativeContainer<Types...>::const_iterator left_it, left_end;
      left_it = left_value.begin();
      left_end = left_value.end();
      
      while( left_it != left_end )
      {
        detailed_name_suffix.str( "" );
        detailed_name_suffix.clear();

        detailed_name_suffix << name_suffix << ".contains("
                             << Utility::toString( *left_it ) << ")";
          
        bool local_success =
          Utility::ComparisonTraits<bool>::compare<EqualityComparisonPolicy>(
               true,
               left_name,
               log_left_name,
               std::find( right_value.begin(), right_value.end(), *left_it ) !=
               right_value.end(),
               right_name,
               log_right_name,
               detailed_name_suffix.str(),
               log,
               true );
        
        if( !local_success )
          success = false;

        ++left_it;
      }
    }

    return success;
  }
};
  
} // end Details namespace

// Create a comparison header
template<typename ComparisonPolicy, typename T>
inline std::string createComparisonHeader(
                 const T& left_value,
                 const std::string& left_name,
                 const T& right_value,
                 const std::string& right_name,
                 const typename ComparisonTraits<T>::ExtraDataType& extra_data,
                 const std::string& name_suffix )
{
  return ComparisonTraits<T>::template createComparisonHeader<ComparisonPolicy>(
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
template<typename ComparisonPolicy, typename T>
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
  return ComparisonTraits<T>::template compare<ComparisonPolicy>(
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
template<typename ComparisonPolicy, typename T1, typename T2>
inline std::string createComparisonHeader(
                T1&& left_value,
                const std::string& left_name,
                const T2& right_value,
                const std::string& right_name,
                const typename ComparisonTraits<T2>::ExtraDataType& extra_data,
                const std::string& name_suffix )
{
  return ComparisonTraits<T2>::template createComparisonHeader<ComparisonPolicy>(
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
template<typename ComparisonPolicy, typename T1, typename T2>
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
  return ComparisonTraits<T2>::template compare<ComparisonPolicy>(
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
template<typename ComparisonPolicy, typename T1, typename T2>
inline std::string createComparisonHeader(
                const T1& left_value,
                const std::string& left_name,
                T2&& right_value,
                const std::string& right_name,
                const typename ComparisonTraits<T1>::ExtraDataType& extra_data,
                const std::string& name_suffix )
{
  return ComparisonTraits<T1>::template createComparisonHeader<ComparisonPolicy>(
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
template<typename ComparisonPolicy, typename T1, typename T2>
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
  return ComparisonTraits<T1>::template compare<ComparisonPolicy>(
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
template<typename ComparisonPolicy, typename T>
inline std::string createComparisonHeader(
                 T&& left_value,
                 const std::string& left_name,
                 T&& right_value,
                 const std::string& right_name,
                 const typename ComparisonTraits<T>::ExtraDataType& extra_data,
                 const std::string& name_suffix )
{
  return ComparisonTraits<T>::template createComparisonHeader<ComparisonPolicy>(
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
template<typename ComparisonPolicy, typename T>
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
  return ComparisonTraits<T>::template compare<ComparisonPolicy>(
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
