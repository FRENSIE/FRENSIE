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

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"

Teuchos::RCP<Utility::OneDDistribution> distribution;

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
// Initialize the distribution
void initializeDistribution(
			 Teuchos::RCP<Utility::OneDDistribution>& distribution )
{
  Teuchos::Array<double> bin_boundaries( 4 );
  bin_boundaries[0] = -2.0;
  bin_boundaries[1] = -1.0;
  bin_boundaries[2] = 1.0;
  bin_boundaries[3] = 2.0;
  
  Teuchos::Array<double> bin_values( 3 );
  bin_values[0] = 2.0;
  bin_values[1] = 1.0;
  bin_values[2] = 2.0;
  
  distribution.reset( new Utility::HistogramDistribution( bin_boundaries,
							 bin_values ) );
  
  Utility::RandomNumberGenerator::initialize();
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( HistogramDistribution, evalute )
{
  initializeDistribution( distribution );

  TEST_EQUALITY_CONST( distribution->evaluate( -3.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -2.0 ), 2.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.5 ), 2.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), 2.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.5 ), 2.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0 ), 2.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( HistogramDistribution, evaluatePDF )
{
  initializeDistribution( distribution );

  TEST_EQUALITY_CONST( distribution->evaluatePDF( -3.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -2.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -1.5 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -1.0 ), 1.0/6.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), 1.0/6.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 1.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 1.5 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 2.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 3.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( HistogramDistribution, sample )
{
  initializeDistribution( distribution );

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

  // First bin
  double sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -2.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.5 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, -1.0, 1e-14 );
  
  // Second bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.0 );

  sample = distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-14 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-14 );
  
  // Third bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.0 );
  
  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 1.5, 1e-14 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the sampling efficiency can be returned
TEUCHOS_UNIT_TEST( HistogramDistribution, getSamplingEfficiency )
{
  initializeDistribution( distribution );

  TEST_EQUALITY_CONST( distribution->getSamplingEfficiency(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( HistogramDistribution, getUpperBoundOfIndepVar )
{
  initializeDistribution( distribution );
  
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution dependent variable can be
// returned
TEUCHOS_UNIT_TEST( HistogramDistribution, getLowerBoundOfIndepVar )
{
  initializeDistribution( distribution );

  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), -2.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( HistogramDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       Utility::HISTOGRAM_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to and read from an xml file
TEUCHOS_UNIT_TEST( HistogramDistribution, toFromParameterList )
{
  Teuchos::RCP<Utility::HistogramDistribution> true_distribution =
    Teuchos::rcp_dynamic_cast<Utility::HistogramDistribution>( distribution );
  
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
// end tstHistogramDistribution.cpp
//---------------------------------------------------------------------------//
