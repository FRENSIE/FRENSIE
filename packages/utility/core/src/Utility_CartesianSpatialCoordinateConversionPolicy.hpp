//---------------------------------------------------------------------------//
//!
//! \file   Utility_CartesianSpatialCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Cartesian spatial coordinate conversion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_CARTESIAN_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_CARTESIAN_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

// FRENSIE Includes
#include "Utility_SpatialCoordinateConversionPolicy.hpp"

namespace Utility{

//! The Cartesian spatial coordinate conversion policy
class CartesianSpatialCoordinateConversionPolicy : public SpatialCoordinateConversionPolicy
{

public:
  
  //! Convert the Cartesian coordinates to Cartesian coordinates
  static void convertFromCartesianPosition( const double input_coords[3],
                                            double output_coords[3] );

  //! Convert the Cartesian coordinates to Cartesian coordinates
  static void convertFromCartesianPosition( const double input_x_spatial_coord,
                                            const double input_y_spatial_coord,
                                            const double input_z_spatial_coord,
                                            double& output_x_spatial_coord,
                                            double& output_y_spatial_coord,
                                            double& output_z_spatial_coord );

  //! Convert the Cartesian coordinates to Cartesian coordinates
  static void convertToCartesianPosition( const double input_coords[3],
                                          double output_coords[3] );

  //! Convert the Cartesian coordinates to Cartesian coordinates
  static void convertToCartesianPosition( const double input_x_spatial_coord,
                                          const double input_y_spatial_coord,
                                          const double input_z_spatial_coord,
                                          double& output_x_spatial_coord,
                                          double& output_y_spatial_coord,
                                          double& output_z_spatial_coord );

  //! Constructor
  CartesianSpatialCoordinateConversionPolicy()
  { /* ... */ }

  //! Destructor
  virtual ~CartesianSpatialCoordinateConversionPolicy()
  { /* ... */ }
};

//---------------------------------------------------------------------------//
// Inline Definitions
//---------------------------------------------------------------------------//

// Convert the Cartesian coordinates to Cartesian coordinates
/*! \details This method will simply copy the input coordinates to the output
 * coordinates. It can be used as the default policy method when no conversion
 * is required.
 */
inline void CartesianSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                                  const double input_coords[3],
                                                  double output_coords[3] )
{
  output_coords[0] = input_coords[0];
  output_coords[1] = input_coords[1];
  output_coords[2] = input_coords[2];
}

// Convert the Cartesian coordinates to Cartesian coordinates
/*! \details This method will simply copy the input coordinates to the output
 * coordinates. It can be used as the default policy method when no conversion
 * is required.
 */
inline void CartesianSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                            const double input_x_spatial_coord,
                                            const double input_y_spatial_coord,
                                            const double input_z_spatial_coord,
                                            double& output_x_spatial_coord,
                                            double& output_y_spatial_coord,
                                            double& output_z_spatial_coord )
{
  output_x_spatial_coord = input_x_spatial_coord;
  output_y_spatial_coord = input_y_spatial_coord;
  output_z_spatial_coord = input_z_spatial_coord;
}

// Convert the Cartesian coordinates to Cartesian coordinates
/*! \details This method will simply copy the input coordinates to the output
 * coordinates. It can be used as the default policy method when no conversion
 * is required.
 */
inline void CartesianSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                                  const double input_coords[3],
                                                  double output_coords[3] )
{
  output_coords[0] = input_coords[0];
  output_coords[1] = input_coords[1];
  output_coords[2] = input_coords[2];
}

// Convert the Cartesian coordinates to Cartesian coordinates
/*! \details This method will simply copy the input coordinates to the output
 * coordinates. It can be used as the default policy method when no conversion
 * is required.
 */
inline void CartesianSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                          const double input_x_spatial_coord,
                                          const double input_y_spatial_coord,
                                          const double input_z_spatial_coord,
                                          double& output_x_spatial_coord,
                                          double& output_y_spatial_coord,
                                          double& output_z_spatial_coord )
{
  output_x_spatial_coord = input_x_spatial_coord;
  output_y_spatial_coord = input_y_spatial_coord;
  output_z_spatial_coord = input_z_spatial_coord;
}
  
} // end Utility namespace

#endif // end UTILITY_CARTESIAN_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_CartesianSpatialCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
