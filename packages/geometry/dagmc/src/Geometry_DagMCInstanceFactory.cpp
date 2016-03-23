//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCInstanceFactory.hpp
//! \author Alex Robinson
//! \brief  Dagmc instance factory class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <map>

// FRENSIE Includes
#include "Geometry_DagMCInstanceFactory.hpp"
#include "Geometry_DagMC.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Geometry{

// Initialize DagMC
void DagMCInstanceFactory::initializeDagMC( 
				        const Teuchos::ParameterList& geom_rep,
					std::ostream& os_warn )
{
  // Validate the geometry representation
  DagMCInstanceFactory::validateGeometryRep( geom_rep );

  // Get the CAD file name
  std::string cad_file_name = geom_rep.get<std::string>( "CAD File" );

  // Get the face tolerance
  double facet_tol = 1e-3; // default value

  if( geom_rep.isParameter( "Facet Tolerance" ) )
    facet_tol = geom_rep.get<double>( "Facet Tolerance" );

  if( geom_rep.isParameter( "Termination Cell Property" ) )
  {
    std::string property_name = 
      geom_rep.get<std::string>( "Termination Cell Property" ); 
    
    TEST_FOR_EXCEPTION( property_name.find( "_" ) < property_name.size(),
			std::runtime_error,
			"Error: the termination cell property name cannot "
                        "have an underscore character!" );

    DagMC::setTerminationCellPropertyName( property_name );
  }

  if( geom_rep.isParameter( "Reflecting Surface Property" ) )
  {
    std::string property_name = 
      geom_rep.get<std::string>( "Reflecting Surface Property" );

    TEST_FOR_EXCEPTION( property_name.find( "_" ) < property_name.size(),
			std::runtime_error,
			"Error: the reflecting surface property name cannot "
                        "have an underscore character!" );

    DagMC::setReflectingSurfacePropertyName( property_name );
  }

  if( geom_rep.isParameter( "Material Property" ) )
  {
    std::string property_name = 
      geom_rep.get<std::string>( "Material Property" );

    TEST_FOR_EXCEPTION( property_name.find( "_" ) < property_name.size(),
			std::runtime_error,
			"Error: the material property name cannot have an "
			"underscore character!" );
    
    DagMC::setMaterialPropertyName( property_name );
  }

  if( geom_rep.isParameter( "Density Property" ) )
  {
    std::string property_name = 
      geom_rep.get<std::string>( "Density Property" );

    TEST_FOR_EXCEPTION( property_name.find( "_" ) < property_name.size(),
			std::runtime_error,
			"Error: the density property name cannot have an "
			"underscore character!" );

    DagMC::setDensityPropertyName( property_name );
  }
  
  if( geom_rep.isParameter( "Estimator Property" ) )
  {
    std::string property_name = 
      geom_rep.get<std::string>( "Estimator Property" );

    TEST_FOR_EXCEPTION( property_name.find( "_" ) < property_name.size(),
			std::runtime_error,
			"Error: the estimator property name cannot have an "
			"underscore character!" );

    DagMC::setEstimatorPropertyName( property_name );
  }

  // Get the estimator type names
  if( geom_rep.isParameter( "Surface Current Name" ) )
  {
    std::string name = geom_rep.get<std::string>( "Surface Current Name" );

    TEST_FOR_EXCEPTION( name.find( "_" ) < name.size(),
			std::runtime_error,
			"Error: the surface current name cannot have an "
			"underscore character!" );

    DagMC::setSurfaceCurrentName( name );
  }

  if( geom_rep.isParameter( "Surface Flux Name" ) )
  {
    std::string name = geom_rep.get<std::string>( "Surface Flux Name" );
    
    TEST_FOR_EXCEPTION( name.find( "_" ) < name.size(),
			std::runtime_error,
			"Error: the surface flux name cannot have an "
			"underscore character!" );

    DagMC::setSurfaceFluxName( name );
  }

  if( geom_rep.isParameter( "Cell Pulse Height Name" ) )
  {
    std::string name = geom_rep.get<std::string>( "Cell Pulse Height Name");

    TEST_FOR_EXCEPTION( name.find( "_" ) < name.size(),
			std::runtime_error,
			"Error: the cell pulse height name cannot have an "
			"underscore character!" );

    DagMC::setCellPulseHeightName( name );
  }

  if( geom_rep.isParameter( "Cell Track-Length Flux Name" ) )
  {
    std::string name = geom_rep.get<std::string>( "Cell Track-Length Flux Name" );

    TEST_FOR_EXCEPTION( name.find( "_" ) < name.size(),
			std::runtime_error,
			"Error: the cell track-length flux name cannot "
			"have an underscore character!" );

    DagMC::setCellTrackLengthFluxName( name );
  }

  if( geom_rep.isParameter( "Cell Collision Flux Name" ) )
  {
    std::string name = geom_rep.get<std::string>( "Cell Collision Flux Name" );

    TEST_FOR_EXCEPTION( name.find( "_" ) < name.size(),
			std::runtime_error,
			"Error: the cell collision flux name cannot "
			"have an underscore character!" );

    DagMC::setCellCollisionFluxName( name );
  }

  bool use_fast_id_lookup = false;

  if( geom_rep.isParameter( "Use Fast Id Lookup" ) )
     use_fast_id_lookup = geom_rep.get<bool>( "Use Fast Id Lookup" );

  // Initialize DagMC
  DagMC::initialize( cad_file_name, facet_tol, use_fast_id_lookup, os_warn );

  // Print the unused parameters
  geom_rep.unused( os_warn );
}

// Validate a geometry representation
void DagMCInstanceFactory::validateGeometryRep( 
				       const Teuchos::ParameterList& geom_rep )
{
  TEST_FOR_EXCEPTION( !geom_rep.isParameter( "Handler" ),
		      InvalidGeometryRepresentation,
		      "Error: The geometry handler type has not been "
		      "specified!" );

  TEST_FOR_EXCEPTION( geom_rep.get<std::string>( "Handler" ) != "DagMC",
		      InvalidGeometryRepresentation,
		      "Error: The geometry handler type is "
		      << geom_rep.get<std::string>( "Handler" ) <<
		      " and not DagMC!" );
  
  TEST_FOR_EXCEPTION( !geom_rep.isParameter( "CAD File" ),
		      InvalidGeometryRepresentation,
		      "Error: The CAD file needs to be specified!" );
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_DagMCInstanceFactory.cpp
//---------------------------------------------------------------------------//
