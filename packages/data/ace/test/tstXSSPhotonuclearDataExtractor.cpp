//---------------------------------------------------------------------------//
//! 
//! \file   tstXSSPhotonuclearDataExtractor.cpp
//! \author Ryan Pease
//! \brief  XSS photonuclear data extractor class unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSPhotonuclearDataExtractor.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::XSSPhotonuclearDataExtractor> h2_xss_data_extractor;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can check if elastic scattering
// data is present
TEUCHOS_UNIT_TEST( XSSPhotonuclearDataExtractor, hasElasticScatteringData )
{
  TEST_ASSERT( !h2_xss_data_extractor->hasElasticScatteringData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can check if average heating
// number data is present
TEUCHOS_UNIT_TEST( XSSPhotonuclearDataExtractor, hasHeatingNumberData )
{
  TEST_ASSERT( h2_xss_data_extractor->hasHeatingNumberData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotonuclearDataExtractor can extract the ESZ data block
TEUCHOS_UNIT_TEST( XSSPhotonuclearDataExtractor, extractESZBlock )
{
  Teuchos::ArrayView<const double> esz_block =
    h2_xss_data_extractor->extractESZBlock();
  
  TEST_EQUALITY_CONST( esz_block.size() , 35)
  TEST_EQUALITY_CONST( esz_block.front() , 2.2246e0)
  TEST_EQUALITY_CONST( esz_block.back() , 3.0e1)

}

// Check that the XSSPhotonuclearDataExtractor can extract the TOT data block
TEUCHOS_UNIT_TEST( XSSPhotonuclearDataExtractor, extractTOTBlock )
{
  Teuchos::ArrayView<const double> tot_block =
    h2_xss_data_extractor->extractTOTBlock();

  TEST_EQUALITY_CONST( tot_block.size() , 35)
  TEST_EQUALITY_CONST( tot_block.front() , 0)
  TEST_EQUALITY_CONST( tot_block.back() , 3.549e-4)

}

// Check that the XSSPhotonuclearDataExtractor can extract the NON data block
TEUCHOS_UNIT_TEST( XSSPhotonuclearDataExtractor, extractNONBlock )
{
  Teuchos::ArrayView<const double> non_block =
    h2_xss_data_extractor->extractNONBlock();  

  TEST_EQUALITY_CONST( non_block.size() , 35)
  TEST_EQUALITY_CONST( non_block.front() , 0)
  TEST_EQUALITY_CONST( non_block.back() , 3.549e-4)

}

// Check that the XSSPhotonuclearDataExtractor can extract the ELS data block
TEUCHOS_UNIT_TEST( XSSPhotonuclearDataExtractor, extractELSBlock )
{
  Teuchos::ArrayView<const double> els_block =
    h2_xss_data_extractor->extractELSBlock();

  TEST_EQUALITY_CONST( els_block.size() , 0)
 
}

// Check that the XSSPhotonuclearDataExtractor can extract the THN data block
TEUCHOS_UNIT_TEST( XSSPhotonuclearDataExtractor, extractTHNBlock )
{
  Teuchos::ArrayView<const double> thn_block = 
    h2_xss_data_extractor->extractTHNBlock();

  TEST_EQUALITY_CONST( thn_block.size() , 35)
  TEST_EQUALITY_CONST( thn_block.front() , 0)
  TEST_EQUALITY_CONST( thn_block.back() , 6.939968e1)
 
}

// Check that the XSSPhotonuclearDataExtractor can extract the MTR data block
TEUCHOS_UNIT_TEST( XSSPhotonuclearDataExtractor, extractMTRBlock )
{
  Teuchos::ArrayView<const double> mtr_block = 
    h2_xss_data_extractor->extractMTRBlock();

  TEST_EQUALITY_CONST( mtr_block.size() , 1)
  TEST_EQUALITY_CONST( mtr_block.front() , 50)

}

// Check that the XSSPhotonuclearDataExtractor can extract the LQR data block
TEUCHOS_UNIT_TEST( XSSPhotonuclearDataExtractor, extractLQRBlock )
{
  Teuchos::ArrayView<const double> lqr_block = 
    h2_xss_data_extractor->extractLQRBlock();

  TEST_EQUALITY_CONST( lqr_block.size() , 1)
  TEST_EQUALITY_CONST( lqr_block.front() , -2.2246)

}

// Check that the XSSPhotonuclearDataExtractor can extract the LSIG data block
TEUCHOS_UNIT_TEST( XSSPhotonuclearDataExtractor, extractLSIGBlock )
{
  Teuchos::ArrayView<const double> lsig_block =
    h2_xss_data_extractor->extractLSIGBlock();

  TEST_EQUALITY_CONST( lsig_block.size() , 1)
  TEST_EQUALITY_CONST( lsig_block.front() , 1)
 
}

// Check that the XSSPhotonuclearDataExtractor can extract the SIG data block
TEUCHOS_UNIT_TEST( XSSPhotonuclearDataExtractor, extractSIGBlock )
{
  Teuchos::ArrayView<const double> sig_block = 
    h2_xss_data_extractor->extractSIGBlock();

  TEST_EQUALITY_CONST( sig_block.size() , 37)
  TEST_EQUALITY_CONST( sig_block.front() , 1)
  TEST_EQUALITY_CONST( sig_block.back() , 3.549e-4)

}

// Check that the XSSPhotonuclearDataExtractor can extract the IXS data block
TEUCHOS_UNIT_TEST( XSSPhotonuclearDataExtractor, extractIXSBlock )
{
  Teuchos::ArrayView<const double> ixs_block = 
    h2_xss_data_extractor->extractIXSBlock();

  TEST_EQUALITY_CONST( ixs_block.size() , 3541 )
  TEST_EQUALITY_CONST( ixs_block.front() , 1)
  TEST_EQUALITY_CONST( ixs_block.back() , 6.66255e-1)

}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{

  std::string h2_ace_file_name, h2_ace_table_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "h2_ace_file",
                 &h2_ace_file_name,
		 "Test H2 ACE file name" );
  clp.setOption( "h2_ace_table",
		 &h2_ace_table_name,
		 "Test H2 ACE table name in ACE file" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  // Initialize ace file handler and data extractor
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
			        new Data::ACEFileHandler( h2_ace_file_name,
							  h2_ace_table_name,
							  1u ) );
  
  h2_xss_data_extractor.reset( 
      new Data::XSSPhotonuclearDataExtractor( 
				     ace_file_handler->getTableNXSArray(),
				     ace_file_handler->getTableJXSArray(),
				     ace_file_handler->getTableXSSArray() ) );

  // Clear setup data
  ace_file_handler.reset();

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
// end tstXSSPhotonuclearDataExtractor.cpp
//---------------------------------------------------------------------------//
