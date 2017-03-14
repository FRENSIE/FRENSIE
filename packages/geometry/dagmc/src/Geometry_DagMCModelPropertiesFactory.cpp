//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCModelPropertiesFactory.cpp
//! \author Alex Robinson
//! \brief  DagMC model properties factory class declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "Geometry_DagMCModelPropertiesFactory.hpp"
#include "Geometry_DagMCLoggingMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

// Load the DagMC model properties
std::shared_ptr<const DagMCModelProperties>
DagMCModelPropertiesFactory::createProperties(
                                     const Teuchos::ParameterList& properties )
{
  // The handler property must be defined
  TEST_FOR_EXCEPTION( !properties.isParameter( "Handler" ),
                      std::runtime_error,
                      "Unable to determine the geometry handler type!" );

  // The handler type must be DagMC
  TEST_FOR_EXCEPTION( properties.get<std::string>( "Handler" ) != "DagMC",
                      std::runtime_error,
                      "Invalid geometry handler type ("
                      << properties.get<std::string>( "Handler" ) << ")!" );

  // The cad file property must be present
  TEST_FOR_EXCEPTION( !properties.isParameter( "CAD File" ),
                      std::runtime_error,
                      "The CAD file needs to be specified!" );

  // Create the new DagMC model properties object
  std::shared_ptr<DagMCModelProperties>
    model_properties( new DagMCModelProperties(
                                 properties.get<std::string>( "CAD File" ) ) );

  // Get the facet tolerance (optional)
  if( properties.isParameter( "Facet Tolerance" ) )
  {
    const double facet_tol = properties.get<double>( "Facet Tolerance" );

    TEST_FOR_EXCEPTION( facet_tol <= 0.0 || facet_tol >= 1.0,
                        std::runtime_error,
                        "The facet tolerance must be between 0 and 1!" );

    model_properties->setFacetTolerance( facet_tol );
  }

  // Get fast id lookup property (optional)
  if( properties.isParameter( "Use Fast Id Lookup" ) )
  {
    if( properties.get<bool>( "Use Fast Id Lookup" ) )
      model_properties->useFastIdLookup();
    else
      model_properties->useStandardIdLookup();
  }

  // Get the termination cell property name (optional)
  if( properties.isParameter( "Termination Cell Property" ) )
  {
    const std::string property_name =
      properties.get<std::string>( "Termination Cell Property" );

    TEST_FOR_EXCEPTION( property_name.size() == 0,
                        std::runtime_error,
                        "The termination cell property name cannot be "
                        "empty!" );
    
    TEST_FOR_EXCEPTION( property_name.find( "_" ) < property_name.size(),
                        std::runtime_error,
                        "The termination cell property name cannot "
                        "have an underscore character!" );

    model_properties->setTerminationCellPropertyName( property_name );
  }

  // Get the reflecting surface property name (optional)
  if( properties.isParameter( "Reflecting Surface Property" ) )
  {
    const std::string property_name =
      properties.get<std::string>( "Reflecting Surface Property" );

    TEST_FOR_EXCEPTION( property_name.size() == 0,
                        std::runtime_error,
                        "The reflecting surface property name cannot be "
                        "empty!" );

    TEST_FOR_EXCEPTION( property_name.find( "_" ) < property_name.size(),
                        std::runtime_error,
                        "The reflecting surface property name cannot "
                        "have an underscore character!" );

    model_properties->setReflectingSurfacePropertyName( property_name );
  }

  // Get the material property name (optional)
  if( properties.isParameter( "Material Property" ) )
  {
    const std::string property_name =
      properties.get<std::string>( "Material Property" );

    TEST_FOR_EXCEPTION( property_name.size() == 0,
                        std::runtime_error,
                        "The material property name cannot be empty!" );

    TEST_FOR_EXCEPTION( property_name.find( "_" ) < property_name.size(),
                        std::runtime_error,
                        "The material property name cannot have an "
                        "underscore character!" );

    model_properties->setMaterialPropertyName( property_name );
  }

  // Get the density property name (optional)
  if( properties.isParameter( "Density Property" ) )
  {
    const std::string property_name =
      properties.get<std::string>( "Density Property" );

    TEST_FOR_EXCEPTION( property_name.size() == 0,
                        std::runtime_error,
                        "The density property name cannot be empty!" );

    TEST_FOR_EXCEPTION( property_name.find( "_" ) < property_name.size(),
                        std::runtime_error,
                        "The density property name cannot have an "
                        "underscore character!" );

    model_properties->setDensityPropertyNmae( property_name );
  }

  // Get the estimator property name (optional)
  if( properties.isParameter( "Estimator Property" ) )
  {
    const std::string property_name =
      properties.get<std::string>( "Estimator Property" );

    TEST_FOR_EXCEPTION( property_name.size() == 0,
                        std::runtime_error,
                        "The estimator property name cannot be empty!" );

    TEST_FOR_EXCEPTION( property_name.find( "_" ) < property_name.size(),
                        std::runtime_error,
                        "The estimator property name cannot have an "
                        "underscore character!" );

    model_properties->setDensityPropertyNmae( property_name );
  }

  // Get the surface current name (optional)
  if( properties.isParameter( "Surface Current Name" ) )
  {
    const std::string name =
      properties.get<std::string>( "Surface Current Name" );

    TEST_FOR_EXCEPTION( name.size() == 0,
                        std::runtime_error,
                        "The surface current name cannot be empty!" );

    TEST_FOR_EXCEPTION( name.find( "_" ) < name.size(),
                        std::runtime_error,
                        "The surface current name cannot have an "
                        "underscore character!" );

    model_properties->setSurfaceCurrentName( name );
  }

  // Get the surface flux name (optional)
  if( properties.isParameter( "Surface Flux Name" ) )
  {
    const std::string name =
      properties.get<std::string>( "Surface Flux Name" );

    TEST_FOR_EXCEPTION( name.size() == 0,
                        std::runtime_error,
                        "The surface flux name cannot be empty!" );

    TEST_FOR_EXCEPTION( name.find( "_" ) < name.size(),
                        std::runtime_error,
                        "The surface flux name cannot have an "
                        "underscore character!" );

    model_properties->setSurfaceFluxName( name );
  }

  // Get the cell pulse height name (optional)
  if( properties.isParameter( "Cell Pulse Height Name" ) )
  {
    const std::string name =
      properties.get<std::string>( "Cell Pulse Height Name" );

    TEST_FOR_EXCEPTION( name.size() == 0,
                        std::runtime_error,
                        "The cell pulse height name cannot be empty!" );

    TEST_FOR_EXCEPTION( name.find( "_" ) < name.size(),
                        std::runtime_error,
                        "The cell pulse height name cannot have an "
                        "underscore character!" );

    model_properties->setCellPulseHeightName( name );
  }

  // Get the cell track-length flux name
  if( properties.isParameter( "Cell Track-Length Flux Name" ) )
  {
    const std::string name =
      properties.get<std::string>( "Cell Track-Length Flux Name" );

    TEST_FOR_EXCEPTION( name.size() == 0,
                        std::runtime_error,
                        "The cell track-length flux name cannot be empty!" );

    TEST_FOR_EXCEPTION( name.find( "_" ) < name.size(),
                        std::runtime_error,
                        "The cell track-length flux name cannot have an "
                        "underscore character!" );

    model_properties->setCellTrackLengthFlux( name );
  }

  // Get the cell collision flux name
  if( properties.isParameter( "Cell Collision Flux Name" ) )
  {
    const std::string name =
      properties.get<std::string>( "Cell Collision Flux Name" );

    TEST_FOR_EXCEPTION( name.size() == 0,
                        std::runtime_error,
                        "The cell collision flux name cannot be empty!" );

    TEST_FOR_EXCEPTION( name.find( "_" ) < name.size(),
                        std::runtime_error,
                        "The cell collision flux name cannot have an "
                        "underscore character!" );

    model_properties->setCellCollisionFlux( name );
  }

  // Log unused parameters
  std::ostringstream oss;

  geom_rep.unused( oss );

  if( oss.str().size() > 0 )
  {
    FRENSIE_LOG_DAGMC_WARNING( oss.str() );
    FRENSIE_FLUSH_ALL_LOGS();
  }
}
  
} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_DagMCModelPropertiesFactory.cpp
//---------------------------------------------------------------------------//
