//---------------------------------------------------------------------------//
//!
//! \file   tstElectroionizationSubshellAdjointElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Electroionization Subshell adjoint electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

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
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "MonteCarlo_AdjointElectronProbeState.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistribution>
    first_subshell_distribution, last_subshell_distribution;

std::shared_ptr<MonteCarlo::ElectroionizationSubshellAdjointElectroatomicReaction<Utility::LogLog> >
    first_subshell_reaction, last_subshell_reaction;

double max_ionization_subshell_adjoint_energy;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectroatomicReaction, getReactionType_ace )
{
  FRENSIE_CHECK_EQUAL( first_subshell_reaction->getReactionType(),
    MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( last_subshell_reaction->getReactionType(),
    MonteCarlo::L3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectroatomicReaction, getThresholdEnergy_ace )
{
  FRENSIE_CHECK_EQUAL( first_subshell_reaction->getThresholdEnergy(),
                       1e-5 );

  FRENSIE_CHECK_EQUAL( last_subshell_reaction->getThresholdEnergy(),
                       1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectroatomicReaction, getNumberOfEmittedAdjointElectrons_ace )
{
  FRENSIE_CHECK_EQUAL( first_subshell_reaction->getNumberOfEmittedAdjointElectrons(1e-3),
                       1u );

  FRENSIE_CHECK_EQUAL( first_subshell_reaction->getNumberOfEmittedAdjointElectrons(20.0),
                       1u );

  FRENSIE_CHECK_EQUAL( last_subshell_reaction->getNumberOfEmittedAdjointElectrons(1e-3),
                       1u );

  FRENSIE_CHECK_EQUAL( last_subshell_reaction->getNumberOfEmittedAdjointElectrons(20.0),
                       1u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectroatomicReaction, getNumberOfEmittedAdjointPhotons_ace )
{
  FRENSIE_CHECK_EQUAL( first_subshell_reaction->getNumberOfEmittedAdjointPhotons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( first_subshell_reaction->getNumberOfEmittedAdjointPhotons(20.0),
                       0u );

  FRENSIE_CHECK_EQUAL( last_subshell_reaction->getNumberOfEmittedAdjointPhotons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( last_subshell_reaction->getNumberOfEmittedAdjointPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectroatomicReaction, getNumberOfEmittedAdjointPositrons_ace )
{
  FRENSIE_CHECK_EQUAL( first_subshell_reaction->getNumberOfEmittedAdjointPositrons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( first_subshell_reaction->getNumberOfEmittedAdjointPositrons(20.0),
                       0u );

  FRENSIE_CHECK_EQUAL( last_subshell_reaction->getNumberOfEmittedAdjointPositrons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( last_subshell_reaction->getNumberOfEmittedAdjointPositrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectroatomicReaction, getCrossSection )
{
  // First Subshell
  double cross_section = first_subshell_reaction->getCrossSection( 1e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.009937675795411468e+08, 1e-12 );

  cross_section = first_subshell_reaction->getCrossSection( 1.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.091746694541046054e+04, 1e-12 );

  cross_section = first_subshell_reaction->getCrossSection( 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.249112208278187245e+04, 1e-12 );

  // Last Subshell
  cross_section = last_subshell_reaction->getCrossSection( 1e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.276666255195859070e+11, 1e-12 );

  cross_section = last_subshell_reaction->getCrossSection( 1.5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.144615009238008060e+05, 1e-12 );

  cross_section = last_subshell_reaction->getCrossSection( 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.073343380201322725e+05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the first_subshell reaction can be simulated
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectroatomicReaction, react )
{
  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( 20.0 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  first_subshell_reaction->react( adjoint_electron, bank, shell_of_interaction );

  FRENSIE_CHECK( adjoint_electron.getEnergy() > 20.0 );
  FRENSIE_CHECK( adjoint_electron.getZDirection() < 1.0 );
  FRENSIE_CHECK( bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::K_SUBSHELL );

  adjoint_electron.setWeight( 1.0 );
  adjoint_electron.setEnergy( 1e-5 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );

  first_subshell_reaction->react( adjoint_electron, bank, shell_of_interaction );

  FRENSIE_CHECK( adjoint_electron.getEnergy() > 1e-5 );
  FRENSIE_CHECK( adjoint_electron.getZDirection() < 1.0 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::K_SUBSHELL );

  FRENSIE_CHECK_EQUAL( bank.size(), 3 );

  double pdf = first_subshell_distribution->evaluate( 1e-5, 0.08 );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 0.08 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getWeight(), pdf, 1e-15 );

  bank.pop();

  pdf = first_subshell_distribution->evaluate(
                1e-5, Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getWeight(), pdf, 1e-15 );

  bank.pop();

  pdf = first_subshell_distribution->evaluate( 1e-5, 1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getWeight(), pdf, 1e-15 );

  bank.pop();

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Generate a probe with energy 1.0
  adjoint_electron.setWeight( 1.0 );
  adjoint_electron.setEnergy( 0.9 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );

  first_subshell_reaction->react( adjoint_electron,
                                  bank,
                                  shell_of_interaction );

  FRENSIE_CHECK_EQUAL( bank.size(), 1 );

  pdf = first_subshell_distribution->evaluate( 0.9, 1.0 );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getWeight(), pdf, 1e-15 );

  bank.pop();

  // Make sure that probes do not generate more probe particles
  MonteCarlo::AdjointElectronProbeState adjoint_electron_probe( 0 );
  adjoint_electron_probe.setEnergy( 0.3 );
  adjoint_electron_probe.setDirection( 0.0, 0.0, 1.0 );

  first_subshell_reaction->react( adjoint_electron_probe,
                                  bank,
                                  shell_of_interaction );

  FRENSIE_CHECK_EQUAL( bank.size(), 0 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_file",
                                        test_native_file_name, "",
                                        "Test Native file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
    // Create the native data file container
    std::shared_ptr<Data::AdjointElectronPhotonRelaxationDataContainer> data_container;
    data_container.reset( new Data::AdjointElectronPhotonRelaxationDataContainer(
                             test_native_file_name ) );

    // Extract the common electron energy grid
    std::shared_ptr<const std::vector<double> > energy_grid(
       new std::vector<double>( data_container->getAdjointElectronEnergyGrid() ) );

    // Create the hash-based grid searcher
    std::shared_ptr<Utility::HashBasedGridSearcher<double> > grid_searcher(
       new Utility::StandardHashBasedGridSearcher<std::vector<double>,false>(
                  energy_grid,
                  energy_grid->front(),
                  energy_grid->back(),
                  energy_grid->size()/10 + 1 ) );

  // Extract the subshell information
  std::set<unsigned> subshells = data_container->getSubshells();

  // Create the distribution for the first subshell
  {
    std::set<unsigned>::iterator shell = data_container->getSubshells().begin();

    // Convert subshell number to enum
    Data::SubshellType subshell_type =
      Data::convertENDFDesignatorToSubshellEnum( *shell );

    // Electroionization cross section
    std::shared_ptr<const std::vector<double> > subshell_cross_section(
       new std::vector<double>( data_container->getAdjointElectroionizationCrossSection( *shell ) ) );

    // Electroionization cross section threshold energy bin index
    size_t threshold_energy_index =
        data_container->getAdjointElectroionizationCrossSectionThresholdEnergyIndex(
        *shell );

    double evaluation_tol = 1e-7;

    // Create the electroionization subshell distribution
    MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<Utility::LogLogLog,Utility::UnitBaseCorrelated>(
        *data_container,
        *shell,
        data_container->getSubshellBindingEnergy( *shell ),
        first_subshell_distribution,
        evaluation_tol );

    // Add critical line energies
    std::shared_ptr<std::vector<double> >
      critical_line_energies( new std::vector<double>(3) );

    (*critical_line_energies)[0] = 0.08;
    (*critical_line_energies)[1] =
      Utility::PhysicalConstants::electron_rest_mass_energy;
    (*critical_line_energies)[2] = 1.0;

    first_subshell_distribution->setCriticalLineEnergies( critical_line_energies );


    // Create the subshell electroelectric reaction
    first_subshell_reaction.reset(
        new MonteCarlo::ElectroionizationSubshellAdjointElectroatomicReaction<Utility::LogLog, false>(
                energy_grid,
                subshell_cross_section,
                threshold_energy_index,
                grid_searcher,
                subshell_type,
                first_subshell_distribution ) );
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
    std::shared_ptr<const std::vector<double> > subshell_cross_section(
       new std::vector<double>( data_container->getAdjointElectroionizationCrossSection( *shell ) ) );

    double evaluation_tol = 1e-7;

    // Electroionization cross section threshold energy bin index
    size_t threshold_energy_index =
        data_container->getAdjointElectroionizationCrossSectionThresholdEnergyIndex(
        *shell );

    MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<Utility::LinLinLin,Utility::UnitBaseCorrelated>(
        *data_container,
        *shell,
        data_container->getSubshellBindingEnergy( *shell ),
        last_subshell_distribution,
        evaluation_tol );

    // Create the subshell electroelectric reaction
    last_subshell_reaction.reset(
        new MonteCarlo::ElectroionizationSubshellAdjointElectroatomicReaction<Utility::LogLog, false>(
                energy_grid,
                subshell_cross_section,
                threshold_energy_index,
                grid_searcher,
                subshell_type,
                last_subshell_distribution ) );

  }
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroionizationSubshellAdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
