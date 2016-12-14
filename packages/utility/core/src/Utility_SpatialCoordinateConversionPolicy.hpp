//---------------------------------------------------------------------------//
//!
//! \file   Utility_SpatialCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Spatial coordinate conversion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

namespace Utility{

//! The spatial coordinate conversion policy class
class SpatialCoordinateConversionPolicy
{

public:

  //! Constructor
  SpatialCoordinateConversionPolicy()
  { /* ... */ }

  //! Destructor
  virtual ~SpatialCoordinateConversionPolicy()
  { /* ... */ }

  //! Convert the spatial coordinates to cartesian coordinates
  virtual void convertToCartesianSpatialCoordinates(
                                          const double primary_spatial_coord,
                                          const double secondary_spatial_coord,
                                          const double tertiary_spatial_coord,
                                          double& x_spatial_coord,
                                          double& y_spatial_coord,
                                          double& z_spatial_coord ) const = 0;

  //! Convert the spatial coordinates to cartesian coordinates
  void convertToCartesianSpatialCoordinates(
                                       const double coordinates[3],
                                       double cartesian_coordinates[3] ) const;

  //! Convert the cartesian coordinates to the spatial coordinate system
  virtual void convertFromCartesianSpatialCoordinates(
                                    const double x_spatial_coord,
                                    const double y_spatial_coord,
                                    const double z_spatial_coord,
                                    double& primary_spatial_coord,
                                    double& secondary_spatial_coord,
                                    double& tertiary_spatial_coord ) const = 0;

  //! Convert the cartesian coordinates to the spatial coordinate system
  void convertFromCartesianSpatialCoordinates(
                                         const double cartesian_coordinates[3],
                                         double coordinates[3] ) const;
};

// Convert the spatial coordinates to cartesian coordinates
inline void SpatialCoordinateConversionPolicy::convertToCartesianSpatialCoordinates(
                                        const double coordinates[3],
                                        double cartesian_coordinates[3] ) const
{
  this->convertToCartesianSpatialCoordinates( coordinates[0],
                                              coordinates[1],
                                              coordinates[2],
                                              cartesian_coordinates[0],
                                              cartesian_coordinates[1],
                                              cartesian_coordinates[2] );
}

// Convert the cartesian coordinates to the spatial coordinate system
inline void SpatialCoordinateConversionPolicy::convertFromCartesianSpatialCoordinates(
                                         const double cartesian_coordinates[3],
                                         double coordinates[3] ) const
{
  this->convertFromCartesianSpatialCoordinates( cartesian_coordinates[0],
                                                cartesian_coordinates[1],
                                                cartesian_coordinates[2],
                                                coordinates[0],
                                                coordinates[1],
                                                coordinates[2] );
}
  
} // end Utility namespace

#endif // end UTILITY_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_SpatialCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
