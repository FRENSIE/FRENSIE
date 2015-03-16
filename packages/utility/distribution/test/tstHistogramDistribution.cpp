//---------------------------------------------------------------------------//
//!
//! \file   tstHistogramDistribution.cpp
//! \author Alex Robinson
//! \brief  Histogram distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Utility::OneDDistribution> pdf_distribution;
Teuchos::RCP<Utility::OneDDistribution> cdf_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( HistogramDistribution, evalute )
{
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( -3.0 ), 0.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( -2.0 ), 2.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( -1.5 ), 2.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( -1.0 ), 1.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( 1.0 ), 2.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( 1.5 ), 2.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( 2.0 ), 2.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluate( 3.0 ), 0.0 );

  TEST_EQUALITY_CONST( cdf_distribution->evaluate( -3.0 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( -2.0 ), 2.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( -1.5 ), 2.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( -1.0 ), 1.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( 1.0 ), 2.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( 1.5 ), 2.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( 2.0 ), 2.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluate( 3.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( HistogramDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( -3.0 ), 0.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( -2.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( -1.5 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( -1.0 ), 1.0/6.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( 0.0 ), 1.0/6.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( 1.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( 1.5 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( 2.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( pdf_distribution->evaluatePDF( 3.0 ), 0.0 );

  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( -3.0 ), 0.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( -2.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( -1.5 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( -1.0 ), 1.0/6.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( 0.0 ), 1.0/6.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( 1.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( 1.5 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( 2.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( cdf_distribution->evaluatePDF( 3.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
TEUCHOS_UNIT_TEST( HistogramDistribution, evaluateCDF )
{
  TEST_EQUALITY_CONST(   pdf_distribution->evaluateCDF(-3.0 ), 0.0 );
  TEST_EQUALITY_CONST(   pdf_distribution->evaluateCDF(-2.0 ), 0.0 );
  TEST_FLOATING_EQUALITY(pdf_distribution->evaluateCDF(-1.5 ), 1.0/6.0, 1e-14 );
  TEST_EQUALITY_CONST(   pdf_distribution->evaluateCDF(-1.0 ), 1.0/3.0 );
  TEST_FLOATING_EQUALITY(pdf_distribution->evaluateCDF( 0.0 ), 0.5, 1e-14 );
  TEST_EQUALITY_CONST(   pdf_distribution->evaluateCDF( 1.0 ), 2.0/3.0 );
  TEST_FLOATING_EQUALITY(pdf_distribution->evaluateCDF( 1.5 ), 5.0/6.0, 1e-14 );
  TEST_EQUALITY_CONST(   pdf_distribution->evaluateCDF( 2.0 ), 1.0 );
  TEST_EQUALITY_CONST(   pdf_distribution->evaluateCDF( 3.0 ), 1.0 );

  TEST_EQUALITY_CONST(   cdf_distribution->evaluateCDF(-3.0 ), 0.0 );
  TEST_EQUALITY_CONST(   cdf_distribution->evaluateCDF(-2.0 ), 0.0 );
  TEST_FLOATING_EQUALITY(cdf_distribution->evaluateCDF(-1.5 ), 1.0/6.0, 1e-14 );
  TEST_EQUALITY_CONST(   cdf_distribution->evaluateCDF(-1.0 ), 1.0/3.0 );
  TEST_FLOATING_EQUALITY(cdf_distribution->evaluateCDF( 0.0 ), 0.5, 1e-14 );
  TEST_EQUALITY_CONST(   cdf_distribution->evaluateCDF( 1.0 ), 2.0/3.0 );
  TEST_FLOATING_EQUALITY(cdf_distribution->evaluateCDF( 1.5 ), 5.0/6.0, 1e-14 );
  TEST_EQUALITY_CONST(   cdf_distribution->evaluateCDF( 2.0 ), 1.0 );
  TEST_EQUALITY_CONST(   cdf_distribution->evaluateCDF( 3.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( HistogramDistribution, sample )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0/6.0;
  fake_stream[2] = 1.0/3.0 - 1e-15;
  fake_stream[3] = 1.0/3.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 2.0/3.0 - 1e-15;
  fake_stream[6] = 2.0/3.0;
  fake_stream[7] = 5.0/6.0;
  fake_stream[8] = 1.0 - 1e-15;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index;

  // Test the first bin
  double sample = pdf_distribution->sample( bin_index );
  TEST_EQUALITY_CONST( sample, -2.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = pdf_distribution->sample( bin_index );
  TEST_EQUALITY_CONST( sample, -1.5 );
  TEST_EQUALITY_CONST( bin_index, 0u );  

  sample = pdf_distribution->sample( bin_index );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 0u );
  
  // Test the second bin
  sample = pdf_distribution->sample( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = pdf_distribution->sample( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = pdf_distribution->sample( bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 1u );
  
  // Test the third bin
  sample = pdf_distribution->sample( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 2u );
  
  sample = pdf_distribution->sample( bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.5, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample = pdf_distribution->sample( bin_index );
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Test the first bin
  sample = cdf_distribution->sample( bin_index );
  TEST_EQUALITY_CONST( sample, -2.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = cdf_distribution->sample( bin_index );
  TEST_EQUALITY_CONST( sample, -1.5 );
  TEST_EQUALITY_CONST( bin_index, 0u );  

  sample = cdf_distribution->sample( bin_index );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 0u );
  
  // Test the second bin
  sample = cdf_distribution->sample( bin_index );
  TEST_EQUALITY_CONST( sample, -1.0 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = cdf_distribution->sample( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  sample = cdf_distribution->sample( bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 1u );
  
  // Test the third bin
  sample = cdf_distribution->sample( bin_index );
  TEST_EQUALITY_CONST( sample, 1.0 );
  TEST_EQUALITY_CONST( bin_index, 2u );
  
  sample = cdf_distribution->sample( bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.5, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  sample = cdf_distribution->sample( bin_index );
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-14 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST( HistogramDistribution, sample_subrange )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15 ;
  fake_stream[3] = 0.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 1.0 - 1e-15;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // PDF Histogram
  // Test max independent value 2nd bin
  double max_indep_val = -1.0;

  double sample = pdf_distribution->sample( max_indep_val );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = pdf_distribution->sample( max_indep_val );
  TEST_FLOATING_EQUALITY( sample, -1.5, 1e-14 ); 

  sample = pdf_distribution->sample( max_indep_val );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  
  // Test max independent value 3rd bin
  max_indep_val = 1.0;

  sample = pdf_distribution->sample( max_indep_val );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = pdf_distribution->sample( max_indep_val );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 ); 

  sample = pdf_distribution->sample( max_indep_val );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // CDF Histogram
  // Test max independent value 2nd bin
  max_indep_val = -1.0;

  sample = cdf_distribution->sample( max_indep_val );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = cdf_distribution->sample( max_indep_val );
  TEST_FLOATING_EQUALITY( sample, -1.5, 1e-14 );

  sample = cdf_distribution->sample( max_indep_val );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  
  // Test max independent value 3rd bin
  max_indep_val = 1.0;

  sample = cdf_distribution->sample( max_indep_val );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  sample = cdf_distribution->sample( max_indep_val );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  sample = cdf_distribution->sample( max_indep_val );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST( HistogramDistribution, sampleWithValue )
{
  std::vector<double> fake_stream( 8 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0/6.0;
  fake_stream[2] = 1.0/3.0 - 1e-15;
  fake_stream[3] = 1.0/3.0;
  fake_stream[4] = 2.0/3.0 - 1e-15;
  fake_stream[5] = 2.0/3.0;
  fake_stream[6] = 5.0/6.0;
  fake_stream[7] = 1.0 - 1e-15;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // PDF Histogram

  // Test the first bin
  double cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  double sample = pdf_distribution->sampleWithValue( cdf_value );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = pdf_distribution->sampleWithValue( cdf_value );
  TEST_FLOATING_EQUALITY( sample, -1.5, 1e-14 ); 

  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = pdf_distribution->sampleWithValue( cdf_value );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  
  // Test the second bin
  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = pdf_distribution->sampleWithValue( cdf_value );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = pdf_distribution->sampleWithValue( cdf_value );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // Test the third bin
  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = pdf_distribution->sampleWithValue( cdf_value );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = pdf_distribution->sampleWithValue( cdf_value );
  TEST_FLOATING_EQUALITY( sample, 1.5, 1e-14 ); 

  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = pdf_distribution->sampleWithValue( cdf_value );
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // CDF Histogram

  // Test the first bin
  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = cdf_distribution->sampleWithValue( cdf_value );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = cdf_distribution->sampleWithValue( cdf_value );
  TEST_FLOATING_EQUALITY( sample, -1.5, 1e-14 );

  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = cdf_distribution->sampleWithValue( cdf_value );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  
  // Test the second bin
  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = cdf_distribution->sampleWithValue( cdf_value );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = cdf_distribution->sampleWithValue( cdf_value );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  // Test the third bin
  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = cdf_distribution->sampleWithValue( cdf_value );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = cdf_distribution->sampleWithValue( cdf_value );
  TEST_FLOATING_EQUALITY( sample, 1.5, 1e-14 );

  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = cdf_distribution->sampleWithValue( cdf_value );
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST( HistogramDistribution, sampleWithValue_subrange )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15 ;
  fake_stream[3] = 0.0;
  fake_stream[4] = 0.5;
  fake_stream[5] = 1.0 - 1e-15;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // PDF Histogram
  // Test max independent value 2nd bin
  double max_indep_val = -1.0;

  double cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  double sample = pdf_distribution->sampleWithValue( cdf_value, max_indep_val );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = pdf_distribution->sampleWithValue( cdf_value, max_indep_val );
  TEST_FLOATING_EQUALITY( sample, -1.5, 1e-14 ); 

  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = pdf_distribution->sampleWithValue( cdf_value, max_indep_val );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  
  // Test max independent value 3rd bin
  max_indep_val = 1.0;

  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = pdf_distribution->sampleWithValue( cdf_value, max_indep_val );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = pdf_distribution->sampleWithValue( cdf_value, max_indep_val );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 ); 

  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = pdf_distribution->sampleWithValue( cdf_value, max_indep_val );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // CDF Histogram
  // Test max independent value 2nd bin
  max_indep_val = -1.0;

  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = cdf_distribution->sampleWithValue( cdf_value, max_indep_val );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = cdf_distribution->sampleWithValue( cdf_value, max_indep_val );
  TEST_FLOATING_EQUALITY( sample, -1.5, 1e-14 );

  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = cdf_distribution->sampleWithValue( cdf_value, max_indep_val );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  
  // Test max independent value 3rd bin
  max_indep_val = 1.0;

  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = cdf_distribution->sampleWithValue( cdf_value, max_indep_val );
  TEST_FLOATING_EQUALITY( sample, -2.0, 1e-14 );

  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = cdf_distribution->sampleWithValue( cdf_value, max_indep_val );
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );

  cdf_value = Utility::RandomNumberGenerator::getRandomNumber<double>();
  sample = cdf_distribution->sampleWithValue( cdf_value, max_indep_val );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the sampling efficiency can be returned
TEUCHOS_UNIT_TEST( HistogramDistribution, getSamplingEfficiency )
{
  TEST_EQUALITY_CONST( pdf_distribution->getSamplingEfficiency(), 1.0 );
  TEST_EQUALITY_CONST( cdf_distribution->getSamplingEfficiency(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( HistogramDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( pdf_distribution->getUpperBoundOfIndepVar(), 2.0 );
  TEST_EQUALITY_CONST( cdf_distribution->getUpperBoundOfIndepVar(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution dependent variable can be
// returned
TEUCHOS_UNIT_TEST( HistogramDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( pdf_distribution->getLowerBoundOfIndepVar(), -2.0 );
  TEST_EQUALITY_CONST( cdf_distribution->getLowerBoundOfIndepVar(), -2.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( HistogramDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( pdf_distribution->getDistributionType(),
		       Utility::HISTOGRAM_DISTRIBUTION );

  TEST_EQUALITY_CONST( cdf_distribution->getDistributionType(),
		       Utility::HISTOGRAM_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to and read from an xml file
TEUCHOS_UNIT_TEST( HistogramDistribution, toFromParameterList )
{
  Teuchos::RCP<Utility::HistogramDistribution> true_distribution =
  Teuchos::rcp_dynamic_cast<Utility::HistogramDistribution>( pdf_distribution );
  
  Teuchos::ParameterList parameter_list;
  
  parameter_list.set<Utility::HistogramDistribution>( "test distribution", 
						     *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"histogram_dist_test_list.xml" );
  
  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list = 
    Teuchos::getParametersFromXmlFile( "histogram_dist_test_list.xml" );
  
  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Utility::HistogramDistribution> 
    copy_distribution( new Utility::HistogramDistribution );

  *copy_distribution = 
    read_parameter_list->get<Utility::HistogramDistribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
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

  // Create a distribution using the standard constructor
  Teuchos::Array<double> bin_boundaries( 4 );
  bin_boundaries[0] = -2.0;
  bin_boundaries[1] = -1.0;
  bin_boundaries[2] = 1.0;
  bin_boundaries[3] = 2.0;
  
  Teuchos::Array<double> bin_values( 3 );
  bin_values[0] = 2.0;
  bin_values[1] = 1.0;
  bin_values[2] = 2.0;
  
  pdf_distribution.reset( new Utility::HistogramDistribution( bin_boundaries,
							                                  bin_values) );

  // Create a distribution using the cdf constructor
  Teuchos::Array<double> cdf_values( 3 );
  cdf_values[0] = 2.0;
  cdf_values[1] = 4.0;
  cdf_values[2] = 6.0;
  
  cdf_distribution.reset( new Utility::HistogramDistribution( bin_boundaries,
							                                  cdf_values,
                                                              true ) );
  
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstHistogramDistribution.cpp
//---------------------------------------------------------------------------//
