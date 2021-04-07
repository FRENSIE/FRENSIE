//---------------------------------------------------------------------------//
//!
//! \file   tstDecoupledElasticAdjointElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Decoupled Elastic electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_DecoupledElasticAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::DecoupledElasticAdjointElectroatomicReaction<Utility::LogLog> > decoupled_elastic_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( DecoupledElasticAdjointElectroatomicReaction, getReactionType )
{
  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getReactionType(),
                       MonteCarlo::DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( DecoupledElasticAdjointElectroatomicReaction, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getThresholdEnergy(),
                       1.0e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( DecoupledElasticAdjointElectroatomicReaction, getNumberOfEmittedAdjointElectrons )
{
  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getNumberOfEmittedAdjointElectrons(1e-3),
                       1u );

  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getNumberOfEmittedAdjointElectrons(20.0),
                       1u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( DecoupledElasticAdjointElectroatomicReaction, getNumberOfEmittedAdjointPhotons )
{
  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getNumberOfEmittedAdjointPhotons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getNumberOfEmittedAdjointPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( DecoupledElasticAdjointElectroatomicReaction, getNumberOfEmittedAdjointPositrons )
{
  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getNumberOfEmittedAdjointPositrons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getNumberOfEmittedAdjointPositrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the joint cross section can be returned
FRENSIE_UNIT_TEST( DecoupledElasticAdjointElectroatomicReaction,
                   getCrossSection )
{

  double cross_section = decoupled_elastic_reaction->getCrossSection( 1.0E-05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.74896E+08, 1e-12 );

  cross_section = decoupled_elastic_reaction->getCrossSection( 1.0E-03 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.804290802376420237e+06, 1e-12 );

  cross_section = decoupled_elastic_reaction->getCrossSection( 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.3022122514987041e+04, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the elastic reaction can be simulated
FRENSIE_UNIT_TEST( DecoupledElasticAdjointElectroatomicReaction, react )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 20.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  decoupled_elastic_reaction->react( electron, bank, shell_of_interaction );

  FRENSIE_CHECK_EQUAL( electron.getEnergy(), 20.0 );
  FRENSIE_CHECK( electron.getZDirection() < 1.0 );
  FRENSIE_CHECK( electron.getZDirection() > -1.0 );
  FRENSIE_CHECK( bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );


  // Set fake stream
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.0; // sample tabuar Cutoff distribution
  fake_stream[1] = 0.0; // sample mu = -1
  fake_stream[2] = 0.0; // sample the azimuthal angle
  fake_stream[3] = 0.0; // sample tabuar Cutoff distribution
  fake_stream[4] = 1.0-1e-15; // sample mu = 0.999999
  fake_stream[5] = 0.0; // sample the azimuthal angle
  fake_stream[6] = 1.0-1e-15; // sample analytical screened Rutherford distribution
  fake_stream[7] = 0.0; // sample mu = 0.999999
  fake_stream[8] = 0.0; // sample the azimuthal angle
  fake_stream[9] = 1.0-1e-15; // sample analytical screened Rutherford distribution
  fake_stream[10] = 1.0-1e-15; // sample mu = 1

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  electron.setDirection( 0.0, 0.0, 1.0 );
  decoupled_elastic_reaction->react( electron, bank, shell_of_interaction );

  FRENSIE_CHECK_EQUAL( electron.getEnergy(), 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(),
                          -1.0,
                          1e-15 );
  FRENSIE_CHECK( bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  electron.setDirection( 0.0, 0.0, 1.0 );
  decoupled_elastic_reaction->react( electron, bank, shell_of_interaction );

  FRENSIE_CHECK_EQUAL( electron.getEnergy(), 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(),
                          0.999999,
                          1e-15 );
  FRENSIE_CHECK( bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  electron.setDirection( 0.0, 0.0, 1.0 );
  decoupled_elastic_reaction->react( electron, bank, shell_of_interaction );

  FRENSIE_CHECK_EQUAL( electron.getEnergy(), 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(),
                          0.999999,
                          1e-15 );
  FRENSIE_CHECK( bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  electron.setDirection( 0.0, 0.0, 1.0 );
  decoupled_elastic_reaction->react( electron, bank, shell_of_interaction );

  FRENSIE_CHECK_EQUAL( electron.getEnergy(), 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(),
                          1.0,
                          1e-15 );
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
  // Create reaction
  {
    // Get native data container
    Data::AdjointElectronPhotonRelaxationDataContainer data_container =
        Data::AdjointElectronPhotonRelaxationDataContainer( test_native_file_name );

    double cutoff_angle_cosine = 0.999999;
    double evaluation_tol = 1e-7;

    // Get electron energy grid
    std::shared_ptr<const std::vector<double> > energy_grid(
       new std::vector<double>( data_container.getAdjointElectronEnergyGrid() ) );

    // Cutoff elastic cross section
    std::shared_ptr<const std::vector<double> > cutoff_cross_section(
       new std::vector<double>( data_container.getAdjointCutoffElasticCrossSection() ) );

    // Cutoff elastic cross section
    std::shared_ptr<const std::vector<double> > total_cross_section(
       new std::vector<double>( data_container.getAdjointTotalElasticCrossSection() ) );

    // Calculate the sampling ratios
    std::shared_ptr<std::vector<double> > sampling_ratios(
                      new std::vector<double>( total_cross_section->size() ) );

    for ( unsigned i = 0; i < sampling_ratios->size(); ++i )
    {
      (*sampling_ratios)[i] =
        (*cutoff_cross_section)[i]/(*total_cross_section)[i];
    }

    // Create cutoff distribution
    std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
        cutoff_elastic_distribution;
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LogLogCosLog,Utility::Correlated>(
        cutoff_elastic_distribution,
        data_container,
        cutoff_angle_cosine,
        evaluation_tol );

    // Create screened Rutherford distribution
    std::shared_ptr<const MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution>
        sr_elastic_distribution;
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createScreenedRutherfordElasticDistribution(
        sr_elastic_distribution,
        data_container.getAtomicNumber() );

    // Create the reaction
    decoupled_elastic_reaction.reset(
      new MonteCarlo::DecoupledElasticAdjointElectroatomicReaction<Utility::LogLog>(
            energy_grid,
            total_cross_section,
            sampling_ratios,
            data_container.getAdjointTotalElasticCrossSectionThresholdEnergyIndex(),
            cutoff_elastic_distribution,
            sr_elastic_distribution ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDecoupledElasticAdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
