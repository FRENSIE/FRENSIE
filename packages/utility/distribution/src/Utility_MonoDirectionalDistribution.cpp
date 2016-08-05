//---------------------------------------------------------------------------//
//!
//! \file   Utility_MonoDirectionalDistribution.hpp
//! \author Alex Robinson
//! \brief  Mono-directional distribution class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_MonoDirectionalDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

//! Constructor
MonoDirectionalDistribution::MonoDirectionalDistribution(
						     const double x_direction,
						     const double y_direction,
						     const double z_direction )
  : d_x_direction( x_direction ),
    d_y_direction( y_direction ),
    d_z_direction( z_direction )
{
  // Make sure the directions are valid
  testPrecondition( !ST::isnaninf( x_direction ) );
  testPrecondition( !ST::isnaninf( y_direction ) );
  testPrecondition( !ST::isnaninf( z_direction ) );

  // Renormalize the direction
  double norm = sqrt( x_direction*x_direction +
		      y_direction*y_direction +
		      z_direction*z_direction );

  d_x_direction /= norm;
  d_y_direction /= norm;
  d_z_direction /= norm;
}

// Evaluate the directional distribution
double MonoDirectionalDistribution::evaluate(
					const double cartesian_point[3] ) const
{
  return 0.0;
}

// Evaluate the directional distribution PDF
double MonoDirectionalDistribution::evaluatePDF(
					const double cartesian_point[3] ) const
{
  return 0.0;
}

// Return a random (cartesian) sample from the distribution (u, v, w)
void MonoDirectionalDistribution::sample( double sampled_direction[3] ) const
{
  sampled_direction[0] = d_x_direction;
  sampled_direction[1] = d_y_direction;
  sampled_direction[2] = d_z_direction;
}

// Return the distribution type
DirectionalDistributionType
MonoDirectionalDistribution::getDistributionType() const
{
  return MONO_DIRECTIONAL_DISTRIBUTION;
}

// Check if the distribution has the same bounds
bool MonoDirectionalDistribution::hasSameBounds(
			    const DirectionalDistribution& distribution ) const
{
  if( this->getDistributionType() == distribution.getDistributionType() )
  {
    const MonoDirectionalDistribution& true_dist =
      dynamic_cast<const MonoDirectionalDistribution&>( distribution );

    if( d_x_direction == true_dist.d_x_direction &&
	d_y_direction == true_dist.d_y_direction &&
	d_z_direction == true_dist.d_z_direction )
      return true;
    else
      return false;
  }
  else
    return false;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_MonoDirectionalDistribution.cpp
//---------------------------------------------------------------------------//
