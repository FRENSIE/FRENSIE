//---------------------------------------------------------------------------//
//!
//! \file   Utility_Tuple_def.hpp
//! \author Alex Robinson
//! \brief  Simple struct for storing objects of arbitrary type
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TUPLE_DEF_HPP
#define UTILITY_TUPLE_DEF_HPP

// Std Lib Includes
#include <type_traits>

// Boost Includes
#include <boost/units/quantity.hpp>

// FRENSIE Includes
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace Utility{

/*! \brief Specialization of TupleElement for all const types
 * \ingroup tuple
 */
template<size_t I, typename T>
struct TupleElement<I, const T>
{
  typedef typename std::add_const<typename TupleElement<I,T>::type>::type type;
};

/*! \brief Specialization of TupleElement for all volatile types
 * \ingroup tuple
 */
template<size_t I, typename T>
struct TupleElement<I, volatile T>
{
  typedef typename std::add_volatile<typename TupleElement<I,T>::type>::type type;
};

/*! \brief Specialization of TupleElement for all const volatile types
 * \ingroup tuple
 */
template<size_t I, typename T>
struct TupleElement<I, const volatile T>
{
  typedef typename std::add_cv<typename TupleElement<I,T>::type>::type type;
};

/*! \brief Specialization of TupleElement for all arithmetic types
 *
 * Unlike std::tuple_element, this specialization allows one to create
 * methods that take both std::tuple types and arithmetic types (Utility::get
 * must also be used instead of std::get). See the 
 * Utility::Search::binaryLowerBound method for an example.
 * \ingroup tuple
 */
template<typename T>
struct TupleElement<0,T,typename std::enable_if<std::is_arithmetic<T>::value>::type>
{ typedef T type; };

/*! \brief Specialization of TupleElement for boost::units::quantity<Unit,T> 
 * types
 * \ingroup tuple
 */
template<typename Unit, typename T>
struct TupleElement<0,boost::units::quantity<Unit,T> >
{ typedef boost::units::quantity<Unit,T> type; };

/*! \brief Specialization of TupleSize for all const types
 * \ingroup tuple
 */
template<typename T>
struct TupleSize<const T> : public TupleSize<T>
{ /* ... */ };

/*! \brief Specialization of TupleSize for all volatile types
 * \ingroup tuple
 */
template<typename T>
struct TupleSize<volatile T> : public TupleSize<T>
{ /* ... */ };

/*! \brief Specialization of TupleSize for all const volatile types
 * \ingroup tuple
 */
template<typename T>
struct TupleSize<const volatile T> : public TupleSize<T>
{ /* ... */ };

/*! \brief Specialization of TupleSize for all arithmetic types
 *
 * Unlike std::tuple_size, this specialization allows one to create
 * methods that take both std::tuple types and arithmetic types (Utility::get
 * must also be used instead of std::get). See the 
 * Utility::Search::binaryLowerBound method for an example.
 * \ingroup tuple
 */
template<typename T>
struct TupleSize<T,typename std::enable_if<std::is_arithmetic<T>::value>::type> : public std::integral_constant<size_t,1>
{ /* ... */ };

/*! \brief Specialization of TupleSize for boost::units::quantity<Unit,T> types
 * \ingroup tuple
 */
template<typename Unit,typename T>
struct TupleSize<boost::units::quantity<Unit,T> > : public std::integral_constant<size_t,1>
{ /* ... */ };

/*! Return a reference to the desired tuple member 
 *
 * This can be used with native (arithmetic) types 
 * (e.g. Utility::get<0>( double )).
 * \ingroup tuple
 */
template<size_t I, typename Tuple>
inline typename std::enable_if<I==0 && std::is_arithmetic<Tuple>::value,Tuple&>::type
get( Tuple& tuple )
{ return tuple; }

/*! Return a const reference to the desired tuple member 
 *
 * This can be used with native (arithmetic) types 
 * (e.g. Utility::get<0>( double )).
 * \ingroup tuple
 */
template<size_t I, typename Tuple>
inline typename std::enable_if<I==0 && std::is_arithmetic<Tuple>::value,const Tuple&>::type
get( const Tuple& tuple )
{ return tuple; }

/*! Return a reference to the desired tuple member
 *
 * This can be used with boost::units::quantity<Unit,T>
 * \ingroup tuple
 */
template<size_t I, typename Unit, typename T>
inline typename std::enable_if<I==0,boost::units::quantity<Unit,T>&>::type
get( boost::units::quantity<Unit,T>& tuple )
{ return tuple; }

/*! Return a const reference to the desired tuple member
 *
 * This can be used with boost::units::quantity<Unit,T>
 * \ingroup tuple
 */
template<size_t I, typename Unit, typename T>
inline typename std::enable_if<I==0,const boost::units::quantity<Unit,T>&>::type
get( const boost::units::quantity<Unit,T>& tuple )
{ return tuple; }

// Set the head tuple member value
template<size_t I, typename TupleType, typename ValueType>
inline void set( TupleType& tuple, ValueType value )
{ Utility::get<I>( tuple ) = value; }

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
 * (specialization for I == std::tuple_size-1, which is for the last element)
 */
template<size_t I, typename TupleType>
struct TupleStreamHelper<I, TupleType, typename std::enable_if<I==std::tuple_size<TupleType>::value-1>::type>
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
 * (specialization for I == std::tuple_size, which is past the last element)
 */
template<size_t I, typename TupleType>
struct TupleStreamHelper<I, TupleType, typename std::enable_if<I==std::tuple_size<TupleType>::value>::type>
{
  static inline void toStream( std::ostream& os, const TupleType& tuple )
  { /* ... */ }

  static inline void fromStream( std::istream& is, TupleType& tuple )
  { /* ... */ }
};

} // end Details namespace

