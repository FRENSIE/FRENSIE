//---------------------------------------------------------------------------//
//!
//! \file   tstDirectionHelpers.cpp
//! \author Alex Robinson
//! \brief  Direction helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FACEMC Includes
#include "DirectionHelpers.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a direction is valid (lies on unit sphere)
TEUCHOS_UNIT_TEST( DirectionHelpers, validDirection )
{
  double direction[3] = {1.0, 1.0, 1.0};

  TEST_ASSERT( !FACEMC::validDirection( direction ) );

  direction[0] = 1.0/sqrt(3.0);
  direction[1] = 1.0/sqrt(3.0);
  direction[2] = 1.0/sqrt(3.0);

  std::cout << FACEMC::vectorMagnitude( direction ) << std::endl;

  TEST_ASSERT( FACEMC::validDirection( direction ) );
}

//---------------------------------------------------------------------------//
// Check that a direction can be normalized
TEUCHOS_UNIT_TEST( DirectionHelpers, normalizeDirection )
{
  double direction[3] = {1.0, 1.0, 1.0};

  FACEMC::normalizeDirection( direction );

  TEST_ASSERT( FACEMC::validDirection( direction ) );
}

//---------------------------------------------------------------------------//
// end tstDirectionHelpers.cpp
//---------------------------------------------------------------------------//
