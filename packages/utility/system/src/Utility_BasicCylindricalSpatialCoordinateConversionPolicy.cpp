//---------------------------------------------------------------------------//
//!
//! \file   Utility_BasicCylindricalSpatialCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Basic cylindrical spatial coordinate conversion policy definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must be included first
#include "Utility_BasicCylindricalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Convert the spatial coordinates to cartesian coordinates
/*! \details The original spatial coordinates are (r,theta,z).
 */
void BasicCylindricalSpatialCoordinateConversionPolicy::convertToCartesianSpatialCoordinates(
                                          const double primary_spatial_coord,
                                          const double secondary_spatial_coord,
                                          const double tertiary_spatial_coord,
                                          double& x_spatial_coord,
                                          double& y_spatial_coord,
                                          double& z_spatial_coord ) const
{
  this->convertToCartesianPosition( primary_spatial_coord,
                                    secondary_spatial_coord,
                                    tertiary_spatial_coord,
                                    x_spatial_coord,
                                    y_spatial_coord,
                                    z_spatial_coord );
}


// Convert the cartesian coordinates to the spatial coordinate system
/*! \details The final spatial coordinates are (r,theta,z)
 */
void BasicCylindricalSpatialCoordinateConversionPolicy::convertFromCartesianSpatialCoordinates(
                                         const double x_spatial_coord,
                                         const double y_spatial_coord,
                                         const double z_spatial_coord,
                                         double& primary_spatial_coord,
                                         double& secondary_spatial_coord,
                                         double& tertiary_spatial_coord ) const
{
  this->convertFromCartesianPosition( x_spatial_coord,
                                      y_spatial_coord,
                                      z_spatial_coord,
                                      primary_spatial_coord,
                                      secondary_spatial_coord,
                                      tertiary_spatial_coord );
}

EXPLICIT_CLASS_SERIALIZE_INST( BasicCylindricalSpatialCoordinateConversionPolicy );
  
} // end Utility namespace

BOOST_CLASS_EXPORT_IMPLEMENT( Utility::BasicCylindricalSpatialCoordinateConversionPolicy );

//---------------------------------------------------------------------------//
// end Utility_BasicCylindricalSpatialCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
