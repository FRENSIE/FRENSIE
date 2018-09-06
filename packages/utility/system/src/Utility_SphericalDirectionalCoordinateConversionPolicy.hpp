//---------------------------------------------------------------------------//
//!
//! \file   Utility_SphericalDirectionalCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Spherical directional coordinate conversion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SPHERICAL_DIRECTIONAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_SPHERICAL_DIRECTIONAL_COORDINATE_CONVERSION_POLICY_HPP

// Std Lib Includes
#include <cmath>

// FRENSIE Includes
#include "Utility_DirectionalCoordinateConversionPolicy.hpp"
#include "Utility_DirectionalCoordinateSystemTraits.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

//! The spherical directional coordinate conversion policy class
class SphericalDirectionalCoordinateConversionPolicy : public DirectionalCoordinateConversionPolicy
{

protected:

  //! The local coordinate system traits
  typedef DirectionalCoordinateSystemTraits<SPHERICAL_DIRECTIONAL_COORDINATE_SYSTEM> LocalCSTraits;

public:

  //! Convert the Cartesian direction to spherical coords (on unit sphere)
  static void convertFromCartesianDirection(
                                           const double cartesian_direction[3],
                                           double spherical_coords[3] );

  //! Convert the Cartesian direction to spherical coords (on unit sphere)
  static void convertFromCartesianDirection( const double x_direction,
                                             const double y_direction,
                                             const double z_direction,
                                             double& r_directional_coord,
                                             double& theta_directional_coord,
                                             double& mu_directional_coord );

  //! Convert the spherical coords (on unit sphere) to a Cartesian direction
  static void convertToCartesianDirection( const double spherical_coords[3],
                                           double cartesian_direction[3] );

  //! Convert the spherical coords (on unit sphere) to a Cartesian direction
  static void convertToCartesianDirection(
                                          const double,
                                          const double theta_directional_coord,
                                          const double mu_directional_coord,
                                          double& x_direction,
                                          double& y_direction,
                                          double& z_direction );

  //! Constructor
  SphericalDirectionalCoordinateConversionPolicy()
  { /* ... */ }

  //! Destructor
  virtual ~SphericalDirectionalCoordinateConversionPolicy()
  { /* ... */ }

  //! Get the local coordinate system type
  DirectionalCoordinateSystemType getLocalDirectionalCoordinateSystemType() const override;

  //! Check if the primary directional coordinate is valid
  bool isPrimaryDirectionalCoordinateValid( const double coordinate ) const override;

  //! Check if the secondary directional coordinate is valid
  bool isSecondaryDirectionalCoordinateValid( const double coordinate ) const override;

  //! Check if the tertiary directional coordinate is valid
  bool isTertiaryDirectionalCoordinateValid( const double coordinate ) const override;

  //! Normalize the local directional coordinates
  void normalizeLocalDirectionalCoordinates(
                           double& primary_directional_coord,
                           double& secondary_directional_coord,
                           double& tertiary_directional_coord ) const override;

private:

  // Save the policy to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( DirectionalCoordinateConversionPolicy );
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

//---------------------------------------------------------------------------//
// Inline Definitions
//---------------------------------------------------------------------------//

// Convert the Cartesian direction to spherical coords (on unit sphere)
/*! \details The spherical coordinates are (r,theta,mu) where theta is
 * the azimuthal angle and mu is the polar angle cosine.
 */
inline void SphericalDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
                                           const double cartesian_direction[3],
                                           double spherical_coords[3] )
{
  // Make sure that the direction is valid
  testPrecondition( isUnitVector( cartesian_direction ) );

  SphericalDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
                                                        cartesian_direction[0],
                                                        cartesian_direction[1],
                                                        cartesian_direction[2],
                                                        spherical_coords[0],
                                                        spherical_coords[1],
                                                        spherical_coords[2] );


}

// Convert the Cartesian direction to spherical coords (on unit sphere)
/*! \details The spherical coordinates are (1.0,theta,mu) where theta is
 * the azimuthal angle and mu is the polar angle cosine.
 */
inline void SphericalDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
                                               const double x_direction,
                                               const double y_direction,
                                               const double z_direction,
                                               double& r_directional_coord,
                                               double& theta_directional_coord,
                                               double& mu_directional_coord )
{
  // Make sure that the direction is valid
  testPrecondition( isUnitVector( x_direction, y_direction, z_direction ) );

  // Compute the azimuthal angle
  theta_directional_coord = atan2( y_direction, x_direction );

  // Shift the azimuthal angle to the range [0.0, 2*Pi]
  if( theta_directional_coord < 0.0 )
    theta_directional_coord += 2*Utility::PhysicalConstants::pi;

  // Compute the polar angle cosine
  mu_directional_coord = z_direction;

  // Check for round-off error
  if( fabs( mu_directional_coord ) > 1.0 )
    mu_directional_coord = copysign( 1.0, mu_directional_coord );

  // The radial component should always be 1.0 (set this to avoid rounding
  // errors).
  r_directional_coord = 1.0;

  // Make sure that the azimuthal angle is valid
  testPostcondition( theta_directional_coord >= LocalCSTraits::secondaryDirectionalDimensionLowerBound() );
  testPostcondition( theta_directional_coord <= LocalCSTraits::secondaryDirectionalDimensionUpperBound() );

  // Make sure that the polar angle cosine is valid
  testPostcondition( mu_directional_coord >= LocalCSTraits::tertiaryDirectionalDimensionLowerBound() );
  testPostcondition( mu_directional_coord <= LocalCSTraits::tertiaryDirectionalDimensionUpperBound() );
}

