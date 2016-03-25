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
std::string test_u238_ace_file_name;
std::string test_u238_ace_table_name;

Teuchos::RCP<Data::ACEFileHandler> ace_file_handler_h1;
Teuchos::RCP<Data::ACEFileHandler> ace_file_handler_u238;

Teuchos::RCP<Data::XSSNeutronDataExtractor> xss_data_extractor_h1;
Teuchos::RCP<Data::XSSNeutronDataExtractor> xss_data_extractor_u238;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can check if fission data is present
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, hasFissionData_h1 )
{
  TEST_ASSERT( !xss_data_extractor_h1->hasFissionData() );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, hasFissionData_u238 )
{
  TEST_ASSERT( xss_data_extractor_u238->hasFissionData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can check if delayed neutron data is present
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, hasDelayedNeutronData_h1 )
{
  TEST_ASSERT( !xss_data_extractor_h1->hasDelayedNeutronData() );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, hasDelayedNeutronData_u238 )
{
  TEST_ASSERT( xss_data_extractor_u238->hasDelayedNeutronData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can check if unresolved resonance
// data is present
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, hasUnresolvedResonanceData_h1 )
{
  TEST_ASSERT( !xss_data_extractor_h1->hasUnresolvedResonanceData() );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, hasUnresolvedResonanceData_u238 )
{
  TEST_ASSERT( xss_data_extractor_u238->hasUnresolvedResonanceData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the ESZ block from the 
// XSS array
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractESZBlock_h1 )
{
  Teuchos::ArrayView<const double> esz_block = 
    xss_data_extractor_h1->extractESZBlock();

  TEST_EQUALITY_CONST( esz_block.size(), 590*5 );
  TEST_EQUALITY_CONST( esz_block.front(), 1e-11 );
  TEST_EQUALITY_CONST( esz_block.back(), 1.016085e1 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractESZBlock_u238 )
{
  Teuchos::ArrayView<const double> esz_block = 
    xss_data_extractor_u238->extractESZBlock();

  TEST_EQUALITY_CONST( esz_block.size(), 788770 );
  TEST_EQUALITY_CONST( esz_block.front(), 1e-11 );
  TEST_EQUALITY_CONST( esz_block.back(), 4.99417e1 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the energy grid from the
// XSS array
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractEnergyGrid_h1 )
{
  Teuchos::ArrayView<const double> energy_grid = 
    xss_data_extractor_h1->extractEnergyGrid();

  TEST_EQUALITY_CONST( energy_grid.size(), 590 );
  TEST_EQUALITY_CONST( energy_grid.front(), 1e-11 );
  TEST_EQUALITY_CONST( energy_grid.back(), 2e1 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractEnergyGrid_u238 )
{
  Teuchos::ArrayView<const double> energy_grid = 
    xss_data_extractor_u238->extractEnergyGrid();

  TEST_EQUALITY_CONST( energy_grid.size(), 157754 );
  TEST_EQUALITY_CONST( energy_grid.front(), 1e-11  );
  TEST_EQUALITY_CONST( energy_grid.back(), 30 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the total cross section
// from the XSS array
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractTotalCrossSec_h1 )
{
  Teuchos::ArrayView<const double> total_cross_sec = 
    xss_data_extractor_h1->extractTotalCrossSection();

  TEST_EQUALITY_CONST( total_cross_sec.size(), 590 );
  TEST_EQUALITY_CONST( total_cross_sec.front(), 1.17724711e3 );
  TEST_EQUALITY_CONST( total_cross_sec.back(), 4.82773424e-1 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractTotalCrossSec_u238 )
{
  Teuchos::ArrayView<const double> total_cross_sec = 
    xss_data_extractor_u238->extractTotalCrossSection();

  TEST_EQUALITY_CONST( total_cross_sec.size(), 157754 );
  TEST_EQUALITY_CONST( total_cross_sec.front(), 1.69844353e2  );
  TEST_EQUALITY_CONST( total_cross_sec.back(), 5.71955315 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the total absorption
// cross section from the XSS array
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractAbsorptionCrossSec_h1 )
{
  Teuchos::ArrayView<const double> absorption_cross_sec =
    xss_data_extractor_h1->extractTotalAbsorptionCrossSection();

  TEST_EQUALITY_CONST( absorption_cross_sec.size(), 590 );
  TEST_EQUALITY_CONST( absorption_cross_sec.front(), 1.670111e1 );
  TEST_EQUALITY_CONST( absorption_cross_sec.back(), 2.722354e-5 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractAbsorptionCrossSec_u238 )
{
  Teuchos::ArrayView<const double> absorption_cross_sec =
    xss_data_extractor_u238->extractTotalAbsorptionCrossSection();

  TEST_EQUALITY_CONST( absorption_cross_sec.size(), 157754 );
  TEST_EQUALITY_CONST( absorption_cross_sec.front(), 1.344458e2 );
  TEST_EQUALITY_CONST( absorption_cross_sec.back(), 1.0e-4 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the elastic cross section
// from the XSS array
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractElasticCrossSection_h1 )
{
  Teuchos::ArrayView<const double> elastic_cross_sec = 
    xss_data_extractor_h1->extractElasticCrossSection();

  TEST_EQUALITY_CONST( elastic_cross_sec.size(), 590 );
  TEST_EQUALITY_CONST( elastic_cross_sec.front(), 1.160546e3 );
  TEST_EQUALITY_CONST( elastic_cross_sec.back(), 4.827462e-1 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractElasticCrossSection_u238 )
{
  Teuchos::ArrayView<const double> elastic_cross_sec = 
    xss_data_extractor_u238->extractElasticCrossSection();

  TEST_EQUALITY_CONST( elastic_cross_sec.size(), 157754 );
  TEST_EQUALITY_CONST( elastic_cross_sec.front(), 3.539771e1  );
  TEST_EQUALITY_CONST( elastic_cross_sec.back(), 2.78998  );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the average heating
// numbers from the XSS array
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractAverageHeatingNumbers_h1)
{
  Teuchos::ArrayView<const double> ave_heating_nums =
    xss_data_extractor_h1->extractAverageHeatingNumbers();

  TEST_EQUALITY_CONST( ave_heating_nums.size(), 590 );
  TEST_EQUALITY_CONST( ave_heating_nums.front(), 5.000028e-12 );
  TEST_EQUALITY_CONST( ave_heating_nums.back(), 1.016085e1 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractAverageHeatingNumbers_u238)
{
  Teuchos::ArrayView<const double> ave_heating_nums =
    xss_data_extractor_u238->extractAverageHeatingNumbers();

  TEST_EQUALITY_CONST( ave_heating_nums.size(), 157754 );
  TEST_EQUALITY_CONST( ave_heating_nums.front(), 8.59985e-4 );
  TEST_EQUALITY_CONST( ave_heating_nums.back(), 4.99417e1 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the NU block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractNUBlock_h1 )
{
  Teuchos::ArrayView<const double> nu_block = 
    xss_data_extractor_h1->extractNUBlock();

  TEST_EQUALITY_CONST( nu_block.size(), 0 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractNUBlock_u238 )
{
  Teuchos::ArrayView<const double> nu_block = 
    xss_data_extractor_u238->extractNUBlock();

  TEST_EQUALITY_CONST( nu_block.size(), 47 );
  TEST_EQUALITY_CONST( nu_block.front(), -23 );
  TEST_EQUALITY_CONST( nu_block.back(), 6.414109 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the MTR block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractMTRBlock_h1 )
{
  Teuchos::ArrayView<const double> mtr_block = 
    xss_data_extractor_h1->extractMTRBlock();

  TEST_EQUALITY_CONST( mtr_block.size(), 3 );
  TEST_EQUALITY_CONST( mtr_block[0], 102 );
  TEST_EQUALITY_CONST( mtr_block[1], 204 );
  TEST_EQUALITY_CONST( mtr_block[2], 444 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractMTRBlock_u238 )
{
  Teuchos::ArrayView<const double> mtr_block = 
    xss_data_extractor_u238->extractMTRBlock();

  TEST_EQUALITY_CONST( mtr_block.size(), 47 );
  TEST_EQUALITY_CONST( mtr_block.front(), 16 );
  TEST_EQUALITY_CONST( mtr_block[1], 17 );
  TEST_EQUALITY_CONST( mtr_block[2], 18 );
  TEST_EQUALITY_CONST( mtr_block.back(), 444 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the MTRP block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractMTRPBlock_h1 )
{
  Teuchos::ArrayView<const double> mtrp_block = 
    xss_data_extractor_h1->extractMTRPBlock();

  TEST_EQUALITY_CONST( mtrp_block.size(), 1 );
  TEST_EQUALITY_CONST( mtrp_block.front(), 102001 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractMTRPBlock_u238 )
{
  Teuchos::ArrayView<const double> mtrp_block = 
    xss_data_extractor_u238->extractMTRPBlock();

  TEST_EQUALITY_CONST( mtrp_block.size(), 6  );
  TEST_EQUALITY_CONST( mtrp_block.front(), 18001 );
  TEST_EQUALITY_CONST( mtrp_block.back(), 3004 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LQR block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractLQRBlock_h1 )
{
  Teuchos::ArrayView<const double> lqr_block = 
    xss_data_extractor_h1->extractLQRBlock();

  TEST_EQUALITY_CONST( lqr_block.size(), 3 );
  TEST_EQUALITY_CONST( lqr_block[0], 2.224631e0 );
  TEST_EQUALITY_CONST( lqr_block[1], 0.0 );
  TEST_EQUALITY_CONST( lqr_block[2], 0.0 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractLQRBlock_u238 )
{
  Teuchos::ArrayView<const double> lqr_block = 
    xss_data_extractor_u238->extractLQRBlock();

  TEST_EQUALITY_CONST( lqr_block.size(), 47 );
  TEST_EQUALITY_CONST( lqr_block.front(), -6.1528 );
  TEST_EQUALITY_CONST( lqr_block.back(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the TYR block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractTYRBlock_h1 )
{
  Teuchos::ArrayView<const double> tyr_block = 
    xss_data_extractor_h1->extractTYRBlock();

  TEST_EQUALITY_CONST( tyr_block.size(), 3 );
  TEST_EQUALITY_CONST( tyr_block[0], 0.0 );
  TEST_EQUALITY_CONST( tyr_block[1], 0.0 );
  TEST_EQUALITY_CONST( tyr_block[2], 0.0 );  
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractTYRBlock_u238 )
{
  Teuchos::ArrayView<const double> tyr_block = 
    xss_data_extractor_u238->extractTYRBlock();

  TEST_EQUALITY_CONST( tyr_block.size(), 47  );
  TEST_EQUALITY_CONST( tyr_block.front(), -2  );
  TEST_EQUALITY_CONST( tyr_block.back(), 0  );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LSIG block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractLSIGBlock_h1 )
{
  Teuchos::ArrayView<const double> lsig_block = 
    xss_data_extractor_h1->extractLSIGBlock();

  TEST_EQUALITY_CONST( lsig_block.size(), 3 );
  TEST_EQUALITY_CONST( lsig_block[0], 1 );
  TEST_EQUALITY_CONST( lsig_block[1], 593 );
  TEST_EQUALITY_CONST( lsig_block[2], 1185 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractLSIGBlock_u238 )
{
  Teuchos::ArrayView<const double> lsig_block = 
    xss_data_extractor_u238->extractLSIGBlock();

  TEST_EQUALITY_CONST( lsig_block.size(), 47 );
  TEST_EQUALITY_CONST( lsig_block.front(), 1 );
  TEST_EQUALITY_CONST( lsig_block.back(), 324068 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LSIGP block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractLSIGPBlock_h1 )
{
  Teuchos::ArrayView<const double> lsigp_block = 
    xss_data_extractor_h1->extractLSIGPBlock();

  TEST_EQUALITY_CONST( lsigp_block.size(), 1 );
  TEST_EQUALITY_CONST( lsigp_block.front(), 1 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractLSIGPBlock_u238 )
{
  Teuchos::ArrayView<const double> lsigp_block = 
    xss_data_extractor_u238->extractLSIGPBlock();

  TEST_EQUALITY_CONST( lsigp_block.size(), 6 );
  TEST_EQUALITY_CONST( lsigp_block.front(), 1 );
  TEST_EQUALITY_CONST( lsigp_block.back(), 276 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the SIG block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractSIGBlock_h1 )
{
  Teuchos::ArrayView<const double> sig_block =
    xss_data_extractor_h1->extractSIGBlock();

  TEST_EQUALITY_CONST( sig_block.size(), 1389 );
  TEST_EQUALITY_CONST( sig_block.front(), 1 );
  TEST_EQUALITY_CONST( sig_block.back(), 3.067696e-4 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractSIGBlock_u238 )
{
  Teuchos::ArrayView<const double> sig_block =
    xss_data_extractor_u238->extractSIGBlock();

  TEST_EQUALITY_CONST( sig_block.size(), 481823 );
  TEST_EQUALITY_CONST( sig_block.front(), 157648 );
  TEST_EQUALITY_CONST( sig_block.back(), 3.216104e-1 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LAND block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractLANDBlock_h1 )
{
  Teuchos::ArrayView<const double> land_block =
    xss_data_extractor_h1->extractLANDBlock();

  TEST_EQUALITY_CONST( land_block.size(), 1 );
  TEST_EQUALITY_CONST( land_block.front(), 1 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractLANDBlock_u238 )
{
  Teuchos::ArrayView<const double> land_block =
    xss_data_extractor_u238->extractLANDBlock();

  TEST_EQUALITY_CONST( land_block.size(), 46 );
  TEST_EQUALITY_CONST( land_block.front(), 1 );
  TEST_EQUALITY_CONST( land_block.back(), -1 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the AND block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractANDBlock_h1 )
{
  Teuchos::ArrayView<const double> and_block = 
    xss_data_extractor_h1->extractANDBlock();

  TEST_EQUALITY_CONST( and_block.size(), 1291 );
  TEST_EQUALITY_CONST( and_block.front(), 96 );
  TEST_EQUALITY_CONST( and_block.back(), 1.0 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractANDBlock_u238 )
{
  Teuchos::ArrayView<const double> and_block = 
    xss_data_extractor_u238->extractANDBlock();

  TEST_EQUALITY_CONST( and_block.size(), 93093 );
  TEST_EQUALITY_CONST( and_block.front(), 38 );
  TEST_EQUALITY_CONST( and_block.back(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LDLW block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractLDLWBlock_h1 )
{
  Teuchos::ArrayView<const double> ldlw_block = 
    xss_data_extractor_h1->extractLDLWBlock();

  TEST_EQUALITY_CONST( ldlw_block.size(), 0 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractLDLWBlock_u238 )
{
  Teuchos::ArrayView<const double> ldlw_block = 
    xss_data_extractor_u238->extractLDLWBlock();

  TEST_EQUALITY_CONST( ldlw_block.size(), 45 );
  TEST_EQUALITY_CONST( ldlw_block.front(), 1 );
  TEST_EQUALITY_CONST( ldlw_block.back(), 70954 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LDLWP block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractLDLWPBlock_h1 )
{
  Teuchos::ArrayView<const double> ldlwp_block = 
    xss_data_extractor_h1->extractLDLWPBlock();

  TEST_EQUALITY_CONST( ldlwp_block.size(), 1 );
  TEST_EQUALITY_CONST( ldlwp_block.front(), 1 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractLDLWPBlock_u238 )
{
  Teuchos::ArrayView<const double> ldlwp_block = 
    xss_data_extractor_u238->extractLDLWPBlock();

  TEST_EQUALITY_CONST( ldlwp_block.size(), 6 );
  TEST_EQUALITY_CONST( ldlwp_block.front(), 1 );
  TEST_EQUALITY_CONST( ldlwp_block.back(), 792 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the DLW block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractDLWBlock_h1 )
{
  Teuchos::ArrayView<const double> dlw_block = 
    xss_data_extractor_h1->extractDLWBlock();

  TEST_EQUALITY_CONST( dlw_block.size(), 0 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractDLWBlock_u238 )
{
  Teuchos::ArrayView<const double> dlw_block = 
    xss_data_extractor_u238->extractDLWBlock();

  TEST_EQUALITY_CONST( dlw_block.size(), 112255 );
  TEST_EQUALITY_CONST( dlw_block.front(), 0 );
  TEST_EQUALITY_CONST( dlw_block.back(), 9.99999999e-1 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the DLWP block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractDLWPBlock_h1 )
{
  Teuchos::ArrayView<const double> dlwp_block = 
    xss_data_extractor_h1->extractDLWPBlock();

  TEST_EQUALITY_CONST( dlwp_block.size(), 683 );
  TEST_EQUALITY_CONST( dlwp_block.front(), 0 );
  TEST_EQUALITY_CONST( dlwp_block.back(), 1 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractDLWPBlock_u238 )
{
  Teuchos::ArrayView<const double> dlwp_block = 
    xss_data_extractor_u238->extractDLWPBlock();

  TEST_EQUALITY_CONST( dlwp_block.size(), 3170 );
  TEST_EQUALITY_CONST( dlwp_block.front(), 0 );
  TEST_EQUALITY_CONST( dlwp_block.back(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the GPD block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractGPDBlock_h1 )
{
  Teuchos::ArrayView<const double> gpd_block = 
    xss_data_extractor_h1->extractGPDBlock();

  TEST_EQUALITY_CONST( gpd_block.size(), 590 );
  TEST_EQUALITY_CONST( gpd_block.front(), 1.6701110e1 );
  TEST_EQUALITY_CONST( gpd_block.back(), 2.7223540e-5 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractGPDBlock_u238 )
{
  Teuchos::ArrayView<const double> gpd_block = 
    xss_data_extractor_u238->extractGPDBlock();

  TEST_EQUALITY_CONST( gpd_block.size(), 157754 );
  TEST_EQUALITY_CONST( gpd_block.front(), 5.821567e2 );
  TEST_EQUALITY_CONST( gpd_block.back(), 1.650796e1 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the SIGP block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractSIGPBlock_h1 )
{
  Teuchos::ArrayView<const double> sigp_block = 
    xss_data_extractor_h1->extractSIGPBlock();

  TEST_EQUALITY_CONST( sigp_block.size(), 8 );
  TEST_EQUALITY_CONST( sigp_block.front(), 16 );
  TEST_EQUALITY_CONST( sigp_block.back(), 1.0 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractSIGPBlock_u238 )
{
  Teuchos::ArrayView<const double> sigp_block = 
    xss_data_extractor_u238->extractSIGPBlock();

  TEST_EQUALITY_CONST( sigp_block.size(), 539 );
  TEST_EQUALITY_CONST( sigp_block.front(), 12 );
  TEST_EQUALITY_CONST( sigp_block.back(), 3.952 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the LANDP block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractLANDPBlock_h1 )
{
  Teuchos::ArrayView<const double> landp_block = 
    xss_data_extractor_h1->extractLANDPBlock();

  TEST_EQUALITY_CONST( landp_block.size(), 1 );
  TEST_EQUALITY_CONST( landp_block.front(), 0 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractLANDPBlock_u238 )
{
  Teuchos::ArrayView<const double> landp_block = 
    xss_data_extractor_u238->extractLANDPBlock();

  TEST_EQUALITY_CONST( landp_block.size(), 6 );
  TEST_EQUALITY_CONST( landp_block.front(), 0 );
  TEST_EQUALITY_CONST( landp_block.back(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the ANDP block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractANDPBlock_h1 )
{
  Teuchos::ArrayView<const double> andp_block = 
    xss_data_extractor_h1->extractANDPBlock();

  TEST_EQUALITY_CONST( andp_block.size(), 0 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractANDPBlock_u238 )
{
  Teuchos::ArrayView<const double> andp_block = 
    xss_data_extractor_u238->extractANDPBlock();

  TEST_EQUALITY_CONST( andp_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the YP block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractYPBlock_h1 )
{
  Teuchos::ArrayView<const double> yp_block = 
    xss_data_extractor_h1->extractYPBlock();

  TEST_EQUALITY_CONST( yp_block.size(), 2 );
  TEST_EQUALITY_CONST( yp_block.front(), 1 );
  TEST_EQUALITY_CONST( yp_block.back(), 102 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractYPBlock_u238 )
{
  Teuchos::ArrayView<const double> yp_block = 
    xss_data_extractor_u238->extractYPBlock();

  TEST_EQUALITY_CONST( yp_block.size(), 3 );
  TEST_EQUALITY_CONST( yp_block.front(), 2 );
  TEST_EQUALITY_CONST( yp_block.back(), 102 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the FIS block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractFISBlock_h1 )
{
  Teuchos::ArrayView<const double> fis_block = 
    xss_data_extractor_h1->extractFISBlock();

  TEST_EQUALITY_CONST( fis_block.size(), 0 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractFISBlock_u238 )
{
  Teuchos::ArrayView<const double> fis_block = 
    xss_data_extractor_u238->extractFISBlock();

  TEST_EQUALITY_CONST( fis_block.size(), 157756 );
  TEST_EQUALITY_CONST( fis_block.front(), 1 );
  TEST_EQUALITY_CONST( fis_block.back(), 1.666468 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the UNR block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractUNRBlock_h1 )
{
  Teuchos::ArrayView<const double> unr_block = 
    xss_data_extractor_h1->extractUNRBlock();

  TEST_EQUALITY_CONST( unr_block.size(), 0 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractUNRBlock_u238 )
{
  Teuchos::ArrayView<const double> unr_block = 
    xss_data_extractor_u238->extractUNRBlock();

  TEST_EQUALITY_CONST( unr_block.size(), 2184 );
  TEST_EQUALITY_CONST( unr_block.front(), 18 );
  TEST_EQUALITY_CONST( unr_block.back(), 1.02014888699 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the DNU block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractDNUBlock_h1 )
{
  Teuchos::ArrayView<const double> dnu_block = 
    xss_data_extractor_h1->extractDNUBlock();

  TEST_EQUALITY_CONST( dnu_block.size(), 0 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractDNUBlock_u238 )
{
  Teuchos::ArrayView<const double> dnu_block = 
    xss_data_extractor_u238->extractDNUBlock();

  TEST_EQUALITY_CONST( dnu_block.size(), 11 );
  TEST_EQUALITY_CONST( dnu_block.front(), 2 );
  TEST_EQUALITY_CONST( dnu_block.back(), 2.60000000000e-02 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the BDD block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractBDDBlock_h1 )
{
  Teuchos::ArrayView<const double> bdd_block =
    xss_data_extractor_h1->extractBDDBlock();
  
  TEST_EQUALITY_CONST( bdd_block.size(), 0 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractBDDBlock_u238 )
{
  Teuchos::ArrayView<const double> bdd_block = 
    xss_data_extractor_u238->extractBDDBlock();

  TEST_EQUALITY_CONST( bdd_block.size(), 42 );
  TEST_EQUALITY_CONST( bdd_block.front(), 1.24942300000e-10 );
  TEST_EQUALITY_CONST( bdd_block.back(), 6.16886800000e-02 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the DNEDL block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractDNEDLBlock_h1 )
{
  Teuchos::ArrayView<const double> dnedl_block = 
    xss_data_extractor_h1->extractDNEDLBlock();

  TEST_EQUALITY_CONST( dnedl_block.size(), 0 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractDNEDLBlock_u238 )
{
  Teuchos::ArrayView<const double> dnedl_block = 
    xss_data_extractor_u238->extractDNEDLBlock();

  TEST_EQUALITY_CONST( dnedl_block.size(), 6 );
  TEST_EQUALITY_CONST( dnedl_block.front(), 1 );
  TEST_EQUALITY_CONST( dnedl_block.back(), 7944 );
}

//---------------------------------------------------------------------------//
// Check that the XSSNeutronDataExtractor can extract the DNED block
TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractDNEDBlock_h1 )
{
  Teuchos::ArrayView<const double> dned_block = 
    xss_data_extractor_h1->extractDNEDBlock();

  TEST_EQUALITY_CONST( dned_block.size(), 0 );
}

TEUCHOS_UNIT_TEST( XSSNeutronDataExtractor, extractDNEDBlock_u238 )
{
  Teuchos::ArrayView<const double> dned_block =
    xss_data_extractor_u238->extractDNEDBlock();

  TEST_EQUALITY_CONST( dned_block.size(), 9768 );
  TEST_EQUALITY_CONST( dned_block.front(), 0 );
  TEST_EQUALITY_CONST( dned_block.back(), 9.99999999000e-01 );
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

  clp.setOption( "test_u238_ace_file",
		 &test_u238_ace_file_name,
		 "Test u238 ACE file name" );
  clp.setOption( "test_u238_ace_table",
		 &test_u238_ace_table_name,
		 "Test u238 ACE table name in u238 ACE file" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  // Initialize ace file handler and data extractor
  ace_file_handler_h1.reset( new Data::ACEFileHandler( test_h1_ace_file_name,
						    test_h1_ace_table_name,
						    1u ) );

  ace_file_handler_u238.reset( new Data::ACEFileHandler( test_u238_ace_file_name,
						    test_u238_ace_table_name,
						    1u ) );

  xss_data_extractor_h1.reset( 
   new Data::XSSNeutronDataExtractor( ace_file_handler_h1->getTableNXSArray(),
				      ace_file_handler_h1->getTableJXSArray(),
				      ace_file_handler_h1->getTableXSSArray() ) );

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
// end tstXSSNeutronDataExtractor.cpp
//---------------------------------------------------------------------------//
