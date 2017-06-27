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
#include <tuple>
#include <utility>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

// Boost Includes
#include <boost/algorithm/string.hpp>

// FRENSIE Includes
#include "Utility_FromStringTraitsDecl.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace Utility{

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

        TEST_FOR_EXCEPTION( is.eof(),
                            Utility::StringConversionException,
                            "Unable to get the string element (EOF reached "
                            "unexpectedly)!" );

        TEST_FOR_EXCEPTION( !is,
                            Utility::StringConversionException,
                            "Unable to get the string element (one or more "
                            "error flags have been set)!" );

        for( size_t i = 0; i < delims.size(); ++i )
        {
          // A deliminator has been reached - stop reading from stream
          if( string_element == delims[i] )
          {
            done = true;

            // Put the deliminator back in the stream so that it can be
            // parsed correctly later
            is.putback( string_element );
            
            break;
          }
        }

        if( !done )
          obj.push_back( string_element );
      }

      // Trim the extracted string
      boost::algorithm::trim( obj );
    }
    // No deliminators have been specified - use the default extraction method
    else
      std::getline( is, obj );
  }
};

/*! Specialization of FromStringTraits for char
 * \ingroup from_string_traits
 */
template<>
struct FromStringTraits<char>
{
  //! The type that a string will be converted to
  typedef char ReturnType;

  //! Return the char
  static inline ReturnType fromString( const std::string& obj_rep )
  {
    TEST_FOR_EXCEPTION( obj_rep.size() != 1,
                        Utility::StringConversionException,
                        "Cannot convert the string to a char (the string has "
                        "more than one character)!" );

    return obj_rep.front();
  }

  //! Extract a char from the stream
  static inline void fromStream( std::istream& is,
                                 char& obj,
                                 const std::string& delims = std::string() )
  {
    std::string tmp_string;

    if( delims.size() > 0 )
    {
      FromStringTraits<std::string>::fromStream( is, tmp_string, delims );

      // We will assume that an empty string corresponds to a space character
      // since we are trimming white space from the string (are there cases
      // when this assumption isn't valid?).
      if( tmp_string.size() == 0 )
        obj = ' ';
      else if( tmp_string.size() == 1 )
        obj = tmp_string.front();
      else
      {
        THROW_EXCEPTION( Utility::StringConversionException,
                         "Cannot extract a char from the stream (the current "
                         "element has more than one character)!" );
      }
    }
    else
      is.get( obj );
  }
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
    std::string bool_rep;

    Utility::fromStream( is, bool_rep, delim );

    obj = FromStringTraits<bool>::fromString( bool_rep );
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
    std::string lower_case_obj_rep =
      boost::algorithm::to_lower_copy( obj_rep );

    // Check for the negative infinity keyword
    if( lower_case_obj_rep.find( "-inf" ) < lower_case_obj_rep.size() )
      return -std::numeric_limits<ReturnType>::infinity();

    // Check for the infinity keyword
    if( lower_case_obj_rep.find( "inf" ) < lower_case_obj_rep.size() )
      return std::numeric_limits<ReturnType>::infinity();

    // Check for the pi keyword
    if( lower_case_obj_rep.find( "pi" ) < lower_case_obj_rep.size() )
    {
      try{
        Utility::expandPiKeywords( lower_case_obj_rep );
      }
      EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                  Utility::StringConversionException,
                                  "Unable to replace the pi keywords!" );
    }

    std::istringstream iss( lower_case_obj_rep );

    ReturnType obj;

    iss >> obj;

    return obj;
  }

  //! Extract an object of type T from the stream
  static inline void fromStream( std::istream& is,
                                 T& obj,
                                 const std::string& delim = std::string() )
  {
    std::string obj_rep;

    Utility::fromStream( is, obj_rep, delim );

    obj = FromStringTraits<T>::fromString( obj_rep );
  }
};

