//---------------------------------------------------------------------------//
//!
//! \file   Utility_CylindricalSpatialDistribution.cpp
//! \author Alex Robinson
//! \brief  Cylindrical spatial distribution class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_CylindricalSpatialDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_CylindricalCoordinateHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
CylindricalSpatialDistribution::CylindricalSpatialDistribution(
                   const std::shared_ptr<OneDDistribution>& r_distribution,
		   const std::shared_ptr<OneDDistribution>& theta_distribution,
                   const std::shared_ptr<OneDDistribution>& axis_distribution,
                   const double center_x_position,
                   const double center_y_position,
                   const double center_z_position,
                   const Axis axis )
  : d_r_distribution( r_distribution ),
    d_theta_distribution( theta_distribution ),
    d_axis_distribution( axis_distribution ),
    d_center_x_position( center_x_position ),
    d_center_y_position( center_y_position ),
    d_center_z_position( center_z_position ),
    d_axis( axis ),
    d_uniform( true )
{
  // Make sure that the distributions have been set
  testPrecondition( r_distribution.get() );
  testPrecondition( theta_distribution.get() );
  testPrecondition( axis_distribution.get() );
  // Make sure that the theta distribution is valid
  testPrecondition( theta_distribution->getUpperBoundOfIndepVar() 
		    <= 2*PhysicalConstants::pi );
  testPrecondition( theta_distribution->getLowerBoundOfIndepVar()
		    >= 0.0 );
  // Make sure that the start positions are valid
  testPrecondition( !ST::isnaninf( center_x_position ) );
  testPrecondition( !ST::isnaninf( center_y_position ) );
  testPrecondition( !ST::isnaninf( center_z_position ) );

  // Determine if the distribution is uniform
  if( r_distribution->getDistributionType() != POWER_1_DISTRIBUTION )
    d_uniform = false;
  
  if( theta_distribution->getDistributionType() != UNIFORM_DISTRIBUTION )
    d_uniform = false;

  if( axis_distribution->getDistributionType() != UNIFORM_DISTRIBUTION )
    d_uniform = false;
}

// Evaluate the spatial distribution
/*! \details The cylindrical volume element is r*dr*dtheta*dz. Therefore, when
 * evaluating the radial distribution, the value returned must be divided by
 * the radius to account for the volume element. When specifying a radial
 * distribution, the r term of the volume element is assumed to be incorporated
 * into the distribution (this means that a power_1 distribution is actually
 * a uniform distribution, a uniform distribution is actually a 1/r 
 * distribution, etc.). This implicit handling of the volume element does not
 * effect sampling, only evaluation.
 */ 
double CylindricalSpatialDistribution::evaluate( 
				        const double cartesian_point[3] ) const
{
  double cylindrical_point[3];

  CylindricalSpatialDistribution::convertCartesianCoordsToCylindrical(
							   cartesian_point,
							   cylindrical_point );
  
  // If r = 0, re-evaluate at r~0 
  if( cylindrical_point[0] == 0.0 )
    cylindrical_point[0] = std::numeric_limits<double>::min();
  
  double distribution_value = d_r_distribution->evaluate(cylindrical_point[0])/
    cylindrical_point[0];
  distribution_value *= d_theta_distribution->evaluate( cylindrical_point[1] );
  distribution_value *= d_axis_distribution->evaluate( cylindrical_point[2] );

  // If one distribution evaluate to inf and another to zero (value = nan),
  // return zero
  if( distribution_value != distribution_value )
    distribution_value = 0.0;

  // Make sure that the distribution value is valid
  testPostcondition( distribution_value == distribution_value );
  
  return distribution_value;
}

