//---------------------------------------------------------------------------//
//!
//! \file   tstDefaultPopulationController.cpp
//! \author Philip Britt
//! \brief  DefaultPopulationController test
//!
//---------------------------------------------------------------------------//

// std includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_PopulationControl.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "FRENSIE_config.hpp"
#include "ArchiveTestHelpers.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ParticleBank.hpp"

// Default population controller variable
std::shared_ptr<MonteCarlo::PopulationControl> default_population_controller;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// test that default population controller check doesn't do anything
FRENSIE_UNIT_TEST( DefaultPopulationController, checkParticleWithPopulationController_default )
{

  MonteCarlo::ParticleBank particle_bank;
  MonteCarlo::PhotonState photon(0);

  photon.setEnergy( 1.0 );
  photon.setTime( 6.67128190396304e-11 );
  photon.setWeight( 1.0 );

  default_population_controller->checkParticleWithPopulationController(photon, particle_bank);

  FRENSIE_CHECK(particle_bank.isEmpty());
  FRENSIE_CHECK(!photon.isGone());

}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{

  default_population_controller = MonteCarlo::PopulationControl::getDefault();

}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDefaultPopulationController.cpp
//---------------------------------------------------------------------------//
