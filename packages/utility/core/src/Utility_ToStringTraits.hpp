//---------------------------------------------------------------------------//
//!
//! \file   Utility_ToStringTraits.hpp
//! \author Alex Robinson
//! \brief  ToStringTraits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TO_STRING_TRAITS_HPP
#define UTILITY_TO_STRING_TRAITS_HPP

// Std Lib Includes
#include <sstream>
#include <type_traits>
#include <iterator>
#include <tuple>
#include <utility>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

// FRENSIE Includes
#include "Utility_ToStringTraitsDecl.hpp"

namespace Utility{

/*! Specialization of ToStringTraits for std::string
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<std::string>
{
  //! Return the string
  static inline std::string toString( const std::string& obj )
  { return obj; }

  //! Place the string in a stream
  static inline void toStream( std::ostream& os, const std::string& obj )
  { os << obj; }
};

/*! Specialization of ToStringTraits for const char*
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<const char*>
{
  //! Return the string
  static inline std::string toString( const char* obj )
  { return obj; }

  //! Place the c-string in a stream
  static inline void toStream( std::ostream& os, const char* obj )
  { os << obj; }
};

/*! Specialization of ToStringTraits for char*
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<char*> : public ToStringTraits<const char*>
{ /* ... */ };

/*! Partial specialization of ToStringTraits for char[]
 * \ingroup to_string_traits
 */
template<size_t N>
struct ToStringTraits<char[N]> : public ToStringTraits<const char*>
{ /* ... */ };

/*! Partial specialization of ToStringTraits for const char[]
 * \ingroup to_string_traits
 */
template<size_t N>
struct ToStringTraits<const char[N]> : public ToStringTraits<const char*>
{ /* ... */ };
  
/*! Specialization of ToStringTraits for bool
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<bool>
{
  //! Convert the boolean to a string
  static inline std::string toString( const bool& obj )
  { return (obj ? "true" : "false"); }

  //! Place the boolean in a stream
  static inline void toStream( std::ostream& os, const bool& obj )
  { os << ToStringTraits<bool>::toString( obj ); }
};

/*! Specialization of ToStringTraits for float
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<float>
{
  //! Convert the float to a string
  static inline std::string toString( const float& obj )
  {
    std::ostringstream oss;

    ToStringTraits<float>::toStream( oss, obj );
    
    return oss.str();
  }

  //! Place to float in a stream
  static inline void toStream( std::ostream& os, const float& obj )
  {
    // Make the stream precision high enough to capture the float without any
    // rounding loss
    os.setf( std::ios::scientific );
    os.precision( 9 );
    
    os << obj;
  }
};

/*! Specialization of ToStringTraits for double
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<double>
{
  //! Convert the double to a string
  static inline std::string toString( const double& obj )
  {
    std::ostringstream oss;

    ToStringTraits<double>::toStream( oss, obj );
    
    return oss.str();
  }

  //! Place the double in a stream
  static inline void toStream( std::ostream& os, const double& obj )
  {
    // Make the stream precision high enough to capture the double without any
    // rounding loss
    os.setf( std::ios::scientific );
    os.precision( 18 );
    
    os << obj;
  }
};

/*! Partial specialization of ToStringTraits for integral types
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<T,typename std::enable_if<std::is_integral<T>::value>::type>
{
  //! Convert the integral type to a string
  static inline std::string toString( const T& obj )
  {
    std::ostringstream oss;

    ToStringTraits<T>::toStream( oss, obj );

    return oss.str();
  }

  //! Place the integral type in a stream
  static inline void toStream( std::ostream& os, const T& obj )
  { os << obj; }
};

namespace Details{

//! The tuple output stream helper class 
template<size_t I, typename TupleType, typename Enable = void>
struct TupleToStreamHelper
{
  static inline void toStream( std::ostream& os, const TupleType& tuple )
  { 
    // Insert the tuple element
    Utility::toStream( os, std::get<I>( tuple ) );
    
    os << ", ";

    // Insert the remaining tuple elements
    TupleToStreamHelper<I+1,TupleType>::toStream( os, tuple );
  }
};

/*! \brief The tuple output stream helper class 
 * (specialization for I == std::tuple_size-1, which is for the last element)
 */
template<size_t I, typename TupleType>
struct TupleToStreamHelper<I, TupleType, typename std::enable_if<I==std::tuple_size<TupleType>::value-1>::type>
{
  static inline void toStream( std::ostream& os, const TupleType& tuple )
  {
    // Insert the tuple element
    Utility::toStream( os, std::get<I>( tuple ) );
  }
};

/*! \brief The tuple output stream helper class
 * (specialization for I == std::tuple_size, which is past the last element)
 */
template<size_t I, typename TupleType>
struct TupleToStreamHelper<I, TupleType, typename std::enable_if<I==std::tuple_size<TupleType>::value>::type>
{
  static inline void toStream( std::ostream& os, const TupleType& tuple )
  { /* ... */ }
};

} // end Details namespace

