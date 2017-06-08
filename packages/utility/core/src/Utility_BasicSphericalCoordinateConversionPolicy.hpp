//---------------------------------------------------------------------------//
//!
//! \file   Utility_BasicSphericalCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Basic spherical coordinate conversion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_BASIC_SPHERICAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_BASIC_SPHERICAL_COORDINATE_CONVERSION_POLICY_HPP

// FRENSIE Includes
#include "Utility_SphericalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_SphericalDirectionalCoordinateConversionPolicy.hpp"

namespace Utility{

//! The basic spherical coordinate conversion policy class
class BasicSphericalCoordinateConversionPolicy : public SphericalSpatialCoordinateConversionPolicy,
                                                 public SphericalDirectionalCoordinateConversionPolicy
{

public:

  //! Constructor
  BasicSphericalCoordinateConversionPolicy()
  { /* ... */ }

  //! Destructor
  ~BasicSphericalCoordinateConversionPolicy()
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
};
  
} // end Utility namespace

#endif // end UTILITY_BASIC_SPHERICAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_BasicSphericalCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//