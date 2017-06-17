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
  
} // end Utility namespace

#endif // end UTILITY_TUPLE_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_Tuple_def.hpp
//---------------------------------------------------------------------------//
