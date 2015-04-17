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
#include "Geometry_DagMCHelpers.hpp"
#include "Geometry_DagMCProperties.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Geometry{

// Initialize DagMC
void DagMCInstanceFactory::initializeDagMC( 
				       const Teuchos::ParameterList& geom_rep )
{
  // Validate the geometry representation
  DagMCInstanceFactory::validateGeometryRep( geom_rep );

  // Get the CAD file name
  std::string cad_file_name = geom_rep.get<std::string>( "CAD File" );

  // Get the face tolerance
  double facet_tol = 1e-3; // default value

  if( geom_rep.isParameter( "Facet Tolerance" ) )
    facet_tol = geom_rep.get<double>( "Facet Tolerance" );

  // Get the property synonyms
  std::vector<std::string> properties( 4 );

  if( geom_rep.isParameter( "Termination Cell Synonym" ) )
  {
    properties[0] = geom_rep.get<std::string>( "Termination Cell Synonym" ); 
    
    TEST_FOR_EXCEPTION( properties[0].find( "_" ) < properties[0].size(),
			std::runtime_error,
			"Error: the termination cell synonym cannot have an "
			"underscore character!" );

    DagMCProperties::setTerminationCellPropertyName( properties[0] );
  }
  else
    properties[0] = DagMCProperties::getTerminationCellPropertyName();

  if( geom_rep.isParameter( "Material Synonym" ) )
  {
    properties[1] = geom_rep.get<std::string>( "Material Synonym" );

    TEST_FOR_EXCEPTION( properties[1].find( "_" ) < properties[1].size(),
			std::runtime_error,
			"Error: the material synonym cannot have an "
			"underscore character!" );
    
    DagMCProperties::setMaterialPropertyName( properties[1] );
  }
  else
    properties[1] = DagMCProperties::getMaterialPropertyName();

  if( geom_rep.isParameter( "Density Synonym" ) )
  {
    properties[2] = geom_rep.get<std::string>( "Density Synonym" );

    TEST_FOR_EXCEPTION( properties[2].find( "_" ) < properties[2].size(),
			std::runtime_error,
			"Error: the density synonym cannot have an "
			"underscore character!" );

    DagMCProperties::setDensityPropertyName( properties[2] );
  }
  else
    properties[2] = DagMCProperties::getDensityPropertyName();

  if( geom_rep.isParameter( "Estimator Synonym" ) )
  {
    properties[3] = geom_rep.get<std::string>( "Estimator Synonym" );

    TEST_FOR_EXCEPTION( properties[3].find( "_" ) < properties[3].size(),
			std::runtime_error,
			"Error: the estimator synonym cannot have an "
			"underscore character!" );

    DagMCProperties::setEstimatorPropertyName( properties[3] );
  }
  else
    properties[3] = DagMCProperties::getEstimatorPropertyName();

  // Get the estimator type synonyms
  if( geom_rep.isParameter( "Surface Current Synonym" ) )
  {
    std::string name = geom_rep.get<std::string>( "Surface Current Synonym" );

    TEST_FOR_EXCEPTION( name.find( "_" ) < name.size(),
			std::runtime_error,
			"Error: the surface current synonym cannot have an "
			"underscore character!" );

    DagMCProperties::setSurfaceCurrentName( name );
  }

  if( geom_rep.isParameter( "Surface Flux Synonym" ) )
  {
    std::string name = geom_rep.get<std::string>( "Surface Flux Synonym" );
    
    TEST_FOR_EXCEPTION( name.find( "_" ) < name.size(),
			std::runtime_error,
			"Error: the surface flux synonym cannot have an "
			"underscore character!" );

    DagMCProperties::setSurfaceFluxName( name );
  }

  if( geom_rep.isParameter( "Cell Pulse Height Synonym" ) )
  {
    std::string name = geom_rep.get<std::string>( "Cell Pulse Height Synonym");

    TEST_FOR_EXCEPTION( name.find( "_" ) < name.size(),
			std::runtime_error,
			"Error: the cell pulse height synonym cannot have an "
			"underscore character!" );

    DagMCProperties::setCellPulseHeightName( name );
  }

  if( geom_rep.isParameter( "Cell Track-Length Flux Synonym" ) )
  {
    std::string name = geom_rep.get<std::string>( "Cell Track-Length Flux Synonym" );

    TEST_FOR_EXCEPTION( name.find( "_" ) < name.size(),
			std::runtime_error,
			"Error: the cell track-length flux synonym cannot "
			"have an underscore character!" );

    DagMCProperties::setCellTrackLengthFluxName( name );
  }

  if( geom_rep.isParameter( "Cell Collision Flux Synonym" ) )
  {
    std::string name = geom_rep.get<std::string>( "Cell Collision Flux Synonym" );

    TEST_FOR_EXCEPTION( name.find( "_" ) < name.size(),
			std::runtime_error,
			"Error: the cell collision flux synonym cannot "
			"have an underscore character!" );

    DagMCProperties::setCellCollisionFluxName( name );
  }

  // Initialize DagMC
  Geometry::initializeDagMC( cad_file_name, properties, facet_tol );

  // Print the unused parameters
  geom_rep.unused( std::cerr );
}

// Validate a geometry representation
void DagMCInstanceFactory::validateGeometryRep( 
				       const Teuchos::ParameterList& geom_rep )
{
  testPrecondition( geom_rep.get<std::string>( "Handler" ) == "DagMC" );
  
  TEST_FOR_EXCEPTION( !geom_rep.isParameter( "CAD File" ),
		      InvalidGeometryRepresentation,
		      "Error: The CAD file needs to be specified!" );
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_DagMCInstanceFactory.cpp
//---------------------------------------------------------------------------//
