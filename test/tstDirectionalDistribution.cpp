//---------------------------------------------------------------------------//
//!
//! \file   tstDirectionalDistribution.cpp
//! \author Alex Robinson
//! \brief  Directional distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "FACEMC_UnitTestHarnessExtensions.hpp"
#include "OneDDistribution.hpp"
#include "UniformDistribution.hpp"
#include "DirectionalDistribution.hpp"
#include "PhysicalConstants.hpp"
#include "RandomNumberGenerator.hpp"

Teuchos::RCP<FACEMC::DirectionalDistribution> directional_distribution;

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
// Initialize the distribution
void initializeDistribution( 
		  Teuchos::RCP<FACEMC::DirectionalDistribution>& distribution )
{
  // Uniform distribution in theta dimension
  Teuchos::RCP<FACEMC::OneDDistribution>
    theta_distribution( new FACEMC::UniformDistribution( 
					       0.0,
					       2*FACEMC::PhysicalConstants::pi,
					       1.0 ) );

  // Uniform distribution in mu dimension
  Teuchos::RCP<FACEMC::OneDDistribution>
    mu_distribution( new FACEMC::UniformDistribution( -1.0, 1.0, 1.0 ) );

  directional_distribution.reset( new FACEMC::DirectionalDistribution(
							   theta_distribution,
							   mu_distribution ) );
} 

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( DirectionalDistribution, evaluate )
{
  initializeDistribution( directional_distribution );

  double cartesian_point[3] = {0.0, 0.0, 1.0};
  TEST_EQUALITY_CONST( directional_distribution->evaluate( cartesian_point ),
		       1.0 );

  cartesian_point[1] = 1.0;
  cartesian_point[2] = 0.0;
  TEST_EQUALITY_CONST( directional_distribution->evaluate( cartesian_point ),
		       1.0 );

  cartesian_point[0] = 1.0;
  cartesian_point[1] = 0.0;
  TEST_EQUALITY_CONST( directional_distribution->evaluate( cartesian_point ),
		       1.0 );

  cartesian_point[0] = 1.0/sqrt(3.0);
  cartesian_point[1] = 1.0/sqrt(3.0);
  cartesian_point[2] = 1.0/sqrt(3.0);
  TEST_EQUALITY_CONST( directional_distribution->evaluate( cartesian_point ),
		       1.0 );

  cartesian_point[0] = -1.0/sqrt(3.0);
  cartesian_point[1] = -1.0/sqrt(3.0);
  cartesian_point[2] = -1.0/sqrt(3.0);
  TEST_EQUALITY_CONST( directional_distribution->evaluate( cartesian_point ),
		       1.0 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( DirectionalDistribution, evaluatePDF )
{
  initializeDistribution( directional_distribution );

  double pdf_value = 1.0/(FACEMC::PhysicalConstants::pi*4);

  double cartesian_point[3] = {0.0, 0.0, 1.0};
  TEST_EQUALITY_CONST( directional_distribution->evaluatePDF(cartesian_point),
		       pdf_value );

  cartesian_point[1] = 1.0;
  cartesian_point[2] = 0.0;
  TEST_EQUALITY_CONST( directional_distribution->evaluatePDF(cartesian_point),
		       pdf_value );

  cartesian_point[0] = 1.0;
  cartesian_point[1] = 0.0;
  TEST_EQUALITY_CONST( directional_distribution->evaluatePDF(cartesian_point),
		       pdf_value );

  cartesian_point[0] = 1.0/sqrt(3.0);
  cartesian_point[1] = 1.0/sqrt(3.0);
  cartesian_point[2] = 1.0/sqrt(3.0);
  TEST_EQUALITY_CONST( directional_distribution->evaluatePDF(cartesian_point),
		       pdf_value );

  cartesian_point[0] = -1.0/sqrt(3.0);
  cartesian_point[1] = -1.0/sqrt(3.0);
  cartesian_point[2] = -1.0/sqrt(3.0);
  TEST_EQUALITY_CONST( directional_distribution->evaluatePDF(cartesian_point),
		       pdf_value );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from
TEUCHOS_UNIT_TEST( DirectionalDistribution, sample )
{
  initializeDistribution( directional_distribution );
  
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.5;
  fake_stream[4] = 1.0 - 1e-15;
  fake_stream[5] = 1.0 - 1e-15;

  FACEMC::RandomNumberGenerator::setFakeStream( fake_stream );

  double sampled_direction[3];

  directional_distribution->sample( sampled_direction );
  TEST_EQUALITY_CONST( sampled_direction[0], 0.0 );
  TEST_EQUALITY_CONST( sampled_direction[1], 0.0 );
  TEST_EQUALITY_CONST( sampled_direction[2], -1.0 );

  directional_distribution->sample( sampled_direction );
  TEST_EQUALITY_CONST( sampled_direction[0], -1.0 );
  FACEMC_TEST_FLOATING_EQUALITY( sampled_direction[1], 0.0, 1e-15 );
  TEST_EQUALITY_CONST( sampled_direction[2], 0.0 );

  directional_distribution->sample( sampled_direction );
  FACEMC_TEST_FLOATING_EQUALITY( sampled_direction[0], 0.0, 1e-7 );
  FACEMC_TEST_FLOATING_EQUALITY( sampled_direction[1], 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( sampled_direction[2], 1.0, 1e-14 );

  FACEMC::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// end tstDirectionalDistribution.cpp
//---------------------------------------------------------------------------//
