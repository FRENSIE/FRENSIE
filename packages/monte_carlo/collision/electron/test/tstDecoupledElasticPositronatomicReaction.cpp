//---------------------------------------------------------------------------//
//!
//! \file   tstDecoupledElasticPositronatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Decoupled Elastic positron-atomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_DecoupledElasticPositronatomicReaction.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::DecoupledElasticPositronatomicReaction<Utility::LinLin> > decoupled_elastic_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( DecoupledElasticPositronatomicReaction, getReactionType )
{
  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getReactionType(),
                       MonteCarlo::DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( DecoupledElasticPositronatomicReaction, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getThresholdEnergy(),
                       1.0e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( DecoupledElasticPositronatomicReaction, getNumberOfEmittedElectrons )
{
  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getNumberOfEmittedElectrons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getNumberOfEmittedElectrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( DecoupledElasticPositronatomicReaction, getNumberOfEmittedPhotons )
{
  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getNumberOfEmittedPhotons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( DecoupledElasticPositronatomicReaction, getNumberOfEmittedPositrons )
{
  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getNumberOfEmittedPositrons(1e-3),
                       1u );

  FRENSIE_CHECK_EQUAL( decoupled_elastic_reaction->getNumberOfEmittedPositrons(20.0),
                       1u );
}

//---------------------------------------------------------------------------//
// Check that the joint cross section can be returned
FRENSIE_UNIT_TEST( DecoupledElasticPositronatomicReaction,
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
// Check that the elastic reaction can be simulated
FRENSIE_UNIT_TEST( DecoupledElasticPositronatomicReaction, react )
{
  MonteCarlo::PositronState positron( 0 );
  positron.setEnergy( 20.0 );
  positron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  decoupled_elastic_reaction->react( positron, bank, shell_of_interaction );

  FRENSIE_CHECK_EQUAL( positron.getEnergy(), 20.0 );
  FRENSIE_CHECK( positron.getZDirection() < 1.0 );
  FRENSIE_CHECK( positron.getZDirection() > -1.0 );
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

  positron.setDirection( 0.0, 0.0, 1.0 );
  decoupled_elastic_reaction->react( positron, bank, shell_of_interaction );

  FRENSIE_CHECK_EQUAL( positron.getEnergy(), 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(),
                          -1.0,
                          1e-15 );
  FRENSIE_CHECK( bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  positron.setDirection( 0.0, 0.0, 1.0 );
  decoupled_elastic_reaction->react( positron, bank, shell_of_interaction );

  FRENSIE_CHECK_EQUAL( positron.getEnergy(), 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(),
                          0.999999,
                          1e-15 );
  FRENSIE_CHECK( bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  positron.setDirection( 0.0, 0.0, 1.0 );
  decoupled_elastic_reaction->react( positron, bank, shell_of_interaction );

  FRENSIE_CHECK_EQUAL( positron.getEnergy(), 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(),
                          0.999999,
                          1e-15 );
  FRENSIE_CHECK( bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  positron.setDirection( 0.0, 0.0, 1.0 );
  decoupled_elastic_reaction->react( positron, bank, shell_of_interaction );

  FRENSIE_CHECK_EQUAL( positron.getEnergy(), 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(),
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
      new MonteCarlo::DecoupledElasticPositronatomicReaction<Utility::LinLin>(
            energy_grid,
            total_cross_section,
            sampling_ratios,
            data_container.getTotalElasticCrossSectionThresholdEnergyIndex(),
            cutoff_elastic_distribution,
            sr_elastic_distribution ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDecoupledElasticPositronatomicReaction.cpp
//---------------------------------------------------------------------------//
