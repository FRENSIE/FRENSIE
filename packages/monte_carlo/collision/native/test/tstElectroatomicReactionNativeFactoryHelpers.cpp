//---------------------------------------------------------------------------//
//!
//! \file   tstElectroatomicReactionNativeFactoryHelpers.cpp
//! \author Luke Kersting
//! \brief  Electroatomic reaction native factory helpers unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactoryHelpers.hpp"
#include "MonteCarlo_AnalogElasticElectroatomicReaction.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_TabularDistribution.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::ElectroatomicReaction> analog_elastic_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers, getReactionType )
{
  TEST_EQUALITY_CONST( analog_elastic_reaction->getReactionType(),
                       MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers, getThresholdEnergy )
{
  TEST_EQUALITY_CONST( analog_elastic_reaction->getThresholdEnergy(),
                       1.0e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers, getNumberOfEmittedElectrons )
{
  TEST_EQUALITY_CONST( analog_elastic_reaction->getNumberOfEmittedElectrons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( analog_elastic_reaction->getNumberOfEmittedElectrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers, getNumberOfEmittedPhotons )
{
  TEST_EQUALITY_CONST( analog_elastic_reaction->getNumberOfEmittedPhotons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( analog_elastic_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the analog cross section can be returned
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   getCrossSection )
{

  double cross_section =
    analog_elastic_reaction->getCrossSection( 1.0E-05 );

  TEST_FLOATING_EQUALITY( cross_section, 2.74896E+08, 1e-12 );

  cross_section =
    analog_elastic_reaction->getCrossSection( 1.0E-03 );

  TEST_FLOATING_EQUALITY( cross_section, 2.80423E+06, 1e-12 );

  cross_section =
    analog_elastic_reaction->getCrossSection( 1.0E+05 );

  TEST_FLOATING_EQUALITY( cross_section, 1.29871E+04, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the elastic reaction can be simulated
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers, react )
{
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 20.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  analog_elastic_reaction->react( electron, bank, shell_of_interaction );

  TEST_EQUALITY_CONST( electron.getEnergy(), 20.0 );
  TEST_ASSERT( electron.getZDirection() < 2.0 );
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
    Data::ElectronPhotonRelaxationDataContainer data_container =
        Data::ElectronPhotonRelaxationDataContainer( test_native_file_name );

    bool linlinlog_interpolation_mode_on = true;
    bool correlated_sampling_mode_on = true;
    double evaluation_tol = 1e-7;

    // Create analog distribution
    analog_elastic_reaction = MonteCarlo::createAnalogElasticReaction(
        data_container,
        linlinlog_interpolation_mode_on,
        correlated_sampling_mode_on,
        evaluation_tol );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END(); 

//---------------------------------------------------------------------------//
// end tstElectroatomicReactionNativeFactoryHelpers.cpp
//---------------------------------------------------------------------------//
