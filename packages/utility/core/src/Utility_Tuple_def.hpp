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

/*! The tuple slice element extractor class
 * \ingroup tuple
 */
template<size_t I, size_t N>
struct TupleSliceElementExtractor
{
  //! Extract the tuple slice element from the full type
  template<size_t head, typename Tuple, typename TupleSlice>
  static inline void extractSlice( const Tuple& tuple, TupleSlice& slice )
  {
    Utility::get<I>( slice ) = Utility::get<head+I>( tuple );

    TupleSliceElementExtractor<I+1,N-1>::extractSlice<head>( tuple, slice );
  }

  //! Extract the tuple slice element from the full type
  template<size_t head, typename Tuple, typename TupleSlice>
  static inline void extractTiedSlice( const Tuple& tuple, TupleSlice& slice )
  {
    Utility::get<I>( slice ) = std::cref( Utility::get<head+I>( tuple ) );

    TupleSliceElementExtractor<I+1,N-1>::extractTiedSlice<head>( tuple, slice );
  }

  //! Extract the tuple slice element from the full type
  template<size_t head, typename Tuple, typename TupleSlice>
  static inline void extractTiedSlice( Tuple& tuple, TupleSlice& slice )
  {
    Utility::get<I>( slice ) = std::ref( Utility::get<head+I>( tuple ) );

    TupleSliceElementExtractor<I+1,N-1>::extractTiedSlice<head>( tuple, slice );
  }
};

/*! Partial specialization of TupleSliceElementExtractor for N == 0
 * \ingroup tuple
 */
template<size_t I>
struct TupleSliceElementExtractor<I,0>
{
  //! Extract the tuple slice element from the full type
  template<size_t head, typename Tuple, typename TupleSlice>
  static inline void extractSlice( const Tuple&, TupleSlice& )
  { /* ... */ }

  //! Extract the tuple slice element from the full type
  template<size_t head, typename Tuple, typename TupleSlice>
  static inline void extractTiedSlice( const Tuple&, TupleSlice& )
  { /* ... */ }

  //! Extract the tuple slice element from the full type
  template<size_t head, typename Tuple, typename TupleSlice>
  static inline void extractTiedSlice( Tuple&, TupleSlice& )
  { /* ... */ }
};

/*! The tuple front slice helper (the default is undefined)
 * \ingroup tuple
 */
template<typename T, typename... Types>
struct TupleFrontSliceHelper
{ /* ... */ };

/*! Specialization of tuple front slice helper for index sequence
 * \ingroup tuple
 */
template<size_t... I, typename... Types>
struct TupleFrontSliceHelper<std::index_sequence<I...>,Types...>
{
protected:

  //! The full tuple type
  typedef std::tuple<Types...> FullTupleType;

public:

  //! The tuple slice type
  typedef std::tuple<typename std::remove_cv<typename Utility::TupleElement<I,FullTupleType>::type>::type...> type;

  //! The tied tuple slice type
  typedef std::tuple<std::reference_wrapper<typename Utility::TupleElement<I,FullTupleType>::type>...> TiedType;

  //! The const tied tuple slice type
  typedef std::tuple<std::reference_wrapper<typename std::add_const<typename Utility::TupleElement<I,FullTupleType>::type>::type>...> ConstTiedType;
};

/*! The tuple slice helper class (the default is undefined)
 * \ingroup tuple
 */
template<size_t offset, size_t size, typename... Types>
struct TupleSliceHelper
{ /* ... */ };

/*! The tuple slice helper class
 *
 * The first type of the parameter pack will be popped off until the
 * offset is 0 (see the specialization for offset == 0).
 * \ingroup tuple
 */
template<size_t offset, size_t size, typename StartT, typename... Types>
struct TupleSliceHelper<offset, size, StartT, Types...>
{
  typedef typename TupleSliceHelper<offset-1,size,Types...>::type type;
  typedef typename TupleSliceHelper<offset-1,size,Types...>::TiedType TiedType;
  typedef typename TupleSliceHelper<offset-1,size,Types...>::ConstTiedType ConstTiedType;

  //! Slice the tuple
  template<size_t head, typename Tuple>
  static inline type slice( const Tuple& tuple )
  {
    return TupleSliceHelper<offset-1,size,Types...>::slice<head+1>( tuple );
  }

