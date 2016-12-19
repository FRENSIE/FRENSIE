//---------------------------------------------------------------------------//
//!
//! \file   Utility_CartesianDirectionalCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Cartesian directional coordinate conversion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_CARTESIAN_DIRECTIONAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_CARTESIAN_DIRECTIONAL_COORDINATE_CONVERSION_POLICY_HPP

// FRENSIE Includes
#include "Utility_DirectionalCoordinateConversionPolicy.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

//! The Cartesian directional coordinate conversion policy
class CartesianDirectionalCoordinateConversionPolicy : public DirectionalCoordinateConversionPolicy
{

public:

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
  CartesianDirectionalCoordinateConversionPolicy()
  { /* ... */ }

  //! Destructor
  virtual ~CartesianDirectionalCoordinateConversionPolicy()
  { /* ... */ }
};

//---------------------------------------------------------------------------//
// Inline Definitions
//---------------------------------------------------------------------------//

// Convert the Cartesian direction to Cartesian direction
/*! \details This method will simply copy the input direction to the output
 * direction. It can be used as the default policy method when no conversion
 * is required.
 */
inline void CartesianDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
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
inline void CartesianDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
                                                const double input_x_direction,
                                                const double input_y_direction,
                                                const double input_z_direction,
                                                double& output_x_direction,
                                                double& output_y_direction,
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
inline void CartesianDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
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
inline void CartesianDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
                                                const double input_x_direction,
                                                const double input_y_direction,
                                                const double input_z_direction,
                                                double& output_x_direction,
                                                double& output_y_direction,
                                                double& output_z_direction )
{
  // Make sure that the input direction is valid
  testPrecondition( isUnitVector( input_x_direction, input_y_direction, input_z_direction ) );

  output_x_direction = input_x_direction;
  output_y_direction = input_y_direction;
  output_z_direction = input_z_direction;
}
  
} // end Utility namespace

#endif // end UTILITY_CARTESIAN_DIRECTIONAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_CartesianDirectionalCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
