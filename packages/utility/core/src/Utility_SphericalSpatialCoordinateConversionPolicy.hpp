//---------------------------------------------------------------------------//
//!
//! \file   Utility_SphericalSpatialCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Spherical spatial coordinate conversion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SPHERICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_SPHERICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

// Std Lib Includes
#include <cmath>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_SpatialCoordinateConversionPolicy.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

//! The spherical spatial coordinate conversion policy class
class SphericalSpatialCoordinateConversionPolicy : public SpatialCoordinateConversionPolicy
{

public:
  
  //! Convert the Cartesian coordinates to spherical coordinates
  static void convertFromCartesianPosition( const double cartesian_coords[3],
                                            double spherical_coords[3] );

  //! Convert the Cartesian coordinates to spherical coordinates
  static void convertFromCartesianPosition( const double x_spatial_coord,
                                            const double y_spatial_coord,
                                            const double z_spatial_coord,
                                            double& r_spatial_coord,
                                            double& theta_spatial_coord,
                                            double& mu_spatial_coord );

  //! Convert the spherical coordinates to Cartesian coordinates
  static void convertToCartesianPosition( const double spherical_coords[3],
                                          double cartesian_coords[3] );

  //! Convert the spherical coordinates to Cartesian coordinates
  static void convertToCartesianPosition( const double r_spatial_coord,
                                          const double theta_spatial_coord,
                                          const double mu_spatial_coord,
                                          double& x_spatial_coord,
                                          double& y_spatial_coord,
                                          double& z_spatial_coord );

  //! Constructor
  SphericalSpatialCoordinateConversionPolicy()
  { /* ... */ }

  //! Destructor
  virtual ~SphericalSpatialCoordinateConversionPolicy()
  { /* ... */ }
};

//---------------------------------------------------------------------------//
// Inline Definitions
//---------------------------------------------------------------------------//

// Convert the Cartesian coordinates to spherical coordinates
/*! \details The spherical coordinates are (r,theta,mu) where theta is 
 * the azimuthal angle and mu is the polar angle cosine.
 */
inline void SphericalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                              const double cartesian_coords[3],
                                              double spherical_coords[3] )
{
  SphericalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                                         cartesian_coords[0],
                                                         cartesian_coords[1],
                                                         cartesian_coords[2],
                                                         spherical_coords[0],
                                                         spherical_coords[1],
                                                         spherical_coords[2] );
}

// Convert the Cartesian coordinates to spherical coordinates
/*! \details Mu is the polar angle cosine. Theta is the azimuthal angle.
 */
inline void SphericalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                                  const double x_spatial_coord,
                                                  const double y_spatial_coord,
                                                  const double z_spatial_coord,
                                                  double& r_spatial_coord,
                                                  double& theta_spatial_coord,
                                                  double& mu_spatial_coord )
{
  // Compute the radius
  r_spatial_coord = sqrt( x_spatial_coord*x_spatial_coord +
                          y_spatial_coord*y_spatial_coord +
                          z_spatial_coord*z_spatial_coord );

  // Compute the azimuthal angle
  theta_spatial_coord = atan2( y_spatial_coord, x_spatial_coord );

  // Shift the azimuthal angle to the range [0.0, 2*Pi]
  if( theta_spatial_coord < 0.0 )
    theta_spatial_coord += 2*Utility::PhysicalConstants::pi;
  
  // Compute the polar angle cosine
  mu_spatial_coord = z_spatial_coord/r_spatial_coord;

  // Check for round-off error
  if( Teuchos::ScalarTraits<double>::magnitude( mu_spatial_coord ) > 1.0 )
    mu_spatial_coord = copysign( 1.0, mu_spatial_coord );

  // Make sure that the radius is valid
  testPostcondition( r_spatial_coord >= 0.0 );
  // Make sure that the azimuthal angle is valid
  testPostcondition( theta_spatial_coord >= 0.0 );
  testPostcondition( theta_spatial_coord <= 2*Utility::PhysicalConstants::pi );
  // Make sure that the polar angle cosine is valid
  testPostcondition( mu_spatial_coord >= -1.0 );
  testPostcondition( mu_spatial_coord <= 1.0 );
}

// Convert the spherical coordinates to Cartesian coordinates
/*! \details The spherical coordinates are (r,theta,mu) where theta is 
 * the azimuthal angle and mu is the polar angle cosine.
 */
inline void SphericalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              const double spherical_coords[3],
                                              double cartesian_coords[3] )
{
  SphericalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                                         spherical_coords[0],
                                                         spherical_coords[1],
                                                         spherical_coords[2],
                                                         cartesian_coords[0],
                                                         cartesian_coords[1],
                                                         cartesian_coords[2] );
}

// Convert the spherical coordinates to Cartesian coordinates
/*! \details Mu is the polar angle cosine. Theta is the azimuthal angle.
 */
inline void SphericalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              const double r_spatial_coord,
                                              const double theta_spatial_coord,
                                              const double mu_spatial_coord,
                                              double& x_spatial_coord,
                                              double& y_spatial_coord,
                                              double& z_spatial_coord )
{
  // Make sure that the radius is valid
  testPrecondition( r_spatial_coord >= 0.0 );
  // Make sure that the polar angle cosine is valid
  testPrecondition( mu_spatial_coord >= -1.0 );
  testPrecondition( mu_spatial_coord <= 1.0 );
  
  const double polar_angle_sine =
    sqrt( std::max(0.0, 1.0-mu_spatial_coord*mu_spatial_coord) );
  
  // Compute the x coordinate
  x_spatial_coord = r_spatial_coord*cos(theta_spatial_coord)*polar_angle_sine;

  // Compute the y coordinate
  y_spatial_coord = r_spatial_coord*sin(theta_spatial_coord)*polar_angle_sine;

  // Compute the z coordinate
  z_spatial_coord = r_spatial_coord*mu_spatial_coord;
}
  
} // end Utility namespace

#endif // end UTILITY_SPHERICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_SphericalSpatialCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
