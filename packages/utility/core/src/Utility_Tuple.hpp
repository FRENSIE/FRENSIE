//---------------------------------------------------------------------------//
//!
//! \file   Utility_Tuple.hpp
//! \author Alex Robinson
//! \brief  Helper function and class declarations for std::tuple
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TUPLE_HPP
#define UTILITY_TUPLE_HPP

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <tuple>
#include <utility>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_FromStringTraits.hpp"

/*! \defgroup tuple Tuple.
 *
 * Additional helper functions and classes for use with std::tuple and
 * std::pair types have been defined that do not appear in the standard 
 * library. For example, Utility::get, Utility::TupleElement and 
 * Utility::TupleSize can all be used instead of std::get, std::tuple_element 
 * and std::tuple_size respectively to create methods that can take both tuple
 * types and arithmetic types. 
 */

namespace Utility{

/*! \brief Enum for refering to commonly used tuple elements (previously 
 * referred to as members)
 * \ingroup tuple
 */
enum TupleMember{
  FIRST = 0,
  SECOND,
  THIRD,
  FOURTH
};

/*! The tuple element struct (see std::tuple_element)
 * \ingroup tuple
 */
template<size_t I, typename T, typename Enabled = void>
struct TupleElement : public std::tuple_element<I,T>
{ /* ... */ };

/*! The tuple size struct (see std::tuple_size)
 * \ingroup tuple
 */
template<typename T, typename Enabled = void>
struct TupleSize : public std::tuple_size<T>
{ /* ... */ };

/*! Return a reference to the desired tuple element (std::get)
 * \ingroup tuple
 */
template<size_t I, typename... Types>
inline typename TupleElement<I,std::tuple<Types...> >::type&
get( std::tuple<Types...>& tuple ) noexcept
{ return std::get<I>( tuple ); }

/*! Return a const reference to the desired tuple element (std::get)
 * \ingroup tuple
 */
template<size_t I, typename... Types>
inline const typename TupleElement<I,std::tuple<Types...> >::type&
get( const std::tuple<Types...>& tuple ) noexcept
{ return std::get<I>( tuple ); }

/*! Return a reference to the desired tuple element (std::get)
 * \ingroup tuple
 */
template<size_t I, typename T1, typename T2>
inline typename TupleElement<I,std::pair<T1,T2> >::type&
get( std::pair<T1,T2>& tuple ) noexcept
{ return std::get<I>( tuple ); }

/*! Return a const reference to the desired tuple element (std::get)
 * \ingroup tuple
 */
template<size_t I, typename T1, typename T2>
inline const typename TupleElement<I,std::pair<T1,T2> >::type&
get( const std::pair<T1,T2>& tuple ) noexcept
{ return std::get<I>( tuple ); }

/*! Set the head tuple member value
 *
 * The ValueType must be implicitly convertable to the tuple member type.
 * \ingroup tuple
 */
template<size_t I, typename TupleType, typename ValueType>
void set( TupleType& tuple, ValueType value );

/*! Partial specialization of ToStringTraits for tuple types
 * \ingroup tuple
 * \ingroup to_string_traits
 */
template<typename... Types>
struct ToStringTraits<std::tuple<Types...> >
{
  //! Convert the tuple to a string
  static std::string toString( const std::tuple<Types...>& tuple );

  //! Place the tuple in a stream
  static void toStream( std::ostream& os, const std::tuple<Types...>& tuple );
};

/*! Partial specialization of FromStringTraits for std::tuple
 * \ingroup tuple
 * \ingroup from_string_traits
 */
template<typename... Types>
struct FromStringTraits<std::tuple<Types...> >
{
  //! The type that a string will be converted to
  typedef std::tuple<typename std::remove_reference<Types>::type...> ReturnType;
  
  //! Convert the string to an object of type T
  static ReturnType fromString( const std::string& obj_rep );

  //! Extract the object from a stream
  static void fromStream( std::istream& is,
                          std::tuple<Types...>& obj,
                          const std::string& = std::string() );
};

/*! Partial specialization of ToStringTraits for std::pair types
 * \ingroup tuple
 * \ingroup to_string_traits
 */
template<typename T1, typename T2>
struct ToStringTraits<std::pair<T1,T2> >
{
  //! Convert the tuple to a string
  static std::string toString( const std::pair<T1,T2>& pair );

  //! Place the tuple in a stream
  static void toStream( std::ostream& os, const std::pair<T1,T2>& pair );
};

/*! Partial specialization of FromStringTraits for std::pair
 * \ingroup tuple
 * \ingroup from_string_traits
 */
template<typename T1, typename T2>
struct FromStringTraits<std::pair<T1,T2> >
{
  //! The type that a string will be converted to
  typedef std::pair<typename std::remove_reference<T1>::type, typename std::remove_reference<T2>::type> ReturnType;
  
  //! Convert the string to an object of type T
  static ReturnType fromString( const std::string& obj_rep );

  //! Extract the object from a stream
  static void fromStream( std::istream& is,
                          std::pair<T1,T2>& obj,
                          const std::string& = std::string() );
};
  
} // end Utility namespace

namespace std{

/*! Place a std::tuple in a stream
 * \ingroup tuple
 */
template<typename... Types>
inline std::ostream& operator<<( std::ostream& os,
                                 const std::tuple<Types...>& tuple )
{
  Utility::toStream( os, tuple );

  return os;
}

/*! Extract a std::tuple from a stream
 * \ingroup tuple
 */
template<typename... Types>
inline std::istream& operator>>( std::istream& is,
                                 std::tuple<Types...>& tuple )
{
  Utility::fromStream( is, tuple );

  return is;
}

/*! Place a std::pair in a stream
 * \ingroup tuple
 */
template<typename T1, typename T2>
inline std::ostream& operator<<( std::ostream& os,
                                 const std::pair<T1,T2>& pair )
{
  Utility::toStream( os, pair );

  return os;
}

/*! Extract a std::pair from a stream
 * \ingroup tuple
 */
template<typename T1, typename T2>
inline std::istream& operator>>( std::istream& is,
                                 std::pair<T1,T2>& pair )
{
  Utility::fromStream( is, pair );

  return is;
}
  
} // end std namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Utility_Tuple_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_TUPLE_HPP

//---------------------------------------------------------------------------//
// end Utility_Tuple.hpp
//---------------------------------------------------------------------------//