// Evaluate the spatial distribution PDF
double CylindricalSpatialDistribution::evaluatePDF(
					const double cartesian_point[3] ) const
{
  double cylindrical_point[3];

  CylindricalSpatialDistribution::convertCartesianCoordsToCylindrical(
							   cartesian_point,
							   cylindrical_point );
  
  double pdf_value = d_r_distribution->evaluatePDF( cylindrical_point[0] );
  pdf_value *= d_theta_distribution->evaluatePDF( cylindrical_point[1] );
  pdf_value *= d_axis_distribution->evaluatePDF( cylindrical_point[2] );

  // Make sure that the pdf valud is valid
  testPostcondition( !ST::isnaninf( pdf_value ) );

  return pdf_value;
}

// Return a random sample from the distribution
/* \details The sampled position will be a point in cartesian space
 */
void CylindricalSpatialDistribution::sample( double sampled_point[3] ) const
{
  // Sample from the distributions
  const double cylindrical_point[3] = {d_r_distribution->sample(),
				       d_theta_distribution->sample(),
				       d_axis_distribution->sample()};
  // Convert the cylindrical coordinate to cartesian
  convertCylindricalCoordsToCartesian( cylindrical_point, 
				       sampled_point,
				       d_axis );
  
  // Add the initialize position to the sampled point
  sampled_point[0] += d_center_x_position;
  sampled_point[1] += d_center_y_position;
  sampled_point[2] += d_center_z_position;
}

// Return the distribution type
SpatialDistributionType 
CylindricalSpatialDistribution::getDistributionType() const
{
  return CYLINDRICAL_SPATIAL_DISTRIBUTION;
}

// Check if the distribution is uniform
bool CylindricalSpatialDistribution::isUniform() const
{
  return d_uniform;
}

// Check if the distribution has the same bounds
bool CylindricalSpatialDistribution::hasSameBounds( 
				const SpatialDistribution& distribution ) const
{
  if( this->getDistributionType() == distribution.getDistributionType() )
  {
    const CylindricalSpatialDistribution& true_dist =
      dynamic_cast<const CylindricalSpatialDistribution&>( distribution );

    if( d_axis == true_dist.d_axis )
    {
      return 
	Policy::relError( d_center_x_position,
			  true_dist.d_center_x_position ) < 1e-9 &&
	Policy::relError( d_center_y_position,
			  true_dist.d_center_y_position ) < 1e-9 &&
	Policy::relError( d_center_z_position,
			  true_dist.d_center_z_position ) < 1e-9 &&
	Policy::relError(d_r_distribution->getLowerBoundOfIndepVar(),
			 true_dist.d_r_distribution->getLowerBoundOfIndepVar())
	< 1e-9 &&
	Policy::relError(d_r_distribution->getUpperBoundOfIndepVar(), 
			 true_dist.d_r_distribution->getUpperBoundOfIndepVar())
	< 1e-9 &&
	Policy::relError(d_theta_distribution->getLowerBoundOfIndepVar(),
		     true_dist.d_theta_distribution->getLowerBoundOfIndepVar())
	< 1e-9 &&
	Policy::relError(d_theta_distribution->getUpperBoundOfIndepVar(),
		     true_dist.d_theta_distribution->getUpperBoundOfIndepVar())
	< 1e-9 &&
	Policy::relError(d_axis_distribution->getLowerBoundOfIndepVar(),
		      true_dist.d_axis_distribution->getLowerBoundOfIndepVar())
	< 1e-9 &&
	Policy::relError(d_axis_distribution->getUpperBoundOfIndepVar(),
		      true_dist.d_axis_distribution->getUpperBoundOfIndepVar())
	< 1e-9;
    }
    else
      return false;
  }
  else
    return false;
}

// Convert a cartesian coordinate to a cylindrical coordinate
void CylindricalSpatialDistribution::convertCartesianCoordsToCylindrical(
					    const double cartesian_point[3],
					    double cylindrical_point[3] ) const
{
  const double origin[3] = 
    {d_center_x_position, d_center_y_position, d_center_z_position};

  Utility::convertCartesianCoordsToCylindrical( cartesian_point,
						origin,
						cylindrical_point,
						d_axis );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_CylindricalSpatialDistribution.cpp
//---------------------------------------------------------------------------//
