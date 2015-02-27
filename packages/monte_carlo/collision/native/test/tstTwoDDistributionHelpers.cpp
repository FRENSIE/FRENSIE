//---------------------------------------------------------------------------//
//!
//! \file   tstTwoDDistributionHelpers.cpp
//! \author Luke Kersting
//! \brief  Coherent photon scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_TwoDDistributionHelpers.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variable
//---------------------------------------------------------------------------//

MonteCarlo::TwoDDistribution twod_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that lower bin is sample for independent variable < lower boundary
TEUCHOS_UNIT_TEST( TwoDDistributionHelpers, sampleTwoDDistribution_below )
{
  double sampled_variable;

  sampled_variable = MonteCarlo::sampleTwoDDistribution( 0.0001, twod_distribution );

  TEST_FLOATING_EQUALITY( sampled_variable, 0.000000000000, 1e-15  );
}

//---------------------------------------------------------------------------//
// Check that upper bin is sample for independent variable > upper boundary
TEUCHOS_UNIT_TEST( TwoDDistributionHelpers, sampleTwoDDistribution_above )
{
  double sampled_variable;

  sampled_variable = MonteCarlo::sampleTwoDDistribution( 1.0, twod_distribution );

  TEST_FLOATING_EQUALITY( sampled_variable, 2.000000000000, 1e-15  );
}

//---------------------------------------------------------------------------//
// Check that lower bin is sample for independent variable inbetween bins
TEUCHOS_UNIT_TEST( TwoDDistributionHelpers, sampleTwoDDistribution_lower )
{
  double sampled_variable;

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.4; // sample lower bin (1.0)
 
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sampled_variable = MonteCarlo::sampleTwoDDistribution( 0.05, twod_distribution );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( sampled_variable, 2.000000000000, 1e-15  );
}

//---------------------------------------------------------------------------//
// Check that upper bin is sample for independent variable inbetween bins
TEUCHOS_UNIT_TEST( TwoDDistributionHelpers, sampleTwoDDistribution_upper )
{
  double sampled_variable;

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.6; // sample upper bin (2.0)
 
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sampled_variable = MonteCarlo::sampleTwoDDistribution( 0.05, twod_distribution );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( sampled_variable, 1.000000000000, 1e-15  );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Create the two dimensional distribution
  twod_distribution.resize(3);
  twod_distribution[0].first = 0.001;
  twod_distribution[0].second.reset( new Utility::DeltaDistribution(0.0) );
  twod_distribution[1].first = 0.01;
  twod_distribution[1].second.reset( new Utility::DeltaDistribution(1.0) );
  twod_distribution[2].first = 0.1;
  twod_distribution[2].second.reset( new Utility::DeltaDistribution(2.0) );

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
// end tstCoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
