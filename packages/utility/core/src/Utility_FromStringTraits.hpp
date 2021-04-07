//---------------------------------------------------------------------------//
//!
//! \file   Utility_FromStringTraits.hpp
//! \author Alex Robinson
//! \brief  FromStringTraits class specialization declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_FROM_STRING_TRAITS_HPP
#define UTILITY_FROM_STRING_TRAITS_HPP

// Std Lib Includes
#include <sstream>
#include <iterator>
#include <limits>
#include <complex>
#include <vector>

// Boost Includes
#include <boost/algorithm/string.hpp>
#include <boost/type_traits/promote.hpp>
#include <boost/units/quantity.hpp>

// FRENSIE Includes
#include "Utility_FromStringTraitsDecl.hpp"
#include "Utility_LogRecordType.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace Utility{

namespace Details{

// 9 = tab (\t), 10 = new line (\n), 32 = white space
extern const std::string white_space_delims;

} // end Details namespace

/*! Partial specialization for reference type
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<T&> : public FromStringTraits<T>
{ /* ... */ };

/*! Specialization of FromStringTraits for std::string
 * \ingroup from_string_traits
 */
template<>
struct FromStringTraits<std::string>
{
  //! The type that a string will be converted to
  typedef std::string ReturnType;

  //! Return the string
  static inline ReturnType fromString( const std::string& obj_rep )
  { return obj_rep; }

  //! Extract the string from the stream
  static inline void fromStream( std::istream& is,
                                 std::string& obj,
                                 const std::string& delims = std::string() )
  {
    obj.clear();

    // Extract an element string
    if( delims.find( "," ) < delims.size() &&
        delims.find( "}" ) < delims.size() )
    {
      obj = FromStringTraits<std::string>::extractElementString( is, delims );
    }
    else
      obj = FromStringTraits<std::string>::extractString( is, delims );
  }

private:

  // Extract a string
  static std::string extractString( std::istream& is,
                                    const std::string& delims );

  // Extract a string element
  static std::string extractElementString( std::istream& is,
                                           const std::string& delims );
};

namespace Details{

/*! The FromStringTraits enum helper
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraitsEnumHelper
{
  //! The type that a string will be converted to
  typedef T ReturnType;

protected:

  //! This type (base type)
  typedef FromStringTraitsEnumHelper<T> BaseType;

  //! Extract enum value name from stream
  static inline std::string extractEnumValueNameFromStream(
                                                     std::istream& is,
                                                     std::string& delim )
  {
    std::string enum_value_name;

    if( delim.size() == 0 )
      delim = Details::white_space_delims;

    // Handle concurrent deliminators
    while( enum_value_name.size() == 0 )
      Utility::fromStream( is, enum_value_name, delim );

    return enum_value_name;
  }

  //! Default implementation of fromStream
  template<typename FromStringFunction>
  static inline void fromStreamImpl( std::istream& is,
                                     T& obj,
                                     const std::string& delim,
                                     FromStringFunction fromStringFunc )
  {
    std::string delim_copy = delim;

    std::string obj_rep =
      BaseType::extractEnumValueNameFromStream( is, delim_copy );

    obj = fromStringFunc( obj_rep );
  }
};

} // end Details namespace

/*! Specialization of FromStringTraits for Utility::LogRecordType
 *
 * This specialization is not specified with the LogRecordType enum because
 * many of the other FromStringTraits specializations indirectly depend on the
 * enum (e.g. through the exception test macros). Declaring this specialization
 * here prevents any circular dependencies.
 * \ingroup from_string_traits
 */
template<>
struct FromStringTraits<LogRecordType> : public Details::FromStringTraitsEnumHelper<LogRecordType>
{
  //! Convert the string to a Utility::LogRecordType
  static ReturnType fromString( const std::string& obj_rep );

