//---------------------------------------------------------------------------//
//!
//! \file   tstLinearCongruentialGenerator.cpp
//! \author Alex Robinson
//! \brief  Linear Congruential Generator class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_LinearCongruentialGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a random number in the interval [0,1) can be obtained
FRENSIE_UNIT_TEST( LinearCongruentialGenerator, getRandomNumber )
{
  Utility::LinearCongruentialGenerator lcg;

  double random_number = lcg.getRandomNumber();

  FRENSIE_CHECK_GREATER_OR_EQUAL( random_number, 0.0 );
  FRENSIE_CHECK_LESS( random_number, 1.0 );
}

//---------------------------------------------------------------------------//
// end tstLinearCongruentialGenerator.cpp
//---------------------------------------------------------------------------//

