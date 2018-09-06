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
#include <type_traits>

// Boost Includes
#include <boost/serialization/utility.hpp>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_ComparisonTraits.hpp"
#include "Utility_TypeTraits.hpp"
#include "Utility_TypeNameTraits.hpp"

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
enum TupleMember : size_t {
  FIRST = 0,
  SECOND,
  THIRD,
  FOURTH
};

/*! The tuple size struct (the default is 1)
 * \ingroup tuple
 */
template<typename T, typename Enabled = void>
struct TupleSize : public std::integral_constant<size_t,1>
{ /* ... */ };

/*! \brief Partial specialization of TupleSize for all const types
 * \ingroup tuple
 */
template<typename T>
struct TupleSize<const T> : public TupleSize<T>
{ /* ... */ };

/*! \brief Partial specialization of TupleSize for all volatile types
 * \ingroup tuple
 */
template<typename T>
struct TupleSize<volatile T> : public TupleSize<T>
{ /* ... */ };

/*! \brief Partial specialization of TupleSize for all const volatile types
 * \ingroup tuple
 */
template<typename T>
struct TupleSize<const volatile T> : public TupleSize<T>
{ /* ... */ };

/*! \brief Partial specialization of TupleSize for std::tuple and std::pair types
 * \ingroup tuple
 */
template<typename T>
struct TupleSize<T,typename std::enable_if<Utility::IsTuple<T>::value && !std::is_const<T>::value && !std::is_volatile<T>::value>::type> : public std::tuple_size<T>
{ /* ... */ };

/*! The tuple element struct (the default is undefined)
 * \ingroup tuple
 */
template<size_t I, typename T, typename Enabled = void>
struct TupleElement 
{ /* ... */ };

/*! \brief Partial specialization of TupleElement for all const types
 * \ingroup tuple
 */
template<size_t I, typename T>
struct TupleElement<I, T, typename std::enable_if<std::is_const<T>::value && !std::is_volatile<T>::value>::type> 
{
  typedef typename std::add_const<typename TupleElement<I,typename std::remove_const<T>::type>::type>::type type;
};

/*! \brief Partial specialization of TupleElement for all volatile types
 * \ingroup tuple
 */
template<size_t I, typename T>
struct TupleElement<I, T, typename std::enable_if<std::is_volatile<T>::value && !std::is_const<T>::value>::type>
{
  typedef typename std::add_volatile<typename TupleElement<I,typename std::remove_volatile<T>::type>::type>::type type;
};

/*! \brief Partial specialization of TupleElement for all const volatile types
 * \ingroup tuple
 */
template<size_t I, typename T>
struct TupleElement<I, T, typename std::enable_if<std::is_const<T>::value && std::is_volatile<T>::value>::type>
{
  typedef typename std::add_cv<typename TupleElement<I,typename std::remove_cv<T>::type>::type>::type type;
};

/*! \brief Partial specialization of TupleElement for all non-tuple types (as 
 * long as I == 0).
 *
 * Unlike std::tuple_element, this specialization allows one to create
 * methods that take both std::tuple types and non-tuple types (Utility::get
 * must also be used instead of std::get). See the 
 * Utility::Search::binaryLowerBound method for an example.
 * \ingroup tuple
 */
template<size_t I, typename T>
struct TupleElement<I,T,typename std::enable_if<I==0 && !Utility::IsTuple<T>::value && !std::is_const<T>::value && !std::is_volatile<T>::value>::type>
{ typedef T type; };

/*! \brief Partial specialization of TupleElement for std::tuple and std::pair 
 * types
 * \ingroup tuple
 */
template<size_t I, typename T>
struct TupleElement<I,T,typename std::enable_if<Utility::IsTuple<T>::value && !std::is_const<T>::value && !std::is_volatile<T>::value>::type> : public std::tuple_element<I,T>
{ /* ... */ };

/*! Return a reference to the desired tuple element (std::get)
 * \ingroup tuple
 */
template<size_t I, typename T>
inline typename std::enable_if<Utility::IsTuple<T>::value,typename TupleElement<I,T>::type>::type&
get( T& tuple ) noexcept
{ return std::get<I>( tuple ); }

/*! Return a const reference to the desired tuple element (std::get)
 * \ingroup tuple
 */
