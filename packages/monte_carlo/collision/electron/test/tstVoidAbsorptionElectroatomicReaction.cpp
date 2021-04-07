//---------------------------------------------------------------------------//
//!
//! \file   tstVoidAbsorptionElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Void absorption electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_VoidAbsorptionElectroatomicReaction.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::ElectroatomicReaction>
  void_absorption_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( VoidAbsorptionElectroatomicReaction, getReactionType )
{
  FRENSIE_CHECK_EQUAL( void_absorption_reaction->getReactionType(),
		       MonteCarlo::TOTAL_ABSORPTION_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( VoidAbsorptionElectroatomicReaction, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( void_absorption_reaction->getThresholdEnergy(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( VoidAbsorptionElectroatomicReaction, getNumberOfEmittedElectrons )
{
  FRENSIE_CHECK_EQUAL( void_absorption_reaction->getNumberOfEmittedElectrons(1e-5),
                       0u );

  FRENSIE_CHECK_EQUAL( void_absorption_reaction->getNumberOfEmittedElectrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( VoidAbsorptionElectroatomicReaction, getNumberOfEmittedPhotons )
{
  FRENSIE_CHECK_EQUAL( void_absorption_reaction->getNumberOfEmittedPhotons(1e-5),
                       0u );

  FRENSIE_CHECK_EQUAL( void_absorption_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( VoidAbsorptionElectroatomicReaction, getNumberOfEmittedPositrons )
{
  FRENSIE_CHECK_EQUAL( void_absorption_reaction->getNumberOfEmittedPositrons(1e-5),
                       0u );

  FRENSIE_CHECK_EQUAL( void_absorption_reaction->getNumberOfEmittedPositrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( VoidAbsorptionElectroatomicReaction, getCrossSection )
{
  double cross_section = void_absorption_reaction->getCrossSection( 1e-5 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = void_absorption_reaction->getCrossSection( 1.0 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = void_absorption_reaction->getCrossSection( 1e5 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the basic dipole bremsstrahlung reaction can be simulated
FRENSIE_UNIT_TEST( VoidAbsorptionElectroatomicReaction, react )
{
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 20 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  void_absorption_reaction->react( electron, bank, shell_of_interaction );

  FRENSIE_CHECK( electron.getEnergy() == 20.0 );
  FRENSIE_CHECK_EQUAL( electron.getZDirection(), 1.0 );
  FRENSIE_CHECK( bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the void absorption reaction
  void_absorption_reaction.reset(
             new MonteCarlo::VoidAbsorptionElectroatomicReaction() );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstVoidAbsorptionElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
