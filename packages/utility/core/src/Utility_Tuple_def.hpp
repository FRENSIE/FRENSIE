//---------------------------------------------------------------------------//
//!
//! \file   Utility_Tuple_def.hpp
//! \author Alex Robinson
//! \brief  Simple struct for storing objects of arbitrary type
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TUPLE_DEF_HPP
#define UTILITY_TUPLE_DEF_HPP

// std Lib Includes
#include <functional>
#include <utility>

// FRENSIE Includes
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace Utility{
  
namespace Details{

//! The tuple output stream helper class 
template<size_t I, typename TupleType, typename Enable = void>
struct TupleStreamHelper
{
  static inline void toStream( std::ostream& os, const TupleType& tuple )
  { 
    // Insert the tuple element
    Utility::toStream( os, std::get<I>( tuple ) );
    
    os << ", ";

    // Insert the remaining tuple elements
    TupleStreamHelper<I+1,TupleType>::toStream( os, tuple );
  }

  static inline void fromStream( std::istream& is, TupleType& tuple )
  {
    // Extract the tuple element
    try{
      Utility::fromStream( is, std::get<I>( tuple ), ",}" );
    }
    EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                             "Tuple element " << I << " was not successfully "
                             "extracted from the input stream!" );

    // Position the stream at the start of the next element (or end)
    try{
      Utility::moveInputStreamToNextElement( is, ',', '}' );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                Utility::StringConversionException,
                                "Could not move the input stream to the next "
                                "element (last tuple element successfully "
                                "extracted = " << I << ")!" );

    // Extract the remaining tuple elements
    TupleStreamHelper<I+1,TupleType>::fromStream( is, tuple );
  }
};

/*! \brief The tuple output stream helper class 
 * (specialization for I == Utility::TupleSize-1, which is for the last element)
 */
template<size_t I, typename TupleType>
struct TupleStreamHelper<I, TupleType, typename std::enable_if<I==Utility::TupleSize<TupleType>::value-1>::type>
{
  static inline void toStream( std::ostream& os, const TupleType& tuple )
  {
    // Insert the tuple element
    Utility::toStream( os, std::get<I>( tuple ) );
  }

  static inline void fromStream( std::istream& is, TupleType& tuple )
  {
    // Extract the tuple element
    try{
      Utility::fromStream( is, std::get<I>( tuple ), ",}" );
    }
    EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                             "Tuple element " << I << " was not "
                             "successfully extracted from the input stream!" );

    // Position the stream at the start of the next element (or end)
    bool at_end;
    try{
      at_end = Utility::moveInputStreamToNextElement( is, ',', '}' );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                Utility::StringConversionException,
                                "Could not move the input stream to the next "
                                "element (last tuple element successfully "
                                "extracted = " << I << ")!" );

    TEST_FOR_EXCEPTION( !at_end,
                        Utility::StringConversionException,
                        "Finished extracting tuple before the end of the "
                        "stream was reached (this likely means that the "
                        "string is not compatible with the tuple type)!" );
  }
};

/*! \brief The tuple output stream helper class
 * (specialization for I == Utility::TupleSize, which is past the last element)
 */
template<size_t I, typename TupleType>
struct TupleStreamHelper<I, TupleType, typename std::enable_if<I==Utility::TupleSize<TupleType>::value>::type>
{
  static inline void toStream( std::ostream& os, const TupleType& tuple )
  { /* ... */ }

  static inline void fromStream( std::istream& is, TupleType& tuple )
  { /* ... */ }
};

} // end Details namespace

// Convert the tuple to a string
template<typename T>
inline std::string ToStringTraits<T,typename std::enable_if<Utility::IsTuple<T>::value>::type>::toString(
                                            const T& tuple )
{
  std::ostringstream oss;
  
  ToStringTraits<T>::toStream( oss, tuple );
  
  return oss.str();
}

// Place the tuple in a stream
template<typename T>
inline void ToStringTraits<T,typename std::enable_if<Utility::IsTuple<T>::value>::type>::toStream(
                                                              std::ostream& os,
                                                              const T& tuple )
{
  os << '{';
  Details::TupleStreamHelper<0,T>::toStream( os, tuple );
  os << '}';
}


// Convert the string to an object of type T
template<typename T>
inline auto FromStringTraits<T,typename std::enable_if<Utility::IsTuple<T>::value>::type>::fromString(
                                     const std::string& obj_rep ) -> ReturnType
{
  std::istringstream iss( obj_rep );

  ReturnType obj;

  FromStringTraits<ReturnType>::fromStream( iss, obj );

  return obj;
}

