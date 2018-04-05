//---------------------------------------------------------------------------//
//!
//! \file   tstVoidAbsorptionElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Void absorption electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_VoidAbsorptionElectroatomicReaction.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::ElectroatomicReaction>
  void_absorption_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
TEUCHOS_UNIT_TEST( VoidAbsorptionElectroatomicReaction, getReactionType )
{
  TEST_EQUALITY_CONST( void_absorption_reaction->getReactionType(),
		       MonteCarlo::TOTAL_ABSORPTION_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( VoidAbsorptionElectroatomicReaction, getThresholdEnergy )
{
  TEST_EQUALITY_CONST( void_absorption_reaction->getThresholdEnergy(), 1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( VoidAbsorptionElectroatomicReaction, getNumberOfEmittedElectrons )
{
  TEST_EQUALITY_CONST( void_absorption_reaction->getNumberOfEmittedElectrons(1e-5),
                       0u );

  TEST_EQUALITY_CONST( void_absorption_reaction->getNumberOfEmittedElectrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( VoidAbsorptionElectroatomicReaction, getNumberOfEmittedPhotons )
{
  TEST_EQUALITY_CONST( void_absorption_reaction->getNumberOfEmittedPhotons(1e-5),
                       0u );

  TEST_EQUALITY_CONST( void_absorption_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( VoidAbsorptionElectroatomicReaction, getCrossSection )
{
  double cross_section = void_absorption_reaction->getCrossSection( 1e-5 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = void_absorption_reaction->getCrossSection( 1.0 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = void_absorption_reaction->getCrossSection( 1e5 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the basic dipole bremsstrahlung reaction can be simulated
TEUCHOS_UNIT_TEST( VoidAbsorptionElectroatomicReaction, react )
{
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 20 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  void_absorption_reaction->react( electron, bank, shell_of_interaction );

  TEST_ASSERT( electron.getEnergy() == 20.0 );
  TEST_EQUALITY_CONST( electron.getZDirection(), 1.0 );
  TEST_ASSERT( bank.isEmpty() );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create the void absorption reaction
  void_absorption_reaction.reset(
             new MonteCarlo::VoidAbsorptionElectroatomicReaction() );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstVoidAbsorptionElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