  //! Slice and tie the tuple
  template<size_t head, typename Tuple>
  static inline ConstTiedType tiedSlice( const Tuple& tuple )
  {
    return TupleSliceHelper<offset-1,size,Types...>::tiedSlice<head+1>( tuple );
  }

  //! Slice and tie the tuple
  template<size_t head, typename Tuple>
  static inline TiedType tiedSlice( Tuple& tuple )
  {
    return TupleSliceHelper<offset-1,size,Types...>::tiedSlice<head+1>( tuple );
  }
};

/*! Partial specialization of the TupleSliceHelper for offset == 0
 *
 * The tuple slice type will be constructed from the first "size" types of the
 * parameter pack.
 * \ingroup tuple
 */
template<size_t size, typename... Types>
struct TupleSliceHelper<0, size, Types...>
{
  typedef typename TupleFrontSliceHelper<std::make_index_sequence<size>,Types...>::type type;
  typedef typename TupleFrontSliceHelper<std::make_index_sequence<size>,Types...>::TiedType TiedType;
  typedef typename TupleFrontSliceHelper<std::make_index_sequence<size>,Types...>::ConstTiedType ConstTiedType;

  //! Slice the tuple
  template<size_t head, typename Tuple>
  static inline type slice( const Tuple& tuple )
  {
    type tuple_slice;

    TupleSliceElementExtractor<0,sizeof...(Types)>::extractSlice<head>( tuple, tuple_slice );

    return tuple_slice;
  }

  //! Slice and tie the tuple
  template<size_t head, typename Tuple>
  static inline ConstTiedType tiedSlice( const Tuple& tuple )
  {
    ConstTiedType tied_tuple_slice;

    TupleSliceElementExtractor<0,sizeof...(Types)>::extractTiedSlice<head>( tuple, tied_tuple_slice );

    return tied_tuple_slice;
  }

  //! Slice and tie the tuple
  template<size_t head, typename Tuple>
  static inline TiedType tiedSlice( Tuple& tuple )
  {
    TiedType tied_tuple_slice;

    TupleSliceElementExtractor<0,sizeof...(Types)>::extractTiedSlice<head>( tuple, tied_tuple_slice );

    return tied_tuple_slice;
  }
};

/*! The tuple slice helper wrapper (the default is undefined)
 * \ingroup tuple
 */
template<size_t offset, size_t size, typename T>
struct TupleSliceHelperWrapper
{ /* ... */ };

/*! The TupleSliceHelperWrapper partial specialization for std::tuple
 *
 * By specializating with std::tuple we can deduce the parameter pack.
 * \ingroup tuple
 */
template<size_t offset, size_t size, typename... Types>
struct TupleSliceHelperWrapper<offset,size,std::tuple<Types...> > : public TupleSliceHelper<offset,size,Types...>
{ /* ... */ };

/*! The TupleSliceHelperWrapper partial specialization for std::pair
 * \ingroup tuple
 */
template<size_t offset, size_t size, typename T1, typename T2>
struct TupleSliceHelperWrapper<offset,size,std::pair<T1,T2> > : public TupleSliceHelper<offset,size,T1,T2>
{ /* ... */ };
  
} // end Details namespace

// Partial specialization of TupleSlice for all tuple types
template<size_t offset, size_t size, typename TupleType>
struct TupleSlice<offset,size,TupleType,typename std::enable_if<offset < Utility::TupleSize<TupleType>::value-1 && offset+size <= Utility::TupleSize<TupleType>::value && Utility::IsTuple<TupleType>::value>::type> : public Details::TupleSliceHelperWrapper<offset,size,TupleType>
{ /* ... */ };

// Partial specialization of TupleSlice for non-tuple types
template<size_t offset, size_t size, typename T>
struct TupleSlice<offset,size,T,typename std::enable_if<offset == 0 && size == 1 && !Utility::IsTuple<T>::value>::type>
{
  typedef typename std::remove_const<T>::type type;
  typedef std::reference_wrapper<type> TiedType;
  typedef std::reference_wrapper<typename std::add_const<type>::type> ConstTiedType;

  //! Slice the tuple
  template<size_t head, typename Tuple>
  static inline type slice( const Tuple& tuple )
  { return Utility::get<head>( tuple ); }