  //! Extract the object from a stream
  static void fromStream( std::istream& is,
                          LogRecordType& obj,
                          const std::string& delim = std::string() );
};

namespace Details{

template<typename T>
struct FromStringTraitsSingleByteIntegralTypeHelper;

/*! FromStringTraits helper class for multiple byte integral types (e.g. int)
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraitsIntegralTypeHelper
{
  //! The type that a string will be converted to
  typedef T ReturnType;

protected:

  //! Convert the string to an object of type T
  static inline ReturnType fromStringImpl( const std::string& obj_rep,
                                           const std::string& valid_chars )
  {
    std::string trimmed_obj_rep = boost::algorithm::trim_copy( obj_rep );

    TEST_FOR_EXCEPTION( trimmed_obj_rep.size() == 0,
                        Utility::StringConversionException,
                        "Cannot convert an empty string to an integral "
                        "type!" );

    // Check for unsupported characters
    TEST_FOR_EXCEPTION( trimmed_obj_rep.find_first_not_of( valid_chars ) <
                        trimmed_obj_rep.size(),
                        Utility::StringConversionException,
                        "Unable to convert the string to an integral "
                        "type because unsupported characters are present (\""
                        << trimmed_obj_rep[trimmed_obj_rep.find_first_not_of(valid_chars)] <<
                        "\")!" );

    std::istringstream iss( trimmed_obj_rep );

    ReturnType obj;

    iss >> obj;

    // An error has occurred
    if( !iss )
    {
      // Check for overflow error
      if( obj == std::numeric_limits<T>::max() )
      {
        THROW_EXCEPTION( Utility::StringConversionException,
                         "Unable to convert the string to an integral type "
                         "because of overflow (\"" << trimmed_obj_rep <<
                         "\" > max==\""
                         << std::numeric_limits<T>::max() << "\")!" );
      }
      // Check for underflow error
      else if( obj == std::numeric_limits<T>::min() )
      {
        THROW_EXCEPTION( Utility::StringConversionException,
                         "Unable to convert the string to an integral type "
                         "because of underflow (\"" << trimmed_obj_rep <<
                         "\" < min==\""
                         << std::numeric_limits<T>::min() << "\")!" );
      }
      // Generic error
      else
      {
        THROW_EXCEPTION( Utility::StringConversionException,
                         "Unable to convert the string to an integral type "
                         "because an error occurred in the string stream!" );
      }
    }
    // Unused characters are present
    else if( !iss.eof() )
    {
      std::string unused_characters;
      iss >> unused_characters;

      THROW_EXCEPTION( Utility::StringConversionException,
                       "Unused characters (\"" << unused_characters << "\") "
                       "in string after conversion to integral type!" );
    }

    return obj;
  }

  //! Extract the object from a stream
  static inline void fromStreamImpl( std::istream& is,
                                     T& obj,
                                     const std::string& valid_chars,
                                     const std::string& delim )
  {
    if( delim.size() > 0 )
    {
      std::string obj_rep;

      Utility::fromStream( is, obj_rep, delim );

      obj = FromStringTraitsIntegralTypeHelper<T>::fromStringImpl( obj_rep, valid_chars );
    }
    // Use white space characters as the delimators
    else
    {
      std::string obj_rep;

      // This loop will take care of consecutive white space characters
      while( obj_rep.size() == 0 )
        Utility::fromStream( is, obj_rep, Details::white_space_delims );

      obj = FromStringTraitsIntegralTypeHelper<T>::fromStringImpl( obj_rep, valid_chars );
    }
  }

private:

  template<typename U>
  friend class FromStringTraitsSingleByteIntegralTypeHelper;
};

/*! FromStringTraits helper class for single byte integral types (e.g. char)
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraitsSingleByteIntegralTypeHelper
{
  //! The type that a string will be converted to
  typedef typename FromStringTraitsIntegralTypeHelper<T>::ReturnType ReturnType;

protected:

  //! Attempt to extract the type from the string
  static inline ReturnType fromStringImpl( const std::string& obj_rep,
                                           const std::string& valid_chars )
  {
    // Special case: empty string - not allowed
    if( obj_rep.size() == 0 )
    {
      THROW_EXCEPTION( Utility::StringConversionException,
                       "Cannot convert an empty string to the single byte "
                       "type!" );
      return static_cast<ReturnType>( 0 );
    }
    // Single element string
    else if( obj_rep.size() == 1 )
      return static_cast<ReturnType>( obj_rep.front() );
    // Special case: multiple element string
    else
    {
      std::string trimmed_string = boost::algorithm::trim_copy( obj_rep );

      // All white space - return a white space character
      if( trimmed_string.size() == 0 )
        return static_cast<ReturnType>( ' ' );
      // Only 1 non-white space character
      else if( trimmed_string.size() == 1 )
        return static_cast<ReturnType>( trimmed_string.front() );
      // Multiple non-white space characters - possible integer representation
      else
      {
        typename boost::promote<ReturnType>::type tmp_value;

        try{
          tmp_value =
            FromStringTraitsIntegralTypeHelper<typename boost::promote<ReturnType>::type>::fromStringImpl( trimmed_string, valid_chars );
        }
        EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                                 "Could not convert the string to the "
                                 "single byte integral type!" );

        TEST_FOR_EXCEPTION( tmp_value > std::numeric_limits<ReturnType>::max(),
                            Utility::StringConversionException,
                            "Unable to convert the string to an integral type "
                            "because of overflow (\"" << tmp_value <<
                            "\" > max==\""
                            << std::numeric_limits<ReturnType>::max() <<
                            "\")!" );

        TEST_FOR_EXCEPTION( tmp_value < std::numeric_limits<T>::min(),
                            Utility::StringConversionException,
                            "Unable to convert the string to an integral type "
                            "because of underflow (\"" << tmp_value <<
                            "\" < min==\""
                            << std::numeric_limits<ReturnType>::min() <<
                            "\")!" );

        return static_cast<ReturnType>( tmp_value );
      }
    }
  }

  //! Extract a char from the stream
  static inline void fromStreamImpl( std::istream& is,
                                     T& obj,
                                     const std::string& valid_chars,
                                     const std::string& delims = std::string() )
  {
    if( delims.size() > 0 )
    {
      std::string tmp_string;

      FromStringTraits<std::string>::fromStream( is, tmp_string, delims );

      obj = FromStringTraitsSingleByteIntegralTypeHelper<T>::fromStringImpl( tmp_string, valid_chars );
    }
    else
    {
      char stream_element;
      is.get( stream_element );

      obj = static_cast<T>( stream_element );
    }
  }
};

} // end Details namespace

/*! Partial specialization for single byte signed integral types
 *
 * This partial specialization handles signed char and int8_t types (and
 * possibly char depending on compiler).
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<T,typename std::enable_if<std::is_integral<T>::value && std::is_signed<T>::value && sizeof(T) == 1>::type> : public Details::FromStringTraitsSingleByteIntegralTypeHelper<T>
{
  //! The type that a string will be converted to
  typedef typename Details::FromStringTraitsSingleByteIntegralTypeHelper<T>::ReturnType ReturnType;

  //! Convert the string to an object of type T
  static inline ReturnType fromString( const std::string& obj_rep )
  { return Details::FromStringTraitsSingleByteIntegralTypeHelper<T>::fromStringImpl( obj_rep, "-0123456789" ); }

  //! Extract the object from a stream
  static inline void fromStream( std::istream& is,
                                 T& obj,
                                 const std::string& delim = std::string() )
  { Details::FromStringTraitsSingleByteIntegralTypeHelper<T>::fromStreamImpl( is, obj, "-0123456789", delim ); }
};

/*! Partial specialization for single byte unsigned integral types
 *
 * This partial specialization handles unsigned char and uint8_t types (and
 * possibly char depending on compiler).
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<T,typename std::enable_if<std::is_integral<T>::value && std::is_unsigned<T>::value && sizeof(T) == 1>::type> : public Details::FromStringTraitsSingleByteIntegralTypeHelper<T>
{
  //! The type that a string will be converted to
  typedef typename Details::FromStringTraitsSingleByteIntegralTypeHelper<T>::ReturnType ReturnType;

  //! Convert the string to an object of type T
  static inline ReturnType fromString( const std::string& obj_rep )
  { return Details::FromStringTraitsSingleByteIntegralTypeHelper<T>::fromStringImpl( obj_rep, "0123456789" ); }

  //! Extract the object from a stream
  static inline void fromStream( std::istream& is,
                                 T& obj,
                                 const std::string& delim = std::string() )
  { Details::FromStringTraitsSingleByteIntegralTypeHelper<T>::fromStreamImpl( is, obj, "0123456789", delim ); }
};

/*! Specialization of FromStringTraits for bool
 *
 * The following special keywords are allowed in strings when converting to
 * bool: true and false. The special keywords are case insensitive.
 * \ingroup from_string_traits
 */
template<>
struct FromStringTraits<bool>
{
  //! The type that a string will be converted to
  typedef bool ReturnType;

