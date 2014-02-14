//---------------------------------------------------------------------------//
//!
//! \file   tstLinearCongruentialGenerator.cpp
//! \author Alex Robinson
//! \brief  Linear Congruential Generator class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "FACEMC_UnitTestHarnessExtensions.hpp"
#include "LinearCongruentialGenerator.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a random number in the interval [0,1) can be obtained
TEUCHOS_UNIT_TEST( LinearCongruentialGenerator, getRandomNumber )
{
  FACEMC::LinearCongruentialGenerator lcg;
  
  double random_number = lcg.getRandomNumber();
  
  TEST_COMPARE( random_number, >=, 0.0 );
  TEST_COMPARE( random_number, <, 1.0 );
}

//---------------------------------------------------------------------------//
// end tstLinearCongruentialGenerator.cpp
//---------------------------------------------------------------------------//