/*! Partial specialization of FromStringTraits for integral types
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<T,typename std::enable_if<std::is_integral<T>::value>::type>
{
  //! The type that a string will be converted to
  typedef T ReturnType;
  
  //! Convert the string to an object of type T
  static inline ReturnType fromString( const std::string& obj_rep )
  {
    std::istringstream iss( obj_rep );

    ReturnType obj;

    FromStringTraits<ReturnType>::fromStream( iss, obj );

    return obj;
  }

  //! Extract the object from a stream
  static inline void fromStream( std::istream& is,
                                 T& obj,
                                 const std::string& = std::string() )
  { is >> obj; }
};

namespace Details{

// The helper class for stream i/o ops with tuples
template<size_t I, typename TupleType, typename Enable = void>
struct TupleFromStreamHelper
{
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
    TupleFromStreamHelper<I+1,TupleType>::fromStream( is, tuple );
  }
};

/*! \brief The helper class for stream i/o ops with tuples
 * (specialization for I == std::tuple_size-1, which is for the last element)
 */
template<size_t I, typename TupleType>
struct TupleFromStreamHelper<I, TupleType, typename std::enable_if<I==std::tuple_size<TupleType>::value-1>::type>
{
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

/*! \brief The helper class for stream i/o ops with tuples
 * (specialization for I == std::tuple_size, which is past the last element)
 */
template<size_t I, typename TupleType>
struct TupleFromStreamHelper<I, TupleType, typename std::enable_if<I==std::tuple_size<TupleType>::value>::type>
{
  static inline void fromStream( std::istream& is, TupleType& tuple )
  { /* ... */ }
};

} // end Details namespace

/*! Partial specialization of FromStringTraits for std::tuple
 * \ingroup from_string_traits
 */
template<typename... Types>
struct FromStringTraits<std::tuple<Types...> >
{
  //! The type that a string will be converted to
  typedef std::tuple<typename std::remove_reference<Types>::type...> ReturnType;
  
  //! Convert the string to an object of type T
  static inline ReturnType fromString( const std::string& obj_rep )
  {
    std::istringstream iss( obj_rep );

    ReturnType obj;

    FromStringTraits<ReturnType>::fromStream( iss, obj );

    return obj;
  }

  //! Extract the object from a stream
  static inline void fromStream( std::istream& is,
                                 std::tuple<Types...>& obj,
                                 const std::string& = std::string() )
  { 
    try{
      // Initialize the input stream
      Utility::initializeInputStream( is, '{' );

      Details::TupleFromStreamHelper<0,std::tuple<Types...> >::fromStream( is, obj );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                Utility::StringConversionException,
                                "Could not extract a tuple from the stream!" );
  }
};

/*! Partial specialization of FromStringTraits for std::pair
 * \ingroup from_string_traits
 */
template<typename T1, typename T2>
struct FromStringTraits<std::pair<T1,T2> >
{
  //! The type that a string will be converted to
  typedef std::pair<typename std::remove_reference<T1>::type, typename std::remove_reference<T2>::type> ReturnType;
  
  //! Convert the string to an object of type T
  static inline ReturnType fromString( const std::string& obj_rep )
  {
    ReturnType pair;

    std::istringstream iss( obj_rep );

    FromStringTraits<ReturnType>::fromStream( iss, pair );

    return pair;
  }

  //! Extract the object from a stream
  static inline void fromStream( std::istream& is,
                                 std::pair<T1,T2>& obj,
                                 const std::string& = std::string() )
  { 
    auto pair_reference = std::tie( obj.first, obj.second );

    Utility::fromStream( is, pair_reference );
  }
};

namespace Details{

//! FromStringTraits base helper class for stl compliant containers with general value types
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
                          "Unable to get element " << element_index << " (EOF "
                          "reached unexpectedly)!" );

      TEST_FOR_EXCEPTION( !is,
                          Utility::StringConversionException,
                          "Unable to get element " << element_index << " (one "
                          "or more error flags have been set)!" );

      // The element has been successfully extracted
      (obj.*insert_element)( element );
      ++element_index;
      
      // Position the stream at the start of the next element (or end)
      try{
        done = Utility::moveInputStreamToNextElement( is, ',', '}' );
      }
      EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                  Utility::StringConversionException,
                                  "Could not move the input stream to the next "
                                  "element (" << element_index << ")!" );
    }
  }
};

