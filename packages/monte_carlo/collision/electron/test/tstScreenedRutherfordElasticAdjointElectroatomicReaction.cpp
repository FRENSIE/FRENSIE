//---------------------------------------------------------------------------//
//!
//! \file   tstScreenedRutherfordElasticAdjointElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Moment preserving Elastic adjoint electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_ScreenedRutherfordElasticAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

typedef MonteCarlo::ElasticElectronScatteringDistributionNativeFactory
    NativeFactory;

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointElectroatomicReaction>
    rutherford_elastic_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( ScreenedRutherfordElasticAdjointElectroatomicReaction, getReactionType )
{
  FRENSIE_CHECK_EQUAL(
    rutherford_elastic_reaction->getReactionType(),
    MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( ScreenedRutherfordElasticAdjointElectroatomicReaction, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( rutherford_elastic_reaction->getThresholdEnergy(),
                       2.59024e-01 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( ScreenedRutherfordElasticAdjointElectroatomicReaction, getNumberOfEmittedAdjointElectrons )
{
  FRENSIE_CHECK_EQUAL( rutherford_elastic_reaction->getNumberOfEmittedAdjointElectrons(1e-3),
                       1u );

  FRENSIE_CHECK_EQUAL( rutherford_elastic_reaction->getNumberOfEmittedAdjointElectrons(20.0),
                       1u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( ScreenedRutherfordElasticAdjointElectroatomicReaction, getNumberOfEmittedAdjointPhotons )
{
  FRENSIE_CHECK_EQUAL( rutherford_elastic_reaction->getNumberOfEmittedAdjointPhotons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( rutherford_elastic_reaction->getNumberOfEmittedAdjointPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( ScreenedRutherfordElasticAdjointElectroatomicReaction, getNumberOfEmittedAdjointPositrons )
{
  FRENSIE_CHECK_EQUAL( rutherford_elastic_reaction->getNumberOfEmittedAdjointPositrons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( rutherford_elastic_reaction->getNumberOfEmittedAdjointPositrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the moment preserving cross section can be returned
FRENSIE_UNIT_TEST( ScreenedRutherfordElasticAdjointElectroatomicReaction,
                   getCrossSection )
{

  double cross_section = rutherford_elastic_reaction->getCrossSection( 1.0E-05 );
  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  cross_section = rutherford_elastic_reaction->getCrossSection( 1.0E-03 );
  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  cross_section = rutherford_elastic_reaction->getCrossSection( 2.59024e-01 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.574552047073666472, 1e-12 );

  cross_section = rutherford_elastic_reaction->getCrossSection( 20.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.271739489125800355e+04, 1e-12 );
}


//---------------------------------------------------------------------------//
// Check that the elastic reaction can be simulated
FRENSIE_UNIT_TEST( ScreenedRutherfordElasticAdjointElectroatomicReaction, react )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 20.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  rutherford_elastic_reaction->react( electron, bank, shell_of_interaction );

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
  // Create reaction
  {
    // Get native data container
    Data::AdjointElectronPhotonRelaxationDataContainer data_container =
        Data::AdjointElectronPhotonRelaxationDataContainer( test_native_file_name );

    // Extract the energy grid and cross section
    std::shared_ptr<const std::vector<double> > energy_grid(
       new std::vector<double>( data_container.getAdjointElectronEnergyGrid() ) );

    std::shared_ptr<const std::vector<double> > cross_section(
       new std::vector<double>( data_container.getAdjointScreenedRutherfordElasticCrossSection() ) );

    size_t threshold_index(
        data_container.getAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex() );

    // Create the screened rutherford distribution
    std::shared_ptr<const MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution>
        rutherford_elastic_distribution;

    NativeFactory::createScreenedRutherfordElasticDistribution(
        rutherford_elastic_distribution,
        data_container.getAtomicNumber() );

    // Create the reaction
    rutherford_elastic_reaction.reset(
      new MonteCarlo::ScreenedRutherfordElasticAdjointElectroatomicReaction<Utility::LogLog>(
                energy_grid,
                cross_section,
                threshold_index,
                rutherford_elastic_distribution ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCutoffElasticAdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
