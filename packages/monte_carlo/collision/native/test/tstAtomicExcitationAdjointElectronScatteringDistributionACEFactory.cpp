//---------------------------------------------------------------------------//
//!
//! \file   tstAtomicExcitationAdjointElectronScatteringDistributionACEFactory.cpp
//! \author Luke Kersting
//! \brief  Atomic Excitation scattering distribution ACE factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor;
Teuchos::RCP<const MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution>
   distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the sample() function
TEUCHOS_UNIT_TEST( AtomicExcitationAdjointElectronScatteringDistributionACEFactory,
                   sample )
{
  MonteCarlo::AtomicExcitationAdjointElectronScatteringDistributionACEFactory::createAtomicExcitationAdjointDistribution(
                                                 *xss_data_extractor,
                                                 distribution );

  double incoming_energy = 1.000000000000e-03 - 9.32298000000E-06;
  double outgoing_energy,scattering_angle_cosine;

  // sample distribution
  distribution->sample( incoming_energy,
                        outgoing_energy,
                        scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( outgoing_energy,
                          1.000000000000e-03,
                          1e-12 );
  TEST_EQUALITY_CONST( scattering_angle_cosine, 1.0 );

}

//---------------------------------------------------------------------------//
// Check that the sampleAndRecordTrials() function
TEUCHOS_UNIT_TEST( AtomicExcitationAdjointElectronScatteringDistributionACEFactory,
                   sampleAndRecordTrials )
{
  MonteCarlo::AtomicExcitationAdjointElectronScatteringDistributionACEFactory::createAtomicExcitationAdjointDistribution(
                                                 *xss_data_extractor,
                                                 distribution );

  unsigned trials = 10;
  double incoming_energy = 1.000000000000e-03 - 9.32298000000E-06;
  double outgoing_energy,scattering_angle_cosine;

  // sample distribution
  distribution->sampleAndRecordTrials( incoming_energy,
                                       outgoing_energy,
                                       scattering_angle_cosine,
                                       trials );

  // Test
  TEST_FLOATING_EQUALITY( outgoing_energy,
                          1.000000000000e-03,
                          1e-12 );
  TEST_EQUALITY_CONST( scattering_angle_cosine, 1.0 );
  TEST_EQUALITY_CONST( trials, 11 );

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

  // Create a file handler and data extractor
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
				 new Data::ACEFileHandler( test_ace_file_name,
							   test_ace_table_name,
							   1u ) );
  xss_data_extractor.reset( new Data::XSSEPRDataExtractor(
				      ace_file_handler->getTableNXSArray(),
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
// end tstAtomicExcitationAdjointElectronScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
