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
#include "Utility_HistogramDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variable
//---------------------------------------------------------------------------//

MonteCarlo::TwoDDistribution twod_distribution;
double interpolation_fraction, independent_value, energy;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that lower bin is sample for independent variable < lower boundary
TEUCHOS_UNIT_TEST( TwoDDistributionHelpers, sampleTwoDDistributionCorrelated_below )
{
  double sampled_variable;

  // Set up the random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 3.0/18.0; // sample the first distribution
 
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sampled_variable = MonteCarlo::sampleTwoDDistributionCorrelated( 0.0001, twod_distribution );

  TEST_FLOATING_EQUALITY( sampled_variable, -1.5, 1e-15  );
}

//---------------------------------------------------------------------------//
// Check that upper bin is sample for independent variable > upper boundary
TEUCHOS_UNIT_TEST( TwoDDistributionHelpers, sampleTwoDDistributionCorrelated_above )
{
  double sampled_variable;

  // Set up the random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample the last distribution
 
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sampled_variable = MonteCarlo::sampleTwoDDistributionCorrelated( 1.0, twod_distribution );

  TEST_FLOATING_EQUALITY( sampled_variable, 2.0, 1e-15  );
}

//---------------------------------------------------------------------------//
// Check the sample for independent variable inbetween bins
TEUCHOS_UNIT_TEST( TwoDDistributionHelpers, sampleTwoDDistributionCorrelated_inbetween )
{
  double sampled_variable;

  // Set up the random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample between the middle and last distribution
 
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sampled_variable = MonteCarlo::sampleTwoDDistributionCorrelated( 0.05, twod_distribution );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( sampled_variable, 13.0/9.0, 1e-15  );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be correlated sampled with a random number
TEUCHOS_UNIT_TEST( TwoDDistributionHelpers, sampleTwoDDistributionCorrelatedWithRandomNumber )
{
  double sampled_variable;
  double random_number =  3.0/18.0; // sample the first distribution

  sampled_variable = 
    MonteCarlo::sampleTwoDDistributionCorrelatedWithRandomNumber( 
        0.0001, 
        twod_distribution,
        random_number ); 

  TEST_FLOATING_EQUALITY( sampled_variable, -1.5, 1e-15  );

  random_number = 0.5;

  sampled_variable = 
    MonteCarlo::sampleTwoDDistributionCorrelatedWithRandomNumber( 
        1.0, 
        twod_distribution,
        random_number );

  TEST_FLOATING_EQUALITY( sampled_variable, 2.0, 1e-15  );

  sampled_variable = 
    MonteCarlo::sampleTwoDDistributionCorrelatedWithRandomNumber( 
        0.05, 
        twod_distribution,
        random_number );

  TEST_FLOATING_EQUALITY( sampled_variable, 13.0/9.0, 1e-15  );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled with a random number using independent sampling
TEUCHOS_UNIT_TEST( TwoDDistributionHelpers, sampleTwoDDistributionIndependent )
{
  double sampled_variable;

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // sample between the middle and last distribution
  fake_stream[1] = 0.5; // sample from middle distribution
 
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sampled_variable = 
    MonteCarlo::sampleTwoDDistributionIndependent( 0.05, twod_distribution );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( sampled_variable, 1.0, 1e-15  );
}

//---------------------------------------------------------------------------//
// Check the correlated cdf value can be evaluated
TEUCHOS_UNIT_TEST( TwoDDistributionHelpers, evaluateTwoDDistributionCorrelatedCDF )
{
  double sampled_variable;

  sampled_variable = MonteCarlo::evaluateTwoDDistributionCorrelatedCDF(
                                                   energy,  
                                                   independent_value,
                                                   twod_distribution );

  TEST_FLOATING_EQUALITY( sampled_variable, 0.4259259259259260, 1e-15  );
}

//---------------------------------------------------------------------------//
// Check the correlated pdf value can be evaluated
TEUCHOS_UNIT_TEST( TwoDDistributionHelpers, evaluateTwoDDistributionCorrelatedPDF )
{
  double sampled_variable;

  sampled_variable = MonteCarlo::evaluateTwoDDistributionCorrelatedPDF( 
                                                   energy,  
                                                   independent_value,
                                                   twod_distribution );

  TEST_FLOATING_EQUALITY( sampled_variable, 1.5/9.0, 1e-15  );
}

//---------------------------------------------------------------------------//
// Check the correlated value can be evaluated
TEUCHOS_UNIT_TEST( TwoDDistributionHelpers, evaluateTwoDDistributionCorrelated )
{
  double sampled_variable;

  sampled_variable = MonteCarlo::evaluateTwoDDistributionCorrelated( 
                                                   energy,  
                                                   independent_value,
                                                   twod_distribution );

  TEST_FLOATING_EQUALITY( sampled_variable, 1.0, 1e-15  );
}

//---------------------------------------------------------------------------//
// Check the correlation sample for two bins with random number
TEUCHOS_UNIT_TEST( TwoDDistributionHelpers, correlatedSampleWithRandomNumber )
{
  double sampled_variable;

  double random_number = 0.5; // sample between the middle and last distribution

  sampled_variable = 
    MonteCarlo::correlatedSampleWithRandomNumber( twod_distribution[2].second,
                                                  twod_distribution[1].second,
                                                  interpolation_fraction,
                                                  random_number );

  TEST_FLOATING_EQUALITY( sampled_variable, 13.0/9.0, 1e-15  );
}

//---------------------------------------------------------------------------//
// Check the correlation sample for two bins
TEUCHOS_UNIT_TEST( TwoDDistributionHelpers, correlatedSample )
{
  double sampled_variable;

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // sample between the middle and last distribution
 
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sampled_variable = MonteCarlo::correlatedSample( twod_distribution[2].second,
                                                   twod_distribution[1].second,
                                                   interpolation_fraction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( sampled_variable, 13.0/9.0, 1e-15  );
}

//---------------------------------------------------------------------------//
// Check the correlation sample for two bins in a subrange
TEUCHOS_UNIT_TEST( TwoDDistributionHelpers, correlatedSampleInSubrange )
{
  double sampled_variable;

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // sample between the middle and last distribution
 
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sampled_variable = 
           MonteCarlo::correlatedSampleInSubrange( twod_distribution[2].second,
                                                   twod_distribution[1].second,
                                                   interpolation_fraction,
                                                   3.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( sampled_variable, 1.0, 1e-15  );
}

//---------------------------------------------------------------------------//
// Check the correlated cdf value can be evaluated
TEUCHOS_UNIT_TEST( TwoDDistributionHelpers, evaluateCorrelatedCDF )
{
  double sampled_variable;

  sampled_variable = MonteCarlo::evaluateCorrelatedCDF( 
                                                   twod_distribution[2].second,
                                                   twod_distribution[1].second,
                                                   interpolation_fraction,
                                                   independent_value );

  TEST_FLOATING_EQUALITY( sampled_variable, 0.4259259259259260, 1e-15  );
}

//---------------------------------------------------------------------------//
// Check the correlated pdf value can be evaluated
TEUCHOS_UNIT_TEST( TwoDDistributionHelpers, evaluateCorrelatedPDF )
{
  double sampled_variable;

  sampled_variable = MonteCarlo::evaluateCorrelatedPDF( 
                                                   twod_distribution[2].second,
                                                   twod_distribution[1].second,
                                                   interpolation_fraction,
                                                   independent_value );

  TEST_FLOATING_EQUALITY( sampled_variable, 1.5/9.0, 1e-12  );
}

//---------------------------------------------------------------------------//
// Check the correlated value can be evaluated
TEUCHOS_UNIT_TEST( TwoDDistributionHelpers, evaluateCorrelated )
{
  double sampled_variable;

  sampled_variable = MonteCarlo::evaluateCorrelated( 
                                                   twod_distribution[2].second,
                                                   twod_distribution[1].second,
                                                   interpolation_fraction,
                                                   independent_value );

  TEST_FLOATING_EQUALITY( sampled_variable, 1.0, 1e-12  );
}

//---------------------------------------------------------------------------//
// Check that the distributions can be sampled independently
TEUCHOS_UNIT_TEST( TwoDDistributionHelpers, independentSample )
{
  double sampled_variable;

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // sample from the middle distribution
  fake_stream[1] = 0.5; // sample cdf = 0.5
 
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sampled_variable = MonteCarlo::independentSample( twod_distribution[2].second,
                                                    twod_distribution[1].second,
                                                    interpolation_fraction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( sampled_variable, 1.0, 1e-12  );
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

  // Create a first fake histogram distribution
  Teuchos::Array<double> dist_1_bin_boundaries( 4 );
  dist_1_bin_boundaries[0] = -2.0;
  dist_1_bin_boundaries[1] = -1.0;
  dist_1_bin_boundaries[2] = 1.0;
  dist_1_bin_boundaries[3] = 2.0;
  
  Teuchos::Array<double> bin_values( 3 );
  bin_values[0] = 2.0;
  bin_values[1] = 1.0;
  bin_values[2] = 2.0;

  twod_distribution[0].second.reset( new Utility::HistogramDistribution( 
                                                          dist_1_bin_boundaries,
							                              bin_values) );

  twod_distribution[1].first = 0.01;

  // Create a second fake histogram distribution
  Teuchos::Array<double> dist_2_bin_boundaries( 4 );
  dist_2_bin_boundaries[0] = -1.0;
  dist_2_bin_boundaries[1] = 0.0;
  dist_2_bin_boundaries[2] = 2.0;
  dist_2_bin_boundaries[3] = 3.0;

  twod_distribution[1].second.reset( new Utility::HistogramDistribution( 
                                                          dist_2_bin_boundaries,
							                              bin_values) );

  twod_distribution[2].first = 0.1;

  // Create a third fake histogram distribution
  Teuchos::Array<double> dist_3_bin_boundaries( 4 );
  dist_3_bin_boundaries[0] = 0.0;
  dist_3_bin_boundaries[1] = 1.0;
  dist_3_bin_boundaries[2] = 3.0;
  dist_3_bin_boundaries[3] = 4.0; 

  twod_distribution[2].second.reset( new Utility::HistogramDistribution( 
                                                          dist_3_bin_boundaries,
							                              bin_values) );

  independent_value = 1.0;
  energy = 0.05;

  interpolation_fraction = ( energy - twod_distribution[1].first )/
                 ( twod_distribution[2].first  - twod_distribution[1].first );

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
