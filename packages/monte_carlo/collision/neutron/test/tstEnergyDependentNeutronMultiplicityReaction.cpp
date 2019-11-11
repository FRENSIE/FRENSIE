//---------------------------------------------------------------------------//
//!
//! \file   tstEnergyDependentNeutronMultiplicityReaction.cpp
//! \author Alex Robinson
//! \brief  Energy dependent neutron multiplicity reaction
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_NeutronNuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_EnergyDependentNeutronMultiplicityReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::NeutronNuclearReaction> nuclear_reaction;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the number of emitted neutrons can be returned
FRENSIE_UNIT_TEST( EnergyDependentNeutronMultiplicityReaction,
		   getNumberOfEmittedParticles )
{
  unsigned number_of_emitted_neutrons =
    nuclear_reaction->getNumberOfEmittedParticles( 1e-11 );

  FRENSIE_CHECK_EQUAL( number_of_emitted_neutrons, 0.0 );

  number_of_emitted_neutrons =
    nuclear_reaction->getNumberOfEmittedParticles( 30.0 );

  FRENSIE_CHECK_EQUAL( number_of_emitted_neutrons, 0.0 );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.15;
  fake_stream[1] = 0.20;
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  number_of_emitted_neutrons =
    nuclear_reaction->getNumberOfEmittedParticles( 150.0 );

  FRENSIE_CHECK_EQUAL( number_of_emitted_neutrons, 1.0 );

  number_of_emitted_neutrons =
    nuclear_reaction->getNumberOfEmittedParticles( 150.0 );

  FRENSIE_CHECK_EQUAL( number_of_emitted_neutrons, 2.0 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name;
unsigned test_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file",
                                        test_ace_file_name, "",
                                        "Test ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file_start_line",
                                        test_ace_file_start_line, 1,
                                        "Test ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize the ace file handler and data extractor
  std::unique_ptr<const Data::ACEFileHandler> ace_file_handler(
                        new Data::ACEFileHandler( test_ace_file_name,
                                                  "8016.70c",
                                                  test_ace_file_start_line ) );
  
  std::unique_ptr<const Data::XSSNeutronDataExtractor> xss_data_extractor(
     new Data::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
                                        ace_file_handler->getTableJXSArray(),
                                        ace_file_handler->getTableXSSArray()));

  MonteCarlo::NeutronNuclearScatteringDistributionACEFactory
    factory( "8016.70c",
	     ace_file_handler->getTableAtomicWeightRatio(),
	     *xss_data_extractor );

  MonteCarlo::SimulationProperties properties;

  std::shared_ptr<const MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState> > scattering_dist;

  factory.createScatteringDistribution( MonteCarlo::N__ANYTHING_REACTION,
                                        properties,
					scattering_dist );

  std::shared_ptr<const std::vector<double> > energy_grid(
          new std::vector<double>( xss_data_extractor->extractEnergyGrid() ) );

  Utility::ArrayView<const double> sig_block =
    xss_data_extractor->extractSIGBlock();

  unsigned threshold_index = (unsigned)sig_block[0] - 1u;
  unsigned num_energies = (unsigned)sig_block[1];

  std::shared_ptr<const std::vector<double> > cross_section(
                     new std::vector<double>( sig_block( 2, num_energies ) ) );

  Utility::ArrayView<const double> dlw_block =
    xss_data_extractor->extractDLWBlock();

  Utility::ArrayView<const double> multiplicity_energy_grid =
    dlw_block( 2, (unsigned)dlw_block[1] );

  Utility::ArrayView<const double> multiplicity =
    dlw_block( 2 + (unsigned)dlw_block[1], (unsigned)dlw_block[1] );

  nuclear_reaction.reset(
		   new MonteCarlo::EnergyDependentNeutronMultiplicityReaction(
                               energy_grid,
                               cross_section,
                               threshold_index,
                               MonteCarlo::N__ANYTHING_REACTION,
                               0.0,
                               ace_file_handler->getTableTemperature().value(),
                               scattering_dist,
                               multiplicity_energy_grid,
                               multiplicity ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstEnergyDependentNeutronMultiplicityReaction.cpp
//---------------------------------------------------------------------------//
