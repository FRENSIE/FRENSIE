//---------------------------------------------------------------------------//
//!
//! \file   Utility_BasicSphericalCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Basic spherical coordinate conversion policy declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Utility_BasicSphericalCoordinateConversionPolicy.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Convert the spatial coordinates to cartesian coordinates
/*! \details The original spatial coordinates are (r,theta,mu). Mu is the polar
 * angle cosine while theta is the azimuthal angle.
 */
void BasicSphericalCoordinateConversionPolicy::convertToCartesianSpatialCoordinates(
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

  this->convertToCartesianPosition( primary_spatial_coord,
                                    secondary_spatial_coord,
                                    tertiary_spatial_coord,
                                    x_spatial_coord,
                                    y_spatial_coord,
                                    z_spatial_coord );
}

// Convert the cartesian coordinates to the spatial coordinate system
void BasicSphericalCoordinateConversionPolicy::convertFromCartesianSpatialCoordinates(
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
/*! \details The original directional coordinates are (1.0,theta,mu). The
 * primary directional coordinate will be ignored since a direction will always
 * lie on the unit sphere. Mu is the polar angle cosine while theta is the 
 * azimuthal angle.
 */
void BasicSphericalCoordinateConversionPolicy::convertToCartesianDirectionalCoordinates(
                                      const double,
                                      const double secondary_directional_coord,
                                      const double tertiary_directional_coord,
                                      double& x_directional_coord,
                                      double& y_directional_coord,
                                      double& z_directional_coord ) const
{
  // Make sure that the mu spatial coordinate is valid
  testPrecondition( tertiary_directional_coord >= -1.0 );
  testPrecondition( tertiary_directional_coord <= 1.0 );

  this->convertToCartesianDirection( 1.0,
                                     secondary_directional_coord,
                                     tertiary_directional_coord,
                                     x_directional_coord,
                                     y_directional_coord,
                                     z_directional_coord );
}

// Convert the cartesian coordinates to the directional coordinate system
/*! \details The final directional coordinates are (1.0,theta,mu). The
 * primary directional coordinate will will always be 1.0 since a direction 
 * will always lie on the unit sphere. Mu is the polar angle cosine while theta
 * is the azimuthal angle.
 */
void BasicSphericalCoordinateConversionPolicy::convertFromCartesianDirectionalCoordinates(
                                     const double x_directional_coord,
                                     const double y_directional_coord,
                                     const double z_directional_coord,
                                     double& primary_directional_coord,
                                     double& secondary_directional_coord,
                                     double& tertiary_directional_coord ) const
{
  // Make sure that the Cartesian coordinates are valid
  testPrecondition( isUnitVector( x_directional_coord, y_directional_coord, z_directional_coord ) );
  
  this->convertFromCartesianDirection( x_directional_coord,
                                       y_directional_coord,
                                       z_directional_coord,
                                       primary_directional_coord,
                                       secondary_directional_coord,
                                       tertiary_directional_coord );
}

EXPLICIT_CLASS_SERIALIZE_INST( BasicSphericalCoordinateConversionPolicy );
  
} // end Utility namespace

BOOST_CLASS_EXPORT_IMPLEMENT( Utility::BasicSphericalCoordinateConversionPolicy );

//---------------------------------------------------------------------------//
// end Utility_BasicSphericalCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
