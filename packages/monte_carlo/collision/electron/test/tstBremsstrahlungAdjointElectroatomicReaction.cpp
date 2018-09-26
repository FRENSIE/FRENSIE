//---------------------------------------------------------------------------//
//!
//! \file   tstBremsstrahlungAdjointElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Bremsstrahlung adjoint electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_BremsstrahlungAdjointElectroatomicReaction.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointElectroatomicReaction>
    bremsstrahlung_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( BremsstrahlungAdjointElectroatomicReaction, getReactionType )
{
  FRENSIE_CHECK_EQUAL( bremsstrahlung_reaction->getReactionType(),
                 MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( BremsstrahlungAdjointElectroatomicReaction, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( bremsstrahlung_reaction->getThresholdEnergy(), 1e-05 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( BremsstrahlungAdjointElectroatomicReaction, getNumberOfEmittedAdjointElectrons )
{
  FRENSIE_CHECK_EQUAL( bremsstrahlung_reaction->getNumberOfEmittedAdjointElectrons(1e-3),
                       1u );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_reaction->getNumberOfEmittedAdjointElectrons(20.0),
                       1u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( BremsstrahlungAdjointElectroatomicReaction, getNumberOfEmittedAdjointPhotons )
{
  FRENSIE_CHECK_EQUAL( bremsstrahlung_reaction->getNumberOfEmittedAdjointPhotons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_reaction->getNumberOfEmittedAdjointPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( BremsstrahlungAdjointElectroatomicReaction, getNumberOfEmittedAdjointPositrons )
{
  FRENSIE_CHECK_EQUAL( bremsstrahlung_reaction->getNumberOfEmittedAdjointPositrons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_reaction->getNumberOfEmittedAdjointPositrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( BremsstrahlungAdjointElectroatomicReaction, getCrossSection )
{
  double cross_section = bremsstrahlung_reaction->getCrossSection( 1e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.980092756766359940e+01, 1e-12 );

  cross_section = bremsstrahlung_reaction->getCrossSection( 2e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.490273650787403259, 1e-12 );

  cross_section = bremsstrahlung_reaction->getCrossSection( 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.497134894717789044e-01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung reaction can be simulated
FRENSIE_UNIT_TEST( BremsstrahlungAdjointElectroatomicReaction, react )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1e-5 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  bremsstrahlung_reaction->react( electron, bank, shell_of_interaction );

  FRENSIE_CHECK( electron.getEnergy() > 1e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK( bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
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
  // Create Native Reaction
  {
    // Get native data container
    Data::AdjointElectronPhotonRelaxationDataContainer data_container =
      Data::AdjointElectronPhotonRelaxationDataContainer( test_native_file_name );

    std::shared_ptr<const MonteCarlo::BremsstrahlungAdjointElectronScatteringDistribution>
        scattering_distribution;

    double evaluation_tol = 1e-7;

    MonteCarlo::BremsstrahlungAdjointElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LogLogLog,Utility::UnitBaseCorrelated>(
        data_container,
        data_container.getAdjointElectronEnergyGrid(),
        scattering_distribution,
        evaluation_tol );

    // Get the energy grid
    std::shared_ptr<const std::vector<double> > energy_grid(
       new std::vector<double>( data_container.getAdjointElectronEnergyGrid() ) );

    // Get the cross section
    std::shared_ptr<const std::vector<double> > cross_section(
       new std::vector<double>( data_container.getAdjointBremsstrahlungElectronCrossSection() ) );

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

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstBremsstrahlungAdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