// Extract the object from a stream
template<typename T>
inline void FromStringTraits<T,typename std::enable_if<Utility::IsTuple<T>::value>::type>::fromStream(
                                                     std::istream& is,
                                                     T& obj,
                                                     const std::string& )
{ 
  try{
    // Initialize the input stream
    Utility::initializeInputStream( is, '{' );
    
    Details::TupleStreamHelper<0,T>::fromStream( is, obj );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                              Utility::StringConversionException,
                              "Could not extract a tuple from the stream!" );
}

namespace Details{

//! The helper class for converting extra data to the desired type
template<typename T, typename Enabled = void>
struct ExtraDataConversionHelper
{
  //! Convert the extra data to the desired type
  static inline T convert( const double extra_data )
  { return static_cast<T>( extra_data ); }
};

//! The ExtraDataConversionHelper specialization for std::string
template<>
struct ExtraDataConversionHelper<std::string>
{
  //! Convert the extra data to the desired type
  static inline std::string convert( const double extra_data )
  { return Utility::toString( extra_data ); }
};

//! The ExtraDataConversionHelper partial specialization for non-arithmetic types
template<typename T>
struct ExtraDataConversionHelper<T,typename std::enable_if<!std::is_arithmetic<T>::value>::type>
{
  //! Convert the extra data to the desired type
  static inline T convert( const double extra_data )
  { return T(); }
};

//! The helper class that is used to compare tuple members
template<size_t I, typename TupleType, typename Enabled = void>
struct TupleMemberCompareHelper
{
  //! Compare tuple members
  template<typename ComparePolicy, size_t RightShift>
  static inline bool compareTupleMembers(
                     const TupleType& left_tuple,
                     const std::string& left_name,
                     const bool log_left_name,
                     const TupleType& right_tuple,
                     const std::string& right_name,
                     const bool log_right_name,
                     const std::string& name_suffix,
                     std::ostream& log,
                     const bool log_comparison_details,
                     const double extra_data )
  {
    std::ostringstream detailed_left_name;

    detailed_left_name << "Utility::get<" << I << ">("
                       << left_name << name_suffix << ")";

    std::ostringstream detailed_right_name;

    detailed_right_name << "Utility::get<" << I << ">("
                        << right_name << name_suffix << ")";

    typedef typename Utility::TupleElement<I,TupleType>::type
      TupleElementIType;

    typedef Details::ExtraDataConversionHelper<typename Utility::ComparisonTraits<TupleElementIType>::ExtraDataType>
      TupleElementIExtraDataConversionHelper;

    const bool local_success =
      Utility::ComparisonTraits<TupleElementIType>::template compare<ComparePolicy,RightShift>(
          Utility::get<I>( left_tuple ),
          detailed_left_name.str(),
          log_left_name,
          Utility::get<I>( right_tuple ),
          detailed_right_name.str(),
          log_right_name,
          "",
          log,
          log_comparison_details,
          TupleElementIExtraDataConversionHelper::convert( extra_data ) );
    
    const bool next_local_success =
      TupleMemberCompareHelper<I+1,TupleType>::template compareTupleMembers<ComparePolicy,RightShift>(
                                                        left_tuple,
                                                        left_name,
                                                        log_left_name,
                                                        right_tuple,
                                                        right_name,
                                                        log_right_name,
                                                        name_suffix,
                                                        log,
                                                        log_comparison_details,
                                                        extra_data );
    return (local_success && next_local_success);
  }
};

// The helper class that is used to compare tuple members
template<size_t I, typename TupleType>
struct TupleMemberCompareHelper<I,TupleType,typename std::enable_if<I==TupleSize<TupleType>::value>::type>
{
  template<typename ComparePolicy, size_t RightShift>
  static inline bool compareTupleMembers( const TupleType&,
                                          const std::string&,
                                          const bool,
                                          const TupleType&,
                                          const std::string&,
                                          const bool,
                                          const std::string&,
                                          std::ostream&,
                                          const bool,
                                          const double )
  { return true; }
};

/*! The tuple comparison policy helper
 * \ingroup tuple
 * \ingroup comparison_traits
 */
template<typename Policy, typename TupleType, typename Enabled = void>
struct TupleComparePolicyHelper
{
private:

  // Typedef for this type
  typedef TupleComparePolicyHelper<Policy,TupleType> ThisType;

public:
  
