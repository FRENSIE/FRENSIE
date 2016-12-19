//---------------------------------------------------------------------------//
//!
//! \file   Utility_BasicCartesianDirectionalCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Basic Cartesian directional coordinate conversion policy definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_BasicCartesianDirectionalCoordinateConversionPolicy.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Convert the directional coordinates to cartesian coordinates
/*! \details This method will simply copy the input direction to the output
 * direction.
 */
void BasicCartesianDirectionalCoordinateConversionPolicy::convertToCartesianDirectionalCoordinates(
                                      const double primary_directional_coord,
                                      const double secondary_directional_coord,
                                      const double tertiary_directional_coord,
                                      double& x_directional_coord,
                                      double& y_directional_coord,
                                      double& z_directional_coord ) const
{
  // Make sure that the input direction is valid
  testPrecondition( isUnitVector( primary_directional_coord, secondary_directional_coord, tertiary_directional_coord ) );

  this->convertToCartesianDirection( primary_directional_coord,
                                     secondary_directional_coord,
                                     tertiary_directional_coord,
                                     x_directional_coord,
                                     y_directional_coord,
                                     z_directional_coord );
}

// Convert the cartesian coordinates to the directional coordinate system
/*! \details This method will simply copy the input direction to the output
 * direction.
 */
void BasicCartesianDirectionalCoordinateConversionPolicy::convertFromCartesianDirectionalCoordinates(
                                     const double x_directional_coord,
                                     const double y_directional_coord,
                                     const double z_directional_coord,
                                     double& primary_directional_coord,
                                     double& secondary_directional_coord,
                                     double& tertiary_directional_coord ) const
{
  // Make sure that the input direction is valid
  testPrecondition( isUnitVector( x_directional_coord, y_directional_coord, z_directional_coord ) );

  this->convertFromCartesianDirection( x_directional_coord,
                                       y_directional_coord,
                                       z_directional_coord,
                                       primary_directional_coord,
                                       secondary_directional_coord,
                                       tertiary_directional_coord );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_BasicCartesianCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
