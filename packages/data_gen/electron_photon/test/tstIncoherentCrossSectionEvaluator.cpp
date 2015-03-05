//---------------------------------------------------------------------------//
//!
//! \file   tstIncoherentCrossSectionEvaluator.cpp
//! \author Alex Robinson
//! \brief  Incoherent cross section evaluator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "DataGen_IncoherentCrossSectionEvaluator.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_KleinNishinaDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
Teuchos::RCP<DataGen::IncoherentCrossSectionEvaluator>
  incoherent_cs_evaluator_free(new DataGen::IncoherentCrossSectionEvaluator());

Teuchos::RCP<DataGen::IncoherentCrossSectionEvaluator>
  incoherent_cs_evaluator_h;

Teuchos::RCP<DataGen::IncoherentCrossSectionEvaluator>
  incoherent_cs_evaluator_pb;

Teuchos::RCP<Utility::OneDDistribution> incoherent_cs_h;
Teuchos::RCP<Utility::OneDDistribution> incoherent_cs_pb;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
bool notEqualZero( const double value )
{
  return value != 0.0;
}

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the differential cross section can be evaluated
TEUCHOS_UNIT_TEST( IncoherentCrossSectionEvaluator, 
		   evaluateDifferentialCrossSection_free )
{
  Utility::KleinNishinaDistribution kn_distribution( 0.001 );

  double differential_cs = 
    incoherent_cs_evaluator_free->evaluateDifferentialCrossSection( 
							    1.0039139026724953,
							    kn_distribution );
  TEST_EQUALITY( differential_cs, 
		 kn_distribution.evaluate( 1.0039139026724953 )/1e-24 );
  
  differential_cs = 
    incoherent_cs_evaluator_free->evaluateDifferentialCrossSection( 
							     1.0,
							     kn_distribution );
  TEST_EQUALITY( differential_cs, kn_distribution.evaluate( 1.0 )/1e-24 );

  kn_distribution.setEnergy( 20.0 );

  differential_cs = 
    incoherent_cs_evaluator_free->evaluateDifferentialCrossSection( 
							     39.13902672495315,
							     kn_distribution );
  TEST_EQUALITY( differential_cs, 
		 kn_distribution.evaluate( 39.13902672495315 )/1e-24 );

  differential_cs = 
    incoherent_cs_evaluator_free->evaluateDifferentialCrossSection( 
							     1.0,
							     kn_distribution );
  
  TEST_EQUALITY( differential_cs, kn_distribution.evaluate( 1.0 )/1e-24 );
}

