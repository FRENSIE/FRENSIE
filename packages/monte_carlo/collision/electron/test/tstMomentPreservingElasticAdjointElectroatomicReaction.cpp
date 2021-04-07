//---------------------------------------------------------------------------//
//!
//! \file   tstMomentPreservingElasticAdjointElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Moment preserving Elastic adjoint electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_MomentPreservingElasticAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

typedef MonteCarlo::ElasticElectronScatteringDistributionNativeFactory
    NativeFactory;

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointElectroatomicReaction> mp_elastic_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( MomentPreservingElasticAdjointElectroatomicReaction,
                   getReactionType )
{
  FRENSIE_CHECK_EQUAL( mp_elastic_reaction->getReactionType(),
		       MonteCarlo::MOMENT_PRESERVING_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( MomentPreservingElasticAdjointElectroatomicReaction,
                   getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( mp_elastic_reaction->getThresholdEnergy(),
                       1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( MomentPreservingElasticAdjointElectroatomicReaction,
                   getNumberOfEmittedAdjointElectrons )
{
  FRENSIE_CHECK_EQUAL( mp_elastic_reaction->getNumberOfEmittedAdjointElectrons(1e-3),
                       1u );

  FRENSIE_CHECK_EQUAL( mp_elastic_reaction->getNumberOfEmittedAdjointElectrons(20.0),
                       1u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( MomentPreservingElasticAdjointElectroatomicReaction,
                   getNumberOfEmittedAdjointPhotons )
{
  FRENSIE_CHECK_EQUAL( mp_elastic_reaction->getNumberOfEmittedAdjointPhotons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( mp_elastic_reaction->getNumberOfEmittedAdjointPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of positron emitted from the rxn can be returned
FRENSIE_UNIT_TEST( MomentPreservingElasticAdjointElectroatomicReaction,
                   getNumberOfEmittedAdjointPositrons )
{
  FRENSIE_CHECK_EQUAL( mp_elastic_reaction->getNumberOfEmittedAdjointPositrons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( mp_elastic_reaction->getNumberOfEmittedAdjointPositrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the moment preserving cross section can be returned
FRENSIE_UNIT_TEST( MomentPreservingElasticAdjointElectroatomicReaction,
                   getCrossSection )
{
  double cross_section = mp_elastic_reaction->getCrossSection( 1.0E-05 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.2217606103336416e+07, 1e-12 );

  cross_section = mp_elastic_reaction->getCrossSection( 1.0E-03 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.651784305723777972e+06, 1e-12 );

  cross_section = mp_elastic_reaction->getCrossSection( 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.051213497766151139, 1e-12 );
}


//---------------------------------------------------------------------------//
// Check that the elastic reaction can be simulated
FRENSIE_UNIT_TEST( MomentPreservingElasticAdjointElectroatomicReaction, react )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 20.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  mp_elastic_reaction->react( electron, bank, shell_of_interaction );

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
  Data::AdjointElectronPhotonRelaxationDataContainer data_container =
    Data::AdjointElectronPhotonRelaxationDataContainer( test_native_file_name );

  // Extract the energy grid and cross section
  std::shared_ptr<const std::vector<double> > energy_grid(
    new std::vector<double>( data_container.getAdjointElectronEnergyGrid() ) );

  double cutoff_angle_cosine = 0.9;
  double evaluation_tol = 1e-15;

  // Moment preserving elastic cross section
  std::vector<double> moment_preserving_cross_sections;
  size_t threshold_index;
  NativeFactory::calculateMomentPreservingCrossSections<Utility::LogLogCosLog,Utility::Correlated>(
                                moment_preserving_cross_sections,
                                threshold_index,
                                data_container,
                                energy_grid,
                                evaluation_tol );

  std::shared_ptr<const std::vector<double> > cross_section(
                 new std::vector<double>( moment_preserving_cross_sections ) );

  // Create the distribution
  std::shared_ptr<const MonteCarlo::MomentPreservingElasticElectronScatteringDistribution>
        discrete_elastic_distribution;

  NativeFactory::createMomentPreservingElasticDistribution<Utility::LogLogCosLog,Utility::Correlated>(
        discrete_elastic_distribution,
        data_container,
        cutoff_angle_cosine,
        evaluation_tol );

  // Create the reaction
  mp_elastic_reaction.reset(
      new MonteCarlo::MomentPreservingElasticAdjointElectroatomicReaction<Utility::LogLog>(
                energy_grid,
                cross_section,
                threshold_index,
                discrete_elastic_distribution ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCutoffElasticAdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
