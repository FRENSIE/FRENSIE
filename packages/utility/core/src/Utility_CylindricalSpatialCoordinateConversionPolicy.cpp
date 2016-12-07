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
void CylindricalSpatialCoordinateConversionPolicy::convertToCartesianCoordinates(
                                       const double primary_spatial_coord,
                                       const double secondary_spatial_coord,
                                       const double tertiary_spatial_coord,
                                       double& x_spatial_coord,
                                       double& y_spatial_coord,
                                       double& z_spatial_coord ) const override
{

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

}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_CylindricalSpatialCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
