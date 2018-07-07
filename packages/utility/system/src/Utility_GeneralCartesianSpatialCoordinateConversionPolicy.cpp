//---------------------------------------------------------------------------//
//!
//! \file   Utility_GeneralCartesianSpatialCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  General Cartesian spatial coordinate conversion policy definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Utility_GeneralCartesianSpatialCoordinateConversionPolicy.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Constructor
/*! \details The origin is the origin of the local coordinate system w.r.t. the
 * global coordinate system. The axis parameter is the z-axis of the local
 * coordinate system w.r.t. the global coordinate system. It does not need to
 * be a unit vector as it will be normalized by the constructor.
 */
GeneralCartesianSpatialCoordinateConversionPolicy::GeneralCartesianSpatialCoordinateConversionPolicy(
                                                        const double origin[3],
                                                        const double axis[3] )
  : d_origin{origin[0], origin[1], origin[2]},
    d_axis{axis[0], axis[1], axis[2]}
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
void GeneralCartesianSpatialCoordinateConversionPolicy::convertToCartesianSpatialCoordinates(
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
                                    d_origin,
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
void GeneralCartesianSpatialCoordinateConversionPolicy::convertFromCartesianSpatialCoordinates(
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
                                    d_origin,
                                    primary_spatial_coord,
                                    secondary_spatial_coord,
                                    tertiary_spatial_coord );

  // Clear rounding errors
  clearVectorOfRoundingErrors( primary_spatial_coord,
                               primary_spatial_coord,
                               primary_spatial_coord,
                               1e-15 );
}

EXPLICIT_CLASS_SAVE_LOAD_INST( GeneralCartesianSpatialCoordinateConversionPolicy );

} // end Utility namespace

BOOST_CLASS_EXPORT_IMPLEMENT( Utility::GeneralCartesianSpatialCoordinateConversionPolicy );

//---------------------------------------------------------------------------//
// end Utility_GeneralCartesianCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
