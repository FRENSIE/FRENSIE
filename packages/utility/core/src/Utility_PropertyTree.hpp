//---------------------------------------------------------------------------//
//!
//! \file   Utility_PropertyTree.hpp
//! \author Alex Robinson
//! \brief  Boost property tree helper functions and extensions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_PROPERTY_TREE_HPP
#define UTILITY_PROPERTY_TREE_HPP

// Std Lib Includes
#include <string>
#include <type_traits>
#include <stdexcept>

// Boost Includes
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

// FRENSIE Includes
#include "Utility_Variant.hpp"
#include "Utility_Array.hpp"
#include "Utility_Set.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_FromStringTraits.hpp"

/*! \defgroup ptree Property Tree
 *
 * The property tree is an associative container type provided by boost with
 * support for exporting to and importing from JSON, XML, INI and INFO file
 * types. Unlike the default property tree provided by boost, which uses
 * std::string for both the key and value types, the property tree defined
 * here uses std::string for the key type and Utility::Variant for the
 * value type. This is because the Utility::Variant class provides more
 * advanced string parsing capabilities than the std::iostream classes do.
 */

/*! \defgroup ptree_traits Property Tree Traits
 * \ingroup ptree
 * \ingroup traits
 */

namespace Utility{

/*! The property tree type
 * \ingroup ptree
 */
typedef boost::property_tree::basic_ptree<std::string,Utility::Variant> PropertyTree;

/*! \brief Exception thrown by methods when an attempt to convert a
 * property tree to another type fails
 * \ingroup ptree
 */
class PropertyTreeConversionException : public std::runtime_error
{
public:
  PropertyTreeConversionException( const std::string& msg )
    : std::runtime_error( msg )
  { /* ... */ }

  ~PropertyTreeConversionException() throw()
  { /* ... */ }
};

/*! The comment node key
 *
 * Currently, the boost property tree JSON parser does not have
 * support for normal comment syntax. Users can instead use this comment node
 * key to create comments that will be ignored by our custom property tree
 * conversion methods. This also means that developers must ensure that
 * new property tree conversion methods ignore any node that is assigned
 * to this key.
 * \ingroup ptree
 */
#define PTREE_COMMENT_NODE_KEY "comment"

/*! The type node key
 *
 * This is the default key for specifying a type name
 * \ingroup ptree
 */
#define PTREE_TYPE_KEY "type"

/*! Check if the property tree stores a JSON array
 * \ingroup ptree
 */
bool doesPropertyTreeStoreJSONArray( const Utility::PropertyTree& ptree );

/*! Traits class used to convert to a Utility::PropertyTree
 *
 * Any type that can be converted to a Utility::Variant can also be converted
 * to a Utility::PropertyTree. Specialize this class with the type of interest
 * if a custom conversion is required (e.g. object string conversion is not
 * possible so child nodes must be populated).
 * \ingroup ptree_traits
 */
template<typename T, typename Enabled = void>
struct ToPropertyTreeTraits
{
  //! Data is inlined by default
  typedef std::true_type InlineDefault;

