//---------------------------------------------------------------------------//
//!
//! \file   Utility_RotationCylindricalSpatialCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Rotation cylindrical spatial coordinate conversion policy decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ROTATION_CYLINDRICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_ROTATION_CYLINDRICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

// FRENSIE Includes
#include "Utility_CylindricalSpatialCoordinateConversionPolicy.hpp"

namespace Utility{

//! The rotation cylindrical spatial coordinate conversion policy class
class RotationCylindricalSpatialCoordinateConversionPolicy : public CylindricalSpatialCoordinateConversionPolicy
{

public:

  //! Constructor
  RotationCylindricalSpatialCoordinateConversionPolicy( const double axis[3] );

  //! Destructor
  ~RotationCylindricalSpatialCoordinateConversionPolicy()
  { /* ... */ }

  //! Convert the spatial coordinates to cartesian coordinates
  void convertToCartesianSpatialCoordinates(
                                      const double primary_spatial_coord,
                                      const double secondary_spatial_coord,
                                      const double tertiary_spatial_coord,
                                      double& x_spatial_coord,
                                      double& y_spatial_coord,
                                      double& z_spatial_coord ) const override;

  //! Convert the cartesian coordinates to the spatial coordinate system
  void convertFromCartesianSpatialCoordinates(
                               const double x_spatial_coord,
                               const double y_spatial_coord,
                               const double z_spatial_coord,
                               double& primary_spatial_coord,
                               double& secondary_spatial_coord,
                               double& tertiary_spatial_coord ) const override;

private:

  // The default constructor should not be used - if the z-axis of the local
  // coordinate system w.r.t. the global Cartesian coordinate system aligns
  // with the z-axis of the Cartesian coordinate system use the basic
  // conversion policy
  RotationCylindricalSpatialCoordinateConversionPolicy();

  // We have C-arrays as members - hide the copy constructor and assignment
  // operator
  RotationCylindricalSpatialCoordinateConversionPolicy( const RotationCylindricalSpatialCoordinateConversionPolicy& that );
  RotationCylindricalSpatialCoordinateConversionPolicy& operator=( const RotationCylindricalSpatialCoordinateConversionPolicy& that );

  // The z-axis (unit vector) of the local cylindrical coordinate system w.r.t.
  // the global Cartesian coordinate system
  double d_axis[3];
};
  
} // end Utility namespace

#endif // end UTILITY_ROTATION_CYLINDRICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_RotationCylindricalSpatialCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