//---------------------------------------------------------------------------//
// Check that the differential cross section can be evaluated
TEUCHOS_UNIT_TEST( IncoherentCrossSectionEvaluator,
		   evaluateDifferentialCrossSection_h )
{
  Utility::KleinNishinaDistribution kn_distribution( 0.001 );

  double differential_cs = 
    incoherent_cs_evaluator_h->evaluateDifferentialCrossSection( 
							    1.0039139026724953,
							    kn_distribution );
  
  TEST_FLOATING_EQUALITY( differential_cs, 61.34340692766187, 1e-12 );
		 
  
  differential_cs = 
    incoherent_cs_evaluator_h->evaluateDifferentialCrossSection( 
							     1.0,
							     kn_distribution );

  TEST_EQUALITY_CONST( differential_cs, 0.0 );

  kn_distribution.setEnergy( 20.0 );

  differential_cs = 
    incoherent_cs_evaluator_h->evaluateDifferentialCrossSection( 
							     39.13902672495315,
							     kn_distribution );

  TEST_FLOATING_EQUALITY( differential_cs, 0.000158800282084155253, 1e-15 );

  differential_cs = 
    incoherent_cs_evaluator_h->evaluateDifferentialCrossSection( 
							     1.0,
							     kn_distribution );

  TEST_EQUALITY_CONST( differential_cs, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the differential cross section can be evaluated
TEUCHOS_UNIT_TEST( IncoherentCrossSectionEvaluator,
		   evaluateDifferentialCrossSection_pb )
{
  Utility::KleinNishinaDistribution kn_distribution( 0.001 );

  double differential_cs = 
    incoherent_cs_evaluator_pb->evaluateDifferentialCrossSection( 
							    1.0039139026724953,
							    kn_distribution );
  
  TEST_FLOATING_EQUALITY( differential_cs, 866.3845157219779, 1e-12 );
		 
  
  differential_cs = 
    incoherent_cs_evaluator_pb->evaluateDifferentialCrossSection( 
							     1.0,
							     kn_distribution );

  TEST_EQUALITY_CONST( differential_cs, 0.0 );

  kn_distribution.setEnergy( 20.0 );

  differential_cs = 
    incoherent_cs_evaluator_pb->evaluateDifferentialCrossSection( 
							     39.13902672495315,
							     kn_distribution );

  TEST_FLOATING_EQUALITY( differential_cs, 0.01302162313090073, 1e-15 );

  differential_cs = 
    incoherent_cs_evaluator_pb->evaluateDifferentialCrossSection( 
							     1.0,
							     kn_distribution );

  TEST_EQUALITY_CONST( differential_cs, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the incoherent cross section can be evaluated
TEUCHOS_UNIT_TEST( IncoherentCrossSectionEvaluator, 
		   evaluateCrossSection_free )
{
  double cross_section =
    incoherent_cs_evaluator_free->evaluateCrossSection( 0.001 );

  double expected_cross_section = Utility::KleinNishinaDistribution::evaluateIntegratedKleinNishinaCrossSection( 0.0019569513362476575 )/1e-24;
  
  TEST_FLOATING_EQUALITY( cross_section, expected_cross_section, 1e-8 );

  cross_section =
    incoherent_cs_evaluator_free->evaluateCrossSection( 0.1 );
  
  expected_cross_section = Utility::KleinNishinaDistribution::evaluateIntegratedKleinNishinaCrossSection( 0.19569513362476573 )/1e-24;

  TEST_FLOATING_EQUALITY( cross_section, expected_cross_section, 1e-12 );

  cross_section =
    incoherent_cs_evaluator_free->evaluateCrossSection( 20.0 );
  
  expected_cross_section = Utility::KleinNishinaDistribution::evaluateIntegratedKleinNishinaCrossSection( 39.13902672495315 )/1e-24;
  
  TEST_FLOATING_EQUALITY( cross_section, expected_cross_section, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the incoherent cross section can be evaluated
TEUCHOS_UNIT_TEST( IncoherentCrossSectionEvaluator, 
		   evaluateCrossSection_h )
{
  double cross_section =
    incoherent_cs_evaluator_h->evaluateCrossSection( 0.001 );

  TEST_FLOATING_EQUALITY( cross_section, 
			  incoherent_cs_h->evaluate( 0.001 ),
			  1e-3 );

  cross_section =
    incoherent_cs_evaluator_h->evaluateCrossSection( 0.1 );
  
  TEST_FLOATING_EQUALITY( cross_section, 
			  incoherent_cs_h->evaluate( 0.1 ),
			  1e-3 );

  cross_section =
    incoherent_cs_evaluator_h->evaluateCrossSection( 20.0 );
  
  TEST_FLOATING_EQUALITY( cross_section, 
			  incoherent_cs_h->evaluate( 20.0 ),
			  1e-3 );
}

//---------------------------------------------------------------------------//
// Check that the incoherent cross section can be evaluated
TEUCHOS_UNIT_TEST( IncoherentCrossSectionEvaluator, 
		   evaluateCrossSection_pb )
{
  double cross_section =
    incoherent_cs_evaluator_pb->evaluateCrossSection( 0.001 );

  TEST_FLOATING_EQUALITY( cross_section, 
			  incoherent_cs_pb->evaluate( 0.001 ),
			  1e-3 );

  cross_section =
    incoherent_cs_evaluator_pb->evaluateCrossSection( 0.1, 1e-5 );
  
  TEST_FLOATING_EQUALITY( cross_section, 
			  incoherent_cs_pb->evaluate( 0.1 ),
			  1e-3 );

  cross_section =
    incoherent_cs_evaluator_pb->evaluateCrossSection( 20.0 );
  
  TEST_FLOATING_EQUALITY( cross_section, 
			  incoherent_cs_pb->evaluate( 20.0 ),
			  1e-3 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_h_ace_file_name, test_h_ace_table_name;
  std::string test_pb_ace_file_name, test_pb_ace_table_name;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_h_ace_file",
		 &test_h_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_h_ace_table",
		 &test_h_ace_table_name,
		 "Test ACE table name" );
  clp.setOption( "test_pb_ace_file",
		 &test_pb_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_pb_ace_table",
		 &test_pb_ace_table_name,
		 "Test ACE table name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  {
    // Create the file handler and data extractor for hydrogen
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
			       new Data::ACEFileHandler( test_h_ace_file_name,
							 test_h_ace_table_name,
							 1u ) );

    Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
				new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

    // Create the scattering function
    Teuchos::ArrayView<const double> jince_block = 
      xss_data_extractor->extractJINCEBlock();

    unsigned scatt_func_size = jince_block.size()/2;
    
    Teuchos::Array<double> recoil_momentum( jince_block( 0, scatt_func_size ));
    Teuchos::Array<double> scatt_func_vals( 
			     jince_block( scatt_func_size, scatt_func_size ) );

    for( unsigned i = 0; i < scatt_func_size; ++i )
      recoil_momentum[i] *= 1e8; // convert from inverse Angstrom to inverse cm
    
    if( recoil_momentum.front() == 0.0 )
      recoil_momentum.front() = std::numeric_limits<double>::min();
    
    if( scatt_func_vals.front() == 0.0 )
      scatt_func_vals.front() = std::numeric_limits<double>::min();
    
    Teuchos::RCP<Utility::OneDDistribution> scattering_function(
		   new Utility::TabularDistribution<Utility::LogLog>(
			   recoil_momentum,
			   scatt_func_vals ) );

    incoherent_cs_evaluator_h.reset( 
				new DataGen::IncoherentCrossSectionEvaluator(
						       scattering_function ) );

    // Extract the incoherent cross section
    Teuchos::ArrayView<const double> raw_energy_grid = 
      xss_data_extractor->extractPhotonEnergyGrid();
     
    Teuchos::ArrayView<const double> raw_incoherent_cross_section = 
      xss_data_extractor->extractIncoherentCrossSection();
    
    Teuchos::ArrayView<const double>::iterator start = 
      std::find_if( raw_incoherent_cross_section.begin(),
		    raw_incoherent_cross_section.end(),
		    notEqualZero );

    Teuchos::Array<double> incoherent_cross_section;
    incoherent_cross_section.assign( start, 
				     raw_incoherent_cross_section.end() );
    
    unsigned start_index = std::distance( raw_incoherent_cross_section.begin(),
					  start );

    start = raw_energy_grid.begin();
    
    std::advance( start, start_index );
    
    Teuchos::Array<double> energy_grid;
    energy_grid.assign( start, raw_energy_grid.end() );
    
    // Extract the original energy and cross section values
    for( unsigned i = 0; i < energy_grid.size(); ++i )
    {
      energy_grid[i] = exp( energy_grid[i] );
      incoherent_cross_section[i] = exp( incoherent_cross_section[i] );
    }

    incoherent_cs_h.reset( new Utility::TabularDistribution<Utility::LogLog>(
						  energy_grid,
						  incoherent_cross_section ) );
  }

  {
    // Create the file handler and data extractor for lead
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
			      new Data::ACEFileHandler( test_pb_ace_file_name,
							test_pb_ace_table_name,
							1u ) );

    Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
				new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

    // Create the scattering function
    Teuchos::ArrayView<const double> jince_block = 
      xss_data_extractor->extractJINCEBlock();

    unsigned scatt_func_size = jince_block.size()/2;
    
    Teuchos::Array<double> recoil_momentum( jince_block( 0, scatt_func_size ));
    Teuchos::Array<double> scatt_func_vals( 
			     jince_block( scatt_func_size, scatt_func_size ) );

    for( unsigned i = 0; i < scatt_func_size; ++i )
      recoil_momentum[i] *= 1e8; // convert from inverse Angstrom to inverse cm
    
    if( recoil_momentum.front() == 0.0 )
      recoil_momentum.front() = std::numeric_limits<double>::min();
    
    if( scatt_func_vals.front() == 0.0 )
      scatt_func_vals.front() = std::numeric_limits<double>::min();

    Teuchos::RCP<Utility::OneDDistribution> scattering_function(
		   new Utility::TabularDistribution<Utility::LogLog>(
			   recoil_momentum,
			   scatt_func_vals ) );

    incoherent_cs_evaluator_pb.reset( 
				new DataGen::IncoherentCrossSectionEvaluator(
						       scattering_function ) );

    // Extract the incoherent cross section
    Teuchos::ArrayView<const double> raw_energy_grid = 
      xss_data_extractor->extractPhotonEnergyGrid();
     
    Teuchos::ArrayView<const double> raw_incoherent_cross_section = 
      xss_data_extractor->extractIncoherentCrossSection();
    
    Teuchos::ArrayView<const double>::iterator start = 
      std::find_if( raw_incoherent_cross_section.begin(),
		    raw_incoherent_cross_section.end(),
		    notEqualZero );

    Teuchos::Array<double> incoherent_cross_section;
    incoherent_cross_section.assign( start, 
				     raw_incoherent_cross_section.end() );
    
    unsigned start_index = std::distance( raw_incoherent_cross_section.begin(),
					  start );

    start = raw_energy_grid.begin();
    
    std::advance( start, start_index );
    
    Teuchos::Array<double> energy_grid;
    energy_grid.assign( start, raw_energy_grid.end() );
    
    // Extract the original energy and cross section values
    for( unsigned i = 0; i < energy_grid.size(); ++i )
    {
      energy_grid[i] = exp( energy_grid[i] );
      incoherent_cross_section[i] = exp( incoherent_cross_section[i] );
    }

    incoherent_cs_pb.reset( new Utility::TabularDistribution<Utility::LogLog>(
						  energy_grid,
						  incoherent_cross_section ) );
  }

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
// end tstIncoherentCrossSectionEvaluator.cpp
//---------------------------------------------------------------------------//
