//---------------------------------------------------------------------------//
//!
//! \file   Utility_RotationSphericalCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Rotation spherical coordinate conversion policy definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include this first
#include "Utility_RotationSphericalCoordinateConversionPolicy.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Constructor
/*! \details The axis parameter is the z-axis of the local coordinate system
 * w.r.t. the global Cartesian coordinate system. It does not need to be a 
 * unit vector as it will be normalized by the constructor. 
 */ 
RotationSphericalCoordinateConversionPolicy::RotationSphericalCoordinateConversionPolicy( const double axis[3] )
  : d_axis{ axis[0], axis[1], axis[2] }
{
  // Normalize the axis vector
  normalizeVector( d_axis );
}

// Convert the spatial coordinates to cartesian coordinates
/*! \details The primary coordinate is the local r coordinate. The secondary
 * coordinate is the local theta (azimuthal) coordinate. The tertiary
 * coordinate is the local mu (polar angle cosine) coordinate. They will be
 * converted to coordinates in the global Cartesian coordinate system.
 */
void RotationSphericalCoordinateConversionPolicy::convertToCartesianSpatialCoordinates(
                                          const double primary_spatial_coord,
                                          const double secondary_spatial_coord,
                                          const double tertiary_spatial_coord,
                                          double& x_spatial_coord,
                                          double& y_spatial_coord,
                                          double& z_spatial_coord ) const
{
  // Make sure that the radial spatial coordinate is valid
  testPrecondition( primary_spatial_coord >= 0.0 );
  // Make sure that the mu spatial coordinate is valid
  testPrecondition( tertiary_spatial_coord >= -1.0 );
  testPrecondition( tertiary_spatial_coord <= 1.0 );

  // Convert the spherical coordinates to local cartesian coordinates
  double local_x_spatial_coord, local_y_spatial_coord, local_z_spatial_coord;

  this->convertToCartesianPosition( primary_spatial_coord,
                                    secondary_spatial_coord,
                                    tertiary_spatial_coord,
                                    local_x_spatial_coord,
                                    local_y_spatial_coord,
                                    local_z_spatial_coord );
  
  // Convert the local Cartesian coordinates to global Cartesian coordinates
  convertLocalVectorToGlobalVector( local_x_spatial_coord,
                                    local_y_spatial_coord,
                                    local_z_spatial_coord,
                                    d_axis,
                                    x_spatial_coord,
                                    y_spatial_coord,
                                    z_spatial_coord );

  // Clear rounding errors
  clearVectorOfRoundingErrors( x_spatial_coord,
                               y_spatial_coord,
                               z_spatial_coord,
                               1e-15 );
}

// Convert the cartesian coordinates to the spatial coordinate system
/*! \details The primary coordinate is the local r coordinate. The secondary
 * coordinate is the local theta (azimuthal) coordinate. The tertiary
 * coordinate is the local mu (polar angle cosine) coordinate. The global
 * Cartesian coordinates will be converted to these local coordinates.
 */
void RotationSphericalCoordinateConversionPolicy::convertFromCartesianSpatialCoordinates(
                                         const double x_spatial_coord,
                                         const double y_spatial_coord,
                                         const double z_spatial_coord,
                                         double& primary_spatial_coord,
                                         double& secondary_spatial_coord,
                                         double& tertiary_spatial_coord ) const
{
  // Convert the global cartesian coordinates to local cartesian coordinates
  double local_x_spatial_coord, local_y_spatial_coord, local_z_spatial_coord;

  convertGlobalVectorToLocalVector( x_spatial_coord,
                                    y_spatial_coord,
                                    z_spatial_coord,
                                    d_axis,
                                    local_x_spatial_coord,
                                    local_y_spatial_coord,
                                    local_z_spatial_coord );

  // Clear rounding errors
  clearVectorOfRoundingErrors( local_x_spatial_coord,
                               local_y_spatial_coord,
                               local_z_spatial_coord,
                               1e-15 );

  // Convert the local cartesian coordinates to spherical coordinates
  this->convertFromCartesianPosition( local_x_spatial_coord,
                                      local_y_spatial_coord,
                                      local_z_spatial_coord,
                                      primary_spatial_coord,
                                      secondary_spatial_coord,
                                      tertiary_spatial_coord );
}

