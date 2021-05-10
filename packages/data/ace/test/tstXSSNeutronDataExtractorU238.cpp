//---------------------------------------------------------------------------//
//!
//! \file   tstXSSNeutronDataExtractorU238.cpp
//! \author Alex Robinson
//! \brief  XSS neutron data extractor class unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using Utility::Units::MeV;
using Utility::Units::barn;
using Utility::Units::barns;

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::shared_ptr<const Data::XSSNeutronDataExtractor> xss_data_extractor_u238;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can check if fission data is present
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, hasFissionData_u238 )
{
  FRENSIE_CHECK( xss_data_extractor_u238->hasFissionData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can check if delayed neutron data is present
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, hasDelayedNeutronData_u238 )
{
  FRENSIE_CHECK( xss_data_extractor_u238->hasDelayedNeutronData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can check if unresolved resonance
// data is present
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, hasUnresolvedResonanceData_u238 )
{
  FRENSIE_CHECK( xss_data_extractor_u238->hasUnresolvedResonanceData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the ESZ block from the
// XSS array
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractESZBlock_u238 )
{
  Utility::ArrayView<const double> esz_block =
    xss_data_extractor_u238->extractESZBlock();

  FRENSIE_CHECK_EQUAL( esz_block.size(), 788770 );
  FRENSIE_CHECK_EQUAL( esz_block.front(), 1e-11 );
  FRENSIE_CHECK_EQUAL( esz_block.back(), 4.99417e1 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the energy grid from the
// XSS array
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractEnergyGrid_u238 )
{
  auto energy_grid = xss_data_extractor_u238->extractEnergyGrid();

  FRENSIE_CHECK_EQUAL( energy_grid.size(), 157754 );
  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1e-11 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 30 );

  auto energy_grid_in_mev = xss_data_extractor_u238->extractEnergyGridInMeV();

  FRENSIE_CHECK_EQUAL( energy_grid_in_mev.size(), 157754 );
  FRENSIE_CHECK_EQUAL( energy_grid_in_mev.front(), 1e-11*MeV );
  FRENSIE_CHECK_EQUAL( energy_grid_in_mev.back(), 30*MeV );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the total cross section
// from the XSS array
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractTotalCrossSec_u238 )
{
  auto total_cross_sec = xss_data_extractor_u238->extractTotalCrossSection();

  FRENSIE_CHECK_EQUAL( total_cross_sec.size(), 157754 );
  FRENSIE_CHECK_EQUAL( total_cross_sec.front(), 1.69844353e2  );
  FRENSIE_CHECK_EQUAL( total_cross_sec.back(), 5.71955315 );

  auto total_cross_sec_in_barns =
    xss_data_extractor_u238->extractTotalCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( total_cross_sec_in_barns.size(), 157754 );
  FRENSIE_CHECK_EQUAL( total_cross_sec_in_barns.front(), 1.69844353e2*barns  );
  FRENSIE_CHECK_EQUAL( total_cross_sec_in_barns.back(), 5.71955315*barns );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the total absorption
// cross section from the XSS array
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractAbsorptionCrossSec_u238 )
{
  auto absorption_cross_sec =
    xss_data_extractor_u238->extractTotalAbsorptionCrossSection();

  FRENSIE_CHECK_EQUAL( absorption_cross_sec.size(), 157754 );
  FRENSIE_CHECK_EQUAL( absorption_cross_sec.front(), 1.344458e2 );
  FRENSIE_CHECK_EQUAL( absorption_cross_sec.back(), 1.0e-4 );

  auto absorption_cross_sec_in_barns =
    xss_data_extractor_u238->extractTotalAbsorptionCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( absorption_cross_sec_in_barns.size(), 157754 );
  FRENSIE_CHECK_EQUAL( absorption_cross_sec_in_barns.front(), 1.344458e2*barns );
  FRENSIE_CHECK_EQUAL( absorption_cross_sec_in_barns.back(), 1.0e-4*barns );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the elastic cross section
// from the XSS array
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractElasticCrossSection_u238 )
{
  auto elastic_cross_sec =
    xss_data_extractor_u238->extractElasticCrossSection();

  FRENSIE_CHECK_EQUAL( elastic_cross_sec.size(), 157754 );
  FRENSIE_CHECK_EQUAL( elastic_cross_sec.front(), 3.539771e1 );
  FRENSIE_CHECK_EQUAL( elastic_cross_sec.back(), 2.78998  );

  auto elastic_cross_sec_in_barns =
    xss_data_extractor_u238->extractElasticCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( elastic_cross_sec_in_barns.size(), 157754 );
  FRENSIE_CHECK_EQUAL( elastic_cross_sec_in_barns.front(), 3.539771e1*barns );
  FRENSIE_CHECK_EQUAL( elastic_cross_sec_in_barns.back(), 2.78998*barns  );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the average heating
// numbers from the XSS array
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractAverageHeatingNumbers_u238)
{
  auto ave_heating_nums =
    xss_data_extractor_u238->extractAverageHeatingNumbers();

  FRENSIE_CHECK_EQUAL( ave_heating_nums.size(), 157754 );
  FRENSIE_CHECK_EQUAL( ave_heating_nums.front(), 8.59985e-4 );
  FRENSIE_CHECK_EQUAL( ave_heating_nums.back(), 4.99417e1 );

  auto ave_heating_nums_in_mev =
    xss_data_extractor_u238->extractAverageHeatingNumbersInMeV();

  FRENSIE_CHECK_EQUAL( ave_heating_nums_in_mev.size(), 157754 );
  FRENSIE_CHECK_EQUAL( ave_heating_nums_in_mev.front(), 8.59985e-4*MeV );
  FRENSIE_CHECK_EQUAL( ave_heating_nums_in_mev.back(), 4.99417e1*MeV );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the NU block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractNUBlock_u238 )
{
  Utility::ArrayView<const double> nu_block =
    xss_data_extractor_u238->extractNUBlock();

  FRENSIE_CHECK_EQUAL( nu_block.size(), 47 );
  FRENSIE_CHECK_EQUAL( nu_block.front(), -23 );
  FRENSIE_CHECK_EQUAL( nu_block.back(), 6.414109 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the MTR block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractMTRBlock_u238 )
{
  Utility::ArrayView<const double> mtr_block =
    xss_data_extractor_u238->extractMTRBlock();

  FRENSIE_CHECK_EQUAL( mtr_block.size(), 47 );
  FRENSIE_CHECK_EQUAL( mtr_block.front(), 16 );
  FRENSIE_CHECK_EQUAL( mtr_block[1], 17 );
  FRENSIE_CHECK_EQUAL( mtr_block[2], 18 );
  FRENSIE_CHECK_EQUAL( mtr_block.back(), 444 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the MTRP block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractMTRPBlock_u238 )
{
  Utility::ArrayView<const double> mtrp_block =
    xss_data_extractor_u238->extractMTRPBlock();

  FRENSIE_CHECK_EQUAL( mtrp_block.size(), 6  );
  FRENSIE_CHECK_EQUAL( mtrp_block.front(), 18001 );
  FRENSIE_CHECK_EQUAL( mtrp_block.back(), 3004 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LQR block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractLQRBlock_u238 )
{
  Utility::ArrayView<const double> lqr_block =
    xss_data_extractor_u238->extractLQRBlock();

  FRENSIE_CHECK_EQUAL( lqr_block.size(), 47 );
  FRENSIE_CHECK_EQUAL( lqr_block.front(), -6.1528 );
  FRENSIE_CHECK_EQUAL( lqr_block.back(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the TYR block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractTYRBlock_u238 )
{
  Utility::ArrayView<const double> tyr_block =
    xss_data_extractor_u238->extractTYRBlock();

  FRENSIE_CHECK_EQUAL( tyr_block.size(), 47  );
  FRENSIE_CHECK_EQUAL( tyr_block.front(), -2  );
  FRENSIE_CHECK_EQUAL( tyr_block.back(), 0  );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LSIG block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractLSIGBlock_u238 )
{
  Utility::ArrayView<const double> lsig_block =
    xss_data_extractor_u238->extractLSIGBlock();

  FRENSIE_CHECK_EQUAL( lsig_block.size(), 47 );
  FRENSIE_CHECK_EQUAL( lsig_block.front(), 1 );
  FRENSIE_CHECK_EQUAL( lsig_block.back(), 324068 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LSIGP block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractLSIGPBlock_u238 )
{
  Utility::ArrayView<const double> lsigp_block =
    xss_data_extractor_u238->extractLSIGPBlock();

  FRENSIE_CHECK_EQUAL( lsigp_block.size(), 6 );
  FRENSIE_CHECK_EQUAL( lsigp_block.front(), 1 );
  FRENSIE_CHECK_EQUAL( lsigp_block.back(), 276 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the SIG block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractSIGBlock_u238 )
{
  Utility::ArrayView<const double> sig_block =
    xss_data_extractor_u238->extractSIGBlock();

  FRENSIE_CHECK_EQUAL( sig_block.size(), 191 );
  FRENSIE_CHECK_EQUAL( sig_block.front(), 157648 );
  FRENSIE_CHECK_EQUAL( sig_block.back(), 1.716853e-01); // Value in line 2878303 last column (191 entries after start)
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LAND block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractLANDBlock_u238 )
{
  Utility::ArrayView<const double> land_block =
    xss_data_extractor_u238->extractLANDBlock();

  FRENSIE_CHECK_EQUAL( land_block.size(), 46 );
  FRENSIE_CHECK_EQUAL( land_block.front(), 1 );
  FRENSIE_CHECK_EQUAL( land_block.back(), -1 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the AND block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractANDBlock_u238 )
{
  Utility::ArrayView<const double> and_block =
    xss_data_extractor_u238->extractANDBlock();

  FRENSIE_CHECK_EQUAL( and_block.size(), 93093 );
  FRENSIE_CHECK_EQUAL( and_block.front(), 38 );
  FRENSIE_CHECK_EQUAL( and_block.back(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LDLW block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractLDLWBlock_u238 )
{
  Utility::ArrayView<const double> ldlw_block =
    xss_data_extractor_u238->extractLDLWBlock();

  FRENSIE_CHECK_EQUAL( ldlw_block.size(), 45 );
  FRENSIE_CHECK_EQUAL( ldlw_block.front(), 1 );
  FRENSIE_CHECK_EQUAL( ldlw_block.back(), 70954 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LDLWP block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractLDLWPBlock_u238 )
{
  Utility::ArrayView<const double> ldlwp_block =
    xss_data_extractor_u238->extractLDLWPBlock();

  FRENSIE_CHECK_EQUAL( ldlwp_block.size(), 6 );
  FRENSIE_CHECK_EQUAL( ldlwp_block.front(), 1 );
  FRENSIE_CHECK_EQUAL( ldlwp_block.back(), 792 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the DLW block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractDLWBlock_u238 )
{
  Utility::ArrayView<const double> dlw_block =
    xss_data_extractor_u238->extractDLWBlock();

  FRENSIE_CHECK_EQUAL( dlw_block.size(), 100244 ); 
  FRENSIE_CHECK_EQUAL( dlw_block.front(), 0 );
  FRENSIE_CHECK_EQUAL( dlw_block.back(), 1.910696 ); // TODO Value in line 3047069 first column should be 18, but map thinks 1.91069
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the DLWP block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractDLWPBlock_u238 )
{
  Utility::ArrayView<const double> dlwp_block =
    xss_data_extractor_u238->extractDLWPBlock();

  FRENSIE_CHECK_EQUAL( dlwp_block.size(), 3170 );
  FRENSIE_CHECK_EQUAL( dlwp_block.front(), 0 );
  FRENSIE_CHECK_EQUAL( dlwp_block.back(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the GPD block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractGPDBlock_u238 )
{
  Utility::ArrayView<const double> gpd_block =
    xss_data_extractor_u238->extractGPDBlock();

  FRENSIE_CHECK_EQUAL( gpd_block.size(), 157754 );
  FRENSIE_CHECK_EQUAL( gpd_block.front(), 5.821567e2 );
  FRENSIE_CHECK_EQUAL( gpd_block.back(), 1.650796e1 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the SIGP block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractSIGPBlock_u238 )
{
  Utility::ArrayView<const double> sigp_block =
    xss_data_extractor_u238->extractSIGPBlock();

  FRENSIE_CHECK_EQUAL( sigp_block.size(), 539 );
  FRENSIE_CHECK_EQUAL( sigp_block.front(), 12 );
  FRENSIE_CHECK_EQUAL( sigp_block.back(), 3.952 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LANDP block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractLANDPBlock_u238 )
{
  Utility::ArrayView<const double> landp_block =
    xss_data_extractor_u238->extractLANDPBlock();

  FRENSIE_CHECK_EQUAL( landp_block.size(), 6 );
  FRENSIE_CHECK_EQUAL( landp_block.front(), 0 );
  FRENSIE_CHECK_EQUAL( landp_block.back(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the ANDP block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractANDPBlock_u238 )
{
  Utility::ArrayView<const double> andp_block =
    xss_data_extractor_u238->extractANDPBlock();

  FRENSIE_CHECK_EQUAL( andp_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the YP block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractYPBlock_u238 )
{
  Utility::ArrayView<const double> yp_block =
    xss_data_extractor_u238->extractYPBlock();

  FRENSIE_CHECK_EQUAL( yp_block.size(), 3 );
  FRENSIE_CHECK_EQUAL( yp_block.front(), 2 );
  FRENSIE_CHECK_EQUAL( yp_block.back(), 102 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the FIS block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractFISBlock_u238 )
{
  Utility::ArrayView<const double> fis_block =
    xss_data_extractor_u238->extractFISBlock();

  FRENSIE_CHECK_EQUAL( fis_block.size(), 157756 );
  FRENSIE_CHECK_EQUAL( fis_block.front(), 1 );
  FRENSIE_CHECK_EQUAL( fis_block.back(), 1.666468 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the UNR block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractUNRBlock_u238 )
{
  Utility::ArrayView<const double> unr_block =
    xss_data_extractor_u238->extractUNRBlock();

  FRENSIE_CHECK_EQUAL( unr_block.size(), 2184 );
  FRENSIE_CHECK_EQUAL( unr_block.front(), 18 );
  FRENSIE_CHECK_EQUAL( unr_block.back(), 1.02014888699 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the DNU block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractDNUBlock_u238 )
{
  Utility::ArrayView<const double> dnu_block =
    xss_data_extractor_u238->extractDNUBlock();

  FRENSIE_CHECK_EQUAL( dnu_block.size(), 11 );
  FRENSIE_CHECK_EQUAL( dnu_block.front(), 2 );
  FRENSIE_CHECK_EQUAL( dnu_block.back(), 2.60000000000e-02 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the BDD block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractBDDBlock_u238 )
{
  Utility::ArrayView<const double> bdd_block =
    xss_data_extractor_u238->extractBDDBlock();

  FRENSIE_CHECK_EQUAL( bdd_block.size(), 42 );
  FRENSIE_CHECK_EQUAL( bdd_block.front(), 1.24942300000e-10 );
  FRENSIE_CHECK_EQUAL( bdd_block.back(), 6.16886800000e-02 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the DNEDL block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractDNEDLBlock_u238 )
{
  Utility::ArrayView<const double> dnedl_block =
    xss_data_extractor_u238->extractDNEDLBlock();

  FRENSIE_CHECK_EQUAL( dnedl_block.size(), 6 );
  FRENSIE_CHECK_EQUAL( dnedl_block.front(), 1 );
  FRENSIE_CHECK_EQUAL( dnedl_block.back(), 7944 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the DNED block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractDNEDBlock_u238 )
{
  Utility::ArrayView<const double> dned_block =
    xss_data_extractor_u238->extractDNEDBlock();

  FRENSIE_CHECK_EQUAL( dned_block.size(), 9768 );
  FRENSIE_CHECK_EQUAL( dned_block.front(), 0 );
  FRENSIE_CHECK_EQUAL( dned_block.back(), 9.99999999000e-01 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_u238_ace_file_name;
std::string test_u238_ace_table_name;
unsigned test_u238_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_u238_ace_table",
                                        test_u238_ace_table_name, "",
                                        "Test u238 ACE table name in u238 ACE file" );
  
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_u238_ace_file",
                                        test_u238_ace_file_name, "",
                                        "Test u238 ACE file name" );
  
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_u238_ace_file_start_line",
                                        test_u238_ace_file_start_line, 1,
                                        "Test u238 ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  Data::ACEFileHandler ace_file_handler_u238( test_u238_ace_file_name,
                                              test_u238_ace_table_name,
                                              test_u238_ace_file_start_line );

  xss_data_extractor_u238.reset(
   new Data::XSSNeutronDataExtractor( ace_file_handler_u238.getTableNXSArray(),
				      ace_file_handler_u238.getTableJXSArray(),
				      ace_file_handler_u238.getTableXSSArray() ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstXSSNeutronDataExtractorU238.cpp
//---------------------------------------------------------------------------//
