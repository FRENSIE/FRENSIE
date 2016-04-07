//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Ray.cpp
//! \author Alex Robinson
//! \brief  Ray class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Geometry_Ray.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

// Constructor
Ray::Ray( const double x_position,
	  const double y_position,
	  const double z_position,
	  const double x_direction,
	  const double y_direction,
	  const double z_direction )
  : d_position( new double[3] ),
    d_direction( new double[3] ),
    d_deep_copy_initialization( true )
{
  // Make sure the position is valid
  testPrecondition( !ST::isnaninf( d_position[0] ) );
  testPrecondition( !ST::isnaninf( d_position[1] ) );
  testPrecondition( !ST::isnaninf( d_position[2] ) );
  // Make sure the direction is a unit vector
  testPrecondition( Utility::validDirection( x_direction, 
					     y_direction, 
					     z_direction ) );

  d_position[0] = x_position;
  d_position[1] = y_position;
  d_position[2] = z_position;

  d_direction[0] = x_direction;
  d_direction[1] = y_direction;
  d_direction[2] = z_direction;
}

// Constructor
Ray::Ray( const double position[3],
	  const double direction[3] )
  : d_position( new double[3] ), 
    d_direction( new double[3] ),
    d_deep_copy_initialization( true )
{
  // Make sure the position and direction are valid
  testPrecondition( !ST::isnaninf( d_position[0] ) );
  testPrecondition( !ST::isnaninf( d_position[1] ) );
  testPrecondition( !ST::isnaninf( d_position[2] ) );
  // Make sure the direction is a unit vector
  testPrecondition( Utility::validDirection( direction[0], 
					     direction[1], 
					     direction[2] ) );

  d_position[0] = position[0];
  d_position[1] = position[1];
  d_position[2] = position[2];

  d_direction[0] = direction[0];
  d_direction[1] = direction[1];
  d_direction[2] = direction[2];
}

// Constructor
/*! \details Warning: creating a shallow copy of the input pointers can be
 * dangerous. Only do this if you know what you're doing!
 */
Ray::Ray( double position[3],
	  double direction[3],
	  const bool deep_copy )
  : d_position( position ), 
    d_direction( direction ),
    d_deep_copy_initialization( deep_copy )
{
  if( deep_copy )
  {
    // Make sure the position and direction are valid
    testPrecondition( !ST::isnaninf( d_position[0] ) );
    testPrecondition( !ST::isnaninf( d_position[1] ) );
    testPrecondition( !ST::isnaninf( d_position[2] ) );
    // Make sure the direction is a unit vector
    testPrecondition( Utility::validDirection( direction[0], 
					       direction[1], 
					       direction[2] ) );
    d_position = new double[3];
    d_position[0] = position[0];
    d_position[1] = position[1];
    d_position[2] = position[2];

    d_direction = new double[3];
    d_direction[0] = direction[0];
    d_direction[1] = direction[1];
    d_direction[2] = direction[2];
  }
}

// Destructor
Ray::~Ray()
{
  if( d_deep_copy_initialization )
  {
    delete[] d_position;
    delete[] d_direction;
  }
}

// Return the x position of the ray
double Ray::getXPosition() const
{
  return d_position[0];
}

// Return the y position of the ray
double Ray::getYPosition() const
{
  return d_position[1];
}

// Return the z position of the ray
double Ray::getZPosition() const
{
  return d_position[2];
}

// Return the position of the ray
const double* Ray::getPosition() const
{
  return d_position;
}

// Return the x direction of the ray
double Ray::getXDirection() const
{
  return d_direction[0];
}

// Return the y direction of the ray
double Ray::getYDirection() const
{
  return d_direction[1];
}

// Return the z direction of the ray
double Ray::getZDirection() const
{
  return d_direction[2];
}

// Return the direction of the ray
const double* Ray::getDirection() const
{
  return d_direction;
}

// Change the direction of the ray
void Ray::changeDirection( const double direction[3] )
{
  // Make sure the direction is valid
  testPrecondition( Utility::validDirection( direction ) );

  // Deep copy the direction
  d_direction[0] = direction[0];
  d_direction[1] = direction[1];
  d_direction[2] = direction[2];
}

// Change the direction of the ray
void Ray::changeDirection( const double x_direction,
                           const double y_direction,
                           const double z_direction )
{
  // Make sure the direction is valid
  testPrecondition( Utility::validDirection( x_direction, 
                                             y_direction, 
                                             z_direction ) );

  d_direction[0] = x_direction;
  d_direction[1] = y_direction;
  d_direction[2] = z_direction;
}

// Advance the head along its direction by the requested distance
void Ray::advanceHead( const double distance )
{
  // Make sure the distance is valid
  testPrecondition( !ST::isnaninf( distance ) );

  d_position[0] += d_direction[0]*distance;
  d_position[1] += d_direction[1]*distance;
  d_position[2] += d_direction[2]*distance;
}

// Print method implementation
void Ray::print( std::ostream& os ) const
{
  os.precision( 16 );
  os << "Position: {" << d_position[0] << "," << d_position[1] << ","
     << d_position[2] << "}" << std::endl;
  os << "Direction: {" << d_direction[0] << "," 
     << d_direction[1] << ","
     << d_direction[2] << "}" << std::endl;
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_Ray.cpp
//---------------------------------------------------------------------------//
