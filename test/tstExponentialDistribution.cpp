//---------------------------------------------------------------------------//
//!
//! \file   tstExponentialDistribution.cpp
//! \author Alex Robinson
//! \brief  Histogram distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "FACEMC_UnitTestHarnessExtensions.hpp"
#include "OneDDistribution.hpp"
#include "ExponentialDistribution.hpp"
#include "RandomNumberGenerator.hpp"

Teuchos::RCP<FACEMC::OneDDistribution> distribution( 
			     new FACEMC::ExponentialDistribution( 2.0, 3.0 ) );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( ExponentialDistribution, evaluate )
{
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 2.0 );
  TEST_FLOATING_EQUALITY(distribution->evaluate( 1.0 ), 2.0*exp(-3.0), 1e-12);
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( ExponentialDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), 3.0 );
  TEST_FLOATING_EQUALITY(distribution->evaluatePDF(1.0), 3.0*exp(-3.0), 1e-12);
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( ExponentialDistribution, sample )
{
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;
  fake_stream[2] = 0.5;

  FACEMC::RandomNumberGenerator::setFakeStream( fake_stream );
  
  double sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, std::numeric_limits<double>::infinity() );
  
  sample = distribution->sample(); 
  FACEMC_TEST_FLOATING_EQUALITY( sample, 0.0, 1e-15 );

  sample = distribution->sample(); 
  TEST_FLOATING_EQUALITY( sample, -log(0.5)/3.0, 1e-12 );

  FACEMC::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the sampling efficiency can be returned
TEUCHOS_UNIT_TEST( ExponentialDistribution, getSamplingEfficiency )
{
  TEST_EQUALITY_CONST( distribution->getSamplingEfficiency(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( ExponentialDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(),
		       std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( ExponentialDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( ExponentialDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       FACEMC::EXPONENTIAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// end tstExponentialDistribution.cpp
//---------------------------------------------------------------------------//
