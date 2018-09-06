//---------------------------------------------------------------------------//
//!
//! \file   Utility_GeneralSphericalSpatialCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  General spherical spatial coordinate conversion policy definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Utility_GeneralSphericalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Constructor
GeneralSphericalSpatialCoordinateConversionPolicy::GeneralSphericalSpatialCoordinateConversionPolicy(
                                                        const double origin[3],
                                                        const double axis[3] )
  : d_origin{origin[0], origin[1], origin[2]},
    d_axis{axis[0], axis[1], axis[2]}
{
  // Normalize the axis vector
  normalizeVector( d_axis );
}

// Convert the spatial coordinates to cartesian coordinates
/*! \details The original spatial coordinates are (r,theta,mu). Mu is the polar
 * angle cosine w.r.t. the axis vector while theta is the azimuthal angle 
 * w.r.t. the axis vector.
 */
void GeneralSphericalSpatialCoordinateConversionPolicy::convertToCartesianSpatialCoordinates(
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
  
  // Convert the local cartesian coordinates to global cartesian coordinates
  convertLocalVectorToGlobalVector( local_x_spatial_coord,
                                    local_y_spatial_coord,
                                    local_z_spatial_coord,
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
/*! \details The final spatial coordinates are (r,theta,mu). Mu is the polar
 * angle cosine w.r.t. the axis vector while theta is the azimuthal angle 
 * w.r.t. the axis vector.
 */
void GeneralSphericalSpatialCoordinateConversionPolicy::convertFromCartesianSpatialCoordinates(
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
                                    d_origin,
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

EXPLICIT_CLASS_SAVE_LOAD_INST( GeneralSphericalSpatialCoordinateConversionPolicy );
  
} // end Utility namespace

BOOST_CLASS_EXPORT_IMPLEMENT( Utility::GeneralSphericalSpatialCoordinateConversionPolicy );

//---------------------------------------------------------------------------//
// end Utility_GeneralSphericalSpatialCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
