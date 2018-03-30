//---------------------------------------------------------------------------//
//!
//! \file   tstPositronatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Positron-atomic reaction base class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PositronatomicReaction.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that positrons can be annihilated
TEUCHOS_UNIT_TEST( PositronatomicReaction, producesAnnihilationPhotons )
{
  MonteCarlo::PositronState positron( 0 );
  positron.setEnergy(20.0);
  positron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  MonteCarlo::PositronatomicReaction::producesAnnihilationPhotons( positron, bank );

  // Test the positron
  TEST_ASSERT( !positron.isGone() );
  TEST_FLOATING_EQUALITY( positron.getEnergy(), 20.0, 1e-12 );
  TEST_FLOATING_EQUALITY( positron.getXDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( positron.getYDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( positron.getZDirection(), 1.0, 1e-12 );
  TEST_ASSERT( !bank.isEmpty() );

  // Test the first photon
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(),
                          positron.getRestMassEnergy(), 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getZDirection(), 0.0 );
  double x_direction = bank.top().getXDirection();
  double y_direction = bank.top().getYDirection();

  // Remove the first photon
  bank.pop();
  TEST_ASSERT( !bank.isEmpty() );

  // Test the second photon
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(),
                          positron.getRestMassEnergy(), 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getXDirection(), -x_direction, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getYDirection(), -y_direction, 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getZDirection(), 0.0 );

  // Remove the second photon
  bank.pop();
  TEST_ASSERT( bank.isEmpty() );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPositronatomicReaction.cpp
//---------------------------------------------------------------------------//
