//---------------------------------------------------------------------------//
//!
//! \file   tstTabularDistribution.cpp
//! \author Alex Robinson
//! \brief  Tabular distribution unit tests.
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
#include "TabularDistribution.hpp"
#include "RandomNumberGenerator.hpp"

Teuchos::RCP<FACEMC::OneDDistribution> distribution;

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name )				\
  typedef FACEMC::LinLin LinLin;					\
  typedef FACEMC::LogLin LogLin;					\
  typedef FACEMC::LinLog LinLog;					\
  typedef FACEMC::LogLog LogLog;					\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, LinLin )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, LogLin )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, LinLog )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, LogLog )	

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the distribution
template<typename InterpolationPolicy>
void initializeDistribution()
{
  Teuchos::Array<double> independent_values( 4 );
  independent_values[0] = 1e-3;
  independent_values[1] = 1e-2;
  independent_values[2] = 1e-1;
  independent_values[3] = 1.0;
  
  Teuchos::Array<double> dependent_values( 4 );
  dependent_values[0] = 1e2;
  dependent_values[1] = 1e1;
  dependent_values[2] = 1.0;
  dependent_values[3] = 1e-1;

  distribution.reset( new FACEMC::TabularDistribution<InterpolationPolicy>(
							  independent_values,
							  dependent_values ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution, 
				   evaluate,
				   InterpolationPolicy )
{
  initializeDistribution<InterpolationPolicy>();

  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1e-3 ), 1e2 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1e-2 ), 1e1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1e-1 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), 1e-1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0 ), 0.0 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, evaluate );

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated 
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution, 
				   evaluatePDF,
				   InterpolationPolicy )
{
  initializeDistribution<InterpolationPolicy>();

  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( distribution->evaluatePDF( 1e-3 ), 
			  67.340006734, 
			  1e-6 );
  TEST_FLOATING_EQUALITY( distribution->evaluatePDF( 1e-2 ), 
			  6.7340006734, 
			  1e-6 );
  TEST_FLOATING_EQUALITY( distribution->evaluatePDF( 1e-1 ), 
			  0.67340006734, 
			  1e-6 );
  TEST_FLOATING_EQUALITY( distribution->evaluatePDF( 1.0 ), 
			  0.067340006734, 
			  1e-6 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 2.0 ), 0.0 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, evaluatePDF );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
				   sample,
				   InterpolationPolicy )
{
  initializeDistribution<InterpolationPolicy>();

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  FACEMC::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 1e-3 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-12 );

  FACEMC::RandomNumberGenerator::unsetFakeStream();
  FACEMC::RandomNumberGenerator::initialize();
  
  sample = distribution->sample();
  TEST_COMPARE( sample, >=, 1e-3 );
  TEST_COMPARE( sample, <=, 1.0 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, sample );

//---------------------------------------------------------------------------//
// Check that the sampling efficiency can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
				   getSamplingEfficiency,
				   InterpolationPolicy )
{
  initializeDistribution<InterpolationPolicy>();

  TEST_EQUALITY_CONST( distribution->getSamplingEfficiency(), 1.0 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, getSamplingEfficiency );

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
				   getUpperBoundOfIndepVar,
				   InterpolationPolicy )
{
  initializeDistribution<InterpolationPolicy>();

  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 1.0 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, getUpperBoundOfIndepVar );

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
				   getLowerBoundOfIndepVar,
				   InterpolationPolicy )
{
  initializeDistribution<InterpolationPolicy>();

  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), 1e-3 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, getLowerBoundOfIndepVar );



//---------------------------------------------------------------------------//
// end tstTabularDistribution.cpp
//---------------------------------------------------------------------------//
