//---------------------------------------------------------------------------//
//!
//! \file   Utility_CartesianCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Cartesian coordinate conversion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_CARTESIAN_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_CARTESIAN_COORDINATE_CONVERSION_POLICY_HPP

// FRENSIE Includes
#include "Utility_SpatialCoordinateConversionPolicy.hpp"
#include "Utility_DirectionalCoordinateConversionPolicy.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

//! The Cartesian coordinate conversion policy
class CartesianCoordinateConversionPolicy : public CoordinateConversionPolicy,
                                            public DirectionalCoordinateConversionPolicy
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

  //! Convert the Cartesian direction to Cartesian direction
  static void convertFromCartesianDirection(
                                           const double input_direction[3],
                                           double output_direction[3] );

  //! Convert the Cartesian direction to Cartesian direction
  static void convertFromCartesianDirection( const double input_x_direction,
                                             const double input_y_direction,
                                             const double input_z_direction,
                                             double& output_x_direction,
                                             double& outout_y_direction,
                                             double& output_z_direction );

  //! Convert the Cartesian direction to a Cartesian direction
  static void convertToCartesianDirection( const double input_direction[3],
                                           double output_direction[3] );

  //! Convert the Cartesian direction to a Cartesian direction
  static void convertToCartesianDirection( const double input_x_direction,
                                           const double input_y_direction,
                                           const double input_z_direction,
                                           double& output_x_direction,
                                           double& outout_y_direction,
                                           double& output_z_direction );
                                          

  //! Constructor
  CartesianCoordinateConversionPolicy()
  { /* ... */ }

  //! Destructor
  virtual ~CartesianCoordinateConversionPolicy()
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
inline void CartesianCoordinateConversionPolicy::convertFromCartesianPosition(
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
inline void CartesianCoordinateConversionPolicy::convertFromCartesianPosition(
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
inline void CartesianCoordinateConversionPolicy::convertToCartesianPosition(
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
inline void CartesianCoordinateConversionPolicy::convertToCartesianPosition(
                                          const double input_x_spatial_coord,
                                          const double input_y_spatial_coord,
                                          const double input_z_spatial_coord,
                                          double& output_x_spatial_coord,
                                          double& output_y_spatial_coord,
                                          double& output_z_spatial_coord )
{
  output_x_spatial_coords = input_x_spatial_coords;
  output_y_spatial_coords = input_y_spatial_coords;
  output_z_spatial_coords = input_z_spatial_coords;
}

// Convert the Cartesian direction to Cartesian direction
/*! \details This method will simply copy the input direction to the output
 * direction. It can be used as the default policy method when no conversion
 * is required.
 */
inline void CartesianCoordinateConversionPolicy::convertFromCartesianDirection(
                                           const double input_direction[3],
                                           double output_direction[3] )
{
  // Make sure that the input direction is valid
  testPrecondition( isUnitVector( input_direction ) );

  output_direction[0] = input_direction[0];
  output_direction[1] = input_direction[1];
  output_direction[2] = input_direction[2];
}

// Convert the Cartesian direction to Cartesian direction
/*! \details This method will simply copy the input direction to the output
 * direction. It can be used as the default policy method when no conversion
 * is required.
 */
inline void CartesianCoordinateConversionPolicy::convertFromCartesianDirection(
                                                const double input_x_direction,
                                                const double input_y_direction,
                                                const double input_z_direction,
                                                double& output_x_direction,
                                                double& outout_y_direction,
                                                double& output_z_direction )
{
  // Make sure that the input direction is valid
  testPrecondition( isUnitVector( input_x_direction, input_y_direction, input_z_direction ) );

  output_x_direction = input_x_direction;
  output_y_direction = input_y_direction;
  output_z_direction = input_z_direction;
}

// Convert the Cartesian direction to a Cartesian direction
/*! \details This method will simply copy the input direction to the output
 * direction. It can be used as the default policy method when no conversion
 * is required.
 */
inline void CartesianCoordinateConversionPolicy::convertToCartesianDirection(
                                               const double input_direction[3],
                                               double output_direction[3] )
{
  // Make sure that the input direction is valid
  testPrecondition( isUnitVector( input_direction ) );

  output_direction[0] = input_direction[0];
  output_direction[1] = input_direction[1];
  output_direction[2] = input_direction[2];
}

// Convert the Cartesian direction to a Cartesian direction
/*! \details This method will simply copy the input direction to the output
 * direction. It can be used as the default policy method when no conversion
 * is required.
 */
inline void CartesianCoordinateConversionPolicy::convertToCartesianDirection(
                                                const double input_x_direction,
                                                const double input_y_direction,
                                                const double input_z_direction,
                                                double& output_x_direction,
                                                double& outout_y_direction,
                                                double& output_z_direction )
{
  // Make sure that the input direction is valid
  testPrecondition( isUnitVector( input_x_direction, input_y_direction, input_z_direction ) );

  output_x_direction = input_x_direction;
  output_y_direction = input_y_direction;
  output_z_direction = input_z_direction;
}
  
} // end Utility namespace

#endif // end UTILITY_CARTESIAN_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_CartesianCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
