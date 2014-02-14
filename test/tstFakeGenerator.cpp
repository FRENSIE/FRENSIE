//---------------------------------------------------------------------------//
//!
//! \file   tstFakeGenerator.cpp
//! \author Alex Robinson
//! \brief  Fake generator class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "FakeGenerator.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the fake stream returns the correct values
TEUCHOS_UNIT_TEST( FakeGenerator, getRandomNumber )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.1;
  fake_stream[1] = 0.2;
  fake_stream[2] = 0.3;
  
  Teuchos::RCP<FACEMC::LinearCongruentialGenerator> 
    generator( new FACEMC::FakeGenerator( fake_stream ) );
  
  double random_number = generator->getRandomNumber();
  TEST_EQUALITY_CONST( random_number, 0.1 );

  random_number = generator->getRandomNumber();
  TEST_EQUALITY_CONST( random_number, 0.2 );
  
  random_number = generator->getRandomNumber();
  TEST_EQUALITY_CONST( random_number, 0.3 );
  
  // Test that it wraps correctly
  random_number = generator->getRandomNumber();
  TEST_EQUALITY_CONST( random_number, 0.1 );
}

//---------------------------------------------------------------------------//
// end tstFakeGenerator.cpp
//---------------------------------------------------------------------------//
