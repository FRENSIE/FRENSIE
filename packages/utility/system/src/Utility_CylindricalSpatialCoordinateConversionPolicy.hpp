//---------------------------------------------------------------------------//
//!
//! \file   Utility_CylindricalSpatialCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Cylindrical coordinate conversion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_CYLINDRICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_CYLINDRICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

// Std Lib Includes
#include <cmath>

// FRENSIE Includes
#include "Utility_SpatialCoordinateConversionPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

//! The cylindrical spatial coordinate conversion policy class
class CylindricalSpatialCoordinateConversionPolicy : public SpatialCoordinateConversionPolicy
{

protected:

  //! The local coordinate system traits
  typedef SpatialCoordinateSystemTraits<CYLINDRICAL_SPATIAL_COORDINATE_SYSTEM> LocalCSTraits;

public:

  //! Convert the Cartesian coordinates to cylindrical coordinates
  static void convertFromCartesianPosition( const double cartesian_coords[3],
                                            double cylindrical_coords[3] );

  //! Convert the Cartesian coordinates to cylindrical coordinates
  static void convertFromCartesianPosition( const double x_spatial_coord,
                                            const double y_spatial_coord,
                                            const double z_spatial_coord_in,
                                            double& r_spatial_coord,
                                            double& theta_spatial_coord,
                                            double& z_spatial_coord_out );

  //! Convert the cylindrical coordinates to Cartesian coordinates
  static void convertToCartesianPosition( const double cylindrical_coords[3],
                                          double cartesian_coords[3] );

  //! Convert the cylindrical coordinates to Cartesian coordinates
  static void convertToCartesianPosition( const double r_spatial_coord,
                                          const double theta_spatial_coord,
                                          const double z_spatial_coord_in,
                                          double& x_spatial_coord,
                                          double& y_spatial_coord,
                                          double& z_spatial_coord_out );

  //! Constructor
  CylindricalSpatialCoordinateConversionPolicy()
  { /* ... */ }

  //! Destructor
  virtual ~CylindricalSpatialCoordinateConversionPolicy()
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

// Convert the cartesian coordinates to cylindrical coordinates
inline void CylindricalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                              const double cartesian_coords[3],
                                              double cylindrical_coords[3] )
{
  CylindricalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                                       cartesian_coords[0],
                                                       cartesian_coords[1],
                                                       cartesian_coords[2],
                                                       cylindrical_coords[0],
                                                       cylindrical_coords[1],
                                                       cylindrical_coords[2] );
}

// Convert the cartesian coordinates to cylindrical coordinates
inline void CylindricalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                               const double x_spatial_coord,
                                               const double y_spatial_coord,
                                               const double z_spatial_coord_in,
                                               double& r_spatial_coord,
                                               double& theta_spatial_coord,
                                               double& z_spatial_coord_out )
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
                    z_spatial_coord_in );
  testPrecondition( GlobalCSTraits::tertiarySpatialDimensionUpperBound() >=
                    z_spatial_coord_in );

  // Compute the radius
  r_spatial_coord = sqrt( x_spatial_coord*x_spatial_coord +
                          y_spatial_coord*y_spatial_coord );

  // Compute the azimuthal angle
  theta_spatial_coord = atan2( y_spatial_coord, x_spatial_coord );

  // Shift the azimuthal angle to the range [0.0, 2*Pi]
  if( theta_spatial_coord < 0.0 )
    theta_spatial_coord += 2*Utility::PhysicalConstants::pi;

  // The z coordinate is the same
  z_spatial_coord_out = z_spatial_coord_in;

  // Make sure that the radius is valid
  testPostcondition( r_spatial_coord >= LocalCSTraits::primarySpatialDimensionLowerBound() );
  testPostcondition( r_spatial_coord <= LocalCSTraits::primarySpatialDimensionUpperBound() );
  // Make sure that the azimuthal angle is valid
  testPostcondition( theta_spatial_coord >= LocalCSTraits::secondarySpatialDimensionLowerBound() );
  testPostcondition( theta_spatial_coord <= LocalCSTraits::secondarySpatialDimensionUpperBound() );
}

// Convert the cylindrical coordinates to cartesian coordinates
inline void CylindricalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                            const double cylindrical_coords[3],
                                            double cartesian_coords[3] )
{
  CylindricalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                                         cylindrical_coords[0],
                                                         cylindrical_coords[1],
                                                         cylindrical_coords[2],
                                                         cartesian_coords[0],
                                                         cartesian_coords[1],
                                                         cartesian_coords[2] );
}

// Convert the cylindrical coordinates to cartesian coordinates
inline void CylindricalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                              const double r_spatial_coord,
                                              const double theta_spatial_coord,
                                              const double z_spatial_coord_in,
                                              double& x_spatial_coord,
                                              double& y_spatial_coord,
                                              double& z_spatial_coord_out )
{
  // Make sure that the radius is valid
  testPrecondition( r_spatial_coord >= LocalCSTraits::primarySpatialDimensionLowerBound() );
  testPrecondition( r_spatial_coord <= LocalCSTraits::primarySpatialDimensionUpperBound() );
  // Make sure that the z coordinate is valid
  testPrecondition( z_spatial_coord_in >= LocalCSTraits::tertiarySpatialDimensionLowerBound() );
  testPrecondition( z_spatial_coord_in <= LocalCSTraits::tertiarySpatialDimensionUpperBound() );

  // Compute the x coordinate
  x_spatial_coord = r_spatial_coord*cos(theta_spatial_coord);

  // Compute the y coordinate
  y_spatial_coord = r_spatial_coord*sin(theta_spatial_coord);

  // The z coordinate is the same
  z_spatial_coord_out = z_spatial_coord_in;

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
                     z_spatial_coord_out );
  testPostcondition( GlobalCSTraits::tertiarySpatialDimensionUpperBound() >=
                     z_spatial_coord_out );
}

// Get the local coordinate system type
inline SpatialCoordinateSystemType CylindricalSpatialCoordinateConversionPolicy::getLocalSpatialCoordinateSystemType() const
{
  return CYLINDRICAL_SPATIAL_COORDINATE_SYSTEM;
}

// Check if the primary spatial coordinate is valid
inline bool CylindricalSpatialCoordinateConversionPolicy::isPrimarySpatialCoordinateValid(
                                                const double coordinate ) const
{
  return coordinate >= LocalCSTraits::primarySpatialDimensionLowerBound() &&
    coordinate <= LocalCSTraits::primarySpatialDimensionUpperBound();
}

// Check if the secondary spatial coordinate is valid
inline bool CylindricalSpatialCoordinateConversionPolicy::isSecondarySpatialCoordinateValid(
                                                const double coordinate ) const
{
  return coordinate >= LocalCSTraits::secondarySpatialDimensionLowerBound() &&
    coordinate <= LocalCSTraits::secondarySpatialDimensionUpperBound();
}

// Check if the tertiary spatial coordinate is valid
inline bool CylindricalSpatialCoordinateConversionPolicy::isTertiarySpatialCoordinateValid(
                                                const double coordinate ) const
{
  return coordinate >= LocalCSTraits::tertiarySpatialDimensionLowerBound() &&
    coordinate <= LocalCSTraits::tertiarySpatialDimensionUpperBound();
}

} // end Utility namespace

BOOST_SERIALIZATION_CLASS_VERSION( CylindricalSpatialCoordinateConversionPolicy, Utility, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( CylindricalSpatialCoordinateConversionPolicy, Utility );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( Utility, CylindricalSpatialCoordinateConversionPolicy );

#endif // end UTILITY_CYLINDRICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_CylindricalSpatialCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
