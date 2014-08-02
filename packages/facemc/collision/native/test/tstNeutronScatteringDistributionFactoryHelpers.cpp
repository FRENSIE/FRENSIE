//---------------------------------------------------------------------------//
//! 
//! \file   tstNeutronScatteringDistributionFactoryHelpers.cpp
//! \author Alex Robinson
//! \brief  Neutron scattering distribution factory helpers unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Facemc_NeutronScatteringDistributionFactoryHelpers.hpp"
#include "Facemc_NuclearReactionType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::string test_u238_ace_file_name;
std::string test_u238_ace_table_name;

Teuchos::RCP<Data::ACEFileHandler> ace_file_handler_u238;

Teuchos::RCP<Data::XSSNeutronDataExtractor> xss_data_extractor_u238;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the size of the arrays in the and block can be calculated
TEUCHOS_UNIT_TEST( NeutronScatteringDistributionFactoryHelpers,
		   calculateDistArraySizes_and_block )
{
  Teuchos::Array<unsigned> dist_array_sizes;

  Facemc::calculateDistArraySizes( xss_data_extractor_u238->extractLANDBlock(),
				   xss_data_extractor_u238->extractANDBlock(),
				   dist_array_sizes );

  TEST_EQUALITY( dist_array_sizes.size(), 
		 xss_data_extractor_u238->extractLANDBlock().size() );
  TEST_EQUALITY_CONST( dist_array_sizes[0], 9825 );
  TEST_EQUALITY_CONST( dist_array_sizes[1], 0 );
  TEST_EQUALITY_CONST( dist_array_sizes[2], 0 );
  TEST_EQUALITY_CONST( dist_array_sizes[3], 0 );
  TEST_EQUALITY_CONST( dist_array_sizes[4], 0 );
  TEST_EQUALITY_CONST( dist_array_sizes[5], 6686 );
  TEST_EQUALITY_CONST( dist_array_sizes[6], 4578 );
  TEST_EQUALITY_CONST( dist_array_sizes[7], 3652 );
  TEST_EQUALITY_CONST( dist_array_sizes[8], 842 );
  TEST_EQUALITY_CONST( dist_array_sizes[9], 1006 );
  TEST_EQUALITY_CONST( dist_array_sizes[10], 750 );
  TEST_EQUALITY_CONST( dist_array_sizes[11], 651 );
  TEST_EQUALITY_CONST( dist_array_sizes[12], 680 );
  TEST_EQUALITY_CONST( dist_array_sizes[13], 1157 );
  TEST_EQUALITY_CONST( dist_array_sizes[14], 994 );
  TEST_EQUALITY_CONST( dist_array_sizes[15], 786 );
  TEST_EQUALITY_CONST( dist_array_sizes[16], 726 );
  TEST_EQUALITY_CONST( dist_array_sizes[17], 768 );
  TEST_EQUALITY_CONST( dist_array_sizes[18], 1170 );
  TEST_EQUALITY_CONST( dist_array_sizes[19], 690 );
  TEST_EQUALITY_CONST( dist_array_sizes[20], 750 );
  TEST_EQUALITY_CONST( dist_array_sizes[21], 666 );
  TEST_EQUALITY_CONST( dist_array_sizes[22], 678 );
  TEST_EQUALITY_CONST( dist_array_sizes[23], 759 );
  TEST_EQUALITY_CONST( dist_array_sizes[24], 482 );
  TEST_EQUALITY_CONST( dist_array_sizes[25], 656 );
  TEST_EQUALITY_CONST( dist_array_sizes[26], 3304 );
  TEST_EQUALITY_CONST( dist_array_sizes[27], 3358 );
  TEST_EQUALITY_CONST( dist_array_sizes[28], 3168 );
  TEST_EQUALITY_CONST( dist_array_sizes[29], 3114 );
  TEST_EQUALITY_CONST( dist_array_sizes[30], 3066 );
  TEST_EQUALITY_CONST( dist_array_sizes[31], 3015 );
  TEST_EQUALITY_CONST( dist_array_sizes[32], 2945 );
  TEST_EQUALITY_CONST( dist_array_sizes[33], 2888 );
  TEST_EQUALITY_CONST( dist_array_sizes[34], 2807 );
  TEST_EQUALITY_CONST( dist_array_sizes[35], 1945 );
  TEST_EQUALITY_CONST( dist_array_sizes[36], 2956 );
  TEST_EQUALITY_CONST( dist_array_sizes[37], 2865 );
  TEST_EQUALITY_CONST( dist_array_sizes[38], 2808 );
  TEST_EQUALITY_CONST( dist_array_sizes[39], 2726 );
  TEST_EQUALITY_CONST( dist_array_sizes[40], 2690 );
  TEST_EQUALITY_CONST( dist_array_sizes[41], 2672 );
  TEST_EQUALITY_CONST( dist_array_sizes[42], 2630 );
  TEST_EQUALITY_CONST( dist_array_sizes[43], 2627 );
  TEST_EQUALITY_CONST( dist_array_sizes[44], 2557 );
  TEST_EQUALITY_CONST( dist_array_sizes[45], 0 );
}

