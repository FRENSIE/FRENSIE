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

// FACEMC Includes
#include "OneDDistribution.hpp"
#include "HistogramDistribution.hpp"
#include "RandomNumberGenerator.hpp"

Teuchos::RCP<FACEMC::OneDDistribution> distribution;

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
// Initialize the distribution
void initializeDistribution(
			 Teuchos::RCP<FACEMC::OneDDistribution>& distribution )
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
  
  distribution.reset( new FACEMC::HistogramDistribution( bin_boundaries,
							 bin_values ) );
  
  FACEMC::RandomNumberGenerator::initialize();
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
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0 ), 2.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), 1.0 );
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
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -1.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), 1.0/6.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 1.0 ), 1.0/6.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 1.5 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 2.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 3.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( HistogramDistribution, sample )
{
  initializeDistribution( distribution );

  Teuchos::RCP<FACEMC::HistogramDistribution> histogram_distribution = 
    Teuchos::rcp_dynamic_cast<FACEMC::HistogramDistribution>( distribution );
  
  // First bin
  TEST_EQUALITY_CONST( histogram_distribution->sample( 0.0, 0.0 ), -2.0 );
  TEST_EQUALITY_CONST( histogram_distribution->sample( 0.0, 0.5 ), -1.5 );
  TEST_EQUALITY_CONST( histogram_distribution->sample( 0.0, 1.0 ), -1.0 );
  TEST_EQUALITY_CONST( histogram_distribution->sample( 1.0/3.0, 0.0 ), -2.0 );
  TEST_EQUALITY_CONST( histogram_distribution->sample( 1.0/3.0, 0.5 ), -1.5 );
  TEST_EQUALITY_CONST( histogram_distribution->sample( 1.0/3.0, 1.0 ), -1.0 );
  // Second bin
  TEST_EQUALITY_CONST( histogram_distribution->sample( 0.4, 0.0 ), -1.0 );
  TEST_EQUALITY_CONST( histogram_distribution->sample( 0.4, 0.5 ), -0.0 );
  TEST_EQUALITY_CONST( histogram_distribution->sample( 0.4, 1.0 ), 1.0 );
  TEST_EQUALITY_CONST( histogram_distribution->sample( 2.0/3.0, 0.0 ), -1.0 );
  TEST_EQUALITY_CONST( histogram_distribution->sample( 2.0/3.0, 0.5 ), -0.0 );
  TEST_EQUALITY_CONST( histogram_distribution->sample( 2.0/3.0, 1.0 ), 1.0 );
  // Third bin
  TEST_EQUALITY_CONST( histogram_distribution->sample( 0.7, 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( histogram_distribution->sample( 0.7, 0.5 ), 1.5 );
  TEST_EQUALITY_CONST( histogram_distribution->sample( 0.7, 1.0 ), 2.0 );
  TEST_EQUALITY_CONST( histogram_distribution->sample( 1.0, 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( histogram_distribution->sample( 1.0, 0.5 ), 1.5 );
  TEST_EQUALITY_CONST( histogram_distribution->sample( 1.0, 1.0 ), 2.0 );
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
// end tstHistogramDistribution.cpp
//---------------------------------------------------------------------------//
