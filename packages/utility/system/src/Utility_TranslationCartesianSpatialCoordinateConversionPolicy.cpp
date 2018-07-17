//---------------------------------------------------------------------------//
//!
//! \file   Utility_TranslationCartesianSpatialCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Translation Cartesian spatial coordinate conversion policy def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Utility_TranslationCartesianSpatialCoordinateConversionPolicy.hpp"

namespace Utility{

// Constructor
/*! \details The origin is the origin of the local coordinate system w.r.t. the
 * global coordinate system.
 */
TranslationCartesianSpatialCoordinateConversionPolicy::TranslationCartesianSpatialCoordinateConversionPolicy(
                                                       const double origin[3] )
  : d_origin{ origin[0], origin[1], origin[2] }
{ /* ... */ }

// Convert the spatial coordinates to cartesian coordinates
/*! \details The primary, secondary and tertiary spatial coordinates are the
 * Cartesian coordinates in the local coordinate system. They will be converted
 * to coordinates in the global coordinate system.
 */
void TranslationCartesianSpatialCoordinateConversionPolicy::convertToCartesianSpatialCoordinates(
                                          const double primary_spatial_coord,
                                          const double secondary_spatial_coord,
                                          const double tertiary_spatial_coord,
                                          double& x_spatial_coord,
                                          double& y_spatial_coord,
                                          double& z_spatial_coord ) const
{
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
void TranslationCartesianSpatialCoordinateConversionPolicy::convertFromCartesianSpatialCoordinates(
                                         const double x_spatial_coord,
                                         const double y_spatial_coord,
                                         const double z_spatial_coord,
                                         double& primary_spatial_coord,
                                         double& secondary_spatial_coord,
                                         double& tertiary_spatial_coord ) const
{
  this->translateGlobalCartesianPositionToLocalCartesianPosition(
                                                      x_spatial_coord,
                                                      y_spatial_coord,
                                                      z_spatial_coord,
                                                      d_origin,
                                                      primary_spatial_coord,
                                                      secondary_spatial_coord,
                                                      tertiary_spatial_coord );
}

EXPLICIT_CLASS_SAVE_LOAD_INST( TranslationCartesianSpatialCoordinateConversionPolicy );
  
} // end Utility namespace

BOOST_CLASS_EXPORT_IMPLEMENT( Utility::TranslationCartesianSpatialCoordinateConversionPolicy );

//---------------------------------------------------------------------------//
// end Utility_TranslationCartesianSpatialCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
