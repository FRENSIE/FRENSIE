//---------------------------------------------------------------------------//
//!
//! \file   tstXSSNeutronDataExtractor.cpp
//! \author Alex Robinson
//! \brief  XSS neutron data extractor class unit tests.
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
#include "Data_XSSNeutronDataExtractor.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string test_h1_ace_file_name;
std::string test_h1_ace_table_name;
// std::string test_fission_ace_file_name;
// std::string test_ptable_ace_file_name;
// std::string test_fission_ptable_ace_file_name;

Teuchos::RCP<Data::ACEFileHandler> ace_file_handler;

Teuchos::RCP<Data::XSSNeutronDataExtractor> xss_data_extractor;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can check if fission data is present
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, hasFissionData_h1 )
{
  TEST_ASSERT( !xss_data_extractor->hasFissionData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can check if unresolved resonance
// data is present
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, hasUnresolvedResonanceData_h1 )
{
  TEST_ASSERT( !xss_data_extractor->hasUnresolvedResonanceData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the ESZ block from the 
// XSS array
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractESZBlock_h1 )
{
  Teuchos::ArrayView<const double> esz_block = 
    xss_data_extractor->extractESZBlock();

  TEST_EQUALITY_CONST( esz_block.size(), 590*5 );
  TEST_EQUALITY_CONST( esz_block.front(), 1e-11 );
  TEST_EQUALITY_CONST( esz_block.back(), 1.016085e1 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the energy grid from the
// XSS array
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractEnergyGrid_h1 )
{
  Teuchos::ArrayView<const double> energy_grid = 
    xss_data_extractor->extractEnergyGrid();

  TEST_EQUALITY_CONST( energy_grid.size(), 590 );
  TEST_EQUALITY_CONST( energy_grid.front(), 1e-11 );
  TEST_EQUALITY_CONST( energy_grid.back(), 2e1 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the total cross section
// from the XSS array
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractTotalCrossSec_h1 )
{
  Teuchos::ArrayView<const double> total_cross_sec = 
    xss_data_extractor->extractTotalCrossSection();

  TEST_EQUALITY_CONST( total_cross_sec.size(), 590 );
  TEST_EQUALITY_CONST( total_cross_sec.front(), 1.17724711e3 );
  TEST_EQUALITY_CONST( total_cross_sec.back(), 4.82773424e-1 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the total absorption
// cross section from the XSS array
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractAbsorptionCrossSec_h1 )
{
  Teuchos::ArrayView<const double> absorption_cross_sec =
    xss_data_extractor->extractTotalAbsorptionCrossSection();

  TEST_EQUALITY_CONST( absorption_cross_sec.size(), 590 );
  TEST_EQUALITY_CONST( absorption_cross_sec.front(), 1.670111e1 );
  TEST_EQUALITY_CONST( absorption_cross_sec.back(), 2.722354e-5 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the elastic cross section
// from the XSS array
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractElasticCrossSection_h1 )
{
  Teuchos::ArrayView<const double> elastic_cross_sec = 
    xss_data_extractor->extractElasticCrossSection();

  TEST_EQUALITY_CONST( elastic_cross_sec.size(), 590 );
  TEST_EQUALITY_CONST( elastic_cross_sec.front(), 1.160546e3 );
  TEST_EQUALITY_CONST( elastic_cross_sec.back(), 4.827462e-1 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the average heating
// numbers from the XSS array
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractAverageHeatingNumbers_h1)
{
  Teuchos::ArrayView<const double> ave_heating_nums =
    xss_data_extractor->extractAverageHeatingNumbers();

  TEST_EQUALITY_CONST( ave_heating_nums.size(), 590 );
  TEST_EQUALITY_CONST( ave_heating_nums.front(), 5.000028e-12 );
  TEST_EQUALITY_CONST( ave_heating_nums.back(), 1.016085e1 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the NU block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractNUBlock_h1 )
{
  Teuchos::ArrayView<const double> nu_block = 
    xss_data_extractor->extractNUBlock();

  TEST_EQUALITY_CONST( nu_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the MTR block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractMTRBlock_h1 )
{
  Teuchos::ArrayView<const double> mtr_block = 
    xss_data_extractor->extractMTRBlock();

  TEST_EQUALITY_CONST( mtr_block.size(), 3 );
  TEST_EQUALITY_CONST( mtr_block[0], 102 );
  TEST_EQUALITY_CONST( mtr_block[1], 204 );
  TEST_EQUALITY_CONST( mtr_block[2], 444 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the MTRP block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractMTRPBlock_h1 )
{
  Teuchos::ArrayView<const double> mtrp_block = 
    xss_data_extractor->extractMTRPBlock();

  TEST_EQUALITY_CONST( mtrp_block.size(), 1 );
  TEST_EQUALITY_CONST( mtrp_block.front(), 102001 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LQR block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractLQRBlock_h1 )
{
  Teuchos::ArrayView<const double> lqr_block = 
    xss_data_extractor->extractLQRBlock();

  TEST_EQUALITY_CONST( lqr_block.size(), 3 );
  TEST_EQUALITY_CONST( lqr_block[0], 2.224631e0 );
  TEST_EQUALITY_CONST( lqr_block[1], 0.0 );
  TEST_EQUALITY_CONST( lqr_block[2], 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the TYR block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractTYRBlock_h1 )
{
  Teuchos::ArrayView<const double> tyr_block = 
    xss_data_extractor->extractTYRBlock();

  TEST_EQUALITY_CONST( tyr_block.size(), 3 );
  TEST_EQUALITY_CONST( tyr_block[0], 0.0 );
  TEST_EQUALITY_CONST( tyr_block[1], 0.0 );
  TEST_EQUALITY_CONST( tyr_block[2], 0.0 );  
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LSIG block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractLSIGBlock_h1 )
{
  Teuchos::ArrayView<const double> lsig_block = 
    xss_data_extractor->extractLSIGBlock();

  TEST_EQUALITY_CONST( lsig_block.size(), 3 );
  TEST_EQUALITY_CONST( lsig_block[0], 1 );
  TEST_EQUALITY_CONST( lsig_block[1], 593 );
  TEST_EQUALITY_CONST( lsig_block[2], 1185 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LSIGP block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractLSIGPBlock_h1 )
{
  Teuchos::ArrayView<const double> lsigp_block = 
    xss_data_extractor->extractLISGPBlock();

  TEST_EQUALITY_CONST( lsigp_block.size(), 1 );
  TEST_EQUALITY_CONST( lsigp_block.front(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the SIG block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractSIGBlock_h1 )
{
  Teuchos::ArrayView<const double> sig_block =
    xss_data_extractor->extractSIGBlock();

  TEST_EQUALITY_CONST( sig_block.size(), 1389 );
  TEST_EQUALITY_CONST( sig_block.front(), 1 );
  TEST_EQUALITY_CONST( sig_block.back(), 3.067696e-4 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LAND block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractLANDBlock_h1 )
{
  Teuchos::ArrayView<const double> land_block =
    xss_data_extractor->extractLANDBlock();

  TEST_EQUALITY_CONST( land_block.size(), 1 );
  TEST_EQUALITY_CONST( land_block.front(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the AND block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractANDBlock_h1 )
{
  Teuchos::ArrayView<const double> and_block = 
    xss_data_extractor->extractANDBlock();

  TEST_EQUALITY_CONST( and_block.size(), 1291 );
  TEST_EQUALITY_CONST( and_block.front(), 96 );
  TEST_EQUALITY_CONST( and_block.back(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LDLW block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractLDLWBlock_h1 )
{
  Teuchos::ArrayView<const double> ldlw_block = 
    xss_data_extractor->extractLDLWBlock();

  TEST_EQUALITY_CONST( ldlw_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LDLWP block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractLDLWPBlock_h1 )
{
  Teuchos::ArrayView<const double> ldlwp_block = 
    xss_data_extractor->extractLDLWPBlock();

  TEST_EQUALITY_CONST( ldlwp_block.size(), 1 );
  TEST_EQUALITY_CONST( ldlwp_block.front(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the delayed neutron
// LDLW block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, 
		   extractDelayedNeutronLDLWBlock_h1 )
{
  Teuchos::ArrayView<const double> delayed_neutron_ldlw_block = 
    xss_data_extractor->extractDelayedNeutronLDLWBlock();

  TEST_EQUALITY_CONST( delayed_neutron_ldlw_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the DLW block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractDLWBlock_h1 )
{
  Teuchos::ArrayView<const double> dlw_block = 
    xss_data_extractor->extractDLWBlock();

  TEST_EQUALITY_CONST( dlw_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the DLWP block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractDLWPBlock_h1 )
{
  Teuchos::ArrayView<const double> dlwp_block = 
    xss_data_extractor->extractDLWPBlock();

  TEST_EQUALITY_CONST( dlwp_block.size(), 683 );
  TEST_EQUALITY_CONST( dlwp_block.front(), 0 );
  TEST_EQUALITY_CONST( dlwp_block.back(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the delayed neutron
// DLW block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, 
		   extractDelayedNeutronDLWBlock_h1 )
{
  Teuchos::ArrayView<const double> delayed_neutron_dlw_block = 
    xss_data_extractor->extractDelayedNeutronDLWBlock();

  TEST_EQUALITY_CONST( delayed_neutron_dlw_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the GPD block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractGPDBlock )
{
  Teuchos::ArrayView<const double> gpd_block = 
    xss_data_extractor->extractGPDBlock();

  TEST_EQUALITY_CONST( gpd_block.size(), 590 );
  TEST_EQUALITY_CONST( gpd_block.front(), 1.6701110e1 );
  TEST_EQUALITY_CONST( gpd_block.back(), 2.7223540e-5 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the SIGP block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractSIGPBlock )
{
  Teuchos::ArrayView<const double> sigp_block = 
    xss_data_extractor->extractSIGPBlock();

  TEST_EQUALITY_CONST( sigp_block.size(), 8 );
  TEST_EQUALITY_CONST( sigp_block.front(), 16 );
  TEST_EQUALITY_CONST( sigp_block.back(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LANDP block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractLANDPBlock )
{
  Teuchos::ArrayView<const double> landp_block = 
    xss_data_extractor->extractLANDPBlock();

  TEST_EQUALITY_CONST( landp_block.size(), 1 );
  TEST_EQUALITY_CONST( landp_block.front(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the ANDP block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractANDPBlock )
{
  Teuchos::ArrayView<const double> andp_block = 
    xss_data_extractor->extractANDPBlock();

  TEST_EQUALITY_CONST( andp_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the YP block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractYPBlock )
{
  Teuchos::ArrayView<const double> yp_block = 
    xss_data_extractor->extractYPBlock();

  TEST_EQUALITY_CONST( yp_block.size(), 2 );
  TEST_EQUALITY_CONST( yp_block.front(), 1 );
  TEST_EQUALITY_CONST( yp_block.back(), 102 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the FIS block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractFISBlock )
{
  Teuchos::ArrayView<const double> fis_block = 
    xss_data_extractor->extractFISBlock();

  TEST_EQUALITY_CONST( fis_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the UNR block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractUNRBlock )
{
  Teuchos::ArrayView<const double> unr_block = 
    xss_data_extractor->extractUNRBlock();

  TEST_EQUALITY_CONST( unr_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_h1_ace_file",
		 &test_h1_ace_file_name,
		 "Test h1 ACE file name" );
  clp.setOption( "test_h1_ace_table",
		 &test_h1_ace_table_name,
		 "Test h1 ACE table name in h1 ACE file" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  // Initialize ace file handler and data extractor
  ace_file_handler.reset( new Data::ACEFileHandler( test_h1_ace_file_name,
						    test_h1_ace_table_name,
						    1u ) );

  xss_data_extractor.reset( 
   new Data::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

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
// end tstXSSNeutronDataExtractor.cpp
//---------------------------------------------------------------------------//
