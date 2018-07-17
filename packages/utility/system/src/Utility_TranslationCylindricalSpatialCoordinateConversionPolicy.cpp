//---------------------------------------------------------------------------//
//!
//! \file   Utility_TranslationCylindricalSpatialCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Translation cylindrical spatial coordinate conversion policy def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Utility_TranslationCylindricalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Constructor
/*! \details The origin is the origin of the local cylindrical coordinate 
 * system w.r.t. the global Cartesian coordinate system.
 */
TranslationCylindricalSpatialCoordinateConversionPolicy::TranslationCylindricalSpatialCoordinateConversionPolicy(
                                                       const double origin[3] )
  : d_origin{ origin[0], origin[1], origin[2] }
{ /* ... */ }

// Convert the spatial coordinates to cartesian coordinates
/*! \details The primary coordinate is the local r coordinate. The secondary
 * coordinate is the local theta (azimuthal) coordinate. The tertiary
 * coordinate is the local z coordinate. They will be converted to coordinates 
 * in the global Cartesian coordinate system.
 */
void TranslationCylindricalSpatialCoordinateConversionPolicy::convertToCartesianSpatialCoordinates(
                                          const double primary_spatial_coord,
                                          const double secondary_spatial_coord,
                                          const double tertiary_spatial_coord,
                                          double& x_spatial_coord,
                                          double& y_spatial_coord,
                                          double& z_spatial_coord ) const
{
  // Make sure that the radial spatial coordinate is valid
  testPrecondition( primary_spatial_coord >= 0.0 );

  // Convert the local cylindrical coordinates to local Cartesian coordinates
  double local_x_spatial_coord, local_y_spatial_coord, local_z_spatial_coord;

  this->convertToCartesianPosition( primary_spatial_coord,
                                    secondary_spatial_coord,
                                    tertiary_spatial_coord,
                                    local_x_spatial_coord,
                                    local_y_spatial_coord,
                                    local_z_spatial_coord );

  // Convert the local Cartesian coordinates to global Cartesian coordinates
  this->translateLocalCartesianPositionToGlobalCartesianPosition(
                                                       local_x_spatial_coord,
                                                       local_y_spatial_coord,
                                                       local_z_spatial_coord,
                                                       d_origin,
                                                       x_spatial_coord,
                                                       y_spatial_coord,
                                                       z_spatial_coord );
}

// Convert the cartesian coordinates to the spatial coordinate system
/*! \details The primary coordinate is the local r coordinate. The secondary
 * coordinate is the local theta (azimuthal) coordinate. The tertiary
 * coordinate is the local z coordinate. The global Cartesian coordinates will 
 * be converted to these local coordinates.
 */
void TranslationCylindricalSpatialCoordinateConversionPolicy::convertFromCartesianSpatialCoordinates(
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
                                                       local_x_spatial_coord,
                                                       local_y_spatial_coord,
                                                       local_z_spatial_coord );

  // Convert the local Cartesian coordinates to cylindrical coordinates
  this->convertFromCartesianPosition( local_x_spatial_coord,
                                      local_y_spatial_coord,
                                      local_z_spatial_coord,
                                      primary_spatial_coord,
                                      secondary_spatial_coord,
                                      tertiary_spatial_coord );
}

EXPLICIT_CLASS_SAVE_LOAD_INST( TranslationCylindricalSpatialCoordinateConversionPolicy );
  
} // end Utility namespace

BOOST_CLASS_EXPORT_IMPLEMENT( Utility::TranslationCylindricalSpatialCoordinateConversionPolicy );

//---------------------------------------------------------------------------//
// end Utility_TranslationCylindricalSpatialCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
