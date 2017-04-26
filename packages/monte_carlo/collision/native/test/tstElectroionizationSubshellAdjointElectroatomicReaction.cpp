//---------------------------------------------------------------------------//
//!
//! \file   tstElectroionizationSubshellAdjointElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Electroionization Subshell adjoint electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_AdjointElectroatomicReactionType.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Data_SubshellType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::ElectroionizationSubshellAdjointElectroatomicReaction<Utility::LinLin> >
    first_subshell_reaction, last_subshell_reaction;

double max_ionization_subshell_adjoint_energy;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
TEUCHOS_UNIT_TEST( ElectroionizationSubshellAdjointElectroatomicReaction, getReactionType_ace )
{
  TEST_EQUALITY_CONST( first_subshell_reaction->getReactionType(),
    MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( last_subshell_reaction->getReactionType(),
    MonteCarlo::L3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( ElectroionizationSubshellAdjointElectroatomicReaction, getThresholdEnergy_ace )
{
  TEST_EQUALITY_CONST( first_subshell_reaction->getThresholdEnergy(),
                       1e-5 );

  TEST_EQUALITY_CONST( last_subshell_reaction->getThresholdEnergy(),
                       1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( ElectroionizationSubshellAdjointElectroatomicReaction, getNumberOfEmittedElectrons_ace )
{
  TEST_EQUALITY_CONST( first_subshell_reaction->getNumberOfEmittedElectrons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( first_subshell_reaction->getNumberOfEmittedElectrons(20.0),
                       0u );

  TEST_EQUALITY_CONST( last_subshell_reaction->getNumberOfEmittedElectrons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( last_subshell_reaction->getNumberOfEmittedElectrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( ElectroionizationSubshellAdjointElectroatomicReaction, getNumberOfEmittedPhotons_ace )
{
  TEST_EQUALITY_CONST( first_subshell_reaction->getNumberOfEmittedPhotons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( first_subshell_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );

  TEST_EQUALITY_CONST( last_subshell_reaction->getNumberOfEmittedPhotons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( last_subshell_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( ElectroionizationSubshellAdjointElectroatomicReaction, getCrossSection )
{
  // First Subshell
  double cross_section = first_subshell_reaction->getCrossSection( 1e-5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.7938377467756383e+09, 1e-12 );

  cross_section = first_subshell_reaction->getCrossSection( 1.5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.2270796221648970e+04, 1e-12 );

  cross_section = first_subshell_reaction->getCrossSection( 20.0 );
  TEST_FLOATING_EQUALITY( cross_section, 1.9076048247978626e+04, 1e-12 );

  // Last Subshell
  cross_section = last_subshell_reaction->getCrossSection( 1e-5 );
  TEST_FLOATING_EQUALITY( cross_section, 2.0962782769350122e+11, 1e-12 );

  cross_section = last_subshell_reaction->getCrossSection( 1.5 );
  TEST_FLOATING_EQUALITY( cross_section, 5.6144661069777433e+05, 1e-12 );

  cross_section = last_subshell_reaction->getCrossSection( 20.0 );
  TEST_FLOATING_EQUALITY( cross_section, 1.4157750803045169e+05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the first_subshell reaction can be simulated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellAdjointElectroatomicReaction, react )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 20.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  first_subshell_reaction->react( electron, bank, shell_of_interaction );

  TEST_ASSERT( electron.getEnergy() > 20.0 );
  TEST_ASSERT( electron.getZDirection() < 1.0 );
  TEST_ASSERT( bank.isEmpty() );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::K_SUBSHELL );
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
    // Create the native data file container
    std::shared_ptr<Data::AdjointElectronPhotonRelaxationDataContainer> data_container;
    data_container.reset( new Data::AdjointElectronPhotonRelaxationDataContainer(
                             test_native_file_name ) );

    // Extract the common electron energy grid
    Teuchos::ArrayRCP<double> energy_grid;
    energy_grid.assign(
      data_container->getAdjointElectronEnergyGrid().begin(),
      data_container->getAdjointElectronEnergyGrid().end() );

    // Create the hash-based grid searcher
    Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
        new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
                  energy_grid,
                  energy_grid[0],
                  energy_grid[energy_grid.size()-1],
                  energy_grid.size()/10 + 1 ) );

  // Extract the subshell information
  std::set<unsigned> subshells = data_container->getSubshells();

  // Create the distribution for the first subshell
  {
  std::set<unsigned>::iterator shell = data_container->getSubshells().begin();

    // Convert subshell number to enum
    Data::SubshellType subshell_type =
      Data::convertENDFDesignatorToSubshellEnum( *shell );

    // Electroionization cross section
    Teuchos::ArrayRCP<double> subshell_cross_section;
    subshell_cross_section.assign(
        data_container->getAdjointElectroionizationCrossSection( *shell ).begin(),
        data_container->getAdjointElectroionizationCrossSection( *shell ).end() );

    // Electroionization cross section threshold energy bin index
    unsigned threshold_energy_index =
        data_container->getAdjointElectroionizationCrossSectionThresholdEnergyIndex(
        *shell );

    // The electroionization subshell distribution
    std::shared_ptr<const MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistribution>
        electroionization_subshell_distribution;

    bool correlated_sampling_mode_on = true;
    bool unit_based_interpolation_mode_on = true;
    double evaluation_tol = 1e-7;

    // Create the electroionization subshell distribution
    MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<Utility::LinLinLog>(
        *data_container,
        *shell,
        data_container->getSubshellBindingEnergy( *shell ),
        electroionization_subshell_distribution,
        correlated_sampling_mode_on,
        unit_based_interpolation_mode_on,
        evaluation_tol );


    // Create the subshell electroelectric reaction
    first_subshell_reaction.reset(
        new MonteCarlo::ElectroionizationSubshellAdjointElectroatomicReaction<Utility::LinLin, false>(
                energy_grid,
                subshell_cross_section,
                threshold_energy_index,
                grid_searcher,
                subshell_type,
                electroionization_subshell_distribution ) );
  }

  // Create the distribution for the last subshell
  {
  // For the last subshell
  std::set<unsigned>::iterator shell = data_container->getSubshells().end();
  --shell;

    // Convert subshell number to enum
    Data::SubshellType subshell_type =
      Data::convertENDFDesignatorToSubshellEnum( *shell );

    // Electroionization cross section
    Teuchos::ArrayRCP<double> subshell_cross_section;
    subshell_cross_section.assign(
        data_container->getAdjointElectroionizationCrossSection( *shell ).begin(),
        data_container->getAdjointElectroionizationCrossSection( *shell ).end() );

    bool correlated_sampling_mode_on = true;
    bool unit_based_interpolation_mode_on = true;
    double evaluation_tol = 1e-7;

    // Electroionization cross section threshold energy bin index
    unsigned threshold_energy_index =
        data_container->getAdjointElectroionizationCrossSectionThresholdEnergyIndex(
        *shell );

    // The electroionization subshell distribution
    std::shared_ptr<const MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistribution>
        electroionization_subshell_distribution;

    MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<Utility::LinLinLog>(
        *data_container,
        *shell,
        data_container->getSubshellBindingEnergy( *shell ),
        electroionization_subshell_distribution,
        correlated_sampling_mode_on,
        unit_based_interpolation_mode_on,
        evaluation_tol );

    // Create the subshell electroelectric reaction
    last_subshell_reaction.reset(
        new MonteCarlo::ElectroionizationSubshellAdjointElectroatomicReaction<Utility::LinLin, false>(
                energy_grid,
                subshell_cross_section,
                threshold_energy_index,
                grid_searcher,
                subshell_type,
                electroionization_subshell_distribution ) );

  }
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroionizationSubshellAdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