  //! Convert the string to a boolean
  static inline ReturnType fromString( const std::string& obj_rep )
  {
    std::string lower_case_obj_rep =
      boost::algorithm::to_lower_copy( obj_rep );

    boost::algorithm::trim( lower_case_obj_rep );

    if( lower_case_obj_rep == "true" || lower_case_obj_rep == "1" )
      return true;
    else if( lower_case_obj_rep == "false" || lower_case_obj_rep == "0" )
      return false;
    else
    {
      THROW_EXCEPTION( Utility::StringConversionException,
                       "The string (" << obj_rep << ") does not correspond to "
                       "a boolean!" );
      return false;
    }
  }

  //! Extract a boolean from the stream
  static inline void fromStream( std::istream& is,
                                 bool& obj,
                                 const std::string& delim = std::string() )
  {
    if( delim.size() > 0 )
    {
      std::string bool_rep;

      Utility::fromStream( is, bool_rep, delim );

      obj = FromStringTraits<bool>::fromString( bool_rep );
    }
    // Use white space characters as the deliminators
    else
    {
      std::string bool_rep;

      // This loop will take care of consecutive white space characters
      while( bool_rep.size() == 0 )
        Utility::fromStream( is, bool_rep, Details::white_space_delims );

      obj = FromStringTraits<bool>::fromString( bool_rep );
    }
  }
};

/*! Specialization of FromStringTraits for floating point types
 *
 * The following special keywords are allowed in strings when converting to
 * floating point types: pi, inf*, -inf*. These keywords are case insensitive.
 * A valid string with the 'pi' keyword must have one of the following formats:
 * 'n*pi/d', '-pi' or '-pi/d', where n and d are integers and/or floating point
 * values. The wildcard character after the inf keywords indicates that any
 * keyword that starts with 'inf' or '-inf' will be parsed as infinity or
 * negative infinity respectively.
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<T,typename std::enable_if<std::is_floating_point<T>::value>::type>
{
  //! The type that a string will be converted to
  typedef T ReturnType;

  //! Convert the string to an object of type T
  static inline ReturnType fromString( const std::string& obj_rep )
  {
    // Remove leading and trailing white space from the string
    std::string trimmed_obj_rep = boost::algorithm::trim_copy( obj_rep );

    TEST_FOR_EXCEPTION( trimmed_obj_rep.size() == 0,
                        Utility::StringConversionException,
                       "Cannot convert an empty string to an floating point "
                       "type!" );

    boost::algorithm::to_lower( trimmed_obj_rep );

    // Check for the negative infinity keyword
    if( trimmed_obj_rep.find( "-inf" ) < trimmed_obj_rep.size() )
      return -std::numeric_limits<ReturnType>::infinity();

    // Check for the infinity keyword
    if( trimmed_obj_rep.find( "inf" ) < trimmed_obj_rep.size() )
      return std::numeric_limits<ReturnType>::infinity();

    // Check for the pi keyword
    if( trimmed_obj_rep.find( "pi" ) < trimmed_obj_rep.size() )
    {
      try{
        Utility::expandPiKeywords( trimmed_obj_rep );
      }
      EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                  Utility::StringConversionException,
                                  "Unable to replace the pi keywords!" );
    }

    // Check for unsupported characters
    TEST_FOR_EXCEPTION( trimmed_obj_rep.find_first_not_of( "+-0123456789e." ) <
                        trimmed_obj_rep.size(),
                        Utility::StringConversionException,
                        "Unable to convert the string to a floating point "
                        "type because unsupported characters (\""
                        << trimmed_obj_rep[trimmed_obj_rep.find_first_not_of( "+-0123456789e." )] <<
                        "\") are present!" );

    std::istringstream iss( trimmed_obj_rep );

    ReturnType obj;

    iss >> obj;

    // An error has occurred
    if( !iss && !iss.eof() )
    {
      THROW_EXCEPTION( Utility::StringConversionException,
                       "Unable to convert the string to a floating point "
                       "type because an error occurred in the string "
                       "stream!" );
    }
    // Unused characters are present
    else if( !iss.eof() )
    {
      std::string unused_characters;
      iss >> unused_characters;

      THROW_EXCEPTION( Utility::StringConversionException,
                       "Unused characters (\"" << unused_characters << "\") "
                       "in string after conversion to floating point type!" );
    }

    return obj;
  }

  //! Extract an object of type T from the stream
  static inline void fromStream( std::istream& is,
                                 T& obj,
                                 const std::string& delim = std::string() )
  {
    if( delim.size() > 0 )
    {
      std::string obj_rep;

      Utility::fromStream( is, obj_rep, delim );

      obj = FromStringTraits<T>::fromString( obj_rep );
    }
    // Use white space characters as the deliminators
    else
    {
      std::string obj_rep;

      // This loop will take care of consecutive white space characters
      while( obj_rep.size() == 0 )
        Utility::fromStream( is, obj_rep, Details::white_space_delims );

      obj = FromStringTraits<T>::fromString( obj_rep );
    }
  }
};

/*! \brief Partial specialization of FromStringTraits for signed integral types
 * (except for single byte signed integral types).
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<T,typename std::enable_if<std::is_integral<T>::value && std::is_signed<T>::value && (sizeof(T) > 1)>::type> : public Details::FromStringTraitsIntegralTypeHelper<T>
{
  //! The type that a string will be converted to
  typedef typename Details::FromStringTraitsIntegralTypeHelper<T>::ReturnType ReturnType;

  //! Convert the string to an object of type T
  static inline ReturnType fromString( const std::string& obj_rep )
  { return Details::FromStringTraitsIntegralTypeHelper<T>::fromStringImpl( obj_rep, "-0123456789" ); }

  //! Extract the object from a stream
  static inline void fromStream( std::istream& is,
                                 T& obj,
                                 const std::string& delim = std::string() )
  { Details::FromStringTraitsIntegralTypeHelper<T>::fromStreamImpl( is, obj, "-0123456789", delim ); }
};

/*! \brief Partial specialization of FromStringTraits for unsigned integral
 * types (except for single byte unsigned integral types).
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<T,typename std::enable_if<std::is_integral<T>::value && std::is_unsigned<T>::value && (sizeof(T) > 1)>::type> : public Details::FromStringTraitsIntegralTypeHelper<T>
{
  //! The type that a string will be converted to
  typedef typename Details::FromStringTraitsIntegralTypeHelper<T>::ReturnType ReturnType;

  //! Convert the string to an object of type T
  static inline ReturnType fromString( const std::string& obj_rep )
  { return Details::FromStringTraitsIntegralTypeHelper<T>::fromStringImpl( obj_rep, "0123456789" ); }

  //! Extract the object from a stream
  static inline void fromStream( std::istream& is,
                                 T& obj,
                                 const std::string& delim = std::string() )
  { Details::FromStringTraitsIntegralTypeHelper<T>::fromStreamImpl( is, obj, "0123456789", delim ); }
};

namespace Details{

//! FromStringTraits base helper class for stl compliant containers with general value (non-arithmetic) types
template<typename STLCompliantContainer,
         typename ContainerValueType = typename STLCompliantContainer::value_type,
         typename ReturnContainerType = STLCompliantContainer,
         typename ReturnContainerValueType = typename ReturnContainerType::value_type,
         typename Enabled = void>
struct FromStringTraitsSTLCompliantContainerBaseHelper
{
  //! The type that a string will be converted to
  typedef ReturnContainerType ReturnType;

  //! Convert the string to the required container type
  template<typename ElementInsertionMemberFunction>
  static inline ReturnType fromStringImpl( const std::string& obj_rep,
                                           ElementInsertionMemberFunction insert_element )
  {
    ReturnType container;

    std::istringstream iss( obj_rep );

    FromStringTraitsSTLCompliantContainerBaseHelper<ReturnType,ReturnContainerValueType>::fromStreamImpl( iss, container, insert_element );

    return container;
  }

  //! Extract the container object from a stream
  template<typename ElementInsertionMemberFunction>
  static inline void fromStreamImpl( std::istream& is,
                                     STLCompliantContainer& obj,
                                     ElementInsertionMemberFunction insert_element )
  {
    obj.clear();

    try{
      // Initialize the input stream
      Utility::initializeInputStream( is, container_start_char );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                Utility::StringConversionException,
                                "Could not initialize the stream!" );

    // Extract each element of the container
    bool done = false;
    size_t element_index = 0;

    if( Utility::doesInputStreamContainAnotherElement( is, container_end_char ) )
    {
      while( !done )
      {
        ContainerValueType element;

        try{
          Utility::fromStream( is, element, container_element_delims );
        }
        EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                                 "Element " << element_index << " was not "
                                 "successfully extracted from the stream!" );

        // Check if the stream is still valid
        TEST_FOR_EXCEPTION( is.eof(),
                            Utility::StringConversionException,
                            "Unable to get element " << element_index <<
                            " (EOF reached unexpectedly)!" );

        TEST_FOR_EXCEPTION( !is,
                            Utility::StringConversionException,
                            "Unable to get element " << element_index <<
                            " (one or more error flags have been set)!" );

        // The element has been successfully extracted
        (obj.*insert_element)( element );
        ++element_index;

        // Position the stream at the start of the next element (or end)
        try{
          done = Utility::moveInputStreamToNextElement( is, next_container_element_char, container_end_char );
        }
        EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                    Utility::StringConversionException,
                                    "Could not move the input stream to the "
                                    "next element (" << element_index <<
                                    ")!" );
      }
    }
  }
};

//! FromStringTraits base helper class for stl compliant containers with arithmetic value types
template<typename STLCompliantContainer,
         typename ContainerValueType,
         typename ReturnContainerType,
         typename ReturnContainerValueType>
struct FromStringTraitsSTLCompliantContainerBaseHelper<STLCompliantContainer,ContainerValueType,ReturnContainerType,ReturnContainerValueType,typename std::enable_if<std::is_arithmetic<ContainerValueType>::value && std::is_arithmetic<ReturnContainerValueType>::value && (sizeof(ContainerValueType) > 1) && (sizeof(ReturnContainerType) > 1)>::type>
{
  //! The type that a string will be converted to
  typedef ReturnContainerType ReturnType;

  //! Convert the string to the required container type
  template<typename ElementInsertionMemberFunction>
  static inline ReturnType fromStringImpl( const std::string& obj_rep,
                                           ElementInsertionMemberFunction insert_element )
  {
    ReturnType container;

    std::istringstream iss( obj_rep );

    FromStringTraitsSTLCompliantContainerBaseHelper<ReturnType,ReturnContainerValueType>::fromStreamImpl( iss, container, insert_element );

    return container;
  }

  //! Extract the container object from a stream
  template<typename ElementInsertionMemberFunction>
  static inline void fromStreamImpl( std::istream& is,
                                     STLCompliantContainer& obj,
                                     ElementInsertionMemberFunction insert_element )
  {
    obj.clear();

    // Extract the entire string
    std::string obj_rep;

    try{
      Utility::fromStream( is, obj_rep, container_element_delims );
    }
    EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                             "Could not extract the object string from the "
                             "stream!" );

    // Expand repeat keywords
    try{
      Utility::expandRepeatKeywords<ContainerValueType>( obj_rep );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                Utility::StringConversionException,
                                "Unable to expand the repeat keywords!" );

    // Expand interval keywords
    try{
      Utility::expandIntervalKeywords<ContainerValueType>( obj_rep );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                Utility::StringConversionException,
                                "Unable to expand the interval keywords!" );

    // Create a new stream from the extracted and potentially modified
    // object representation
    std::istringstream iss( obj_rep );

    try{
      // Initialize the input stream
      Utility::initializeInputStream( iss, container_start_char );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                Utility::StringConversionException,
                                "Could not initialize the stream!" );

    if( Utility::doesInputStreamContainAnotherElement( iss, container_end_char, true ) )
    {
      // Extract each element of the container
      bool done = false;
      size_t element_index = 0;

      while( !done )
      {
        ContainerValueType element;

        try{
          Utility::fromStream( iss, element, container_element_delims );
        }
        EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                                 "Element " << element_index << " was not "
                                 "successfully extracted from the stream!" );

        // Check if the stream is still valid
        TEST_FOR_EXCEPTION( iss.eof(),
                            Utility::StringConversionException,
                            "Unable to get element " << element_index <<
                            " (EOF reached unexpectedly)!" );

        TEST_FOR_EXCEPTION( !iss,
                            Utility::StringConversionException,
                            "Unable to get element " << element_index <<
                            " (one or more error flags have been set)!" );

        // The element has been successfully extracted
        (obj.*insert_element)( element );
        ++element_index;

        // Position the stream at the start of the next element (or end)
        try{
          done = Utility::moveInputStreamToNextElement( iss, next_container_element_char, container_end_char );
        }
        EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                    Utility::StringConversionException,
                                    "Could not move the input stream to the "
                                    "next element (" << element_index <<
                                    ")!" );
      }
    }
  }
};

/*! \brief FromStringTraits helper class for stl compliant containers with a
 * push_back method.
 */
template<typename STLCompliantContainer,
         typename ReturnContainerType = STLCompliantContainer>
struct FromStringTraitsSTLCompliantContainerPushBackHelper : protected FromStringTraitsSTLCompliantContainerBaseHelper<STLCompliantContainer,typename STLCompliantContainer::value_type,ReturnContainerType,typename ReturnContainerType::value_type>
{
protected:
  //! The base helper class type
  typedef FromStringTraitsSTLCompliantContainerBaseHelper<STLCompliantContainer,typename STLCompliantContainer::value_type,ReturnContainerType,typename ReturnContainerType::value_type> BaseType;

public:
  //! The type that a string will be converted to
  typedef typename BaseType::ReturnType ReturnType;

