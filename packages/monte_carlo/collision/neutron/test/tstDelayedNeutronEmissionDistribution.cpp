//---------------------------------------------------------------------------//
//!
//! \file   tstDelayedNeutronEmissionDistribution.cpp
//! \author Alex Robinson
//! \brief  Delayed neutron emission distribution factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_DelayedNeutronEmissionDistributionACEFactory.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState> > distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the delayed neutron can be emitted correcly
FRENSIE_UNIT_TEST( DelayedNeutronEmissionDistribution, scatterNeutron )
{
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.20; // select 3rd precursor group
  fake_stream[1] = 0.5; // sample emission time of 5.978622815721089
  fake_stream[2] = 0.1;
  fake_stream[3] = 0.6;
  fake_stream[4] = 0.7;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::NeutronState neutron( 1ull );
  neutron.setEnergy( 1.0 );
  neutron.setTime( 0.0 );
  neutron.setDirection( 0.0, 0.0, 1.0 );

  distribution->scatterParticle( neutron, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getTime(), 5.978622815721089, 1e-15 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_u238_ace_file_name;
unsigned test_u238_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_u238_ace_file",
                                        test_u238_ace_file_name, "",
                                        "Test U238 ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_u238_ace_file_start_line",
                                        test_u238_ace_file_start_line, 1,
                                        "Test U238 ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize ace file handler, data extractor and multiplicity factory
  std::unique_ptr<Data::ACEFileHandler>
    ace_file_handler( new Data::ACEFileHandler( test_u238_ace_file_name,
                                                "92238.70c",
                                                test_u238_ace_file_start_line ) );

  std::unique_ptr<Data::XSSNeutronDataExtractor>
    xss_data_extractor( new Data::XSSNeutronDataExtractor(
                                      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

  std::unique_ptr<MonteCarlo::DelayedNeutronEmissionDistributionACEFactory>
    factory( new MonteCarlo::DelayedNeutronEmissionDistributionACEFactory(
				 ace_file_handler->getTableName(),
				 ace_file_handler->getTableAtomicWeightRatio(),
				 xss_data_extractor->extractBDDBlock(),
				 xss_data_extractor->extractDNEDLBlock(),
				 xss_data_extractor->extractDNEDBlock() ) );

  factory->createEmissionDistribution( distribution );

  ace_file_handler.reset();
  xss_data_extractor.reset();
  factory.reset();

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDelayedNeutronEmissionDistribution.cpp
//---------------------------------------------------------------------------//
