//---------------------------------------------------------------------------//
//!
//! \file   Utility_FromStringTraits.hpp
//! \author Alex Robinson
//! \brief  FromStringTraits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_FROM_STRING_TRAITS_HPP
#define UTILITY_FROM_STRING_TRAITS_HPP

// Std Lib Includes
#include <sstream>
#include <iterator>
#include <limits>

// Boost Includes
#include <boost/algorithm/string.hpp>
#include <boost/type_traits/promote.hpp>

// FRENSIE Includes
#include "Utility_FromStringTraitsDecl.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace Utility{

namespace Details{

// 9 = tab (\t), 10 = new line (\n), 32 = white space
const char white_space_delims[3] = {(char)9, (char)10, (char)32};
  
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
    
    if( delims.size() > 0 )
    {
      bool done = false;
      
      while( !done )
      {
        char string_element;
        is.get( string_element );

        if( (delims.size() == 0 || delims == Details::white_space_delims ) && is.eof() )
        {
          done = true;
        }
        else if( is.eof() )
        {
          THROW_EXCEPTION( Utility::StringConversionException,
                           "Unable to get the string element (EOF reached "
                           "unexpectedly)!" );
        }
        else if( !is )
        {
          THROW_EXCEPTION( Utility::StringConversionException,
                           "Unable to get the string element (one or more "
                           "error flags have been set)!" );
        }

        if( delims.find( string_element ) < delims.size() )
        {
          done = true;

          // Put the deliminator back in the stream so that it can be
          // parsed correctly later
          if( delims != Details::white_space_delims )
            is.putback( string_element );
        }

        if( !done )
          obj.push_back( string_element );
      }

      // Trim the extracted string (unless the string is only whitespace)
      if( obj.find_first_not_of( " " ) < obj.size() )
        boost::algorithm::trim( obj );
    }
    // No deliminators have been specified - use the default extraction method
    else
      std::getline( is, obj );
  }
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
 * floating point types: pi, inf*, -inf*. These keywords are case insenstive.
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
      Utility::initializeInputStream( is, '{' );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                Utility::StringConversionException,
                                "Could not initialize the stream!" );

    // Extract each element of the container
    bool done = false;
    size_t element_index = 0;

    if( Utility::doesInputStreamContainAnotherElement( is, '}' ) )
    {
      while( !done )
      {
        ContainerValueType element;

        try{
          Utility::fromStream( is, element, ",}" );
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
          done = Utility::moveInputStreamToNextElement( is, ',', '}' );
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
struct FromStringTraitsSTLCompliantContainerBaseHelper<STLCompliantContainer,ContainerValueType,ReturnContainerType,ReturnContainerValueType,typename std::enable_if<std::is_arithmetic<ContainerValueType>::value && std::is_arithmetic<ReturnContainerValueType>::value && !std::is_same<ContainerValueType,char>::value && !std::is_same<ReturnContainerValueType,char>::value>::type>
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
      Utility::initializeInputStream( is, '{' );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                Utility::StringConversionException,
                                "Could not initialize the stream!" );

    // Extract the entire string
    std::string obj_rep;

    try{
      Utility::fromStream( is, obj_rep, "}" );
    }
    EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                             "Could not extract the object string from the "
                             "stream!" );

    if( obj_rep.size() > 0 )
    {
      // Expand interval keywords
      try{
        Utility::expandIntervalKeywords( obj_rep );
      }
      EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                  Utility::StringConversionException,
                                  "Unable to expand the interval keywords!" );

      // Create a new stream from the extracted and potentially modified
      // object representation
      std::istringstream iss( obj_rep );
      
      try{
        // Initialize the input stream
        Utility::initializeInputStream( iss, '{' );
      }
      EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                  Utility::StringConversionException,
                                  "Could not initialize the stream!" );

      // Extract each element of the container
      bool done = false;
      size_t element_index = 0;
      
      while( !done )
      {
        ContainerValueType element;
        
        try{
          Utility::fromStream( iss, element, ",}" );
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
          done = Utility::moveInputStreamToNextElement( iss, ',', '}' );
        }
        EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                    Utility::StringConversionException,
                                    "Could not move the input stream to the "
                                    "next element (" << element_index <<
                                    ")!" );
      }

      // Position the original stream at the start of the next element (or end)
      try{
        Utility::moveInputStreamToNextElement( is, ',', '}' );
      }
      EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                  Utility::StringConversionException,
                                  "Could not move the input stream to the "
                                  "next element!" );
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

