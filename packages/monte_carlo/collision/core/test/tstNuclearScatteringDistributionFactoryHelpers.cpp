//---------------------------------------------------------------------------//
//!
//! \file   tstNuclearScatteringDistributionFactoryHelpers.cpp
//! \author Alex Robinson
//! \brief  Neutron scattering distribution factory helpers unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistributionFactoryHelpers.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<Data::ACEFileHandler> ace_file_handler_u238;

std::shared_ptr<Data::XSSNeutronDataExtractor> xss_data_extractor_u238;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the size of the arrays in the and block can be calculated
FRENSIE_UNIT_TEST( NuclearScatteringDistributionFactoryHelpers,
		   calculateDistArraySizes_and_block )
{
  std::vector<unsigned> dist_array_sizes;

  MonteCarlo::calculateDistArraySizes( xss_data_extractor_u238->extractLANDBlock(),
                                       xss_data_extractor_u238->extractANDBlock(),
                                       dist_array_sizes );

  FRENSIE_CHECK_EQUAL( dist_array_sizes.size(),
                       xss_data_extractor_u238->extractLANDBlock().size() );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[0], 9825 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[1], 0 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[2], 0 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[3], 0 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[4], 0 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[5], 6686 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[6], 4578 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[7], 3652 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[8], 842 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[9], 1006 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[10], 750 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[11], 651 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[12], 680 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[13], 1157 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[14], 994 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[15], 786 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[16], 726 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[17], 768 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[18], 1170 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[19], 690 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[20], 750 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[21], 666 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[22], 678 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[23], 759 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[24], 482 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[25], 656 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[26], 3304 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[27], 3358 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[28], 3168 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[29], 3114 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[30], 3066 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[31], 3015 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[32], 2945 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[33], 2888 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[34], 2807 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[35], 1945 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[36], 2956 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[37], 2865 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[38], 2808 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[39], 2726 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[40], 2690 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[41], 2672 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[42], 2630 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[43], 2627 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[44], 2557 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[45], 0 );
}

//---------------------------------------------------------------------------//
// Check that the size of the arrays in the and block can be calculated
FRENSIE_UNIT_TEST( NuclearScatteringDistributionFactoryHelpers,
		   calculateDistArraySizes_dlw_block )
{
  std::vector<unsigned> dist_array_sizes;

  MonteCarlo::calculateDistArraySizes( xss_data_extractor_u238->extractLDLWBlock(),
                                       xss_data_extractor_u238->extractDLWBlock(),
                                       dist_array_sizes );

  FRENSIE_CHECK_EQUAL( dist_array_sizes.size(),
                       xss_data_extractor_u238->extractLDLWBlock().size() );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[0], 13138 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[1], 6566 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[2], 48336 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[3], 2473 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[4], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[5], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[6], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[7], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[8], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[9], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[10], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[11], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[12], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[13], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[14], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[15], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[16], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[17], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[18], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[19], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[20], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[21], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[22], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[23], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[24], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[25], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[26], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[27], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[28], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[29], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[30], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[31], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[32], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[33], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[34], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[35], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[36], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[37], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[38], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[39], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[40], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[41], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[42], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[43], 11 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[44], 41302 );
}

//---------------------------------------------------------------------------//
// Check that the size of the arrays in the and block can be calculated
FRENSIE_UNIT_TEST( NuclearScatteringDistributionFactoryHelpers,
		   calculateDistArraySizes_dned_block )
{
  std::vector<unsigned> dist_array_sizes;

  MonteCarlo::calculateDistArraySizes(xss_data_extractor_u238->extractDNEDLBlock(),
                                      xss_data_extractor_u238->extractDNEDBlock(),
                                      dist_array_sizes );

  FRENSIE_CHECK_EQUAL( dist_array_sizes.size(),
                       xss_data_extractor_u238->extractDNEDLBlock().size() );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[0], 1129 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[1], 1339 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[2], 1825 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[3], 1825 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[4], 1825 );
  FRENSIE_CHECK_EQUAL( dist_array_sizes[5], 1825 );
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
  // Initialize ace file handler and data extractor
  ace_file_handler_u238.reset(
                   new Data::ACEFileHandler( test_u238_ace_file_name,
                                             "92238.70c",
                                             test_u238_ace_file_start_line ) );

  xss_data_extractor_u238.reset( new Data::XSSNeutronDataExtractor(
                                 ace_file_handler_u238->getTableNXSArray(),
                                 ace_file_handler_u238->getTableJXSArray(),
                                 ace_file_handler_u238->getTableXSSArray() ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstNuclearScatteringDistributionFactoryHelpers.cpp
//---------------------------------------------------------------------------//

