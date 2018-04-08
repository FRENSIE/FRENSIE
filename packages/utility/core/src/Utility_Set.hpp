//---------------------------------------------------------------------------//
//!
//! \file   Utility_Set.hpp
//! \author Alex Robinson
//! \brief  Helper function and class declarations for std::set and
//!         std::unordered_set
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SET_HPP
#define UTILITY_SET_HPP

// Std Lib Includes
#include <iostream>
#include <set>
#include <unordered_set>

// Boost Includes
#include <boost/serialization/set.hpp>
#include <boost/serialization/unordered_set.hpp>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_ComparisonTraits.hpp"
#include "Utility_TypeNameTraits.hpp"

/*! \defgroup set Set
 *
 * Additional helper functions and classes for use with the std::set and
 * std::unordered_set have been defined that do not appear in the standard
 * library.
 */

namespace Utility{

/*! Partial specialization of ToStringTraits for std::set
 * \ingroup set
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<std::set<T> > : public Details::ToStringTraitsIteratorHelper<std::set<T> >
{ /* ... */ };

/*! Partial specialization of ToStringTraits for std::set iterator types
 *
 * Unfortunately this cannot be used with a past-the-end iterator due to 
 * the dereference.
 * \ingroup set
 * \ingroup to_string_traits
 */
template<typename Iterator>
struct ToStringTraits<Iterator,typename std::enable_if<
         (std::is_same<Iterator,typename std::set<typename std::iterator_traits<Iterator>::value_type>::iterator>::value ||
          std::is_same<Iterator,typename std::set<typename std::iterator_traits<Iterator>::value_type>::const_iterator>::value ||
          std::is_same<Iterator,typename std::set<typename std::iterator_traits<Iterator>::value_type>::reverse_iterator>::value ||
          std::is_same<Iterator,typename std::set<typename std::iterator_traits<Iterator>::value_type>::const_reverse_iterator>::value)>::type>
{
  //! Convert the pointer type to a string
  static inline std::string toString( const Iterator& obj )
  { return ToStringTraits<typename std::iterator_traits<Iterator>::pointer>::toString( &(*obj) ); }

  //! Place the pointer type in a stream
  static inline void toStream( std::ostream& os, const Iterator& obj )
  { return ToStringTraits<typename std::iterator_traits<Iterator>::pointer>::toStream( os, &(*obj) ); }
};

/*! Partial specialization of ToStringTraits for std::unordered_set
 * \ingroup set
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<std::unordered_set<T> > : public Details::ToStringTraitsIteratorHelper<std::unordered_set<T> >
{ /* ... */ };

/*! Partial specialization of ToStringTraits for std::unordered_set iterator types
 *
 * Unfortunately this cannot be used with a past-the-end iterator due to 
 * the dereference.
 * \ingroup set
 * \ingroup to_string_traits
 */
template<typename Iterator>
struct ToStringTraits<Iterator,typename std::enable_if<
         (std::is_same<Iterator,typename std::unordered_set<typename std::iterator_traits<Iterator>::value_type>::iterator>::value ||
          std::is_same<Iterator,typename std::unordered_set<typename std::iterator_traits<Iterator>::value_type>::const_iterator>::value)>::type>
{
  //! Convert the pointer type to a string
  static inline std::string toString( const Iterator& obj )
  { return ToStringTraits<typename std::iterator_traits<Iterator>::pointer>::toString( &(*obj) ); }

  //! Place the pointer type in a stream
  static inline void toStream( std::ostream& os, const Iterator& obj )
  { return ToStringTraits<typename std::iterator_traits<Iterator>::pointer>::toStream( os, &(*obj) ); }
};

/*! Partial specialization of FromStringTraits for std::set
 * \ingroup set
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<std::set<T> > : public Details::FromStringTraitsSTLCompliantContainerInsertHelper<std::set<T> >
{ /* ... */ };

/*! Partial specialization of FromStringTraits for std::unordered_set
 * \ingroup set
 * \ingroup from_string_traits
 */
template<typename T>
struct FromStringTraits<std::unordered_set<T> > : public Details::FromStringTraitsSTLCompliantContainerInsertHelper<std::unordered_set<T> >
{ /* ... */ };

/*! Partial specialization of Utility::TypeNameTraits for std::set types
 * \ingroup set
 * \ingroup type_name_traits
 */
template<typename T>
struct TypeNameTraits<std::set<T> >
{
  //! Get the type name
  static inline std::string name()
  { return std::string("std::set<") + Utility::typeName<T>()+">"; }
};

/*! Partial specialization of Utility::TypeNameTraits for std::unordered_set types
 * \ingroup unordered_set
 * \ingroup type_name_traits
 */
template<typename T>
struct TypeNameTraits<std::unordered_set<T> >
{
  //! Get the type name
  static inline std::string name()
  { return std::string("std::unordered_set<") + Utility::typeName<T>()+">"; }
};

/*! Partial specialization of ComparisonTraits for std::set
 * \ingroup set
 * \ingroup comparison_traits
 */
template<typename T>
struct ComparisonTraits<std::set<T> > : public Details::ComparisonTraitsAssociativeContainerHelper<std::set<T> >
{ /* ... */ };

/*! Partial specialization of ComparisonTraits for std::unordered_set
 * \ingroup set
 * \ingroup comparison_traits
 */
template<typename T>
struct ComparisonTraits<std::unordered_set<T> > : public Details::ComparisonTraitsAssociativeContainerHelper<std::unordered_set<T> >
{ /* ... */ };

namespace Details{

/*! Partial specialization of the zero helper for std::set
 * \ingroup set
 * \ingroup comparison_traits
 */
template<typename T>
struct ZeroHelper<std::set<T> > : public STLCompliantContainerZeroHelper<std::set<T> >
{ /* ... */ };

/*! Partial specialization of the zero helper for std::unordered_set
 * \ingroup set
 * \ingroup comparison_traits
 */
template<typename T>
struct ZeroHelper<std::unordered_set<T> > : public STLCompliantContainerZeroHelper<std::unordered_set<T> >
{ /* ... */ };
  
} // end Details namespace
  
} // end Utility namespace

namespace std{

/*! Place a std::set in a stream
 * \ingroup set
 */
template<typename T>
inline std::ostream& operator<<( std::ostream& os, const std::set<T>& set )
{
  Utility::toStream( os, set );

  return os;
}

/*! Extract a std::set from a stream
 * \ingroup set
 */
template<typename T>
inline std::istream& operator>>( std::istream& is, std::set<T>& set )
{
  Utility::fromStream( is, set );

  return is;
}

/*! Place a std::unordered_set in a stream
 * \ingroup set
 */
template<typename T>
inline std::ostream& operator<<( std::ostream& os,
                                 const std::unordered_set<T>& set )
{
  Utility::toStream( os, set );

  return os;
}

/*! Extract a std::unordered_set from a stream
 * \ingroup set
 */
template<typename T>
inline std::istream& operator>>( std::istream& is,
                                 std::unordered_set<T>& set )
{
  Utility::fromStream( is, set );

  return is;
}
  
} // end std namespace

#endif // end UTILITY_SET_HPP

//---------------------------------------------------------------------------//
// end Utility_Set.hpp
//---------------------------------------------------------------------------//
