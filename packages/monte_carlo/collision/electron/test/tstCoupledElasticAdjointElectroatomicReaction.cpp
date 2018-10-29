//---------------------------------------------------------------------------//
//!
//! \file   tstCoupledElasticAdjointElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Coupled Elastic adjoint electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_CoupledElasticAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_CoupledElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::CoupledElasticAdjointElectroatomicReaction<Utility::LogLog> > coupled_elastic_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( CoupledElasticAdjointElectroatomicReaction, getReactionType )
{
  FRENSIE_CHECK_EQUAL( coupled_elastic_reaction->getReactionType(),
		       MonteCarlo::COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( CoupledElasticAdjointElectroatomicReaction, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( coupled_elastic_reaction->getThresholdEnergy(),
                       1.0e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( CoupledElasticAdjointElectroatomicReaction, getNumberOfEmittedAdjointElectrons )
{
  FRENSIE_CHECK_EQUAL( coupled_elastic_reaction->getNumberOfEmittedAdjointElectrons(1e-3),
                       1u );

  FRENSIE_CHECK_EQUAL( coupled_elastic_reaction->getNumberOfEmittedAdjointElectrons(20.0),
                       1u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( CoupledElasticAdjointElectroatomicReaction, getNumberOfEmittedAdjointPhotons )
{
  FRENSIE_CHECK_EQUAL( coupled_elastic_reaction->getNumberOfEmittedAdjointPhotons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( coupled_elastic_reaction->getNumberOfEmittedAdjointPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( CoupledElasticAdjointElectroatomicReaction, getNumberOfEmittedAdjointPositrons )
{
  FRENSIE_CHECK_EQUAL( coupled_elastic_reaction->getNumberOfEmittedAdjointPositrons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( coupled_elastic_reaction->getNumberOfEmittedAdjointPositrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the coupled cross section can be returned
FRENSIE_UNIT_TEST( CoupledElasticAdjointElectroatomicReaction,
                   getCrossSection )
{

  double cross_section = coupled_elastic_reaction->getCrossSection( 1.0E-05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.74896E+08, 1e-12 );

  cross_section = coupled_elastic_reaction->getCrossSection( 1.0E-03 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.804290802376420237e+06, 1e-12 );

  cross_section = coupled_elastic_reaction->getCrossSection( 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.3022122514987041e+04, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the elastic reaction can be simulated
FRENSIE_UNIT_TEST( CoupledElasticAdjointElectroatomicReaction, react )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 20.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  coupled_elastic_reaction->react( electron, bank, shell_of_interaction );

  FRENSIE_CHECK_EQUAL( electron.getEnergy(), 20.0 );
  FRENSIE_CHECK( electron.getZDirection() < 2.0 );
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
  // Create reaction
  {
    // Get native data container
    Data::AdjointElectronPhotonRelaxationDataContainer data_container =
        Data::AdjointElectronPhotonRelaxationDataContainer( test_native_file_name );

    MonteCarlo::CoupledElasticSamplingMethod sampling_method =
      MonteCarlo::TWO_D_UNION;
    double evaluation_tol = 1e-7;

    std::shared_ptr<const std::vector<double> > energy_grid(
       new std::vector<double>( data_container.getAdjointElectronEnergyGrid() ) );

    std::shared_ptr<const std::vector<double> > cutoff_cross_section(
       new std::vector<double>( data_container.getAdjointCutoffElasticCrossSection() ) );


    std::shared_ptr<const std::vector<double> > total_cross_section(
       new std::vector<double>( data_container.getAdjointTotalElasticCrossSection() ) );

    // Create coupled distribution
    std::shared_ptr<const MonteCarlo::CoupledElasticElectronScatteringDistribution>
        coupled_elastic_distribution;
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<Utility::LinLinLog,Utility::Correlated>(
        coupled_elastic_distribution,
        energy_grid,
        cutoff_cross_section,
        total_cross_section,
        data_container,
        sampling_method,
        evaluation_tol );

    // Create the reaction
    coupled_elastic_reaction.reset(
      new MonteCarlo::CoupledElasticAdjointElectroatomicReaction<Utility::LogLog>(
        energy_grid,
        total_cross_section,
        data_container.getAdjointTotalElasticCrossSectionThresholdEnergyIndex(),
        coupled_elastic_distribution ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCoupledElasticAdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
