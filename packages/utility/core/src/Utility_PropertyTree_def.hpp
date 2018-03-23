//---------------------------------------------------------------------------//
//!
//! \file   Utility_PropertyTree_def.hpp
//! \author Alex Robinson
//! \brief  Boost property tree helper function template definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_PROPERTY_TREE_DEF_HPP
#define UTILITY_PROPERTY_TREE_DEF_HPP

// FRENSIE Includes
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace Utility{

namespace Details{

/*! The generic ptree object translator
 *
 * This class relies on Utility::FromStringTraits to extract values from a
 * string and Utility::ToStingTraits to convert values to a string.
 * \ingroup ptree
 */
template<typename T>
struct GenericPTreeObjectTranslator
{
  typedef Utility::Variant internal_type;
  typedef typename Utility::FromStringTraits<typename std::conditional<std::is_same<char*,typename std::remove_const<typename std::decay<T>::type>::type>::value,std::string,T>::type>::ReturnType external_type;

  //! Convert a Utility::Variant to an object of type T
  static inline boost::optional<external_type> get_value( const internal_type& obj_rep )
  {
    if( !obj_rep.isNull() )
    {
      try{
        return boost::optional<external_type>(
                             Utility::variant_cast<external_type>( obj_rep ) );
      }
      catch( const std::runtime_error& error )
      {
        FRENSIE_LOG_TAGGED_ERROR( "PropertyTree", error.what() );

        return boost::optional<external_type>( boost::none );
      }
    }
    else
      return boost::optional<external_type>( boost::none );
  }

  //! Convert an object of type T to a Utility::Variant
  static inline boost::optional<internal_type> put_value( const T& obj )
  {
    return Utility::Variant( obj );
  }
};

/*! The generic ptree object translator specialization for std::string
 * \ingroup ptree
 */
template<>
struct GenericPTreeObjectTranslator<std::string>
{
  typedef Utility::Variant internal_type;
  typedef typename Utility::FromStringTraits<std::string>::ReturnType external_type;

  //! Convert a Utility::Variant to a std::string
  static inline boost::optional<external_type> get_value( const internal_type& obj_rep )
  {
    return boost::optional<external_type>( obj_rep.toString() );
  }

  // Convert an std::string to a Utility::Variant
  static inline boost::optional<internal_type> put_value( const std::string& obj )
  {
    return Utility::Variant( obj );
  }
};

/*! \brief Helper class for converting property tree nodes that contain a
 * JSON array to the desired sequence container
 * \ingroup ptree
 */
template<typename T, typename Enabled = void>
struct JSONArrayPropertyTreeNodeToSequenceContainerHelper
{
  /*! Convert json array property tree node to sequence container
    *
    * You must verify that the node actually contains a JSON array before
    * calling this method.
    */
  template<typename ElementInsertionMemberFunction,
           typename FinalizeFunction>
  static T convert( const Utility::PropertyTree& ptree,
                    ElementInsertionMemberFunction insert_element,
                    FinalizeFunction finalize_container );
};

/*! \brief Specialization of JSONArrayPropertyTreeNodeToSequenceContainerHelper for containers with a Utility::Variant value type
 * \ingroup ptree
 */
template<typename T>
struct JSONArrayPropertyTreeNodeToSequenceContainerHelper<T,typename std::enable_if<std::is_same<typename T::value_type, Utility::Variant>::value>::type>
{
  /*! Convert json array property tree node to sequence container
    *
    * You must verify that the node actually contains a JSON array before
    * calling this method.
    */
  template<typename ElementInsertionMemberFunction,
           typename FinalizeFunction>
  static T convert( const Utility::PropertyTree& ptree,
                    ElementInsertionMemberFunction insert_element,
                    FinalizeFunction finalize_container );
};

/*! Helper class for converting a sequence container to a Utility::PropertyTree
 * \ingroup ptree_traits
 */
template<typename T>
struct SequenceContainerToPropertyTreeHelper
{
  //! Inline data is the default
  typedef std::true_type InlineDefault;

  //! Convert a sequence container object object to a Utility::PropertyTree
  static Utility::PropertyTree toPropertyTree(
                             const T& container,
                             const bool inline_data = InlineDefault::value );
};

/*! Helper class for converting a Utility::PropertyTree to a sequence container
 * \ingroup ptree_traits
 */
template<typename T>
struct SequenceContainerFromPropertyTreeBaseHelper
{
  //! The return type from a PropertyTree conversion
  typedef T ReturnType;

protected:

  //! Convert the property tree to a container object
  template<typename ElementInsertionMemberFunction,
           typename FinalizeFunction>
  static ReturnType fromPropertyTreeImpl(
                               const Utility::PropertyTree& ptree,
                               ElementInsertionMemberFunction insert_element,
                               FinalizeFunction finalize_container );
};

/*! \brief Helper class for converting a Utility::PropertyTree to a sequence
 * container with a push_back method
 * \ingroup ptree_traits
 */
template<typename T>
struct SequenceContainerFromPropertyTreePushBackHelper : public SequenceContainerFromPropertyTreeBaseHelper<T>
{
protected:

  //! The base helper class type
  typedef SequenceContainerFromPropertyTreeBaseHelper<T> BaseType;

public:

  //! The return type from a PropertyTree conversion
  typedef typename BaseType::ReturnType ReturnType;

  //! Convert the property tree to a container object
  template<template<typename,typename...> class STLCompliantSequenceContainer>
  static inline ReturnType fromPropertyTree(
                             const PropertyTree& ptree,
                             STLCompliantSequenceContainer<std::string>& )
  {
    return BaseType::fromPropertyTreeImpl( ptree,
                                           (void (ReturnType::*)(const typename ReturnType::value_type&))&ReturnType::push_back,
                                           &ReturnType::empty );
  }
};

/*! \brief Helper class for converting a Utility::PropertyTree to a sequence
 * container with an insert method
 * \ingroup ptree_traits
 */
template<typename T>
struct SequenceContainerFromPropertyTreeInsertHelper : public SequenceContainerFromPropertyTreeBaseHelper<T>
{
protected:

  //! The base helper class type
  typedef SequenceContainerFromPropertyTreeBaseHelper<T> BaseType;

public:

  //! The return type from a PropertyTree conversion
  typedef typename BaseType::ReturnType ReturnType;

  //! Convert the property tree to a container object
  template<template<typename,typename...> class STLCompliantSequenceContainer>
  static inline ReturnType fromPropertyTree(
                             const PropertyTree& ptree,
                             STLCompliantSequenceContainer<std::string>& )
  {
    return BaseType::fromPropertyTreeImpl( ptree,
                                           (std::pair<typename ReturnType::iterator,bool> (ReturnType::*)(const typename ReturnType::value_type&))&ReturnType::insert,
                                           &ReturnType::empty );
  }
};

/*! \brief Helper class for converting an associative container to a
 * Utility::PropertyTree
 * \ingroup ptree_traits
 */
template<template<typename,typename,typename...> class STLCompliantAssociativeContainer,
         typename Key,
         typename T>
struct AssociativeContainerToPropertyTreeHelper
{
  //! Inline data is not the default
  typedef std::false_type InlineDefault;

  //! Convert a sequence container object object to a Utility::PropertyTree
  static inline Utility::PropertyTree toPropertyTree(
                      const STLCompliantAssociativeContainer<Key,T>& container,
                      const bool inline_data = InlineDefault::value );
};

/*! \brief Helper class for converting a Utility::PropertyTree to an
 * associative container
 *
 * This default template class assumes that the template type T is a basic
 * type (e.g. int, double, etc.)
 * \ingroup ptree_traits
 */
template<template<typename,typename,typename...> class STLCompliantAssociativeContainer,
         typename Key,
         typename T,
         typename Enabled = void>
struct AssociativeContainerFromPropertyTreeHelper
{
  //! The type that a property tree will be converted to
  typedef STLCompliantAssociativeContainer<Key,T> ReturnType;

  //! Convert the property tree to an associative container
  template<template<typename,typename...> class STLCompliantSequenceContainer>
  static ReturnType fromPropertyTree(
                 const PropertyTree& ptree,
                 STLCompliantSequenceContainer<std::string>& unused_children );
};

/*! \brief Partial specialization of AssociativeContainerFromPropertyTreeHelper
 * for Utility::Variant value type
 */
template<template<typename,typename,typename...> class STLCompliantAssociativeContainer,
         typename Key>
struct AssociativeContainerFromPropertyTreeHelper<STLCompliantAssociativeContainer,Key,Utility::Variant>
{
  //! The type that a property tree will be converted to
  typedef STLCompliantAssociativeContainer<Key,Utility::Variant> ReturnType;

  //! Convert the property tree to an associative container
  template<template<typename,typename...> class STLCompliantSequenceContainer>
  static ReturnType fromPropertyTree(
             const PropertyTree& ptree,
             STLCompliantSequenceContainer<std::string>& unused_children );
};

} // end Details namespace

// Convert an object of type T to a Utility::PropertyTree
template<typename T, typename Enabled>
inline PropertyTree ToPropertyTreeTraits<T,Enabled>::toPropertyTree(
                                                                  const T& obj,
                                                                  const bool )
{
  Utility::PropertyTree ptree;
  ptree.data().setValue( obj );

  return ptree;
}

// Utility::ToPropertyTreeTraits class specialization for std::array
template<typename T, size_t N>
struct ToPropertyTreeTraits<std::array<T,N> > : public Details::SequenceContainerToPropertyTreeHelper<std::array<T,N> >
{ /* ... */ };

// Utility::ToPropertyTreeTraits class specialization for std::vector
template<typename T>
struct ToPropertyTreeTraits<std::vector<T> > : public Details::SequenceContainerToPropertyTreeHelper<std::vector<T> >
{ /* ... */ };

// Utility::ToPropertyTreeTraits class specialization for std::deque
template<typename T>
struct ToPropertyTreeTraits<std::deque<T> > : public Details::SequenceContainerToPropertyTreeHelper<std::deque<T> >
{ /* ... */ };

// Utility::ToPropertyTreeTraits class specialization for std::list
template<typename T>
struct ToPropertyTreeTraits<std::list<T> > : public Details::SequenceContainerToPropertyTreeHelper<std::list<T> >
{ /* ... */ };

// Utility::ToPropertyTreeTraits class specialization for std::forward_list
template<typename T>
struct ToPropertyTreeTraits<std::forward_list<T> > : public Details::SequenceContainerToPropertyTreeHelper<std::forward_list<T> >
{ /* ... */ };

// Utility::ToPropertyTreeTraits class specialization for std::set
template<typename T>
struct ToPropertyTreeTraits<std::set<T> > : public Details::SequenceContainerToPropertyTreeHelper<std::set<T> >
{ /* ... */ };

// Utility::ToPropertyTreeTraits class specialization for std::unordered_set
template<typename T>
struct ToPropertyTreeTraits<std::unordered_set<T> > : public Details::SequenceContainerToPropertyTreeHelper<std::unordered_set<T> >
{ /* ... */ };

// Utility::ToPropertyTreeTraits class specialization for std::map
template<typename Key, typename T>
struct ToPropertyTreeTraits<std::map<Key,T> > : public Details::AssociativeContainerToPropertyTreeHelper<std::map,Key,T>
{ /* ... */ };

// Utility::ToPropertyTreeTraits class specialization for std::unordered_map
template<typename Key, typename T>
struct ToPropertyTreeTraits<std::unordered_map<Key,T> > : public Details::AssociativeContainerToPropertyTreeHelper<std::unordered_map,Key,T>
{ /* ... */ };

// Convert the object to a property tree
template<typename T>
inline Utility::PropertyTree toPropertyTree( const T& obj,
                                             const bool inline_data )
{
  return ToPropertyTreeTraits<T>::toPropertyTree( obj, inline_data );
}

// Convert the object to a property tree
template<typename T>
inline typename std::enable_if<std::is_same<typename Utility::ToPropertyTreeTraits<T>::InlineDefault::value_type,bool>::value,Utility::PropertyTree>::type toPropertyTree( const T& obj )
{
  return Utility::toPropertyTree( obj, ToPropertyTreeTraits<T>::InlineDefault::value );
}

// Convert the property tree to an object of type T
template<typename T, typename Enabled>
template<template<typename,typename...> class STLCompliantSequenceContainer>
inline auto FromPropertyTreeTraits<T,Enabled>::fromPropertyTree(
                    const PropertyTree& ptree,
                    STLCompliantSequenceContainer<std::string>& ) -> ReturnType
{
  TEST_FOR_EXCEPTION( ptree.size() != 0,
                      Utility::PropertyTreeConversionException,
                      "Could not convert the property tree to the desired "
                      "type (only inline data is allowed for this type)!" );

  try{
    return Utility::variant_cast<T>( ptree.data() );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                              Utility::PropertyTreeConversionException,
                              "Could not convert the property tree data to "
                              "the desired type!" );
}

/*! Utility::FromPropertyTreeTraits class specialization for std::vector
 * \ingroup ptree_traits
 */
template<typename T>
struct FromPropertyTreeTraits<std::vector<T> > : public Details::SequenceContainerFromPropertyTreePushBackHelper<std::vector<T> >
{ /* ... */ };

/*! Utility::FromPropertyTreeTraits class specialization for std::deque
 * \ingroup ptree_traits
 */
template<typename T>
struct FromPropertyTreeTraits<std::deque<T> > : public Details::SequenceContainerFromPropertyTreePushBackHelper<std::deque<T> >
{ /* ... */ };

/*! Utility::FromPropertyTreeTraits class specialization for std::list
 * \ingroup ptree_traits
 */
template<typename T>
struct FromPropertyTreeTraits<std::list<T> > : public Details::SequenceContainerFromPropertyTreePushBackHelper<std::list<T> >
{ /* ... */ };

/*! Utility::FromPropertyTreeTraits class specialization for std::forward_list
 * \ingroup ptree_traits
 */
template<typename T>
struct FromPropertyTreeTraits<std::forward_list<T> > : public Details::SequenceContainerFromPropertyTreeBaseHelper<std::forward_list<T> >
{
protected:

  //! The base helper class type
  typedef Details::SequenceContainerFromPropertyTreeBaseHelper<std::forward_list<T> > BaseType;

public:

  //! The return type from a PropertyTree conversion
  typedef typename BaseType::ReturnType ReturnType;

  //! Convert the property tree to a container object
  template<template<typename,typename...> class STLCompliantSequenceContainer>
  static inline ReturnType fromPropertyTree(
                             const PropertyTree& ptree,
                             STLCompliantSequenceContainer<std::string>& )
  {
    return BaseType::fromPropertyTreeImpl( ptree,
                                           (void (ReturnType::*)(const typename ReturnType::value_type&))&ReturnType::push_front,
                                           &ReturnType::reverse );
  }
};

/*! Utility::FromPropertyTreeTraits class specialization for std::set
 * \ingroup ptree_traits
 */
template<typename T>
struct FromPropertyTreeTraits<std::set<T> > : public Details::SequenceContainerFromPropertyTreeInsertHelper<std::set<T> >
{ /* ... */ };

/*! Utility::FromPropertyTreeTraits class specialization for std::unordered_set
 * \ingroup ptree_traits
 */
template<typename T>
struct FromPropertyTreeTraits<std::unordered_set<T> > : public Details::SequenceContainerFromPropertyTreeInsertHelper<std::unordered_set<T> >
{ /* ... */ };

/*! Utility::FromPropertyTreeTraits class specialization for std::map
 * \ingroup ptree_traits
 */
template<typename Key, typename T>
struct FromPropertyTreeTraits<std::map<Key,T> > : public Details::AssociativeContainerFromPropertyTreeHelper<std::map,Key,T>
{ /* ... */ };

/*! Utility::FromPropertyTreeTraits class specialization for std::unordered_map
 * \ingroup ptree_traits
 */
template<typename Key, typename T>
struct FromPropertyTreeTraits<std::unordered_map<Key,T> > : public Details::AssociativeContainerFromPropertyTreeHelper<std::unordered_map,Key,T>
{ /* ... */ };

// Convert the property tree to an object of the desired type
template<typename T,
         template<typename,typename...> class STLCompliantSequenceContainer>
inline typename FromPropertyTreeTraits<T>::ReturnType
fromPropertyTree( const Utility::PropertyTree& ptree,
                  STLCompliantSequenceContainer<std::string>& unused_children )
{
  return FromPropertyTreeTraits<T>::fromPropertyTree( ptree, unused_children );
}

// Convert the property tree to an object of the desired type
template<typename T>
typename FromPropertyTreeTraits<T>::ReturnType
fromPropertyTree( const Utility::PropertyTree& ptree,
                  const bool log_unused_children )
{
  std::vector<std::string> unused_children;

  typename FromPropertyTreeTraits<T>::ReturnType obj =
    Utility::fromPropertyTree<T>( ptree, unused_children );

  // Log the unused children requested
  if(  log_unused_children )
    Utility::logUnusedChildrenOfPropertyTree( unused_children );

  return obj;
}

// Log the unused children or property tree
/*! \details Logging will only occur if there is at least one unused child.
 */
template<template<typename,typename...> class STLCompliantSequenceContainer>
void logUnusedChildrenOfPropertyTree(
                  STLCompliantSequenceContainer<std::string>& unused_children )
{
  if( unused_children.size() > 0 )
  {
    std::ostringstream oss;

    for( size_t i = 0; i < unused_children.size(); ++i )
    {
      oss << "\"" << unused_children[i] << "\"";

      if( i < unused_children.size() - 2 )
        oss << ", ";
      else if( i == unused_children.size() - 2 )
        oss << " and ";
    }

    FRENSIE_LOG_TAGGED_WARNING( "PropertyTree",
                                "property tree nodes " << oss.str() <<
                                " are unused!" );
  }
}

namespace Details{

// Convert json array property tree node to sequence container
template<typename T, typename Enabled>
template<typename ElementInsertionMemberFunction,
         typename FinalizeFunction>
inline T JSONArrayPropertyTreeNodeToSequenceContainerHelper<T,Enabled>::convert(
                                const Utility::PropertyTree& ptree,
                                ElementInsertionMemberFunction insert_element,
                                FinalizeFunction finalize_container )
{
  T sequence_container;

  Utility::PropertyTree::const_iterator node_it, node_end;
  node_it = ptree.begin();
  node_end = ptree.end();

  size_t i = 0;

  while( node_it != node_end )
  {
    try{
      (sequence_container.*insert_element)( Utility::variant_cast<typename T::value_type>( node_it->second.data() ) );
    }
    EXCEPTION_CATCH_RETHROW_AS( Utility::StringConversionException,
                                Utility::PropertyTreeConversionException,
                                "Unable to convert JSON element " << i <<
                                " to the desired type!" );
    ++i;
    ++node_it;
  }

  (sequence_container.*finalize_container)();

  return sequence_container;
}


// Convert json array property tree node to sequence container
template<typename T>
template<typename ElementInsertionMemberFunction,
         typename FinalizeFunction>
inline T JSONArrayPropertyTreeNodeToSequenceContainerHelper<T,typename std::enable_if<std::is_same<typename T::value_type, Utility::Variant>::value>::type>::convert(
                                const Utility::PropertyTree& ptree,
                                ElementInsertionMemberFunction insert_element,
                                FinalizeFunction finalize_container )
{
  T sequence_container;

  Utility::PropertyTree::const_iterator node_it, node_end;
  node_it = ptree.begin();
  node_end = ptree.end();

  while( node_it != node_end )
  {
    (sequence_container.*insert_element)( node_it->second.data() );

    ++node_it;
  }

  (sequence_container.*finalize_container)();

  return sequence_container;
}

// Convert a sequence container object object to a Utility::PropertyTree
template<typename T>
inline Utility::PropertyTree
SequenceContainerToPropertyTreeHelper<T>::toPropertyTree(
                                                       const T& container,
                                                       const bool inline_data )
{
  Utility::PropertyTree ptree;

  if( inline_data )
    ptree.data().setValue( container );
  else
  {
    typename T::const_iterator
      container_it, container_end;
    container_it = container.begin();
    container_end = container.end();

    // Create a JSON array
    while( container_it != container_end )
    {
      ptree.push_back( std::make_pair("", Utility::toPropertyTree( *container_it, inline_data )) );

      ++container_it;
    }
  }

  return ptree;
}

// Convert the property tree to a container object
template<typename T>
template<typename ElementInsertionMemberFunction,
         typename FinalizeFunction>
inline auto SequenceContainerFromPropertyTreeBaseHelper<T>::fromPropertyTreeImpl(
                  const PropertyTree& ptree,
                  ElementInsertionMemberFunction insert_element,
                  FinalizeFunction finalize_container ) -> ReturnType
{
  // This property tree stores an array
  if( Utility::doesPropertyTreeStoreJSONArray( ptree ) )
  {
    return JSONArrayPropertyTreeNodeToSequenceContainerHelper<ReturnType>::convert( ptree, insert_element, finalize_container );
  }
  // This is a leaf node (the data is inline)
  else if( ptree.size() == 0 )
  {
    try{
      return Utility::variant_cast<ReturnType>( ptree.data() );
    }
    EXCEPTION_CATCH_RETHROW_AS( Utility::StringConversionException,
                                Utility::PropertyTreeConversionException,
                                "Could not convert the property tree to a "
                                "sequence container!" );
  }
  else
  {
    THROW_EXCEPTION( Utility::PropertyTreeConversionException,
                     "Could not convert the property tree to a sequence "
                     "container because the data is not stored inline or as "
                     "a JSON array!" );
    return ReturnType();
  }
}

// Convert a sequence container object object to a Utility::PropertyTree
template<template<typename,typename,typename...> class STLCompliantAssociativeContainer,
         typename Key,
         typename T>
inline Utility::PropertyTree AssociativeContainerToPropertyTreeHelper<STLCompliantAssociativeContainer,Key,T>::toPropertyTree(
                      const STLCompliantAssociativeContainer<Key,T>& container,
                      const bool inline_data )
{
  Utility::PropertyTree ptree;

  if( inline_data )
    ptree.data().setValue( container );
  else
  {
    typename STLCompliantAssociativeContainer<Key,T>::const_iterator
      container_it, container_end;
    container_it = container.begin();
    container_end = container.end();

    // Create child nodes
    while( container_it != container_end )
    {
      ptree.put_child( Utility::toString(container_it->first),
                       Utility::toPropertyTree( container_it->second, inline_data ) );

      ++container_it;
    }
  }

  return ptree;
}

// Convert the property tree to an associative container
template<template<typename,typename,typename...> class STLCompliantAssociativeContainer,
         typename Key,
         typename T,
         typename Enabled>
template<template<typename,typename...> class STLCompliantSequenceContainer>
inline auto AssociativeContainerFromPropertyTreeHelper<STLCompliantAssociativeContainer,Key,T,Enabled>::fromPropertyTree(
                    const PropertyTree& ptree,
                    STLCompliantSequenceContainer<std::string>& ) -> ReturnType
{
  // Check that this node does not store an array
  TEST_FOR_EXCEPTION( Utility::doesPropertyTreeStoreJSONArray( ptree ),
                      Utility::PropertyTreeConversionException,
                      "Could not convert the property tree to the "
                      "associative container type because the property tree "
                      "contains a JSON array!" );

  if( ptree.size() == 0 )
  {
    try{
      return Utility::variant_cast<ReturnType>( ptree.data() );
    }
    EXCEPTION_CATCH_RETHROW_AS( Utility::StringConversionException,
                                Utility::PropertyTreeConversionException,
                                "Could not convert the property tree to an "
                                "associative container!" );
  }
  else
  {
    ReturnType map;

    Utility::PropertyTree::const_iterator node_it, node_end;
    node_it = ptree.begin();
    node_end = ptree.end();

    while( node_it != node_end )
    {
      Key map_key;

      try{
        map_key = Utility::fromString<Key>( node_it->first );
      }
      EXCEPTION_CATCH_RETHROW_AS( Utility::StringConversionException,
                                  Utility::PropertyTreeConversionException,
                                  "Could not convert property tree node key "
                                  << node_it->first << " to the requested "
                                  "map key type!" );

      typename ReturnType::const_iterator
        child_node_map_element = map.find( map_key );

      // Check that this child node key is unique
      TEST_FOR_EXCEPTION( child_node_map_element != map.end(),
                          Utility::PropertyTreeConversionException,
                          "Could not convert the property tree to the "
                          "associative container type because child node "
                          "key \"" << node_it->first << "\" appears "
                          "multiple times!" );

      try{
        map[map_key] = Utility::fromPropertyTree<T>( node_it->second );
      }
      EXCEPTION_CATCH_RETHROW_AS( Utility::StringConversionException,
                                  Utility::PropertyTreeConversionException,
                                  "Could not convert property tree node \""
                                  << node_it->first << "\" to the associative "
                                  "container value type!" );

      ++node_it;
    }

    return map;
  }
}

// Convert the property tree to an associative container
template<template<typename,typename,typename...> class STLCompliantAssociativeContainer,
         typename Key>
template<template<typename,typename...> class STLCompliantSequenceContainer>
inline auto AssociativeContainerFromPropertyTreeHelper<STLCompliantAssociativeContainer,Key,Utility::Variant>::fromPropertyTree(
    const Utility::PropertyTree& ptree,
    STLCompliantSequenceContainer<std::string>& unused_children ) -> ReturnType
{
  // Check that this node does not store an array
  TEST_FOR_EXCEPTION( Utility::doesPropertyTreeStoreJSONArray( ptree ),
                      Utility::PropertyTreeConversionException,
                      "Could not convert the property tree to the "
                      "associative container type because the property tree "
                      "contains a JSON array!" );

  ReturnType map;

  Utility::PropertyTree::const_iterator node_it, node_end;
  node_it = ptree.begin();
  node_end = ptree.end();

  while( node_it != node_end )
  {
    Key map_key;

    try{
      map_key = Utility::fromString<Key>( node_it->first );
    }
    EXCEPTION_CATCH_RETHROW_AS( Utility::StringConversionException,
                                Utility::PropertyTreeConversionException,
                                "Could not convert property tree node key "
                                << node_it->first << " to the requested "
                                "map key type!" );

    typename ReturnType::iterator
      child_node_map_element = map.find( map_key );

    // This child node does not have an associated key in the map
    if( child_node_map_element == map.end() )
    {
      // Check if this is a leaf node
      if( node_it->second.size() == 0 )
        map.insert( std::make_pair(map_key, node_it->second.data()) );

      // Check if this is a JSON array node
      else if( Utility::doesPropertyTreeStoreJSONArray( node_it->second ) )
      {
        VariantVector vector =
          Utility::fromPropertyTree<VariantVector>( node_it->second,
                                                    unused_children );

        map.insert( std::make_pair(node_it->first, Utility::Variant(vector)) );
      }

      // This is not a leaf node or a JSON array node - insert entire node
      else
      {
        VariantMap sub_map =
          Utility::fromPropertyTree<VariantMap>( node_it->second,
                                                 unused_children );

        map.insert( std::make_pair(node_it->first, Utility::Variant(sub_map)) );
      }
    }

    // Another child node with the same key has already been added to the
    // map - append it to the key's Utility::Variant object
    else
    {
      // Check if this is a leaf node
      if( node_it->second.size() == 0 )
        child_node_map_element->second += node_it->second.data();

      // Check if this is a JSON array node
      else if( Utility::doesPropertyTreeStoreJSONArray( node_it->second ) )
      {
        child_node_map_element->second +=
          Utility::fromPropertyTree<VariantVector>( node_it->second,
                                                    unused_children );
      }

      // This is not a leaf node or JSON array node - insert entire node
      else
      {
        child_node_map_element->second +=
          Utility::fromPropertyTree<VariantMap>( node_it->second,
                                                 unused_children );
      }
    }

    ++node_it;
  }

  return map;
}

} // end Details namespace

} // end Utility namespace

namespace boost {

namespace property_tree {

/*! \brief Specialize boost::property_tree::translator_between so that it uses
 * the custom translator Utility::GenericPTreeObjectTranslator
 * \ingroup ptree
 */
template<typename T>
struct translator_between<Utility::Variant,T>
{
  //! The translator type
  typedef Utility::Details::GenericPTreeObjectTranslator<T> type;
};

} // end property_tree namespace

} // end boost namespace

#endif // end UTILITY_PROPERTY_TREE_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_PropertyTree_def.hpp
//---------------------------------------------------------------------------//
