//---------------------------------------------------------------------------//
//!
//! \file   Utility_RotationCartesianCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Rotation Cartesian coordinate conversion policy definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Utility_RotationCartesianCoordinateConversionPolicy.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Constructor
/*! \details The axis parameter is the z-axis of the local coordinate system
 * w.r.t. the global coordinate system. It does not need to be a unit vector
 * as it will be normalized by the constructor.
 */
RotationCartesianCoordinateConversionPolicy::RotationCartesianCoordinateConversionPolicy( const double axis[3] )
  : d_axis{ axis[0], axis[1], axis[2] }
{
  // Normalize the axis vector
  normalizeVector( d_axis );
}

// Convert the spatial coordinates to cartesian coordinates
/*! \details The primary, secondary and tertiary spatial coordinates are the
 * Cartesian coordinates in the local coordinate system. They will be converted
 * to coordinates in the global coordinate system by using a rotation matrix
 * created from the axis vector.
 */
void RotationCartesianCoordinateConversionPolicy::convertToCartesianSpatialCoordinates(
                                          const double primary_spatial_coord,
                                          const double secondary_spatial_coord,
                                          const double tertiary_spatial_coord,
                                          double& x_spatial_coord,
                                          double& y_spatial_coord,
                                          double& z_spatial_coord ) const
{
  convertLocalVectorToGlobalVector( primary_spatial_coord,
                                    secondary_spatial_coord,
                                    tertiary_spatial_coord,
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
/*! \details The x, y and z spatial coordinates are the Cartesian coordinates
 * in the global coordinate system. They will be converted to coordinates in
 * the local coordinate system by using a rotation matrix created from the
 * axis vector.
 */
void RotationCartesianCoordinateConversionPolicy::convertFromCartesianSpatialCoordinates(
                                         const double x_spatial_coord,
                                         const double y_spatial_coord,
                                         const double z_spatial_coord,
                                         double& primary_spatial_coord,
                                         double& secondary_spatial_coord,
                                         double& tertiary_spatial_coord ) const
{
  convertGlobalVectorToLocalVector( x_spatial_coord,
                                    y_spatial_coord,
                                    z_spatial_coord,
                                    d_axis,
                                    primary_spatial_coord,
                                    secondary_spatial_coord,
                                    tertiary_spatial_coord );

  // Clear rounding errors
  clearVectorOfRoundingErrors( primary_spatial_coord,
                               secondary_spatial_coord,
                               tertiary_spatial_coord,
                               1e-15 );
}

// Convert the directional coordinates to cartesian coordinates
/*! \details The primary, secondary and tertiary directional coordinates are
 * the Cartesian coordinates in the local coordinate system. They will be
 * converted to coordinates in the global coordinate system by using a rotation
 * matrix created from the axis vector
 */
void RotationCartesianCoordinateConversionPolicy::convertToCartesianDirectionalCoordinates(
                                      const double primary_directional_coord,
                                      const double secondary_directional_coord,
                                      const double tertiary_directional_coord,
                                      double& x_directional_coord,
                                      double& y_directional_coord,
                                      double& z_directional_coord ) const
{
  // Make sure that the input directional coordinates are valid
  testPrecondition( isUnitVector( primary_directional_coord, secondary_directional_coord, tertiary_directional_coord ) );

  convertLocalVectorToGlobalVector( primary_directional_coord,
                                    secondary_directional_coord,
                                    tertiary_directional_coord,
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
/*! \details The x, y and z directional coordinates are the Cartesian
 * coordinates in the global coordinate system. They will be converted to
 * coordinates in the local coordinate system by using a rotation matrix
 * created from the axis vector.
 */
void RotationCartesianCoordinateConversionPolicy::convertFromCartesianDirectionalCoordinates(
                                     const double x_directional_coord,
                                     const double y_directional_coord,
                                     const double z_directional_coord,
                                     double& primary_directional_coord,
                                     double& secondary_directional_coord,
                                     double& tertiary_directional_coord ) const
{
  // Make sure that the input directional coordinates are valid
  testPrecondition( isUnitVector( x_directional_coord, y_directional_coord, z_directional_coord ) );

  convertGlobalVectorToLocalVector( x_directional_coord,
                                    y_directional_coord,
                                    z_directional_coord,
                                    d_axis,
                                    primary_directional_coord,
                                    secondary_directional_coord,
                                    tertiary_directional_coord );

  // Clear rounding errors
  clearUnitVectorOfRoundingErrors( primary_directional_coord,
                                   secondary_directional_coord,
                                   tertiary_directional_coord,
                                   1e-15 );
}

EXPLICIT_CLASS_SAVE_LOAD_INST( RotationCartesianCoordinateConversionPolicy );

} // end Utility namespace

BOOST_CLASS_EXPORT_IMPLEMENT( Utility::RotationCartesianCoordinateConversionPolicy );

//---------------------------------------------------------------------------//
// end Utility_RotationCartesianCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
