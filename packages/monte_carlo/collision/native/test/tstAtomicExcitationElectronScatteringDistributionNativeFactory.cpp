//---------------------------------------------------------------------------//
//!
//! \file   tstAtomicExcitationElectronScatteringDistributionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  Atomic Excitation scattering distribution Native factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationElectronScatteringDistributionNativeFactory.hpp"
#include "Data_EvaluatedElectronDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::EvaluatedElectronDataContainer> data_container;
Teuchos::RCP<const MonteCarlo::AtomicExcitationElectronScatteringDistribution> 
   distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the sample() function
TEUCHOS_UNIT_TEST( AtomicExcitationElectronScatteringDistributionNativeFactory, 
                   sample )
{
  MonteCarlo::AtomicExcitationElectronScatteringDistributionNativeFactory::createAtomicExcitationDistribution(
                                                 *data_container,
                                                 distribution );

  double incoming_energy = 1.000000000000e-03;
  double outgoing_energy,scattering_angle_cosine;

  // sample distribution
  distribution->sample( incoming_energy,
                        outgoing_energy,
                        scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( outgoing_energy, 
                          1.000000000000e-03- 9.32298000000E-06, 
                          1e-12 );
  TEST_EQUALITY_CONST( scattering_angle_cosine, 1.0 );

}

//---------------------------------------------------------------------------//
// Check that the sampleAndRecordTrials() function
TEUCHOS_UNIT_TEST( AtomicExcitationElectronScatteringDistributionNativeFactory, 
                   sampleAndRecordTrials )
{
  MonteCarlo::AtomicExcitationElectronScatteringDistributionNativeFactory::createAtomicExcitationDistribution(
                                                 *data_container,
                                                 distribution );

  unsigned trials = 10;
  double incoming_energy = 1.000000000000e-03;
  double outgoing_energy,scattering_angle_cosine;

  // sample distribution
  distribution->sampleAndRecordTrials( incoming_energy,
                                       outgoing_energy,
                                       scattering_angle_cosine,
                                       trials );

  // Test
  TEST_FLOATING_EQUALITY( outgoing_energy, 
                          1.000000000000e-03- 9.32298000000E-06, 
                          1e-12 );
  TEST_EQUALITY_CONST( scattering_angle_cosine, 1.0 );
  TEST_EQUALITY_CONST( trials, 11 ); 

}


//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_native_file_name;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_native_file",
		 &test_native_file_name,
		 "Test Native file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  // Create the native data file container
  data_container.reset( new Data::EvaluatedElectronDataContainer( 
						     test_native_file_name ) );
 
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
// end tstAtomicExcitationElectronScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
