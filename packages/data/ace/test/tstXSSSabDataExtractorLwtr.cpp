//---------------------------------------------------------------------------//
//!
//! \file   tstXSSSabDataExtractorLwtr.cpp
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
std::shared_ptr<Data::XSSSabDataExtractor> xss_data_extractor_lwtr;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return the correct inelastic
// scattering mode
FRENSIE_UNIT_TEST( XSSSabDataExtractor,
		   getInelasticScatteringMode_lwtr )
{
  FRENSIE_CHECK_EQUAL(
	       xss_data_extractor_lwtr->getInelasticScatteringMode(),
	       Data::EQUIPROBABLE_COSINE_INELASTIC_MODE );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return if elastic cross section
// data is present
FRENSIE_UNIT_TEST( XSSSabDataExtractor,
		   hasElasticScatteringCrossSectionData_lwtr )
{
  FRENSIE_CHECK( !xss_data_extractor_lwtr->hasElasticScatteringCrossSectionData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return if elastic angular
// angular distribution data is present
FRENSIE_UNIT_TEST( XSSSabDataExtractor,
		   hasElasticScatteringAngularDistributionData_lwtr )
{
  FRENSIE_CHECK( !xss_data_extractor_lwtr->hasElasticScatteringAngularDistributionData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return the correct elastic scattering
// mode
FRENSIE_UNIT_TEST( XSSSabDataExtractor,
		   getElasticScatteringMode_lwtr )
{
  FRENSIE_CHECK_EQUAL(
		 xss_data_extractor_lwtr->getElasticScatteringMode(),
		 Data::INCOHERENT_ELASTIC_MODE );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITIE block from the
// XSS array
FRENSIE_UNIT_TEST( XSSSabDataExtractor, extractITIEBlock_lwtr )
{
  Utility::ArrayView<const double> itie_block =
    xss_data_extractor_lwtr->extractITIEBlock();

  FRENSIE_CHECK_EQUAL( itie_block.size(), 116*2+1 );
  FRENSIE_CHECK_EQUAL( itie_block.front(), 116 );
  FRENSIE_CHECK_EQUAL( itie_block.back(), 2.05498256000e+01 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the inelastic energy grid
// from the ITIE block
FRENSIE_UNIT_TEST( XSSSabDataExtractor,
		   extractInelasticEnergyGrid_lwtr )
{
  auto inelastic_energy_grid =
    xss_data_extractor_lwtr->extractInelasticEnergyGrid();

  FRENSIE_CHECK_EQUAL( inelastic_energy_grid.size(), 116 );
  FRENSIE_CHECK_EQUAL( inelastic_energy_grid.front(), 1.00000000000e-11 );
  FRENSIE_CHECK_EQUAL( inelastic_energy_grid.back(), 9.15000000000e-06 );

  auto inelastic_energy_grid_in_mev =
    xss_data_extractor_lwtr->extractInelasticEnergyGridInMeV();

  FRENSIE_CHECK_EQUAL( inelastic_energy_grid_in_mev.size(), 116 );
  FRENSIE_CHECK_EQUAL( inelastic_energy_grid_in_mev.front(), 1.00000000000e-11*MeV );
  FRENSIE_CHECK_EQUAL( inelastic_energy_grid_in_mev.back(), 9.15000000000e-06*MeV );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the inelastic cross section
// from the ITIE block
FRENSIE_UNIT_TEST( XSSSabDataExtractor,
		   extractInelasticCrossSection_lwtr )
{
  auto inelastic_cross_section =
    xss_data_extractor_lwtr->extractInelasticCrossSection();

  FRENSIE_CHECK_EQUAL( inelastic_cross_section.size(), 116 );
  FRENSIE_CHECK_EQUAL( inelastic_cross_section.front(), 8.20604100000e+02 );
  FRENSIE_CHECK_EQUAL( inelastic_cross_section.back(), 2.05498256000e+01 );

  auto inelastic_cross_section_in_barns =
    xss_data_extractor_lwtr->extractInelasticCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( inelastic_cross_section_in_barns.size(), 116 );
  FRENSIE_CHECK_EQUAL( inelastic_cross_section_in_barns.front(), 8.20604100000e+02*barns );
  FRENSIE_CHECK_EQUAL( inelastic_cross_section_in_barns.back(), 2.05498256000e+01*barns );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITCE block from the
// XSS array
FRENSIE_UNIT_TEST( XSSSabDataExtractor, extractITCEBlock_lwtr )
{
  Utility::ArrayView<const double> itce_block =
    xss_data_extractor_lwtr->extractITCEBlock();

  FRENSIE_CHECK_EQUAL( itce_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the elastic energy grid from
// the ITCE block
FRENSIE_UNIT_TEST( XSSSabDataExtractor,
		   extractElasticEnergyGrid_lwtr )
{
  auto elastic_energy_grid =
    xss_data_extractor_lwtr->extractElasticEnergyGrid();

  FRENSIE_CHECK_EQUAL( elastic_energy_grid.size(), 0 );

  auto elastic_energy_grid_in_mev =
    xss_data_extractor_lwtr->extractElasticEnergyGridInMeV();

  FRENSIE_CHECK_EQUAL( elastic_energy_grid_in_mev.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the elastic cross section
// from the ITCE block
FRENSIE_UNIT_TEST( XSSSabDataExtractor,
		   extractElasticCrossSection_lwtr )
{
  auto elastic_cross_section =
    xss_data_extractor_lwtr->extractElasticCrossSection();

  FRENSIE_CHECK_EQUAL( elastic_cross_section.size(), 0 );

  auto elastic_cross_section_in_barns =
    xss_data_extractor_lwtr->extractElasticCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( elastic_cross_section_in_barns.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITXE block from the
// XSS array
FRENSIE_UNIT_TEST( XSSSabDataExtractor,
		   extractITXEBlock_lwtr )
{
  Utility::ArrayView<const double> itxe_block =
    xss_data_extractor_lwtr->extractITXEBlock();

  FRENSIE_CHECK_EQUAL( itxe_block.size(), 194880 );
  FRENSIE_CHECK_EQUAL( itxe_block.front(), 3.70354602832e-12 );
  FRENSIE_CHECK_EQUAL( itxe_block.back(), 9.98829728076e-01 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITCA block from the
// XSS array
FRENSIE_UNIT_TEST( XSSSabDataExtractor,
		   extractITCABlock_lwtr )
{
  Utility::ArrayView<const double> itca_block =
    xss_data_extractor_lwtr->extractITCABlock();

  FRENSIE_CHECK_EQUAL( itca_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_lwtr_sab_ace_file_name;
std::string test_lwtr_sab_ace_table_name;
unsigned test_lwtr_sab_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_lwtr_sab_ace_table",
                                        test_lwtr_sab_ace_table_name, "",
                                        "Test light water S(a,b) ACE table name in ACE file" );
  
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_lwtr_sab_ace_file",
                                        test_lwtr_sab_ace_file_name, "",
                                        "Test light water S(a,b) ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_lwtr_sab_ace_file_start_line",
                                        test_lwtr_sab_ace_file_start_line, 1,
                                        "Test light water S(a,b) ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize ace file handler and data extractor
  std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
  	      new Data::ACEFileHandler( test_lwtr_sab_ace_file_name,
					test_lwtr_sab_ace_table_name,
					test_lwtr_sab_ace_file_start_line ) );

  xss_data_extractor_lwtr.reset(
       new Data::XSSSabDataExtractor( ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstXSSSabDataExtractorLwtr.cpp
//---------------------------------------------------------------------------//
