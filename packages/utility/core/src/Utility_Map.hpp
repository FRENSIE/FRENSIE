//---------------------------------------------------------------------------//
//!
//! \file   Utility_Map.hpp
//! \author Alex Robinson
//! \brief  Helper function and class declarations for std::map and
//!         std::unordered_map
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_MAP_HPP
#define UTILITY_MAP_HPP

// Std Lib Includes
#include <iostream>
#include <map>
#include <unordered_map>

// Boost Includes
#include <boost/serialization/map.hpp>
#include <boost/serialization/unordered_map.hpp>

// FRENSIE Includes
#include "Utility_Tuple.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_IteratorTypeTraits.hpp"
#include "Utility_ComparisonTraits.hpp"
#include "Utility_TypeNameTraits.hpp"

/*! \defgroup map Map
 *
 * Additional helper functions and classes for use with the set::map and
 * std::unordered_map have been defined that do not appear in the standard
 * library.
 */

namespace Utility{

/*! Partial specialization of ToStringTraits for std::map
 * \ingroup map
 * \ingroup to_string_traits
 */
template<typename Key, typename T>
struct ToStringTraits<std::map<Key,T> > : public Details::ToStringTraitsIteratorHelper<std::map<Key,T> >
{ /* ... */ };

/*! Partial specialization of ToStringTraits for std::map iterator types
 *
 * Unfortunately this cannot be used with a past-the-end iterator due to 
 * the dereference.
 * \ingroup map
 * \ingroup to_string_traits
 */
template<typename Iterator>
struct ToStringTraits<Iterator,typename std::enable_if<
         (std::is_same<Iterator,typename std::map<typename Details::RemovePairMemberCV<typename std::iterator_traits<Iterator>::value_type>::T1,typename Details::RemovePairMemberCV<typename std::iterator_traits<Iterator>::value_type>::T2>::iterator>::value ||
          std::is_same<Iterator,typename std::map<typename Details::RemovePairMemberCV<typename std::iterator_traits<Iterator>::value_type>::T1,typename Details::RemovePairMemberCV<typename std::iterator_traits<Iterator>::value_type>::T2>::const_iterator>::value ||
          std::is_same<Iterator,typename std::map<typename Details::RemovePairMemberCV<typename std::iterator_traits<Iterator>::value_type>::T1,typename Details::RemovePairMemberCV<typename std::iterator_traits<Iterator>::value_type>::T2>::reverse_iterator>::value ||
          std::is_same<Iterator,typename std::map<typename Details::RemovePairMemberCV<typename std::iterator_traits<Iterator>::value_type>::T1,typename Details::RemovePairMemberCV<typename std::iterator_traits<Iterator>::value_type>::T2>::const_reverse_iterator>::value)>::type>
{
  //! Convert the pointer type to a string
  static inline std::string toString( const Iterator& obj )
  { return ToStringTraits<typename std::iterator_traits<Iterator>::pointer>::toString( &(*obj) ); }

  //! Place the pointer type in a stream
  static inline void toStream( std::ostream& os, const Iterator& obj )
  { return ToStringTraits<typename std::iterator_traits<Iterator>::pointer>::toStream( os, &(*obj) ); }
};

/*! Partial specialization of ToStringTraits for std::unordered_map
 * \ingroup map
 * \ingroup to_string_traits
 */
template<typename Key, typename T>
struct ToStringTraits<std::unordered_map<Key,T> > : public Details::ToStringTraitsIteratorHelper<std::unordered_map<Key,T> >
{ /* ... */ };

/*! Partial specialization of ToStringTraits for std::unordered_map iterator types
 *
 * Unfortunately this cannot be used with a past-the-end iterator due to 
 * the dereference.
 * \ingroup map
 * \ingroup to_string_traits
 */
template<typename Iterator>
struct ToStringTraits<Iterator,typename std::enable_if<
         (std::is_same<Iterator,typename std::unordered_map<typename Details::InterceptUnhashableType<typename std::iterator_traits<Iterator>::value_type>::T1,typename Details::InterceptUnhashableType<typename std::iterator_traits<Iterator>::value_type>::T2>::iterator>::value ||
          std::is_same<Iterator,typename std::unordered_map<typename Details::InterceptUnhashableType<typename std::iterator_traits<Iterator>::value_type>::T1,typename Details::InterceptUnhashableType<typename std::iterator_traits<Iterator>::value_type>::T2>::const_iterator>::value)>::type>
{
  //! Convert the pointer type to a string
  static inline std::string toString( const Iterator& obj )
  { return ToStringTraits<typename std::iterator_traits<Iterator>::pointer>::toString( &(*obj) ); }

  //! Place the pointer type in a stream
  static inline void toStream( std::ostream& os, const Iterator& obj )
  { return ToStringTraits<typename std::iterator_traits<Iterator>::pointer>::toStream( os, &(*obj) ); }
};

/*! Partial specialization of FromStringTraits for std::map
 * \ingroup map
 * \ingroup from_string_traits
 */
template<typename Key, typename T>
struct FromStringTraits<std::map<Key,T> > : public Details::FromStringTraitsSTLCompliantContainerInsertHelper<std::map<Key,T>, std::pair<Key,T>, std::map<Key,T>, std::pair<Key,T> >
{ /* ... */ };

/*! Partial specialization of FromStringTraits for std::unordered_map
 * \ingroup map
 * \ingroup from_string_traits
 */
template<typename Key, typename T>
struct FromStringTraits<std::unordered_map<Key,T> > : public Details::FromStringTraitsSTLCompliantContainerInsertHelper<std::unordered_map<Key,T>, std::pair<Key,T>, std::unordered_map<Key,T>, std::pair<Key,T> >
{ /* ... */ };

/*! Partial specialization of Utility::TypeNameTraits for std::map types
 * \ingroup map
 * \ingroup type_name_traits
 */
template<typename Key, typename T>
struct TypeNameTraits<std::map<Key,T> >
{
  //! Get the type name
  static inline std::string name()
  {
    return std::string("std::map<") + Utility::typeName<Key>() + "," +
      Utility::typeName<T>()+">";
  }
};

/*! Partial specialization of Utility::TypeNameTraits for std::unordered_map types
 * \ingroup unordered_map
 * \ingroup type_name_traits
 */
template<typename Key, typename T>
struct TypeNameTraits<std::unordered_map<Key,T> >
{
  //! Get the type name
  static inline std::string name()
  {
    return std::string("std::unordered_map<") + Utility::typeName<Key>() + ","+
      Utility::typeName<T>()+">";
  }
};

/*! Partial specialization of ComparisonTraits for std::map
 * \ingroup map
 * \ingroup comparison_traits
 */
template<typename Key, typename T>
struct ComparisonTraits<std::map<Key,T> > : public Details::ComparisonTraitsAssociativeContainerHelper<std::map<Key,T> >
{ /* ... */ };

/*! Partial specialization of ComparisonTraits for std::unordered_map
 * \ingroup map
 * \ingroup comparison_traits
 */
template<typename Key, typename T>
struct ComparisonTraits<std::unordered_map<Key,T> > : public Details::ComparisonTraitsAssociativeContainerHelper<std::unordered_map<Key,T> >
{ /* ... */ };



// A hash function used to hash a pair of any kind
struct custom_hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const
    {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};



} // end Utility namespace