  //! Convert an object of type T to a Utility::PropertyTree
  static PropertyTree toPropertyTree(
                               const T& obj,
                               const bool inline_data = InlineDefault::value );
};

/*! Utility::ToPropertyTreeTraits class specialization for std::array
 * \ingroup ptree_traits
 */
template<typename T, size_t N>
struct ToPropertyTreeTraits<std::array<T,N> >;

/*! Utility::ToPropertyTreeTraits class specialization for std::vector
 * \ingroup ptree_traits
 */
template<typename T>
struct ToPropertyTreeTraits<std::vector<T> >;

/*! Utility::ToPropertyTreeTraits class specialization for std::deque
 * \ingroup ptree_traits
 */
template<typename T>
struct ToPropertyTreeTraits<std::deque<T> >;

/*! Utility::ToPropertyTreeTraits class specialization for std::list
 * \ingroup ptree_traits
 */
template<typename T>
struct ToPropertyTreeTraits<std::list<T> >;

/*! Utility::ToPropertyTreeTraits class specialization for std::forward_list
 * \ingroup ptree_traits
 */
template<typename T>
struct ToPropertyTreeTraits<std::forward_list<T> >;

/*! Utility::ToPropertyTreeTraits class specialization for std::set
 * \ingroup ptree_traits
 */
template<typename T>
struct ToPropertyTreeTraits<std::set<T> >;

/*! Utility::ToPropertyTreeTraits class specialization for std::unordered_set
 * \ingroup ptree_traits
 */
template<typename T>
struct ToPropertyTreeTraits<std::unordered_set<T> >;

/*! Utility::ToPropertyTreeTraits class specialization for std::map
 * \ingroup ptree_traits
 */
template<typename Key, typename T>
struct ToPropertyTreeTraits<std::map<Key,T> >;

/*! Utility::ToPropertyTreeTraits class specialization for std::unordered_map
 * \ingroup ptree_traits
 */
template<typename Key, typename T>
struct ToPropertyTreeTraits<std::unordered_map<Key,T> >;

/*! Traits class used to convert from a Utility::PropertyTree
 *
 * Any type that a Utility::Variant can be converted to can also be created
 * from a Utility::PropertyTree. Specialize this class with the type of
 * interest if a custom conversion is required (e.g. object string conversion
 * is not possible so child nodes must be parsed).
 * \ingroup ptree_traits
 */
template<typename T, typename Enabled = void>
struct FromPropertyTreeTraits
{
  //! The type that a property tree will be converted to (usually T)
  typedef typename Utility::FromStringTraits<T>::ReturnType ReturnType;

