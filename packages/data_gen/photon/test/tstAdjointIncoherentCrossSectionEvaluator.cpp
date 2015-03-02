//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointIncoherentCrossSection.cpp
//! \author Alex Robinson
//! \brief  Adjoint incoherent cross section evaluator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_AdjointIncoherentCrossSectionEvaluator.cpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<DataGen::AdjointIncoherentCrossSectionEvaluator> 
  adjoint_free_cs;

Teuchos::RCP<DataGen::AdjointIncoherentCrossSectionEvaluator>
  adjoint_h_cs;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( AdjointIncoherentCrossSectionEvaluator, 
		   getEnergyOfMaxCrossSection )
{
  double energy = 
    DataGen::AdjointIncoherentCrossSectionEvaluator::getEnergyOfMaxCrossSection( 
								       0.001 );

  TEST_FLOATING_EQUALITY( energy, 0.0009961013562397372, 1e-15 );

  energy = DataGen::AdjointIncoherentCrossSectionEvaluator::getEnergyOfMaxCrossSection( 
								        0.01 );

  TEST_FLOATING_EQUALITY( energy, 0.0096233513926591, 1e-15 );

  energy = DataGen::AdjointIncoherentCrossSectionEvaluator::getEnergyOfMaxCrossSection( 
									 0.1 );

  TEST_FLOATING_EQUALITY( energy, 0.0718705616632476, 1e-15 );

  energy = DataGen::AdjointIncoherentCrossSectionEvaluator::getEnergyOfMaxCrossSection( 
									 1.0 );

  TEST_FLOATING_EQUALITY( energy, 0.20350423413905203, 1e-15 );

  energy = DataGen::AdjointIncoherentCrossSectionEvaluator::getEnergyOfMaxCrossSection( 
									10.0 );

  TEST_FLOATING_EQUALITY( energy, 0.24913409257587504, 1e-15 );

  energy = DataGen::AdjointIncoherentCrossSectionEvaluator::getEnergyOfMaxCrossSection( 
								       100.0 );

  TEST_FLOATING_EQUALITY( energy, 0.25484831899871596, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the energy can be tested for the presence of a max cross section
// value
TEUCHOS_UNIT_TEST( AdjointIncoherentCrossSectionEvaluator,
		   doesEnergyCorrespondToAMaxCrossSectionValue )
{
  TEST_ASSERT( DataGen::AdjointIncoherentCrossSectionEvaluator::doesEnergyCorrespondToAMaxCrossSectionValue( 0.001 ) );

  TEST_ASSERT( DataGen::AdjointIncoherentCrossSectionEvaluator::doesEnergyCorrespondToAMaxCrossSectionValue( 0.255 ) );

  TEST_ASSERT( !DataGen::AdjointIncoherentCrossSectionEvaluator::doesEnergyCorrespondToAMaxCrossSectionValue( 0.255499455065 ) );

  TEST_ASSERT( !DataGen::AdjointIncoherentCrossSectionEvaluator::doesEnergyCorrespondToAMaxCrossSectionValue( 10.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the max energy resulting in a max cross section value at an 
// energy can be returned
TEUCHOS_UNIT_TEST( AdjointIncoherentCrossSectionEvaluator,
		   getMaxEnergyResultingInMaxCrossSectionValueAtEnergy )
{
  double max_energy = DataGen::AdjointIncoherentCrossSectionEvaluator::getMaxEnergyResultingInMaxCrossSectionValueAtEnergy(
								       0.001 );

  TEST_FLOATING_EQUALITY( max_energy, 0.0010039292814978508, 1e-15 );

  max_energy = DataGen::AdjointIncoherentCrossSectionEvaluator::getMaxEnergyResultingInMaxCrossSectionValueAtEnergy(
									0.01 );

  TEST_FLOATING_EQUALITY( max_energy, 0.010407332879714635, 1e-15 );

  max_energy = DataGen::AdjointIncoherentCrossSectionEvaluator::getMaxEnergyResultingInMaxCrossSectionValueAtEnergy(
									 0.1 );

  TEST_FLOATING_EQUALITY( max_energy, 0.16430890703649043, 1e-15 );

  max_energy = DataGen::AdjointIncoherentCrossSectionEvaluator::getMaxEnergyResultingInMaxCrossSectionValueAtEnergy( 
							 0.25227662801581613 );

  TEST_FLOATING_EQUALITY( max_energy, 20.0, 1e-14 );

  max_energy = DataGen::AdjointIncoherentCrossSectionEvaluator::getMaxEnergyResultingInMaxCrossSectionValueAtEnergy(
								       0.255 );

  TEST_FLOATING_EQUALITY( max_energy, 130.44689223759954, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the free electron differential cross section can be evaluated
TEUCHOS_UNIT_TEST( AdjointIncoherentCrossSectionEvaluator,
		   evaluateDifferentialCrossSection_free )
{
  // Evaluate the differential cross section at E = 0.001
  Teuchos::RCP<Utility::AdjointKleinNishinaDistribution> free_distribution(
	     new Utility::AdjointKleinNishinaDistribution( 0.001, 0.001002 ) );
  
  double diff_cross_section = 
    adjoint_free_cs->evaluateDifferentialCrossSection( 0.9980039920159681,
						       *free_distribution );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  1.2752875406768333e-22/1e-24,
				  1e-15 );

  diff_cross_section = 
    adjoint_free_cs->evaluateDifferentialCrossSection( 0.999,
						       *free_distribution );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  1.5796027186150774e-22/1e-24,
				  1e-15 );

  diff_cross_section = 
    adjoint_free_cs->evaluateDifferentialCrossSection( 1.0,
						       *free_distribution );
  
  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section, 
				  2.5495493722278393e-22/1e-24,
				  1e-15 );

  // Evaluate the differential cross section at E = 1.0
  free_distribution.reset(
		   new Utility::AdjointKleinNishinaDistribution( 1.0, 20.0 ) );

  diff_cross_section = 
    adjoint_free_cs->evaluateDifferentialCrossSection( 0.05,
						       *free_distribution );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  2.462197064530928e-24/1e-24,
				  1e-15 );

  diff_cross_section = 
    adjoint_free_cs->evaluateDifferentialCrossSection( 0.5,
						       *free_distribution );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  2.6187454952849134e-25/1e-24,
				  1e-15 );

  diff_cross_section = 
    adjoint_free_cs->evaluateDifferentialCrossSection( 1.0,
						       *free_distribution );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  2.54954937226494e-25/1e-24,
				  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the free electron differential cross section can be evaluated
TEUCHOS_UNIT_TEST( AdjointIncoherentCrossSectionEvaluator,
		   evaluateDifferentialCrossSection_h )
{
  Teuchos::RCP<Utility::AdjointKleinNishinaDistribution> free_distribution(
	     new Utility::AdjointKleinNishinaDistribution( 0.001, 0.001002 ) );
  
  double diff_cross_section = 
    adjoint_h_cs->evaluateDifferentialCrossSection( 0.9980039920159681,
						    *free_distribution );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  1.7166517186844102e-23/1e-24,
				  1e-15 );

  diff_cross_section = 
    adjoint_h_cs->evaluateDifferentialCrossSection( 0.999,
						    *free_distribution );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  1.1113108842743224e-23/1e-24,
				  1e-15 );

  diff_cross_section = 
    adjoint_h_cs->evaluateDifferentialCrossSection( 1.0,
						    *free_distribution );
  
  TEST_EQUALITY_CONST( diff_cross_section, 0.0 );

  // Evaluate the differential cross section at E = 1.0
  free_distribution.reset(
		   new Utility::AdjointKleinNishinaDistribution( 1.0, 20.0 ) );

  diff_cross_section = 
    adjoint_h_cs->evaluateDifferentialCrossSection( 0.05,
						    *free_distribution );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  2.462197064530928e-24/1e-24,
				  1e-15 );

  diff_cross_section = 
    adjoint_h_cs->evaluateDifferentialCrossSection( 0.5,
						    *free_distribution );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  2.6187454952849134e-25/1e-24,
				  1e-15 );

  diff_cross_section = 
    adjoint_h_cs->evaluateDifferentialCrossSection( 1.0,
						    *free_distribution );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
				  0.0,
				  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the free electron cross section can be evaluated