// Convert the tuple to a string
template<typename... Types>
inline std::string ToStringTraits<std::tuple<Types...> >::toString(
                                            const std::tuple<Types...>& tuple )
{
  std::ostringstream oss;
  
  ToStringTraits<std::tuple<Types...> >::toStream( oss, tuple );
  
  return oss.str();
}

// Place the tuple in a stream
template<typename... Types>
inline void ToStringTraits<std::tuple<Types...> >::toStream(
                                            std::ostream& os,
                                            const std::tuple<Types...>& tuple )
{
  os << '{';
  Details::TupleStreamHelper<0,std::tuple<Types...> >::toStream( os, tuple);
  os << '}';
}


// Convert the string to an object of type T
template<typename... Types>
inline auto FromStringTraits<std::tuple<Types...> >::fromString(
                                     const std::string& obj_rep ) -> ReturnType
{
  std::istringstream iss( obj_rep );

  ReturnType obj;

  FromStringTraits<ReturnType>::fromStream( iss, obj );

  return obj;
}

// Extract the object from a stream
template<typename... Types>
inline void FromStringTraits<std::tuple<Types...> >::fromStream(
                                                     std::istream& is,
                                                     std::tuple<Types...>& obj,
                                                     const std::string& )
{ 
  try{
    // Initialize the input stream
    Utility::initializeInputStream( is, '{' );
    
    Details::TupleStreamHelper<0,std::tuple<Types...> >::fromStream( is, obj );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                              Utility::StringConversionException,
                              "Could not extract a tuple from the stream!" );
}

// Convert the tuple to a string
template<typename T1, typename T2>
inline std::string ToStringTraits<std::pair<T1,T2> >::toString(
                                                 const std::pair<T1,T2>& pair )
{
  auto pair_copy = std::tie( pair.first, pair.second );

  return ToStringTraits<decltype(pair_copy)>::toString( pair_copy );
}

// Place the tuple in a stream
template<typename T1, typename T2>
inline void ToStringTraits<std::pair<T1,T2> >::toStream(
                                                 std::ostream& os,
                                                 const std::pair<T1,T2>& pair )
{
  auto pair_copy = std::tie( pair.first, pair.second );
  
  ToStringTraits<decltype(pair_copy)>::toStream( os, pair_copy );
}


// Convert the string to an object of type T
template<typename T1, typename T2>
inline auto FromStringTraits<std::pair<T1,T2> >::fromString(
                                     const std::string& obj_rep ) -> ReturnType
{
  ReturnType pair;

  std::istringstream iss( obj_rep );
  
  FromStringTraits<ReturnType>::fromStream( iss, pair );
  
  return pair;
}

// Extract the object from a stream
template<typename T1, typename T2>
inline void FromStringTraits<std::pair<T1,T2> >::fromStream(
                                                         std::istream& is,
                                                         std::pair<T1,T2>& obj,
                                                         const std::string& )
{ 
  auto pair_reference = std::tie( obj.first, obj.second );

  Utility::fromStream( is, pair_reference );
}
  
} // end Utility namespace

#endif // end UTILITY_TUPLE_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_Tuple_def.hpp
//---------------------------------------------------------------------------//
