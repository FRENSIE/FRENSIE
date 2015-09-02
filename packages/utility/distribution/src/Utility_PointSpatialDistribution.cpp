//---------------------------------------------------------------------------//
//!
//! \file   Utility_PointSpatialDistribution.cpp
//! \author Alex Robinson
//! \brief  Point spatial distribution declatation.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_PointSpatialDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

//! Constructor
PointSpatialDistribution::PointSpatialDistribution( const double x_position,
						    const double y_position,
						    const double z_position )
  : d_x_position( x_position ),
    d_y_position( y_position ),
    d_z_position( z_position )
{
  // Make sure th position is valid
  testPrecondition( !ST::isnaninf( x_position ) );
  testPrecondition( !ST::isnaninf( y_position ) );
  testPrecondition( !ST::isnaninf( z_position ) );
}

// Evaluate the spatial distribution
double PointSpatialDistribution::evaluate( 
					const double cartesian_point[3] ) const
{
  return 0.0;
}

// Evaluate the spatial distribution PDF
double PointSpatialDistribution::evaluatePDF( 
					const double cartesian_point[3] ) const
{
  return 0.0;
}

// Return a random (cartesian) sample from the distribution (x, y, z)
void PointSpatialDistribution::sample( double sampled_point[3] ) const
{
  sampled_point[0] = d_x_position;
  sampled_point[1] = d_y_position;
  sampled_point[2] = d_z_position;
}

// Return the distribution type
SpatialDistributionType PointSpatialDistribution::getDistributionType() const
{
  return POINT_SPATIAL_DISTRIBUTION;
}
  
// Check if the distribution is uniform
bool PointSpatialDistribution::isUniform() const
{
  return true;
}

// Check if the distribution has the same bounds
bool PointSpatialDistribution::hasSameBounds( 
				const SpatialDistribution& distribution ) const
{
  if( this->getDistributionType() == distribution.getDistributionType() )
  {
    const PointSpatialDistribution& true_dist = 
      dynamic_cast<const PointSpatialDistribution&>( distribution );

    return d_x_position == true_dist.d_x_position &&
      d_y_position == true_dist.d_y_position &&
      d_z_position == true_dist.d_z_position;
  }
  else
    return false;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_PointSpatialDistribution.cpp
//---------------------------------------------------------------------------//
