//---------------------------------------------------------------------------//
//!
//! \file   CylindricalSpatialDistribution.cpp
//! \author Alex Robinson
//! \brief  Cylindrical spatial distribution class definition.
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "CylindricalSpatialDistribution.hpp"
#include "PhysicalConstants.hpp"
#include "CylindricalCoordinateHelpers.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
CylindricalSpatialDistribution::CylindricalSpatialDistribution(
                      const Teuchos::RCP<OneDDistribution>& r_distribution,
		      const Teuchos::RCP<OneDDistribution>& theta_distribution,
		      const Teuchos::RCP<OneDDistribution>& axis_distribution,
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
    d_axis( axis )
{
  // Make sure that the distributions have been set
  testPrecondition( !r_distribution.is_null() );
  testPrecondition( !theta_distribution.is_null() );
  testPrecondition( !axis_distribution.is_null() );
  // Make sure that the theta distribution is valid
  testPrecondition( theta_distribution->getUpperBoundOfIndepVar() 
		    <= 2*PhysicalConstants::pi );
  testPrecondition( theta_distribution->getLowerBoundOfIndepVar()
		    >= 0.0 );
  // Make sure that the start positions are valid
  testPrecondition( !ST::isnaninf( center_x_position ) );
  testPrecondition( !ST::isnaninf( center_y_position ) );
  testPrecondition( !ST::isnaninf( center_z_position ) );
}

// Evaluate the spatial distribution
double CylindricalSpatialDistribution::evaluate( 
				        const double cartesian_point[3] ) const
{
  double cylindrical_point[3];

  CylindricalSpatialDistribution::convertCartesianCoordsToCylindrical(
							   cartesian_point,
							   cylindrical_point );
  
  double distribution_value = d_r_distribution->evaluate(cylindrical_point[0]);
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
void CylindricalSpatialDistribution::sample( double sampled_point[3] )
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

// Convert a cartesian coordinate to a cylindrical coordinate
void CylindricalSpatialDistribution::convertCartesianCoordsToCylindrical(
					    const double cartesian_point[3],
					    double cylindrical_point[3] ) const
{
  const double origin[3] = 
    {d_center_x_position, d_center_y_position, d_center_z_position};

  FACEMC::convertCartesianCoordsToCylindrical( cartesian_point,
					       origin,
					       cylindrical_point,
					       d_axis );
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end CylindricalSpatialDistribution.cpp
//---------------------------------------------------------------------------//
