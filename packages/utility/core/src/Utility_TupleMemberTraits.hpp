//---------------------------------------------------------------------------//
//!
//! \file   Utility_TupleMemberTraits.hpp
//! \author Alex Robinson
//! \brief  Tuple member traits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TUPLE_MEMBER_TRAITS_HPP
#define UTILITY_TUPLE_MEMBER_TRAITS_HPP

// Std Lib Includes
#include <utility>
#include <tuple>

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>

// FRENSIE Includes
#include "Utility_TupleMemberTraitsDecl.hpp"
#include "Utility_Tuple.hpp"

namespace Utility{

/*! \brief The partial spacialization of the TupleMemberTraits for all
 * constant types
 * \details The set method will not compile when using const types.
 * \ingroup tuple_member_traits
 */
template<typename T, TupleMember member>
struct TupleMemberTraits<T,member,typename boost::enable_if<boost::is_const<T> >::type> : public TupleMemberTraits<typename boost::remove_const<T>::type,member>
{ /* ... */ };

/*! \brief The partial specialization of the TupleMemberTraits for arithmetic
 * types and FIRST
 * \ingroup tuple_member_traits
 */
template<typename T>
struct TupleMemberTraits<T,FIRST,typename boost::enable_if<typename boost::mpl::and_<boost::is_arithmetic<T>,typename boost::mpl::not_<boost::is_const<T> >::type>::type>::type>
{
  typedef T tupleType;
  typedef T tupleMemberType;
  static inline T& get( tupleType& value )
  { return value; }
  static inline const T& get( const tupleType& value )
  { return value; }
  static inline void set( tupleType& value, const tupleMemberType new_value )
  { value = new_value; }
};
  
/*! The partial specialization of the TupleMemberTraits for
 * boost::units::quantity and FIRST
 * \ingroup tuple_member_traits
 */
template<typename Unit, typename T>
struct TupleMemberTraits<boost::units::quantity<Unit,T>,FIRST>
{
  typedef boost::units::quantity<Unit,T> tupleType;
  typedef boost::units::quantity<Unit,T> tupleMemberType;
  static inline tupleMemberType& get( tupleType& quantity )
  { return quantity; }
  static inline const tupleMemberType& get( const tupleType& quantity )
  { return quantity; }
  static inline void set( tupleType& quantity,
			  const tupleMemberType& new_quantity )
  { quantity = new_quantity; }
};

/*! The partial specialization of the TupleMemberTraits for FIRST
 * \ingroup tuple_member_traits
 */
  template<typename T,
           typename... Types,
           template<typename...> class Tuple>
struct TupleMemberTraits<Tuple<T,Types...>,FIRST>
{
  typedef Tuple<T,Types...> tupleType;
  typedef typename tupleType::firstType tupleMemberType;
  static inline tupleMemberType& get( tupleType& tuple )
  { return tuple.first; }
  static inline const tupleMemberType& get( const tupleType& tuple )
  { return tuple.first; }
  static inline void set( tupleType& tuple, const tupleMemberType& value )
  { tuple.first = value; }
};

/*! The partial specialization of the TupleMemberTraits for SECOND
 * \ingroup tuple_member_traits
 */
template<typename T1,
         typename T2,
         typename... Types,
         template<typename...> class Tuple>
struct TupleMemberTraits<Tuple<T1,T2,Types...>,SECOND>
{
  typedef Tuple<T1,T2,Types...> tupleType;
  typedef typename tupleType::secondType tupleMemberType;
  static inline tupleMemberType& get( tupleType& tuple )
  { return tuple.second; }
  static inline const tupleMemberType& get( const tupleType& tuple )
  { return tuple.second; }
  static inline void set( tupleType& tuple, const tupleMemberType& value )
  { tuple.second = value; }
};

/*! The partial specialization of the TupleMemberTraits for THIRD
 * \ingroup tuple_member_traits
 */
template<typename T1,
         typename T2,
         typename T3,
         typename... Types,
         template<typename...> class Tuple>
struct TupleMemberTraits<Tuple<T1,T2,T3,Types...>,THIRD>
{
  typedef Tuple<T1,T2,T3,Types...> tupleType;
  typedef typename tupleType::thirdType tupleMemberType;
  static inline tupleMemberType& get( tupleType& tuple )
  { return tuple.third; }
  static inline const tupleMemberType& get( const tupleType& tuple )
  { return tuple.third; }
  static inline void set( tupleType& tuple, const tupleMemberType& value )
  { tuple.third = value; }
};

/*! The partial specialization of the TupleMemberTraits for FOURTH
 * \ingroup tuple_member_traits
 */
template<typename T1,
         typename T2,
         typename T3,
         typename T4,
         typename... Types,
         template<typename...> class Tuple>
struct TupleMemberTraits<Tuple<T1,T2,T3,T4,Types...>,FOURTH>
{
  typedef Tuple<T1,T2,T3,T4,Types...> tupleType;
  typedef typename tupleType::fourthType tupleMemberType;
  static inline tupleMemberType& get( tupleType& tuple )
  { return tuple.fourth; }
  static inline const tupleMemberType& get( const tupleType& tuple )
  { return tuple.fourth; }
  static inline void set( tupleType& tuple, const tupleMemberType& value )
  { tuple.fourth = value; }
};

/*! \brief The partial specialization of the TupleMemberTraits for std::tuple
 * and FIRST
 * \ingroup tuple_member_traits
 */
template<typename T, typename... Types>
struct TupleMemberTraits<std::tuple<T,Types...>,FIRST>
{
  typedef std::tuple<T,Types...> tupleType;
  typedef T tupleMemberType;
  static inline tupleMemberType& get( tupleType& tuple )
  { return std::get<0>(tuple); }
  static inline const tupleMemberType& get( const tupleType& tuple )
  { return std::get<0>(tuple); }
  static inline void set( tupleType& tuple, const tupleMemberType& value )
  { std::get<0>(tuple) = value; }
};

/*! \brief The partial specialization of the TupleMemberTraits for std::tuple
 * and SECOND
 * \ingroup tuple_member_traits
 */
template<typename T1, typename T2, typename... Types>
struct TupleMemberTraits<std::tuple<T1,T2,Types...>,SECOND>
{
  typedef std::tuple<T1,T2,Types...> tupleType;
  typedef T2 tupleMemberType;
  static inline tupleMemberType& get( tupleType& tuple )
  { return std::get<1>(tuple); }
  static inline const tupleMemberType& get( const tupleType& tuple )
  { return std::get<1>(tuple); }
  static inline void set( tupleType& tuple, const tupleMemberType& value )
  { std::get<1>(tuple) = value; }
};

/*! \brief The partial specialization of the TupleMemberTraits for std::tuple
 * and THIRD
 * \ingroup tuple_member_traits
 */
template<typename T1, typename T2, typename T3, typename... Types>
struct TupleMemberTraits<std::tuple<T1,T2,T3,Types...>,SECOND>
{
  typedef std::tuple<T1,T2,T3,Types...> tupleType;
  typedef T3 tupleMemberType;
  static inline tupleMemberType& get( tupleType& tuple )
  { return std::get<2>(tuple); }
  static inline const tupleMemberType& get( const tupleType& tuple )
  { return std::get<2>(tuple); }
  static inline void set( tupleType& tuple, const tupleMemberType& value )
  { std::get<2>(tuple) = value; }
};

/*! \brief The partial specialization of the TupleMemberTraits for std::tuple
 * and FOURTH
 * \ingroup tuple_member_traits
 */
template<typename T1, typename T2, typename T3, typename T4, typename... Types>
struct TupleMemberTraits<std::tuple<T1,T2,T3,T4,Types...>,SECOND>
{
  typedef std::tuple<T1,T2,T3,T4,Types...> tupleType;
  typedef T4 tupleMemberType;
  static inline tupleMemberType& get( tupleType& tuple )
  { return std::get<3>(tuple); }
  static inline const tupleMemberType& get( const tupleType& tuple )
  { return std::get<3>(tuple); }
  static inline void set( tupleType& tuple, const tupleMemberType& value )
  { std::get<3>(tuple) = value; }
};

} // end Utility namespace

#endif // end UTILITY_TUPLE_MEMBER_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_TupleMemberTraits.hpp
//---------------------------------------------------------------------------//


