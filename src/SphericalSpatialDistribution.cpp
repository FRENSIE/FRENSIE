//---------------------------------------------------------------------------//
//!
//! \file   SphericalSpatialDistribution.cpp
//! \author Alex Robinson
//! \brief  Spherical spatial distribution class definition.
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "SphericalSpatialDistribution.hpp"
#include "SphericalDistributionHelpers.hpp"
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
    d_axis( axis )
{
  // Make sure that the distributions have been set
  testPrecondition( !r_distribution.is_null() );
  testPrecondition( !theta_distribution.is_null() );
  testPrecondition( !mu_distribution.is_null() );
  // Make sure that the theta distribution is valid
  testPrecondition( theta_distribution->getUpperBoundOfIndepVar() 
		    <= 2*acos(-1.0) );
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

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end SphericalSpatialDistribution.cpp
//---------------------------------------------------------------------------//
