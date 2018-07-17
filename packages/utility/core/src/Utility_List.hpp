//---------------------------------------------------------------------------//
//!
//! \file   Utility_List.hpp
//! \author Alex Robinson
//! \brief  Helper function and class declarations for std::list
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_LIST_HPP
#define UTILITY_LIST_HPP

// Std Lib Includes
#include <iostream>
#include <list>
#include <forward_list>

// Boost Includes
#include <boost/serialization/list.hpp>
#include <boost/serialization/forward_list.hpp>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_TypeNameTraits.hpp"
#include "Utility_ComparisonTraits.hpp"
#include "Utility_DesignByContract.hpp"

/*! \defgroup list List
 *
 * Additional helper functions and classes for use with the std::list 
 * and std::forward_list have been defined that do not appear in the standard 
 * library.
 */

namespace Utility{

/*! Partial specialization of ToStringTraits for std::list
 * \ingroup list
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<std::list<T> > : public Details::ToStringTraitsIteratorHelper<std::list<T> >
{ /* ... */ };

/*! Partial specialization of ToStringTraits for std::list iterator types
 *
 * Unfortunately this cannot be used with a past-the-end iterator due to 
 * the dereference.
 * \ingroup vector
 * \ingroup to_string_traits
 */
template<typename Iterator>
struct ToStringTraits<Iterator,typename std::enable_if<
         (std::is_same<Iterator,typename std::list<typename std::iterator_traits<Iterator>::value_type>::iterator>::value ||
          std::is_same<Iterator,typename std::list<typename std::iterator_traits<Iterator>::value_type>::const_iterator>::value ||
          std::is_same<Iterator,typename std::list<typename std::iterator_traits<Iterator>::value_type>::reverse_iterator>::value ||
          std::is_same<Iterator,typename std::list<typename std::iterator_traits<Iterator>::value_type>::const_reverse_iterator>::value)>::type>
{
  //! Convert the pointer type to a string
  static inline std::string toString( const Iterator& obj )
  { return ToStringTraits<typename std::iterator_traits<Iterator>::pointer>::toString( &(*obj) ); }

  //! Place the pointer type in a stream
  static inline void toStream( std::ostream& os, const Iterator& obj )
  { return ToStringTraits<typename std::iterator_traits<Iterator>::pointer>::toStream( os, &(*obj) ); }
};

/*! Partial specialization of ToStringTraits for std::forward_list
 * \ingroup list
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<std::forward_list<T> > : public Details::ToStringTraitsIteratorHelper<std::forward_list<T> >
{ /* ... */ };

/*! Partial specialization of ToStringTraits for std::forward_list iterator types
 *
 * Unfortunately this cannot be used with a past-the-end iterator due to 
 * the dereference.
 * \ingroup vector
 * \ingroup to_string_traits
 */
template<typename Iterator>
struct ToStringTraits<Iterator,typename std::enable_if<
         (std::is_same<Iterator,typename std::forward_list<typename std::iterator_traits<Iterator>::value_type>::iterator>::value ||
          std::is_same<Iterator,typename std::forward_list<typename std::iterator_traits<Iterator>::value_type>::const_iterator>::value)>::type>
{
  //! Convert the pointer type to a string
  static inline std::string toString( const Iterator& obj )
  { return ToStringTraits<typename std::iterator_traits<Iterator>::pointer>::toString( &(*obj) ); }

  //! Place the pointer type in a stream
  static inline void toStream( std::ostream& os, const Iterator& obj )
  { return ToStringTraits<typename std::iterator_traits<Iterator>::pointer>::toStream( os, &(*obj) ); }
};

/*! Partial specialization of FromStringTraits for std::list
 * \ingroup list
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<std::list<T> > : public Details::FromStringTraitsSTLCompliantContainerPushBackHelper<std::list<T> >
{ /* ... */ };

/*! Partial specialization of FromStringTraits for std::forward_list
 * \ingroup list
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<std::forward_list<T> > : protected Details::FromStringTraitsSTLCompliantContainerBaseHelper<std::forward_list<T> >
{
protected:
  //! The base helper class type
  typedef Details::FromStringTraitsSTLCompliantContainerBaseHelper<std::forward_list<T> > BaseType;

public:
  //! The type that a string will be converted to
  typedef typename BaseType::ReturnType ReturnType;

  //! Convert the string to an object of the container type
  static inline ReturnType fromString( const std::string& obj_rep )
  {
    ReturnType container =
      BaseType::fromStringImpl( obj_rep, (void (ReturnType::*)(const typename ReturnType::value_type&))&ReturnType::push_front );

    container.reverse();

    return container;
  }

  //! Extract the object from a stream
  static inline void fromStream( std::istream& is,
                                 std::forward_list<T>& obj,
                                 const std::string& = std::string() )
  {
    BaseType::fromStreamImpl( is, obj, (void (std::forward_list<T>::*)(const typename std::forward_list<T>::value_type&))&std::forward_list<T>::push_front );

    obj.reverse();
  }
};

/*! Partial specialization of Utility::TypeNameTraits for std::list types
 * \ingroup list
 * \ingroup type_name_traits
 */
