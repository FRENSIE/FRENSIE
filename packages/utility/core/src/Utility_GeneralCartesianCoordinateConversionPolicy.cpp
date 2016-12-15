//---------------------------------------------------------------------------//
//!
//! \file   Utility_GeneralCartesianCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  General Cartesian coordinate conversion policy definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_GeneralCartesianCoordinateConversionPolicy.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
GeneralCartesianCoordinateConversionPolicy::GeneralCartesianCoordinateConversionPolicy(
                                                        const double origin[3],
                                                        const double axis[3] )
  : d_origin{origin[0], origin[1], origin[2]},
    d_axis{axis[0], axis[1], axis[2]}
{
  // Normalize the axis vector
  normalizeVector( d_axis );
}

// Constructor (global origin)
GeneralCartesianCoordinateConversionPolicy::GeneralCartesianCoordinateConversionPolicy(
                                                         const double axis[3] )
  : d_origin{0.0, 0.0, 0.0},
    d_axis{axis[0], axis[1], axis[2]}
{
  // Normalize the axis vector
  normalizeVector( d_axis );
}

// Convert the spatial coordinates to cartesian coordinates
/*! \details The original spatial coordinates are (x',y',z'), which are the
 * coordinates in the local coordinate system (defined by origin and axis).
 * These will be converted to the global coordinate system.
 */
void GeneralCartesianCoordinateConversionPolicy::convertToCartesianSpatialCoordinates(
                                          const double primary_spatial_coord,
                                          const double secondary_spatial_coord,
                                          const double tertiary_spatial_coord,
                                          double& x_spatial_coord,
                                          double& y_spatial_coord,
                                          double& z_spatial_coord ) const
{
  convertLocalVectorToGlobalVector( primary_spatial_coord,
                                    secondary_spatial_coord,
                                    tertiary_spatial_coord,
                                    d_axis,
                                    d_origin,
                                    x_spatial_coord,
                                    y_spatial_coord,
                                    z_spatial_coord );
}

// Convert the cartesian coordinates to the spatial coordinate system
/*! \details The final spatial coordinates are (x',y',z'), which are the 
 * coordinates in the local coordinate system (defined by origin and axis).
 * The global coordinates will be converted to the local coordinate system.
 */
void GeneralCartesianCoordinateConversionPolicy::convertFromCartesianSpatialCoordinates(
                                         const double x_spatial_coord,
                                         const double y_spatial_coord,
                                         const double z_spatial_coord,
                                         double& primary_spatial_coord,
                                         double& secondary_spatial_coord,
                                         double& tertiary_spatial_coord ) const
{
  convertGlobalVectorToLocalVector( x_spatial_coord,
                                    y_spatial_coord,
                                    z_spatial_coord,
                                    d_axis,
                                    d_origin,
                                    primary_spatial_coord,
                                    secondary_spatial_coord,
                                    tertiary_spatial_coord );
}

// Convert the directional coordinates to cartesian coordinates
/*! \details The original directional coordinates are (u',v',w'), which are the
 * directional coordinates in the local coordinate system (defined only by
 * the axis - the origin is ignored with directional coordinate transforms).
 * The local directional coordinates will be converted to the global
 * coordinate system.
 */
void GeneralCartesianCoordinateConversionPolicy::convertToCartesianDirectionalCoordinates(
                                      const double primary_directional_coord,
                                      const double secondary_directional_coord,
                                      const double tertiary_directional_coord,
                                      double& x_directional_coord,
                                      double& y_directional_coord,
                                      double& z_directional_coord ) const
{
  // Make sure that the input directional coordinates are valid
  testPrecondition( isUnitVector( primary_directional_coord, secondary_directional_coord, tertiary_directional_coord ) );

  convertLocalVectorToGlobalVector( primary_directional_coord,
                                    secondary_directional_coord,
                                    tertiary_directional_coord,
                                    d_axis,
                                    x_directional_coord,
                                    y_directional_coord,
                                    z_directional_coord );
}

// Convert the cartesian coordinates to the directional coordinate system
/*! \details The final directional coordinates are (u',v',w'), which are the
 * directional coordinates in the local coordinate system (defined only the the
 * axis - the origin is ignored with directional coordinate transforms). The
 * glboal directional coordinates will be converted to the local 
 * coordinate system.
 */
void GeneralCartesianCoordinateConversionPolicy::convertFromCartesianDirectionalCoordinates(
                                     const double x_directional_coord,
                                     const double y_directional_coord,
                                     const double z_directional_coord,
                                     double& primary_directional_coord,
                                     double& secondary_directional_coord,
                                     double& tertiary_directional_coord ) const
{
  // Make sure that the input directional coordinates are valid
  testPrecondition( isUnitVector( x_directional_coord, y_directional_coord, z_directional_coord ) );

  convertGlobalVectorToLocalVector( x_directional_coord,
                                    y_directional_coord,
                                    z_directional_coord,
                                    d_axis,
                                    primary_directional_coord,
                                    secondary_directional_coord,
                                    tertiary_directional_coord );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_GeneralCartesianCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