template<size_t I, typename T>
inline const typename std::enable_if<Utility::IsTuple<T>::value,typename TupleElement<I,T>::type>::type&
get( const T& tuple ) noexcept
{ return std::get<I>( tuple ); }

/*! Return a reference to the desired tuple member 
 *
 * This can be used with all types 
 * (e.g. double my_double = 1.0; Utility::get<0>( my_double ) == 1.0; }
 * \ingroup tuple
 */
template<size_t I, typename T>
inline typename std::enable_if<I==0 && !Utility::IsTuple<T>::value,T>::type&
get( T& value ) noexcept
{ return value; }

/*! Return a const reference to the desired tuple member 
 *
 * This can be used with all types 
 * (e.g. double my_double = 1.0; Utility::get<0>( my_double ) == 1.0; }
 * \ingroup tuple
 */
template<size_t I, typename T>
inline const typename std::enable_if<I==0 && !Utility::IsTuple<T>::value,T>::type&
get( const T& value ) noexcept
{ return value; }

/*! Set the head tuple member value
 *
 * The ValueType must be implicitly convertable to the tuple member type.
 * \ingroup tuple
 */
template<size_t I, typename TupleType, typename ValueType>
inline void set( TupleType& tuple, ValueType value )
{ Utility::get<I>( tuple ) = value; }

/*! Partial specialization of ToStringTraits for tuple types
 * \ingroup tuple
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<T,typename std::enable_if<Utility::IsTuple<T>::value>::type>
{
  //! Convert the tuple to a string
  static std::string toString( const T& tuple );

  //! Place the tuple in a stream
  static void toStream( std::ostream& os, const T& tuple );
};

/*! Partial specialization of FromStringTraits for std::tuple
 * \ingroup tuple
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<T,typename std::enable_if<Utility::IsTuple<T>::value>::type>;

TYPE_NAME_TRAITS_QUICK_DECL( std::tuple<> );

/*! \brief The partial specialization of Utility::TypeNameTraits for
 * std::tuple types.
 * \ingroup type_name_traits
 */
template<typename... Types>
struct TypeNameTraits<std::tuple<Types...> >
{
  //! Get the type name
  static std::string name();
};

/*! \brief The partial specialization of Utility::TypeNameTraits for
 * std::pair types.
 * \ingroup type_name_traits
 */
template<typename T1, typename T2>
struct TypeNameTraits<std::pair<T1,T2> >
{
  //! Get the type name
  static std::string name();

  //! Get the type name
  static std::string name( const std::pair<T1,T2>& obj );
};

/*! \brief The partial specialization of the Utility::ComparisonTraits for
 * std::tuple types (with at least one element).
 * \ingroup comparison_traits
 */
template<typename... Types>
struct ComparisonTraits<std::tuple<Types...>,typename std::enable_if<Utility::TupleSize<std::tuple<Types...> >::value!=1>::type>
{
  //! Check if the comparison is allowed
  template<typename ComparisonPolicy>
  struct IsComparisonAllowed : public std::true_type
  { /* ... */ };
  
  //! The extra data type (usually a comparison tolerance)
  typedef double ExtraDataType;

  //! Create a comparison header
  template<typename ComparisonPolicy, size_t RightShift>
  static std::string createComparisonHeader(
                           const std::tuple<Types...>& left_value,
                           const std::string& left_name,
                           const bool log_left_name,
                           const std::tuple<Types...>& right_value,
                           const std::string& right_name,
                           const bool log_right_name,
                           const std::string& name_suffix,
                           const ExtraDataType& extra_data = ExtraDataType() );

  //! Compare two tuples
  template<typename ComparisonPolicy,
           size_t HeaderRightShift = 0,
           size_t DetailsRightShift = Details::incrementRightShift(HeaderRightShift)>
  static bool compare( const std::tuple<Types...>& left_value,
                       const std::string& left_name,
                       const bool log_left_name,
                       const std::tuple<Types...>& right_value,
                       const std::string& right_name,
                       const bool log_right_name,
                       const std::string& name_suffix,
                       std::ostream& log,
                       const bool log_comparison_details = false,
                       const ExtraDataType& extra_data = ExtraDataType() );
};

