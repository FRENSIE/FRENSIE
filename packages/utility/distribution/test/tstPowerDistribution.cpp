//---------------------------------------------------------------------------//
//!
//! \file   tstPowerDistribution.cpp
//! \author Alex Robinson
//! \brief  Power distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_PowerDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"

Teuchos::RCP<Utility::OneDDistribution> distribution;

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name )			\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, 1u )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, 2u )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, 3u )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, 4u )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, 5u )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, 6u )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, 7u )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, 8u )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, 9u )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, 10u )	

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the distribution
template<unsigned N>
void initializeDistribution( 
			Teuchos::RCP<Utility::OneDDistribution>& distribution )
{
  distribution.reset( new Utility::PowerDistribution<N>( (N+1.0), 0.0, 1.0 ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
UTILITY_UNIT_TEST_UNSIGNED_TEMPLATE_1_DECL( PowerDistribution, evaluate, N )
{
  initializeDistribution<N>( distribution );
  
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), N + 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0 ), 0.0 );
}
				   
UNIT_TEST_INSTANTIATION( PowerDistribution, evaluate );

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
UTILITY_UNIT_TEST_UNSIGNED_TEMPLATE_1_DECL( PowerDistribution, evaluatePDF, N )
{
  initializeDistribution<N>( distribution );

  TEST_EQUALITY_CONST( distribution->evaluate( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), N + 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0 ), 0.0 );
}
				   
UNIT_TEST_INSTANTIATION( PowerDistribution, evaluatePDF );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
UTILITY_UNIT_TEST_UNSIGNED_TEMPLATE_1_DECL( PowerDistribution, sample, N )
{
  initializeDistribution<N>( distribution );
  
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  double sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, pow(0.5, 1.0/(N+1u)) );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

UNIT_TEST_INSTANTIATION( PowerDistribution, sample );

//---------------------------------------------------------------------------//
// Check that the sampling efficiency can be returned
UTILITY_UNIT_TEST_UNSIGNED_TEMPLATE_1_DECL( PowerDistribution, 
					   getSamplingEfficiency, 
					   N )
{
  initializeDistribution<N>( distribution );

  TEST_EQUALITY_CONST( distribution->getSamplingEfficiency(), 1.0 );
}

UNIT_TEST_INSTANTIATION( PowerDistribution, getSamplingEfficiency );

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
UTILITY_UNIT_TEST_UNSIGNED_TEMPLATE_1_DECL( PowerDistribution, 
					   getUpperBoundOfIndepVar,
					   N )
{
  initializeDistribution<N>( distribution );
  
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 1.0 );
}

UNIT_TEST_INSTANTIATION( PowerDistribution, getUpperBoundOfIndepVar );

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
UTILITY_UNIT_TEST_UNSIGNED_TEMPLATE_1_DECL( PowerDistribution, 
					   getLowerBoundOfIndepVar,
					   N )
{
  initializeDistribution<N>( distribution );
  
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

UNIT_TEST_INSTANTIATION( PowerDistribution, getLowerBoundOfIndepVar );

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
UTILITY_UNIT_TEST_UNSIGNED_TEMPLATE_1_DECL( PowerDistribution,
					   getDistributionType,
					   N )
{
  initializeDistribution<N>( distribution );

  switch( N )
  {
  case 1u:
    TEST_EQUALITY_CONST( distribution->getDistributionType(),
			 Utility::POWER_1_DISTRIBUTION );
    break;
  case 2u:
    TEST_EQUALITY_CONST( distribution->getDistributionType(),
			 Utility::POWER_2_DISTRIBUTION );
    break;
  default:
    TEST_EQUALITY_CONST( distribution->getDistributionType(),
			 Utility::POWER_N_DISTRIBUTION );
    break;
  }
}

UNIT_TEST_INSTANTIATION( PowerDistribution, getDistributionType );

//---------------------------------------------------------------------------//
// end tstPowerDistribution.cpp
//---------------------------------------------------------------------------//