template<typename T>
struct TypeNameTraits<std::list<T> >
{
  //! Get the type name
  static inline std::string name()
  { return std::string("std::list<") + Utility::typeName<T>()+">"; }
};

/*! Partial specialization of Utility::TypeNameTraits for std::forward_list types
 * \ingroup forward_list
 * \ingroup type_name_traits
 */
template<typename T>
struct TypeNameTraits<std::forward_list<T> >
{
  //! Get the type name
  static inline std::string name()
  { return std::string("std::forward_list<") + Utility::typeName<T>()+">"; }
};

/*! Partial specialization of ComparisonTraits for std::list
 * \ingroup list
 * \ingroup comparison_traits
 */
template<typename T>
struct ComparisonTraits<std::list<T> > : public Details::ComparisonTraitsSequenceContainerHelper<std::list<T> >
{ /* ... */ };

/*! Partial specialization of ComparisonTraits for std::forward_list
 * \ingroup list
 * \ingroup comparison_traits
 */
template<typename T>
struct ComparisonTraits<std::forward_list<T> > : public Details::ComparisonTraitsSequenceContainerHelper<std::forward_list<T> >
{ /* ... */ };

namespace Details{

/*! Partial specialization of the zero helper for std::list
 * \ingroup list
 * \ingroup comparison_traits
 */
template<typename T>
struct ZeroHelper<std::list<T> > : public STLCompliantContainerZeroHelper<std::list<T> >
{ /* ... */ };

/*! Partial specialization of the zero helper for std::forward_list
 * \ingroup list
 * \ingroup comparison_traits
 */
template<typename T>
struct ZeroHelper<std::forward_list<T> > : public STLCompliantContainerZeroHelper<std::forward_list<T> >
{ /* ... */ };
  
} // end Details namespace
  
} // end Utility namespace

namespace std{

/*! Place a std::list in a stream
 * \ingroup list
 */
template<typename T>
inline std::ostream& operator<<( std::ostream& os, const std::list<T>& list )
{
  Utility::toStream( os, list );

  return os;
}

/*! Extract a std::list from a stream
 * \ingroup list
 */
template<typename T>
inline std::istream& operator>>( std::istream& is, std::list<T>& list )
{
  Utility::fromStream( is, list );

  return is;
}

/*! Place a std::forward_list in a stream
 * \ingroup list
 */
template<typename T>
inline std::ostream& operator<<( std::ostream& os, const std::forward_list<T>& list )
{
  Utility::toStream( os, list );

  return os;
}

/*! Extract a std::forward_list from a stream
 * \ingroup list
 */
template<typename T>
inline std::istream& operator>>( std::istream& is, std::forward_list<T>& list )
{
  Utility::fromStream( is, list );

  return is;
}

/*! Append an element to a std::list
 *
 * This operator gives a std::list ostream-like capabilities.
 * \ingroup list
 */
template<typename T, typename U>
inline std::list<T>& operator<<( std::list<T>& list, const U& value )
{
  list.push_back( value );
  return list;
}

/*! Append an element that has been converted to a string to a std::list
 *
 * This operator first converts the string to a value of type T and then
 * appends it to the list.
 * \ingroup list
 */
template<typename T>
inline std::list<T>& operator<<( std::list<T>& list,
                                 const std::string& value_string )
{
  list.push_back( Utility::fromString<T>( value_string ) );
  return list;
}

/*! Append an element that has been converted to a string to a std::list
 *
 * This operator first converts the string to a value of type T and then
 * appends it to the list.
 * \ingroup list
 */
template<typename T>
inline std::list<T>& operator<<( std::list<T>& list,
                                 const char* value_string )
{
  list.push_back( Utility::fromString<T>( value_string ) );
  return list;
}

/*! Extract an element from a std::list
 *
 * This operator give a std::list istream-like capabilities. Unlike an istream,
 * the last element is taken from the list first (FILO).
 * \ingroup list
 */
template<typename T, typename U>
inline std::list<T>& operator>>( std::list<T>& list, U& value )
{
  // Make sure that there are elements to extract
  testPrecondition( list.size() > 0 );

  value = list.back();
  list.pop_back();

  return list;
}

/*! Extract an element from a std::list in its string form
 *
 * This operator extracts the last element from a list and converts it
 * to a string.
 * \ingroup list
 */
template<typename T>
inline std::list<T>& operator>>( std::list<T>& list,
                                 std::string& value_string )
{
  // Make sure that there are elements to extract
  testPrecondition( list.size() > 0 );

  value_string = Utility::toString( list.back() );
  list.pop_back();

  return list;
}
  
} // end std namespace

#endif // end UTILITY_LIST_HPP

//---------------------------------------------------------------------------//
// end Utility_List.hpp
//---------------------------------------------------------------------------//
