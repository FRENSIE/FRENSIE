//---------------------------------------------------------------------------//
//!
//! \file   Utility_GeneralSphericalCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  General spherical coordinate conversion policy definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_GeneralSphericalCoordinateConversionPolicy.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
GeneralSphericalCoordinateConversionPolicy::GeneralSphericalCoordinateConversionPolicy(
                                                        const double origin[3],
                                                        const double axis[3] )
  : d_origin{origin[0], origin[1], origin[2]},
    d_axis{axis[0], axis[1], axis[2]}
{
  // Normalize the axis vector
  normalizeVector( d_axis );
}

// Constructor (global origin)
GeneralSphericalCoordinateConversionPolicy::GeneralSphericalCoordinateConversionPolicy( const double axis[3] )
  : d_origin{0.0, 0.0, 0.0},
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
void GeneralSphericalCoordinateConversionPolicy::convertToCartesianSpatialCoordinates(
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
}

// Convert the cartesian coordinates to the spatial coordinate system
/*! \details The final spatial coordinates are (r,theta,mu). Mu is the polar
 * angle cosine w.r.t. the axis vector while theta is the azimuthal angle 
 * w.r.t. the axis vector.
 */
void GeneralSphericalCoordinateConversionPolicy::convertFromCartesianSpatialCoordinates(
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

  // Convert the local cartesian coordinates to spherical coordinates
  this->convertFromCartesianPosition( local_x_spatial_coord,
                                      local_y_spatial_coord,
                                      local_z_spatial_coord,
                                      primary_spatial_coord,
                                      secondary_spatial_coord,
                                      tertiary_spatial_coord );
}

// Convert the directional coordinates to cartesian coordinates
/*! \details The original directional coordinates are (1.0,theta,mu). The
 * primary directional coordinate will be ignored since a direction will always
 * lie on the unit sphere. Mu is the polar angle cosine w.r.t. the axis vector 
 * while theta is the azimuthal angle w.r.t. the axis vector. Note that the
 * origin of the local coordinate system is not used when transforming 
 * directional coordinates.
 */
void GeneralSphericalCoordinateConversionPolicy::convertToCartesianDirectionalCoordinates(
                                      const double primary_directional_coord,
                                      const double secondary_directional_coord,
                                      const double tertiary_directional_coord,
                                      double& x_directional_coord,
                                      double& y_directional_coord,
                                      double& z_directional_coord ) const
{
  // Make sure that the mu directional coordinate is valid
  testPrecondition( tertiary_directional_coord >= -1.0 );
  testPrecondition( tertiary_directional_coord <= 1.0 );

  // Convert the spherical coordinates to local cartesian coordinates
  double local_x_directional_coord, local_y_directional_coord,
    local_z_directional_coord;

  this->convertToCartesianDirection( 1.0,
                                     secondary_directional_coord,
                                     tertiary_directional_coord,
                                     local_x_directional_coord,
                                     local_y_directional_coord,
                                     local_z_directional_coord );
  
  // Convert the local cartesian coordinates to global cartesian coordinates
  convertLocalVectorToGlobalVector( local_x_directional_coord,
                                    local_y_directional_coord,
                                    local_z_directional_coord,
                                    d_axis,
                                    x_directional_coord,
                                    y_directional_coord,
                                    z_directional_coord );
}

// Convert the cartesian coordinates to the directional coordinate system
/*! \details The final directional coordinates are (1.0,theta,mu). The
 * primary directional coordinate will will always be 1.0 since a direction 
 * will always lie on the unit sphere. Mu is the polar angle cosine w.r.t. the 
 * axis vector while theta is the azimuthal angle w.r.t. the axis vector.
 * Note that the origin of the local coordinate system is not used when 
 * transforming directional coordinates.
 */
void GeneralSphericalCoordinateConversionPolicy::convertFromCartesianDirectionalCoordinates(
                                     const double x_directional_coord,
                                     const double y_directional_coord,
                                     const double z_directional_coord,
                                     double& primary_directional_coord,
                                     double& secondary_directional_coord,
                                     double& tertiary_directional_coord ) const
{
  // Make sure that the Cartesian directional coordinates are valid
  testPrecondition( isUnitVector( x_directional_coord, y_directional_coord, z_directional_coord ) );

  // Convert the global cartesian coordinates to local cartesian coordinates
  double local_x_directional_coord, local_y_directional_coord,
    local_z_directional_coord;

  convertGlobalVectorToLocalVector( x_directional_coord,
                                    y_directional_coord,
                                    z_directional_coord,
                                    d_axis,
                                    local_x_directional_coord,
                                    local_y_directional_coord,
                                    local_z_directional_coord );

  // Convert the local cartesian coordinates to spherical coordinates
  this->convertFromCartesianDirection( local_x_directional_coord,
                                       local_y_directional_coord,
                                       local_z_directional_coord,
                                       primary_directional_coord,
                                       secondary_directional_coord,
                                       tertiary_directional_coord );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_GeneralSphericalCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
