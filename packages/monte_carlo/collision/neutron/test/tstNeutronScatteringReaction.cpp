//---------------------------------------------------------------------------//
//!
//! \file   tstNeutronScatteringReaction.cpp
//! \author Alex Robinson
//! \brief  Nuclear reaction unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_NeutronNuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_NeutronScatteringReaction.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::NeutronNuclearReaction> nuclear_reaction;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the number of emitted neutrons can be returned
FRENSIE_UNIT_TEST( NeutronScatteringReaction_elastic,
		   getNumberOfEmittedNeutrons )
{
  FRENSIE_CHECK_EQUAL( nuclear_reaction->getNumberOfEmittedParticles( 0.0 ), 1);
}

//---------------------------------------------------------------------------//
// Check that the reaction can be simulated
FRENSIE_UNIT_TEST( NeutronScatteringReaction_elastic,
		   react )
{
  MonteCarlo::ParticleBank bank;

  {
    std::shared_ptr<MonteCarlo::NeutronState> neutron( new MonteCarlo::NeutronState(0ull) );

    neutron->setDirection( 0.0, 0.0, 1.0 );
    neutron->setEnergy( 1.0 );

    bank.push( neutron );
  }

  nuclear_reaction->react( dynamic_cast<MonteCarlo::NeutronState&>(bank.top()),
			   bank );

  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_basic_ace_file_name;
unsigned test_basic_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_basic_ace_file",
                                        test_basic_ace_file_name, "",
                                        "Test basic ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_basic_ace_file_start_line",
                                        test_basic_ace_file_start_line, 1,
                                        "Test basic ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize the ace file handler and data extractor
  std::unique_ptr<const Data::ACEFileHandler> ace_file_handler(
                  new Data::ACEFileHandler( test_basic_ace_file_name,
                                            "1001.70c",
					    test_basic_ace_file_start_line ) );
  
  std::unique_ptr<const Data::XSSNeutronDataExtractor> xss_data_extractor(
     new Data::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
                                        ace_file_handler->getTableJXSArray(),
                                        ace_file_handler->getTableXSSArray()));

  MonteCarlo::NeutronNuclearScatteringDistributionACEFactory
    factory( "1001.70c",
	     ace_file_handler->getTableAtomicWeightRatio(),
	     *xss_data_extractor );

  MonteCarlo::SimulationProperties properties;

  std::shared_ptr<const MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState> > scattering_dist;

  factory.createScatteringDistribution( MonteCarlo::N__N_ELASTIC_REACTION,
                                        properties,
					scattering_dist );

  std::shared_ptr<const std::vector<double> > energy_grid(
          new std::vector<double>( xss_data_extractor->extractEnergyGrid() ) );

  std::shared_ptr<const std::vector<double> > cross_section(
          new std::vector<double>( xss_data_extractor->extractElasticCrossSection() ) );

  nuclear_reaction.reset( new MonteCarlo::NeutronScatteringReaction(
                               energy_grid,
                               cross_section,
                               0u,
                               MonteCarlo::N__N_ELASTIC_REACTION,
                               0.0,
                               ace_file_handler->getTableTemperature().value(),
                               1u,
                               scattering_dist ) );
    
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstNeutronScatteringReaction.cpp
//---------------------------------------------------------------------------//

