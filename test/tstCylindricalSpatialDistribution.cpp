//---------------------------------------------------------------------------//
//!
//! \file   tstCylindricalSpatialDistribution.cpp
//! \author Alex Robinson
//! \brief  Cylindrical spatial distribution unit tests.
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
#include "PowerDistribution.hpp"
#include "UniformDistribution.hpp"
#include "SpatialDistribution.hpp"
#include "CylindricalSpatialDistribution.hpp"
#include "PhysicalConstants.hpp"
#include "RandomNumberGenerator.hpp"

Teuchos::RCP<FACEMC::SpatialDistribution> spatial_distribution;

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
// Initialize the distribution
void initializeDistribution( 
		      Teuchos::RCP<FACEMC::SpatialDistribution>& distribution )
{
  // Power distribution in r dimension
  Teuchos::RCP<FACEMC::OneDDistribution>
    r_distribution( new FACEMC::PowerDistribution<1u>( 2.0, 0.0, 1.0 ) );

  // Uniform distribution in theta dimension
  Teuchos::RCP<FACEMC::OneDDistribution>
    theta_distribution( new FACEMC::UniformDistribution( 
					       0.0, 
					       2*FACEMC::PhysicalConstants::pi,
					       1.0 ) );

  // Uniform distribution in axis dimension
  Teuchos::RCP<FACEMC::OneDDistribution>
    axis_distribution( new FACEMC::UniformDistribution( -1.0, 1.0, 1.0 ) );

  distribution.reset( new FACEMC::CylindricalSpatialDistribution( 
							   r_distribution,
							   theta_distribution,
							   axis_distribution,
							   1.0,
							   1.0,
							   1.0 ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( CylindricalSpatialDistribution, evaluate )
{
  initializeDistribution( spatial_distribution );

  double cartesian_point[3] = {1.0, 1.0, 1.0};
  TEST_EQUALITY_CONST( spatial_distribution->evaluate( cartesian_point ), 2.0);

  cartesian_point[0] = 2.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluate( cartesian_point ), 2.0);

  cartesian_point[0] = 1.0;
  cartesian_point[1] = 2.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluate( cartesian_point ), 2.0);
  
  cartesian_point[2] = 2.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluate( cartesian_point ), 2.0);
  
  cartesian_point[0] = 1.0/sqrt(2.0)+1;
  cartesian_point[1] = 1.0/sqrt(2.0)+1;
  cartesian_point[2] = 1.0;
  TEST_FLOATING_EQUALITY( spatial_distribution->evaluate( cartesian_point ), 
			  2.0, 
			  1e-15 );

  
  cartesian_point[0] = -1.0/sqrt(2.0)+1;
  cartesian_point[1] = -1.0/sqrt(2.0)+1;
  cartesian_point[2] = 0.0;
  TEST_FLOATING_EQUALITY( spatial_distribution->evaluate( cartesian_point ), 
			  2.0, 
			  1e-15 );

  cartesian_point[0] = 1.0;
  cartesian_point[1] = 2.0;
  cartesian_point[2] = 3.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluate( cartesian_point ), 0.0);
  
  cartesian_point[0] = 1.0;
  cartesian_point[1] = 0.0;
  cartesian_point[2] = -1.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluate( cartesian_point ), 0.0);
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( CylindricalSpatialDistribution, evaluatePDF )
{
  initializeDistribution( spatial_distribution );

  double pdf_value = 2.0/(FACEMC::PhysicalConstants::pi*4);

  double cartesian_point[3] = {1.0, 1.0, 1.0};
  TEST_EQUALITY_CONST( spatial_distribution->evaluatePDF( cartesian_point ), 
		       0.0 );

  cartesian_point[0] = 2.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluatePDF( cartesian_point ), 
		       pdf_value );

  cartesian_point[0] = 1.0;
  cartesian_point[1] = 2.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluatePDF( cartesian_point ), 
		       pdf_value );

  cartesian_point[0] = 1.0/sqrt(2.0)+1;
  cartesian_point[1] = 1.0/sqrt(2.0)+1;
  cartesian_point[2] = 2.0;
  TEST_FLOATING_EQUALITY( spatial_distribution->evaluatePDF( cartesian_point ),
			  pdf_value,
			  1e-15 );

  cartesian_point[0] = -1.0/sqrt(2.0)+1;
  cartesian_point[1] = -1.0/sqrt(2.0)+1;
  cartesian_point[2] = 0.0;
  TEST_FLOATING_EQUALITY( spatial_distribution->evaluatePDF( cartesian_point ),
			  pdf_value,
			  1e-15 );

  cartesian_point[0] = 2.0;
  cartesian_point[1] = 2.0;
  cartesian_point[2] = 1.0;
  TEST_EQUALITY_CONST( spatial_distribution->evaluatePDF( cartesian_point ), 
		       0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from
TEUCHOS_UNIT_TEST( CylindricalSpatialDistribution, sample )
{
  initializeDistribution( spatial_distribution );

  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.5;
  fake_stream[5] = 0.5;
  fake_stream[6] = 1.0 - 1e-15;
  fake_stream[7] = 1.0 - 1e-15;
  fake_stream[8] = 1.0 - 1e-15;

  FACEMC::RandomNumberGenerator::setFakeStream( fake_stream );

  double sampled_point[3];

  spatial_distribution->sample( sampled_point );
  TEST_EQUALITY_CONST( sampled_point[0], 1.0 );
  TEST_EQUALITY_CONST( sampled_point[1], 1.0 );
  TEST_EQUALITY_CONST( sampled_point[2], 0.0 );

  spatial_distribution->sample( sampled_point );
  TEST_EQUALITY_CONST( sampled_point[0], 1.0-sqrt(0.5) );
  TEST_EQUALITY_CONST( sampled_point[1], 1.0 );
  TEST_EQUALITY_CONST( sampled_point[2], 1.0 );

  spatial_distribution->sample( sampled_point );
  TEST_FLOATING_EQUALITY( sampled_point[0], 2.0, 1e-14 );
  TEST_FLOATING_EQUALITY( sampled_point[1], 1.0, 1e-14 );
  TEST_FLOATING_EQUALITY( sampled_point[2], 2.0, 1e-14 );

  FACEMC::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that distribution can be tested for uniformity
TEUCHOS_UNIT_TEST( CylindricalSpatialDistribution, isUniform )
{
  initializeDistribution( spatial_distribution );

  TEST_ASSERT( spatial_distribution->isUniform() );
}

//---------------------------------------------------------------------------//
// end tstCylindricalSpatialDistribution.cpp
//---------------------------------------------------------------------------//

