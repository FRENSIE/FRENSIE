//---------------------------------------------------------------------------//
//!
//! \file   tstJointElasticElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Joint Elastic electroatomic reaction unit tests
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
#include "MonteCarlo_JointElasticElectroatomicReaction.hpp"
#include "MonteCarlo_AnalogElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_TabularDistribution.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::JointElasticElectroatomicReaction<Utility::LinLin> > joint_elastic_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
TEUCHOS_UNIT_TEST( JointElasticElectroatomicReaction, getReactionType )
{
  TEST_EQUALITY_CONST( joint_elastic_reaction->getReactionType(),
                       MonteCarlo::JOINT_ELASTIC_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( JointElasticElectroatomicReaction, getThresholdEnergy )
{
  TEST_EQUALITY_CONST( joint_elastic_reaction->getThresholdEnergy(),
                       1.0e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( JointElasticElectroatomicReaction, getNumberOfEmittedElectrons )
{
  TEST_EQUALITY_CONST( joint_elastic_reaction->getNumberOfEmittedElectrons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( joint_elastic_reaction->getNumberOfEmittedElectrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( JointElasticElectroatomicReaction, getNumberOfEmittedPhotons )
{
  TEST_EQUALITY_CONST( joint_elastic_reaction->getNumberOfEmittedPhotons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( joint_elastic_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the joint cross section can be returned
TEUCHOS_UNIT_TEST( JointElasticElectroatomicReaction,
                   getCrossSection )
{

  double cross_section = joint_elastic_reaction->getCrossSection( 1.0E-05 );
  TEST_FLOATING_EQUALITY( cross_section, 2.74896E+08, 1e-12 );

  cross_section = joint_elastic_reaction->getCrossSection( 1.0E-03 );
  TEST_FLOATING_EQUALITY( cross_section, 2.80423E+06, 1e-12 );

  cross_section = joint_elastic_reaction->getCrossSection( 1.0E+05 );
  TEST_FLOATING_EQUALITY( cross_section, 1.29871E+04, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the elastic reaction can be simulated
TEUCHOS_UNIT_TEST( JointElasticElectroatomicReaction, react )
{
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 20.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  joint_elastic_reaction->react( electron, bank, shell_of_interaction );

  TEST_EQUALITY_CONST( electron.getEnergy(), 20.0 );
  TEST_ASSERT( electron.getZDirection() < 1.0 );
  TEST_ASSERT( electron.getZDirection() > -1.0 );
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

  electron.setDirection( 0.0, 0.0, 1.0 );
  joint_elastic_reaction->react( electron, bank, shell_of_interaction );

  TEST_EQUALITY_CONST( electron.getEnergy(), 20.0 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(),
                          -1.0,
                          1e-15 );
  TEST_ASSERT( bank.isEmpty() );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  electron.setDirection( 0.0, 0.0, 1.0 );
  joint_elastic_reaction->react( electron, bank, shell_of_interaction );

  TEST_EQUALITY_CONST( electron.getEnergy(), 20.0 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(),
                          0.999999,
                          1e-15 );
  TEST_ASSERT( bank.isEmpty() );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  electron.setDirection( 0.0, 0.0, 1.0 );
  joint_elastic_reaction->react( electron, bank, shell_of_interaction );

  TEST_EQUALITY_CONST( electron.getEnergy(), 20.0 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(),
                          0.999999,
                          1e-15 );
  TEST_ASSERT( bank.isEmpty() );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  electron.setDirection( 0.0, 0.0, 1.0 );
  joint_elastic_reaction->react( electron, bank, shell_of_interaction );

  TEST_EQUALITY_CONST( electron.getEnergy(), 20.0 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(),
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
    bool correlated_sampling_mode_on = true;
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
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LinLinLog>(
        cutoff_elastic_distribution,
        data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );

    // Create screened Rutherford distribution
    std::shared_ptr<const MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution>
        sr_elastic_distribution;
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createScreenedRutherfordElasticDistribution(
        sr_elastic_distribution,
        cutoff_elastic_distribution,
        data_container.getAtomicNumber() );

    // Create the reaction
    joint_elastic_reaction.reset(
      new MonteCarlo::JointElasticElectroatomicReaction<Utility::LinLin>(
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
// end tstJointElasticElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
