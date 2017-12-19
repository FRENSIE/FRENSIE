//---------------------------------------------------------------------------//
//!
//! \file   tstFakeGenerator.cpp
//! \author Alex Robinson
//! \brief  Fake generator class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "Utility_FakeGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the fake stream returns the correct values
FRENSIE_UNIT_TEST( FakeGenerator, getRandomNumber )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.1;
  fake_stream[1] = 0.2;
  fake_stream[2] = 0.3;

  std::shared_ptr<Utility::LinearCongruentialGenerator>
    generator( new Utility::FakeGenerator( fake_stream ) );

  double random_number = generator->getRandomNumber();
  FRENSIE_CHECK_EQUAL( random_number, 0.1 );

  random_number = generator->getRandomNumber();
  FRENSIE_CHECK_EQUAL( random_number, 0.2 );

  random_number = generator->getRandomNumber();
  FRENSIE_CHECK_EQUAL( random_number, 0.3 );

  // Test that it wraps correctly
  random_number = generator->getRandomNumber();
  FRENSIE_CHECK_EQUAL( random_number, 0.1 );
}

//---------------------------------------------------------------------------//
// end tstFakeGenerator.cpp
//---------------------------------------------------------------------------//