// Initialize the input stream that will be used to deserialize an object
inline void initializeInputStream( std::istream& is, const char start_delim )
{
  // Read the start deliminator
  std::string start_bracket;
  std::getline( is, start_bracket, start_delim );
  boost::algorithm::trim( start_bracket );

  TEST_FOR_EXCEPTION( start_bracket.size() != 0,
                      std::runtime_error,
                      "Unable to initialize the input stream because there "
                      "are characters preceding the start deliminator ("
                      << start_delim << ")! Here are the extra characters: "
                      << start_bracket );
}

// Move the input stream to the start of the next element
inline bool moveInputStreamToNextElement( std::istream& is,
                                          const char elem_delim,
                                          const char end_delim )
{
  // Search for the specified element deliminator
  char delim;
  
  while( true )
  {
    is.get( delim );

    TEST_FOR_EXCEPTION( is.eof(),
                        std::runtime_error,
                        "Unable to move the input stream to the next element "
                        "(EOF reached unexpectedly)!" );

    TEST_FOR_EXCEPTION( !is,
                        std::runtime_error,
                        "Unable to move the input stream to the next element "
                        "(one or more error flags have been set)!" );
    
    // Another element must be deserialized
    if( delim == elem_delim )
      return false;
    
    // All elements have been deserialized
    else if( delim == end_delim )
      return true;

    // An invalid deliminator has been encountered
    else if( delim != ' ' )
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Unable to move the input stream to the next element "
                       "(bad deliminator encountered: " << delim << ")!" );
      return true;
    }
  }
}

// Check if the input stream contains any more elements to read.
inline bool doesInputStreamContainAnotherElement( std::istream& is,
                                                  const char end_delim,
                                                  const bool ignore_whitespace )
{
  std::string stream_cache;
  char element;

  bool another_element_present;
  
  while( true )
  {
    is.get( element );

    TEST_FOR_EXCEPTION( is.eof(),
                        std::runtime_error,
                        "Unable to move the input stream to the next element "
                        "(EOF reached unexpectedly)!" );

    TEST_FOR_EXCEPTION( !is,
                        std::runtime_error,
                        "Unable to move the input stream to the next element "
                        "(one or more error flags have been set)!" );

    stream_cache.push_back( element );

    // The end deliminator was encountered - there are no more elements
    if( element == end_delim )
    {
      another_element_present = false;
      break;
    }
    else if( element == ' ' )
    {
      if( !ignore_whitespace )
      {
        another_element_present = true;
        break;
      }
    }
    else
    {
      another_element_present = true;
      break;
    }
  }

  // Restore the stream
  if( another_element_present )
  {
    while( stream_cache.size() > 0 )
    {
      is.putback( stream_cache.back() );

      stream_cache.pop_back();
    }
  }

  return another_element_present;
}

namespace Details{

// Expand pi keyword in a substring
inline void expandPiKeywordInSubstring( const std::string::size_type start,
                                        const std::string::size_type true_end,
                                        std::string& substring )
{
  // Convert to lower case
  boost::algorithm::to_lower( substring );
  
  std::string::size_type pi_pos = substring.find( "pi", start );

  TEST_FOR_EXCEPTION( substring.find( "pi", pi_pos+2 ) < true_end,
		      std::runtime_error,
		      "The 'pi' keyword cannot occur multiple times in the "
                      "same element!" );

  if( pi_pos >= start && pi_pos < true_end )
  {
    double front_value = 1.0, end_value = 1.0;

    std::string front_string = substring.substr( start, pi_pos-start );

    if( front_string.find_first_of( "0123456789" ) < front_string.size() )
    {
      std::istringstream iss( front_string );

      iss >> front_value;
    }
    else if( front_string.find( "-" ) < front_string.size() )
      front_value = -1.0;

    std::string::size_type div_pos = substring.find_first_of( "/", start );

    if( div_pos < true_end && div_pos > pi_pos )
    {
      std::string end_string =
	substring.substr( div_pos+1, true_end - div_pos );

      if( end_string.find_first_of( "0123456789" ) <
	  end_string.size() )
      {
	std::istringstream iss( end_string );

	iss >> end_value;
      }
    }
    else if( div_pos < pi_pos )
    {
      THROW_EXCEPTION( std::runtime_error,
		       "invalid array element value ("
		       << substring.substr( start, true_end )
		       << ")! " );
    }

    std::ostringstream oss;
    oss.precision( 18 );

    oss << front_value*Utility::PhysicalConstants::pi/end_value;

    substring.replace( start, true_end - start + 1, oss.str() );
  }
}
  
} // end Details namespace

