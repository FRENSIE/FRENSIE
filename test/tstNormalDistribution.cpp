//---------------------------------------------------------------------------//
//!
//! \file   tstNormalDistribution.cpp
//! \author Alex Robinson
//! \brief  Normal distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FACEMC Includes
#include "FACEMC_UnitTestHarnessExtensions.hpp"
#include "OneDDistribution.hpp"
#include "NormalDistribution.hpp"
#include "PhysicalConstants.hpp"
#include "RandomNumberGenerator.hpp"

Teuchos::RCP<FACEMC::OneDDistribution> distribution(
				  new FACEMC::NormalDistribution( 0.0, 1.0 ) );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( NormalDistribution, evaluate )
{
  double center_value = 1.0/sqrt( 2.0*FACEMC::PhysicalConstants::pi );
  double off_center_value = center_value*exp( -4.0/2.0 );
  
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), center_value);
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0 ), off_center_value );
  TEST_EQUALITY_CONST( distribution->evaluate( -2.0 ), off_center_value );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( NormalDistribution, evaluatePDF )
{
  double center_value = 1.0/sqrt( 2.0*FACEMC::PhysicalConstants::pi );
  double off_center_value = center_value*exp( -4.0/2.0 );
  
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), center_value);
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0 ), off_center_value );
  TEST_EQUALITY_CONST( distribution->evaluate( -2.0 ), off_center_value );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( NormalDistribution, sample )
{
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.9;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.2;
  fake_stream[6] = 0.049787;
  fake_stream[7] = 0.449329;
  fake_stream[8] = 0.5;
  fake_stream[9] = 0.5;
  fake_stream[10] = 0.4;

  FACEMC::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 0.69314718055995, 1e-14 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, -0.69314718055995, 1e-14 );

  FACEMC::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the sampling efficiency can be returned
TEUCHOS_UNIT_TEST( NormalDistribution, getSamplingEfficiency )
{
  TEST_COMPARE( distribution->getSamplingEfficiency(), >=, 0.0 );
  TEST_COMPARE( distribution->getSamplingEfficiency(), <=, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( NormalDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(),
		       std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( NormalDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(),
		       -std::numeric_limits<double>::infinity() );
}

//---------------------------------------------------------------------------//
// end tstNormalDistribution.cpp
//---------------------------------------------------------------------------//

