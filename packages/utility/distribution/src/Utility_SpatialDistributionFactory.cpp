//---------------------------------------------------------------------------//
//!
//! \file   Utility_SpatialDistributionFactory.cpp
//! \author Alex Robinson
//! \brief  Spatial distribution factory class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_SpatialDistributionFactory.hpp"
#include "Utility_CartesianSpatialDistribution.hpp"
#include "Utility_CylindricalSpatialDistribution.hpp"
#include "Utility_SphericalSpatialDistribution.hpp"
#include "Utility_PointSpatialDistribution.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Utility{

// Create the spatial distribution represented by the parameter list
std::shared_ptr<SpatialDistribution> 
SpatialDistributionFactory::createDistribution( 
			       const Teuchos::ParameterList& distribution_rep )
{
  // Validate the distribution representation
  SpatialDistributionFactory::validateDistributionRep( distribution_rep );
  
  // Create a cartesian spatial distribution
  if( distribution_rep.isParameter( "X Distribution" ) )
  {
    return SpatialDistributionFactory::createCartesianDistribution( 
							    distribution_rep );
  }
  
  // Create a cylindrical spatial distribution
  else if( distribution_rep.isParameter( "Axis Distribution" ) )
  {
    return SpatialDistributionFactory::createCylindricalDistribution(
							    distribution_rep );
  }

  // Create a spherical spatial distribution
  else if( distribution_rep.isParameter( "Mu Distribution" ) )
  {
    return SpatialDistributionFactory::createSphericalDistribution(
							    distribution_rep );
  }

  // Create a point spatial distribution
  else if( distribution_rep.isParameter( "Position" ) )
  {
    return SpatialDistributionFactory::createPointDistribution(
							    distribution_rep );
  }
}

