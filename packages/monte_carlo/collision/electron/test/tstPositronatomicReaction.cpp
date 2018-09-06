//---------------------------------------------------------------------------//
//!
//! \file   tstPositronatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Positron-atomic reaction base class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_PositronatomicReaction.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that positrons can be annihilated
FRENSIE_UNIT_TEST( PositronatomicReaction, producesAnnihilationPhotons )
{
  MonteCarlo::PositronState positron( 0 );
  positron.setEnergy(20.0);
  positron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  MonteCarlo::PositronatomicReaction::producesAnnihilationPhotons( positron, bank );

  // Test the positron
  FRENSIE_CHECK( !positron.isGone() );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getXDirection(), 0.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getYDirection(), 0.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK( !bank.isEmpty() );

  // Test the first photon
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::PHOTON );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(),
                          positron.getRestMassEnergy(), 1e-12 );
  FRENSIE_CHECK_EQUAL( bank.top().getZDirection(), 0.0 );
  double x_direction = bank.top().getXDirection();
  double y_direction = bank.top().getYDirection();

  // Remove the first photon
  bank.pop();
  FRENSIE_CHECK( !bank.isEmpty() );

  // Test the second photon
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::PHOTON );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(),
                          positron.getRestMassEnergy(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getXDirection(), -x_direction, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getYDirection(), -y_direction, 1e-12 );
  FRENSIE_CHECK_EQUAL( bank.top().getZDirection(), 0.0 );

  // Remove the second photon
  bank.pop();
  FRENSIE_CHECK( bank.isEmpty() );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPositronatomicReaction.cpp
//---------------------------------------------------------------------------//
