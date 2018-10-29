//---------------------------------------------------------------------------//
//!
//! \file   tstCutoffElasticAdjointElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  CutoffElastic adjoint electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_CutoffElasticAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

typedef MonteCarlo::ElasticElectronScatteringDistributionNativeFactory
    NativeFactory;

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointElectroatomicReaction>
    elastic_reaction, cutoff_elastic_reaction;

std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
        cutoff_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( CutoffElasticAdjointElectroatomicReaction, getReactionType )
{
  FRENSIE_CHECK_EQUAL( elastic_reaction->getReactionType(),
                       MonteCarlo::CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( CutoffElasticAdjointElectroatomicReaction, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( elastic_reaction->getThresholdEnergy(),
                       1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( CutoffElasticAdjointElectroatomicReaction, getNumberOfEmittedAdjointElectrons )
{
  FRENSIE_CHECK_EQUAL( elastic_reaction->getNumberOfEmittedAdjointElectrons(1e-3),
                       1u );

  FRENSIE_CHECK_EQUAL( elastic_reaction->getNumberOfEmittedAdjointElectrons(20.0),
                       1u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( CutoffElasticAdjointElectroatomicReaction, getNumberOfEmittedAdjointPhotons )
{
  FRENSIE_CHECK_EQUAL( elastic_reaction->getNumberOfEmittedAdjointPhotons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( elastic_reaction->getNumberOfEmittedAdjointPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( CutoffElasticAdjointElectroatomicReaction, getNumberOfEmittedAdjointPositrons )
{
  FRENSIE_CHECK_EQUAL( elastic_reaction->getNumberOfEmittedAdjointPositrons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( elastic_reaction->getNumberOfEmittedAdjointPositrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( CutoffElasticAdjointElectroatomicReaction, getCrossSection )
{
  double cross_section = elastic_reaction->getCrossSection( 1.0E-05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.74896E+08, 1e-12 );

  cross_section = elastic_reaction->getCrossSection( 1.0E-03 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.804290802376420237e+06, 1e-12 );

  cross_section = elastic_reaction->getCrossSection( 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.0472762372903748E+02, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cutoff cross section can be returned
FRENSIE_UNIT_TEST( CutoffElasticAdjointElectroatomicReaction,
                   getCrossSection_cutoff )
{
  // cross section ratio for cutoff angle
  double ratio = cutoff_distribution->evaluateCutoffCrossSectionRatio( 1.0E-05 );
  double cross_section = cutoff_elastic_reaction->getCrossSection( 1.0E-05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.74896E+08*ratio, 1e-12 );

  ratio = cutoff_distribution->evaluateCutoffCrossSectionRatio( 1.0E-03 );
  cross_section = cutoff_elastic_reaction->getCrossSection( 1.0E-03 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.804290802376420237e+06*ratio, 1e-12 );

  ratio = cutoff_distribution->evaluateCutoffCrossSectionRatio( 20.0 );
  cross_section = cutoff_elastic_reaction->getCrossSection( 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.0472762372903748e+02*ratio, 1e-9 );
}


//---------------------------------------------------------------------------//
// Check that the elastic reaction can be simulated
FRENSIE_UNIT_TEST( CutoffElasticAdjointElectroatomicReaction, react )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 20.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  elastic_reaction->react( electron, bank, shell_of_interaction );

  FRENSIE_CHECK_EQUAL( electron.getEnergy(), 20.0 );
  FRENSIE_CHECK( electron.getZDirection() < 1.0 );
  FRENSIE_CHECK( electron.getZDirection() > 0.0 );
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
  // Get native data container
  std::shared_ptr<Data::AdjointElectronPhotonRelaxationDataContainer>
    data_container( new Data::AdjointElectronPhotonRelaxationDataContainer(
                             test_native_file_name ) );

  // Extract the energy grid and cross section
  std::shared_ptr<const std::vector<double> > energy_grid(
     new std::vector<double>( data_container->getAdjointElectronEnergyGrid() ) );

  std::shared_ptr<const std::vector<double> > elastic_cross_section(
     new std::vector<double>( data_container->getAdjointCutoffElasticCrossSection() ) );

  size_t elastic_threshold_index =
    data_container->getAdjointCutoffElasticCrossSectionThresholdEnergyIndex();

  std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
        elastic_scattering_distribution;

  // Create the full cutoff reaction
  {
    double cutoff_angle_cosine = 1.0;
    double evaluation_tol = 1e-15;

    // Create the distribution
    NativeFactory::createCutoffElasticDistribution<Utility::LogLogCosLog,Utility::Correlated>(
                elastic_scattering_distribution,
                *data_container,
                cutoff_angle_cosine,
                evaluation_tol );

    // Create the reaction
    elastic_reaction.reset(
      new MonteCarlo::CutoffElasticAdjointElectroatomicReaction<Utility::LogLog>(
                energy_grid,
                elastic_cross_section,
                elastic_threshold_index,
                elastic_scattering_distribution ) );
  }
  // Create the partial cutoff reaction
  {
    double cutoff_angle_cosine = 0.9;
    double evaluation_tol = 1e-7;

    std::shared_ptr<const std::vector<double> > cutoff_cross_section(
       new std::vector<double>( data_container->getAdjointCutoffElasticCrossSection() ) );

    // Create the distribution
    NativeFactory::createCutoffElasticDistribution<Utility::LogLogCosLog,Utility::Correlated>(
                cutoff_distribution,
                *data_container,
                cutoff_angle_cosine,
                evaluation_tol );

    // Create the reaction
    cutoff_elastic_reaction.reset(
      new MonteCarlo::CutoffElasticAdjointElectroatomicReaction<Utility::LogLog>(
                energy_grid,
                cutoff_cross_section,
                elastic_threshold_index,
                cutoff_distribution ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCutoffElasticAdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
