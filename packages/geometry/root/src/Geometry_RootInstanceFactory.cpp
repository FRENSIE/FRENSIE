//---------------------------------------------------------------------------//
//!
//! \file   Geometry_RootInstanceFactory.hpp
//! \author Eli Moll
//! \brief  Root instance factory class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <map>

// FRENSIE Includes
#include "Geometry_RootInstanceFactory.hpp"
#include "Geometry_Root.hpp"
#include "Geometry_ModuleInterface_Root.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Geometry{

// Initialize the static member data
std::ostream* RootInstanceFactory::s_os_warn = NULL;

// Initialize Root
void RootInstanceFactory::initializeRoot( 
				       const Teuchos::ParameterList& geom_rep,
				       std::ostream& os_warn )
{
  // Set the warning output stream
  s_os_warn = &os_warn;

  // Validate the geometry representation
  RootInstanceFactory::validateGeometryRep( geom_rep );

  // Get the Root file name
  std::string root_file_name = geom_rep.get<std::string>( "Root File" );
  
  // Initialize the Root geometry handler
  Geometry::Root::initialize( root_file_name );

  // Print unused parameters
  geom_rep.unused( *s_os_warn );

}

// Validate a geometry representation
void RootInstanceFactory::validateGeometryRep( 
				       const Teuchos::ParameterList& geom_rep )
{
  testPrecondition( geom_rep.get<std::string>( "Handler" ) == "ROOT" );
  
  TEST_FOR_EXCEPTION( !geom_rep.isParameter( "Root File" ),
		      InvalidGeometryRepresentation,
		      "Error: The Root file needs to be specified!" );
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_RootInstanceFactory.cpp
//---------------------------------------------------------------------------//
