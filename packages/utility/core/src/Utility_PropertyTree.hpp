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

// Boost Includes
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/info_parser.hpp>

// FRENSIE Includes
#include "Utility_Variant.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_LoggingMacros.hpp"

/*! \defgroup ptree Property Tree
 */

namespace Utility{

/*! The property tree
 *
 * \ingroup ptree
 */
typedef boost::property_tree::basic_ptree<std::string,Utility::Variant> PropertyTree;
  
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
        FRENSIE_LOG_TAGGED_ERROR( "VariantPtree", error.what() );

        return boost::optional<external_type>( boost::none );
      }
    }
    else
      return boost::optional<external_type>( boost::none );
  }

  // Convert an object of type T to a Utility::Variant
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

/*! Check if the property tree node stores a JSON array
 *
 * The property tree handles JSON array elements by simply creating child nodes
 * with no name (no key value). It is also considered invalid property tree
 * usage to create a node that has both named and unnamed child nodes. 
 * Therefore we can safetly check the node type by checking if there are
 * any unnamed child nodes.
 * \ingroup ptree
 */
bool doesPTreeNodeStoreJSONArray( const Utility::PropertyTree& ptree )
{
  return ptree.count( "" ) > 0;
}

namespace Details{

/*! \brief Convert property tree node that contains a JSON array to the desired
 * sequence container
 *
 * You must verify that the node actually contains a JSON array before calling
 * this method.
 * \ingroup ptree
 */
template<template<typename,typename...> class STLCompliantSequenceContainer,
         typename ElementInsertionMemberFunction>
inline STLCompliantSequenceContainer<Utility::Variant> convertJSONArrayPTreeNodeToSequenceContainer(
                                const Utility::PropertyTree& ptree,
                                ElementInsertionMemberFunction insert_element )
{
  STLCompliantSequenceContainer<Utility::Variant> sequence_container;

  Utility::PropertyTree::const_iterator node_it, node_end;
  node_it = ptree.begin();
  node_end = ptree.end();

  while( node_it != node_end )
  {
    (sequence_container.*insert_element)( node_it->second.data() );
    
    ++node_it;
  }
  
  return sequence_container;
}

/*! Convert property tree node to the desired sequence container of Utility::Variant
 *
 * If a node does not store a JSON array and the node is not a leaf, an empty 
 * container will be returned (these types of nodes can only be converted to a 
 * Utility::VariantMap). Use the Utility::doesPTreeNodeStoreJSONArray helper 
 * function to test the node type. To test if the node is a leaf, simply
 * check if the size is equal to zero.
 * \ingroup ptree
 */
template<template<typename,typename...> class STLCompliantSequenceContainer,
         typename ElementInsertionMemberFunction>
inline STLCompliantSequenceContainer<Utility::Variant> convertPTreeNodeToSequenceContainer(
                                const Utility::PropertyTree& ptree,
                                ElementInsertionMemberFunction insert_element )
{
  // This node stores an array
  if( Utility::doesPTreeNodeStoreJSONArray( ptree ) )
  {
    return Details::convertJSONArrayPTreeNodeToSequenceContainer<STLCompliantSequenceContainer>( ptree, insert_element );
  }
  
  // This is a leaf node
  else if( ptree.size() == 0 )
  {
    return ptree.data().toType<STLCompliantSequenceContainer<Utility::Variant> >();
  }
  else
    return STLCompliantSequenceContainer<Utility::Variant>();
}

/*! Convert property tree node to the desired associated container of std::string and Utility::Variant
 *
 * If the node stores a JSON array, an empty associative container will be
 * returned. This is because of the way that JSON arrays are handled by the 
 * property tree - JSON array elements are simply child nodes with no name (no 
 * key value). Use the Utility::doesPTreeNodeStoreJSONArray helper function to 
 * test the node type.
 * \ingroup ptree
 */
template<template<typename,typename,typename...> class STLCompliantAssociativeContainer>
inline STLCompliantAssociativeContainer<std::string,Utility::Variant>
convertPTreeNodeToAssociativeContainer( const Utility::PropertyTree& ptree )
{
  // This node does not store an array
  if( !Utility::doesPTreeNodeStoreJSONArray( ptree ) )
  {
    STLCompliantAssociativeContainer<std::string,Utility::Variant> map;
  
    Utility::PropertyTree::const_iterator node_it, node_end;
    node_it = ptree.begin();
    node_end = ptree.end();
    
    while( node_it != node_end )
    {
      typename STLCompliantAssociativeContainer<std::string,Utility::Variant>::iterator child_node_map_element =
        map.find( node_it->first );

      // This child node does not have an associated key in the map
      if( child_node_map_element == map.end() )
      {
        // Check if this is a leaf node
        if( node_it->second.size() == 0 )
          map.insert( std::make_pair(node_it->first, node_it->second.data()) );
        // Check if this is a JSON array node
        else if( Utility::doesPTreeNodeStoreJSONArray( node_it->second ) )
        {
          VariantVector vector =
            convertJSONArrayPTreeNodeToSequenceContainer<std::vector>( node_it->second,
                                                                       (void (VariantVector::*)(const VariantVector::value_type&))&VariantVector::push_back );

          map.insert( std::make_pair(node_it->first, Utility::Variant(vector)) );
        }
        // This is not a leaf node or a JSON array node - insert the entire node
        else
        {
          STLCompliantAssociativeContainer<std::string,Utility::Variant> sub_map = 
            convertPTreeNodeToAssociativeContainer<STLCompliantAssociativeContainer>( node_it->second );
          
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
        else if( Utility::doesPTreeNodeStoreJSONArray( node_it->second ) )
        {
          child_node_map_element->second +=
            convertJSONArrayPTreeNodeToSequenceContainer<std::list>( node_it->second,
                                                                     (void (VariantList::*)(const VariantVector::value_type&))&VariantList::push_back );
        }
        // This is not a leaf node or JSON array node - insert the entire node
        else
        {
          child_node_map_element->second +=
            convertPTreeNodeToAssociativeContainer<STLCompliantAssociativeContainer>( node_it->second );
        }
      }
      
      ++node_it;
    }

    return map;
  }
  else
    return STLCompliantAssociativeContainer<std::string,Utility::Variant>();  
}
  
} // end Details namespace

/*! Convert property tree node to a VariantVector
 *
 * See Utility::Details::convertPTreeNodeToSequenceContainer details.
 * \ingroup ptree
 */
VariantVector convertPTreeNodeToVariantVector( const Utility::PropertyTree& ptree )
{
  return Details::convertPTreeNodeToSequenceContainer<std::vector>( ptree, (void (VariantVector::*)(const VariantVector::value_type&))&VariantVector::push_back );
}

/*! Convert property tree node to a VariantDeque
 *
 * See Utility::Details::convertPTreeNodeToSequenceContainer details.
 * \ingroup ptree
 */
VariantDeque convertPTreeNodeToVariantDeque( const Utility::PropertyTree& ptree )
{
  return Details::convertPTreeNodeToSequenceContainer<std::deque>( ptree, (void (VariantDeque::*)(const VariantDeque::value_type&))&VariantDeque::push_back );
}
  
/*! Convert property tree node to a VariantList
 *
 * See Utility::Details::convertPTreeNodeToSequenceContainer details.
 * \ingroup ptree
 */
VariantList convertPTreeNodeToVariantList( const Utility::PropertyTree& ptree )
{
  return Details::convertPTreeNodeToSequenceContainer<std::list>( ptree, (void (VariantList::*)(const VariantList::value_type&))&VariantList::push_back );
}

/*! Convert property tree node to a VariantForwardList
 *
 * See Utility::Details::convertPTreeNodeToSequenceContainer details.
 * \ingroup ptree
 */
VariantForwardList convertPTreeNodeToVariantForwardList( const Utility::PropertyTree& ptree )
{
  // This node stores an array
  if( Utility::doesPTreeNodeStoreJSONArray( ptree ) )
  {
    VariantForwardList reversed_list = Details::convertJSONArrayPTreeNodeToSequenceContainer<std::forward_list>( ptree, (void (VariantForwardList::*)(const VariantForwardList::value_type&))&VariantForwardList::push_front );

    reversed_list.reverse();

    return reversed_list;
  }
  
  // This is a leaf node
  else if( ptree.size() == 0 )
    return ptree.data().toForwardList();
  else
    return VariantForwardList();
}
  
/*! Convert property tree node to a VariantMap
 *
 * See Utility::Details::convertPTreeNodeToAssociativeContainer details.
 * \ingroup ptree
 */
VariantMap convertPTreeNodeToVariantMap( const Utility::PropertyTree& ptree )
{
  return Details::convertPTreeNodeToAssociativeContainer<std::map>( ptree );
}

/*! Specialization of Utility::ToStringTraits for Utility::PropertyTree
 * \ingroup ptree
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<PropertyTree>
{
  //! Convert a PropertyTree to a string
  static inline std::string toString( const PropertyTree& obj )
  {
    std::ostringstream oss;

    ToStringTraits<PropertyTree>::toStream( oss, obj );

    return boost::algorithm::trim_copy(oss.str());
  }

  //! Place the PropertyTree in a stream
  static inline void toStream( std::ostream& os, const PropertyTree& obj )
  { boost::property_tree::write_json( os, obj, false ); }
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
  static inline ReturnType fromString( const std::string& obj_rep )
  {
    std::istringstream iss( obj_rep );

    ReturnType ptree;

    FromStringTraits<PropertyTree>::fromStream( iss, ptree );

    return ptree;
  }

  //! Extract a ProperyTree from a stream
  static inline void fromStream( std::istream& is,
                                 PropertyTree& obj,
                                 const std::string& delims = std::string() )
  { boost::property_tree::read_json( is, obj ); }
};
  
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
  typedef Utility::GenericPTreeObjectTranslator<T> type;
};
  
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

#endif // end UTILITY_PROPERTY_TREE_HPP

//---------------------------------------------------------------------------//
// end Utility_PropertyTree.hpp
//---------------------------------------------------------------------------//
