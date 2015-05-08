//---------------------------------------------------------------------------//
//!
//! \file   tstCoherentScatteringDistributionACEFactory.cpp
//! \author Alex Robinson
//! \brief  Coherent scattering distribution ACE factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_CoherentScatteringDistributionACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor;
Teuchos::RCP<const MonteCarlo::CoherentScatteringDistribution> distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a Thompson distribution can be created
TEUCHOS_UNIT_TEST( CoherentScatteringDistributionACEFactory, 
		   createThompsonDistribution )
{
  MonteCarlo::CoherentScatteringDistributionACEFactory::createThompsonDistribution(
							        distribution );

  // Test distribution properties
  double dist_value = distribution->evaluate( 0.1, 1.0 );

  TEST_FLOATING_EQUALITY( dist_value, 4.989344050883251e-1, 1e-15 );

  dist_value = distribution->evaluate( 0.1, 0.0 );

  TEST_FLOATING_EQUALITY( dist_value, 2.4946720254416256e-1, 1e-15 );

  dist_value = distribution->evaluate( 0.1, -1.0 );

  TEST_FLOATING_EQUALITY( dist_value, 4.989344050883251e-1, 1e-15 );

  double outgoing_energy, scattering_angle_cosine;
  MonteCarlo::SubshellType shell_of_interaction;

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.75;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Sample 1st term
  distribution->sample( 0.1,
			outgoing_energy,
			scattering_angle_cosine,
			shell_of_interaction );

  TEST_EQUALITY_CONST( outgoing_energy, 0.1 );
  UTILITY_TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.0, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::UNKNOWN_SUBSHELL );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a basic coherent distribution can be created
TEUCHOS_UNIT_TEST( CoherentScatteringDistributionACEFactory, 
		   createBasicCoherentDistribution )
{
  MonteCarlo::CoherentScatteringDistributionACEFactory::createBasicCoherentDistribution(
							   *xss_data_extractor,
							   distribution );
  
  // Test distribution properties
  double dist_value = distribution->evaluate( 0.1, 1.0 );

  TEST_FLOATING_EQUALITY( dist_value, 3.354834939813898e3, 1e-15 );
  
  dist_value = distribution->evaluate( 0.1, 0.0 );
  
  TEST_FLOATING_EQUALITY( dist_value, 4.17273487105470142, 1e-15 );
  
  dist_value = distribution->evaluate( 0.1, -1.0 );
  
  TEST_FLOATING_EQUALITY( dist_value, 3.59244179705391486, 1e-15 );

  double outgoing_energy, scattering_angle_cosine;
  MonteCarlo::SubshellType shell_of_interaction;
  
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.75;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.003; // reject
  fake_stream[3] = 0.7;
  fake_stream[4] = 0.8;
  fake_stream[5] = 0.006; 

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sample( 0.1,
			outgoing_energy,
			scattering_angle_cosine,
			shell_of_interaction );
  
  TEST_EQUALITY_CONST( outgoing_energy, 0.1 );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.6, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::UNKNOWN_SUBSHELL );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that an efficient coherent distribution can be created
TEUCHOS_UNIT_TEST( CoherentScatteringDistributionACEFactory,
		   createEfficientCoherentDistribution )
{
  MonteCarlo::CoherentScatteringDistributionACEFactory::createEfficientCoherentDistribution(
							   *xss_data_extractor,
							   distribution );

  // Test distribution properties
  double outgoing_energy, scattering_angle_cosine;
  MonteCarlo::SubshellType shell_of_interaction;

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.942; // reject
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.941;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sample( 0.1,
			outgoing_energy,
			scattering_angle_cosine,
			shell_of_interaction );
  
  TEST_EQUALITY_CONST( outgoing_energy, 0.1 );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.940007827406442842, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::UNKNOWN_SUBSHELL );

  Utility::RandomNumberGenerator::unsetFakeStream();
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
  
  {
    // Create a file handler and data extractor
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler( 
				 new Data::ACEFileHandler( test_ace_file_name,
							   test_ace_table_name,
							   1u ) );
    xss_data_extractor.reset( new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
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
// end tstCoherentScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
