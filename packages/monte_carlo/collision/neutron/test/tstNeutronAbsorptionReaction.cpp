//---------------------------------------------------------------------------//
//!
//! \file   tstNeutronAbsorptionReaction.cpp
//! \author Alex Robinson
//! \brief  Nuclear reaction unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_NeutronAbsorptionReaction.hpp"
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
FRENSIE_UNIT_TEST( NeutronAbsorptionReaction,
		   getNumberOfEmittedParticles )
{
  FRENSIE_CHECK_EQUAL( nuclear_reaction->getNumberOfEmittedParticles( 0.0 ), 0);
}

//---------------------------------------------------------------------------//
// Check that the reaction can be simulated
FRENSIE_UNIT_TEST( NeutronAbsorptionReaction,
		   react )
{
  MonteCarlo::ParticleBank bank;

  {
    std::shared_ptr<MonteCarlo::NeutronState>
      neutron( new MonteCarlo::NeutronState(0ull) );

    neutron->setDirection( 0.0, 0.0, 1.0 );
    neutron->setEnergy( 1.0 );

    bank.push( neutron );
  }

  nuclear_reaction->react( dynamic_cast<MonteCarlo::NeutronState&>(bank.top()),
			   bank );

  FRENSIE_CHECK( bank.top().isGone() );
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
  std::unique_ptr<Data::ACEFileHandler> ace_file_handler(
                  new Data::ACEFileHandler( test_basic_ace_file_name,
                                            "1001.70c",
					    test_basic_ace_file_start_line ) );
  
  std::unique_ptr<Data::XSSNeutronDataExtractor> xss_data_extractor(
   new Data::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
                                      ace_file_handler->getTableJXSArray(),
                                      ace_file_handler->getTableXSSArray()));

  std::shared_ptr<const std::vector<double> > energy_grid(
          new std::vector<double>( xss_data_extractor->extractEnergyGrid() ) );

  std::shared_ptr<const std::vector<double> > cross_section(
          new std::vector<double>( xss_data_extractor->extractElasticCrossSection() ) );

  nuclear_reaction.reset( new MonteCarlo::NeutronAbsorptionReaction(
                           energy_grid,
                           cross_section,
                           0u,
                           MonteCarlo::N__N_ELASTIC_REACTION,
                           0.0,
                           ace_file_handler->getTableTemperature().value() ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstNeutronAbsorptionReaction.cpp
//---------------------------------------------------------------------------//

