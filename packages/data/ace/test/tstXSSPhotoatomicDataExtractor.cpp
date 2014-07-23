//---------------------------------------------------------------------------//
//!
//! \file   tstXSSPhotoatomicDataExtractor.cpp
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
#include "Data_XSSPhotoatomicDataExtractor.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::string test_ace_file_name;
std::string test_ace_table_name;

Teuchos::RCP<Data::ACEFileHandler> ace_file_handler;

Teuchos::RCP<Data::XSSPhotoatomicDataExtractor> xss_data_extractor;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can check if fluorescence data
// is present
TEUCHOS_UNIT_TEST( XSSPhotoatomicDataExtractor, hasFluorescenceData )
{
  TEST_ASSERT( xss_data_extractor->hasFluorescenceData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can check if shell occupancy
// data is present
TEUCHOS_UNIT_TEST( XSSPhotoatomicDataExtractor, hasElectronShellOccupancyData )
{
  TEST_ASSERT( xss_data_extractor->hasElectronShellOccupancyData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can check if compton profile
// data is present
TEUCHOS_UNIT_TEST( XSSPhotoatomicDataExtractor, hasComptonProfileData )
{
  TEST_ASSERT( xss_data_extractor->hasComptonProfileData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the ESZG block
TEUCHOS_UNIT_TEST( XSSPhotoatomicDataExtractor, extractESZGBlock )
{
  Teuchos::ArrayView<const double> eszg_block = 
    xss_data_extractor->extractESZGBlock();

  TEST_EQUALITY_CONST( eszg_block.size(), 6315 );
  TEST_EQUALITY_CONST( eszg_block.front(), -6.90775527898e+00 );
  TEST_EQUALITY_CONST( eszg_block.back(), 3.71803283438e+00 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the energy grid
TEUCHOS_UNIT_TEST( XSSPhotoatomicDataExtractor, extractEnergyGrid )
{
  Teuchos::ArrayView<const double> energy_grid = 
    xss_data_extractor->extractEnergyGrid();

  TEST_EQUALITY_CONST( energy_grid.size(), 1263 );
  TEST_EQUALITY_CONST( energy_grid.front(), -6.90775527898e+00 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.15129254650e+01 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the incoherent
// cross section
TEUCHOS_UNIT_TEST( XSSPhotoatomicDataExtractor, extractIncoherentCrossSection )
{
  Teuchos::ArrayView<const double> incoherent_cross_section = 
    xss_data_extractor->extractIncoherentCrossSection();

  TEST_EQUALITY_CONST( incoherent_cross_section.size(), 1263 );
  TEST_EQUALITY_CONST( incoherent_cross_section.front(),2.11151938462e-01 );
  TEST_EQUALITY_CONST( incoherent_cross_section.back(), -6.57328504503e+00 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the coherent
// cross section
TEUCHOS_UNIT_TEST( XSSPhotoatomicDataExtractor, extractCoherentCrossSection )
{
  Teuchos::ArrayView<const double> coherent_cross_section = 
    xss_data_extractor->extractCoherentCrossSection();

  TEST_EQUALITY_CONST( coherent_cross_section.size(), 1263 );
  TEST_EQUALITY_CONST( coherent_cross_section.front(), 7.72666576631e+00 );
  TEST_EQUALITY_CONST( coherent_cross_section.back(), -2.30949823825e+01 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the photoelectric
// cross section
TEUCHOS_UNIT_TEST( XSSPhotoatomicDataExtractor, 
		   extractPhotoelectricCrossSection )
{
  Teuchos::ArrayView<const double> photoelectric_cross_section = 
    xss_data_extractor->extractPhotoelectricCrossSection();

  TEST_EQUALITY_CONST( photoelectric_cross_section.size(), 1263 );
  TEST_EQUALITY_CONST( photoelectric_cross_section.front(), 1.43969286532e+01);
  TEST_EQUALITY_CONST( photoelectric_cross_section.back(), -1.11594725061e+01);
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the pair production
// cross section
TEUCHOS_UNIT_TEST( XSSPhotoatomicDataExtractor,
		   extractPairProductionCrossSection )
{
  Teuchos::ArrayView<const double> pair_production_cross_section = 
    xss_data_extractor->extractPairProductionCrossSection();

  TEST_EQUALITY_CONST( pair_production_cross_section.size(), 1263 );
  TEST_EQUALITY_CONST( pair_production_cross_section.front(), 0.0 );
  TEST_EQUALITY_CONST( pair_production_cross_section.back(), 
		       3.71803283438e+00 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the JINC block
TEUCHOS_UNIT_TEST( XSSPhotoatomicDataExtractor, extractJINCBlock )
{
  Teuchos::ArrayView<const double> jinc_block = 
    xss_data_extractor->extractJINCBlock();

  TEST_EQUALITY_CONST( jinc_block.size(), 21 );
  TEST_EQUALITY_CONST( jinc_block.front(), 0.0 );
  TEST_EQUALITY_CONST( jinc_block.back(), 7.85210000000e+01 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the JCOH block
TEUCHOS_UNIT_TEST( XSSPhotoatomicDataExtractor, extractJCOHBlock )
{
  Teuchos::ArrayView<const double> jcoh_block = 
    xss_data_extractor->extractJCOHBlock();

  TEST_EQUALITY_CONST( jcoh_block.size(), 110 );
  TEST_EQUALITY_CONST( jcoh_block.front(), 0.0 );
  TEST_EQUALITY_CONST( jcoh_block.back(), 3.87140000000e+00 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the JFLO block
TEUCHOS_UNIT_TEST( XSSPhotoatomicDataExtractor, extractJFLOBlock )
{
  Teuchos::ArrayView<const double> jflo_block =
    xss_data_extractor->extractJFLOBlock();

  TEST_EQUALITY_CONST( jflo_block.size(), 24 );
  TEST_EQUALITY_CONST( jflo_block.front(), 1.47126666667e-02 );
  TEST_EQUALITY_CONST( jflo_block.back(), 8.76202453125e-02 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the LHNM block
TEUCHOS_UNIT_TEST( XSSPhotoatomicDataExtractor, extractLHNMBlock )
{
  Teuchos::ArrayView<const double> lhnm_block = 
    xss_data_extractor->extractLHNMBlock();

  TEST_EQUALITY_CONST( lhnm_block.size(), 1263 );
  TEST_EQUALITY_CONST( lhnm_block.front(), 9.98732853634e-04 );
  TEST_EQUALITY_CONST( lhnm_block.back(), 9.99986424397e+04 );
}	  

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the LNEPS block
TEUCHOS_UNIT_TEST( XSSPhotoatomicDataExtractor, extractLNEPSBlock )
{
  Teuchos::ArrayView<const double> lneps_block = 
    xss_data_extractor->extractLNEPSBlock();

  TEST_EQUALITY_CONST( lneps_block.size(), 23 );
  TEST_EQUALITY_CONST( lneps_block.front(), 2 );
  TEST_EQUALITY_CONST( lneps_block.back(), 2 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the LBEPS block
TEUCHOS_UNIT_TEST( XSSPhotoatomicDataExtractor, extractLBEPSBlock )
{
  Teuchos::ArrayView<const double> lbeps_block = 
    xss_data_extractor->extractLBEPSBlock();

  TEST_EQUALITY_CONST( lbeps_block.size(), 23 );
  TEST_EQUALITY_CONST( lbeps_block.front(), 8.800500000000e-02 );
  TEST_EQUALITY_CONST( lbeps_block.back(), 0.000000000000e+00 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the LPIPS block
TEUCHOS_UNIT_TEST( XSSPhotoatomicDataExtractor, extractLPIPSBlock )
{
  Teuchos::ArrayView<const double> lpips_block = 
    xss_data_extractor->extractLPIPSBlock();

  TEST_EQUALITY_CONST( lpips_block.size(), 23 );
  TEST_EQUALITY_CONST( lpips_block.front(), 2.439024390244e-02 );
  TEST_EQUALITY_CONST( lpips_block.back(), 2.439024390244e-02 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the LSWD block
TEUCHOS_UNIT_TEST( XSSPhotoatomicDataExtractor, extractLSWDBlock )
{
  Teuchos::ArrayView<const double> lswd_block = 
    xss_data_extractor->extractLSWDBlock();

  TEST_EQUALITY_CONST( lswd_block.size(), 23 );
  TEST_EQUALITY_CONST( lswd_block.front(), 1 );
  TEST_EQUALITY_CONST( lswd_block.back(), 2091 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the SWD block
TEUCHOS_UNIT_TEST( XSSPhotoatomicDataExtractor, extractSWDBlock )
{
  Teuchos::ArrayView<const double> swd_block = 
    xss_data_extractor->extractSWDBlock();

  TEST_EQUALITY_CONST( swd_block.size(), 2185 );
  TEST_EQUALITY_CONST( swd_block.front(), 2 );
  TEST_EQUALITY_CONST( swd_block.back(), 1.000000000000e+00 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_ace_file",
		 &test_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_ace_table",
		 &test_ace_table_name,
		 "Test ACE table name in ACE file" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  // Initialize ace file handler and data extractor
  ace_file_handler.reset( new Data::ACEFileHandler( test_ace_file_name,
						    test_ace_table_name,
						    1u ) );

  xss_data_extractor.reset( 
   new Data::XSSPhotoatomicDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
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
// end tstXSSPhotoatomicDataExtractor.cpp
//---------------------------------------------------------------------------//

