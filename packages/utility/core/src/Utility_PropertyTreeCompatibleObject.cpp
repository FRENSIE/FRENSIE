//---------------------------------------------------------------------------//
//!
//! \file   Utility_PropertyTreeCompatibleObject.cpp
//! \author Alex Robinson
//! \brief  Property tree compatible object base class definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/algorithm/string.hpp>

// FRENSIE Includes
#include "Utility_PropertyTreeCompatibleObject.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_LoggingMacros.hpp"

namespace Utility{

// Check if data can be inlined
bool PropertyTreeCompatibleObject::canDataBeInlined() const
{
  return false;
}

// Return the type key
std::string PropertyTreeCompatibleObject::getTypeKey() const
{
  return PTREE_TYPE_KEY;
}

// Return the type name
std::string PropertyTreeCompatibleObject::getTypeName(
                                                   const bool verbose_name,
                                                   const bool lowercase ) const
{
  if( lowercase )
  {
    std::string type_name = this->getTypeNameImpl( verbose_name );
    
    boost::algorithm::to_lower( type_name );

    return type_name;
  }
  else
    return this->getTypeNameImpl( verbose_name );
}

// Method for initializing the object from a property tree
void PropertyTreeCompatibleObject::fromPropertyTree(
                                             const Utility::PropertyTree& node,
                                             const bool log_unused_children )
{
  std::vector<std::string> unused_children;

  this->fromPropertyTree( node, unused_children );

  if( log_unused_children )
    Utility::logUnusedChildrenOfPropertyTree( unused_children );
}

// Verify that the distribution type is correct
void PropertyTreeCompatibleObject::verifyType( const Utility::Variant& type_data ) const
{
  TEST_FOR_EXCEPTION( !this->doesTypeNameMatch( type_data.toString() ),
                      Utility::StringConversionException,
                      "The " << this->getTypeName(true, true) <<
                      " cannot be constructed because the type ("
                      << type_data.toString() << ") does not match!" );
}

// Check if the type name matches the distribution type name
/*! \details The type name provided will be checked against the type name 
 * returned from getTypeName( false, true ).
 */
bool PropertyTreeCompatibleObject::doesTypeNameMatch( const std::string type_name ) const
{
  std::string lower_type_name = boost::algorithm::to_lower_copy( type_name );

  return lower_type_name.find(this->getTypeName( false, true )) < lower_type_name.size();
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_PropertyTreeCompatibleObject.cpp
//---------------------------------------------------------------------------//
