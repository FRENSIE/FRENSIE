//---------------------------------------------------------------------------//
//!
//! \file   Utility_PropertyTree.cpp
//! \author Alex Robinson
//! \brief  Boost property tree helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_PropertyTree.hpp"

namespace Utility{

// Check if the property tree node stores a JSON array
/*! \details The property tree handles JSON array elements by simply creating 
 * child nodes with no name (no key value). It is also considered invalid 
 * property tree usage to create a node that has both named and unnamed child 
 * nodes. Therefore we can safetly check the node type by checking if there are
 * any unnamed child nodes.
 * \ingroup ptree
 */
bool doesPTreeNodeStoreJSONArray( const Utility::PropertyTree& ptree )
{
  return ptree.count( "" ) > 0;
}
  
// Convert property tree node to a VariantVector
/*! \details See Utility::Details::convertPTreeNodeToSequenceContainer details.
 */
VariantVector convertPTreeNodeToVariantVector( const Utility::PropertyTree& ptree )
{
  return Details::convertPTreeNodeToSequenceContainer<std::vector>( ptree, (void (VariantVector::*)(const VariantVector::value_type&))&VariantVector::push_back );
}

// Convert property tree node to a VariantDeque
/*! \details See Utility::Details::convertPTreeNodeToSequenceContainer details.
 */
VariantDeque convertPTreeNodeToVariantDeque( const Utility::PropertyTree& ptree )
{
  return Details::convertPTreeNodeToSequenceContainer<std::deque>( ptree, (void (VariantDeque::*)(const VariantDeque::value_type&))&VariantDeque::push_back );
}

// Convert property tree node to a VariantList
/*! \details See Utility::Details::convertPTreeNodeToSequenceContainer details.
 */
VariantList convertPTreeNodeToVariantList( const Utility::PropertyTree& ptree )
{
  return Details::convertPTreeNodeToSequenceContainer<std::list>( ptree, (void (VariantList::*)(const VariantList::value_type&))&VariantList::push_back );
}

// Convert property tree node to a VariantForwardList
/*! \details See Utility::Details::convertPTreeNodeToSequenceContainer details.
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

// Convert property tree node to a VariantMap
/*! \details See Utility::Details::convertPTreeNodeToAssociativeContainer
 * details.
 */
VariantMap convertPTreeNodeToVariantMap( const Utility::PropertyTree& ptree )
{
  return Details::convertPTreeNodeToAssociativeContainer<std::map>( ptree );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_PropertyTree.cpp
//---------------------------------------------------------------------------//
