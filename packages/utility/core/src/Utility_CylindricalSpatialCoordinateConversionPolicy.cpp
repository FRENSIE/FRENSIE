//---------------------------------------------------------------------------//
//!
//! \file   Utility_CylindricalSpatialCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Cylindrical coordinate conversion policy definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_CylindricalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
CylindricalSpatialCoordinateConversionPolicy::CylindricalSpatialCoordinateConversionPolicy(
                                                        const double origin[3],
                                                        const double axis[3] )
  : d_origin( {origin[0], origin[1], origin[2]} ),
    d_axis( {axis[0], axis[1], axis[2]} )
{
  // Normalize the axis vector
  normalizeDirection( d_axis );
}

// Convert the spatial coordinates to cartesian coordinates
/*! \details
 */
void CylindricalSpatialCoordinateConversionPolicy::convertToCartesianCoordinates(
                                       const double primary_spatial_coord,
                                       const double secondary_spatial_coord,
                                       const double tertiary_spatial_coord,
                                       double& x_spatial_coord,
                                       double& y_spatial_coord,
                                       double& z_spatial_coord ) const override
{
  // Compute the cartesian coordinates w.r.t. the specified axis
  const double local_x_spatial_coord =
    primary_spatial_coord*cos(secondary_spatial_coord);
  const double local_y_spatial_coord =
    primary_spatial_coord*cos(secondary_spatial_coord);
  
  double axis_polar_angle_sine =
    sqrt( std::max(0.0, 1.0 - d_axis[2]*d_axis[2]) );

  if( axis_polar_angle_sine > 1e-10 )
  {
    x_spatial_coord = (d_axis[0]*d_axis[2]*local_x_spatial_coord -
                       d_axis[1]*local_y_spatial_coord)/axis_polar_angle_sine +
      d_axis[0]*tertiary_spatial_coord + d_origin[0];

    y_spatial_coord = (d_axis[1]*d_axis[2]*local_x_spatial_coord +
                       d_axis[0]*local_y_spatial_coord)/axis_polar_angle_sine +
      d_axis[1]*tertiary_spatial_coord + d_origin[1];

    z_spatial_coord = -axis_polar_angle_sine*tertiary_spatial_coord +
      d_axis[2]*tertiary_spatial_coord + d_origin[2];
      
  }
  // For the special case where z-component of the axis vector ~ 1 =>
  // sqrt(1 - z^2) ~ 0. Assume spherical coordinates are w.r.t. the y-axis
  // instead of the z-axis
  else
  {
    // Recompute the sine of the polar angle of the axis direction
    axis_polar_angle_sine =
      sqrt( std::max(0.0, 1.0 - d_axis[1]*d_axis[1]) );

    x_spatial_coord = (d_axis[0]*d_axis[1]*local_x_spatial_coord +
                       d_axis[2]*local_y_spatial_coord)/axis_polar_angle_sine +
      d_axis[0]*tertiary_spatial_coord + d_origin[0];

    y_spatial_coord = -axis_polar_angle_sine*local_x_spatial_coord +
      d_axis[1]*tertiary_spatial_coord + d_origin[1];

    z_spatial_coord = (d_axis[1]*d_axis[2]*local_x_spatial_coord -
                       d_axis[0]*local_y_spatial_coord)/axis_polar_angle_sine +
      d_axis[2]*tertiary_spatial_coord + d_origin[2];
  }
}

// Convert the cartesian coordinates to the spatial coordinate system
void CylindricalSpatialCoordinateConversionPolicy::convertFromCartesianCoordinates(
                                const double x_spatial_coord,
                                const double y_spatial_coord,
                                const double z_spatial_coord,
                                double& primary_spatial_coord,
                                double& secondary_spatial_coord,
                                double& tertiary_spatial_coord ) const override
{
  // Compute the spatial coordinates w.r.t. the origin
  const double relative_x_spatial_coord = x_spatial_coord - d_origin[0];
  const double relative_y_spatial_coord = y_spatial_coord - d_origin[1];
  const double relative_z_spatial_coord = z_spatial_coord - d_origin[2];

  // Compute the local coordinates w.r.t. the axis
  double axis_polar_angle_sine =
    sqrt( std::max(0.0, 1.0 - d_axis[2]*d_axis[2]) );

  double local_x_spatial_coord;
  double local_y_spatial_coord;

  if( axis_polar_angle_sine > 1e-10 )
  {
    local_x_spatial_coord = (d_axis[0]*relative_x_spatial_coord +
                             d_axis[1]*relative_y_spatial_coord)*
      (d_axis[2]/axis_polar_angle_sine) -
      axis_polar_angle_sine*relative_z_spatial_coord;

    local_y_spatial_coord = (d_axis[0]*relative_y_spatial_coord -
                             d_axis[1]*relative_x_spatial_coord)/
      axis_polar_angle_sine;

    tertiary_spatial_coord = d_axis[0]*relative_x_spatial_coord +
      d_axis[1]*relative_y_spatial_coord +
      d_axis[2]*relative_z_spatial_coord;
  }
  // For the special case where z-component of the axis vector ~ 1 =>
  // sqrt(1 - z^2) ~ 0. Assume spherical coordinates are w.r.t. the y-axis
  // instead of the z-axis
  else
  {
    // Recompute the sine of the polar angle of the axis direction
    axis_polar_angle_sine =
      sqrt( std::max(0.0, 1.0 - d_axis[1]*d_axis[1]) );

    local_x_spatial_coord = (d_axis[0]*relative_x_spatial_coord +
                             d_axis[2]*relative_z_spatial_coord)*
      (d_axis[1]/axis_polar_angle_sine) -
      axis_polar_angle_sine*relative_y_spatial_coord;

    local_y_spatial_coord = (d_axis[2]*relative_x_spatial_coord -
                             d_axis[0]*relative_z_spatial_coord)/
      axis_polar_angle_sine;

    tertiary_spatial_coord = d_axis[0]*relative_x_spatial_coord +
      d_axis[1]*relative_y_spatial_coord +
      d_axis[2]*relative_z_spatial_coord;
  }

  // Convert the local cartesian coordinates into cylindrical coordinates
  primary_spatial_coord = sqrt(local_x_spatial_coord*local_x_spatial_coord +
                               local_y_spatial_coord*local_y_spatial_coord);

  secondary_spatial_coord = atan2( local_y_spatial_coord,
                                   local_x_spatial_coord );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_CylindricalSpatialCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
