//---------------------------------------------------------------------------//
//!
//! \file   Utility_GeneralCylindricalSpatialCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  General cylindrical spatial coordinate conversion policy definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_GeneralCylindricalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
GeneralCylindricalSpatialCoordinateConversionPolicy::GeneralCylindricalSpatialCoordinateConversionPolicy(
                                                        const double origin[3],
                                                        const double axis[3] )
  : d_origin( {origin[0], origin[1], origin[2]} ),
    d_axis( {axis[0], axis[1], axis[2]} )
{
  // Normalize the axis vector
  normalizeVector( d_axis );
}

// Constructor (global origin)
GeneralCylindricalSpatialCoordinateConversionPolicy::GeneralCylindricalSpatialCoordinateConversionPolicy(
                                                         const double axis[3] )
  : d_origin( {0.0, 0.0, 0.0} )
    d_axis( {axis[0], axis[1], axis[2]} )
{
  // Normalize the axis vector
  normalizeVector( d_axis );
}

// Convert the spatial coordinates to cartesian coordinates
/*! \details The original spatial coordinates are (r,theta,z').
 */
void GeneralCylindricalSpatialCoordinateConversionPolicy::convertToCartesianSpatialCoordinates(
                                       const double primary_spatial_coord,
                                       const double secondary_spatial_coord,
                                       const double tertiary_spatial_coord,
                                       double& x_spatial_coord,
                                       double& y_spatial_coord,
                                       double& z_spatial_coord ) const override
{
  // Convert the cylindrical coordinates to local cartesian coordinates
  const double local_x_spatial_coord, local_y_spatial_coord,
    local_z_spatial_coord;

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
}

// Convert the cartesian coordinates to the spatial coordinate system
/*! \details The final spatial coordinates are (r,theta,z')
 */
void GeneralCylindricalSpatialCoordinateConversionPolicy::convertFromCartesianSpatialCoordinates(
                                const double x_spatial_coord,
                                const double y_spatial_coord,
                                const double z_spatial_coord,
                                double& primary_spatial_coord,
                                double& secondary_spatial_coord,
                                double& tertiary_spatial_coord ) const override
{
  
  // Convert the global cartesian coordinates to local cartesian coordinates
  const double local_x_spatial_coord, local_y_spatial_coord;
  
  convertGlobalVectorToLocalVector( x_spatial_coord,
                                    y_spatial_coord,
                                    z_spatial_coord,
                                    d_axis,
                                    d_origin,
                                    local_x_spatial_coord,
                                    local_y_spatial_coord,
                                    tertiary_spatial_coord );

  // Convert the local cartesian coordinates to cylindrical coordinates
  this->convertFromCartesianPosition( local_x_spatial_coord,
                                      local_y_spatial_coord,
                                      tertiary_spatial_coord,
                                      primary_spatial_coord,
                                      secondary_spatial_coord,
                                      tertiary_spatial_coord );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_CylindricalSpatialCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
