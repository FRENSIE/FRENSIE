//---------------------------------------------------------------------------//
//!
//! \file   Utility_CartesianSpatialCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Cartesian spatial coordinate conversion policy definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_CartesianSpatialCoordinateConversionPolicy.hpp"

namespace Utility{

// Convert the spatial coordinates to cartesian coordinates
void CartesianSpatialCoordinateConversionPolicy::convertToCartesianCoordinates(
                                          const double primary_spatial_coord,
                                          const double secondary_spatial_coord,
                                          const double tertiary_spatial_coord,
                                          double& x_spatial_coord,
                                          double& y_spatial_coord,
                                          double& z_spatial_coord ) const
{
  x_spatial_coord = primary_spatial_coord;
  y_spatial_coord = secondary_spatial_coord;
  z_spatial_coord = tertiary_spatial_coord;
}

// Convert the cartesian coordinates to the spatial coordinate system
void CartesianSpatialCoordinateConversionPolicy::convertFromCartesianCoordinates(
                                         const double x_spatial_coord,
                                         const double y_spatial_coord,
                                         const double z_spatial_coord,
                                         double& primary_spatial_coord,
                                         double& secondary_spatial_coord,
                                         double& tertiary_spatial_coord ) const
{
  primary_spatial_coord = x_spatial_coord;
  secondary_spatial_coord = y_spatial_coord;
  tertiary_spatial_coord = z_spatial_coord;
}

  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_CartesianSpatialCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