// Expand pi keyword in string
inline void expandPiKeywords( std::string& obj_rep )
{
  std::string::size_type orig_string_size = 0;
  std::string::size_type elem_start_pos, elem_end_pos;

  do{
    // This is either the first loop or the string has changed because
    // an occurance of the pi keyword has been replaced.
    if( orig_string_size != obj_rep.size() )
    {
      // Find the start of an element
      elem_start_pos = obj_rep.find( "{" );

      if( elem_start_pos < obj_rep.size() )
        ++elem_start_pos;
      else
        elem_start_pos = 0;

      orig_string_size = obj_rep.size();
    }
    else
    {
      // Move the the next element
      elem_start_pos = elem_end_pos+1;
    }

    // Find the end of an element
    elem_end_pos = obj_rep.find_first_of( ",}", elem_start_pos );
    
    if( elem_end_pos > obj_rep.size() )
      elem_end_pos = obj_rep.size();

    
    Details::expandPiKeywordInSubstring( elem_start_pos,
                                         elem_end_pos - 1,
                                         obj_rep );
  }while( elem_end_pos < obj_rep.size() );
}
  
namespace Details{

// Replace occurances of interval keyword within a substring
inline void expandIntervalKeywordInSubstring( const std::string& left_element,
                                              std::string& middle_element,
                                              const std::string& right_element )
{
  bool raw_left_element = left_element.find( "," ) > left_element.size();
  bool raw_right_element = right_element.find( "," ) > right_element.size();

  std::string::size_type op_pos;

  if( middle_element.find( "pi" ) >= middle_element.size() )
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

    double left_value = Utility::fromString<double>( left_element );
    double right_value = Utility::fromString<double>( right_element );

    TEST_FOR_EXCEPTION( left_value > right_value,
			std::runtime_error,
			"the array elements must be in ascending order ("
                        << left_value << " !<= " << right_value << ")!" );

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
      double step_size = (right_value-left_value)/intervals;

      // Replace the interval keyword with the new elements
      middle_element = " ";

      for( size_t i = 1; i < intervals; ++i )
      {
	std::ostringstream oss;
	oss.precision( 18 );

	oss << left_value + step_size*i;

	middle_element += oss.str();

	if( i < intervals-1 )
	  middle_element += ", ";
      }
    }
    // Log increments
    else 
    {
      TEST_FOR_EXCEPTION( left_value <= 0.0,
			  std::runtime_error,
			  "the starting value ( " << left_value <<
                          ") must be positive when using the log interval "
                          "keyword 'l'!" );

      double step_size = log(right_value/left_value)/intervals;

      // Replace the interval keyword with the new elements
      middle_element = " ";

      for( size_t i = 1; i < intervals; ++i )
      {
	std::ostringstream oss;
	oss.precision( 18 );

	oss << exp( log(left_value) + step_size*i );

	middle_element += oss.str();

	if( i < intervals-1 )
	  middle_element += ", ";
      }
    }
  }
}

} // end Details namespace

// Expand interval keywords in string
inline void expandIntervalKeywords( std::string& obj_rep )
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

  std::string::size_type bracket_pos = array_elements.front().find( "{" );

  if( bracket_pos < array_elements.front().size() )
    array_elements.front().erase( bracket_pos, 1 );

  bracket_pos = array_elements.back().find( "}" );

  if( bracket_pos < array_elements.back().size() )
    array_elements.back().erase( bracket_pos, 1 );

  for( size_t i = 1; i < array_elements.size()-1; ++i )
  {
    // We want the 'i' and 'l' keywords to be case insensitive
    boost::algorithm::to_lower( array_elements[i] );
    
    Details::expandIntervalKeywordInSubstring(
                      boost::algorithm::to_lower_copy( array_elements[i-1] ),
                      array_elements[i],
                      boost::algorithm::to_lower_copy( array_elements[i+1] ) );
  }

  // Reconstruct the array string
  obj_rep = "{";
  obj_rep += array_elements.front();

  for( unsigned i = 1; i < array_elements.size(); ++i )
  {
    obj_rep += ",";
    obj_rep += array_elements[i];
  }

  obj_rep += "}";
}
  
} // end Utility namespace

#endif // end UTILITY_FROM_STRING_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_FromStringTraits.hpp
//---------------------------------------------------------------------------//
