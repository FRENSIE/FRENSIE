//---------------------------------------------------------------------------//
//!
//! \file   DirectionHelpers.hpp
//! \author Alex Robinson
//! \brief  Direction helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef DIRECTION_HELPERS_HPP
#define DIRECTION_HELPERS_HPP

namespace FACEMC{

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

} // end FACEMC namespace

// Test if the direction is valid
inline bool FACEMC::validDirection( const double direction[3] )
{
  return validDirection( direction[0], direction[1], direction[2] );
}

#endif // end DIRECTION_HELPERS_HPP

//---------------------------------------------------------------------------//
// end DirectionHelpers.hpp
//---------------------------------------------------------------------------//
