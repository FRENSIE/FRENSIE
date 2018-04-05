//---------------------------------------------------------------------------//
//!
//! \file   tstDelayedNeutronEmissionDistribution.cpp
//! \author Alex Robinson
//! \brief  Delayed neutron emission distribution factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_DelayedNeutronEmissionDistributionACEFactory.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
Teuchos::RCP<MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState> > distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the delayed neutron can be emitted correcly
TEUCHOS_UNIT_TEST( DelayedNeutronEmissionDistribution, scatterNeutron )
{
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.20; // select 3rd precursor group
  fake_stream[1] = 0.5; // sample emission time of 5.978622815721089
  fake_stream[2] = 0.1;
  fake_stream[3] = 0.6;
  fake_stream[4] = 0.7;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::NeutronState neutron( 1ull );
  neutron.setEnergy( 1.0 );
  neutron.setTime( 0.0 );
  neutron.setDirection( 0.0, 0.0, 1.0 );

  distribution->scatterParticle( neutron, 1.0 );

  TEST_FLOATING_EQUALITY( neutron.getTime(), 5.978622815721089, 1e-15 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  std::string test_u238_ace_file_name;
  std::string test_u238_ace_table_name;

  clp.setOption( "test_u238_ace_file",
		 &test_u238_ace_file_name,
		 "Test U238 ACE file name" );
  clp.setOption( "test_u238_ace_table",
		 &test_u238_ace_table_name,
		 "Test U238 ACE table name in basic ACE file" );

  const Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return =
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  // Initialize ace file handler, data extractor and multiplicity factory
  Teuchos::RCP<Data::ACEFileHandler>
  ace_file_handler( new Data::ACEFileHandler( test_u238_ace_file_name,
					      test_u238_ace_table_name,
					      1u ) );

  Teuchos::RCP<Data::XSSNeutronDataExtractor>
  xss_data_extractor(
   new Data::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

  Teuchos::RCP<MonteCarlo::DelayedNeutronEmissionDistributionACEFactory>
    factory( new MonteCarlo::DelayedNeutronEmissionDistributionACEFactory(
				 ace_file_handler->getTableName(),
				 ace_file_handler->getTableAtomicWeightRatio(),
				 xss_data_extractor->extractBDDBlock(),
				 xss_data_extractor->extractDNEDLBlock(),
				 xss_data_extractor->extractDNEDBlock() ) );

  factory->createEmissionDistribution( distribution );

  ace_file_handler.reset();
  xss_data_extractor.reset();
  factory.reset();

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
// end tstDelayedNeutronEmissionDistribution.cpp
//---------------------------------------------------------------------------//