namespace std{

/*! Compare two map elements
 * 
 * The most common usage of this overload is when either LeftKey or RightKey
 * only differ based on their const qualification (the value_type of a 
 * std::map and std::unordered_map with template parameters Key and T is
 * std::pair<const Key,T>).
 * \ingroup map
 * \ingroup comparison_traits
 */
template<typename LeftKey, typename LeftT,
         typename RightKey, typename RightT>
inline bool operator==( const std::pair<LeftKey,LeftT>& left_value,
                        const std::pair<RightKey,RightT>& right_value )
{
  return left_value.first == right_value.first &&
    left_value.second == right_value.second;
}

/*! Place a std::map in a stream
 * \ingroup map
 */
template<typename Key, typename T>
inline std::ostream& operator<<( std::ostream& os,
                                 const std::map<Key,T>& map )
{
  Utility::toStream( os, map );

  return os;
}

/*! Extract a std::map from a stream
 * \ingroup map
 */
template<typename Key, typename T>
inline std::istream& operator>>( std::istream& is,
                                 std::map<Key,T>& map )
{
  Utility::fromStream( is, map );

  return is;
}
  
/*! Place a std::unordered_map in a stream
 * \ingroup map
 */
template<typename Key, typename T>
inline std::ostream& operator<<( std::ostream& os,
                                 const std::unordered_map<Key,T>& map )
{
  Utility::toStream( os, map );

  return os;
}

/*! Extract a std::unordered_map from a stream
 * \ingroup map
 */
template<typename Key, typename T>
inline std::istream& operator>>( std::istream& is,
                                 std::unordered_map<Key,T>& map )
{
  Utility::fromStream( is, map );

  return is;
}
  
} // end std namespace

#endif // end UTILITY_MAP_HPP

//---------------------------------------------------------------------------//
// end Utility_Map.hpp
//---------------------------------------------------------------------------//
