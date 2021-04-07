//---------------------------------------------------------------------------//
//!
//! \file   tstXSSSabDataExtractorPoly.cpp
//! \author Alex Robinson
//! \brief  XSS neutron data extractor class unit test
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSSabDataExtractor.hpp"
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
std::shared_ptr<Data::XSSSabDataExtractor> xss_data_extractor_poly;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return the correct inelastic
// scattering mode
FRENSIE_UNIT_TEST( XSSSabDataExtractor,
		   getInelasticScatteringMode_poly )
{
  FRENSIE_CHECK_EQUAL(
	      xss_data_extractor_poly->getInelasticScatteringMode(),
	      Data::EQUIPROBABLE_COSINE_INELASTIC_MODE );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return if elastic cross section
// data is present
FRENSIE_UNIT_TEST( XSSSabDataExtractor,
		   hasElasticScatteringCrossSectionData_poly )
{
  FRENSIE_CHECK(xss_data_extractor_poly->hasElasticScatteringCrossSectionData());
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return if elastic angular
// distribution data is present
FRENSIE_UNIT_TEST( XSSSabDataExtractor,
		   hasElasticScatteringAngularDistributionData_poly )
{
  FRENSIE_CHECK( xss_data_extractor_poly->hasElasticScatteringAngularDistributionData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return the correct elastic scattering
// mode
FRENSIE_UNIT_TEST( XSSSabDataExtractor, getElasticScatteringMode_poly )
{
  FRENSIE_CHECK_EQUAL( xss_data_extractor_poly->getElasticScatteringMode(),
		       Data::INCOHERENT_ELASTIC_MODE );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITIE block from the
// XSS array
FRENSIE_UNIT_TEST( XSSSabDataExtractor, extractITIEBlock_poly )
{
  Utility::ArrayView<const double> itie_block =
    xss_data_extractor_poly->extractITIEBlock();

  FRENSIE_CHECK_EQUAL( itie_block.size(), 116*2+1 );
  FRENSIE_CHECK_EQUAL( itie_block.front(), 116 );
  FRENSIE_CHECK_EQUAL( itie_block.back(), 2.05400988000e+01 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the inelastic energy grid
// from the ITIE block
FRENSIE_UNIT_TEST( XSSSabDataExtractor, extractInelasticEnergyGrid_poly )
{
  auto inelastic_energy_grid =
    xss_data_extractor_poly->extractInelasticEnergyGrid();

  FRENSIE_CHECK_EQUAL( inelastic_energy_grid.size(), 116 );
  FRENSIE_CHECK_EQUAL( inelastic_energy_grid.front(), 1.00000000000e-11 );
  FRENSIE_CHECK_EQUAL( inelastic_energy_grid.back(), 9.15000000000e-06 );

  auto inelastic_energy_grid_in_mev =
    xss_data_extractor_poly->extractInelasticEnergyGridInMeV();

  FRENSIE_CHECK_EQUAL( inelastic_energy_grid_in_mev.size(), 116 );
  FRENSIE_CHECK_EQUAL( inelastic_energy_grid_in_mev.front(), 1.00000000000e-11*MeV );
  FRENSIE_CHECK_EQUAL( inelastic_energy_grid_in_mev.back(), 9.15000000000e-06*MeV );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the inelastic cross section
// from the ITIE block
FRENSIE_UNIT_TEST( XSSSabDataExtractor, extractInelasticCrossSection_poly )
{
  auto inelastic_cross_section =
    xss_data_extractor_poly->extractInelasticCrossSection();

  FRENSIE_CHECK_EQUAL( inelastic_cross_section.size(), 116 );
  FRENSIE_CHECK_EQUAL( inelastic_cross_section.front(), 3.46065100000e+02 );
  FRENSIE_CHECK_EQUAL( inelastic_cross_section.back(), 2.05400988000e+01 );

  auto inelastic_cross_section_in_barns =
    xss_data_extractor_poly->extractInelasticCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( inelastic_cross_section_in_barns.size(), 116 );
  FRENSIE_CHECK_EQUAL( inelastic_cross_section_in_barns.front(), 3.46065100000e+02*barns );
  FRENSIE_CHECK_EQUAL( inelastic_cross_section_in_barns.back(), 2.05400988000e+01*barns );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITCE block from the
// XSS array
FRENSIE_UNIT_TEST( XSSSabDataExtractor, extractITCEBlock_poly )
{
  Utility::ArrayView<const double> itce_block =
    xss_data_extractor_poly->extractITCEBlock();

  FRENSIE_CHECK_EQUAL( itce_block.size(), 375*2+1 );
  FRENSIE_CHECK_EQUAL( itce_block.front(), 375 );
  FRENSIE_CHECK_EQUAL( itce_block.back(), 6.25377800000E-02 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the elastic energy grid from
// the ITCE block
FRENSIE_UNIT_TEST( XSSSabDataExtractor, extractElasticEnergyGrid_poly )
{
  auto elastic_energy_grid =
    xss_data_extractor_poly->extractElasticEnergyGrid();

  FRENSIE_CHECK_EQUAL( elastic_energy_grid.size(), 375 );
  FRENSIE_CHECK_EQUAL( elastic_energy_grid.front(), 1.00000000000e-11 );
  FRENSIE_CHECK_EQUAL( elastic_energy_grid.back(), 9.37500000000e-06 );

  auto elastic_energy_grid_in_mev =
    xss_data_extractor_poly->extractElasticEnergyGridInMeV();

  FRENSIE_CHECK_EQUAL( elastic_energy_grid_in_mev.size(), 375 );
  FRENSIE_CHECK_EQUAL( elastic_energy_grid_in_mev.front(), 1.00000000000e-11*MeV );
  FRENSIE_CHECK_EQUAL( elastic_energy_grid_in_mev.back(), 9.37500000000e-06*MeV );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the elastic cross section
// from the ITCE block
FRENSIE_UNIT_TEST( XSSSabDataExtractor, extractElasticCrossSection_poly )
{
  auto elastic_cross_section =
    xss_data_extractor_poly->extractElasticCrossSection();

  FRENSIE_CHECK_EQUAL( elastic_cross_section.size(), 375 );
  FRENSIE_CHECK_EQUAL( elastic_cross_section.front(), 8.19227100000e+01 );
  FRENSIE_CHECK_EQUAL( elastic_cross_section.back(), 6.25377800000E-02 );

  auto elastic_cross_section_in_barns =
    xss_data_extractor_poly->extractElasticCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( elastic_cross_section_in_barns.size(), 375 );
  FRENSIE_CHECK_EQUAL( elastic_cross_section_in_barns.front(), 8.19227100000e+01*barns );
  FRENSIE_CHECK_EQUAL( elastic_cross_section_in_barns.back(), 6.25377800000E-02*barns );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITXE block from the
// XSS array
FRENSIE_UNIT_TEST( XSSSabDataExtractor, extractITXEBlock_poly )
{
  Utility::ArrayView<const double> itxe_block =
    xss_data_extractor_poly->extractITXEBlock();

  FRENSIE_CHECK_EQUAL( itxe_block.size(), 194880 );
  FRENSIE_CHECK_EQUAL( itxe_block.front(), 9.69217046589E-10 );
  FRENSIE_CHECK_EQUAL( itxe_block.back(), 9.97610585476E-01 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITCA block from the
// XSS array
FRENSIE_UNIT_TEST( XSSSabDataExtractor, extractITCABlock_poly )
{
  Utility::ArrayView<const double> itca_block =
    xss_data_extractor_poly->extractITCABlock();

  FRENSIE_CHECK_EQUAL( itca_block.size(), 7500 );
  FRENSIE_CHECK_EQUAL( itca_block.front(), -9.49966200000e-01 );
  FRENSIE_CHECK_EQUAL( itca_block.back(), 9.99961210000e-01 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_poly_sab_ace_file_name;
std::string test_poly_sab_ace_table_name;
unsigned test_poly_sab_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_poly_sab_ace_table",
                                        test_poly_sab_ace_table_name, "",
                                        "Test polyethylene S(a,b) ACE table name" );
  
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_poly_sab_ace_file",
                                        test_poly_sab_ace_file_name, "",
                                        "Test polyethylene S(a,b) ACE file name" );
  
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_poly_sab_ace_file_start_line",
                                        test_poly_sab_ace_file_start_line, 1,
                                        "Test polyethylene S(a,b) ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize ace file handler and data extractor
  std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
	     new Data::ACEFileHandler( test_poly_sab_ace_file_name,
				       test_poly_sab_ace_table_name,
				       test_poly_sab_ace_file_start_line ) );

  xss_data_extractor_poly.reset(
       new Data::XSSSabDataExtractor( ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstXSSSabDataExtractorPoly.cpp
//---------------------------------------------------------------------------//
