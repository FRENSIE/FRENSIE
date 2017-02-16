//---------------------------------------------------------------------------//
//!
//! \file   Utility_Tuple_def.hpp
//! \author Alex Robinson
//! \brief  Simple struct for storing objects of arbitrary type
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TUPLE_DEF_HPP
#define UTILITY_TUPLE_DEF_HPP

// Boost Includes
#include <boost/mpl/or.hpp>

namespace Utility{

/*! \brief Specialization of meta function that returns the tuple member type
 * for first member.
 * \ingroup tuple
 */
template<typename T, typename... Types>
struct GetMemberType<0, Tuple<T,Types...> >
{ typedef T type; };

/*! \brief Specialization of meta function that returns the tuple member type
 * for all members but the first.
 * \ingroup tuple
 */
template<size_t k, typename T, typename... Types>
struct GetMemberType<k, Tuple<T,Types...> >
{ typedef typename GetMemberType<k-1, Tuple<Types...> >::type type; };

/*! \brief Specialization of meta function that returns the std::tuple member
 * type
 * \ingroup tuple
 */
template<size_t k, typename... Types>
struct GetMemberType<k, std::tuple<Types...> >
{ typedef typename std::tuple_element<k,std::tuple<Types...> >::type type; };

/*! \brief Specialization of meta function that returns the std::pair first
 * member type
 * \ingroup tuple
 */
template<typename T1, typename T2>
struct GetMemberType<0, std::pair<T1,T2> >
{ typedef T1 type; };

/*! \brief Specialization of meta function that returns the std::pair second
 * member type
 * \ingroup tuple
 */
template<typename T1, typename T2>
struct GetMemberType<1, std::pair<T1,T2> >
{ typedef T2 type; };

/*! Meta function that returns the tuple size
 * \ingroup tuple
 */
template<typename... Types>
struct GetTupleSize<Tuple<Types... > > : public std::tuple_size<std::tuple<Types...> >
{ /* ... */ };

/*! Meta function that returns the std::tuple size
 * \ingroup tuple
 */
template<typename... Types>
struct GetTupleSize<std::tuple<Types... > > : public std::tuple_size<std::tuple<Types...> >
{ /* ... */ };

/*! Meta function that returns the std::tuple size
 * \ingroup tuple
 */
template<typename T1, typename T2>
struct GetTupleSize<std::pair<T1,T2> > : public std::tuple_size<std::pair<T1,T2> >
{ /* ... */ };

/*! Returns a reference to the head tuple member
 * \ingroup tuple
 */
template<size_t k, typename... Types>
inline typename boost::enable_if<boost::is_same<boost::integral_constant<size_t,k>,boost::integral_constant<size_t,0> >, typename GetMemberType<0,Tuple<Types...> >::type&>::type
get( Tuple<Types...>& tuple )
{ return tuple.head; }

/*! Returns a const reference to the head tuple member
 * \ingroup tuple
 */
template<size_t k, typename... Types>
inline typename boost::enable_if<boost::is_same<boost::integral_constant<size_t,k>,boost::integral_constant<size_t,0> >, const typename GetMemberType<0,Tuple<Types...> >::type&>::type
get( const Tuple<Types...>& tuple )
{ return tuple.head; }

/*! Return a reference to the desired tuple member
 * \ingroup tuple
 */
template<size_t k, typename T, typename... Types>
inline typename boost::enable_if<typename boost::mpl::not_<boost::is_same<boost::integral_constant<size_t,k>,boost::integral_constant<size_t,0> > >::type, typename GetMemberType<k,Tuple<T,Types...> >::type&>::type
get( Tuple<T,Types...>& tuple )
{ return get<k-1,Types...>( tuple ); }

/*! Return a const reference to the desired tuple member
 * \ingroup tuple
 */
template<size_t k, typename T, typename... Types>
inline typename boost::enable_if<typename boost::mpl::not_<boost::is_same<boost::integral_constant<size_t,k>,boost::integral_constant<size_t,0> > >::type, const typename GetMemberType<k,Tuple<T,Types...> >::type&>::type
get( const Tuple<T,Types...>& tuple )
{ return get<k-1,Types...>( tuple ); }

/*! Return a reference to the desired std::tuple member
 * \ingroup tuple
 */
template<size_t k, typename... Types>
inline typename GetMemberType<k,std::tuple<Types...> >::type&
get( std::tuple<Types...>& tuple )
{ return std::get<k>( tuple ); }

/*! Return a const reference to the desired std::tuple member
 * \ingroup tuple
 */
template<size_t k, typename... Types>
inline const typename GetMemberType<k,std::tuple<Types...> >::type&
get( const std::tuple<Types...>& tuple )
{ return std::get<k>( tuple ); }

/*! Return a refence to the first std::pair member
 * \ingroup tuple
 */
template<size_t k, typename T1, typename T2>
inline typename boost::enable_if<boost::is_same<boost::integral_constant<size_t,k>,boost::integral_constant<size_t,0> >, typename GetMemberType<0,std::pair<T1,T2> >::type&>::type
get( const std::pair<T1,T2>& tuple )
{ return tuple.first; }

/*! Return a reference to the second std::pair member
 * \ingroup tuple
 */
template<size_t k, typename T1, typename T2>
inline typename boost::enable_if<boost::is_same<boost::integral_constant<size_t,k>,boost::integral_constant<size_t,1> >, typename GetMemberType<1,std::pair<T1,T2> >::type&>::type
get( const std::pair<T1,T2>& tuple )
{ return tuple.first; }

// Default constructor
template<typename T, typename... Types>
Tuple<T,Types...>::Tuple()
  : Tuple<Types...>(),
    head()
{ /* ... */ }

// Constructor
template<typename T, typename... Types>
Tuple<T,Types...>::Tuple( T first_value, Types... last_values )
  : Tuple<Types...>( last_values... ), head( first_value )
{ /* ... */ }

// Constructor
template<typename... Types>
Tuple<Types...>::Tuple( Types... )
{ /* ... */ }

// Copy constructor
template<typename T, typename... Types>
template<template<typename,typename...> class OtherTuple>
Tuple<T,Types...>::Tuple( const OtherTuple<T,Types...>& that )
  : Tuple<Types...>( that ), head( Utility::get<0>( that ) )
{ /* ... */ }

// Copy constructor
template<typename... Types>
template<template<typename...> class OtherTuple>
Tuple<Types...>::Tuple( const OtherTuple<Types...>& )
{ /* ... */ }

// Assignment operator
template<typename T, typename... Types>
template<template<typename,typename...> class OtherTuple>
Tuple<T,Types...>& Tuple<T,Types...>::operator=(
                                           const OtherTuple<T,Types...>& that )
{
  Tuple<Types...>::operator=( that );
  head = Utility::get<0>( that );
  
  return *this;
}

// Assignment operator
template<typename... Types>
template<template<typename...> class OtherTuple>
Tuple<Types...>& Tuple<Types...>::operator=( const OtherTuple<Types...>& )
{ return *this; }

// Reassignment operator
template<typename T, typename... Types>
void Tuple<T,Types...>::operator()( T first_value, Types... last_values )
{
  Tuple<Types...>::operator()( last_values... );
  head = first_value;
}
  
// Reassignment operator
template<typename... Types>
void Tuple<Types...>::operator()( Types... )
{ /* ... */ }

// Inequality operator
template<typename T, typename... Types>
template<template<typename,typename...> class OtherTuple>
bool Tuple<T,Types...>::operator!=( const OtherTuple<T,Types...>& that )
{
  return this.head != Utility::get<0>( that ) ||
    Tuple<Types...>::operator!=( that );
}

// Inequality operator
template<typename... Types>
template<template<typename...> class OtherTuple>
bool Tuple<Types...>::operator!=( const OtherTuple<Types...>& )
{ return false; }

// Equality operator
template<typename T, typename... Types>
template<template<typename,typename...> class OtherTuple>
bool Tuple<T,Types...>::operator==( const OtherTuple<T,Types...>& that )
{
  return this.head == Utility::get<0>( that ) &&
    Tuple<Types...>::operator==( that );
}

// Equality operator
template<typename... Types>
template<template<typename...> class OtherTuple>
bool Tuple<Types...>::operator==( const OtherTuple<Types...>& )
{ return true; }

namespace Details{

//! Helper class used for printing tuples (default)
template<typename Tuple, typename Enabled = void>
struct TupleStreamHelper
{
  inline void useElementDelim( std::ostream& os,
                               const std::string& element_delim )
  { os << element_delim; }
};

//! Specialization of helper class used for printing tuples (single value)
template<typename Tuple>
struct TupleStreamHelper<Tuple,typename boost::enable_if<typename boost::mpl::or_<boost::is_same<GetTupleSize<Tuple>,boost::integral_constant<size_t,0> >,boost::is_same<GetTupleSize<Tuple>,boost::integral_constant<size_t,1> > >::type>::type>
{
  inline void useElementDelim( std::ostream& os,
                               const std::string& element_delim )
  { /* ... */ }
};
  
} // end Details namespace

// Place the tuple in a stream
template<typename T, typename... Types>
void Tuple<T,Types...>::toStream( std::ostream& os,
                                  const std::string& element_delim )
{
  os << head;
  Details::TupleStreamHelper<Tuple<T,Types...> >::useElementDelim( os, element_delim );
  
  Tuple<Types...>::toStream( os, element_delim );
}

// Place the tuple in a stream
template<typename... Types> 
void Tuple<Types...>::toStream( std::ostream&, const std::string& )
{ /* ... */ }
  
} // end Utility namespace

#endif // end UTILITY_TUPLE_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_Tuple_def.hpp
//---------------------------------------------------------------------------//
