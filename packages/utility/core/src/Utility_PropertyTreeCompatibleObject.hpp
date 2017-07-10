//---------------------------------------------------------------------------//
//!
//! \file   Utility_PropertyTreeCompatibleObject.hpp
//! \author Alex Robinson
//! \brief  Property tree compatible object base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_PROPERTY_TREE_COMPATIBLE_OBJECT_HPP
#define UTILITY_PROPERTY_TREE_COMPATIBLE_OBJECT_HPP

// FRENSIE Includes
#include "Utility_StreamableObject.hpp"
#include "Utility_PropertyTree.hpp"
#include "Utility_LoggingMacros.hpp"

namespace Utility{

/*! The base class for Utility::PropertyTree compatible objects
 * \ingroup ptree
 */
class PropertyTreeCompatibleObject : public StreamableObject
{

public:

  //! Method for placing an object in the desired property tree node
  virtual void toNode( const std::string& node_key,
                       Utility::PropertyTree& ptree,
                       const bool inline_data ) const = 0;

  //! Method for placing an object in the desired property tree node
  void toNode( const std::string& node_key,
               Utility::PropertyTree& ptree ) const
  { this->toNode( node_key, ptree, false ); }
  
  //! Method for initializing the object from a property tree node
  virtual void fromNode( const Utility::PropertyTree& node,
                         std::vector<std::string>& unused_children ) = 0;

  //! Method for initializing the object from a property tree node
  void fromNode( const Utility::PropertyTree& node,
                 const bool log_unused_children = true )
  {
    std::vector<std::string> unused_children;

    this->fromNode( node, unused_children );

    if( unused_children.size() > 0 && log_unused_children )
    {
      std::ostringstream oss;
      
      for( size_t i = 0; i < unused_children.size(); ++i )
      {
        oss << unused_children[i];
        
        if( i < unused_children.size() - 1 )
          oss << ", ";
      }
    
      FRENSIE_LOG_WARNING( "property tree nodes " << oss.str() <<
                           " are unused!" );
    }
  }
};
  
} // end Utility namespace

#endif // end UTILITY_PROPERTY_TREE_COMPATIBLE_OBJECT_HPP

//---------------------------------------------------------------------------//
// end Utility_PropertyTreeCompatibleObject.hpp
//---------------------------------------------------------------------------//