  //! Slice and tie the tuple
  template<size_t head, typename Tuple>
  static inline ConstTiedType tiedSlice( const Tuple& tuple )
  { return std::cref( Utility::get<head>( tuple ) ); }

  //! Slice and tie the tuple
  template<size_t head, typename Tuple>
  static inline TiedType tiedSlice( Tuple& tuple )
  { return std::ref( Utility::get<head>( tuple ) ); }
};

// Create a slice of a tuple
template<size_t offset, size_t size, typename TupleType>
inline typename TupleSlice<offset,size,TupleType>::type
slice( const TupleType& tuple )
{
  return TupleSlice<offset,size,TupleType>::slice( tuple );
}

// Create a tied slice of a tuple
template<size_t offset, size_t size, typename TupleType>
inline typename TupleSlice<offset,size,TupleType>::ConstTiedType
tiedSlice( const TupleType& tuple )
{
  return TupleSlice<offset,size,TupleType>::tiedSlice( tuple );
}

// Create a tied slice of a tuple
template<size_t offset, size_t size, typename TupleType>
inline typename TupleSlice<offset,size,TupleType>::TiedType
tiedSlice( TupleType& tuple )
{
  return TupleSlice<offset,size,TupleType>::tiedSlice( tuple );
}

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
                     const double extra_data )
  {
    std::ostringstream extended_name_suffix;
    extended_name_suffix << name_suffix << "." << I;

    typedef typename Utility::TupleElement<I,TupleType>::type
      TupleElementIType;

    typedef Details::ExtraDataConversionHelper<typename Utility::ComparisonTraits<TupleElementIType>::ExtraDataType>
      TupleElementIExtraDataConversionHelper;

    const bool local_success = Utility::ComparisonTraits<TupleElementIType>::template compare<ComparePolicy>(
               Utility::get<I>( left_tuple ),
               left_name,
               log_left_name,
               Utility::get<I>( right_tuple ),
               right_name,
               log_right_name,
               extended_name_suffix.str(),
               log,
               true,
               TupleElementIExtraDataConversionHelper::convert( extra_data ) );

    return local_success &&
      TupleMemberCompareHelper<I+1,TupleType>::compareTupleMembers(
                                                                left_tuple,
                                                                left_name,
                                                                log_left_name,
                                                                right_tuple,
                                                                right_name,
                                                                log_right_name,
                                                                name_suffix,
                                                                log,
                                                                extra_data );
  }
};

// The helper class that is used to compare tuple members
template<size_t I, typename TupleType>
struct TupleMemberCompareHelper<I,TupleType,typename std::enable_if<I==TupleSize<TupleType>::value>::type>
{
  template<typename ComparePolicy>
  static inline bool compareTupleMembers( const TupleType& left_tuple,
                                          const std::string& left_name,
                                          const bool log_left_name,
                                          const TupleType& right_tuple,
                                          const std::string& right_name,
                                          const bool log_right_name,
                                          const std::string& name_suffix,
                                          std::ostream& log,
                                          const double extra_data )
  { return true; }
};

} // end Details namespace

// Create a comparison header
template<typename T>
template<typename ComparisonPolicy>
inline std::string ComparisonTraits<T,typename std::enable_if<Utility::IsTuple<T>::value>::type>::createComparisonHeader(
                                       const T& left_value,
                                       const std::string& left_name,
                                       const bool log_left_name,
                                       const T& right_value,
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
template<typename T>
template<typename ComparisonPolicy>
inline bool ComparisonTraits<T,typename std::enable_if<Utility::IsTuple<T>::value>::type>::compare(
                                       const T& left_value,
                                       const std::string& left_name,
                                       const bool log_left_name,
                                       const T& right_value,
                                       const std::string& right_name,
                                       const bool log_right_name,
                                       const std::string& name_suffix,
                                       std::ostream& log,
                                       const bool, 
                                       const ExtraDataType& extra_data )
{
    return Details::TupleMemberCompareHelper<0,T>::template compareTupleMembers<ComparisonPolicy>(
                                                              left_value,
                                                              left_name,
                                                              log_left_name,
                                                              right_value,
                                                              right_name,
                                                              log_right_name,
                                                              name_suffix,
                                                              log,
                                                              extra_data );
}
  
} // end Utility namespace

#endif // end UTILITY_TUPLE_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_Tuple_def.hpp
//---------------------------------------------------------------------------//
