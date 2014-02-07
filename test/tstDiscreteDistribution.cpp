//---------------------------------------------------------------------------//
//!
//! \file   tstDiscreteDistribution.cpp
//! \author Alex Robinson
//! \brief  Discrete distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FACEMC Includes
#include "OneDDistribution.hpp"
#include "DiscreteDistribution.hpp"
#include "RandomNumberGenerator.hpp"

Teuchos::RCP<FACEMC::OneDDistribution> distribution;

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
// Initialize the distribution
void initializeDistribution( 
			 Teuchos::RCP<FACEMC::OneDDistribution>& distribution )
{
  if( distribution.is_null() )
  {
    Teuchos::Array<double> independent_values( 3 );
    independent_values[0] = -1.0;
    independent_values[1] = 0.0;
    independent_values[2] = 1.0;
    
    Teuchos::Array<double> dependent_values( 3 );
    dependent_values[0] = 1.0;
    dependent_values[1] = 2.0;
    dependent_values[2] = 1.0;
    
    distribution.reset( new FACEMC::DiscreteDistribution( independent_values,
							  dependent_values ) );

    FACEMC::RandomNumberGenerator::initialize();
  }
}


//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( DiscreteDistribution, evaluate )
{  
  initializeDistribution( distribution );
  
  TEST_EQUALITY_CONST( distribution->evaluate( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0 ), 
		       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( distribution->evaluate( -0.5 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 
		       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.5 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), 
		       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( DiscreteDistribution, evaluatePDF )
{
  initializeDistribution( distribution );
  
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -2.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -1.0 ), 0.25 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -0.5 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), 0.50 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.5 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 1.0 ), 0.25 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DeltaDistribution, sample )
{
  initializeDistribution( distribution );
  
  unsigned num_samples = 100000;
  unsigned num_value_1_samples = 0;
  unsigned num_value_2_samples = 0;
  unsigned num_value_3_samples = 0;
  
  for( unsigned i = 0; i < num_samples; ++i )
  {
    double sample = distribution->sample();
    
    if( sample == -1.0 )
      ++num_value_1_samples;
    else if( sample == 0.0 )
      ++num_value_2_samples;
    else if( sample == 1.0 )
      ++num_value_3_samples;
  }

  TEST_FLOATING_EQUALITY( num_value_1_samples/(double)num_samples,0.25,1e-2 );
  TEST_FLOATING_EQUALITY( num_value_2_samples/(double)num_samples,0.50,1e-2 );
  TEST_FLOATING_EQUALITY( num_value_3_samples/(double)num_samples,0.25,1e-2 );
}

//---------------------------------------------------------------------------//
// Check that the sampling efficiency can be returned
TEUCHOS_UNIT_TEST( DiscreteDistribution, getSamplingEfficiency )
{
  initializeDistribution( distribution );
  
  TEST_EQUALITY_CONST( distribution->getSamplingEfficiency(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( DiscreteDistribution, getUpperBoundOfIndepVar )
{
  initializeDistribution( distribution );
  
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution dependent variable can be
// returned
TEUCHOS_UNIT_TEST( DiscreteDistribution, getLowerBoundOfIndepVar )
{
  initializeDistribution( distribution );

  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), -1.0 );
}

//---------------------------------------------------------------------------//
// end tstDiscreteDistribution.cpp
//---------------------------------------------------------------------------//
