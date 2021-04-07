//---------------------------------------------------------------------------//
//!
//! \file   tstXSSPhotoatomicDataExtractor.cpp
//! \author Alex Robinson
//! \brief  XSS photoatomic data extractor class unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSPhotoatomicDataExtractor.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::shared_ptr<Data::XSSPhotoatomicDataExtractor> xss_data_extractor;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can check if fluorescence data
// is present
FRENSIE_UNIT_TEST( XSSPhotoatomicDataExtractor, hasFluorescenceData )
{
  FRENSIE_CHECK( xss_data_extractor->hasFluorescenceData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can check if shell occupancy
// data is present
FRENSIE_UNIT_TEST( XSSPhotoatomicDataExtractor, hasElectronShellOccupancyData )
{
  FRENSIE_CHECK( xss_data_extractor->hasElectronShellOccupancyData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can check if compton profile
// data is present
FRENSIE_UNIT_TEST( XSSPhotoatomicDataExtractor, hasComptonProfileData )
{
  FRENSIE_CHECK( xss_data_extractor->hasComptonProfileData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the ESZG block
FRENSIE_UNIT_TEST( XSSPhotoatomicDataExtractor, extractESZGBlock )
{
  Utility::ArrayView<const double> eszg_block =
    xss_data_extractor->extractESZGBlock();

  FRENSIE_CHECK_EQUAL( eszg_block.size(), 6315 );
  FRENSIE_CHECK_EQUAL( eszg_block.front(), -6.90775527898e+00 );
  FRENSIE_CHECK_EQUAL( eszg_block.back(), 3.71803283438e+00 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the energy grid
FRENSIE_UNIT_TEST( XSSPhotoatomicDataExtractor, extractEnergyGrid )
{
  Utility::ArrayView<const double> energy_grid =
    xss_data_extractor->extractEnergyGrid();

  FRENSIE_CHECK_EQUAL( energy_grid.size(), 1263 );
  FRENSIE_CHECK_EQUAL( energy_grid.front(), -6.90775527898e+00 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.15129254650e+01 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the incoherent
// cross section
FRENSIE_UNIT_TEST( XSSPhotoatomicDataExtractor, extractIncoherentCrossSection )
{
  Utility::ArrayView<const double> incoherent_cross_section =
    xss_data_extractor->extractIncoherentCrossSection();

  FRENSIE_CHECK_EQUAL( incoherent_cross_section.size(), 1263 );
  FRENSIE_CHECK_EQUAL( incoherent_cross_section.front(),2.11151938462e-01 );
  FRENSIE_CHECK_EQUAL( incoherent_cross_section.back(), -6.57328504503e+00 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the coherent
// cross section
FRENSIE_UNIT_TEST( XSSPhotoatomicDataExtractor, extractCoherentCrossSection )
{
  Utility::ArrayView<const double> coherent_cross_section =
    xss_data_extractor->extractCoherentCrossSection();

  FRENSIE_CHECK_EQUAL( coherent_cross_section.size(), 1263 );
  FRENSIE_CHECK_EQUAL( coherent_cross_section.front(), 7.72666576631e+00 );
  FRENSIE_CHECK_EQUAL( coherent_cross_section.back(), -2.30949823825e+01 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the photoelectric
// cross section
FRENSIE_UNIT_TEST( XSSPhotoatomicDataExtractor,
		   extractPhotoelectricCrossSection )
{
  Utility::ArrayView<const double> photoelectric_cross_section =
    xss_data_extractor->extractPhotoelectricCrossSection();

  FRENSIE_CHECK_EQUAL( photoelectric_cross_section.size(), 1263 );
  FRENSIE_CHECK_EQUAL( photoelectric_cross_section.front(), 1.43969286532e+01);
  FRENSIE_CHECK_EQUAL( photoelectric_cross_section.back(), -1.11594725061e+01);
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the pair production
// cross section
FRENSIE_UNIT_TEST( XSSPhotoatomicDataExtractor,
		   extractPairProductionCrossSection )
{
  Utility::ArrayView<const double> pair_production_cross_section =
    xss_data_extractor->extractPairProductionCrossSection();

  FRENSIE_CHECK_EQUAL( pair_production_cross_section.size(), 1263 );
  FRENSIE_CHECK_EQUAL( pair_production_cross_section.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( pair_production_cross_section.back(),
		       3.71803283438e+00 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the JINC block
FRENSIE_UNIT_TEST( XSSPhotoatomicDataExtractor, extractJINCBlock )
{
  Utility::ArrayView<const double> jinc_block =
    xss_data_extractor->extractJINCBlock();

  FRENSIE_CHECK_EQUAL( jinc_block.size(), 21 );
  FRENSIE_CHECK_EQUAL( jinc_block.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( jinc_block.back(), 7.85210000000e+01 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the JCOH block
FRENSIE_UNIT_TEST( XSSPhotoatomicDataExtractor, extractJCOHBlock )
{
  Utility::ArrayView<const double> jcoh_block =
    xss_data_extractor->extractJCOHBlock();

  FRENSIE_CHECK_EQUAL( jcoh_block.size(), 110 );
  FRENSIE_CHECK_EQUAL( jcoh_block.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( jcoh_block.back(), 3.87140000000e+00 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the JFLO block
FRENSIE_UNIT_TEST( XSSPhotoatomicDataExtractor, extractJFLOBlock )
{
  Utility::ArrayView<const double> jflo_block =
    xss_data_extractor->extractJFLOBlock();

  FRENSIE_CHECK_EQUAL( jflo_block.size(), 24 );
  FRENSIE_CHECK_EQUAL( jflo_block.front(), 1.47126666667e-02 );
  FRENSIE_CHECK_EQUAL( jflo_block.back(), 8.76202453125e-02 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the LHNM block
FRENSIE_UNIT_TEST( XSSPhotoatomicDataExtractor, extractLHNMBlock )
{
  Utility::ArrayView<const double> lhnm_block =
    xss_data_extractor->extractLHNMBlock();

  FRENSIE_CHECK_EQUAL( lhnm_block.size(), 1263 );
  FRENSIE_CHECK_EQUAL( lhnm_block.front(), 9.98732853634e-04 );
  FRENSIE_CHECK_EQUAL( lhnm_block.back(), 9.99986424397e+04 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the LNEPS block
FRENSIE_UNIT_TEST( XSSPhotoatomicDataExtractor, extractLNEPSBlock )
{
  Utility::ArrayView<const double> lneps_block =
    xss_data_extractor->extractLNEPSBlock();

  FRENSIE_CHECK_EQUAL( lneps_block.size(), 23 );
  FRENSIE_CHECK_EQUAL( lneps_block.front(), 2 );
  FRENSIE_CHECK_EQUAL( lneps_block.back(), 2 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the LBEPS block
FRENSIE_UNIT_TEST( XSSPhotoatomicDataExtractor, extractLBEPSBlock )
{
  Utility::ArrayView<const double> lbeps_block =
    xss_data_extractor->extractLBEPSBlock();

  FRENSIE_CHECK_EQUAL( lbeps_block.size(), 23 );
  FRENSIE_CHECK_EQUAL( lbeps_block.front(), 8.800500000000e-02 );
  FRENSIE_CHECK_EQUAL( lbeps_block.back(), 0.000000000000e+00 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the LPIPS block
FRENSIE_UNIT_TEST( XSSPhotoatomicDataExtractor, extractLPIPSBlock )
{
  Utility::ArrayView<const double> lpips_block =
    xss_data_extractor->extractLPIPSBlock();

  FRENSIE_CHECK_EQUAL( lpips_block.size(), 23 );
  FRENSIE_CHECK_EQUAL( lpips_block.front(), 2.439024390244e-02 );
  FRENSIE_CHECK_EQUAL( lpips_block.back(), 2.439024390244e-02 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the LSWD block
FRENSIE_UNIT_TEST( XSSPhotoatomicDataExtractor, extractLSWDBlock )
{
  Utility::ArrayView<const double> lswd_block =
    xss_data_extractor->extractLSWDBlock();

  FRENSIE_CHECK_EQUAL( lswd_block.size(), 23 );
  FRENSIE_CHECK_EQUAL( lswd_block.front(), 1 );
  FRENSIE_CHECK_EQUAL( lswd_block.back(), 2091 );
}

//---------------------------------------------------------------------------//
// Check that the XSSPhotoatomicDataExtractor can extract the SWD block
FRENSIE_UNIT_TEST( XSSPhotoatomicDataExtractor, extractSWDBlock )
{
  Utility::ArrayView<const double> swd_block =
    xss_data_extractor->extractSWDBlock();

  FRENSIE_CHECK_EQUAL( swd_block.size(), 2185 );
  FRENSIE_CHECK_EQUAL( swd_block.front(), 2 );
  FRENSIE_CHECK_EQUAL( swd_block.back(), 1.000000000000e+00 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name;
std::string test_ace_table_name;
unsigned test_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_table",
                                        test_ace_table_name, "",
                                        "Test ACE table name in ACE file" );
  
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file",
                                        test_ace_file_name, "",
                                        "Test ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file_start_line",
                                        test_ace_file_start_line, 1,
                                        "Test ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize ace file handler and data extractor
  Data::ACEFileHandler ace_file_handler( test_ace_file_name,
                                         test_ace_table_name,
                                         test_ace_file_start_line );

  xss_data_extractor.reset(
   new Data::XSSPhotoatomicDataExtractor(
				      ace_file_handler.getTableNXSArray(),
				      ace_file_handler.getTableJXSArray(),
				      ace_file_handler.getTableXSSArray() ) );

}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstXSSPhotoatomicDataExtractor.cpp
//---------------------------------------------------------------------------//