// Convert the directional coordinates to cartesian coordinates
/*! \details The local directional coordinates are (1.0,theta,mu). The
 * primary directional coordinate will be ignored since the direction will
 * always lie on the unit sphere. Mu is the polar angle cosine and theta is
 * the azimuthal angle.
 */
void RotationSphericalCoordinateConversionPolicy::convertToCartesianDirectionalCoordinates(
                                      const double,
                                      const double secondary_directional_coord,
                                      const double tertiary_directional_coord,
                                      double& x_directional_coord,
                                      double& y_directional_coord,
                                      double& z_directional_coord ) const
{
  // Make sure that the mu directional coordinate is valid
  testPrecondition( tertiary_directional_coord >= -1.0 );
  testPrecondition( tertiary_directional_coord <= 1.0 );

  // Convert the spherical coordinates to local cartesian coordinates
  double local_x_directional_coord, local_y_directional_coord,
    local_z_directional_coord;

  this->convertToCartesianDirection( 1.0,
                                     secondary_directional_coord,
                                     tertiary_directional_coord,
                                     local_x_directional_coord,
                                     local_y_directional_coord,
                                     local_z_directional_coord );
  
  // Convert the local cartesian coordinates to global cartesian coordinates
  convertLocalVectorToGlobalVector( local_x_directional_coord,
                                    local_y_directional_coord,
                                    local_z_directional_coord,
                                    d_axis,
                                    x_directional_coord,
                                    y_directional_coord,
                                    z_directional_coord );

  // Clear rounding errors
  clearUnitVectorOfRoundingErrors( x_directional_coord,
                                   y_directional_coord,
                                   z_directional_coord,
                                   1e-15 );
}

// Convert the cartesian coordinates to the directional coordinate system
/*! \details The final directional coordinates are (1.0,theta,mu). The
 * primary directional coordinate will will always be 1.0 since a direction 
 * will always lie on the unit sphere. Mu is the polar angle cosine while theta
 * is the azimuthal angle.
 */
void RotationSphericalCoordinateConversionPolicy::convertFromCartesianDirectionalCoordinates(
                                     const double x_directional_coord,
                                     const double y_directional_coord,
                                     const double z_directional_coord,
                                     double& primary_directional_coord,
                                     double& secondary_directional_coord,
                                     double& tertiary_directional_coord ) const
{
  // Make sure that the Cartesian directional coordinates are valid
  testPrecondition( isUnitVector( x_directional_coord, y_directional_coord, z_directional_coord ) );

  // Convert the global cartesian coordinates to local cartesian coordinates
  double local_x_directional_coord, local_y_directional_coord,
    local_z_directional_coord;

  convertGlobalVectorToLocalVector( x_directional_coord,
                                    y_directional_coord,
                                    z_directional_coord,
                                    d_axis,
                                    local_x_directional_coord,
                                    local_y_directional_coord,
                                    local_z_directional_coord );

  // Clear rounding errors
  clearUnitVectorOfRoundingErrors( local_x_directional_coord,
                                   local_y_directional_coord,
                                   local_z_directional_coord,
                                   1e-15 );

  // Convert the local cartesian coordinates to spherical coordinates
  this->convertFromCartesianDirection( local_x_directional_coord,
                                       local_y_directional_coord,
                                       local_z_directional_coord,
                                       primary_directional_coord,
                                       secondary_directional_coord,
                                       tertiary_directional_coord );
}

EXPLICIT_CLASS_SAVE_LOAD_INST( RotationSphericalCoordinateConversionPolicy );

} // end Utility namespace

BOOST_CLASS_EXPORT_IMPLEMENT( Utility::RotationSphericalCoordinateConversionPolicy );

//---------------------------------------------------------------------------//
// end Utility_RotationSphericalCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
