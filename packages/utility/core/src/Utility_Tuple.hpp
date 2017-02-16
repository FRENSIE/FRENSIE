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
#include <string>
#include <tuple>
#include <utility>

// Boost Includes
#include <boost/mpl/and.hpp>
#include <boost/units/quantity.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/type_traits/remove_const.hpp>

/*! \defgroup tuple Tuple.
 */

namespace Utility{

/*! Struct for holding objects of arbitrary type (default - no types)
 * \ingroup tuple
 */
template<typename... Types>
struct Tuple
{
  //! Typedef for base tuple type
  typedef void RemoveHeadType;
  
  //! Constructor
  Tuple( Types... );
  
  //! Copy constructor
  template<template<typename...> class OtherTuple>
  Tuple( const OtherTuple<Types...>& );

  //! Assignment operator
  template<template<typename...> class OtherTuple>
  Tuple& operator=( const OtherTuple<Types...>& );
  
  //! Reassignment operator
  void operator()( Types... );

  //! Inequality operator
  template<template<typename...> class OtherTuple>
  bool operator!=( const OtherTuple<Types...>& );

  //! Equality operator
  template<template<typename...> class OtherTuple>
  bool operator==( const OtherTuple<Types...>& );

  //! Place the tuple in a stream
  void toStream( std::ostream&, const std::string& );
};

/*! Struct for holding objects of arbitrary type
 * \ingroup tuple
 */
template<typename T, typename... Types>
struct Tuple<T,Types...> : public Tuple<Types...>
{
  //! Typedef for base tuple type
  typedef Tuple<Types...> RemoveHeadType;
  
  //! Default constructor
  Tuple();

  //! Constructor
  Tuple( T first_value, Types... last_values );

  //! Copy constructor
  template<template<typename,typename...> class OtherTuple>
  Tuple( const OtherTuple<T,Types...>& that );

  //! Assignment operator
  template<template<typename,typename...> class OtherTuple>
  Tuple& operator=( const OtherTuple<T,Types...>& that );

  //! Reassignment operator
  void operator()( T first_value, Types... last_values );

  //! Inequality operator
  template<template<typename,typename...> class OtherTuple>
  bool operator!=( const OtherTuple<T,Types...>& that );

  //! Equality operator
  template<template<typename,typename...> class OtherTuple>
  bool operator==( const OtherTuple<T,Types...>& that );

  //! Place the tuple in a stream
  void toStream( std::ostream& os, const std::string& element_delim );

  // The head of the tuple
  T head;
};

/*! The single struct
 * \ingroup tuple
 */
template<typename T> using Single = 
  Utility::Tuple<T>;

/*! The pair struct
 * \ingroup tuple
 */
template<typename T1, typename T2> using Pair =
  Utility::Tuple<T1,T2>;

/*! The trip struct
 * \ingroup tuple
 */
template<typename T1, typename T2, typename T3> using Trip =
  Utility::Tuple<T1,T2,T3>;

/*! The quad struct
 * \ingroup tuple
 */
template<typename T1, typename T2, typename T3, typename T4> using Quad =
  Utility::Tuple<T1,T2,T3,T4>;

/*! Enum for refering to commonly used tuple members
 * \ingroup tuple
 */
enum TupleMember{
  FIRST = 0,
  SECOND,
  THIRD,
  FOURTH
};

/*! Meta function that returns the tuple member type
 *
 * Specializations must be made for this meta function struct. 
 * \ingroup tuple
 */
template<size_t k, typename TupleType, typename Enabled = void>
struct GetMemberType
{ 
  struct TupleTypeMissingSpecialization{};

  void notDefined() { TupleType::this_type_is_missing_specialization; }