// Validate the distribution representation
void SpatialDistributionFactory::validateDistributionRep( 
			       const Teuchos::ParameterList& distribution_rep )
{
  bool valid_distribution = false;
  
  // Make sure a valid cartesian distribution has been specified
  if( distribution_rep.isParameter( "X Distribution" ) )
  {
    TEST_FOR_EXCEPTION( distribution_rep.isParameter( "X Distribution" ) &&
			(!distribution_rep.isParameter( "Y Distribution" ) ||
			 !distribution_rep.isParameter( "Z Distribution" ) ),
			InvalidSpatialDistributionRepresentation,
			"Error: A cartesian spatial distribution needs to "
			"have the x, y, and z distributions specified!" );
    
    TEST_FOR_EXCEPTION( distribution_rep.numParams() != 3,
			InvalidSpatialDistributionRepresentation,
			"Error: Three 1D distributions must be specified for "
			"a cartesian spatial distribution!" );

    valid_distribution = true;
  }
  else if( distribution_rep.isParameter( "Y Distribution" ) )
  {
    TEST_FOR_EXCEPTION( distribution_rep.isParameter( "Y Distribution" ) &&
			(!distribution_rep.isParameter( "X Distribution" ) ||
			 !distribution_rep.isParameter( "Z Distribution" ) ),
			InvalidSpatialDistributionRepresentation,
			"Error: A cartesian spatial distribution needs to "
			"have the x, y, and z distributions specified!" );

    TEST_FOR_EXCEPTION( distribution_rep.numParams() != 3,
			InvalidSpatialDistributionRepresentation,
			"Error: Three 1D distributions must be specified for "
			"a cartesian spatial distribution!" );

    valid_distribution = true;
  }

  // Make sure a valid cylindrical distribution has been specified
  if( distribution_rep.isParameter( "Axis Distribution" ) )
  {
    TEST_FOR_EXCEPTION( distribution_rep.isParameter( "Axis Distribution" ) &&
			(!distribution_rep.isParameter( "R Distribution" ) ||
			 !distribution_rep.isParameter( "Theta Distribution")),
			InvalidSpatialDistributionRepresentation,
			"Error: A cylindrical spatial distribution needs to "
			"have the r, theta, and axis distribution specified!");

    TEST_FOR_EXCEPTION( !distribution_rep.isParameter( "Center X Position" ) ||
			!distribution_rep.isParameter( "Center Y Position" ) ||
			!distribution_rep.isParameter( "Center Z Position" ),
			InvalidSpatialDistributionRepresentation,
			"Error: A cylindrical spatial distribution needs to "
			"have the center coordinate specified!" );

    TEST_FOR_EXCEPTION( !distribution_rep.isParameter( "Axis" ),
			InvalidSpatialDistributionRepresentation,
			"Error: A cylindrical spatial distribution needs to "
			"have the alignment axis specified!" );

    TEST_FOR_EXCEPTION( distribution_rep.numParams() != 7,
			InvalidSpatialDistributionRepresentation,
			"Error: Three 1D distributions, the center "
			"coordinates and the axis must be specified for "
			"a cylindrical spatial distribution!" );

    valid_distribution = true;
  }

  // Make sure a valid spherical distribution has been specified
  if( distribution_rep.isParameter( "Mu Distribution" ) )
  {
    TEST_FOR_EXCEPTION( distribution_rep.isParameter( "Mu Distribution" ) &&
			(!distribution_rep.isParameter( "R Distribution" ) ||
			 !distribution_rep.isParameter( "Theta Distribution")),
			InvalidSpatialDistributionRepresentation,
			"Error: A spherical spatial distribution needs to "
			"have the r, theta, and mu distribution specified!");

    TEST_FOR_EXCEPTION( !distribution_rep.isParameter( "Center X Position" ) ||
			!distribution_rep.isParameter( "Center Y Position" ) ||
			!distribution_rep.isParameter( "Center Z Position" ),
			InvalidSpatialDistributionRepresentation,
			"Error: A spherical spatial distribution needs to "
			"have the center coordinate specified!" );

    TEST_FOR_EXCEPTION( !distribution_rep.isParameter( "Axis" ),
			InvalidSpatialDistributionRepresentation,
			"Error: A spherical spatial distribution needs to "
			"have the alignment axis specified!" );

    TEST_FOR_EXCEPTION( distribution_rep.numParams() != 7,
			InvalidSpatialDistributionRepresentation,
			"Error: Three 1D distributions, the center "
			"coordinates and the axis must be specified for "
			"a spherical spatial distribution!" );
    
    valid_distribution = true;
  }

  if( distribution_rep.isParameter( "Position" ) )
  {
    valid_distribution = true;
  }

  TEST_FOR_EXCEPTION( !valid_distribution,
		      InvalidSpatialDistributionRepresentation,
		      "Error: The type of spatial distribution "
		      << distribution_rep << " could not be determined!" );
}

// Validate the axis name
void SpatialDistributionFactory::validateAxisName( 
						 const std::string& axis_name )
{
  TEST_FOR_EXCEPTION( !isValidAxisName( axis_name ),
		      InvalidSpatialDistributionRepresentation,
		      "Error: An invalid axis was specified (" 
		      << axis_name << "). Only 'X', 'Y', and 'Z' are valid "
		      " names!" );
}

// Create a cartesian distribution
std::shared_ptr<Utility::SpatialDistribution> 
SpatialDistributionFactory::createCartesianDistribution(
			       const Teuchos::ParameterList& distribution_rep )
{
  Teuchos::RCP<const Teuchos::ParameterEntry> entry = 
    distribution_rep.getEntryRCP( "X Distribution" );
  
  std::shared_ptr<OneDDistribution> x_distribution = 
    OneDDistributionEntryConverterDB::convertEntryToSharedPtr( entry );
  
  entry = distribution_rep.getEntryRCP( "Y Distribution" );
  
  std::shared_ptr<OneDDistribution> y_distribution = 
    OneDDistributionEntryConverterDB::convertEntryToSharedPtr( entry );
  
  entry = distribution_rep.getEntryRCP( "Z Distribution" );
  
  std::shared_ptr<OneDDistribution> z_distribution = 
    OneDDistributionEntryConverterDB::convertEntryToSharedPtr( entry );

  distribution_rep.unused( std::cout );
  
  return std::shared_ptr<SpatialDistribution>( 
			  new CartesianSpatialDistribution( x_distribution,
							    y_distribution,
							    z_distribution ) );
}

