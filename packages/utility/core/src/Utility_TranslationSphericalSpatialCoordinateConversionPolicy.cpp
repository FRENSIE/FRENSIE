//---------------------------------------------------------------------------//
//!
//! \file   Utility_TranslationSphericalSpatialCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Translation spherical spatial coordinate conversion policy def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_TranslationSphericalSpatialCoordinateConversionPolicy.hpp"

namespace Utility{

// Constructor
/*! \details The origin is the origin of the local spherical coordinate system
 * w.r.t. the global Cartesian coordinate system.
 */
TranslationSphericalSpatialCoordinateConversionPolicy::TranslationSphericalSpatialCoordinateConversionPolicy(
                                                       const double origin[3] )
  : d_origin{ origin[0], origin[1], origin[2] }
{ /* ... */ }

// Convert the spatial coordinates to cartesian coordinates
/*! \details The primary coordinate is the local r coordinate. The secondary
 * coordinate is the local theta (azimuthal) coordinate. The tertiary
 * coordinate is the local mu (polar angle cosine) coordinate. They will be
 * converted to coordinates in the global Cartesian coordinate system.
 */
void TranslationSphericalSpatialCoordinateConversionPolicy::convertToCartesianSpatialCoordinates(
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

  // Convert the local spherical coordinates to local Cartesian coordinates
  double local_x_spatial_coord, local_y_spatial_coord, local_z_spatial_coord;

  this->convertToCartesianPosition( primary_spatial_coord,
                                    secondary_spatial_coord,
                                    tertiary_spatial_coord,
                                    local_x_spatial_coord,
                                    local_y_spatial_coord,
                                    local_z_spatial_coord );

  // Convert the local Cartesian coordinates to global Cartesian coordinates
  this->translateLocalCartesianPositionToGlobalCartesianPosition(
                                                       primary_spatial_coord,
                                                       secondary_spatial_coord,
                                                       tertiary_spatial_coord,
                                                       d_origin,
                                                       x_spatial_coord,
                                                       y_spatial_coord,
                                                       z_spatial_coord );
}

// Convert the cartesian coordinates to the spatial coordinate system
/*! \details The primary coordinate is the local r coordinate. The secondary
 * coordinate is the local theta (azimuthal) coordinate. The tertiary
 * coordinate is the local mu (polar angle cosine) coordinate. The global
 * Cartesian coordinates will be converted to these local coordinates.
 */
void TranslationSphericalSpatialCoordinateConversionPolicy::convertFromCartesianSpatialCoordinates(
                                         const double x_spatial_coord,
                                         const double y_spatial_coord,
                                         const double z_spatial_coord,
                                         double& primary_spatial_coord,
                                         double& secondary_spatial_coord,
                                         double& tertiary_spatial_coord ) const
{
  // Convert the global Cartesian coordinates to local Cartesian coordinates
  double local_x_spatial_coord, local_y_spatial_coord, local_z_spatial_coord;

  this->translateGlobalCartesianPositionToLocalCartesianPosition(
                                                      x_spatial_coord,
                                                      y_spatial_coord,
                                                      z_spatial_coord,
                                                      d_origin,
                                                      primary_spatial_coord,
                                                      secondary_spatial_coord,
                                                      tertiary_spatial_coord );

  // Convert the local cartesian coordinates to spherical coordinates
  this->convertFromCartesianPosition( local_x_spatial_coord,
                                      local_y_spatial_coord,
                                      local_z_spatial_coord,
                                      primary_spatial_coord,
                                      secondary_spatial_coord,
                                      tertiary_spatial_coord );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_TranslationSphericalSpatialCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
