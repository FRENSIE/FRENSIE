//---------------------------------------------------------------------------//
//!
//! \file   DirectionHelpers.cpp
//! \author Alex Robinson
//! \brief  Direction helper function definitions
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "DirectionHelpers.hpp"
#include "ContractException.hpp"

namespace FACEMC{

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
  
  double argument = x_direction*x_direction + y_direction*y_direction +
    z_direction*z_direction;
  double norm_two_value = Teuchos::ScalarTraits<double>::squareroot(argument);
  
  return Teuchos::ScalarTraits<double>::magnitude( norm_two_value - 1.0 ) < 
    Teuchos::ScalarTraits<double>::prec();
}

// Normalize the direction so that it lies on the unit sphere
void normalizeDirection( double direction[3] )
{
  // Make sure that the coordinates are valid
  remember( typedef Teuchos::ScalarTraits<double> ST );
  testPrecondition( !ST::isnaninf( direction[0] ) );
  testPrecondition( !ST::isnaninf( direction[0] ) );
  testPrecondition( !ST::isnaninf( direction[0] ) );
  
  double argument = direction[0]*direction[0] + direction[1]*direction[1] +
    direction[2]*direction[2];
  double magnitude = Teuchos::ScalarTraits<double>::squareroot( argument );

  direction[0] /= magnitude;
  direction[1] /= magnitude;
  direction[2] /= magnitude;
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end DirectionHelpers.cpp
//---------------------------------------------------------------------------//
