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
  template<typename ComparePolicy>
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
    std::ostringstream extended_name_suffix;

    if( log_comparison_details )
      extended_name_suffix << name_suffix << "." << I;

    typedef typename Utility::TupleElement<I,TupleType>::type
      TupleElementIType;

    typedef Details::ExtraDataConversionHelper<typename Utility::ComparisonTraits<TupleElementIType>::ExtraDataType>
      TupleElementIExtraDataConversionHelper;

    const bool local_success =
      Utility::ComparisonTraits<TupleElementIType>::template compare<ComparePolicy>(
          Utility::get<I>( left_tuple ),
          left_name,
          log_left_name,
          Utility::get<I>( right_tuple ),
          right_name,
          log_right_name,
          (log_comparison_details ? extended_name_suffix.str() : name_suffix ),
          log,
          log_comparison_details,
          TupleElementIExtraDataConversionHelper::convert( extra_data ) );
    
    const bool next_local_success =
      TupleMemberCompareHelper<I+1,TupleType>::template compareTupleMembers<ComparePolicy>(
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
  template<typename ComparePolicy>
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

} // end Details namespace

// Create a comparison header
template<typename... Types>
template<typename ComparisonPolicy>
inline std::string ComparisonTraits<std::tuple<Types...> >::createComparisonHeader(
                                       const std::tuple<Types...>& left_value,
                                       const std::string& left_name,
                                       const bool log_left_name,
                                       const std::tuple<Types...>& right_value,
                                       const std::string& right_name,
                                       const bool log_right_name,
                                       const std::string& name_suffix,
                                       const ExtraDataType& extra_data  )
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

// Compare two tuples
template<typename... Types>
template<typename ComparisonPolicy>
inline bool ComparisonTraits<std::tuple<Types...> >::compare(
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
  return Details::TupleMemberCompareHelper<0,std::tuple<Types...> >::template compareTupleMembers<ComparisonPolicy>(
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

// Create a comparison header
template<typename ComparisonPolicy>
inline std::string ComparisonTraits<std::tuple<> >::createComparisonHeader(
                                              const std::tuple<>& left_value,
                                              const std::string& left_name,
                                              const bool log_left_name,
                                              const std::tuple<>& right_value,
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
                                               std::tuple<>() );
  comparison_header += ": ";

  return comparison_header;
}

// Compare two tuples
template<typename ComparisonPolicy>
inline bool ComparisonTraits<std::tuple<> >::compare(
                                              const std::tuple<>& left_value,
                                              const std::string& left_name,
                                              const bool log_left_name,
                                              const std::tuple<>& right_value,
                                              const std::string& right_name,
                                              const bool log_right_name,
                                              const std::string& name_suffix,
                                              std::ostream& log,
                                              const bool log_comparison_header,
                                              const ExtraDataType& extra_data )
{
  if( log_comparison_header )
  {
    log << ComparisonTraits<std::tuple<> >::template createComparisonHeader<ComparisonPolicy>(
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
  const bool success = ComparisonPolicy::compare( left_value, right_value );

  if( log_comparison_header )
    Utility::reportComparisonPassFail( success, log );

  return success;
}
  
} // end Utility namespace

#endif // end UTILITY_TUPLE_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_Tuple_def.hpp
//---------------------------------------------------------------------------//