  //! Convert the string to an object of the container type
  static inline ReturnType fromString( const std::string& obj_rep )
  {
    return BaseType::fromStringImpl( obj_rep, (void (ReturnType::*)(const typename ReturnType::value_type&))&ReturnType::push_back );
  }

  //! Extract the object from a stream
  static inline void fromStream( std::istream& is,
                                 STLCompliantContainer& obj,
                                 const std::string& = std::string() )
  {
    BaseType::fromStreamImpl( is, obj, (void (STLCompliantContainer::*)(const typename STLCompliantContainer::value_type&))&STLCompliantContainer::push_back );
  }
};

/*! \brief FromStringTraits helper class for stl compliant containers with an
 * insert method.
 */
template<typename STLCompliantContainer,
         typename ContainerValueType = typename STLCompliantContainer::value_type,
         typename ReturnContainerType = STLCompliantContainer,
         typename ReturnContainerValueType = typename ReturnContainerType::value_type>
struct FromStringTraitsSTLCompliantContainerInsertHelper : protected FromStringTraitsSTLCompliantContainerBaseHelper<STLCompliantContainer,ContainerValueType,ReturnContainerType,ReturnContainerValueType>
{
protected:
  //! The base helper class type
  typedef FromStringTraitsSTLCompliantContainerBaseHelper<STLCompliantContainer,ContainerValueType,ReturnContainerType,ReturnContainerValueType> BaseType;

public:
  //! The type that a string will be converted to
  typedef typename BaseType::ReturnType ReturnType;

