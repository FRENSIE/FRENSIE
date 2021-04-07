//---------------------------------------------------------------------------//
//!
//! \file   tstFissionNeutronMultiplicityDistribution.cpp
//! \author Alex Robinson
//! \brief  Fission neutron multiplicity distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_FissionNeutronMultiplicityDistributionACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const MonteCarlo::FissionNeutronMultiplicityDistribution> multiplicity_dist;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the total nu-bar can be evaluated correctly
FRENSIE_UNIT_TEST( FissionNeutronMultiplicityDistribution,
		   getAverageNumberOfEmittedNeutrons )
{
  FRENSIE_CHECK_EQUAL(
	       multiplicity_dist->getAverageNumberOfEmittedNeutrons( 1.0e-11 ),
	       2.49208800000e+00 );
  FRENSIE_CHECK_EQUAL(
		  multiplicity_dist->getAverageNumberOfEmittedNeutrons( 5.15 ),
		  3.12383700000e+00 );
  FRENSIE_CHECK_EQUAL(
	       multiplicity_dist->getAverageNumberOfEmittedNeutrons( 30.0 ),
	       6.41410900000e+00 );
}

//---------------------------------------------------------------------------//
// Check that the prompt nu-bar can be evaluated correctly
FRENSIE_UNIT_TEST( FissionNeutronMultiplicityDistribution,
		   getAverageNumberOfPromptNeutrons )
{
  FRENSIE_CHECK_EQUAL(
	       multiplicity_dist->getAverageNumberOfPromptNeutrons( 1.0e-11 ),
	       2.44808800000e+00 );
  FRENSIE_CHECK_EQUAL(
		  multiplicity_dist->getAverageNumberOfPromptNeutrons( 5.15 ),
		  3.08397700000e+00 );
  FRENSIE_CHECK_EQUAL(
	       multiplicity_dist->getAverageNumberOfPromptNeutrons( 30.0 ),
	       6.38810900000e+00 );
}

//---------------------------------------------------------------------------//
// Check that the prompt nu-bar can be evaluated correctly
FRENSIE_UNIT_TEST( FissionNeutronMultiplicityDistribution,
		   getAverageNumberOfDelayedNeutrons )
{
  FRENSIE_CHECK_EQUAL(
	       multiplicity_dist->getAverageNumberOfDelayedNeutrons( 1.0e-11 ),
	       4.40000000000e-02 );
  FRENSIE_CHECK_EQUAL(
		  multiplicity_dist->getAverageNumberOfDelayedNeutrons( 4.0 ),
		  4.40000000000e-02 );
  FRENSIE_CHECK_EQUAL(
	       multiplicity_dist->getAverageNumberOfDelayedNeutrons( 30.0 ),
	       2.60000000000e-02 );
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
  xss_data_extractor(
   new Data::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

  std::unique_ptr<MonteCarlo::FissionNeutronMultiplicityDistributionACEFactory>
  multiplicity_dist_factory(
	      new MonteCarlo::FissionNeutronMultiplicityDistributionACEFactory(
				     ace_file_handler->getTableName(),
				     xss_data_extractor->extractNUBlock(),
				     xss_data_extractor->extractDNUBlock() ) );

  multiplicity_dist_factory->createDistribution( multiplicity_dist );

  ace_file_handler.reset();
  xss_data_extractor.reset();
  multiplicity_dist_factory.reset();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstFissionNeutronMultiplicityDistribution.cpp
//---------------------------------------------------------------------------//

