//---------------------------------------------------------------------------//
//!
//! \file   tstDecoupledElasticPositronatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Decoupled Elastic positron-atomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_DecoupledElasticPositronatomicReaction.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_TabularDistribution.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::DecoupledElasticPositronatomicReaction<Utility::LinLin> > decoupled_elastic_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
TEUCHOS_UNIT_TEST( DecoupledElasticPositronatomicReaction, getReactionType )
{
  TEST_EQUALITY_CONST( decoupled_elastic_reaction->getReactionType(),
                       MonteCarlo::DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( DecoupledElasticPositronatomicReaction, getThresholdEnergy )
{
  TEST_EQUALITY_CONST( decoupled_elastic_reaction->getThresholdEnergy(),
                       1.0e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( DecoupledElasticPositronatomicReaction, getNumberOfEmittedElectrons )
{
  TEST_EQUALITY_CONST( decoupled_elastic_reaction->getNumberOfEmittedElectrons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( decoupled_elastic_reaction->getNumberOfEmittedElectrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( DecoupledElasticPositronatomicReaction, getNumberOfEmittedPhotons )
{
  TEST_EQUALITY_CONST( decoupled_elastic_reaction->getNumberOfEmittedPhotons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( decoupled_elastic_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the joint cross section can be returned
TEUCHOS_UNIT_TEST( DecoupledElasticPositronatomicReaction,
                   getCrossSection )
{

  double cross_section = decoupled_elastic_reaction->getCrossSection( 1.0E-05 );
  TEST_FLOATING_EQUALITY( cross_section, 2.74896E+08, 1e-12 );

  cross_section = decoupled_elastic_reaction->getCrossSection( 1.0E-03 );
  TEST_FLOATING_EQUALITY( cross_section, 2.80423E+06, 1e-12 );

  cross_section = decoupled_elastic_reaction->getCrossSection( 1.0E+05 );
  TEST_FLOATING_EQUALITY( cross_section, 1.29871E+04, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the elastic reaction can be simulated
TEUCHOS_UNIT_TEST( DecoupledElasticPositronatomicReaction, react )
{
  MonteCarlo::PositronState positron( 0 );
  positron.setEnergy( 20.0 );
  positron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  decoupled_elastic_reaction->react( positron, bank, shell_of_interaction );

  TEST_EQUALITY_CONST( positron.getEnergy(), 20.0 );
  TEST_ASSERT( positron.getZDirection() < 1.0 );
  TEST_ASSERT( positron.getZDirection() > -1.0 );
  TEST_ASSERT( bank.isEmpty() );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::UNKNOWN_SUBSHELL );


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

  TEST_EQUALITY_CONST( positron.getEnergy(), 20.0 );
  TEST_FLOATING_EQUALITY( positron.getZDirection(),
                          -1.0,
                          1e-15 );
  TEST_ASSERT( bank.isEmpty() );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  positron.setDirection( 0.0, 0.0, 1.0 );
  decoupled_elastic_reaction->react( positron, bank, shell_of_interaction );

  TEST_EQUALITY_CONST( positron.getEnergy(), 20.0 );
  TEST_FLOATING_EQUALITY( positron.getZDirection(),
                          0.999999,
                          1e-15 );
  TEST_ASSERT( bank.isEmpty() );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  positron.setDirection( 0.0, 0.0, 1.0 );
  decoupled_elastic_reaction->react( positron, bank, shell_of_interaction );

  TEST_EQUALITY_CONST( positron.getEnergy(), 20.0 );
  TEST_FLOATING_EQUALITY( positron.getZDirection(),
                          0.999999,
                          1e-15 );
  TEST_ASSERT( bank.isEmpty() );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  positron.setDirection( 0.0, 0.0, 1.0 );
  decoupled_elastic_reaction->react( positron, bank, shell_of_interaction );

  TEST_EQUALITY_CONST( positron.getEnergy(), 20.0 );
  TEST_FLOATING_EQUALITY( positron.getZDirection(),
                          1.0,
                          1e-15 );
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
  // Create reaction
  {
    // Get native data container
    Data::ElectronPhotonRelaxationDataContainer data_container =
        Data::ElectronPhotonRelaxationDataContainer( test_native_file_name );

    double cutoff_angle_cosine = 0.999999;
    double evaluation_tol = 1e-7;

    // Get electron energy grid
    Teuchos::ArrayRCP<double> energy_grid;
    energy_grid.assign(
        data_container.getElectronEnergyGrid().begin(),
        data_container.getElectronEnergyGrid().end() );

    // Cutoff elastic cross section
    Teuchos::ArrayRCP<double> cutoff_cross_section;
    cutoff_cross_section.assign(
        data_container.getCutoffElasticCrossSection().begin(),
        data_container.getCutoffElasticCrossSection().end() );

    // Cutoff elastic cross section
    Teuchos::ArrayRCP<double> total_cross_section;
    total_cross_section.assign(
        data_container.getTotalElasticCrossSection().begin(),
        data_container.getTotalElasticCrossSection().end() );

    // Calculate the sampling ratios
    Teuchos::ArrayRCP<double> sampling_ratios( total_cross_section.size() );
    for ( unsigned i = 0; i < sampling_ratios.size(); ++i )
    {
      sampling_ratios[i] = cutoff_cross_section[i]/total_cross_section[i];
    }

    // Create cutoff distribution
    std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
        cutoff_elastic_distribution;
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::Correlated<Utility::LinLinLog> >(
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

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDecoupledElasticPositronatomicReaction.cpp
//---------------------------------------------------------------------------//