// Convert the spherical coords (on unit sphere) to a Cartesian direction
/*! \details The spherical coordinates are (1.0,theta,mu) where theta is
 * the azimuthal angle and mu is the polar angle cosine. The radial component
 * (spherical_coords[0]) will be ignored.
 */
inline void SphericalDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
                                              const double spherical_coords[3],
                                              double cartesian_direction[3] )
{
  SphericalDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
                                                      spherical_coords[0],
                                                      spherical_coords[1],
                                                      spherical_coords[2],
                                                      cartesian_direction[0],
                                                      cartesian_direction[1],
                                                      cartesian_direction[2] );
}

// Convert the spherical coords (on unit sphere) to a Cartesian direction
/*! \details The spherical coordinates are (1.0,theta,mu) where theta is
 * the azimuthal angle and mu is the polar angle cosine. The radial component
 * will be ignored since it must always be 1.0.
 */
inline void SphericalDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
                                          const double,
                                          const double theta_directional_coord,
                                          const double mu_directional_coord,
                                          double& x_direction,
                                          double& y_direction,
                                          double& z_direction )
{
  // Make sure that the polar angle cosine is valid
  testPrecondition( mu_directional_coord >= LocalCSTraits::tertiaryDirectionalDimensionLowerBound() );
  testPrecondition( mu_directional_coord <= LocalCSTraits::tertiaryDirectionalDimensionUpperBound() );

  const double polar_angle_sine =
    sqrt( std::max(0.0, 1.0-mu_directional_coord*mu_directional_coord) );

  // Compute the x direction
  x_direction = cos(theta_directional_coord)*polar_angle_sine;

  // Compute the y direction
  y_direction = sin(theta_directional_coord)*polar_angle_sine;

  // Compute the z direction
  z_direction = mu_directional_coord;

  // Normalize the Cartesian direction to eliminate rounding errors
  normalizeVector( x_direction, y_direction, z_direction );

  // Make sure that the direction is a unit vector
  testPostcondition( isUnitVector( x_direction, y_direction, z_direction ) );
}

// Get the local coordinate system type
inline DirectionalCoordinateSystemType SphericalDirectionalCoordinateConversionPolicy::getLocalDirectionalCoordinateSystemType() const
{
  return SPHERICAL_DIRECTIONAL_COORDINATE_SYSTEM;
}

// Check if the primary directional coordinate is valid
inline bool SphericalDirectionalCoordinateConversionPolicy::isPrimaryDirectionalCoordinateValid(
                                                const double coordinate ) const
{
  return coordinate >= LocalCSTraits::primaryDirectionalDimensionLowerBound() &&
    coordinate <= LocalCSTraits::primaryDirectionalDimensionUpperBound();
}

// Check if the secondary directional coordinate is valid
inline bool SphericalDirectionalCoordinateConversionPolicy::isSecondaryDirectionalCoordinateValid(
                                                const double coordinate ) const
{
  return coordinate >= LocalCSTraits::secondaryDirectionalDimensionLowerBound() &&
    coordinate <= LocalCSTraits::secondaryDirectionalDimensionUpperBound();
}

// Check if the tertiary directional coordinate is valid
inline bool SphericalDirectionalCoordinateConversionPolicy::isTertiaryDirectionalCoordinateValid(
                                                const double coordinate ) const
{
  return coordinate >= LocalCSTraits::tertiaryDirectionalDimensionLowerBound() &&
    coordinate <= LocalCSTraits::tertiaryDirectionalDimensionUpperBound();
}

// Normalize the local directional coordinates
inline void SphericalDirectionalCoordinateConversionPolicy::normalizeLocalDirectionalCoordinates(
                                     double& primary_directional_coord,
                                     double& secondary_directional_coord,
                                     double& tertiary_directional_coord ) const
{
  primary_directional_coord = 1.0;
}

} // end Utility namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( SphericalDirectionalCoordinateConversionPolicy, Utility );
BOOST_SERIALIZATION_CLASS_VERSION( SphericalDirectionalCoordinateConversionPolicy, Utility, 0 );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( Utility, SphericalDirectionalCoordinateConversionPolicy );

#endif // end UTILITY_SPHERICAL_DIRECTIONAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_SphericalDirectionalCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
