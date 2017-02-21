//---------------------------------------------------------------------------//
//!
//! \file   Utility_Tuple.hpp
//! \author Alex Robinson
//! \brief  Simple struct for storing objects of arbitrary type
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TUPLE_HPP
#define UTILITY_TUPLE_HPP

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>

/*! \defgroup tuple Tuple.
 *
 * There were originally some homebrew tuple classes (Pair, Trip, Quad)
 * defined in the Utility_Tuple.hpp header file. Since moving to C++11 the 
 * std::tuple variadic template class and helper functions has made these 
 * classes obsolete. To provide backwards compatibility, the Utility_Tuple.hpp
 * header file provides aliases with Pair, Trip and Quad names that use the 
 * std::tuple class. There are some additional helper functions that have
 * been defined that do not appear in the std library. Use Utility::get
 * instead of std::get when accessing tuple elements since some additional
 * useful overloads have been provided. All other std lib tuple helper
 * functions can be used.
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

/*! The pair struct
 * \ingroup tuple
 */
template<typename T1, typename T2> using Pair = std::tuple<T1,T2>;

/*! The trip struct
 * \ingroup tuple
 */
template<typename T1, typename T2, typename T3> using Trip =
  std::tuple<T1,T2,T3>;

/*! The quad struct
 * \ingroup tuple
 */
template<typename T1, typename T2, typename T3, typename T4> using Quad =
  std::tuple<T1,T2,T3,T4>;

/*! The generic tuple struct
 * \ingroup tuple
 */
template<typename... Types> using Tuple = std::tuple<Types...>;

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
inline typename TupleElement<I,Utility::Tuple<Types...> >::type&
get( Utility::Tuple<Types...>& tuple ) noexcept
{ return std::get<I>( tuple ); }

/*! Return a const reference to the desired tuple element (std::get)
 * \ingroup tuple
 */
template<size_t I, typename... Types>
inline const typename TupleElement<I,Utility::Tuple<Types...> >::type&
get( const Utility::Tuple<Types...>& tuple ) noexcept
{ return std::get<I>( tuple ); }

/*! Set the head tuple member value
 *
 * The ValueType must be implicitly convertable to the tuple member type.
 * \ingroup tuple
 */
template<size_t I, typename TupleType, typename ValueType>
void set( TupleType& tuple, ValueType value );

/*! Construct a tuple (std::make_tuple)
 * \ingroup tuple
 */
template<typename... Types>
inline auto makeTuple( Types&&... args ) -> decltype(std::make_tuple(args...))
{ return std::make_tuple( args... ); }

/*! Convert the tuple to a string
 * \ingroup tuple
 */
template<typename... Types>
std::string tupleToString( const Utility::Tuple<Types...>& tuple );

/*! Place the tuple in a stream
 * \ingroup tuple
 */
template<typename... Types>
void tupleToStream( std::ostream&os, const Utility::Tuple<Types...>& tuple );

} // end Utility namespace

namespace std{

/*! Stream operator for tuples
 * \ingroup tuple
 * \ingroup print_format
 */
template<typename... Types>
inline std::ostream& operator<<( std::ostream& os,
                                 const Utility::Tuple<Types...>& tuple )
{
  Utility::tupleToStream( os, tuple );
  
  return os;
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
