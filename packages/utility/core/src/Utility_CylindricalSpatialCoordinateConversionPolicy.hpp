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

namespace Utility{

//! The cylindrical spatial coordinate conversion policy class
class CylindricalSpatialCoordinateConversionPolicy : public SpatialCoordinateConversionPolicy
{

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
};

//---------------------------------------------------------------------------//
// Inline Definitions
//---------------------------------------------------------------------------//

// Convert the cartesian coordinates to cylindrical coordinates
inline void CylindricalSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                              const double cartesian_coords[3],
                                              double cylindrical_coords[3] )
{
  CylindricalSpatialCoordinateConversionPolicy::convertFromCartesian(
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
  // Compute the radius
  r_spatial_coord = sqrt( x_spatial_coord*x_spatial_coord +
                          y_spatial_coord*y_spatial_coord );

  // Compute the azimuthal angle
  theta_spatial_coord = atan2( y_spatial_coord, x_spatial_coord );

  // The z coordinate is the same
  z_spatial_coord_out = z_spatial_coord_in;
}

// Convert the cylindrical coordinates to cartesian coordinates
inline void CylindricalSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                            const double cylindrical_coords[3],
                                            double cartesian_coords[3] )
{
  CylindricalSpatialCoordinateConversionPolicy::convertToCartesian(
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
  // Compute the x coordinate
  x_spatial_coordinate = r_spatial_coordinate*cos(theta_spatial_coord);

  // Compute the y coordinate
  y_spatial_coordinate = r_spatial_coordinate*sin(theta_spatial_coord);

  // The z coordinate is the same
  z_spatial_coord_out = z_spatial_coord_in;
}
  
} // end Utility namespace

#endif // end UTILITY_CYLINDRICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_CylindricalSpatialCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
