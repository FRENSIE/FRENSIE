//---------------------------------------------------------------------------//
//! 
//! \file   tstXSSSabDataExtractor.cpp
//! \author Alex Robinson
//! \brief  XSS neutron data extractor class unit test
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
#include "Data_XSSSabDataExtractor.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string test_inelastic_only_sab_ace_file_name;
std::string test_inelastic_only_sab_ace_table_name;

Teuchos::RCP<Data::XSSSabDataExtractor> xss_data_extractor_inelastic_only;

std::string test_no_elastic_dist_sab_ace_file_name;
std::string test_no_elastic_dist_sab_ace_table_name;

Teuchos::RCP<Data::XSSSabDataExtractor> xss_data_extractor_no_elastic_dist;

std::string test_full_sab_ace_file_name;
std::string test_full_sab_ace_table_name;

Teuchos::RCP<Data::XSSSabDataExtractor> xss_data_extractor_full;

Teuchos::RCP<Data::ACEFileHandler> ace_file_handler;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return the correct inelastic
// scattering mode
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, 
		   getInelasticScatteringMode_inelastic_only )
{
  TEST_EQUALITY_CONST( 
	       xss_data_extractor_inelastic_only->getInelasticScatteringMode(),
	       Data::EQUIPROBABLE_COSINE_INELASTIC_MODE );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return if elastic cross section 
// data is present
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, 
		   hasElasticScatteringCrossSectionData_inelastic_only )
{
  TEST_ASSERT( !xss_data_extractor_inelastic_only->hasElasticScatteringCrossSectionData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return if elastic angular 
// angular distribution data is present
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, 
		   hasElasticScatteringAngularDistributionData_inelastic_only )
{
  TEST_ASSERT( !xss_data_extractor_inelastic_only->hasElasticScatteringAngularDistributionData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return the correct elastic scattering
// mode
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, 
		   getElasticScatteringMode_inelastic_only )
{
  TEST_EQUALITY_CONST( 
		 xss_data_extractor_inelastic_only->getElasticScatteringMode(),
		 Data::INCOHERENT_ELASTIC_MODE );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITIE block from the
// XSS array
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, extractITIEBlock_inelastic_only )
{
  Teuchos::ArrayView<const double> itie_block = 
    xss_data_extractor_inelastic_only->extractITIEBlock();
  
  TEST_EQUALITY_CONST( itie_block.size(), 116*4+1 );
  TEST_EQUALITY_CONST( itie_block.front(), 116 );
  TEST_EQUALITY_CONST( itie_block.back(), 2.05498256000e+01 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the inelastic energy grid
// from the ITIE block
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, 
		   extractInelasticEnergyGrid_inelastic_only )
{
  Teuchos::ArrayView<const double> inelastic_energy_grid = 
    xss_data_extractor_inelastic_only->extractInelasticEnergyGrid();

  TEST_EQUALITY_CONST( inelastic_energy_grid.size(), 116 );
  TEST_EQUALITY_CONST( inelastic_energy_grid.front(), 1.00000000000e-11 );
  TEST_EQUALITY_CONST( inelastic_energy_grid.back(), 9.15000000000e-06 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the inelastic cross section
// from the ITIE block
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, 
		   extractInelasticCrossSection_inelastic_only )
{
  Teuchos::ArrayView<const double> inelastic_cross_section = 
    xss_data_extractor_inelastic_only->extractInelasticCrossSection();

  TEST_EQUALITY_CONST( inelastic_cross_section.size(), 116 );
  TEST_EQUALITY_CONST( inelastic_cross_section.front(), 8.20604100000e+02 );
  TEST_EQUALITY_CONST( inelastic_cross_section.back(), 2.05498256000e+01 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITCE block from the
// XSS array
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, extractITCEBlock_inelastic_only )
{
  Teuchos::ArrayView<const double> itce_block =
    xss_data_extractor_inelastic_only->extractITCEBlock();

  TEST_EQUALITY_CONST( itce_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the elastic energy grid from
// the ITCE block
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, 
		   extractElasticEnergyGrid_inelastic_only )
{
  Teuchos::ArrayView<const double> elastic_energy_grid = 
    xss_data_extractor_inelastic_only->extractElasticEnergyGrid();

  TEST_EQUALITY_CONST( elastic_energy_grid.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the elastic cross section
// from the ITCE block
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, 
		   extractElasticCrossSection_inelastic_only )
{
  Teuchos::ArrayView<const double> elastic_cross_section = 
    xss_data_extractor_inelastic_only->extractElasticCrossSection();

  TEST_EQUALITY_CONST( elastic_cross_section.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITXE block from the
// XSS array
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, 
		   extractITXEBlock_inelastic_only )
{
  Teuchos::ArrayView<const double> itxe_block = 
    xss_data_extractor_inelastic_only->extractITXEBlock();

  TEST_EQUALITY_CONST( itxe_block.size(), 194880 );
  TEST_EQUALITY_CONST( itxe_block.front(), 3.70354602832e-12 );
  TEST_EQUALITY_CONST( itxe_block.back(), 9.98829728076e-01 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITCA block from the
// XSS array
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, 
		   extractITCABlock_inelastic_only )
{
  Teuchos::ArrayView<const double> itca_block = 
    xss_data_extractor_inelastic_only->extractITCABlock();

  TEST_EQUALITY_CONST( itca_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return the correct inelastic
// scattering mode
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, 
		   getInelasticScatteringMode_no_elastic_dist )
{
  TEST_EQUALITY_CONST( 
	      xss_data_extractor_no_elastic_dist->getInelasticScatteringMode(),
	      Data::EQUIPROBABLE_COSINE_INELASTIC_MODE );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return if elastic cross section 
// data is present
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, 
		   hasElasticScatteringCrossSectionData_no_elastic_dist )
{
  TEST_ASSERT( xss_data_extractor_no_elastic_dist->hasElasticScatteringCrossSectionData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return if elastic angular 
// distribution data is present
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, 
		   hasElasticScatteringAngularDistributionData_no_elastic_dist )
{
  TEST_ASSERT( !xss_data_extractor_no_elastic_dist->hasElasticScatteringAngularDistributionData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return the correct elastic scattering
// mode
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, 
		   getElasticScatteringMode_no_elastic_dist )
{
  TEST_EQUALITY_CONST( 
		xss_data_extractor_no_elastic_dist->getElasticScatteringMode(),
		Data::COHERENT_ELASTIC_MODE );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITIE block from the
// XSS array
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, extractITIEBlock_no_elastic_dist )
{
  Teuchos::ArrayView<const double> itie_block = 
    xss_data_extractor_no_elastic_dist->extractITIEBlock();
  
  TEST_EQUALITY_CONST( itie_block.size(), 116*2+1 );
  TEST_EQUALITY_CONST( itie_block.front(), 116 );
  TEST_EQUALITY_CONST( itie_block.back(), 4.65657034539e+00 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the inelastic energy grid
// from the ITIE block
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, 
		   extractInelasticEnergyGrid_no_elastic_dist )
{
  Teuchos::ArrayView<const double> inelastic_energy_grid = 
    xss_data_extractor_no_elastic_dist->extractInelasticEnergyGrid();

  TEST_EQUALITY_CONST( inelastic_energy_grid.size(), 116 );
  TEST_EQUALITY_CONST( inelastic_energy_grid.front(), 1.00000000000e-11 );
  TEST_EQUALITY_CONST( inelastic_energy_grid.back(), 9.15000000000e-06 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the inelastic cross section
// from the ITIE block
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, 
		   extractInelasticCrossSection_no_elastic_dist )
{
  Teuchos::ArrayView<const double> inelastic_cross_section = 
    xss_data_extractor_no_elastic_dist->extractInelasticCrossSection();

  TEST_EQUALITY_CONST( inelastic_cross_section.size(), 116 );
  TEST_EQUALITY_CONST( inelastic_cross_section.front(), 2.52823500000e+00 );
  TEST_EQUALITY_CONST( inelastic_cross_section.back(), 4.65657034539e+00 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITCE block from the
// XSS array
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, extractITCEBlock_no_elastic_dist )
{
  Teuchos::ArrayView<const double> itce_block =
    xss_data_extractor_no_elastic_dist->extractITCEBlock();

  TEST_EQUALITY_CONST( itce_block.size(), 166*2+1 );
  TEST_EQUALITY_CONST( itce_block.front(), 166 );
  TEST_EQUALITY_CONST( itce_block.back(), 6.25957273359e-07 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the elastic energy grid from
// the ITCE block
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, 
		   extractElasticEnergyGrid_no_elastic_dist )
{
  Teuchos::ArrayView<const double> elastic_energy_grid = 
    xss_data_extractor_no_elastic_dist->extractElasticEnergyGrid();

  TEST_EQUALITY_CONST( elastic_energy_grid.size(), 166 );
  TEST_EQUALITY_CONST( elastic_energy_grid.front(), 1.82219700000e-09 );
  TEST_EQUALITY_CONST( elastic_energy_grid.back(), 1.18488400000e-06 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the elastic cross section
// from the ITCE block
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, 
		   extractElasticCrossSection_no_elastic_dist )
{
  Teuchos::ArrayView<const double> elastic_cross_section = 
    xss_data_extractor_no_elastic_dist->extractElasticCrossSection();

  TEST_EQUALITY_CONST( elastic_cross_section.size(), 166 );
  TEST_EQUALITY_CONST( elastic_cross_section.front(), 1.34746493552e-08 );
  TEST_EQUALITY_CONST( elastic_cross_section.back(), 6.25957273359e-07 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITXE block from the
// XSS array
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, extractITXEBlock_no_elastic_dist )
{
  Teuchos::ArrayView<const double> itxe_block = 
    xss_data_extractor_no_elastic_dist->extractITXEBlock();

  TEST_EQUALITY_CONST( itxe_block.size(), 194880 );
  TEST_EQUALITY_CONST( itxe_block.front(), 1.46571129363e-09 );
  TEST_EQUALITY_CONST( itxe_block.back(), 9.83807305184e-01 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITCA block from the
// XSS array
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, 
		   extractITCABlock_no_elastic_dist )
{
  Teuchos::ArrayView<const double> itca_block = 
    xss_data_extractor_no_elastic_dist->extractITCABlock();

  TEST_EQUALITY_CONST( itca_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return the correct inelastic
// scattering mode
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, 
		   getInelasticScatteringMode_full )
{
  TEST_EQUALITY_CONST( 
	      xss_data_extractor_full->getInelasticScatteringMode(),
	      Data::EQUIPROBABLE_COSINE_INELASTIC_MODE );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return if elastic cross section 
// data is present
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, 
		   hasElasticScatteringCrossSectionData_full )
{
  TEST_ASSERT(xss_data_extractor_full->hasElasticScatteringCrossSectionData());
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return if elastic angular 
// distribution data is present
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, 
		   hasElasticScatteringAngularDistributionData_full )
{
  TEST_ASSERT( xss_data_extractor_full->hasElasticScatteringAngularDistributionData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can return the correct elastic scattering
// mode
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, getElasticScatteringMode_full )
{
  TEST_EQUALITY_CONST( xss_data_extractor_full->getElasticScatteringMode(),
		       Data::INCOHERENT_ELASTIC_MODE );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITIE block from the
// XSS array
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, extractITIEBlock_full )
{
  Teuchos::ArrayView<const double> itie_block = 
    xss_data_extractor_full->extractITIEBlock();
  
  TEST_EQUALITY_CONST( itie_block.size(), 116*2+1 );
  TEST_EQUALITY_CONST( itie_block.front(), 116 );
  TEST_EQUALITY_CONST( itie_block.back(), 2.05400988000e+01 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the inelastic energy grid
// from the ITIE block
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, extractInelasticEnergyGrid_full )
{
  Teuchos::ArrayView<const double> inelastic_energy_grid = 
    xss_data_extractor_full->extractInelasticEnergyGrid();

  TEST_EQUALITY_CONST( inelastic_energy_grid.size(), 116 );
  TEST_EQUALITY_CONST( inelastic_energy_grid.front(), 1.00000000000e-11 );
  TEST_EQUALITY_CONST( inelastic_energy_grid.back(), 9.15000000000e-06 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the inelastic cross section
// from the ITIE block
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, extractInelasticCrossSection_full )
{
  Teuchos::ArrayView<const double> inelastic_cross_section = 
    xss_data_extractor_full->extractInelasticCrossSection();

  TEST_EQUALITY_CONST( inelastic_cross_section.size(), 116 );
  TEST_EQUALITY_CONST( inelastic_cross_section.front(), 3.46065100000e+02 );
  TEST_EQUALITY_CONST( inelastic_cross_section.back(), 2.05400988000e+01 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITCE block from the
// XSS array
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, extractITCEBlock_full )
{
  Teuchos::ArrayView<const double> itce_block =
    xss_data_extractor_full->extractITCEBlock();

  TEST_EQUALITY_CONST( itce_block.size(), 375*2+1 );
  TEST_EQUALITY_CONST( itce_block.front(), 375 );
  TEST_EQUALITY_CONST( itce_block.back(), 6.25377800000E-02 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the elastic energy grid from
// the ITCE block
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, extractElasticEnergyGrid_full )
{
  Teuchos::ArrayView<const double> elastic_energy_grid = 
    xss_data_extractor_full->extractElasticEnergyGrid();

  TEST_EQUALITY_CONST( elastic_energy_grid.size(), 375 );
  TEST_EQUALITY_CONST( elastic_energy_grid.front(), 1.00000000000e-11 );
  TEST_EQUALITY_CONST( elastic_energy_grid.back(), 9.37500000000e-06 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the elastic cross section
// from the ITCE block
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, extractElasticCrossSection_full )
{
  Teuchos::ArrayView<const double> elastic_cross_section = 
    xss_data_extractor_full->extractElasticCrossSection();

  TEST_EQUALITY_CONST( elastic_cross_section.size(), 375 );
  TEST_EQUALITY_CONST( elastic_cross_section.front(), 8.19227100000e+01 );
  TEST_EQUALITY_CONST( elastic_cross_section.back(), 6.25377800000E-02 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITXE block from the
// XSS array
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, extractITXEBlock_full )
{
  Teuchos::ArrayView<const double> itxe_block = 
    xss_data_extractor_full->extractITXEBlock();

  TEST_EQUALITY_CONST( itxe_block.size(), 194880 );
  TEST_EQUALITY_CONST( itxe_block.front(), 9.69217046589E-10 );
  TEST_EQUALITY_CONST( itxe_block.back(), 9.97610585476E-01 );
}

//---------------------------------------------------------------------------//
// Check that the XSSSabDataExtractor can extract the ITCA block from the
// XSS array
TEUCHOS_UNIT_TEST( XSSSabDataExtractor, extractITCABlock_full )
{
  Teuchos::ArrayView<const double> itca_block = 
    xss_data_extractor_full->extractITCABlock();

  TEST_EQUALITY_CONST( itca_block.size(), 7500 );
  TEST_EQUALITY_CONST( itca_block.front(), -9.49966200000e-01 );
  TEST_EQUALITY_CONST( itca_block.back(), 9.99961210000e-01 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_inelastic_only_sab_ace_file",
		 &test_inelastic_only_sab_ace_file_name,
		 "Test S(a,b) ACE file name with inelastic data only" );
  clp.setOption( "test_inelastic_only_sab_ace_table",
		 &test_inelastic_only_sab_ace_table_name,
		 "Test S(a,b) ACE table name in ACE file with inelastic data only" );

  clp.setOption( "test_no_elastic_dist_sab_ace_file",
		 &test_no_elastic_dist_sab_ace_file_name,
		 "Test S(a,b) ACE file name with elastic and inelastic data but no elastic scattering angular distribution" );
  clp.setOption( "test_no_elastic_dist_sab_ace_table",
		 &test_no_elastic_dist_sab_ace_table_name,
		 "Test S(a,b) ACE table name in ACE file with elastic and inelastic data but no elastic scattering angular distribution" );

  clp.setOption( "test_full_sab_ace_file",
		 &test_full_sab_ace_file_name,
		 "Test S(a,b) ACE file name with elastic and inelastic data" );
  clp.setOption( "test_full_sab_ace_table",
		 &test_full_sab_ace_table_name,
		 "Test S(a,b) ACE table name in ACE file with elastic and inelastic data" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
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
// end tstXSSSabDataExtractor.cpp
//---------------------------------------------------------------------------//
