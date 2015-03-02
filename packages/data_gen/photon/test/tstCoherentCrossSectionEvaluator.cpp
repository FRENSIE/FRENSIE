//---------------------------------------------------------------------------//
//!
//! \file   tstCoherentCrossSectionEvaluator.cpp
//! \author Alex Robinson
//! \brief  Coherent cross section evaluator unit tests
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
#include "DataGen_CoherentCrossSectionEvaluator.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_KleinNishinaDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
Teuchos::RCP<DataGen::CoherentCrossSectionEvaluator>
  coherent_cs_evaluator_free( new DataGen::CoherentCrossSectionEvaluator() );

Teuchos::RCP<DataGen::CoherentCrossSectionEvaluator>
  coherent_cs_evaluator_h;

Teuchos::RCP<DataGen::CoherentCrossSectionEvaluator>
  coherent_cs_evaluator_pb;

Teuchos::RCP<Utility::OneDDistribution> coherent_cs_h;
Teuchos::RCP<Utility::OneDDistribution> coherent_cs_pb;

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
TEUCHOS_UNIT_TEST( CoherentCrossSectionEvaluator,
		   evaluateDifferentialCrossSection_free )
{
  double differential_cs = 
    coherent_cs_evaluator_free->evaluateDifferentialCrossSection( 0.001, -1.0);

  TEST_FLOATING_EQUALITY( differential_cs, 0.49893440508832515, 1e-15 );

  differential_cs = 
    coherent_cs_evaluator_free->evaluateDifferentialCrossSection( 0.001, 0.0 );

  TEST_FLOATING_EQUALITY( differential_cs, 0.24946720254416258, 1e-15 );

  differential_cs = 
    coherent_cs_evaluator_free->evaluateDifferentialCrossSection( 0.001, 1.0);

  TEST_FLOATING_EQUALITY( differential_cs, 0.49893440508832515, 1e-15 );
  
  differential_cs = 
    coherent_cs_evaluator_free->evaluateDifferentialCrossSection( 20.0, -1.0);

  TEST_FLOATING_EQUALITY( differential_cs, 0.49893440508832515, 1e-15 );

  differential_cs = 
    coherent_cs_evaluator_free->evaluateDifferentialCrossSection( 20.0, 0.0 );

  TEST_FLOATING_EQUALITY( differential_cs, 0.24946720254416258, 1e-15 );

  differential_cs = 
    coherent_cs_evaluator_free->evaluateDifferentialCrossSection( 20.0, 1.0);

  TEST_FLOATING_EQUALITY( differential_cs, 0.49893440508832515, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the differential cross section can be evaluated
TEUCHOS_UNIT_TEST( CoherentCrossSectionEvaluator,
		   evaluateDifferentialCrossSection_h )
{
  double differential_cs = 
    coherent_cs_evaluator_h->evaluateDifferentialCrossSection( 0.001, -1.0);

  TEST_FLOATING_EQUALITY( differential_cs, 0.37776702264104, 1e-15 );

  differential_cs = 
    coherent_cs_evaluator_h->evaluateDifferentialCrossSection( 0.001, 0.0 );

  TEST_FLOATING_EQUALITY( differential_cs, 0.21637982713639206, 1e-15 );

  differential_cs = 
    coherent_cs_evaluator_h->evaluateDifferentialCrossSection( 0.001, 1.0);

  TEST_FLOATING_EQUALITY( differential_cs, 0.49893440508832515, 1e-15 );

  differential_cs = 
    coherent_cs_evaluator_h->evaluateDifferentialCrossSection( 20.0, -1.0);

  UTILITY_TEST_FLOATING_EQUALITY( differential_cs, 
				  7.286996029226393e-31, 
				  1e-12 );

  differential_cs = 
    coherent_cs_evaluator_h->evaluateDifferentialCrossSection( 20.0, 0.0 );

  UTILITY_TEST_FLOATING_EQUALITY( differential_cs, 
				  5.829596823381159e-30, 
				  1e-12 );

  differential_cs = 
    coherent_cs_evaluator_h->evaluateDifferentialCrossSection( 20.0, 1.0);

  TEST_FLOATING_EQUALITY( differential_cs, 0.49893440508832515, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the differential cross section can be evaluated
TEUCHOS_UNIT_TEST( CoherentCrossSectionEvaluator,
		   evaluateDifferentialCrossSection_pb )
{
  double differential_cs = 
    coherent_cs_evaluator_pb->evaluateDifferentialCrossSection( 0.001, -1.0);

  TEST_FLOATING_EQUALITY( differential_cs, 3090.054576298241, 1e-15 );

  differential_cs = 
    coherent_cs_evaluator_pb->evaluateDifferentialCrossSection( 0.001, 0.0 );

  TEST_FLOATING_EQUALITY( differential_cs, 1606.0268828371622, 1e-15 );

  differential_cs = 
    coherent_cs_evaluator_pb->evaluateDifferentialCrossSection( 0.001, 1.0);

  TEST_FLOATING_EQUALITY( differential_cs, 3354.8349398138985, 1e-15 );

  differential_cs = 
    coherent_cs_evaluator_pb->evaluateDifferentialCrossSection( 20.0, -1.0);

  UTILITY_TEST_FLOATING_EQUALITY( differential_cs, 
				  9.70510197423921e-11, 
				  1e-12 );

  differential_cs = 
    coherent_cs_evaluator_pb->evaluateDifferentialCrossSection( 20.0, 0.0 );

  UTILITY_TEST_FLOATING_EQUALITY( differential_cs, 
				  3.1070773170285094e-10, 
				  1e-12 );

  differential_cs = 
    coherent_cs_evaluator_pb->evaluateDifferentialCrossSection( 20.0, 1.0 );

  TEST_FLOATING_EQUALITY( differential_cs, 3354.8349398138985, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be evaluated
TEUCHOS_UNIT_TEST( CoherentCrossSectionEvaluator, evaluateCrossSection_free )
{
  double cross_section = 
    coherent_cs_evaluator_free->evaluateCrossSection( 0.001 );

  TEST_FLOATING_EQUALITY( cross_section, 0.6652458734511002, 1e-15 );

  cross_section = coherent_cs_evaluator_free->evaluateCrossSection( 0.1 );
    
  TEST_FLOATING_EQUALITY( cross_section, 0.6652458734511002, 1e-15 );

  cross_section = coherent_cs_evaluator_free->evaluateCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 0.6652458734511002, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be evaluated
TEUCHOS_UNIT_TEST( CoherentCrossSectionEvaluator, evaluateCrossSection_h )
{
  double cross_section = 
    coherent_cs_evaluator_h->evaluateCrossSection( 0.001, 1e-5 );

  TEST_FLOATING_EQUALITY( cross_section, 
			  coherent_cs_h->evaluate( 0.001 ), 
			  1e-2 );

  cross_section = coherent_cs_evaluator_h->evaluateCrossSection( 0.1, 1e-3 );
    
  TEST_FLOATING_EQUALITY( cross_section, 
			  coherent_cs_h->evaluate( 0.1 ), 
			  1e-3 );

  cross_section = coherent_cs_evaluator_h->evaluateCrossSection( 20.0, 1e-4 );

  TEST_FLOATING_EQUALITY( cross_section, 
			  coherent_cs_h->evaluate( 20.0 ),
			  1e-2 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be evaluated
TEUCHOS_UNIT_TEST( CoherentCrossSectionEvaluator, evaluateCrossSection_pb )
{
  double cross_section = 
    coherent_cs_evaluator_pb->evaluateCrossSection( 0.001, 1e-5 );
  
  TEST_FLOATING_EQUALITY( cross_section, 4287.68938804728168, 1e-15 );

  cross_section = coherent_cs_evaluator_pb->evaluateCrossSection( 0.1, 1e-4 );
    
  TEST_FLOATING_EQUALITY( cross_section, 
			  coherent_cs_pb->evaluate( 0.1 ), 
			  0.05 );

  cross_section = coherent_cs_evaluator_pb->evaluateCrossSection( 20.0, 1e-4 );

  TEST_FLOATING_EQUALITY( cross_section, 
			  coherent_cs_pb->evaluate( 20.0 ),
			  1e-2 );
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

    // Extract the form factor
    Teuchos::ArrayView<const double>  jcohe_block = 
      xss_data_extractor->extractJCOHEBlock();
    
    unsigned form_factor_size = jcohe_block.size()/3;

    Teuchos::Array<double> recoil_momentum(jcohe_block( 0, form_factor_size ));

    Teuchos::Array<double> form_factor(
                         jcohe_block( 2*form_factor_size, form_factor_size ) );

    // convert from inverse A to inverse cm
    for( unsigned i = 0; i < form_factor_size; ++i )
    {
      recoil_momentum[i] *= 1e8; 
      
      if( recoil_momentum[i] == 0.0 )
	recoil_momentum[i] = std::numeric_limits<double>::min();

      if( form_factor[i] == 0.0 )
	form_factor[i] = std::numeric_limits<double>::min();
    }
    
    Teuchos::RCP<Utility::OneDDistribution> form_factor_dist(
                             new Utility::TabularDistribution<Utility::LogLog>(
                                                               recoil_momentum,
							       form_factor ) );

    coherent_cs_evaluator_h.reset( 
	      new DataGen::CoherentCrossSectionEvaluator( form_factor_dist ) );

    // Extract the coherent cross section
    Teuchos::ArrayView<const double> raw_energy_grid = 
      xss_data_extractor->extractPhotonEnergyGrid();

    Teuchos::ArrayView<const double> raw_coherent_cross_section = 
      xss_data_extractor->extractCoherentCrossSection();
    
    Teuchos::ArrayView<const double>::iterator start = 
      std::find_if( raw_coherent_cross_section.begin(),
		    raw_coherent_cross_section.end(),
		    notEqualZero );

    Teuchos::Array<double> coherent_cross_section;
    coherent_cross_section.assign( start, raw_coherent_cross_section.end() );
    
    unsigned start_index = std::distance( raw_coherent_cross_section.begin(),
					  start );
    
    start = raw_energy_grid.begin();

    std::advance( start, start_index );

    Teuchos::Array<double> energy_grid;
    energy_grid.assign( start, raw_energy_grid.end() );
    
    // Extract the original energy and cross section values
    for( unsigned i = 0; i < energy_grid.size(); ++i )
    {
      energy_grid[i] = exp( energy_grid[i] );
      coherent_cross_section[i] = exp( coherent_cross_section[i] );
    }
    
    coherent_cs_h.reset( new Utility::TabularDistribution<Utility::LogLog>(
						    energy_grid,
						    coherent_cross_section ) );
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

    // Extract the form factor
    Teuchos::ArrayView<const double>  jcohe_block = 
      xss_data_extractor->extractJCOHEBlock();
    
    unsigned form_factor_size = jcohe_block.size()/3;

    Teuchos::Array<double> recoil_momentum(jcohe_block( 0, form_factor_size ));

    Teuchos::Array<double> form_factor(
                         jcohe_block( 2*form_factor_size, form_factor_size ) );

    // convert from inverse A to inverse cm
    for( unsigned i = 0; i < form_factor_size; ++i )
    {
      recoil_momentum[i] *= 1e8; 
      
      if( recoil_momentum[i] == 0.0 )
	recoil_momentum[i] = std::numeric_limits<double>::min();

      if( form_factor[i] == 0.0 )
	form_factor[i] = std::numeric_limits<double>::min();

      std::cout << recoil_momentum[i] << " " << form_factor[i] << std::endl;
    }
  
    Teuchos::RCP<Utility::OneDDistribution> form_factor_dist(
                             new Utility::TabularDistribution<Utility::LogLog>(
                                                               recoil_momentum,
							       form_factor ) );

    coherent_cs_evaluator_pb.reset( 
	      new DataGen::CoherentCrossSectionEvaluator( form_factor_dist ) );

    // Extract the coherent cross section
    Teuchos::ArrayView<const double> raw_energy_grid = 
      xss_data_extractor->extractPhotonEnergyGrid();

    Teuchos::ArrayView<const double> raw_coherent_cross_section = 
      xss_data_extractor->extractCoherentCrossSection();

    Teuchos::ArrayView<const double>::iterator start = 
      std::find_if( raw_coherent_cross_section.begin(),
		    raw_coherent_cross_section.end(),
		    notEqualZero );

    Teuchos::Array<double> coherent_cross_section;
    coherent_cross_section.assign( start, raw_coherent_cross_section.end() );

    unsigned start_index = std::distance( raw_coherent_cross_section.begin(),
					  start );

    start = raw_energy_grid.begin();

    std::advance( start, start_index );

    Teuchos::Array<double> energy_grid;
    energy_grid.assign( start, raw_energy_grid.end() );
    
    // Extract the original energy and cross section values
    for( unsigned i = 0; i < energy_grid.size(); ++i )
    {
      energy_grid[i] = exp( energy_grid[i] );
      coherent_cross_section[i] = exp( coherent_cross_section[i] );
    }

    coherent_cs_pb.reset( new Utility::TabularDistribution<Utility::LogLog>(
						    energy_grid,
						    coherent_cross_section ) );
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
// end tstCoherentCrossSectionEvaluator.cpp
//---------------------------------------------------------------------------//
