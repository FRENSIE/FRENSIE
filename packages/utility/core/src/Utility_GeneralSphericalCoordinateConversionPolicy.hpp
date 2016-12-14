//---------------------------------------------------------------------------//
//!
//! \file   Utility_GeneralShericalCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  General spherical coordinate conversion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GENERAL_SPHERICAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_GENERAL_SPHERICAL_COORDINATE_CONVERSION_POLICY_HPP

// FRENSIE Includes
#include "Utility_SphericalCoordinateConversionPolicy.hpp"

namespace Utility{

//! The general spherical coordinate conversion policy class
class GeneralSphericalCoordinateConversionPolicy : public SphericalCoordinateConversionPolicy
{

public:

  //! Constructor
  GeneralSphericalCoordinateConversionPolicy( const double origin[3],
                                              const double axis[3] );

  //! Constructor (global origin)
  GeneralSphericalCoordinateConversionPolicy( const double axis[3] );

  //! Destructor
  ~GeneralSphericalCoordinateConversionPolicy()
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

  //! Convert the directional coordinates to cartesian coordinates
  void convertToCartesianDirectionalCoordinates(
                                  const double primary_directional_coord,
                                  const double secondary_directional_coord,
                                  const double tertiary_directional_coord,
                                  double& x_directional_coord,
                                  double& y_directional_coord,
                                  double& z_directional_coord ) const override;

  //! Convert the cartesian coordinates to the directional coordinate system
  void convertFromCartesianDirectionalCoordinates(
                           const double x_directional_coord,
                           const double y_directional_coord,
                           const double z_directional_coord,
                           double& primary_directional_coord,
                           double& secondary_directional_coord,
                           double& tertiary_directional_coord ) const override;

private:

  // The default constructor should not be used - if the axis and origin
  // correspond to the global coordinate system use the basic conversion
  // policy
  GeneralSphericalCoordinateConversionPolicy();

  // We have C-arrays as members - hide the copy constructor and assignment
  // operator
  GeneralSphericalCoordinateConversionPolicy( const GeneralSphericalCoordinateConversionPolicy& that );
  GeneralSphericalCoordinateConversionPolicy& operator=( const GeneralSphericalCoordinateConversionPolicy& that );

  // The origin of the spherical coordinate system w.r.t. the Cartesian
  // coordinate system
  double d_origin[3];

  // The z-axis (unit vector) of the spherical coordinate system w.r.t. the
  // Cartesian coordinate system
  double d_axis[3];
};

  
} // end Utility namespace

#endif // end UTILITY_GENERAL_SPHERICAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_GeneralSphericalCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