TEUCHOS_UNIT_TEST( AdjointIncoherentCrossSectionEvaluator, 
		   evaluateCrossSection_free )
{
  double cross_section = adjoint_free_cs->evaluateCrossSection( 0.001, 
								0.001,
								1e-6 );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = adjoint_free_cs->evaluateCrossSection( 0.001, 
							 0.001002,
							 1e-6 );
  
  Teuchos::RCP<Utility::AdjointKleinNishinaDistribution> 
    distribution( new Utility::AdjointKleinNishinaDistribution( 0.001,
								0.001002 ) );
  
  UTILITY_TEST_FLOATING_EQUALITY( 
			  cross_section,
			  distribution->evaluateIntegratedCrossSection()/1e-24,
			  1e-8 );

  cross_section = adjoint_free_cs->evaluateCrossSection( 
						       0.001, 
						       0.0010039292814978508,
						       1e-6 );
  
  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 
						     0.001,
						     0.0010039292814978508 ) );

  UTILITY_TEST_FLOATING_EQUALITY( 
			  cross_section, 
			  distribution->evaluateIntegratedCrossSection()/1e-24,
			  1e-9 );

  // Note: The cross section won't change once the peak has been reached for
  //       this energy
  cross_section = adjoint_free_cs->evaluateCrossSection( 0.001, 
							 0.002,
							 1e-6 );
  
  UTILITY_TEST_FLOATING_EQUALITY( 
			  cross_section,
			  distribution->evaluateIntegratedCrossSection()/1e-24,
			  1e-9 );

  cross_section = adjoint_free_cs->evaluateCrossSection( 0.001, 
							 20.0,
							 1e-6 );
  
  UTILITY_TEST_FLOATING_EQUALITY( 
			  cross_section,
			  distribution->evaluateIntegratedCrossSection()/1e-24,
			  1e-9 );

  // Set a new energy
  cross_section = adjoint_free_cs->evaluateCrossSection( 0.01, 
							 0.01,
							 1e-6 );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = adjoint_free_cs->evaluateCrossSection( 0.01, 
							 0.0103,
							 1e-6 );

  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 0.01,
						                    0.0103 ) );

  UTILITY_TEST_FLOATING_EQUALITY( 
			  cross_section,
			  distribution->evaluateIntegratedCrossSection()/1e-24,
			  1e-11 );

  cross_section = adjoint_free_cs->evaluateCrossSection( 
							0.01, 
							0.010407332879714635,
							1e-6 );

  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 
						      0.01,
						      0.010407332879714635 ) );

  UTILITY_TEST_FLOATING_EQUALITY( 
			  cross_section,
			  distribution->evaluateIntegratedCrossSection()/1e-24,
			  1e-12 );

  cross_section = adjoint_free_cs->evaluateCrossSection( 0.01, 
							 20.0,
							 1e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( 
			  cross_section,
			  distribution->evaluateIntegratedCrossSection()/1e-24,
			  1e-12 );

  // Set a new energy
  cross_section = adjoint_free_cs->evaluateCrossSection( 0.25227662801581613,
							 0.25227662801581613,
							 1e-6 );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );
  
  cross_section = adjoint_free_cs->evaluateCrossSection( 0.25227662801581613,
							 10.0,
							 1e-6 );
  
  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 
							   0.25227662801581613,
							   10.0 ) );

  UTILITY_TEST_FLOATING_EQUALITY( 
			  cross_section, 
			  distribution->evaluateIntegratedCrossSection()/1e-24,
			  1e-14 );
  
  cross_section = adjoint_free_cs->evaluateCrossSection( 0.25227662801581613,
							 20.0,
							 1e-6 );
  
  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 
							   0.25227662801581613,
							   20.0 ) );

  UTILITY_TEST_FLOATING_EQUALITY( 
			  cross_section, 
			  distribution->evaluateIntegratedCrossSection()/1e-24,
			  1e-14 );

  cross_section = adjoint_free_cs->evaluateCrossSection( 0.25227662801581613,
							 100.0,
							 1e-6 );
  
  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 
							   0.25227662801581613,
							   100.0 ) );

  UTILITY_TEST_FLOATING_EQUALITY( 
			  cross_section, 
			  distribution->evaluateIntegratedCrossSection()/1e-24,
			  1e-14 );

  // Set a new energy
  cross_section = adjoint_free_cs->evaluateCrossSection( 10.0, 
							 10.0,
							 1e-6 );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = adjoint_free_cs->evaluateCrossSection( 10.0, 
							 20.0,
							 1e-6 );
  
  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 10.0,
								    20.0 ) );

  UTILITY_TEST_FLOATING_EQUALITY( 
			  cross_section, 
			  distribution->evaluateIntegratedCrossSection()/1e-24,
			  1e-15 );

  cross_section = adjoint_free_cs->evaluateCrossSection( 10.0, 
							 100.0,
							 1e-6 );
  
  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 10.0,
								    100.0 ) );

  UTILITY_TEST_FLOATING_EQUALITY( 
			  cross_section, 
			  distribution->evaluateIntegratedCrossSection()/1e-24,
			  1e-14 );

  cross_section = adjoint_free_cs->evaluateCrossSection( 10.0, 
							 1000.0,
							 1e-6 );
  
  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 10.0,
								    1000.0 ) );

  UTILITY_TEST_FLOATING_EQUALITY( 
			  cross_section, 
			  distribution->evaluateIntegratedCrossSection()/1e-24,
			  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint cross section can be evaluated
TEUCHOS_UNIT_TEST( AdjointIncoherentCrossSectionEvaluator,
		   evaluateCrossSection_h )
{
  double cross_section = adjoint_h_cs->evaluateCrossSection( 0.001, 0.001 );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = adjoint_h_cs->evaluateCrossSection( 0.001, 0.001002, 1e-4 );
  
  Teuchos::RCP<Utility::AdjointKleinNishinaDistribution> 
    distribution( new Utility::AdjointKleinNishinaDistribution( 0.001,
  								0.001002 ) );
  
  TEST_ASSERT( cross_section < 
	       distribution->evaluateIntegratedCrossSection()/1e-24 );
  
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
				  2.05061392743816141e-26/1e-24,
  				  1e-15 );

  cross_section = adjoint_h_cs->evaluateCrossSection( 0.001, 
  						      0.0010039292814978508,
  						      1e-4 );
  
  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 
  						     0.001,
  						     0.0010039292814978508 ) );

  TEST_ASSERT( cross_section < 
	       distribution->evaluateIntegratedCrossSection()/1e-24 );
  
  UTILITY_TEST_FLOATING_EQUALITY( cross_section, 
				  8.52311999219016714e-26/1e-24,
  				  1e-15 );

  // Note: The cross section won't change once the peak has been reached for
  //       this energy
  cross_section = adjoint_h_cs->evaluateCrossSection( 0.001, 0.002, 1e-4 );
  
  TEST_ASSERT( cross_section < 
	       distribution->evaluateIntegratedCrossSection()/1e-24 );
  
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
				  8.52311999219016714e-26/1e-24,
  				  1e-15 );

  cross_section = adjoint_h_cs->evaluateCrossSection( 0.001, 20.0, 1e-4 );
  
  TEST_ASSERT( cross_section < 
	       distribution->evaluateIntegratedCrossSection()/1e-24 );
  
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
				  8.52311999219016714e-26/1e-24,
  				  1e-15 );

    // Set a new energy
  cross_section = adjoint_h_cs->evaluateCrossSection( 0.01, 0.01 );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = adjoint_h_cs->evaluateCrossSection( 0.01, 0.0103, 1e-4 );
  
  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 0.01,
  						                    0.0103 ) );
  TEST_ASSERT( cross_section < 
	       distribution->evaluateIntegratedCrossSection()/1e-24 );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
				  4.23357639660378708e-25/1e-24,
  				  1e-15 );

  cross_section = adjoint_h_cs->evaluateCrossSection( 0.01, 
  						      0.010407332879714635,
  						      1e-4 );
  
  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 
  						      0.01,
  						      0.010407332879714635 ) );
  
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
				  6.24561487820609666e-25/1e-24,
  				  1e-15 );

  cross_section = adjoint_h_cs->evaluateCrossSection( 0.01, 20.0, 1e-4 );
  
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
				  6.24561487820609666e-25/1e-24,
  				  1e-12 );

  // Set a new energy
  cross_section = adjoint_h_cs->evaluateCrossSection( 0.25227662801581613,
  						      0.25227662801581613 );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );
  
  cross_section = adjoint_h_cs->evaluateCrossSection( 0.25227662801581613,
  						      10.0 );
  
  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 
  							   0.25227662801581613,
  							   10.0 ) );
  
  TEST_ASSERT( cross_section < 
	       distribution->evaluateIntegratedCrossSection()/1e-24 );
  
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
				  1.7793996774557439e-24/1e-24,
  				  1e-15 );
  
  cross_section = adjoint_h_cs->evaluateCrossSection( 0.25227662801581613,
  						      20.0 );
  
  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 
  							   0.25227662801581613,
  							   20.0 ) );

  TEST_ASSERT( cross_section < 
	       distribution->evaluateIntegratedCrossSection()/1e-24 );
  
  UTILITY_TEST_FLOATING_EQUALITY( cross_section, 
				  2.12961181703444872e-24/1e-24,
  				  1e-15 );

  cross_section = adjoint_h_cs->evaluateCrossSection( 0.25227662801581613,
  						      100.0 );
  
  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 
  							   0.25227662801581613,
  							   100.0 ) );

  TEST_ASSERT( cross_section < 
	       distribution->evaluateIntegratedCrossSection()/1e-24 );
  
  UTILITY_TEST_FLOATING_EQUALITY( cross_section, 
				  2.12961181703444872e-24/1e-24,
  				  1e-15 );

  // Set a new energy
  cross_section = adjoint_h_cs->evaluateCrossSection( 10.0, 10.0 );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = adjoint_h_cs->evaluateCrossSection( 10.0, 20.0 );
  
  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 10.0,
  								    20.0 ) );

  UTILITY_TEST_FLOATING_EQUALITY( 
			  cross_section, 
  			  distribution->evaluateIntegratedCrossSection()/1e-24,
			  1e-15 );

  cross_section = adjoint_h_cs->evaluateCrossSection( 10.0, 100.0 );
  
  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 10.0,
  								    100.0 ) );

  UTILITY_TEST_FLOATING_EQUALITY( 
			  cross_section, 
  			  distribution->evaluateIntegratedCrossSection()/1e-24,
			  1e-14 );

  cross_section = adjoint_h_cs->evaluateCrossSection( 10.0, 1000.0 );
  
  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 10.0,
  								    1000.0 ) );

  UTILITY_TEST_FLOATING_EQUALITY( 
			  cross_section, 
  			  distribution->evaluateIntegratedCrossSection()/1e-24,
			  1e-12 );
}


//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_ace_file_name, test_ace_table_name;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_ace_file",
		 &test_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_ace_table",
		 &test_ace_table_name,
		 "Test ACE table name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Initialize the free electron adjoint cross section evaluator
  adjoint_free_cs.reset(
		       new DataGen::AdjointIncoherentCrossSectionEvaluator() );

  // Create a file handler and data extractor
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
				 new Data::ACEFileHandler( test_ace_file_name,
							   test_ace_table_name,
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

  Teuchos::Array<double> recoil_momentum( jince_block( 0, scatt_func_size ) );
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

  // Initialize the hydrogen adjoint cross section evaluator
  adjoint_h_cs.reset( new DataGen::AdjointIncoherentCrossSectionEvaluator(
						       scattering_function ) );

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
// end tstAdjointIncoherentCrossSectionEvaluator.cpp
//---------------------------------------------------------------------------//
