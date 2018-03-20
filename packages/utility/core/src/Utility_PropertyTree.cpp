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

// Check if the property tree stores a JSON array
/*! \details The property tree handles JSON array elements by simply creating
 * child nodes with no name (no key value). It is also considered invalid
 * property tree usage to create a node that has both named and unnamed child
 * nodes. Therefore we can safely check the node type by checking if there are
 * any unnamed child nodes.
 * \ingroup ptree
 */
bool doesPropertyTreeStoreJSONArray( const Utility::PropertyTree& ptree )
{
  return ptree.count( "" ) > 0;
}

// Convert a PropertyTree to a string
std::string ToStringTraits<PropertyTree>::toString( const PropertyTree& obj )
{
  std::ostringstream oss;

  ToStringTraits<PropertyTree>::toStream( oss, obj );

  return boost::algorithm::trim_copy(oss.str());
}

// Place the PropertyTree in a stream
void ToStringTraits<PropertyTree>::toStream( std::ostream& os,
                                             const PropertyTree& obj )
{
  boost::property_tree::write_json( os, obj, false );
}

// Convert the string to a PropertyTree object
auto FromStringTraits<PropertyTree>::fromString(
                                     const std::string& obj_rep ) -> ReturnType
{
  std::istringstream iss( obj_rep );

  ReturnType ptree;

  FromStringTraits<PropertyTree>::fromStream( iss, ptree );

  return ptree;
}

// Extract a PropertyTree from a stream
void FromStringTraits<PropertyTree>::fromStream( std::istream& is,
                                                 PropertyTree& obj,
                                                 const std::string& delims )
{
  try{
    boost::property_tree::read_json( is, obj );
  }
  EXCEPTION_CATCH_RETHROW_AS( boost::property_tree::json_parser_error,
                              Utility::StringConversionException,
                              "Could not extract a property tree from the "
                              "stream!" );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_PropertyTree.cpp
//---------------------------------------------------------------------------//