  //! Create the comparison header
  template<size_t RightShift, typename ExtraDataType>
  static inline std::string createComparisonHeader(
                                              const TupleType& left_value,
                                              const std::string& left_name,
                                              const bool log_left_name,
                                              const TupleType& right_value,
                                              const std::string& right_name,
                                              const bool log_right_name,
                                              const std::string& name_suffix,
                                              const ExtraDataType& extra_data =
                                              ExtraDataType() )
  {
    return ThisType::template createComparisonHeader<RightShift>(
                                       left_value, left_name, log_left_name,
                                       right_value, right_name, log_right_name,
                                       name_suffix, TupleType() );
  }

  //! Create the comparison header
  template<size_t RightShift>
  static inline std::string createComparisonHeader(
                                              const TupleType& left_value,
                                              const std::string& left_name,
                                              const bool log_left_name,
                                              const TupleType& right_value,
                                              const std::string& right_name,
                                              const bool log_right_name,
                                              const std::string& name_suffix,
                                              const TupleType& extra_data =
                                              TupleType() )
  {
    return Details::createComparisonHeaderImpl<Policy,RightShift>(
                                       left_value, left_name, log_left_name,
                                       right_value, right_name, log_right_name,
                                       name_suffix, extra_data );
  }

  //! Compare two tuples
  template<size_t RightShift, typename ExtraDataType>
  static inline bool compare(
                            const TupleType& left_value,
                            const std::string& left_name,
                            const bool log_left_name,
                            const TupleType& right_value,
                            const std::string& right_name,
                            const bool log_right_name,
                            const std::string& name_suffix,
                            std::ostream& log,
                            const bool log_comparison_details = false,
                            const ExtraDataType& = ExtraDataType() )
  {
    return Details::compareImpl<Policy,RightShift>(
                                      left_value, left_name, log_left_name,
                                      right_value, right_name, log_right_name,
                                      name_suffix, log, log_comparison_details,
                                      TupleType() );
  }
};

/*! \brief Specialization of TupleComparePolicyHelper for 
 * Utility::EqualityComparisonPolicy, Utility::CloseComparisonPolicy and
 * the Utility::RelativeErrorComparisonPolicy (tuple size > 1 only).
 * 
 * If the Utility::EqualityComparisonPolicy, Utility::CloseComparisonPolicy or
 * the Utility::RelativeErrorComparisonPolicy are used extra details regarding
 * the comparison of each tuple member comparison will be added to the log.
 * \ingroup tuple
 * \ingroup comparison_traits
 */
template<typename Policy, typename TupleType>
struct TupleComparePolicyHelper<Policy,TupleType,typename std::enable_if<(std::is_same<Policy,Utility::EqualityComparisonPolicy>::value || std::is_same<Policy,Utility::CloseComparisonPolicy>::value || std::is_same<Policy,Utility::RelativeErrorComparisonPolicy>::value) && (Utility::TupleSize<TupleType>::value>1)>::type>
{
private:

  // Typedef for this type
  typedef TupleComparePolicyHelper<Policy,TupleType,typename std::enable_if<(std::is_same<Policy,Utility::EqualityComparisonPolicy>::value || std::is_same<Policy,Utility::CloseComparisonPolicy>::value || std::is_same<Policy,Utility::RelativeErrorComparisonPolicy>::value) && (Utility::TupleSize<TupleType>::value>1)>::type> ThisType;

public:
  
  //! Create the comparison header
  template<size_t RightShift, typename ExtraDataType>
  static inline std::string createComparisonHeader(
                                              const TupleType& left_value,
                                              const std::string& left_name,
                                              const bool log_left_name,
                                              const TupleType& right_value,
                                              const std::string& right_name,
                                              const bool log_right_name,
                                              const std::string& name_suffix,
                                              const ExtraDataType& =
                                              ExtraDataType() )
  {
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
        << "for every tuple member i, "
        << "Utility::get<i>(" << detailed_left_name << ") "
        << Policy::template getOperatorName<TupleType>()
        << " Utility::get<i>(" << detailed_right_name << "): ";

    return oss.str();
  }

