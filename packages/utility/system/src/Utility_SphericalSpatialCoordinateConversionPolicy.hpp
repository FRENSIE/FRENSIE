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

// FRENSIE Includes
#include "Utility_SpatialCoordinateConversionPolicy.hpp"
#include "Utility_SpatialCoordinateSystemTraits.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

//! The spherical spatial coordinate conversion policy class
class SphericalSpatialCoordinateConversionPolicy : public SpatialCoordinateConversionPolicy
{

protected:

  //! The local coordinate system traits
  typedef SpatialCoordinateSystemTraits<SPHERICAL_SPATIAL_COORDINATE_SYSTEM> LocalCSTraits;

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

  //! Get the local coordinate system type
  SpatialCoordinateSystemType getLocalSpatialCoordinateSystemType() const override;

  //! Check if the primary spatial coordinate is valid
  bool isPrimarySpatialCoordinateValid( const double coordinate ) const override;

  //! Check if the secondary spatial coordinate is valid
  bool isSecondarySpatialCoordinateValid( const double coordinate ) const override;

  //! Check if the tertiary spatial coordinate is valid
  bool isTertiarySpatialCoordinateValid( const double coordinate ) const override;

private:

  // Save the policy to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( SpatialCoordinateConversionPolicy );
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
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
  // Make sure that the x coordinate is valid
  testPrecondition( GlobalCSTraits::primarySpatialDimensionLowerBound() <=
                    x_spatial_coord );
  testPrecondition( GlobalCSTraits::primarySpatialDimensionUpperBound() >=
                    x_spatial_coord );
  // Make sure that the y coordinate is valid
  testPrecondition( GlobalCSTraits::secondarySpatialDimensionLowerBound() <=
                    y_spatial_coord );
  testPrecondition( GlobalCSTraits::secondarySpatialDimensionUpperBound() >=
                    y_spatial_coord );
  // Make sure that the z coordinate is valid
  testPrecondition( GlobalCSTraits::tertiarySpatialDimensionLowerBound() <=
                    z_spatial_coord );
  testPrecondition( GlobalCSTraits::tertiarySpatialDimensionUpperBound() >=
                    z_spatial_coord );

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
  if( r_spatial_coord > 0.0 )
    mu_spatial_coord = z_spatial_coord/r_spatial_coord;
  else
    mu_spatial_coord = 0.0;

  // Check for round-off error
  if( fabs( mu_spatial_coord ) > 1.0 )
    mu_spatial_coord = copysign( 1.0, mu_spatial_coord );

  // Make sure that the radius is valid
  testPostcondition( r_spatial_coord >= LocalCSTraits::primarySpatialDimensionLowerBound() );
  testPostcondition( r_spatial_coord <= LocalCSTraits::primarySpatialDimensionUpperBound() );
  // Make sure that the azimuthal angle is valid
  testPostcondition( theta_spatial_coord >= LocalCSTraits::secondarySpatialDimensionLowerBound() );
  testPostcondition( theta_spatial_coord <= LocalCSTraits::secondarySpatialDimensionUpperBound() );
  // Make sure that the polar angle cosine is valid
  testPostcondition( mu_spatial_coord >= LocalCSTraits::tertiarySpatialDimensionLowerBound() );
  testPostcondition( mu_spatial_coord <= LocalCSTraits::tertiarySpatialDimensionUpperBound() );
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
  testPrecondition( r_spatial_coord >= LocalCSTraits::primarySpatialDimensionLowerBound() );
  testPrecondition( r_spatial_coord <= LocalCSTraits::primarySpatialDimensionUpperBound() );
  // Make sure that the polar angle cosine is valid
  testPrecondition( mu_spatial_coord >= LocalCSTraits::tertiarySpatialDimensionLowerBound() );
  testPrecondition( mu_spatial_coord <= LocalCSTraits::tertiarySpatialDimensionUpperBound() );

  const double polar_angle_sine =
    sqrt( std::max(0.0, 1.0-mu_spatial_coord*mu_spatial_coord) );

  // Compute the x coordinate
  x_spatial_coord = r_spatial_coord*cos(theta_spatial_coord)*polar_angle_sine;

  // Compute the y coordinate
  y_spatial_coord = r_spatial_coord*sin(theta_spatial_coord)*polar_angle_sine;

  // Compute the z coordinate
  z_spatial_coord = r_spatial_coord*mu_spatial_coord;

  // Make sure that the x coordinate is valid
  testPostcondition( GlobalCSTraits::primarySpatialDimensionLowerBound() <=
                     x_spatial_coord );
  testPostcondition( GlobalCSTraits::primarySpatialDimensionUpperBound() >=
                     x_spatial_coord );
  // Make sure that the y coordinate is valid
  testPostcondition( GlobalCSTraits::secondarySpatialDimensionLowerBound() <=
                     y_spatial_coord );
  testPostcondition( GlobalCSTraits::secondarySpatialDimensionUpperBound() >=
                     y_spatial_coord );
  // Make sure that the z coordinate is valid
  testPostcondition( GlobalCSTraits::tertiarySpatialDimensionLowerBound() <=
                     z_spatial_coord );
  testPostcondition( GlobalCSTraits::tertiarySpatialDimensionUpperBound() >=
                     z_spatial_coord );
}

// Get the local coordinate system type
inline SpatialCoordinateSystemType SphericalSpatialCoordinateConversionPolicy::getLocalSpatialCoordinateSystemType() const
{
  return SPHERICAL_SPATIAL_COORDINATE_SYSTEM;
}

// Check if the primary spatial coordinate is valid
inline bool SphericalSpatialCoordinateConversionPolicy::isPrimarySpatialCoordinateValid(
                                                const double coordinate ) const
{
  return coordinate >= LocalCSTraits::primarySpatialDimensionLowerBound() &&
    coordinate <= LocalCSTraits::primarySpatialDimensionUpperBound();
}

// Check if the secondary spatial coordinate is valid
inline bool SphericalSpatialCoordinateConversionPolicy::isSecondarySpatialCoordinateValid(
                                                const double coordinate ) const
{
  return coordinate >= LocalCSTraits::secondarySpatialDimensionLowerBound() &&
    coordinate <= LocalCSTraits::secondarySpatialDimensionUpperBound();
}

// Check if the tertiary spatial coordinate is valid
inline bool SphericalSpatialCoordinateConversionPolicy::isTertiarySpatialCoordinateValid(
                                                const double coordinate ) const
{
  return coordinate >= LocalCSTraits::tertiarySpatialDimensionLowerBound() &&
    coordinate <= LocalCSTraits::tertiarySpatialDimensionUpperBound();
}

} // end Utility namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( SphericalSpatialCoordinateConversionPolicy, Utility );
BOOST_SERIALIZATION_CLASS_VERSION( SphericalSpatialCoordinateConversionPolicy, Utility, 0 );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( Utility, SphericalSpatialCoordinateConversionPolicy );

#endif // end UTILITY_SPHERICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_SphericalSpatialCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
