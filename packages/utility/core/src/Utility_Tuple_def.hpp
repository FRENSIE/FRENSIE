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

namespace Details{

//! The helper class that places a tuple in a stream
template<size_t I, typename TupleType, typename Enable = void>
struct TupleToStreamHelper
{
  static inline void toStream( std::ostream& os, const TupleType& tuple )
  { 
    // Print the tuple element
    os << Utility::get<I>( tuple ) << ", ";

    // Print the remaining tuple elements
    TupleToStreamHelper<I+1,TupleType>::toStream( os, tuple );
  }
};

/*! \brief The helper class that places a tuple in a stream
 * (specialization for I == TupleSize-1, which is for the last element)
 */
template<size_t I, typename TupleType>
struct TupleToStreamHelper<I, TupleType, typename std::enable_if<I==TupleSize<TupleType>::value-1>::type>
{
  static inline void toStream( std::ostream& os, const TupleType& tuple )
  {
    // Print the tuple element
    os << Utility::get<I>( tuple );
  }
};

/*! \brief The helper class that places a tuple in a stream
 * (specialization for I == TupleSize, which is past the last element)
 */
template<size_t I, typename TupleType>
struct TupleToStreamHelper<I, TupleType, typename std::enable_if<I==TupleSize<TupleType>::value>::type>
{
  static inline void toStream( std::ostream& os, const TupleType& tuple )
  { /* ... */ }
};
  
} // end Details namespace

// Place the tuple in a stream
template<typename... Types>
void tupleToStream( std::ostream&os, const Utility::Tuple<Types...>& tuple )
{
  os << "{";
  Utility::Details::TupleToStreamHelper<0,Utility::Tuple<Types...> >::toStream(
                                                                   os, tuple );
  os << "}";
}
  
// Convert the tuple to a string
template<typename... Types>
std::string tupleToString( const Utility::Tuple<Types...>& tuple )
{
  std::ostringstream oss;
  tupleToStream( oss, tuple );

  return oss.str();
}
  
} // end Utility namespace

#endif // end UTILITY_TUPLE_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_Tuple_def.hpp
//---------------------------------------------------------------------------//
