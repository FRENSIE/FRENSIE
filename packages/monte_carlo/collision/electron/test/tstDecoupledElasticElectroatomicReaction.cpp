//---------------------------------------------------------------------------//
//!
//! \file   tstDecoupledElasticElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Decoupled Elastic electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_DecoupledElasticElectroatomicReaction.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::DecoupledElasticElectroatomicReaction<Utility::LinLin> > decoupled_elastic_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( DecoupledElasticElectroatomicReaction, getReactionType )
{
  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getReactionType(),
                       MonteCarlo::DECOUPLED_ELASTIC_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( DecoupledElasticElectroatomicReaction, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getThresholdEnergy(),
                       1.0e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( DecoupledElasticElectroatomicReaction, getNumberOfEmittedElectrons )
{
  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getNumberOfEmittedElectrons(1e-3),
                       1u );

  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getNumberOfEmittedElectrons(20.0),
                       1u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( DecoupledElasticElectroatomicReaction, getNumberOfEmittedPhotons )
{
  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getNumberOfEmittedPhotons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( DecoupledElasticElectroatomicReaction, getNumberOfEmittedPositrons )
{
  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getNumberOfEmittedPositrons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getNumberOfEmittedPositrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the joint cross section can be returned
FRENSIE_UNIT_TEST( DecoupledElasticElectroatomicReaction,
                   getCrossSection )
{

  double cross_section = decoupled_elastic_reaction->getCrossSection( 1.0E-05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.74896E+08, 1e-12 );

  cross_section = decoupled_elastic_reaction->getCrossSection( 1.0E-03 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.80423E+06, 1e-12 );

  cross_section = decoupled_elastic_reaction->getCrossSection( 1.0E+05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.29871E+04, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the sampling ratio can be returned
FRENSIE_UNIT_TEST( DecoupledElasticElectroatomicReaction,
                   getSamplingRatio )
{

  double ratio = decoupled_elastic_reaction->getSamplingRatio( 1.0E-05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( ratio, 1.0, 1e-12 );

  ratio = decoupled_elastic_reaction->getSamplingRatio( 1.0E-03 );
  FRENSIE_CHECK_FLOATING_EQUALITY( ratio, 1.0, 1e-12 );

  ratio = decoupled_elastic_reaction->getSamplingRatio( 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( ratio, 7.7548919965521235e-01, 1e-12 );

  ratio = decoupled_elastic_reaction->getSamplingRatio( 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( ratio, 7.7548919965521235e-01, 1e-12 );

  ratio = decoupled_elastic_reaction->getSamplingRatio( 1.0E+05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( ratio, 1.0100484326755011e-09, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the elastic reaction can be simulated
FRENSIE_UNIT_TEST( DecoupledElasticElectroatomicReaction, react )
{
  MonteCarlo::ElectronState electron( 0 );
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
    Data::ElectronPhotonRelaxationDataContainer data_container =
        Data::ElectronPhotonRelaxationDataContainer( test_native_file_name );

    double cutoff_angle_cosine = 0.999999;
    double evaluation_tol = 1e-7;

    // Get electron energy grid
    std::shared_ptr<const std::vector<double> > energy_grid(
           new std::vector<double>( data_container.getElectronEnergyGrid() ) );

    // Cutoff elastic cross section
    std::shared_ptr<const std::vector<double> > cutoff_cross_section(
       new std::vector<double>( data_container.getCutoffElasticCrossSection() ) );

    // Cutoff elastic cross section
    std::shared_ptr<const std::vector<double> > total_cross_section(
       new std::vector<double>( data_container.getTotalElasticCrossSection() ) );

    // Create cutoff distribution
    std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
        cutoff_elastic_distribution;
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LinLinLog,Utility::Correlated>(
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
      new MonteCarlo::DecoupledElasticElectroatomicReaction<Utility::LinLin>(
            energy_grid,
            total_cross_section,
            cutoff_cross_section,
            data_container.getTotalElasticCrossSectionThresholdEnergyIndex(),
            cutoff_elastic_distribution,
            sr_elastic_distribution ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDecoupledElasticElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