  //! Convert the string to an object of the container type
  static inline ReturnType fromString( const std::string& obj_rep )
  {
    return BaseType::fromStringImpl( obj_rep, (std::pair<typename ReturnType::iterator,bool> (ReturnType::*)(const typename ReturnType::value_type&))&ReturnType::insert );
  }

  //! Extract the object from a stream
  static inline void fromStream( std::istream& is,
                                 STLCompliantContainer& obj,
                                 const std::string& = std::string() )
  {
    BaseType::fromStreamImpl( is, obj, (std::pair<typename STLCompliantContainer::iterator,bool> (STLCompliantContainer::*)(const typename STLCompliantContainer::value_type&))&STLCompliantContainer::insert );
  }
};

} // end Details namespace

// Convert the string to an object of type T
template<typename T>
inline typename Utility::FromStringTraits<T>::ReturnType
fromString( const std::string& obj_rep )
{
  return Utility::FromStringTraits<T>::fromString( obj_rep );
}

// Extract an object of type T from the stream
template<typename T>
inline void fromStream( std::istream& is, T& obj, const std::string& delims )
{
  Utility::FromStringTraits<T>::fromStream( is, obj, delims );
}

namespace Details{

// Replace occurrences of interval keyword within a substring
template<typename T>
inline void expandIntervalKeywordInSubstring( const std::string& left_element,
                                              std::string& middle_element,
                                              const std::string& right_element )
{
  bool raw_left_element = left_element.find( next_container_element_char ) > left_element.size();
  bool raw_right_element = right_element.find( next_container_element_char ) > right_element.size();

  std::string::size_type op_pos;

  if( middle_element.find( "pi" ) >= middle_element.size() &&
      middle_element.find( "inf" ) >= middle_element.size() )
    op_pos = middle_element.find_first_of( "il" );
  else
    op_pos = middle_element.size();


  if( raw_left_element && raw_right_element &&
      op_pos < middle_element.size() )
  {
    TEST_FOR_EXCEPTION( left_element.find( "inf" ) < left_element.size(),
                        std::runtime_error,
                        "The inf keyword cannot be used with the interval "
                        "keyword!" );

    if( left_element.find( "pi" ) >= left_element.size() )
    {
      TEST_FOR_EXCEPTION( left_element.find_first_of( "il" ) <
                          left_element.size(),
                          std::runtime_error,
                          "interval keywords cannot occur in consecutive "
                          "elements!" );
    }

    TEST_FOR_EXCEPTION( right_element.find( "inf" ) < right_element.size(),
                        std::runtime_error,
                        "The inf keyword cannot be used with the interval "
                        "keyword!" );

    if( right_element.find( "pi" ) >= right_element.size() )
    {
      TEST_FOR_EXCEPTION( right_element.find_first_of( "il" ) <
                          right_element.size(),
                          std::runtime_error,
                          "interval keywords cannot occur in consecutive "
                          "elements!" );
    }

    T left_value, right_value;

    try{
      left_value = Utility::fromString<T>( left_element );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                Utility::StringConversionException,
                                "Could not convert the left sequence "
                                "container element (" << left_element << ") "
                                "to the desired type!" );

    try{
      right_value = Utility::fromString<T>( right_element );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                Utility::StringConversionException,
                                "Could not convert the right sequence "
                                "container element (" << right_element << ") "
                                "to the desired type!" );

    // TEST_FOR_EXCEPTION( left_value > right_value,
    //     		std::runtime_error,
    //     		"the array elements must be in ascending order ("
    //                     << left_value << " !<= " << right_value << ")!" );

    size_t intervals =
      Utility::fromString<size_t>( middle_element.substr( 0, op_pos ) );

    TEST_FOR_EXCEPTION( intervals <= 0ll,
			std::runtime_error,
			"a positive integer must be specified with the "
                        "interval keyword (e.g. 3i or 10l)!" );

    // Increment the interval value to account for the last element
    ++intervals;

    // Linear increments
    if( middle_element[op_pos] == 'i' )
    {
      T step_size = (right_value-left_value)/intervals;

      // Replace the interval keyword with the new elements
      middle_element = " ";

      for( size_t i = 1; i < intervals; ++i )
      {
	std::ostringstream oss;

        Utility::toStream( oss, left_value + step_size*i );

	middle_element += oss.str();

	if( i < intervals-1 )
        {
	  middle_element += next_container_element_char;
          middle_element += " ";
        }
      }
    }
    // Log increments
    else
    {
      TEST_FOR_EXCEPTION( left_value <= 0,
			  std::runtime_error,
			  "the starting value ( " << left_value <<
                          ") must be positive when using the log interval "
                          "keyword 'l'!" );

      T step_size = log(right_value/left_value)/intervals;

      // Replace the interval keyword with the new elements
      middle_element = " ";

      for( size_t i = 1; i < intervals; ++i )
      {
	std::ostringstream oss;

        Utility::toStream( oss, (T)exp( log(left_value) + step_size*i ) );

	middle_element += oss.str();

	if( i < intervals-1 )
        {
	  middle_element += next_container_element_char;
          middle_element += " ";
        }
      }
    }
  }
}

} // end Details namespace

// Expand interval keywords in string
template<typename T>
void expandIntervalKeywords( std::string& obj_rep )
{
  // Loop through all array elements
  boost::algorithm::trim( obj_rep );

  std::vector<std::string> array_elements;

  boost::split( array_elements,
                obj_rep,
                boost::is_any_of( "," ) );

  std::string front_copy =
    boost::algorithm::to_lower_copy( array_elements.front() );

  if( front_copy.find( "inf" ) >= front_copy.size() &&
      front_copy.find( "pi" ) >= front_copy.size() )
  {
    TEST_FOR_EXCEPTION( array_elements.front().find_first_of( "il" ) <
                        array_elements.front().size(),
                        std::runtime_error,
                        "the first element cannot have an interval keyword!" );
  }

  std::string back_copy =
    boost::algorithm::to_lower_copy( array_elements.back() );

  if( back_copy.find( "inf" ) >= back_copy.size() &&
      back_copy.find( "pi" ) >= back_copy.size() )
  {
    TEST_FOR_EXCEPTION( array_elements.back().find_first_of( "il" ) <
                        array_elements.back().size(),
                        std::runtime_error,
                        "the last element cannot have an interval keyword!" );
  }

  std::string::size_type bracket_pos =
    array_elements.front().find( container_start_char );

  if( bracket_pos < array_elements.front().size() )
    array_elements.front().erase( bracket_pos, 1 );

  bracket_pos = array_elements.back().find( container_end_char );

  if( bracket_pos < array_elements.back().size() )
    array_elements.back().erase( bracket_pos, 1 );

  for( size_t i = 1; i < array_elements.size()-1; ++i )
  {
    // We want the 'i' and 'l' keywords to be case insensitive
    boost::algorithm::to_lower( array_elements[i] );

    try{
      Details::expandIntervalKeywordInSubstring<T>(
                      boost::algorithm::to_lower_copy( array_elements[i-1] ),
                      array_elements[i],
                      boost::algorithm::to_lower_copy( array_elements[i+1] ) );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                Utility::StringConversionException,
                                "Unable to expand the interval keyword in the "
                                "sequence container sub-string (... "
                                << array_elements[i-1] << ", "
                                << array_elements[i] << ", "
                                << array_elements[i+1] << " ...)!" );
  }

  // Reconstruct the array string
  obj_rep = container_start_char;
  obj_rep += array_elements.front();

  for( size_t i = 1; i < array_elements.size(); ++i )
  {
    obj_rep += next_container_element_char;
    obj_rep += array_elements[i];
  }

  obj_rep += container_end_char;
}

// Expand repeated value keywords in string
template<typename T>
void expandRepeatKeywords( std::string& obj_rep )
{
  // Loop through all array elements
  boost::algorithm::trim( obj_rep );

  std::vector<std::string> array_elements;

  boost::split( array_elements,
                obj_rep,
                boost::is_any_of( "," ) );

  std::string::size_type bracket_pos =
    array_elements.front().find( container_start_char );

  if( bracket_pos < array_elements.front().size() )
    array_elements.front().erase( bracket_pos, 1 );

  bracket_pos = array_elements.back().find( container_end_char );

  if( bracket_pos < array_elements.back().size() )
    array_elements.back().erase( bracket_pos, 1 );

  for( size_t i = 0; i < array_elements.size(); ++i )
  {
    // We want the 'r' to be case insensitive
    boost::algorithm::to_lower( array_elements[i] );

    std::string::size_type op_pos =
      array_elements[i].find_first_of( 'r' );

    if( op_pos < array_elements[i].size() )
    {
      T repeated_value;

      try{
        repeated_value =
          Utility::fromString<T>( array_elements[i].substr( 0, op_pos ) );
      }
      EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                  Utility::StringConversionException,
                                  "Could not extract the repeated value from "
                                  "the sequence container element ("
                                  << array_elements[i] << ")!" );

      size_t number_of_repeats;

      try{
        std::string number_of_repeats_string =
          array_elements[i].substr( op_pos+1,
                                    array_elements[i].size() - op_pos - 1 );

        number_of_repeats =
          Utility::fromString<size_t>( number_of_repeats_string );
      }
      EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                  Utility::StringConversionException,
                                  "Could not extract the number of repeats "
                                  "from the sequence container element ("
                                  << array_elements[i] << ")!" );

      TEST_FOR_EXCEPTION( number_of_repeats <= 0,
                          std::runtime_error,
                          "A positive integer must be specified with repeat "
                          "operator!" );

      std::string repeated_value_string = Utility::toString( repeated_value );

      // Replace the element string with the expansion
      if( i > 0 )
      {
        array_elements[i] = " ";
        array_elements[i] += repeated_value_string;
      }
      else
        array_elements[i] = repeated_value_string;

      for( size_t j = 1; j < number_of_repeats; ++j )
      {
        array_elements[i] += next_container_element_char;
        array_elements[i] += " ";

	array_elements[i] += repeated_value_string;
      }
    }
  }

  // Reconstruct the array string
  obj_rep = container_start_char;
  obj_rep += array_elements.front();

  for( size_t i = 1; i < array_elements.size(); ++i )
  {
    obj_rep += next_container_element_char;
    obj_rep += array_elements[i];
  }

  obj_rep += container_end_char;
}

