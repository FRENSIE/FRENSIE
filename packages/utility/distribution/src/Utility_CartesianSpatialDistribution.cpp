//---------------------------------------------------------------------------//
//!
//! \file   Utility_CartesianSpatialDistribution.hpp
//! \author Alex Robinson
//! \brief  Cartesian spatial distribution definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_CartesianSpatialDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
CartesianSpatialDistribution::CartesianSpatialDistribution( 
		      const std::shared_ptr<OneDDistribution>& x_distribution,
                      const std::shared_ptr<OneDDistribution>& y_distribution,
                      const std::shared_ptr<OneDDistribution>& z_distribution )
  : d_x_distribution( x_distribution ),
    d_y_distribution( y_distribution ),
    d_z_distribution( z_distribution ),
    d_uniform( true )
{
  // Make sure that the distributions have been set
  testPrecondition( x_distribution.get() );
  testPrecondition( y_distribution.get() );
  testPrecondition( z_distribution.get() );

  // Determine if the distribution is uniform
  if( x_distribution->getDistributionType() != UNIFORM_DISTRIBUTION )
    d_uniform = false;

  if( y_distribution->getDistributionType() != UNIFORM_DISTRIBUTION )
    d_uniform = false;

  if( z_distribution->getDistributionType() != UNIFORM_DISTRIBUTION )
    d_uniform = false;
}

// Evaluate the spatial distribution
double CartesianSpatialDistribution::evaluate( 
					const double cartesian_point[3] ) const
{
  double distribution_value = d_x_distribution->evaluate( cartesian_point[0] );
  distribution_value *= d_y_distribution->evaluate( cartesian_point[1] );
  distribution_value *= d_z_distribution->evaluate( cartesian_point[2] );

  // If one distribution evaluates to inf and another to zero (value = nan), 
  // return zero
  if( distribution_value != distribution_value )
    distribution_value = 0.0;

  // Make sure that the distribution value is valid
  testPostcondition( distribution_value == distribution_value );
  
  return distribution_value;
}

// Evaluate the spatial distribution PDF
double CartesianSpatialDistribution::evaluatePDF( 
					const double cartesian_point[3] ) const
{
  double pdf_value = d_x_distribution->evaluatePDF( cartesian_point[0] );
  pdf_value *= d_y_distribution->evaluatePDF( cartesian_point[1] );
  pdf_value *= d_z_distribution->evaluatePDF( cartesian_point[2] );
  
  // Make sure that the pdf value is valid
  testPostcondition( pdf_value == pdf_value );

  return pdf_value;
}

// Return a random sample from the distribution
void CartesianSpatialDistribution::sample( double sampled_point[3] ) const
{
  // Sample the x position
  sampled_point[0] = d_x_distribution->sample();

  // Sample the y position
  sampled_point[1] = d_y_distribution->sample();

  // Sample the z position
  sampled_point[2] = d_z_distribution->sample();
}

// Return the distribution type
SpatialDistributionType 
CartesianSpatialDistribution::getDistributionType() const
{
  return CARTESIAN_SPATIAL_DISTRIBUTION;
}

// Check if the distribution is uniform
bool CartesianSpatialDistribution::isUniform() const
{
  return d_uniform;
}

// Check if the distribution has the same bounds
bool CartesianSpatialDistribution::hasSameBounds( 
			        const SpatialDistribution& distribution ) const
{
  if( this->getDistributionType() == distribution.getDistributionType() )
  {
    const CartesianSpatialDistribution& true_dist = 
      dynamic_cast<const CartesianSpatialDistribution&>( distribution );
    
    return 
      Policy::relError(d_x_distribution->getLowerBoundOfIndepVar(),
		       true_dist.d_x_distribution->getLowerBoundOfIndepVar()) <
      1e-9 &&
      Policy::relError(d_x_distribution->getUpperBoundOfIndepVar(),
		       true_dist.d_x_distribution->getUpperBoundOfIndepVar()) <
      1e-9 &&
      Policy::relError(d_y_distribution->getLowerBoundOfIndepVar(),
		       true_dist.d_y_distribution->getLowerBoundOfIndepVar()) <
      1e-9 &&
      Policy::relError(d_y_distribution->getUpperBoundOfIndepVar(),
		       true_dist.d_y_distribution->getUpperBoundOfIndepVar()) <
      1e-9 &&
      Policy::relError(d_z_distribution->getLowerBoundOfIndepVar(),
		       true_dist.d_z_distribution->getLowerBoundOfIndepVar()) <
      1e-9 &&
      Policy::relError(d_z_distribution->getUpperBoundOfIndepVar(),
		       true_dist.d_z_distribution->getUpperBoundOfIndepVar()) <
      1e-9;
  }
  else
    return false;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_CartesianSpatialDistribution.cpp
//---------------------------------------------------------------------------//
