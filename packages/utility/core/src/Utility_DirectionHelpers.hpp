//---------------------------------------------------------------------------//
//!
//! \file   Utility_DirectionHelpers.hpp
//! \author Alex Robinson
//! \brief  Direction helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DIRECTION_HELPERS_HPP
#define UTILITY_DIRECTION_HELPERS_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace Utility{

//! Calculate the magnitude of a vector
double vectorMagnitude( const double x_component,
			const double y_component,
			const double z_component );

//! Calculate the magnitude of a vector
double vectorMagnitude( const double vector[3] );

//! Test if the direction is valid (on unit sphere)
bool validDirection( const double x_direction, 
		     const double y_direction,
		     const double z_direction );

//! Test if the direction is valid (on unit sphere)
bool validDirection( const double direction[3] );

//! Normalize a direction so that it lies on the unit sphere
void normalizeDirection( double direction[3] );

//! Calculate the cosine of the angle between two directions
double calculateCosineOfAngleBetweenVectors( const double direction_a[3],
					     const double direction_b[3] );

//! Reflect direction about the given unit normal
double reflectDirection( const double direction[3],
                         const double unit_normal[3],
                         double reflected_direction[3] );

//! Rotate a direction (unit vector) through a polar and azimuthal angle
void rotateDirectionThroughPolarAndAzimuthalAngle(
					       const double polar_angle_cosine,
					       const double azimuthal_angle,
					       const double direction[3],
					       double rotated_direction[3] );

// Calculate the magnitude of a vector
inline double vectorMagnitude( const double x_component,
			       const double y_component,
			       const double z_component )
{
  // Make sure that the coordinates are valid
  remember( typedef Teuchos::ScalarTraits<double> ST );
  testPrecondition( !ST::isnaninf( x_component ) );
  testPrecondition( !ST::isnaninf( y_component ) );
  testPrecondition( !ST::isnaninf( z_component ) );
  
  return sqrt( x_component*x_component + y_component*y_component +
	       z_component*z_component );
}

// Calculate the magnitude of a vector
inline double vectorMagnitude( const double vector[3] )
{
  return vectorMagnitude( vector[0], vector[1], vector[2] );
}

// Test if the direction is valid
inline bool validDirection( const double direction[3] )
{
  return validDirection( direction[0], direction[1], direction[2] );
}

} // end Utility namespace

#endif // end UTILITY_DIRECTION_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_DirectionHelpers.hpp
//---------------------------------------------------------------------------//