/*! \brief Partial specialization of FromStringTraits for
 * std::complex types.
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<std::complex<T> >
{
  //! The type that a string will be converted to
  typedef std::complex<T> ReturnType;

  //! Convert the string to an object of type std::complex<T>
  static inline ReturnType fromString( const std::string& obj_rep )
  {
    // Extract the real and imaginary components of the complex number
    std::vector<T> components = Details::FromStringTraitsSTLCompliantContainerPushBackHelper<std::vector<T> >::fromString( obj_rep );

    // There must only be two and only two components
    TEST_FOR_EXCEPTION( components.size() != 2,
                        Utility::StringConversionException,
                        "Could not extract the real and imaginary components "
                        "of the complex number from the stream (number of "
                        "components = " << components.size() << " != 2)." );

    return ReturnType( components[0], components[1] );
  }

  //! Extract an object of type std::complex<T> from the stream
  static inline void fromStream( std::istream& is,
                                 std::complex<T>& obj,
                                 const std::string& delim = std::string() )
  {
    // Extract the real and imaginary components of the complex number
    std::vector<T> components;

    Details::FromStringTraitsSTLCompliantContainerPushBackHelper<std::vector<T> >::fromStream( is, components, delim );

    // There must only be two and only two components
    TEST_FOR_EXCEPTION( components.size() != 2,
                        Utility::StringConversionException,
                        "Could not extract the real and imaginary components "
                        "of the complex number from the stream (number of "
                        "components = " << components.size() << " != 2)." );

    obj.real( components[0] );
    obj.imag( components[1] );
  }
};

/*! \brief Partial specialization of FromStringTraits for
 * boost::unit::quantity types.
 * \ingroup from_string_traits
 */