//! FromStringTraits base helper class for stl compliant containers with general value types
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

    // Extract the entire string
    std::string obj_rep;

    try{
      Utility::fromStream( is, obj_rep, "}" );
    }
    EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                             "Could not extract the object string from the "
                             "stream!" );

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
                          "Unable to get element " << element_index << " (EOF "
                          "reached unexpectedly)!" );

      TEST_FOR_EXCEPTION( !iss,
                          Utility::StringConversionException,
                          "Unable to get element " << element_index << " (one "
                          "or more error flags have been set)!" );

      // The element has been successfully extracted
      (obj.*insert_element)( element );
      ++element_index;
      
      // Position the stream at the start of the next element (or end)
      try{
        done = Utility::moveInputStreamToNextElement( iss, ',', '}' );
      }
      EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                  Utility::StringConversionException,
                                  "Could not move the input stream to the next "
                                  "element (" << element_index << ")!" );
    }

    // Position the original stream at the start of the next element (or end)
    try{
      Utility::moveInputStreamToNextElement( is, ',', '}' );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                Utility::StringConversionException,
                                "Could not move the input stream to the next "
                                "element!" );
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

/*! Partial specialization of FromStringTraits for std::vector
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<std::vector<T> > : public Details::FromStringTraitsSTLCompliantContainerPushBackHelper<std::vector<T> >
{ /* ... */ };

/*! Partial specialization of FromStringTraits for std::list
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<std::list<T> > : public Details::FromStringTraitsSTLCompliantContainerPushBackHelper<std::list<T> >
{ /* ... */ };

/*! Partial specialization of FromStringTraits for std::forward_list
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<std::forward_list<T> > : protected Details::FromStringTraitsSTLCompliantContainerBaseHelper<std::forward_list<T> >
{
protected:
  //! The base helper class type
  typedef Details::FromStringTraitsSTLCompliantContainerBaseHelper<std::forward_list<T> > BaseType;

public:
  //! The type that a string will be converted to
  typedef typename BaseType::ReturnType ReturnType;

  //! Convert the string to an object of the container type
  static inline ReturnType fromString( const std::string& obj_rep )
  {
    ReturnType container =
      BaseType::fromStringImpl( obj_rep, (void (ReturnType::*)(const typename ReturnType::value_type&))&ReturnType::push_front );

    container.reverse();

    return container;
  }

  //! Extract the object from a stream
  static inline void fromStream( std::istream& is,
                                 std::forward_list<T>& obj,
                                 const std::string& = std::string() )
  {
    BaseType::fromStreamImpl( is, obj, (void (std::forward_list<T>::*)(const typename std::forward_list<T>::value_type&))&std::forward_list<T>::push_front );

    obj.reverse();
  }
};

/*! Partial specialization of FromStringTraits for std::deque
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<std::deque<T> > : public Details::FromStringTraitsSTLCompliantContainerPushBackHelper<std::deque<T> >
{ /* ... */ };

/*! Partial specialization of FromStringTraits for std::set
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<std::set<T> > : public Details::FromStringTraitsSTLCompliantContainerInsertHelper<std::set<T> >
{ /* ... */ };

/*! Partial specialization of FromStringTraits for std::unordered_set
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<std::unordered_set<T> > : public Details::FromStringTraitsSTLCompliantContainerInsertHelper<std::unordered_set<T> >
{ /* ... */ };

/*! Partial specialization of FromStringTraits for std::map
 * \ingroup from_string_traits
 */
template<typename Key, typename T>
struct FromStringTraits<std::map<Key,T> > : public Details::FromStringTraitsSTLCompliantContainerInsertHelper<std::map<Key,T>, std::pair<Key,T>, std::map<Key,T>, std::pair<Key,T> >
{ /* ... */ };

/*! Partial specialization of FromStringTraits for std::unordered_map
 * \ingroup from_string_traits
 */
template<typename Key, typename T>
struct FromStringTraits<std::unordered_map<Key,T> > : public Details::FromStringTraitsSTLCompliantContainerInsertHelper<std::unordered_map<Key,T>, std::pair<Key,T>, std::unordered_map<Key,T>, std::pair<Key,T> >
{ /* ... */ };

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
  start_bracket = Teuchos::Utils::trimWhiteSpace( start_bracket );

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

namespace Details{

// Expand pi keyword in a substring
void expandPiKeywordInSubstring( const std::string::size_type start,
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
void expandPiKeywords( std::string& obj_rep )
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
void expandIntervalKeywordInSubstring( const std::string& left_element,
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
