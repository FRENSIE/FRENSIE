//---------------------------------------------------------------------------//
//!
//! \file   Utility_BasicCartesianCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Basic Cartesian coordinate conversion policy definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Convert the spatial coordinates to cartesian coordinates
/*! \details This method will simply copy the input coordinates to the output
 * coordinates.
 */
void BasicCartesianCoordinateConversionPolicy::convertToCartesianSpatialCoordinates(
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
/*! \details This method will simply copy the input coordinates to the output
 * coordinates.
 */
void BasicCartesianCoordinateConversionPolicy::convertFromCartesianSpatialCoordinates(
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

// Convert the directional coordinates to cartesian coordinates
/*! \details This method will simply copy the input direction to the output
 * direction.
 */
void BasicCartesianCoordinateConversionPolicy::convertToCartesianDirectionalCoordinates(
                                      const double primary_directional_coord,
                                      const double secondary_directional_coord,
                                      const double tertiary_directional_coord,
                                      double& x_directional_coord,
                                      double& y_directional_coord,
                                      double& z_directional_coord ) const
{
  // Make sure that the input direction is valid
  testPrecondition( isUnitVector( primary_directional_coord, secondary_directional_coord, tertiary_directional_coord ) );

  this->convertToCartesianDirection( primary_directional_coord,
                                     secondary_directional_coord,
                                     tertiary_directional_coord,
                                     x_directional_coord,
                                     y_directional_coord,
                                     z_directional_coord );
}

// Convert the cartesian coordinates to the directional coordinate system
/*! \details This method will simply copy the input direction to the output
 * direction.
 */
void BasicCartesianCoordinateConversionPolicy::convertFromCartesianDirectionalCoordinates(
                                     const double x_directional_coord,
                                     const double y_directional_coord,
                                     const double z_directional_coord,
                                     double& primary_directional_coord,
                                     double& secondary_directional_coord,
                                     double& tertiary_directional_coord ) const
{
  // Make sure that the input direction is valid
  testPrecondition( isUnitVector( x_directional_coord, y_directional_coord, z_directional_coord ) );

  this->convertFromCartesianDirection( x_directional_coord,
                                       y_directional_coord,
                                       z_directional_coord,
                                       primary_directional_coord,
                                       secondary_directional_coord,
                                       tertiary_directional_coord );
}

EXPLICIT_CLASS_SERIALIZE_INST( BasicCartesianCoordinateConversionPolicy );
  
} // end Utility namespace

BOOST_CLASS_EXPORT_IMPLEMENT( Utility::BasicCartesianCoordinateConversionPolicy );

//---------------------------------------------------------------------------//
// end Utility_BasicCartesianCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
