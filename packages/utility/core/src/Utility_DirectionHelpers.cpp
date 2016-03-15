//---------------------------------------------------------------------------//
//!
//! \file   Utility_DirectionHelpers.cpp
//! \author Alex Robinson
//! \brief  Direction helper function definitions
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_DirectionHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"


namespace Utility{

// Test if the direction is valid
bool validDirection( const double x_direction, 
		     const double y_direction,
		     const double z_direction )
{
  // Make sure that the coordinates are valid
  remember( typedef Teuchos::ScalarTraits<double> ST );
  testPrecondition( !ST::isnaninf( x_direction ) );
  testPrecondition( !ST::isnaninf( y_direction ) );
  testPrecondition( !ST::isnaninf( z_direction ) );

  double argument = 
    vectorMagnitude( x_direction, y_direction, z_direction ) - 1.0;
  argument = Teuchos::ScalarTraits<double>::magnitude( argument );
  
  return argument < Teuchos::ScalarTraits<double>::prec();
}

// Normalize the direction so that it lies on the unit sphere
void normalizeDirection( double direction[3] )
{
  // Make sure that the coordinates are valid
  remember( typedef Teuchos::ScalarTraits<double> ST );
  testPrecondition( !ST::isnaninf( direction[0] ) );
  testPrecondition( !ST::isnaninf( direction[0] ) );
  testPrecondition( !ST::isnaninf( direction[0] ) );
  
  double magnitude = vectorMagnitude( direction );

  direction[0] /= magnitude;
  direction[1] /= magnitude;
  direction[2] /= magnitude;
}

// Calculate the cosine of the angle between two direction
double calculateCosineOfAngleBetweenVectors( const double direction_a[3],
					     const double direction_b[3] )
{
  // Make sure that the directions are valid
  testPrecondition( validDirection( direction_a ) );
  testPrecondition( validDirection( direction_b ) );

  double angle_cosine = direction_a[0]*direction_b[0] + 
    direction_a[1]*direction_b[1] + direction_a[2]*direction_b[2];
  
  // Check for round-off error.
  if( Teuchos::ScalarTraits<double>::magnitude( angle_cosine ) > 1.0 )
    angle_cosine = copysign( 1.0, angle_cosine );
  
  // Make sure the angle cosine is valid
  testPrecondition( angle_cosine >= -1.0 );
  testPrecondition( angle_cosine <= 1.0 );
  
  return angle_cosine;
}

// Reflect direction about the given unit normal
double reflectDirection( const double direction[3],
                         const double unit_normal[3],
                         double reflected_direction[3] )
{
  // Make sure the direction is valid
  testPrecondition( validDirection( direction ) );
  // Make sure the unit normal is valid
  testPrecondition( validDirection( unit_normal ) );

  // Calculate the angle cosine between the direction and unit normal
  double angle_cosine = 
    calculateCosineOfAngleBetweenVectors( direction, unit_normal );

  reflected_direction[0] = direction[0] - 2.0*angle_cosine*unit_normal[0];
  reflected_direction[1] = direction[1] - 2.0*angle_cosine*unit_normal[1];
  reflected_direction[2] = direction[2] - 2.0*angle_cosine*unit_normal[2];
}

// Rotate a direction (unit vector) through a polar and azimuthal angle
/*! \details The polar and azimuthal angles are with respect to the direction.
 * The cosine of the polar angle should be passed as the first 
 * argument instead of the polar angle. This is because the cosine of the
 * polar angle is commonly sampled and used much more often than the 
 * polar angle. The azimuthal angle should be passed as the second argument
 * instead of the cosine of the azimuthal angle. This is because the 
 * azimuthal angle is often directly sampled.
 */
void rotateDirectionThroughPolarAndAzimuthalAngle(
					       const double polar_angle_cosine,
					       const double azimuthal_angle,
					       const double direction[3],
					       double rotated_direction[3] )
{
  // Make sure the polar angle is valid
  testPrecondition( polar_angle_cosine >= -1.0 );
  testPrecondition( polar_angle_cosine <= 1.0 );
  // Make sure the azimuthal angle is valid
  testPrecondition( azimuthal_angle >= 0.0 );
  testPrecondition( azimuthal_angle <= 2*Utility::PhysicalConstants::pi );
  // Make sure the direction is valid
  testPrecondition( validDirection( direction ) );
  
  double polar_angle_sine = 
    sqrt( std::max(0.0, 1.0 - polar_angle_cosine*polar_angle_cosine) );
  double azimuthal_angle_cosine = cos(azimuthal_angle);
  double azimuthal_angle_sine = sin(azimuthal_angle);
  double direction_polar_angle_sine = 
    sqrt( std::max(0.0, 1.0 - direction[2]*direction[2]) );

  if( direction_polar_angle_sine > 1e-10 )
  {
    rotated_direction[0] = polar_angle_cosine*direction[0] +
      polar_angle_sine*(direction[0]*direction[2]*azimuthal_angle_cosine - 
			direction[1]*azimuthal_angle_sine)/
      direction_polar_angle_sine;

    rotated_direction[1] = polar_angle_cosine*direction[1] +
      polar_angle_sine*(direction[1]*direction[2]*azimuthal_angle_cosine +
			direction[0]*azimuthal_angle_sine)/
      direction_polar_angle_sine;

    rotated_direction[2] = polar_angle_cosine*direction[2] -
      polar_angle_sine*direction_polar_angle_sine*azimuthal_angle_cosine;      
  }
  // For the special case where z_dir ~ 1 => sqrt(1 - z^2) ~ 0, assume
  // spherical coordinates are w.r.t. y-axis instead of z-axis
  else
  {
    // Recompute the sine of the polar angle of the direction
    direction_polar_angle_sine = sqrt(1.0 - direction[1]*direction[1]);

    rotated_direction[0] = polar_angle_cosine*direction[0] +
      polar_angle_sine*(direction[0]*direction[1]*azimuthal_angle_cosine +
			direction[2]*azimuthal_angle_sine)/
      direction_polar_angle_sine;

    rotated_direction[1] = polar_angle_cosine*direction[1] -
      polar_angle_sine*direction_polar_angle_sine*azimuthal_angle_cosine;

    rotated_direction[2] = polar_angle_cosine*direction[2] +
      polar_angle_sine*(direction[1]*direction[2]*azimuthal_angle_cosine -
			direction[0]*azimuthal_angle_sine)/
      direction_polar_angle_sine;
  }
  
  // Clean roundoff errors
  normalizeDirection( rotated_direction );
  
  // Make sure that the rotated direction is valid
  testPostcondition( validDirection( rotated_direction ) );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_DirectionHelpers.cpp
//---------------------------------------------------------------------------//
