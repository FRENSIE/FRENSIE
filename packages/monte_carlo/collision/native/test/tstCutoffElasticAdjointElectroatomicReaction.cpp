//---------------------------------------------------------------------------//
//!
//! \file   tstCutoffElasticAdjointElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  CutoffElastic adjoint electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_CutoffElasticAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_RandomNumberGenerator.hpp"

typedef MonteCarlo::ElasticElectronScatteringDistributionNativeFactory 
    NativeFactory;

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointElectroatomicReaction>
    elastic_reaction, cutoff_elastic_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
TEUCHOS_UNIT_TEST( CutoffElasticAdjointElectroatomicReaction, getReactionType )
{
  TEST_EQUALITY_CONST( elastic_reaction->getReactionType(),
                       MonteCarlo::CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( CutoffElasticAdjointElectroatomicReaction, getThresholdEnergy )
{
  TEST_EQUALITY_CONST( elastic_reaction->getThresholdEnergy(),
                       1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( CutoffElasticAdjointElectroatomicReaction, getNumberOfEmittedElectrons )
{
  TEST_EQUALITY_CONST( elastic_reaction->getNumberOfEmittedElectrons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( elastic_reaction->getNumberOfEmittedElectrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( CutoffElasticAdjointElectroatomicReaction, getNumberOfEmittedPhotons )
{
  TEST_EQUALITY_CONST( elastic_reaction->getNumberOfEmittedPhotons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( elastic_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( CutoffElasticAdjointElectroatomicReaction, getCrossSection )
{
  double cross_section =
    elastic_reaction->getCrossSection( 1.0E-05 );

  TEST_FLOATING_EQUALITY( cross_section, 2.74896E+08, 1e-12 );

  cross_section =
    elastic_reaction->getCrossSection( 1.0E-03 );

  TEST_FLOATING_EQUALITY( cross_section, 2.80490481543817E+06, 1e-12 );

  cross_section =
    elastic_reaction->getCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 3.04727623729037E+02, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cutoff cross section can be returned
TEUCHOS_UNIT_TEST( CutoffElasticAdjointElectroatomicReaction,
                   getCrossSection_cutoff )
{
  // cross section ratio for cutoff angle
  double ratio = 9.50000475000238E-01;

  double cross_section =
    cutoff_elastic_reaction->getCrossSection( 1.0E-05 );

  TEST_FLOATING_EQUALITY( cross_section, 2.74896E+08*ratio, 1e-12 );

  ratio = 1.08953394168692E-01;
  cross_section =
    cutoff_elastic_reaction->getCrossSection( 1.0E-03 );

  TEST_FLOATING_EQUALITY( cross_section, 2.80490481543817E+06*ratio, 1e-12 );

  ratio = 8.2702774720157165e-06;
  cross_section =
    cutoff_elastic_reaction->getCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 3.04727623729037E+02*ratio, 1e-9 );
}


//---------------------------------------------------------------------------//
// Check that the elastic reaction can be simulated
TEUCHOS_UNIT_TEST( CutoffElasticAdjointElectroatomicReaction, react )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 20.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  elastic_reaction->react( electron, bank, shell_of_interaction );

  TEST_EQUALITY_CONST( electron.getEnergy(), 20.0 );
  TEST_ASSERT( electron.getZDirection() < 1.0 );
  TEST_ASSERT( electron.getZDirection() > 0.0 );
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
  // Get native data container
  std::shared_ptr<Data::AdjointElectronPhotonRelaxationDataContainer> 
    data_container( new Data::AdjointElectronPhotonRelaxationDataContainer(
                             test_native_file_name ) );

  // Extract the energy grid and cross section
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign(
        data_container->getAdjointElectronEnergyGrid().begin(),
        data_container->getAdjointElectronEnergyGrid().end() );

  Teuchos::ArrayRCP<double> elastic_cross_section;
  elastic_cross_section.assign(
        data_container->getAdjointCutoffElasticCrossSection().begin(),
        data_container->getAdjointCutoffElasticCrossSection().end() );

  unsigned elastic_threshold_index =
      data_container->getAdjointCutoffElasticCrossSectionThresholdEnergyIndex();

  // Create the full cutoff reaction
  {
    double cutoff_angle_cosine = 1.0;
    double evaluation_tol = 1e-7;
    bool correlated_sampling_mode_on = true;

    // Create the distribution
    std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
        elastic_scattering_distribution;

    NativeFactory::createCutoffElasticDistribution(
        elastic_scattering_distribution,
        *data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );

    // Create the reaction
    elastic_reaction.reset(
      new MonteCarlo::CutoffElasticAdjointElectroatomicReaction<Utility::LinLin>(
                energy_grid,
                elastic_cross_section,
                elastic_threshold_index,
                elastic_scattering_distribution ) );
  }
  // Create the partial cutoff reaction
  {
    double cutoff_angle_cosine = 0.9;
    double evaluation_tol = 1e-7;
    bool correlated_sampling_mode_on = true;

    // Create the distribution
    std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
        elastic_scattering_distribution;

    NativeFactory::createCutoffElasticDistribution(
        elastic_scattering_distribution,
        *data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );

    // Create the reaction
    cutoff_elastic_reaction.reset(
      new MonteCarlo::CutoffElasticAdjointElectroatomicReaction<Utility::LinLin>(
                energy_grid,
                elastic_cross_section,
                elastic_threshold_index,
                elastic_scattering_distribution ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCutoffElasticAdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