/*! \brief The partial specialization of the Utility::ComparisonTraits for
 * std::tuple types (with at least one element).
 * \ingroup comparison_traits
 */
template<typename T>
struct ComparisonTraits<std::tuple<T> >
{
  //! Check if the comparison is allowed
  template<typename ComparisonPolicy>
  struct IsComparisonAllowed : public std::true_type
  { /* ... */ };
  
  //! The extra data type (usually a comparison tolerance)
  typedef typename Utility::ComparisonTraits<T>::ExtraDataType ExtraDataType;

  //! Create a comparison header
  template<typename ComparisonPolicy, size_t RightShift>
  static inline std::string createComparisonHeader(
                           const std::tuple<T>& left_value,
                           const std::string& left_name,
                           const bool log_left_name,
                           const std::tuple<T>& right_value,
                           const std::string& right_name,
                           const bool log_right_name,
                           const std::string& name_suffix,
                           const ExtraDataType& extra_data = ExtraDataType() )
  {
    return Utility::ComparisonTraits<T>::template createComparisonHeader<ComparisonPolicy,RightShift>(
                                                Utility::get<0>( left_value ),
                                                left_name,
                                                log_left_name,
                                                Utility::get<0>( right_value ),
                                                right_name,
                                                log_right_name,
                                                name_suffix,
                                                extra_data );
  }
  
  //! Compare two tuples
  template<typename ComparisonPolicy,
           size_t HeaderRightShift = 0,
           size_t DetailsRightShift = Details::incrementRightShift(HeaderRightShift)>
  static bool compare( const std::tuple<T>& left_value,
                       const std::string& left_name,
                       const bool log_left_name,
                       const std::tuple<T>& right_value,
                       const std::string& right_name,
                       const bool log_right_name,
                       const std::string& name_suffix,
                       std::ostream& log,
                       const bool log_comparison_details = false,
                       const ExtraDataType& extra_data = ExtraDataType() )
  {
    return Utility::ComparisonTraits<T>::template compare<ComparisonPolicy,HeaderRightShift,DetailsRightShift>(
                                                Utility::get<0>( left_value ),
                                                left_name,
                                                log_left_name,
                                                Utility::get<0>( right_value ),
                                                right_name,
                                                log_right_name,
                                                name_suffix,
                                                log,
                                                log_comparison_details,
                                                extra_data );
  }
};

/*! \brief The partial specialization of the Utility::ComparisonTraits for
 * std::pair types (with at least one element).
 * \ingroup comparison_traits
 */
template<typename T1, typename T2>
struct ComparisonTraits<std::pair<T1,T2> >
{
  //! Check if the comparison is allowed
  template<typename ComparisonPolicy>
  struct IsComparisonAllowed : public std::true_type
  { /* ... */ };
  
  //! The extra data type (usually a comparison tolerance)
  typedef double ExtraDataType;

  //! Create a comparison header
  template<typename ComparisonPolicy, size_t RightShift>
  static std::string createComparisonHeader(
                           const std::pair<T1,T2>& left_value,
                           const std::string& left_name,
                           const bool log_left_name,
                           const std::pair<T1,T2>& right_value,
                           const std::string& right_name,
                           const bool log_right_name,
                           const std::string& name_suffix,
                           const ExtraDataType& extra_data = ExtraDataType() );

  //! Compare two tuples
  template<typename ComparisonPolicy,
           size_t HeaderRightShift = 0,
           size_t DetailsRightShift = Details::incrementRightShift(HeaderRightShift)>
  static bool compare( const std::pair<T1,T2>& left_value,
                       const std::string& left_name,
                       const bool log_left_name,
                       const std::pair<T1,T2>& right_value,
                       const std::string& right_name,
                       const bool log_right_name,
                       const std::string& name_suffix,
                       std::ostream& log,
                       const bool log_comparison_details = false,
                       const ExtraDataType& extra_data = ExtraDataType() );
};
  
} // end Utility namespace

namespace boost{

namespace serialization{

/*! Serialize a tuple
 *
 * A boost archive must be passed as the archive object
 * \ingroup tuple
 */
template<typename Archive, typename... Types>
void serialize( Archive& archive, std::tuple<Types...>& tuple, const unsigned version );
  
} // end serialization namespace

} // end boost namespace

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
