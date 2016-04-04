//---------------------------------------------------------------------------//
//!
//! \file   Utility_SphericalDirectionalDistribution.hpp
//! \author Alex Robinson
//! \brief  Spherical directional distribution class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_SphericalDirectionalDistribution.hpp"
#include "Utility_SphericalCoordinateHelpers.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
SphericalDirectionalDistribution::SphericalDirectionalDistribution( 
		   const std::shared_ptr<OneDDistribution>& theta_distribution,
                   const std::shared_ptr<OneDDistribution>& mu_distribution,
                   const Axis axis )
  : d_theta_distribution( theta_distribution ),
    d_mu_distribution( mu_distribution ),
    d_axis( axis )
{
  // Make sure that the distributions have been set
  testPrecondition( theta_distribution.get() );
  testPrecondition( mu_distribution.get() );
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
}

// Evaluate the direction distribution
double SphericalDirectionalDistribution::evaluate( 
				        const double cartesian_point[3] ) const
{
  // Make sure that the point is a valid direction
  testPrecondition( validDirection( cartesian_point ) );
  
  double spherical_point[3];

  SphericalDirectionalDistribution::convertCartesianCoordsToSpherical(cartesian_point,
							     spherical_point );

  double distribution_value = 
    d_theta_distribution->evaluate( spherical_point[1] );
  distribution_value *= d_mu_distribution->evaluate( spherical_point[2] );

  // If one distribution evaluates to inf and another to zero (value = nan),
  // return zero
  if( distribution_value != distribution_value )
    distribution_value = 0.0;

  // Make sure that the distribution value is valid
  testPostcondition( distribution_value == distribution_value );
  
  return distribution_value;
}

// Evaluate the directional distribution PDF
double SphericalDirectionalDistribution::evaluatePDF( 
					const double cartesian_point[3] ) const
{
  // Make sure that the point is a valid direction
  testPrecondition( validDirection( cartesian_point ) );
  
  double spherical_point[3];

  SphericalDirectionalDistribution::convertCartesianCoordsToSpherical(cartesian_point,
							     spherical_point );
  double pdf_value = d_theta_distribution->evaluatePDF( spherical_point[1] );
  pdf_value *= d_mu_distribution->evaluatePDF( spherical_point[2] );

  // Make sure that the pdf value is valid
  testPostcondition( !ST::isnaninf( pdf_value ) );

  return pdf_value; 
}

// Return a random (cartesian) sample from the distribution (u, v, w)
void SphericalDirectionalDistribution::sample( double sampled_direction[3] ) const
{
  // Sample from the distributions
  const double spherical_point[3] = {1.0,
				     d_theta_distribution->sample(),
				     d_mu_distribution->sample()};
  
  // Convert the spherical coordinate to cartesian
  convertSphericalCoordsToCartesian( spherical_point,
				     sampled_direction,
				     d_axis );
}

// Return the distribution type
DirectionalDistributionType SphericalDirectionalDistribution::getDistributionType() const
{
  return SPHERICAL_DIRECTIONAL_DISTRIBUTION;
}

// Convert a cartesian coordinate to a spherical coordinate
void SphericalDirectionalDistribution::convertCartesianCoordsToSpherical( 
					      const double cartesian_point[3],
					      double spherical_point[3] ) const
{
  const double origin[3] = {0.0, 0.0, 0.0};

  Utility::convertCartesianCoordsToSpherical( cartesian_point,
					      origin,
					      spherical_point,
					      d_axis );
}

// Check if the distribution has the same bounds
bool SphericalDirectionalDistribution::hasSameBounds( 
			    const DirectionalDistribution& distribution ) const
{
  if( this->getDistributionType() == distribution.getDistributionType() )
  {
    const SphericalDirectionalDistribution& true_dist = 
      dynamic_cast<const SphericalDirectionalDistribution&>( distribution );

    
    if( d_axis == true_dist.d_axis )
    {
      return 
	Policy::relError(d_theta_distribution->getLowerBoundOfIndepVar(),
		  true_dist.d_theta_distribution->getLowerBoundOfIndepVar())
	< 1e-9 &&
	  Policy::relError(d_theta_distribution->getUpperBoundOfIndepVar(),
		  true_dist.d_theta_distribution->getUpperBoundOfIndepVar())
	< 1e-9 &&
	  Policy::relError(d_mu_distribution->getLowerBoundOfIndepVar(),
		     true_dist.d_mu_distribution->getLowerBoundOfIndepVar())
	< 1e-9 &&
	  Policy::relError(d_mu_distribution->getUpperBoundOfIndepVar(),
		     true_dist.d_mu_distribution->getUpperBoundOfIndepVar())
	< 1e-9;
    }
    else
      return false;
  }
  else
    return false;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_SphericalDirectionalDistribution.cpp
//---------------------------------------------------------------------------//
