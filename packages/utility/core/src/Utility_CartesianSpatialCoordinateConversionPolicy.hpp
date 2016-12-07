//---------------------------------------------------------------------------//
//!
//! \file   Utility_CartesianSpatialCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Cartesian spatial coordinate conversion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_CARTESIAN_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_CARTESIAN_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

namespace Utility{

//! The Cartesian spatial coordinate conversion policy
class CartesianSpatialCoordinateConversionPolicy
{

public:

  //! Constructor
  CartesianSpatialCoordinateConversionPolicy()
  { /* ... */ }

  //! Destructor
  ~CartesianSpatialCoordinateConversionPolicy()
  { /* ... */ }

  //! Convert the spatial coordinates to cartesian coordinates
  void convertToCartesianCoordinates( const double primary_spatial_coord,
                                      const double secondary_spatial_coord,
                                      const double tertiary_spatial_coord,
                                      double& x_spatial_coord,
                                      double& y_spatial_coord,
                                      double& z_spatial_coord ) const override;

  //! Convert the cartesian coordinates to the spatial coordinate system
  void convertFromCartesianCoordinates( const double x_spatial_coord,
                                        const double y_spatial_coord,
                                        const double z_spatial_coord,
                                        double& primary_spatial_coord,
                                        double& secondary_spatial_coord,
                                        double& tertiary_spatial_coord ) const override;
};
  
} // end Utility namespace

#endif // end UTILITY_CARTESIAN_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_CartesianSpatialCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
