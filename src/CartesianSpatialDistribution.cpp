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
			 const Teuchos::RCP<OneDDistribution>& x_distribution,
			 const Teuchos::RCP<OneDDistribution>& y_distribution,
			 const Teuchos::RCP<OneDDistribution>& z_distribution )
  : d_x_distribution( x_distribution ),
    d_y_distribution( y_distribution ),
    d_z_distribution( z_distribution )
{
  // Make sure that the distributions have been set
  testPrecondition( !x_distribution.is_null() );
  testPrecondition( !y_distribution.is_null() );
  testPrecondition( !z_distribution.is_null() );
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
void CartesianSpatialDistribution::sample( double sampled_point[3] )
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
