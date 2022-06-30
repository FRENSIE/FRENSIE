//---------------------------------------------------------------------------//
//! 
//! \file   tstXSSSabDataExtractor.cpp
//! \author Eli Moll
//! \brief  XSS neutron data extractor class unit test
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>


// FRENSIE Includes
#include <Utility_UnitTestHarnessWithMain.hpp>
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSSabDataExtractor.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string test_inelastic_only_sab_ace_file_name;
std::string test_inelastic_only_sab_ace_table_name;

std::shared_ptr<Data::XSSSabDataExtractor> xss_data_extractor_inelastic_only;

std::string test_no_elastic_dist_sab_ace_file_name;
std::string test_no_elastic_dist_sab_ace_table_name;

std::shared_ptr<Data::XSSSabDataExtractor> xss_data_extractor_no_elastic_dist;

std::string test_full_sab_ace_file_name;
std::string test_full_sab_ace_table_name;

std::shared_ptr<Data::XSSSabDataExtractor> xss_data_extractor_full;

std::shared_ptr<Data::ACEFileHandler> ace_file_handler;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return the correct inelastic
// scattering mode
FRENSIE_UNIT_TEST( XSSSabDataExtractor, 
		   getInelasticScatteringMode_inelastic_only )
{
  FRENSIE_CHECK_EQUAL( 
	       xss_data_extractor_inelastic_only->getInelasticScatteringMode(),
	       Data::EQUIPROBABLE_COSINE_INELASTIC_MODE );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return if elastic cross section 
// data is present
FRENSIE_UNIT_TEST( XSSSabDataExtractor, 
		   hasElasticScatteringCrossSectionData_inelastic_only )
{
  FRENSIE_CHECK( !xss_data_extractor_inelastic_only->hasElasticScatteringCrossSectionData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return if elastic angular 
// angular distribution data is present
FRENSIE_UNIT_TEST( XSSSabDataExtractor, 
		   hasElasticScatteringAngularDistributionData_inelastic_only )
{
  FRENSIE_CHECK( !xss_data_extractor_inelastic_only->hasElasticScatteringAngularDistributionData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return the correct elastic scattering
// mode
FRENSIE_UNIT_TEST( XSSSabDataExtractor, 
		   getElasticScatteringMode_inelastic_only )
{
  FRENSIE_CHECK_EQUAL( 
		 xss_data_extractor_inelastic_only->getElasticScatteringMode(),
		 Data::INCOHERENT_ELASTIC_MODE );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITIE block from the
// XSS array
FRENSIE_UNIT_TEST( XSSSabDataExtractor, extractITIEBlock_inelastic_only )
{
  Utility::ArrayView<const double> itie_block = 
    xss_data_extractor_inelastic_only->extractITIEBlock();
  
  FRENSIE_CHECK_EQUAL( itie_block.size(), 116*4+1 );
  FRENSIE_CHECK_EQUAL( itie_block.front(), 116 );
  FRENSIE_CHECK_EQUAL( itie_block.back(), 5.85000000000E+02 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the inelastic energy grid
// from the ITIE block
FRENSIE_UNIT_TEST( XSSSabDataExtractor, 
		   extractInelasticEnergyGrid_inelastic_only )
{
  Utility::ArrayView<const double> inelastic_energy_grid = 
    xss_data_extractor_inelastic_only->extractInelasticEnergyGrid();

  FRENSIE_CHECK_EQUAL( inelastic_energy_grid.size(), 116 );
  FRENSIE_CHECK_EQUAL( inelastic_energy_grid.front(), 1.00000000000e-11 );
  FRENSIE_CHECK_EQUAL( inelastic_energy_grid.back(), 9.15000000000e-06 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the inelastic cross section
// from the ITIE block
FRENSIE_UNIT_TEST( XSSSabDataExtractor, 
		   extractInelasticCrossSection_inelastic_only )
{
  Utility::ArrayView<const double> inelastic_cross_section = 
    xss_data_extractor_inelastic_only->extractInelasticCrossSection();

  FRENSIE_CHECK_EQUAL( inelastic_cross_section.size(), 116 );
  FRENSIE_CHECK_EQUAL( inelastic_cross_section.front(), 8.20604100000e+02 );
  FRENSIE_CHECK_EQUAL( inelastic_cross_section.back(), 2.05498356000E+01 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITCE block from the
// XSS array
FRENSIE_UNIT_TEST( XSSSabDataExtractor, extractITCEBlock_inelastic_only )
{
  Utility::ArrayView<const double> itce_block =
    xss_data_extractor_inelastic_only->extractITCEBlock();

  FRENSIE_CHECK_EQUAL( itce_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the elastic energy grid from
// the ITCE block
FRENSIE_UNIT_TEST( XSSSabDataExtractor, 
		   extractElasticEnergyGrid_inelastic_only )
{
  Utility::ArrayView<const double> elastic_energy_grid = 
    xss_data_extractor_inelastic_only->extractElasticEnergyGrid();

  FRENSIE_CHECK_EQUAL( elastic_energy_grid.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the elastic cross section
// from the ITCE block
FRENSIE_UNIT_TEST( XSSSabDataExtractor, 
		   extractElasticCrossSection_inelastic_only )
{
  Utility::ArrayView<const double> elastic_cross_section = 
    xss_data_extractor_inelastic_only->extractElasticCrossSection();

  FRENSIE_CHECK_EQUAL( elastic_cross_section.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITXE block from the
// XSS array
FRENSIE_UNIT_TEST( XSSSabDataExtractor, 
		   extractITXEBlock_inelastic_only )
{
  Utility::ArrayView<const double> itxe_block = 
    xss_data_extractor_inelastic_only->extractITXEBlock();

  FRENSIE_CHECK_EQUAL( itxe_block.size(), 1228384 );
  FRENSIE_CHECK_EQUAL( itxe_block.front(), 5.37107000000E-14 );
  FRENSIE_CHECK_EQUAL( itxe_block.back(),  9.88396962963E-01 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITCA block from the
// XSS array
FRENSIE_UNIT_TEST( XSSSabDataExtractor, 
		   extractITCABlock_inelastic_only )
{
  Utility::ArrayView<const double> itca_block = 
    xss_data_extractor_inelastic_only->extractITCABlock();

  FRENSIE_CHECK_EQUAL( itca_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return the correct inelastic
// scattering mode
FRENSIE_UNIT_TEST( XSSSabDataExtractor, 
		   getInelasticScatteringMode_no_elastic_dist )
{
  FRENSIE_CHECK_EQUAL( 
	      xss_data_extractor_no_elastic_dist->getInelasticScatteringMode(),
	      Data::EQUIPROBABLE_COSINE_INELASTIC_MODE );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return if elastic cross section 
// data is present
FRENSIE_UNIT_TEST( XSSSabDataExtractor, 
		   hasElasticScatteringCrossSectionData_no_elastic_dist )
{
  FRENSIE_CHECK( xss_data_extractor_no_elastic_dist->hasElasticScatteringCrossSectionData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return if elastic angular 
// distribution data is present
FRENSIE_UNIT_TEST( XSSSabDataExtractor, 
		   hasElasticScatteringAngularDistributionData_no_elastic_dist )
{
  FRENSIE_CHECK( !xss_data_extractor_no_elastic_dist->hasElasticScatteringAngularDistributionData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return the correct elastic scattering
// mode
FRENSIE_UNIT_TEST( XSSSabDataExtractor, 
		   getElasticScatteringMode_no_elastic_dist )
{
  FRENSIE_CHECK_EQUAL( 
		xss_data_extractor_no_elastic_dist->getElasticScatteringMode(),
		Data::COHERENT_ELASTIC_MODE );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITIE block from the
// XSS array
FRENSIE_UNIT_TEST( XSSSabDataExtractor, extractITIEBlock_no_elastic_dist )
{
  Utility::ArrayView<const double> itie_block = 
    xss_data_extractor_no_elastic_dist->extractITIEBlock();
  
  FRENSIE_CHECK_EQUAL( itie_block.size(), 116*4+1 );
  FRENSIE_CHECK_EQUAL( itie_block.front(), 116 );
  FRENSIE_CHECK_EQUAL( itie_block.back(), 4.34000000000E+02 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the inelastic energy grid
// from the ITIE block
FRENSIE_UNIT_TEST( XSSSabDataExtractor, 
		   extractInelasticEnergyGrid_no_elastic_dist )
{
  Utility::ArrayView<const double> inelastic_energy_grid = 
    xss_data_extractor_no_elastic_dist->extractInelasticEnergyGrid();

  FRENSIE_CHECK_EQUAL( inelastic_energy_grid.size(), 116 );
  FRENSIE_CHECK_EQUAL( inelastic_energy_grid.front(), 1.00000000000e-11 );
  FRENSIE_CHECK_EQUAL( inelastic_energy_grid.back(), 9.15000000000e-06 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the inelastic cross section
// from the ITIE block
FRENSIE_UNIT_TEST( XSSSabDataExtractor, 
		   extractInelasticCrossSection_no_elastic_dist )
{
  Utility::ArrayView<const double> inelastic_cross_section = 
    xss_data_extractor_no_elastic_dist->extractInelasticCrossSection();

  FRENSIE_CHECK_EQUAL( inelastic_cross_section.size(), 116 );
  FRENSIE_CHECK_EQUAL( inelastic_cross_section.front(), 2.52820200000E+00 );
  FRENSIE_CHECK_EQUAL( inelastic_cross_section.back(), 4.65752074498E+00 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITCE block from the
// XSS array
FRENSIE_UNIT_TEST( XSSSabDataExtractor, extractITCEBlock_no_elastic_dist )
{
  Utility::ArrayView<const double> itce_block =
    xss_data_extractor_no_elastic_dist->extractITCEBlock();

  FRENSIE_CHECK_EQUAL( itce_block.size(), 166*2+1 );
  FRENSIE_CHECK_EQUAL( itce_block.front(), 166 );
  FRENSIE_CHECK_EQUAL( itce_block.back(), 6.25957273359E-07 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the elastic energy grid from
// the ITCE block
FRENSIE_UNIT_TEST( XSSSabDataExtractor, 
		   extractElasticEnergyGrid_no_elastic_dist )
{
  Utility::ArrayView<const double> elastic_energy_grid = 
    xss_data_extractor_no_elastic_dist->extractElasticEnergyGrid();

  FRENSIE_CHECK_EQUAL( elastic_energy_grid.size(), 166 );
  FRENSIE_CHECK_EQUAL( elastic_energy_grid.front(), 1.82219700000E-09 );
  FRENSIE_CHECK_EQUAL( elastic_energy_grid.back(), 1.18488400000E-06 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the elastic cross section
// from the ITCE block
FRENSIE_UNIT_TEST( XSSSabDataExtractor, 
		   extractElasticCrossSection_no_elastic_dist )
{
  Utility::ArrayView<const double> elastic_cross_section = 
    xss_data_extractor_no_elastic_dist->extractElasticCrossSection();

  FRENSIE_CHECK_EQUAL( elastic_cross_section.size(), 166 );
  FRENSIE_CHECK_EQUAL( elastic_cross_section.front(), 1.34746493552E-08 );
  FRENSIE_CHECK_EQUAL( elastic_cross_section.back(), 6.25957273359E-07 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITXE block from the
// XSS array
FRENSIE_UNIT_TEST( XSSSabDataExtractor, extractITXEBlock_no_elastic_dist )
{
  Utility::ArrayView<const double> itxe_block = 
    xss_data_extractor_no_elastic_dist->extractITXEBlock();

  FRENSIE_CHECK_EQUAL( itxe_block.size(), 1194252 );
  FRENSIE_CHECK_EQUAL( itxe_block.front(), 1.09631000000E-10 );
  FRENSIE_CHECK_EQUAL( itxe_block.back(), 8.41618844000E-01 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITCA block from the
// XSS array
FRENSIE_UNIT_TEST( XSSSabDataExtractor, 
		   extractITCABlock_no_elastic_dist )
{
  Utility::ArrayView<const double> itca_block = 
    xss_data_extractor_no_elastic_dist->extractITCABlock();

  FRENSIE_CHECK_EQUAL( itca_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return the correct inelastic
// scattering mode
FRENSIE_UNIT_TEST( XSSSabDataExtractor, 
		   getInelasticScatteringMode_full )
{
  FRENSIE_CHECK_EQUAL( 
	      xss_data_extractor_full->getInelasticScatteringMode(),
	      Data::EQUIPROBABLE_COSINE_INELASTIC_MODE );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return if elastic cross section 
// data is present
FRENSIE_UNIT_TEST( XSSSabDataExtractor, 
		   hasElasticScatteringCrossSectionData_full )
{
  FRENSIE_CHECK(xss_data_extractor_full->hasElasticScatteringCrossSectionData());
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return if elastic angular 
// distribution data is present
FRENSIE_UNIT_TEST( XSSSabDataExtractor, 
		   hasElasticScatteringAngularDistributionData_full )
{
  FRENSIE_CHECK( xss_data_extractor_full->hasElasticScatteringAngularDistributionData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return the correct elastic scattering
// mode
FRENSIE_UNIT_TEST( XSSSabDataExtractor, getElasticScatteringMode_full )
{
  FRENSIE_CHECK_EQUAL( xss_data_extractor_full->getElasticScatteringMode(),
		       Data::INCOHERENT_ELASTIC_MODE );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITIE block from the
// XSS array
FRENSIE_UNIT_TEST( XSSSabDataExtractor, extractITIEBlock_full )
{
  Utility::ArrayView<const double> itie_block = 
    xss_data_extractor_full->extractITIEBlock();
  
  FRENSIE_CHECK_EQUAL( itie_block.size(), 116*4+1 );
  FRENSIE_CHECK_EQUAL( itie_block.front(), 116 );
  FRENSIE_CHECK_EQUAL( itie_block.back(), 3.83000000000E+02 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the inelastic energy grid
// from the ITIE block
FRENSIE_UNIT_TEST( XSSSabDataExtractor, extractInelasticEnergyGrid_full )
{
  Utility::ArrayView<const double> inelastic_energy_grid = 
    xss_data_extractor_full->extractInelasticEnergyGrid();

  FRENSIE_CHECK_EQUAL( inelastic_energy_grid.size(), 116 );
  FRENSIE_CHECK_EQUAL( inelastic_energy_grid.front(), 1.00000000000e-11 );
  FRENSIE_CHECK_EQUAL( inelastic_energy_grid.back(), 9.15000000000e-06 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the inelastic cross section
// from the ITIE block
FRENSIE_UNIT_TEST( XSSSabDataExtractor, extractInelasticCrossSection_full )
{
  Utility::ArrayView<const double> inelastic_cross_section = 
    xss_data_extractor_full->extractInelasticCrossSection();

  FRENSIE_CHECK_EQUAL( inelastic_cross_section.size(), 116 );
  FRENSIE_CHECK_EQUAL( inelastic_cross_section.front(), 3.46057700000E+02 );
  FRENSIE_CHECK_EQUAL( inelastic_cross_section.back(), 2.05407024000E+01 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITCE block from the
// XSS array
FRENSIE_UNIT_TEST( XSSSabDataExtractor, extractITCEBlock_full )
{
  Utility::ArrayView<const double> itce_block =
    xss_data_extractor_full->extractITCEBlock();

  FRENSIE_CHECK_EQUAL( itce_block.size(), 375*2+1 );
  FRENSIE_CHECK_EQUAL( itce_block.front(), 375 );
  FRENSIE_CHECK_EQUAL( itce_block.back(), 6.25377800000E-02 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the elastic energy grid from
// the ITCE block
FRENSIE_UNIT_TEST( XSSSabDataExtractor, extractElasticEnergyGrid_full )
{
  Utility::ArrayView<const double> elastic_energy_grid = 
    xss_data_extractor_full->extractElasticEnergyGrid();

  FRENSIE_CHECK_EQUAL( elastic_energy_grid.size(), 375 );
  FRENSIE_CHECK_EQUAL( elastic_energy_grid.front(), 1.00000000000e-11 );
  FRENSIE_CHECK_EQUAL( elastic_energy_grid.back(), 9.37500000000e-06 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the elastic cross section
// from the ITCE block
FRENSIE_UNIT_TEST( XSSSabDataExtractor, extractElasticCrossSection_full )
{
  Utility::ArrayView<const double> elastic_cross_section = 
    xss_data_extractor_full->extractElasticCrossSection();

  FRENSIE_CHECK_EQUAL( elastic_cross_section.size(), 375 );
  FRENSIE_CHECK_EQUAL( elastic_cross_section.front(), 8.19227100000e+01 );
  FRENSIE_CHECK_EQUAL( elastic_cross_section.back(), 6.25377800000E-02 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITXE block from the
// XSS array
FRENSIE_UNIT_TEST( XSSSabDataExtractor, extractITXEBlock_full )
{
  Utility::ArrayView<const double> itxe_block = 
    xss_data_extractor_full->extractITXEBlock();

  FRENSIE_CHECK_EQUAL( itxe_block.size(), 960894 );
  FRENSIE_CHECK_EQUAL( itxe_block.front(), 7.37621000000E-11 );
  FRENSIE_CHECK_EQUAL( itxe_block.back(), 9.86864771301E-01 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITCA block from the
// XSS array
FRENSIE_UNIT_TEST( XSSSabDataExtractor, extractITCABlock_full )
{
  Utility::ArrayView<const double> itca_block = 
    xss_data_extractor_full->extractITCABlock();

  FRENSIE_CHECK_EQUAL( itca_block.size(), 7500 );
  FRENSIE_CHECK_EQUAL( itca_block.front(), -9.49966200000E-01 );
  FRENSIE_CHECK_EQUAL( itca_block.back(), 9.99961210000e-01 );
}

//---------------------------------------------------------------------------//
// Check that the data is continuous in energy
FRENSIE_UNIT_TEST( XSSSabDataExtractor, test_continuous_energy )
{
  FRENSIE_CHECK(xss_data_extractor_full->isDataContinuousEnergy());
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_inelastic_only_sab_ace_file",
                                        test_inelastic_only_sab_ace_file_name, "",
                                        "Test S(a,b) ACE file name with inelastic data only" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_inelastic_only_sab_ace_table",
		                                    test_inelastic_only_sab_ace_table_name, "",
		                                    "Test S(a,b) ACE table name in ACE file with inelastic data only" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_no_elastic_dist_sab_ace_file",
                                        test_no_elastic_dist_sab_ace_file_name, "",
                                        "Test S(a,b) ACE file name with elastic and inelastic data but no elastic scattering angular distribution" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_no_elastic_dist_sab_ace_table",
                                        test_no_elastic_dist_sab_ace_table_name, "",
                                        "Test S(a,b) ACE table name in ACE file with elastic and inelastic data but no elastic scattering angular distribution" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_full_sab_ace_file",
                                        test_full_sab_ace_file_name, "",
                                        "Test S(a,b) ACE file name with elastic and inelastic data" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_full_sab_ace_table",
                                        test_full_sab_ace_table_name, "",
                                        "Test S(a,b) ACE table name in ACE file with elastic and inelastic data" );

  // Initialize ace file handler and data extractor
  ace_file_handler.reset( 
	      new Data::ACEFileHandler( test_inelastic_only_sab_ace_file_name,
					test_inelastic_only_sab_ace_table_name,
					1u ) );

  xss_data_extractor_inelastic_only.reset( 
       new Data::XSSSabDataExtractor( ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

  ace_file_handler.reset(
	     new Data::ACEFileHandler( test_no_elastic_dist_sab_ace_file_name,
				       test_no_elastic_dist_sab_ace_table_name,
				       1u ) );

  xss_data_extractor_no_elastic_dist.reset(
       new Data::XSSSabDataExtractor( ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

  ace_file_handler.reset(
	     new Data::ACEFileHandler( test_full_sab_ace_file_name,
				       test_full_sab_ace_table_name,
				       1u ) );

  xss_data_extractor_full.reset(
       new Data::XSSSabDataExtractor( ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
  
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();


//---------------------------------------------------------------------------//
// end tstXSSSabDataExtractor.cpp
//---------------------------------------------------------------------------//
