//---------------------------------------------------------------------------//
//!
//! \file   tstCartesianSpatialDistribution.cpp
//! \author Alex Robinson
//! \brief  Cartesian spatial distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_SpatialDistribution.hpp"
#include "Utility_CartesianSpatialDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"

Teuchos::RCP<Utility::SpatialDistribution> spatial_distribution;

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
// Initialize the distribution
void initializeDistribution(
		      Teuchos::RCP<Utility::SpatialDistribution>& distribution )
{
  // Delta distribution in x dimension
  Teuchos::RCP<Utility::OneDDistribution> 
    x_distribution( new Utility::DeltaDistribution( 1.0 ) );

  // Uniform distribution in y dimension
  Teuchos::RCP<Utility::OneDDistribution>
    y_distribution( new Utility::UniformDistribution( 0.0, 2.0, 0.5 ) );

  // Uniform distribution in z dimension
  Teuchos::RCP<Utility::OneDDistribution>
    z_distribution( new Utility::UniformDistribution( 0.0, 2.0, 0.5 ) );

  distribution.reset( new Utility::CartesianSpatialDistribution( 
							    x_distribution,
							    y_distribution,
							    z_distribution ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( CartesianSpatialDistribution, evaluate )
{
  initializeDistribution( spatial_distribution );

  double point[3] = {0.0, 0.0, 0.0};
  TEST_EQUALITY_CONST( spatial_distribution->evaluate( point ), 0.0 );

  point[0] = 1.0;
  point[1] = 1.0;
  point[2] = 1.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluate( point ), 
		       std::numeric_limits<double>::infinity() );

  point[0] = 1.0;
  point[1] = 3.0;
  point[2] = 3.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluate( point ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( CartesianSpatialDistribution, evaluatePDF )
{
  initializeDistribution( spatial_distribution );

  double point[3] = {0.0, 0.0, 0.0};
  TEST_EQUALITY_CONST( spatial_distribution->evaluatePDF( point ), 0.0 );

  point[0] = 1.0;
  point[1] = 1.0;
  point[2] = 1.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluatePDF( point ), 0.25 );

  point[0] = 1.0;
  point[1] = 3.0;
  point[2] = 3.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluatePDF( point ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribuiton can be sampled from
TEUCHOS_UNIT_TEST( CartesianSpatialDistribution, sample )
{
  initializeDistribution( spatial_distribution );

  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.5;
  fake_stream[4] = 1.0 - 1e-15;
  fake_stream[5] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sampled_point[3] = {0.0, 0.0, 0.0};

  spatial_distribution->sample( sampled_point );
  TEST_EQUALITY_CONST( sampled_point[0], 1.0 );
  TEST_EQUALITY_CONST( sampled_point[1], 0.0 );
  TEST_EQUALITY_CONST( sampled_point[2], 0.0 );

  spatial_distribution->sample( sampled_point );
  TEST_EQUALITY_CONST( sampled_point[0], 1.0 );
  TEST_EQUALITY_CONST( sampled_point[1], 1.0 );
  TEST_EQUALITY_CONST( sampled_point[2], 1.0 );
  
  spatial_distribution->sample( sampled_point );
  TEST_EQUALITY_CONST( sampled_point[0], 1.0 );
  TEST_FLOATING_EQUALITY( sampled_point[1], 2.0, 1e-15 );
  TEST_FLOATING_EQUALITY( sampled_point[2], 2.0, 1e-15 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that distribution can be tested for uniformity
TEUCHOS_UNIT_TEST( CartesianSpatialDistribution, isUniform )
{
  initializeDistribution( spatial_distribution );

  TEST_ASSERT( !spatial_distribution->isUniform() );
}

//---------------------------------------------------------------------------//
// end tstCartesianSpatialDistribution.cpp
//---------------------------------------------------------------------------//
