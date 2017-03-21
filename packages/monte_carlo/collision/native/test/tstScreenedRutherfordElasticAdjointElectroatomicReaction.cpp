//---------------------------------------------------------------------------//
//!
//! \file   tstScreenedRutherfordElasticAdjointElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Moment preserving Elastic adjoint electroatomic reaction unit tests
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
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_ScreenedRutherfordElasticAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_TabularOneDDistribution.hpp"

typedef MonteCarlo::ElasticElectronScatteringDistributionNativeFactory<Utility::LinLinLog> 
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
TEUCHOS_UNIT_TEST( ScreenedRutherfordElasticAdjointElectroatomicReaction, getReactionType )
{
  TEST_EQUALITY_CONST(
    rutherford_elastic_reaction->getReactionType(),
    MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( ScreenedRutherfordElasticAdjointElectroatomicReaction, getThresholdEnergy )
{
  TEST_EQUALITY_CONST( rutherford_elastic_reaction->getThresholdEnergy(),
                       0.312509629531249944 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( ScreenedRutherfordElasticAdjointElectroatomicReaction, getNumberOfEmittedElectrons )
{
  TEST_EQUALITY_CONST( rutherford_elastic_reaction->getNumberOfEmittedElectrons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( rutherford_elastic_reaction->getNumberOfEmittedElectrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( ScreenedRutherfordElasticAdjointElectroatomicReaction, getNumberOfEmittedPhotons )
{
  TEST_EQUALITY_CONST( rutherford_elastic_reaction->getNumberOfEmittedPhotons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( rutherford_elastic_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the moment preserving cross section can be returned
TEUCHOS_UNIT_TEST( ScreenedRutherfordElasticAdjointElectroatomicReaction,
                   getCrossSection )
{

  double cross_section =
    rutherford_elastic_reaction->getCrossSection( 1.0E-05 );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section =
    rutherford_elastic_reaction->getCrossSection( 1.0E-03 );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section =
    rutherford_elastic_reaction->getCrossSection( 0.312509629531249944 );

  TEST_FLOATING_EQUALITY( cross_section, 1.69347821609735E+01, 1e-12 );

  cross_section =
    rutherford_elastic_reaction->getCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 1.27173948912580E+04, 1e-12 );
}


//---------------------------------------------------------------------------//
// Check that the elastic reaction can be simulated
TEUCHOS_UNIT_TEST( ScreenedRutherfordElasticAdjointElectroatomicReaction, react )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 20.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  rutherford_elastic_reaction->react( electron, bank, shell_of_interaction );

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
  // Create reaction
  {
    // Get native data container
    Data::AdjointElectronPhotonRelaxationDataContainer data_container =
        Data::AdjointElectronPhotonRelaxationDataContainer( test_native_file_name );

    // Extract the energy grid and cross section
    Teuchos::ArrayRCP<double> energy_grid;
    energy_grid.assign(
        data_container.getAdjointElectronEnergyGrid().begin(),
        data_container.getAdjointElectronEnergyGrid().end() );

    Teuchos::ArrayRCP<double> cross_section;
    cross_section.assign(
        data_container.getAdjointScreenedRutherfordElasticCrossSection().begin(),
        data_container.getAdjointScreenedRutherfordElasticCrossSection().end() );

    unsigned threshold_index(
        data_container.getAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex() );

    // Create the cutoff distribution
    std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
        cutoff_elastic_distribution;

    NativeFactory::createCutoffElasticDistribution(
        cutoff_elastic_distribution,
        data_container,
        1.0,
        1e-7 );

    // Create the screened rutherford distribution
    std::shared_ptr<const MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution>
        rutherford_elastic_distribution;

    NativeFactory::createScreenedRutherfordElasticDistribution(
        rutherford_elastic_distribution,
        cutoff_elastic_distribution,
        data_container.getAtomicNumber() );

    // Create the reaction
    rutherford_elastic_reaction.reset(
      new MonteCarlo::ScreenedRutherfordElasticAdjointElectroatomicReaction<Utility::LinLin>(
                energy_grid,
                cross_section,
                threshold_index,
                rutherford_elastic_distribution ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCutoffElasticAdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
