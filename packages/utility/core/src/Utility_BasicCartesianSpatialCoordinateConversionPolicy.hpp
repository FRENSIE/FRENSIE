//---------------------------------------------------------------------------//
//!
//! \file   Utility_BasicCartesianSpatialCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Basic Cartesian spatial coordinate conversion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_BASIC_CARTESIAN_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_BASIC_CARTESIAN_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

// FRENSIE Includes
#include "Utility_CartesianSpatialCoordinateConversionPolicy.hpp"

namespace Utility{

//! The basic Cartesian spatial coordinate conversion policy
class BasicCartesianSpatialCoordinateConversionPolicy : public CartesianSpatialCoordinateConversionPolicy
{

public:

  //! Constructor
  BasicCartesianSpatialCoordinateConversionPolicy()
  { /* ... */ }

  //! Destructor
  ~BasicCartesianSpatialCoordinateConversionPolicy()
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
};
  
} // end Utility namespace

#endif // end UTILITY_BASIC_CARTESIAN_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_BasicCartesianSpatialCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
