//---------------------------------------------------------------------------//
//!
//! \file   tstBremsstrahlungAdjointElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Bremsstrahlung adjoint electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_BremsstrahlungAdjointElectroatomicReaction.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointElectroatomicReaction>
    bremsstrahlung_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
TEUCHOS_UNIT_TEST( BremsstrahlungAdjointElectroatomicReaction, getReactionType )
{
  TEST_EQUALITY_CONST( bremsstrahlung_reaction->getReactionType(),
                 MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( BremsstrahlungAdjointElectroatomicReaction, getThresholdEnergy )
{
  TEST_EQUALITY_CONST( bremsstrahlung_reaction->getThresholdEnergy(), 1e-05 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( BremsstrahlungAdjointElectroatomicReaction, getNumberOfEmittedElectrons )
{
  TEST_EQUALITY_CONST( bremsstrahlung_reaction->getNumberOfEmittedElectrons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( bremsstrahlung_reaction->getNumberOfEmittedElectrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( BremsstrahlungAdjointElectroatomicReaction, getNumberOfEmittedPhotons )
{
  TEST_EQUALITY_CONST( bremsstrahlung_reaction->getNumberOfEmittedPhotons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( bremsstrahlung_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( BremsstrahlungAdjointElectroatomicReaction, getCrossSection )
{
  double cross_section = bremsstrahlung_reaction->getCrossSection( 1e-5 );
  TEST_FLOATING_EQUALITY( cross_section, 4.6329278793906738e+01, 1e-12 );

  cross_section = bremsstrahlung_reaction->getCrossSection( 2e-2 );
  TEST_FLOATING_EQUALITY( cross_section, 1.8802257008600090, 1e-12 );

  cross_section = bremsstrahlung_reaction->getCrossSection( 20.0 );
  TEST_FLOATING_EQUALITY( cross_section, 7.7114113565473230e-01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung reaction can be simulated
TEUCHOS_UNIT_TEST( BremsstrahlungAdjointElectroatomicReaction, react )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1e-5 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  bremsstrahlung_reaction->react( electron, bank, shell_of_interaction );

  TEST_ASSERT( electron.getEnergy() > 1e-5 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );
  TEST_ASSERT( bank.isEmpty() );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_native_file",
                   &test_native_file_name,
                   "Test Native file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create Native Reaction
  {
    // Get native data container
    Data::AdjointElectronPhotonRelaxationDataContainer data_container =
      Data::AdjointElectronPhotonRelaxationDataContainer( test_native_file_name );

    std::shared_ptr<const MonteCarlo::BremsstrahlungAdjointElectronScatteringDistribution>
        scattering_distribution;

    double evaluation_tol = 1e-7;

    MonteCarlo::BremsstrahlungAdjointElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LogLogLog,Utility::Correlated>(
        data_container,
        data_container.getAdjointElectronEnergyGrid(),
        scattering_distribution,
        evaluation_tol );

    // Get the energy grid
    Teuchos::ArrayRCP<double> energy_grid;
    energy_grid.assign(
        data_container.getAdjointElectronEnergyGrid().begin(),
        data_container.getAdjointElectronEnergyGrid().end() );

    // Get the cross section
    Teuchos::ArrayRCP<double> cross_section;
    cross_section.assign(
        data_container.getAdjointBremsstrahlungElectronCrossSection().begin(),
        data_container.getAdjointBremsstrahlungElectronCrossSection().end() );

    // Create the reaction
    bremsstrahlung_reaction.reset(
      new MonteCarlo::BremsstrahlungAdjointElectroatomicReaction<Utility::LinLin>(
        energy_grid,
        cross_section,
        data_container.getAdjointBremsstrahlungElectronCrossSectionThresholdEnergyIndex(),
        scattering_distribution ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstBremsstrahlungAdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
