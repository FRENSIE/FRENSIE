//---------------------------------------------------------------------------//
//!
//! \file   SphericalSpatialDistribution.cpp
//! \author Alex Robinson
//! \brief  Spherical spatial distribution class definition.
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "SphericalSpatialDistribution.hpp"
#include "SphericalCoordinateHelpers.hpp"
#include "PhysicalConstants.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
SphericalSpatialDistribution::SphericalSpatialDistribution(
		      const Teuchos::RCP<OneDDistribution>& r_distribution,
		      const Teuchos::RCP<OneDDistribution>& theta_distribution,
		      const Teuchos::RCP<OneDDistribution>& mu_distribution,
		      const double center_x_position,
		      const double center_y_position,
		      const double center_z_position,
		      const Axis axis )
  : d_r_distribution( r_distribution ),
    d_theta_distribution( theta_distribution ),
    d_mu_distribution( mu_distribution ),
    d_center_x_position( center_x_position ),
    d_center_y_position( center_y_position ),
    d_center_z_position( center_z_position ),
    d_axis( axis ),
    d_uniform( true )
{
  // Make sure that the distributions have been set
  testPrecondition( !r_distribution.is_null() );
  testPrecondition( !theta_distribution.is_null() );
  testPrecondition( !mu_distribution.is_null() );
  // Make sure that the theta distribution is valid
  testPrecondition( theta_distribution->getUpperBoundOfIndepVar() 
		    <= 2*PhysicalConstants::pi );
  testPrecondition( theta_distribution->getLowerBoundOfIndepVar()
		    >= 0.0 );
  // Make sure that the mu distribution is valid
  testPrecondition( mu_distribution->getUpperBoundOfIndepVar()
		    <= 1.0 );
  testPrecondition( mu_distribution->getLowerBoundOfIndepVar()
		    >= -1.0 );
  // Make sure that the start positions are valid
  testPrecondition( !ST::isnaninf( center_x_position ) );
  testPrecondition( !ST::isnaninf( center_y_position ) );
  testPrecondition( !ST::isnaninf( center_z_position ) );

  // Determine if the distribution is uniform
  if( r_distribution->getDistributionType() != POWER_2_DISTRIBUTION )
    d_uniform = false;

  if( theta_distribution->getDistributionType() != UNIFORM_DISTRIBUTION )
    d_uniform = false;

  if( mu_distribution->getDistributionType() != UNIFORM_DISTRIBUTION )
    d_uniform = false;
}

// Evaluate the spatial distribution
double SphericalSpatialDistribution::evaluate( 
				        const double cartesian_point[3] ) const
{
  double spherical_point[3];

  SphericalSpatialDistribution::convertCartesianCoordsToSpherical( 
							     cartesian_point,
							     spherical_point );
				     
  double distribution_value = d_r_distribution->evaluate( spherical_point[0] );
  distribution_value *= d_theta_distribution->evaluate( spherical_point[1] );
  distribution_value *= d_mu_distribution->evaluate( spherical_point[2] );
  
  // If one distribution evaluates to inf and another to zero (value = nan),
  // return zero
  if( distribution_value != distribution_value )
    distribution_value = 0.0;

  // Make sure that the distribution value is valid
  testPostcondition( distribution_value == distribution_value );
  
  return distribution_value;
}

// Evaluate the spatial distribution PDF
double SphericalSpatialDistribution::evaluatePDF( 
					const double cartesian_point[3] ) const
{
  double spherical_point[3];

  SphericalSpatialDistribution::convertCartesianCoordsToSpherical( 
							     cartesian_point,
							     spherical_point );

  double pdf_value = d_r_distribution->evaluatePDF( spherical_point[0] );
  pdf_value *= d_theta_distribution->evaluatePDF( spherical_point[1] );
  pdf_value *= d_mu_distribution->evaluatePDF( spherical_point[2] );

  // Make sure that the pdf value is valid
  testPostcondition( !ST::isnaninf( pdf_value ) );

  return pdf_value;    
}

// Return a random sample from the distribution
/* \details The sampled position will be a point in cartesian space
 */
void SphericalSpatialDistribution::sample( double sampled_point[3] )
{
  // Sample from the distributions
  const double spherical_point[3] = {d_r_distribution->sample(),
				     d_theta_distribution->sample(),
				     d_mu_distribution->sample()};
  
  // Convert the spherical coordinate to cartesian
  convertSphericalCoordsToCartesian( spherical_point, sampled_point, d_axis );

  // Add the initial position to the sampled point
  sampled_point[0] += d_center_x_position;
  sampled_point[1] += d_center_y_position;
  sampled_point[2] += d_center_z_position;
}

// Check if the distribution is uniform
void SphericalSpatialDistribution::isUniform() const
{
  return d_uniform;
}

// Convert a cartesian coordinate to a spherical coordinate
void SphericalSpatialDistribution::convertCartesianCoordsToSpherical( 
					      const double cartesian_point[3],
					      double spherical_point[3] ) const
{
  const double origin[3] = 
    {d_center_x_position, d_center_y_position, d_center_z_position};
  
  FACEMC::convertCartesianCoordsToSpherical( cartesian_point,
					     origin,
					     spherical_point,
					     d_axis );
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end SphericalSpatialDistribution.cpp
//---------------------------------------------------------------------------//
