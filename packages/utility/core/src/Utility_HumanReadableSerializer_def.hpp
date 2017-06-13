//---------------------------------------------------------------------------//
//!
//! \file   Utility_HumanReadableSerializer_def.hpp
//! \author Alex Robinson
//! \brief  The human-readable serializer class partial specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HUMAN_READABLE_SERIALIZER_DEF_HPP
#define UTILITY_HUMAN_READABLE_SERIALIZER_DEF_HPP

// Std Lib Includes
#include <sstream>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <vector>

// Boost Includes
#include <boost/type_traits/is_base_of.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "Utility_ParameterListCompatibleObject.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace Utility{

namespace Details{

//! Initialize the input stream that will be used to deserialize an object
void initializeInputStream( std::istream& is, const char start_delim )
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

/*! Move the input stream to the start of the next element
 * \details True will be returned when all elements have been read (i.e. the
 * end deliminator has been reached).
 */
bool moveInputStreamToNextElement( std::istream& is,
                                   const char elem_delim,
                                   const char end_delim )
{
  // Search for the specified element deliminator
  char delim;
  
  while( true )
  {
    is.get( delim );

    TEST_FOR_EXCEPTION( !is,
                        std::runtime_error,
                        "Unable to move the input stream to the next element "
                        "(EOF reached unexpectedly)!" );

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
  
} // end Details namespace

//! Specialization of the human-readable serializer class for std::string
template<>
struct HumanReadableSerializer<std::string>
{
  //! Serialize the object
  static inline void serialize( std::ostream& os, const std::string& obj )
  { os << obj; }
  
  //! Serialize the object
  static inline std::string serialize( const std::string& obj )
  { return obj; }

  //! Deserialize the object
  static inline std::string deserialize( const std::string& obj_string )
  { return obj_string; }

  //! Deserialize the object
  static inline std::string deserialize( std::istream& is,
                                         const std::string& delims = std::string() )
  {
    std::string obj;

    if( delims.size() > 0 )
    {
      bool done = false;
      
      while( !done )
      {
        char string_element;
        is.get( string_element );

        TEST_FOR_EXCEPTION( !is,
                            std::runtime_error,
                            "Unable to get the string element (EOF reached "
                            "unexpectedly)!" );

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
    }
    // No deliminators have been specified - use a space
    else
      std::getline( is, obj, ' ' );

    return Teuchos::Utils::trimWhiteSpace( obj );
  }
};

//! Specialization of the human-readable serializer class for float
template<>
struct HumanReadableSerializer<float>
{
  //! Serialize the object
  static inline void serialize( std::ostream& os, const float& obj )
  {
    // Make sure that we use enough decimal places to capture the full
    // precision of the float
    os.setf( std::ios::scientific );
    os.precision( 9 );
    
    os << obj;
  }
  
  //! Serialize the object
  static inline std::string serialize( const float& obj )
  {
    std::ostringstream oss;
    serialize( oss, obj );

    return oss.str();
  }

  //! Deserialize the object
  static inline float deserialize( const std::string& obj_string )
  {
    std::istringstream iss( obj_string );

    return deserialize( iss );
  }

  //! Deserialize the object
  static inline float deserialize( std::istream& is,
                                    const std::string& = std::string() )
  {
    float obj;
     
    is >> obj;

    return obj;
  }
};

//! Specialization of the human-readable serializer class for double
template<>
struct HumanReadableSerializer<double>
{
  //! Serialize the object
  static inline void serialize( std::ostream& os, const double& obj )
  {
    // Make sure that we use enough decimal places to capture the full
    // precision of the double
    os.setf( std::ios::scientific );
    os.precision( 18 );
    
    os << obj;
  }
  
  //! Serialize the object
  static inline std::string serialize( const double& obj )
  {
    std::ostringstream oss;
    serialize( oss, obj );

    return oss.str();
  }

  //! Deserialize the object
  static inline double deserialize( const std::string& obj_string )
  {
    std::istringstream iss( obj_string );

    return deserialize( iss );
  }

  //! Deserialize the object
  static inline double deserialize( std::istream& is,
                                    const std::string& = std::string() )
  {
    double obj;
     
    is >> obj;

    return obj;
  }
};

//! Specialization of the human-readable serializer class for integral types
template<typename T>
struct HumanReadableSerializer<T,typename std::enable_if<std::is_integral<T>::value>::type>
{
  //! Serialize the object
  static inline void serialize( std::ostream& os, const T& obj )
  { os << obj; }
  
  //! Serialize the object
  static inline std::string serialize( const T& obj )
  {
    std::ostringstream oss;
    serialize( oss, obj );

    return oss.str();
  }

  //! Deserialize the object
  static inline T deserialize( const std::string& obj_string )
  {
    std::istringstream iss( obj_string );

    return deserialize( iss );
  }

  //! Deserialize the object
  static inline T deserialize( std::istream& is,
                               const std::string& = std::string() )
  {
    T obj;
     
    is >> obj;

    return obj;
  }
};

/*! \brief Specialization of the human-readable serializer class for types that
 * inherit from Utility::ParameterListCompatibleObject
 */
template<typename T>
struct HumanReadableSerializer<T,typename std::enable_if<boost::is_base_of<ParameterListCompatibleObject<T>,T>::value>::type>
{
  //! Serialize the object
  static inline void serialize( std::ostream& os, const T& obj )
  { obj.toStream( os ); }
  
  //! Serialize the object
  static inline std::string serialize( const T& obj )
  {
    std::ostringstream oss;
    serialize( oss, obj );

    return oss.str();
  }

  //! Deserialize the object
  static inline T deserialize( const std::string& obj_string )
  {
    std::istringstream iss( obj_string );

    return deserialize( iss );
  }

  //! Deserialize the object
  static inline T deserialize( std::istream& is,
                               const std::string& = std::string() )
  {
    T obj;

    obj.fromStream( is );

    return obj;
  }
};

namespace Details{

//! The helper class for stream i/o ops with tuples
template<size_t I, typename TupleType, typename Enable = void>
struct TupleStreamHelper
{
  static inline void toStream( std::ostream& os, const TupleType& tuple )
  { 
    // Serialize the tuple element
    Utility::HumanReadableSerializer<typename Utility::TupleElement<I,TupleType>::type>::serialize( os, Utility::get<I>( tuple ) );
    
    os << ", ";

    // Serialize the remaining tuple elements
    TupleStreamHelper<I+1,TupleType>::toStream( os, tuple );
  }

  static inline void fromStream( std::istream& is, TupleType& tuple )
  {
    // Deserialize the tuple element
    try{
      Utility::get<I>( tuple ) = HumanReadableSerializer<typename Utility::TupleElement<I,TupleType>::type>::deserialize( is, ",}" );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Tuple element " << I << " was not "
                             "successfully deserialized!" );

    // Position the stream at the start of the next element (or end)
    try{
      Details::moveInputStreamToNextElement( is, ',', '}' );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Could not move the input stream to the next "
                             "element (last tuple element successfully "
                             "deserialized = " << I << ")!" );

    // Deserialize the remaining tuple elements
    TupleStreamHelper<I+1,TupleType>::fromStream( is, tuple );
  }
};

/*! \brief The helper class for stream i/o ops with tuples
 * (specialization for I == TupleSize-1, which is for the last element)
 */
template<size_t I, typename TupleType>
struct TupleStreamHelper<I, TupleType, typename std::enable_if<I==TupleSize<TupleType>::value-1>::type>
{
  static inline void toStream( std::ostream& os, const TupleType& tuple )
  {
    // Serialize the tuple element
    Utility::HumanReadableSerializer<typename Utility::TupleElement<I,TupleType>::type>::serialize( os, Utility::get<I>( tuple ) );
  }

  static inline void fromStream( std::istream& is, TupleType& tuple )
  {
    // Deserialize the tuple element
    try{
      Utility::get<I>( tuple ) = HumanReadableSerializer<typename Utility::TupleElement<I,TupleType>::type>::deserialize( is, ",}" );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Tuple element " << I << " was not "
                             "successfully deserialized!" );

    // Position the stream at the start of the next element (or end)
    bool at_end;
    try{
      at_end = Details::moveInputStreamToNextElement( is, ',', '}' );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Could not move the input stream to the next "
                             "element (last tuple element successfully "
                             "deserialized = " << I << ")!" );

    TEST_FOR_EXCEPTION( !at_end,
                        std::runtime_error,
                        "Finished deserializing tuple before the end of the "
                        "stream was reached!" );
  }
};

/*! \brief The helper class for stream i/o ops with tuples
 * (specialization for I == TupleSize, which is past the last element)
 */
template<size_t I, typename TupleType>
struct TupleStreamHelper<I, TupleType, typename std::enable_if<I==TupleSize<TupleType>::value>::type>
{
  static inline void toStream( std::ostream& os, const TupleType& tuple )
  { /* ... */ }

  static inline void fromStream( std::istream& is, TupleType& tuple )
  { /* ... */ }
};
  
} // end Details namespace

//! Specialization of the human-readable serializer class for Utility::Tuple
template<typename ...T>
struct HumanReadableSerializer<Utility::Tuple<T...> >
{
  //! Serialize the object
  static inline void serialize( std::ostream& os, const Utility::Tuple<T...>& obj )
  {
    os << '{';
    Utility::Details::TupleStreamHelper<0,Utility::Tuple<T...> >::toStream( os, obj );
    os << '}';
  }
  
  //! Serialize the object
  static inline std::string serialize( const Utility::Tuple<T...>& obj )
  {
    std::ostringstream oss;
    serialize( oss, obj );

    return oss.str();
  }

  //! Deserialize the object
  static inline Utility::Tuple<T...> deserialize( const std::string& obj_string )
  {
    std::istringstream iss( obj_string );

    return deserialize( iss );
  }

  //! Deserialize the object
  static inline Utility::Tuple<T...> deserialize( std::istream& is,
                                                  const std::string& = std::string() )
  {
    // Initialie the input stream
    Details::initializeInputStream( is, '{' );

    Utility::Tuple<T...> obj;
    
    Utility::Details::TupleStreamHelper<0,Utility::Tuple<T...> >::fromStream( is, obj );

    return obj;
  }
};

//! Specialization of the human-readable serializer class for std::pair
template<typename T1, typename T2>
struct HumanReadableSerializer<std::pair<T1,T2> >
{
  //! Serialize the object
  static inline void serialize( std::ostream& os, const std::pair<T1,T2>& obj )
  {
    os << '{';
    Utility::Details::TupleStreamHelper<0,std::pair<T1,T2> >::toStream( os, obj );
    os << '}';
  }
  
  //! Serialize the object
  static inline std::string serialize( const std::pair<T1,T2>& obj )
  {
    std::ostringstream oss;
    serialize( oss, obj );

    return oss.str();
  }

  //! Deserialize the object
  static inline std::pair<T1,T2> deserialize( const std::string& obj_string )
  {
    std::istringstream iss( obj_string );

    return deserialize( iss );
  }

  //! Deserialize the object
  static inline std::pair<T1,T2> deserialize( std::istream& is,
                                              const std::string& = std::string() )
  {
    // Initialie the input stream
    Details::initializeInputStream( is, '{' );

    std::pair<T1,T2> obj;
    
    Utility::Details::TupleStreamHelper<0,std::pair<T1,T2> >::fromStream( is, obj );

    return obj;
  }
};

namespace Details{

//! The helper class for stream i/o ops with arrays
template<template<typename,typename...> class Array, typename T>
struct ArrayStreamHelper
{
  static inline void toStream( std::ostream& os, const Array<T>& array )
  { 
    os << "{";

    for( size_t i = 0; i < array.size(); ++i )
    {
      os << Utility::HumanReadableSerializer<T>::serialize( array[i] );

      if( i < array.size() - 1 )
        os << ", ";
    }

    os << "}";
  }

  static inline void fromStream( std::istream& is, Array<T>& array )
  {
    // Initialize the input stream
    Details::initializeInputStream( is, '{' );
    
    // Deserialize the array element-by-element
    bool done = false;
    
    while( !done )
    {
      T element;
      
      try{
        element = Utility::HumanReadableSerializer<T>::deserialize( is, ",}" );
      }
      EXCEPTION_CATCH_RETHROW( std::runtime_error,
                               "Array element " << array.size() << " was "
                               "not successfully deserialized!" );

      // An error has occurred in the stream
      TEST_FOR_EXCEPTION( !is,
                          std::runtime_error,
                          "An error has occurred in the stream (last array "
                          "element successfully deserialized = "
                          << array.size() << ")!" );

      // The element was successfully deserialized
      array.push_back( element );

      // Position the stream at the start of the next element (or end)
      try{
        done = Details::moveInputStreamToNextElement( is, ',', '}' );
      }
      EXCEPTION_CATCH_RETHROW( std::runtime_error,
                               "Could not move the input stream to the next "
                               "element (last array element successfully "
                               "deserialized = " << array.size()-1 << ")!" );
    }
  }
};
  
} // end Details namespace

//! Specialization of the human-readable serializer class for std::vector
template<typename T>
struct HumanReadableSerializer<std::vector<T> >
{
  //! Serialize the object
  static inline void serialize( std::ostream& os, const std::vector<T>& obj )
  {
    Details::ArrayStreamHelper<std::vector,T>::toStream( os, obj );
  }
  
  //! Serialize the object
  static inline std::string serialize( const std::vector<T>& obj )
  {
    std::ostringstream oss;
    serialize( oss, obj );

    return oss.str();
  }

  //! Deserialize the object
  static inline std::vector<T> deserialize( const std::string& obj_string )
  {
    std::istringstream iss( obj_string );

    return deserialize( iss );
  }

  //! Deserialize the object
  static inline std::vector<T> deserialize( std::istream& is,
                                            const std::string& = std::string() )
  {
    std::vector<T> obj;

    Details::ArrayStreamHelper<std::vector,T>::fromStream( is, obj );

    return obj;
  }
};

//! Specialization of the human-readable serializer class for Teuchos::Array
template<typename T>
struct HumanReadableSerializer<Teuchos::Array<T> >
{
  //! Serialize the object
  static inline void serialize( std::ostream& os, const Teuchos::Array<T>& obj )
  {
    Details::ArrayStreamHelper<Teuchos::Array,T>::toStream( os, obj );
  }
  
  //! Serialize the object
  static inline std::string serialize( const Teuchos::Array<T>& obj )
  {
    std::ostringstream oss;
    serialize( oss, obj );

    return oss.str();
  }

  //! Deserialize the object
  static inline Teuchos::Array<T> deserialize( const std::string& obj_string )
  {
    std::istringstream iss( obj_string );

    return deserialize( iss );
  }

  //! Deserialize the object
  static inline Teuchos::Array<T> deserialize( std::istream& is,
                                            const std::string& = std::string() )
  {
    Teuchos::Array<T> obj;

    Details::ArrayStreamHelper<Teuchos::Array,T>::fromStream( is, obj );

    return obj;
  }
};

//! Specialization of the human-readable serializer class for Teuchos::ArrayRCP
template<typename T>
struct HumanReadableSerializer<Teuchos::ArrayRCP<T> >
{
  //! Serialize the object
  static inline void serialize( std::ostream& os, const Teuchos::ArrayRCP<T>& obj )
  {
    Details::ArrayStreamHelper<Teuchos::ArrayRCP,T>::toStream( os, obj );
  }
  
  //! Serialize the object
  static inline std::string serialize( const Teuchos::ArrayRCP<T>& obj )
  {
    std::ostringstream oss;
    serialize( oss, obj );

    return oss.str();
  }

  //! Deserialize the object
  static inline Teuchos::ArrayRCP<T> deserialize( const std::string& obj_string )
  {
    std::istringstream iss( obj_string );

    return deserialize( iss );
  }

  //! Deserialize the object
  static inline Teuchos::ArrayRCP<T> deserialize( std::istream& is,
                                                  const std::string& = std::string() )
  {
    Teuchos::Array<T> obj;

    Details::ArrayStreamHelper<Teuchos::Array,T>::fromStream( is, obj );

    Teuchos::ArrayRCP<T> rcp_obj;
    rcp_obj.assign( obj.begin(), obj.end() );

    return rcp_obj;
  }
};
  
} // end Utility namespace

namespace std{

//! Output stream operator overload for Utility::Tuple
template<typename ...T>
std::ostream& operator<<( std::ostream& os, const Utility::Tuple<T...>& obj )
{
  Utility::HumanReadableSerializer<Utility::Tuple<T...> >::serialize( os, obj );
  return os;
}

//! Output stream operator overload for std::pair
template<typename T1, typename T2>
std::ostream& operator<<( std::ostream& os, const std::pair<T1,T2>& obj )
{
  Utility::HumanReadableSerializer<std::pair<T1,T2> >::serialize( os, obj );
  return os;
}

//! Output stream operator overload for std::vector
template<typename T>
std::ostream& operator<<( std::ostream& os, const std::vector<T>& obj )
{
  Utility::HumanReadableSerializer<std::vector<T> >::serialize( os, obj );
  return os;
}
  
} // end std namespace

#endif // end UTILITY_HUMAN_READABLE_SERIALIZER_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_HumanReadableSerializer_def.hpp
//---------------------------------------------------------------------------//