//---------------------------------------------------------------------------//
// Check that the size of the arrays in the and block can be calculated
TEUCHOS_UNIT_TEST( NeutronScatteringDistributionFactoryHelpers,
		   calculateDistArraySizes_dlw_block )
{
  Teuchos::Array<unsigned> dist_array_sizes;

  Facemc::calculateDistArraySizes( xss_data_extractor_u238->extractLDLWBlock(),
				   xss_data_extractor_u238->extractDLWBlock(),
				   dist_array_sizes );

  TEST_EQUALITY( dist_array_sizes.size(), 
		 xss_data_extractor_u238->extractLDLWBlock().size() );
  TEST_EQUALITY_CONST( dist_array_sizes[0], 13138 );
  TEST_EQUALITY_CONST( dist_array_sizes[1], 6566 );
  TEST_EQUALITY_CONST( dist_array_sizes[2], 48336 );
  TEST_EQUALITY_CONST( dist_array_sizes[3], 2473 );
  TEST_EQUALITY_CONST( dist_array_sizes[4], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[5], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[6], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[7], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[8], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[9], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[10], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[11], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[12], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[13], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[14], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[15], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[16], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[17], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[18], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[19], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[20], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[21], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[22], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[23], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[24], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[25], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[26], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[27], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[28], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[29], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[30], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[31], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[32], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[33], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[34], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[35], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[36], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[37], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[38], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[39], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[40], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[41], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[42], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[43], 11 );
  TEST_EQUALITY_CONST( dist_array_sizes[44], 41302 );
}

//---------------------------------------------------------------------------//
// Check that the size of the arrays in the and block can be calculated
TEUCHOS_UNIT_TEST( NeutronScatteringDistributionFactoryHelpers,
		   calculateDistArraySizes_dned_block )
{
  Teuchos::Array<unsigned> dist_array_sizes;

  Facemc::calculateDistArraySizes(xss_data_extractor_u238->extractDNEDLBlock(),
				  xss_data_extractor_u238->extractDNEDBlock(),
				  dist_array_sizes );

  TEST_EQUALITY( dist_array_sizes.size(), 
		 xss_data_extractor_u238->extractDNEDLBlock().size() );
  TEST_EQUALITY_CONST( dist_array_sizes[0], 1129 );
  TEST_EQUALITY_CONST( dist_array_sizes[1], 1339 );
  TEST_EQUALITY_CONST( dist_array_sizes[2], 1825 );
  TEST_EQUALITY_CONST( dist_array_sizes[3], 1825 );
  TEST_EQUALITY_CONST( dist_array_sizes[4], 1825 );
  TEST_EQUALITY_CONST( dist_array_sizes[5], 1825 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_u238_ace_file",
		 &test_u238_ace_file_name,
		 "Test U238 ACE file name" );
  clp.setOption( "test_u238_ace_table",
		 &test_u238_ace_table_name,
		 "Test U238 ACE table name in basic ACE file" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Initialize ace file handler and data extractor
  ace_file_handler_u238.reset( new Data::ACEFileHandler( test_u238_ace_file_name,
						    test_u238_ace_table_name,
						    1u ) );

  xss_data_extractor_u238.reset( 
   new Data::XSSNeutronDataExtractor( ace_file_handler_u238->getTableNXSArray(),
				      ace_file_handler_u238->getTableJXSArray(),
				      ace_file_handler_u238->getTableXSSArray() ) );

  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1); 
}

//---------------------------------------------------------------------------//
// end tstNeutronScatteringDistributionFactoryHelpers.cpp
//---------------------------------------------------------------------------//

