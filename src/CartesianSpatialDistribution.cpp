//---------------------------------------------------------------------------//
//!
//! \file   CartesianSpatialDistribution.hpp
//! \author Alex Robinson
//! \brief  Cartesian spatial distribution definition.
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "CartesianSpatialDistribution.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
CartesianSpatialDistribution::CartesianSpatialDistribution( 
			  const Teuchos::RCP<OneDDistribution> x_distribution,
			  const Teuchos::RCP<OneDDistribution> y_distribution,
			  const Teuchos::RCP<OneDDistribution> z_distribution )
  : d_x_distribution( x_distribution ),
    d_y_distribution( y_distribution ),
    d_z_distribution( z_distribution )
{
  // Make sure that the distributions have been set
  testPrecondition( !x_distribution.is_null() );
  testPrecondition( !y_distribution.is_null() );
  testPrecondition( !z_distribution.is_null() );
}

// Return a random sample from the distribution
CartesianSpatialDistribution::sample( double sampled_point[3] )
{
  // Sample the x position
  sampled_point[0] = d_x_distribution->sample();

  // Sample the y position
  sampled_point[1] = d_y_distribution->sample();

  // Sample the z position
  sampled_point[2] = d_z_distribution->sample();
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end CartesianSpatialDistribution.cpp
//---------------------------------------------------------------------------//