template<typename Unit, typename T>
struct FromStringTraits<boost::units::quantity<Unit,T> >
{

private:

  // This type
  typedef FromStringTraits<boost::units::quantity<Unit,T> > ThisType;

public:

  //! The type that a string will be converted to
  typedef boost::units::quantity<Unit,T> ReturnType;

  //! Convert the string to an object of type boost::units::quantity<Unit,T>
  static inline ReturnType fromString( const std::string& obj_rep )
  {
    std::string trimmed_obj_rep = boost::algorithm::trim_copy( obj_rep );

    size_t container_end_loc = trimmed_obj_rep.find_first_of( Utility::container_end_char );

    size_t space_loc;

    // The type T can be a container (e.g. std::complex) - don't count white
    // spaces that occur inside of the container
    if( container_end_loc < trimmed_obj_rep.size() )
      space_loc = trimmed_obj_rep.find( " ", container_end_loc );
    else
      space_loc =  trimmed_obj_rep.find( " " );

    TEST_FOR_EXCEPTION( space_loc >= trimmed_obj_rep.size(),
                        Utility::StringConversionException,
                        "Unable to convert the string to a "
                        "boost::units::quantity type because the string "
                        "does not contain any units!" );

    std::string value_rep = trimmed_obj_rep.substr( 0, space_loc );
    std::string unit_rep =
      trimmed_obj_rep.substr( space_loc+1,
                              trimmed_obj_rep.size()-space_loc-1 );

    // Check that the unit matches
    ThisType::verifyExtractedUnit( unit_rep );

    T raw_value;

    try{
      raw_value = FromStringTraits<T>::fromString( value_rep );
    }
    EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                             "Could not convert the string to a "
                             "boost::units::quantity type!" );

