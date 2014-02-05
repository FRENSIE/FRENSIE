//---------------------------------------------------------------------------//
//!
//! \file   DirectionalDistribution.cpp
//! \author Alex Robinson
//! \brief  Directional distribution class definition.
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "DirectionalDistribution.hpp"
#include "SphericalDistributionHelpers.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
DirectionalDistribution::DirectionalDistribution( 
		      const Teuchos::RCP<OneDDistribution>& theta_distribution,
		      const Teuchos::RCP<OneDDistribution>& mu_distribution,
		      const Axis axis = Z_AXIS )
  : d_theta_distribution( theta_distribution ),
    d_mu_distribution( mu_distribution ),
    d_axis( axis )
{
  // Make sure that the distributions have been set
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
}

// Return a random (cartesian) sample from the distribution (u, v, w)
void DirectionalDistribution::sample( double sampled_direction[3] )
{
  // Sample from the distributions
  const double spherical_point[3] = {1.0,
				     d_theta_distribution->sample(),
				     d_mu_distribution->sample()}
  
  // Convert the spherical coordinate to cartesian
  convertSphericalCoordinateToCartesian( spherical_point,
					 sampled_direction,
					 d_axis );
}


} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end DirectionalDistribution.cpp
//---------------------------------------------------------------------------//
