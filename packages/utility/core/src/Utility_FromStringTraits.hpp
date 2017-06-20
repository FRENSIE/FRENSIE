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
#include <string>
#include <type_traits>
#include <iterator>
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
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/trim.hpp>

// FRENSIE Includes
#include "Utility_FromStringTraitsDecl.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace Utility{
  
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
                            std::runtime_error,
                            "Unable to get the string element (EOF reached "
                            "unexpectedly)!" );

        TEST_FOR_EXCEPTION( !is,
                            std::runtime_error,
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
                        std::runtime_error,
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
        THROW_EXCEPTION( std::runtime_error,
                         "Cannot extract a char from the stream (the current "
                         "element has more than one character)!" );
      }
    }
    else
      is.get( obj );
  }
};

/*! Specialization of FromStringTraits for bool
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
      THROW_EXCEPTION( std::runtime_error,
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

/*! Partial specialization of FromStringTraits for arithmetic types
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<T,typename std::enable_if<std::is_arithmetic<T>::value>::type>
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
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Tuple element " << I << " was not successfully "
                             "extracted from the input stream!" );

    // Position the stream at the start of the next element (or end)
    try{
      Utility::moveInputStreamToNextElement( is, ',', '}' );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
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
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Tuple element " << I << " was not "
                             "successfully extracted from the input stream!" );

    // Position the stream at the start of the next element (or end)
    bool at_end;
    try{
      at_end = Utility::moveInputStreamToNextElement( is, ',', '}' );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Could not move the input stream to the next "
                             "element (last tuple element successfully "
                             "extracted = " << I << ")!" );

    TEST_FOR_EXCEPTION( !at_end,
                        std::runtime_error,
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
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
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

//! FromStringTraits base helper class for stl compliant containers
template<typename STLCompliantContainer,
         typename ReturnContainerType = STLCompliantContainer>
struct FromStringTraitsSTLCompliantContainerBaseHelper
{
  //! The type that a string will be converted to
  typedef ReturnContainerType ReturnType;

protected:
  
  //! Convert the string to the required container type
  template<typename ElementInsertionMemberFunction>
  static inline ReturnType fromStringImpl( const std::string& obj_rep,
                                           ElementInsertionMemberFunction insert_element )
  {
    ReturnType container;

    std::istringstream iss( obj_rep );

    FromStringTraitsSTLCompliantContainerBaseHelper<ReturnType>::fromStreamImpl( iss, container, insert_element );

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
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Could not extract a tuple from the stream!" );

    // Extract each element of the array
    bool done = false;
    size_t element_index = 0;

    while( !done )
    {
      typename STLCompliantContainer::value_type element;

      try{
        Utility::fromStream( is, element, ",}" );
      }
      EXCEPTION_CATCH_RETHROW( std::runtime_error,
                               "Element " << element_index << " was not "
                               "successfully extracted from the stream!" );

      // Check if the stream is still valid
      TEST_FOR_EXCEPTION( is.eof(),
                          std::runtime_error,
                          "Unable to get element " << element_index << " (EOF "
                          "reached unexpectedly)!" );

      TEST_FOR_EXCEPTION( !is,
                          std::runtime_error,
                          "Unable to get element " << element_index << " (one "
                          "or more error flags have been set)!" );

      // The element has been successfully extracted
      (obj.*insert_element)( element );
      ++element_index;
      
      // Position the stream at the start of the next element (or end)
      try{
        done = Utility::moveInputStreamToNextElement( is, ',', '}' );
      }
      EXCEPTION_CATCH_RETHROW( std::runtime_error,
                               "Could not move the input stream to the next "
                               "element (" << element_index << ")!" );
    }
  }
};

/*! \brief FromStringTraits helper class for stl compliant containers with a
 * push_back method.
 */
template<typename STLCompliantContainer,
         typename ReturnContainerType = STLCompliantContainer>
struct FromStringTraitsSTLCompliantContainerPushBackHelper : public FromStringTraitsSTLCompliantContainerBaseHelper<STLCompliantContainer,ReturnContainerType>
{
  //! The base helper class type
  typedef FromStringTraitsSTLCompliantContainerBaseHelper<STLCompliantContainer,ReturnContainerType> BaseType;
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
         typename ReturnContainerType = STLCompliantContainer>
struct FromStringTraitsSTLCompliantContainerInsertHelper : public FromStringTraitsSTLCompliantContainerBaseHelper<STLCompliantContainer,ReturnContainerType>
{
  //! The base helper class type
  typedef FromStringTraitsSTLCompliantContainerBaseHelper<STLCompliantContainer,ReturnContainerType> BaseType;
  //! The type that a string will be converted to
  typedef typename BaseType::ReturnType ReturnType;

  //! Convert the string to an object of the container type
  static inline ReturnType fromString( const std::string& obj_rep )
  {
    return BaseType::fromStringImpl( obj_rep, &ReturnType::insert );
  }

  //! Extract the object from a stream
  static inline void fromStream( std::istream& is,
                                 STLCompliantContainer& obj,
                                 const std::string& = std::string() )
  {
    BaseType::fromStreamImpl( is, obj, &STLCompliantContainer::insert );
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
struct FromStringTraits<std::forward_list<T> > : public Details::FromStringTraitsSTLCompliantContainerBaseHelper<std::forward_list<T> >
{
  //! The base helper class type
  typedef Details::FromStringTraitsSTLCompliantContainerBaseHelper<std::forward_list<T> > BaseType;
  //! The type that a string will be converted to
  typedef typename BaseType::ReturnType ReturnType;

  //! Convert the string to an object of the container type
  static inline ReturnType fromString( const std::string& obj_rep )
  {
    ReturnType container =
      BaseType::fromStringImpl( obj_rep, &ReturnType::push_front );

    container.reverse();

    return container;
  }

  //! Extract the object from a stream
  static inline void fromStream( std::istream& is,
                                 std::forward_list<T>& obj,
                                 const std::string& = std::string() )
  {
    BaseType::fromStreamImpl( is, obj, &std::forward_list<T>::push_front );

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
struct FromStringTraits<std::map<Key,T> > : public Details::FromStringTraitsSTLCompliantContainerInsertHelper<std::map<Key,T> >
{ /* ... */ };

/*! Partial specialization of FromStringTraits for std::unordered_map
 * \ingroup from_string_traits
 */
template<typename Key, typename T>
struct FromStringTraits<std::unordered_map<Key,T> > : public Details::FromStringTraitsSTLCompliantContainerInsertHelper<std::unordered_map<Key,T> >
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
  
} // end Utility namespace

#endif // end UTILITY_FROM_STRING_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_FromStringTraits.hpp
//---------------------------------------------------------------------------//
