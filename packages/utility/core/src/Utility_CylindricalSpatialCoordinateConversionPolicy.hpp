//---------------------------------------------------------------------------//
//!
//! \file   Utility_CylindricalSpatialCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Cylindrical coordinate conversion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef CYLINDRICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP
#define CYLINDRICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

namespace Utility{

//! The cylindrical coordinate conversion policy class
class CylindricalCoordinateConversionPolicy
{

public:

  //! Constructor
  CylindricalSpatialCoordinateConversionPolicy( const double origin[3],
                                                const double axis[3] );

  //! Destructor
  ~CylindricalSpatialCoordinateConversionPolicy()
  { /* ... */ }

  //! Convert the spatial coordinates to cartesian coordinates
  void convertToCartesianCoordinates( const double primary_spatial_coord,
                                      const double secondary_spatial_coord,
                                      const double tertiary_spatial_coord,
                                      double& x_spatial_coord,
                                      double& y_spatial_coord,
                                      double& z_spatial_coord ) const override;

  //! Convert the cartesian coordinates to the spatial coordinate system
  void convertFromCartesianCoordinates(
                               const double x_spatial_coord,
                               const double y_spatial_coord,
                               const double z_spatial_coord,
                               double& primary_spatial_coord,
                               double& secondary_spatial_coord,
                               double& tertiary_spatial_coord ) const override;

private:

  // The origin of the cylindrical coordinate system w.r.t. the Cartesian
  // coordinate system
  double d_origin[3];

  // The axis (unit vector) of the cylindrical coordinate system w.r.t. the
  // Cartesian coordinate system
  double d_axis[3];
};
  
} // end Utility namespace

#endif // end CYLINDRICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_CylindricalSpatialCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