  //! Compare two tuples
  template<size_t RightShift, typename ExtraDataType>
  static inline bool compare(
                            const TupleType& left_value,
                            const std::string& left_name,
                            const bool log_left_name,
                            const TupleType& right_value,
                            const std::string& right_name,
                            const bool log_right_name,
                            const std::string& name_suffix,
                            std::ostream& log,
                            const bool log_comparison_details = false,
                            const ExtraDataType& extra_data = ExtraDataType() )
  {
    if( log_comparison_details )
    {
      log << ThisType::template createComparisonHeader<RightShift>(
                                       left_value, left_name, log_left_name,
                                       right_value, right_name, log_right_name,
                                       name_suffix, extra_data );
    }

    std::ostringstream local_log;

    bool success = TupleMemberCompareHelper<0,TupleType>::template compareTupleMembers<Policy,Details::incrementRightShift(RightShift)>(
                                left_value, left_name, log_left_name,
                                right_value, right_name, log_right_name,
                                name_suffix, local_log, log_comparison_details,
                                extra_data );

    if( log_comparison_details )
    {
      Utility::reportComparisonPassFail( success, log );
      log << local_log.str();
    }

    return success;
  }
};

} // end Details namespace

// Create a comparison header
template<typename... Types>
template<typename ComparisonPolicy, size_t RightShift>
inline std::string ComparisonTraits<std::tuple<Types...>,typename std::enable_if<Utility::TupleSize<std::tuple<Types...> >::value!=1>::type>::createComparisonHeader(
                                       const std::tuple<Types...>& left_value,
                                       const std::string& left_name,
                                       const bool log_left_name,
                                       const std::tuple<Types...>& right_value,
                                       const std::string& right_name,
                                       const bool log_right_name,
                                       const std::string& name_suffix,
                                       const ExtraDataType& extra_data  )
{
  return Details::TupleComparePolicyHelper<ComparisonPolicy,std::tuple<Types...> >::template createComparisonHeader<RightShift>(
                                       left_value, left_name, log_left_name,
                                       right_value, right_name, log_right_name,
                                       name_suffix, extra_data );
}

// Compare two tuples
template<typename... Types>
template<typename ComparisonPolicy, size_t RightShift>
inline bool ComparisonTraits<std::tuple<Types...>,typename std::enable_if<Utility::TupleSize<std::tuple<Types...> >::value!=1>::type>::compare(
                                       const std::tuple<Types...>& left_value,
                                       const std::string& left_name,
                                       const bool log_left_name,
                                       const std::tuple<Types...>& right_value,
                                       const std::string& right_name,
                                       const bool log_right_name,
                                       const std::string& name_suffix,
                                       std::ostream& log,
                                       const bool log_comparison_details, 
                                       const ExtraDataType& extra_data )
{
  return Details::TupleComparePolicyHelper<ComparisonPolicy,std::tuple<Types...> >::template compare<RightShift>(
                                      left_value, left_name, log_left_name,
                                      right_value, right_name, log_right_name,
                                      name_suffix, log, log_comparison_details,
                                      extra_data );
}

// Create a comparison header
template<typename T1, typename T2>
template<typename ComparisonPolicy, size_t RightShift>
inline std::string ComparisonTraits<std::pair<T1,T2> >::createComparisonHeader(
                                       const std::pair<T1,T2>& left_value,
                                       const std::string& left_name,
                                       const bool log_left_name,
                                       const std::pair<T1,T2>& right_value,
                                       const std::string& right_name,
                                       const bool log_right_name,
                                       const std::string& name_suffix,
                                       const ExtraDataType& extra_data  )
{
  return Details::TupleComparePolicyHelper<ComparisonPolicy,std::pair<T1,T2> >::template createComparisonHeader<RightShift>(
                                       left_value, left_name, log_left_name,
                                       right_value, right_name, log_right_name,
                                       name_suffix, extra_data );
}

// Compare two tuples
template<typename T1, typename T2>
template<typename ComparisonPolicy, size_t RightShift>
inline bool ComparisonTraits<std::pair<T1,T2> >::compare(
                                       const std::pair<T1,T2>& left_value,
                                       const std::string& left_name,
                                       const bool log_left_name,
                                       const std::pair<T1,T2>& right_value,
                                       const std::string& right_name,
                                       const bool log_right_name,
                                       const std::string& name_suffix,
                                       std::ostream& log,
                                       const bool log_comparison_details, 
                                       const ExtraDataType& extra_data )
{
  return Details::TupleComparePolicyHelper<ComparisonPolicy,std::pair<T1,T2> >::template compare<RightShift>(
                                      left_value, left_name, log_left_name,
                                      right_value, right_name, log_right_name,
                                      name_suffix, log, log_comparison_details,
                                      extra_data );
}
  
} // end Utility namespace

#endif // end UTILITY_TUPLE_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_Tuple_def.hpp
//---------------------------------------------------------------------------//
