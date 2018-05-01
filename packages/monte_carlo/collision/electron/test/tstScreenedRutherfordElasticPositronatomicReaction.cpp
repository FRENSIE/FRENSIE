//---------------------------------------------------------------------------//
//!
//! \file   tstScreenedRutherfordElasticPositronatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Moment preserving Elastic positron-atomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_ScreenedRutherfordElasticPositronatomicReaction.hpp"
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

std::shared_ptr<MonteCarlo::PositronatomicReaction>
    rutherford_elastic_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( ScreenedRutherfordElasticPositronatomicReaction, getReactionType )
{
  FRENSIE_CHECK_EQUAL( rutherford_elastic_reaction->getReactionType(),
		       MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_POSITRONATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( ScreenedRutherfordElasticPositronatomicReaction, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( rutherford_elastic_reaction->getThresholdEnergy(),
                       1.75 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( ScreenedRutherfordElasticPositronatomicReaction, getNumberOfEmittedElectrons )
{
  FRENSIE_CHECK_EQUAL( rutherford_elastic_reaction->getNumberOfEmittedElectrons(1e-3),
		       0u );

  FRENSIE_CHECK_EQUAL( rutherford_elastic_reaction->getNumberOfEmittedElectrons(20.0),
		       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( ScreenedRutherfordElasticPositronatomicReaction, getNumberOfEmittedPhotons )
{
  FRENSIE_CHECK_EQUAL( rutherford_elastic_reaction->getNumberOfEmittedPhotons(1e-3),
		       0u );

  FRENSIE_CHECK_EQUAL( rutherford_elastic_reaction->getNumberOfEmittedPhotons(20.0),
		       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( ScreenedRutherfordElasticPositronatomicReaction, getNumberOfEmittedPositrons )
{
  FRENSIE_CHECK_EQUAL( rutherford_elastic_reaction->getNumberOfEmittedPositrons(1e-3),
		       1u );

  FRENSIE_CHECK_EQUAL( rutherford_elastic_reaction->getNumberOfEmittedPositrons(20.0),
		       1u );
}

//---------------------------------------------------------------------------//
// Check that the moment preserving cross section can be returned
FRENSIE_UNIT_TEST( ScreenedRutherfordElasticPositronatomicReaction,
                   getCrossSection )
{

  double cross_section =
    rutherford_elastic_reaction->getCrossSection( 1.0E-05 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section =
    rutherford_elastic_reaction->getCrossSection( 1.0E-03 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section =
    rutherford_elastic_reaction->getCrossSection( 1.75 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.822907080362080E+03, 1e-12 );

  cross_section =
    rutherford_elastic_reaction->getCrossSection( 1.0E+05 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.855069977822990E+05, 1e-12 );
}


//---------------------------------------------------------------------------//
// Check that the elastic reaction can be simulated
FRENSIE_UNIT_TEST( ScreenedRutherfordElasticPositronatomicReaction, react )
{
  MonteCarlo::PositronState positron( 0 );
  positron.setEnergy( 20.0 );
  positron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  rutherford_elastic_reaction->react( positron, bank, shell_of_interaction );

  FRENSIE_CHECK_EQUAL( positron.getEnergy(), 20.0 );
  FRENSIE_CHECK( positron.getZDirection() < 1.0 );
  FRENSIE_CHECK( positron.getZDirection() > 0.0 );
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

    // Create the screened rutherford distribution
    std::shared_ptr<const MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution>
        rutherford_elastic_distribution;

    NativeFactory::createScreenedRutherfordElasticDistribution(
        rutherford_elastic_distribution,
        data_container.getAtomicNumber() );

    std::shared_ptr<const std::vector<double> > energy_grid(
           new std::vector<double>( data_container.getElectronEnergyGrid() ) );

    std::shared_ptr<const std::vector<double> > cross_section(
       new std::vector<double>( data_container.getScreenedRutherfordElasticCrossSection() ) );

    size_t threshold_index(
        data_container.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex() );

    // Create the reaction
    rutherford_elastic_reaction.reset(
      new MonteCarlo::ScreenedRutherfordElasticPositronatomicReaction<Utility::LinLin>(
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
// end tstScreenedRutherfordElasticPositronatomicReaction.cpp
//---------------------------------------------------------------------------//
