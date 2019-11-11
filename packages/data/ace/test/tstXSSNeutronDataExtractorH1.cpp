//---------------------------------------------------------------------------//
//!
//! \file   tstXSSNeutronDataExtractorH1.cpp
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
std::shared_ptr<const Data::XSSNeutronDataExtractor> xss_data_extractor_h1;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can check if fission data is present
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, hasFissionData_h1 )
{
  FRENSIE_CHECK( !xss_data_extractor_h1->hasFissionData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can check if delayed neutron data is present
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, hasDelayedNeutronData_h1 )
{
  FRENSIE_CHECK( !xss_data_extractor_h1->hasDelayedNeutronData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can check if unresolved resonance
// data is present
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, hasUnresolvedResonanceData_h1 )
{
  FRENSIE_CHECK( !xss_data_extractor_h1->hasUnresolvedResonanceData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the ESZ block from the
// XSS array
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractESZBlock_h1 )
{
  Utility::ArrayView<const double> esz_block =
    xss_data_extractor_h1->extractESZBlock();

  FRENSIE_CHECK_EQUAL( esz_block.size(), 590*5 );
  FRENSIE_CHECK_EQUAL( esz_block.front(), 1e-11 );
  FRENSIE_CHECK_EQUAL( esz_block.back(), 1.016085e1 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the energy grid from the
// XSS array
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractEnergyGrid_h1 )
{
  auto energy_grid = xss_data_extractor_h1->extractEnergyGrid();

  FRENSIE_CHECK_EQUAL( energy_grid.size(), 590 );
  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1e-11 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 2e1 );

  auto energy_grid_in_mev = xss_data_extractor_h1->extractEnergyGridInMeV();

  FRENSIE_CHECK_EQUAL( energy_grid_in_mev.size(), 590 );
  FRENSIE_CHECK_EQUAL( energy_grid_in_mev.front(), 1e-11*MeV );
  FRENSIE_CHECK_EQUAL( energy_grid_in_mev.back(), 2e1*MeV );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the total cross section
// from the XSS array
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractTotalCrossSec_h1 )
{
  auto total_cross_sec = xss_data_extractor_h1->extractTotalCrossSection();

  FRENSIE_CHECK_EQUAL( total_cross_sec.size(), 590 );
  FRENSIE_CHECK_EQUAL( total_cross_sec.front(), 1.17724711e3 );
  FRENSIE_CHECK_EQUAL( total_cross_sec.back(), 4.82773424e-1 );

  auto total_cross_sec_in_barns =
    xss_data_extractor_h1->extractTotalCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( total_cross_sec_in_barns.size(), 590 );
  FRENSIE_CHECK_EQUAL( total_cross_sec_in_barns.front(), 1.17724711e3*barns );
  FRENSIE_CHECK_EQUAL( total_cross_sec_in_barns.back(), 4.82773424e-1*barns );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the total absorption
// cross section from the XSS array
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractAbsorptionCrossSec_h1 )
{
  auto absorption_cross_sec =
    xss_data_extractor_h1->extractTotalAbsorptionCrossSection();

  FRENSIE_CHECK_EQUAL( absorption_cross_sec.size(), 590 );
  FRENSIE_CHECK_EQUAL( absorption_cross_sec.front(), 1.670111e1 );
  FRENSIE_CHECK_EQUAL( absorption_cross_sec.back(), 2.722354e-5 );

  auto absorption_cross_sec_in_barns =
    xss_data_extractor_h1->extractTotalAbsorptionCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( absorption_cross_sec_in_barns.size(), 590 );
  FRENSIE_CHECK_EQUAL( absorption_cross_sec_in_barns.front(), 1.670111e1*barns );
  FRENSIE_CHECK_EQUAL( absorption_cross_sec_in_barns.back(), 2.722354e-5*barns );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the elastic cross section
// from the XSS array
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractElasticCrossSection_h1 )
{
  auto elastic_cross_sec = xss_data_extractor_h1->extractElasticCrossSection();

  FRENSIE_CHECK_EQUAL( elastic_cross_sec.size(), 590 );
  FRENSIE_CHECK_EQUAL( elastic_cross_sec.front(), 1.160546e3 );
  FRENSIE_CHECK_EQUAL( elastic_cross_sec.back(), 4.827462e-1 );

  auto elastic_cross_sec_in_barns =
    xss_data_extractor_h1->extractElasticCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( elastic_cross_sec_in_barns.size(), 590 );
  FRENSIE_CHECK_EQUAL( elastic_cross_sec_in_barns.front(), 1.160546e3*barns );
  FRENSIE_CHECK_EQUAL( elastic_cross_sec_in_barns.back(), 4.827462e-1*barns );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the average heating
// numbers from the XSS array
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractAverageHeatingNumbers_h1)
{
  auto ave_heating_nums =
    xss_data_extractor_h1->extractAverageHeatingNumbers();

  FRENSIE_CHECK_EQUAL( ave_heating_nums.size(), 590 );
  FRENSIE_CHECK_EQUAL( ave_heating_nums.front(), 5.000028e-12 );
  FRENSIE_CHECK_EQUAL( ave_heating_nums.back(), 1.016085e1 );

  auto ave_heating_nums_in_mev =
    xss_data_extractor_h1->extractAverageHeatingNumbersInMeV();

  FRENSIE_CHECK_EQUAL( ave_heating_nums_in_mev.size(), 590 );
  FRENSIE_CHECK_EQUAL( ave_heating_nums_in_mev.front(), 5.000028e-12*MeV );
  FRENSIE_CHECK_EQUAL( ave_heating_nums_in_mev.back(), 1.016085e1*MeV );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the NU block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractNUBlock_h1 )
{
  Utility::ArrayView<const double> nu_block =
    xss_data_extractor_h1->extractNUBlock();

  FRENSIE_CHECK_EQUAL( nu_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the MTR block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractMTRBlock_h1 )
{
  Utility::ArrayView<const double> mtr_block =
    xss_data_extractor_h1->extractMTRBlock();

  FRENSIE_CHECK_EQUAL( mtr_block.size(), 3 );
  FRENSIE_CHECK_EQUAL( mtr_block[0], 102 );
  FRENSIE_CHECK_EQUAL( mtr_block[1], 204 );
  FRENSIE_CHECK_EQUAL( mtr_block[2], 444 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the MTRP block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractMTRPBlock_h1 )
{
  Utility::ArrayView<const double> mtrp_block =
    xss_data_extractor_h1->extractMTRPBlock();

  FRENSIE_CHECK_EQUAL( mtrp_block.size(), 1 );
  FRENSIE_CHECK_EQUAL( mtrp_block.front(), 102001 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LQR block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractLQRBlock_h1 )
{
  Utility::ArrayView<const double> lqr_block =
    xss_data_extractor_h1->extractLQRBlock();

  FRENSIE_CHECK_EQUAL( lqr_block.size(), 3 );
  FRENSIE_CHECK_EQUAL( lqr_block[0], 2.224631e0 );
  FRENSIE_CHECK_EQUAL( lqr_block[1], 0.0 );
  FRENSIE_CHECK_EQUAL( lqr_block[2], 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the TYR block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractTYRBlock_h1 )
{
  Utility::ArrayView<const double> tyr_block =
    xss_data_extractor_h1->extractTYRBlock();

  FRENSIE_CHECK_EQUAL( tyr_block.size(), 3 );
  FRENSIE_CHECK_EQUAL( tyr_block[0], 0.0 );
  FRENSIE_CHECK_EQUAL( tyr_block[1], 0.0 );
  FRENSIE_CHECK_EQUAL( tyr_block[2], 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LSIG block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractLSIGBlock_h1 )
{
  Utility::ArrayView<const double> lsig_block =
    xss_data_extractor_h1->extractLSIGBlock();

  FRENSIE_CHECK_EQUAL( lsig_block.size(), 3 );
  FRENSIE_CHECK_EQUAL( lsig_block[0], 1 );
  FRENSIE_CHECK_EQUAL( lsig_block[1], 593 );
  FRENSIE_CHECK_EQUAL( lsig_block[2], 1185 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LSIGP block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractLSIGPBlock_h1 )
{
  Utility::ArrayView<const double> lsigp_block =
    xss_data_extractor_h1->extractLSIGPBlock();

  FRENSIE_CHECK_EQUAL( lsigp_block.size(), 1 );
  FRENSIE_CHECK_EQUAL( lsigp_block.front(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the SIG block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractSIGBlock_h1 )
{
  Utility::ArrayView<const double> sig_block =
    xss_data_extractor_h1->extractSIGBlock();

  FRENSIE_CHECK_EQUAL( sig_block.size(), 1389 );
  FRENSIE_CHECK_EQUAL( sig_block.front(), 1 );
  FRENSIE_CHECK_EQUAL( sig_block.back(), 3.067696e-4 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LAND block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractLANDBlock_h1 )
{
  Utility::ArrayView<const double> land_block =
    xss_data_extractor_h1->extractLANDBlock();

  FRENSIE_CHECK_EQUAL( land_block.size(), 1 );
  FRENSIE_CHECK_EQUAL( land_block.front(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the AND block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractANDBlock_h1 )
{
  Utility::ArrayView<const double> and_block =
    xss_data_extractor_h1->extractANDBlock();

  FRENSIE_CHECK_EQUAL( and_block.size(), 1291 );
  FRENSIE_CHECK_EQUAL( and_block.front(), 96 );
  FRENSIE_CHECK_EQUAL( and_block.back(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LDLW block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractLDLWBlock_h1 )
{
  Utility::ArrayView<const double> ldlw_block =
    xss_data_extractor_h1->extractLDLWBlock();

  FRENSIE_CHECK_EQUAL( ldlw_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LDLWP block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractLDLWPBlock_h1 )
{
  Utility::ArrayView<const double> ldlwp_block =
    xss_data_extractor_h1->extractLDLWPBlock();

  FRENSIE_CHECK_EQUAL( ldlwp_block.size(), 1 );
  FRENSIE_CHECK_EQUAL( ldlwp_block.front(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the DLW block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractDLWBlock_h1 )
{
  Utility::ArrayView<const double> dlw_block =
    xss_data_extractor_h1->extractDLWBlock();

  FRENSIE_CHECK_EQUAL( dlw_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the DLWP block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractDLWPBlock_h1 )
{
  Utility::ArrayView<const double> dlwp_block =
    xss_data_extractor_h1->extractDLWPBlock();

  FRENSIE_CHECK_EQUAL( dlwp_block.size(), 683 );
  FRENSIE_CHECK_EQUAL( dlwp_block.front(), 0 );
  FRENSIE_CHECK_EQUAL( dlwp_block.back(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the GPD block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractGPDBlock_h1 )
{
  Utility::ArrayView<const double> gpd_block =
    xss_data_extractor_h1->extractGPDBlock();

  FRENSIE_CHECK_EQUAL( gpd_block.size(), 590 );
  FRENSIE_CHECK_EQUAL( gpd_block.front(), 1.6701110e1 );
  FRENSIE_CHECK_EQUAL( gpd_block.back(), 2.7223540e-5 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the SIGP block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractSIGPBlock_h1 )
{
  Utility::ArrayView<const double> sigp_block =
    xss_data_extractor_h1->extractSIGPBlock();

  FRENSIE_CHECK_EQUAL( sigp_block.size(), 8 );
  FRENSIE_CHECK_EQUAL( sigp_block.front(), 16 );
  FRENSIE_CHECK_EQUAL( sigp_block.back(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LANDP block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractLANDPBlock_h1 )
{
  Utility::ArrayView<const double> landp_block =
    xss_data_extractor_h1->extractLANDPBlock();

  FRENSIE_CHECK_EQUAL( landp_block.size(), 1 );
  FRENSIE_CHECK_EQUAL( landp_block.front(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the ANDP block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractANDPBlock_h1 )
{
  Utility::ArrayView<const double> andp_block =
    xss_data_extractor_h1->extractANDPBlock();

  FRENSIE_CHECK_EQUAL( andp_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the YP block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractYPBlock_h1 )
{
  Utility::ArrayView<const double> yp_block =
    xss_data_extractor_h1->extractYPBlock();

  FRENSIE_CHECK_EQUAL( yp_block.size(), 2 );
  FRENSIE_CHECK_EQUAL( yp_block.front(), 1 );
  FRENSIE_CHECK_EQUAL( yp_block.back(), 102 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the FIS block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractFISBlock_h1 )
{
  Utility::ArrayView<const double> fis_block =
    xss_data_extractor_h1->extractFISBlock();

  FRENSIE_CHECK_EQUAL( fis_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the UNR block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractUNRBlock_h1 )
{
  Utility::ArrayView<const double> unr_block =
    xss_data_extractor_h1->extractUNRBlock();

  FRENSIE_CHECK_EQUAL( unr_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the DNU block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractDNUBlock_h1 )
{
  Utility::ArrayView<const double> dnu_block =
    xss_data_extractor_h1->extractDNUBlock();

  FRENSIE_CHECK_EQUAL( dnu_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the BDD block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractBDDBlock_h1 )
{
  Utility::ArrayView<const double> bdd_block =
    xss_data_extractor_h1->extractBDDBlock();

  FRENSIE_CHECK_EQUAL( bdd_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the DNEDL block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractDNEDLBlock_h1 )
{
  Utility::ArrayView<const double> dnedl_block =
    xss_data_extractor_h1->extractDNEDLBlock();

  FRENSIE_CHECK_EQUAL( dnedl_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the DNED block
FRENSIE_UNIT_TEST( XSSNeutronDataExtractor, extractDNEDBlock_h1 )
{
  Utility::ArrayView<const double> dned_block =
    xss_data_extractor_h1->extractDNEDBlock();

  FRENSIE_CHECK_EQUAL( dned_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_h1_ace_table_name;
std::string test_h1_ace_file_name;
unsigned test_h1_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_h1_ace_table",
                                        test_h1_ace_table_name, "",
                                        "Test h1 ACE table name in h1 ACE file" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_h1_ace_file",
                                        test_h1_ace_file_name, "",
                                        "Test h1 ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_h1_ace_file_start_line",
                                        test_h1_ace_file_start_line, 1,
                                        "Test h1 ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  Data::ACEFileHandler ace_file_handler_h1( test_h1_ace_file_name,
                                            test_h1_ace_table_name,
                                            test_h1_ace_file_start_line );

  xss_data_extractor_h1.reset(
   new Data::XSSNeutronDataExtractor( ace_file_handler_h1.getTableNXSArray(),
				      ace_file_handler_h1.getTableJXSArray(),
				      ace_file_handler_h1.getTableXSSArray() ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstXSSNeutronDataExtractorH1.cpp
//---------------------------------------------------------------------------//