  //! Convert the property tree to an object of type T
  template<template<typename,typename...> class STLCompliantSequenceContainer>
  static ReturnType fromPropertyTree(
                 const PropertyTree& ptree,
                 STLCompliantSequenceContainer<std::string>& unused_children );
};

/*! Utility::FromPropertyTreeTraits class specialization for std::vector
 * \ingroup ptree_traits
 */
template<typename T>
struct FromPropertyTreeTraits<std::vector<T> >;

/*! Utility::FromPropertyTreeTraits class specialization for std::deque
 * \ingroup ptree_traits
 */
template<typename T>
struct FromPropertyTreeTraits<std::deque<T> >;

/*! Utility::FromPropertyTreeTraits class specialization for std::list
 * \ingroup ptree_traits
 */
template<typename T>
struct FromPropertyTreeTraits<std::list<T> >;

/*! Utility::FromPropertyTreeTraits class specialization for std::forward_list
 * \ingroup ptree_traits
 */
template<typename T>
struct FromPropertyTreeTraits<std::forward_list<T> >;

/*! Utility::FromPropertyTreeTraits class specialization for std::set
 * \ingroup ptree_traits
 */
template<typename T>
struct FromPropertyTreeTraits<std::set<T> >;

/*! Utility::FromPropertyTreeTraits class specialization for std::unordered_set
 * \ingroup ptree_traits
 */
template<typename T>
struct FromPropertyTreeTraits<std::unordered_set<T> >;

/*! Utility::FromPropertyTreeTraits class specialization for std::map
 * \ingroup ptree_traits
 */
template<typename Key, typename T>
struct FromPropertyTreeTraits<std::map<Key,T> >;

/*! Utility::FromPropertyTreeTraits class specialization for std::unordered_map
 * \ingroup ptree_traits
 */
template<typename Key, typename T>
struct FromPropertyTreeTraits<std::unordered_map<Key,T> >;

/*! Convert the object to a property tree
 *
 * This method relies on the Utility::ToPropertyTreeTraits class associated
 * with type T to do the conversion. It is possible to overload this method
 * for a custom type, however it is recommended that a specialization of
 * the Utility::ToPropertyTreeTraits class is created instead.
 * \ingroup ptree
 */
template<typename T>
Utility::PropertyTree toPropertyTree( const T& obj, const bool inline_data );

/*! Convert the object to a property tree
 *
 * This method relies on the Utility::ToPropertyTreeTraits class associated
 * with type T to do the conversion. It is possible to overload this method
 * for a custom type, however it is recommended that a specialization of
 * the Utility::ToPropertyTreeTraits class is created instead. The inline
 * data default value for type T will be used.
 * \ingroup ptree
 */
template<typename T>
typename std::enable_if<std::is_same<typename Utility::ToPropertyTreeTraits<T>::InlineDefault::value_type,bool>::value,Utility::PropertyTree>::type toPropertyTree( const T& obj );

/*! Convert the property tree to an object of the desired type
 *
 * This method relies on the Utility::FromPropertyTreeTraits class associated
 * with type T to do the conversion. Any children in the node that are unused
 * will be stored in the unused_children container.
 * \ingroup ptree
 */
template<typename T,
         template<typename,typename...> class STLCompliantSequenceContainer>
typename FromPropertyTreeTraits<T>::ReturnType
fromPropertyTree( const Utility::PropertyTree& ptree,
                  STLCompliantSequenceContainer<std::string>& unused_children );

/*! Convert the property tree to an object of the desired type
 *
 * This method relies on the Utility::FromPropertyTreeTraits class associated
 * with type T to do the conversion. Any unused children can be optionally
 * logged with the warning logger.
 * \ingroup ptree
 */
template<typename T>
typename FromPropertyTreeTraits<T>::ReturnType
fromPropertyTree( const Utility::PropertyTree& ptree,
                  const bool log_unused_children = true );

/*! Log the unused children or property tree
 * \ingroup ptree
 */
template<template<typename,typename...> class STLCompliantSequenceContainer>
void logUnusedChildrenOfPropertyTree(
                 STLCompliantSequenceContainer<std::string>& unused_children );

/*! Specialization of Utility::ToStringTraits for Utility::PropertyTree
 * \ingroup ptree
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<PropertyTree>
{
  //! Convert a PropertyTree to a string
  static std::string toString( const PropertyTree& obj );

  //! Place the PropertyTree in a stream
  static void toStream( std::ostream& os, const PropertyTree& obj );
};

/*! Specialization of Utility::FromStringTraits for Utility::PropertyTree
 * \ingroup ptree
 * \ingroup from_string_traits
 */
template<>
struct FromStringTraits<PropertyTree>
{
  //! The type that a string will be converted to
  typedef PropertyTree ReturnType;

  //! Convert the string to a PropertyTree object
  static ReturnType fromString( const std::string& obj_rep );

  //! Extract a PropertyTree from a stream
  static void fromStream( std::istream& is,
                          PropertyTree& obj,
                          const std::string& delims = std::string() );
};

} // end Utility namespace

namespace boost {

namespace property_tree {

/*! \brief Specialize boost::property_tree::translator_between so that we can
 * use a custom translator between Utility::Variant and other types.
 * \ingroup ptree
 */
template<typename T>
struct translator_between<Utility::Variant,T>;

} // end property_tree namespace

} // end boost namespace

namespace std{

/*! Place a Utility::PropertyTree in a stream
 * \ingroup ptree
 */
inline std::ostream& operator<<( std::ostream& os,
                                 const Utility::PropertyTree& ptree )
{
  Utility::toStream( os, ptree );

  return os;
}

/*! Extract a Utility::PropertyTree from a stream
 * \ingroup ptree
 */
inline std::istream& operator>>( istream& is,
                                 Utility::PropertyTree& ptree )
{
  Utility::fromStream( is, ptree );

  return is;
}

} // end std namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_PropertyTree_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_PROPERTY_TREE_HPP

//---------------------------------------------------------------------------//
// end Utility_PropertyTree.hpp
//---------------------------------------------------------------------------//