    return boost::units::quantity<Unit,T>::from_value( raw_value );
  }

  //! Extract an object of type boost::units::quantity<Unit,T> from the stream
  static inline void fromStream( std::istream& is,
                                 boost::units::quantity<Unit,T>& obj,
                                 const std::string& delim = std::string() )
  {
    // Remove leading white space characters from the stream
    ThisType::removeLeadingWhiteSpaceChars( is );

    // Extract the raw value
    T raw_value;
    Utility::fromStream( is, raw_value, " " );

    Utility::moveInputStreamToNextElement( is, ' ', ' ' );

    // Extract the unit
    std::string unit_rep;

    if( delim.size() > 0 )
      Utility::fromStream( is, unit_rep, delim );
    else
    {
      // Extract the unit
      std::string unit_rep_element;

      size_t num_elements = ThisType::getExpectedNumberOfElementsInUnit();

      for( size_t i = 0; i < num_elements; ++i )
      {
        // This loop will take care of consecutive white space characters
        while( unit_rep_element.size() == 0 )
          Utility::fromStream( is, unit_rep_element, Details::white_space_delims );

        unit_rep += unit_rep_element;

        if( i < num_elements - 1 )
          unit_rep += ' ';

        unit_rep_element.clear();
      }
    }

    // Check that the extracted unit is correct
    ThisType::verifyExtractedUnit( unit_rep );

    obj = boost::units::quantity<Unit,T>::from_value( raw_value );
  }

private:

  // Remove leading white space characters
  static void removeLeadingWhiteSpaceChars( std::istream& is )
  {
    char stream_char;
    bool done = false;

    while( !done )
    {
      stream_char = is.peek();

      done = true;

      for( size_t i = 0; i < Details::white_space_delims.size(); ++i )
      {
        if( stream_char == Details::white_space_delims[i] )
        {
          is.get();
          done = false;
          break;
        }
      }
    }
  }

  // Check that the extract unit is correct
  static void verifyExtractedUnit( const std::string& unit_rep )
  {
    TEST_FOR_EXCEPTION( Utility::UnitTraits<Unit>::symbol() != unit_rep,
                        Utility::StringConversionException,
                        "Unable to convert the string to a "
                        "boost::units::quantity type because the requested "
                        "units (" << Utility::UnitTraits<Unit>::symbol() <<
                        ") do not match the extracted units ("
                        << unit_rep << ")!" );
  }

  // Get the number of expected spaces in the quantity string
  static size_t getExpectedNumberOfElementsInUnit()
  {
    // There will always be at least one space since to separate the value
    // from the unit (the unit may introduce more spaces)
    size_t num_spaces = 0;

    std::string unit_string =
      Utility::UnitTraits<Unit>::symbol();

    std::vector<std::string> unit_string_elements;
    boost::split( unit_string_elements, unit_string, boost::is_any_of( " " ) );

    return unit_string_elements.size();
  }
};

} // end Utility namespace

#endif // end UTILITY_FROM_STRING_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_FromStringTraits.hpp
//---------------------------------------------------------------------------//
