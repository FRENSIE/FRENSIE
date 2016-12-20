//---------------------------------------------------------------------------//
//!
//! \file   Utility_GeneralSphericalSpatialCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  General spherical spatial coordinate conversion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GENERAL_SPHERICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_GENERAL_SPHERICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

// FRENSIE Includes
#include "Utility_SphericalSpatialCoordinateConversionPolicy.hpp"

namespace Utility{

//! The general spherical spatial coordinate conversion policy class
class GeneralSphericalSpatialCoordinateConversionPolicy : public SphericalSpatialCoordinateConversionPolicy
{

public:

  //! Constructor
  GeneralSphericalSpatialCoordinateConversionPolicy( const double origin[3],
                                                     const double axis[3] );

  //! Destructor
  ~GeneralSphericalSpatialCoordinateConversionPolicy()
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

  // The default constructor should not be used - if the axis and origin
  // correspond to the global coordinate system use the basic conversion
  // policy
  GeneralSphericalSpatialCoordinateConversionPolicy();

  // We have C-arrays as members - hide the copy constructor and assignment
  // operator
  GeneralSphericalSpatialCoordinateConversionPolicy( const GeneralSphericalSpatialCoordinateConversionPolicy& that );
  GeneralSphericalSpatialCoordinateConversionPolicy& operator=( const GeneralSphericalSpatialCoordinateConversionPolicy& that );

  // The origin of the spherical coordinate system w.r.t. the global Cartesian
  // coordinate system
  double d_origin[3];

  // The z-axis (unit vector) of the spherical coordinate system w.r.t. the
  // global Cartesian coordinate system
  double d_axis[3];
};

  
} // end Utility namespace

#endif // end UTILITY_GENERAL_SPHERICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_GeneralSphericalSpatialCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