// Create a cylindrical distribution
std::shared_ptr<Utility::SpatialDistribution> 
SpatialDistributionFactory::createCylindricalDistribution(
			       const Teuchos::ParameterList& distribution_rep )
{
  Teuchos::RCP<const Teuchos::ParameterEntry> entry = 
    distribution_rep.getEntryRCP( "R Distribution" );

  std::shared_ptr<OneDDistribution> r_distribution = 
    OneDDistributionEntryConverterDB::convertEntryToSharedPtr( entry );
  
  entry = distribution_rep.getEntryRCP( "Theta Distribution" );
  
  std::shared_ptr<OneDDistribution> theta_distribution = 
    OneDDistributionEntryConverterDB::convertEntryToSharedPtr( entry );
  
  entry = distribution_rep.getEntryRCP( "Axis Distribution" );
  
  std::shared_ptr<OneDDistribution> axis_distribution = 
    OneDDistributionEntryConverterDB::convertEntryToSharedPtr( entry );
  
  double center_x_position = 
    distribution_rep.get<double>( "Center X Position" );  
  
  double center_y_position = 
    distribution_rep.get<double>( "Center Y Position" );  
  
  double center_z_position = 
    distribution_rep.get<double>( "Center Z Position" );  
  
  std::string axis_name = 
    distribution_rep.get<std::string>( "Axis" );
  
  SpatialDistributionFactory::validateAxisName( axis_name );
  
  Axis axis = convertAxisNameToAxisEnum( axis_name );
  
  distribution_rep.unused( std::cout );

  return std::shared_ptr<SpatialDistribution>( 
			new CylindricalSpatialDistribution( r_distribution,
						            theta_distribution,
							    axis_distribution,
							    center_x_position,
							    center_y_position,
							    center_z_position,
							    axis ) );
}

// Create a spherical distribution
std::shared_ptr<Utility::SpatialDistribution> 
SpatialDistributionFactory::createSphericalDistribution(
			       const Teuchos::ParameterList& distribution_rep )
{
  Teuchos::RCP<const Teuchos::ParameterEntry> entry = 
    distribution_rep.getEntryRCP( "R Distribution" );
  
  std::shared_ptr<OneDDistribution> r_distribution = 
    OneDDistributionEntryConverterDB::convertEntryToSharedPtr( entry );
  
  entry = distribution_rep.getEntryRCP( "Theta Distribution" );
  
  std::shared_ptr<OneDDistribution> theta_distribution = 
    OneDDistributionEntryConverterDB::convertEntryToSharedPtr( entry );
  
  entry = distribution_rep.getEntryRCP( "Mu Distribution" );
  
  std::shared_ptr<OneDDistribution> mu_distribution = 
    OneDDistributionEntryConverterDB::convertEntryToSharedPtr( entry );
  
  double center_x_position = 
    distribution_rep.get<double>( "Center X Position" );  
  
  double center_y_position = 
    distribution_rep.get<double>( "Center Y Position" );  
  
  double center_z_position = 
    distribution_rep.get<double>( "Center Z Position" );  
  
  std::string axis_name = 
    distribution_rep.get<std::string>( "Axis" );
  
  SpatialDistributionFactory::validateAxisName( axis_name );
  
  Axis axis = convertAxisNameToAxisEnum( axis_name );
  
  distribution_rep.unused( std::cout );

  return std::shared_ptr<SpatialDistribution>( 
			  new SphericalSpatialDistribution( r_distribution,
							    theta_distribution,
							    mu_distribution,
							    center_x_position,
							    center_y_position,
							    center_z_position,
							    axis ) );
}

// Create a point distribution
std::shared_ptr<Utility::SpatialDistribution>
SpatialDistributionFactory::createPointDistribution( 
			       const Teuchos::ParameterList& distribution_rep )
{
  Teuchos::Array<double> position = 
    distribution_rep.get<Teuchos::Array<double> >( "Position" );

  TEST_FOR_EXCEPTION( position.size() != 3,
		      InvalidSpatialDistributionRepresentation,
		      "Error: the position is invalid - size ("
		      << position.size() << ") != 3" );

  return std::shared_ptr<SpatialDistribution>(
				  new PointSpatialDistribution( position[0],
								position[1],
								position[2]) );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_SpatialDistributionFactory.cpp
//---------------------------------------------------------------------------//