  typedef TupleTypeMissingSpecialization type;
};

/*! \brief Specialization of meta function that returns the tuple member type
 * for all arithmetic types
 * \ingroup tuple
 */
template<size_t k, typename T>
struct GetMemberType<k,T,typename boost::enable_if<typename boost::mpl::and_<boost::is_same<boost::integral_constant<size_t,k>,boost::integral_constant<size_t,0> >,boost::is_arithmetic<T> >::type>::type>
{ typedef T type; };

/*! \brief Specialization of meta function that returns the tuple member type
 * for boost::units::quantity<Unit,T> types
 * \ingroup tuple
 */
template<size_t k, typename Unit, typename T>
struct GetMemberType<k,boost::units::quantity<Unit,T>,typename boost::enable_if<boost::is_same<boost::integral_constant<size_t,k>,boost::integral_constant<size_t,0> > >::type>
{ typedef boost::units::quantity<Unit,T> type; };

/*! \brief Specialization of meta function that returns the tuple member type
 * for const boost::units::quantity<Unit,T> types
 * \ingroup tuple
 */
template<size_t k, typename Unit, typename T>
struct GetMemberType<k,const boost::units::quantity<Unit,T>,typename boost::enable_if<boost::is_same<boost::integral_constant<size_t,k>,boost::integral_constant<size_t,0> > >::type>
{ typedef const boost::units::quantity<Unit,T> type; };

/*! Meta function that returns the tuple size
 *
 * Specializations must be made for this meta function struct.
 * \ingroup tuple
 */
template<typename Tuple, typename Enabled = void>
struct GetTupleSize
{ 
  // static size_t value = ?
};

/*! \brief Specialization of meta function that returns the tuple size for
 * all arithmetic types
 * \ingroup tuple
 */
template<typename T>
struct GetTupleSize<T,typename boost::enable_if<boost::is_arithmetic<T> >::type> : public boost::integral_constant<size_t,1>
{ /* ... */ };

/*! \brief Specialization of meta function that returns the tuple size for
 * boost::units::quantity<Unit,T> types
 * \ingroup tuple
 */
template<typename Unit,typename T>
struct GetTupleSize<boost::units::quantity<Unit,T>,typename boost::enable_if<boost::is_arithmetic<T> >::type> : public boost::integral_constant<size_t,1>
{ /* ... */ };

/*! \brief Specialization of meta function that returns the tuple size for
 * const boost::units::quantity<Unit,T> types
 * \ingroup tuple
 */
template<typename Unit,typename T>
struct GetTupleSize<const boost::units::quantity<Unit,T>,typename boost::enable_if<boost::is_arithmetic<T> >::type> : public boost::integral_constant<size_t,1>
{ /* ... */ };

/*! Return a reference to the desired tuple member 
 *
 * This can be used with native (arithmetic) types 
 * (e.g. Utility::get<0>( double )).
 * \ingroup tuple
 */
template<size_t k, typename Tuple>
inline typename boost::enable_if<typename boost::mpl::and_<boost::is_same<boost::integral_constant<size_t,k>,boost::integral_constant<size_t,0> >,boost::is_arithmetic<Tuple> >::type, Tuple&>::type get( Tuple& tuple )
{ return tuple; }

/*! Return a reference to the desired tuple member
 *
 * This can be used with boost::units::quantity<Unit,T>
 * \ingroup tuple
 */
template<size_t k, typename Unit, typename T>
inline typename boost::enable_if<boost::is_same<boost::integral_constant<size_t,k>,boost::integral_constant<size_t,0> >,boost::units::quantity<Unit,T>&>::type
get( boost::units::quantity<Unit,T>& tuple )
{ return tuple; }

/*! Return a reference to the desired tuple member
 *
 * This can be used with boost::units::quantity<Unit,T>
 * \ingroup tuple
 */
template<size_t k, typename Unit, typename T>
inline typename boost::enable_if<boost::is_same<boost::integral_constant<size_t,k>,boost::integral_constant<size_t,0> >,const boost::units::quantity<Unit,T>&>::type
get( const boost::units::quantity<Unit,T>& tuple )
{ return tuple; }

/*! Set the head tuple member value
 *
 * The ValueType must be implicitly convertable to the tuple member type.
 * \ingroup tuple
 */
template<size_t k, typename... Types, typename ValueType>
inline void set( Tuple<Types...>& tuple, ValueType value )
{ Utility::get<k>( tuple ) = value; }

/*! Create a tuple with the specified type values
 * \ingroup tuple
 */
template<typename... Types>
inline Utility::Tuple<Types...> makeTuple( Types... values )
{ return Utility::Tuple<Types...>( values... ); }

/*! Stream operator for tuples
 * \ingroup tuple
 * \ingroup print_format
 */
template<typename... Types>
inline std::ostream& operator<<( std::ostream& os,
                                 const Utility::Tuple<Types...>& tuple )
{
  os << "{";
  tuple.toStream( os, ", " );
  os << "}";
  
  return os;
}

/*! Stream operator for std::tuple
 * \ingroup tuple
 * \ingroup print_format
 */
template<typename... Types>
inline std::ostream& operator<<( std::ostream& os,
                                 const std::tuple<Types...>& tuple )
{
  Utility::Tuple<Types...> tuple_copy( tuple );
  
  os << "{";
  tuple_copy.toStream( os, ", " );
  os << "}";
  
  return os;
}

/*! Stream operator for std::pair
 * \ingroup tuple
 * \ingroup print_format
 */
template<typename T1, typename T2>
inline std::ostream& operator<<( std::ostream& os,
                                 const std::pair<T1,T2>& tuple )
{
  os << "{" << tuple.first << "," << tuple.second << "}";
  
  return os;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Utility_Tuple_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_TUPLE_HPP

//---------------------------------------------------------------------------//
// end Utility_Tuple.hpp
//---------------------------------------------------------------------------//