/*! Partial specialization of ToStringTraits for tuple types
 * \ingroup to_string_traits
 */
template<typename... Types>
struct ToStringTraits<std::tuple<Types...> >
{
  //! Convert the tuple to a string
  static inline std::string toString( const std::tuple<Types...>& tuple )
  {
    std::ostringstream oss;

    ToStringTraits<std::tuple<Types...> >::toStream( oss, tuple );

    return oss.str();
  }

  //! Place the tuple in a stream
  static inline void toStream( std::ostream& os,
                               const std::tuple<Types...>& tuple )
  {
    os << '{';
    
    Details::TupleToStreamHelper<0,std::tuple<Types...> >::toStream( os, tuple);
    os << '}';
  }
};

/*! Partial specialization of ToStringTraits for std::pair types
 * \ingroup to_string_traits
 */
template<typename T1, typename T2>
struct ToStringTraits<std::pair<T1,T2> >
{
  //! Convert the tuple to a string
  static inline std::string toString( const std::pair<T1,T2>& pair )
  {
    auto pair_copy = std::tie( pair.first, pair.second );

    return ToStringTraits<decltype(pair_copy)>::toString( pair_copy );
  }

  //! Place the tuple in a stream
  static inline void toStream( std::ostream& os,
                               const std::pair<T1,T2>& pair )
  {
    auto pair_copy = std::tie( pair.first, pair.second );
    
    ToStringTraits<decltype(pair_copy)>::toStream( os, pair_copy );
  }
};

namespace Details{

//! ToStringTraits helper class for types with iterators
template<typename T>
struct ToStringTraitsIteratorHelper
{
  //! Convert the object of type T to a string
  static inline std::string toString( const T& obj )
  { 
    std::ostringstream oss;

    ToStringTraits<T>::toStream( oss, obj );

    return oss.str();
  }

  //! Place the object of type T in a stream
  static inline void toStream( std::ostream& os, const T& obj )
  {
    os << "{";

    typename T::const_iterator it, end;
    it = obj.begin();
    end = obj.end();

    while( it != end )
    {
      Utility::toStream( os, *it );

      ++it;

      if( it != end )
        os << ", ";
    }

    os << "}";
  }
};
  
} // end Details namespace

/*! Partial specialization of ToStringTraits for std::array
 * \ingroup to_string_traits
 */
template<typename T, size_t N>
struct ToStringTraits<std::array<T,N> > : public Details::ToStringTraitsIteratorHelper<std::array<T,N> >
{ /* ... */ };

/*! Partial specialization of ToStringTraits for std::vector
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<std::vector<T> > : public Details::ToStringTraitsIteratorHelper<std::vector<T> >
{ /* ... */ };

/*! Partial specialization of ToStringTraits for std::list
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<std::list<T> > : public Details::ToStringTraitsIteratorHelper<std::list<T> >
{ /* ... */ };

/*! Partial specialization of ToStringTraits for std::forward_list
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<std::forward_list<T> > : public Details::ToStringTraitsIteratorHelper<std::forward_list<T> >
{ /* ... */ };

/*! Partial specialization of ToStringTraits for std::deque
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<std::deque<T> > : public Details::ToStringTraitsIteratorHelper<std::deque<T> >
{ /* ... */ };

/*! Partial specialization of ToStringTraits for std::set
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<std::set<T> > : public Details::ToStringTraitsIteratorHelper<std::set<T> >
{ /* ... */ };

/*! Partial specialization of ToStringTraits for std::unordered_set
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<std::unordered_set<T> > : public Details::ToStringTraitsIteratorHelper<std::unordered_set<T> >
{ /* ... */ };

/*! Partial specialization of ToStringTraits for std::map
 * \ingroup to_string_traits
 */
template<typename Key, typename T>
struct ToStringTraits<std::map<Key,T> > : public Details::ToStringTraitsIteratorHelper<std::map<Key,T> >
{ /* ... */ };

/*! Partial specialization of ToStringTraits for std::unordered_map
 * \ingroup to_string_traits
 */
template<typename Key, typename T>
struct ToStringTraits<std::unordered_map<Key,T> > : public Details::ToStringTraitsIteratorHelper<std::unordered_map<Key,T> >
{ /* ... */ };

// Convert the object to a string
template<typename T>
inline std::string toString( const T& obj )
{
  return Utility::ToStringTraits<T>::toString( obj );
}

// Place the object in a stream
template<typename T>
inline void toStream( std::ostream& os, const T& obj )
{
  Utility::ToStringTraits<T>::toStream( os, obj );
}

} // end Utility namespace

#endif // end UTILITY_TO_STRING_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_ToStringTraits.hpp
//---------------------------------------------------------------------------//
