//---------------------------------------------------------------------------//
//!
//! \file   CylindricalSpatialDistribution.cpp
//! \author Alex Robinson
//! \brief  Cylindrical spatial distribution class definition.
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "CylindricalSpatialDistribution.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
CylindricalSpatialDistribution::CylindricalSpatialDistribution(
                      const Teuchos::RCP<OneDDistribution>& r_distribution,
		      const Teuchos::RCP<OneDDistribution>& theta_distribution,
		      const Teuchos::RCP<OneDDistribution>& axis_distribution,
		      const double start_x_position,
		      const double start_y_position,
		      const double start_z_position,
		      const Axis axis )
  : d_r_distribution( r_distribution ),
    d_theta_distribution( theta_distribution ),
    d_axis_distribution( axis_distribution ),
    d_start_x_position( start_x_position ),
    d_start_y_position( start_y_position ),
    d_start_z_position( start_z_position ),
    d_axis( axis )
{
  // Make sure that the distributions have been set
  testPrecondition( !r_distribution.is_null() );
  testPrecondition( !theta_distribution.is_null() );
  testPrecondition( !axis_distribution.is_null() );
  // Make sure that the theta distribution is valid
  testPrecondition( theta_distribution->getUpperBoundOfIndepVar() 
		    <= 2*acos(-1.0) );
  testPrecondition( theta_distribution->getLowerBoundOfIndepVar()
		    >= 0.0 );
  // Make sure that the start positions are valid
  testPrecondition( !ST::isnaninf( start_x_position ) );
  testPrecondition( !ST::isnaninf( start_y_position ) );
  testPrecondition( !ST::isnaninf( start_z_position ) );
}

// Return a random sample from the distribution
/* \details The sampled position will be a point in cartesian space
 */
void CylindricalSpatialDistribution::sample( double sampled_point[3] )
{
  // Sample from the distributions
  double radius = d_r_distribution->sample();
  
  double theta = d_theta_distribution->sample();
  double cos_theta = cos( theta );
  double sin_theta = sin( theta );
  
  double axis_position = d_axis_distribution->sample();

  // Initialize the sampled position
  sampled_point[0] = d_start_x_position;
  sampled_point[1] = d_start_y_position;
  sampled_point[2] = d_start_z_position;

  // Construct the sampled position
  switch( d_axis )
  {
  case Z_AXIS:
    sampled_point[0] += radius*cos_theta;
    sampled_point[1] += radius*sin_theta;
    sampled_point[2] += axis_position;
    break;
    
  case Y_AXIS:
    sampled_point[0] += radius*sin_theta;
    sampled_point[1] += axis_position;
    sampled_point[2] += radius*cos_theta;
    break;
    
  case X_AXIS:
    sampled_point[0] += axis_position;
    sampled_point[1] += radius*cos_theta;
    sampled_point[2] += radius*sin_theta;
    break;
  }
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end CylindricalSpatialDistribution.cpp
//---------------------------------------------------------------------------//
