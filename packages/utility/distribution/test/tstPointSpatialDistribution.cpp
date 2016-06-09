//---------------------------------------------------------------------------//
//!
//! \file   tstPointSpatialDistribution.cpp
//! \author Alex Robinson
//! \brief  Point spatial distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_PointSpatialDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"

Teuchos::RCP<Utility::SpatialDistribution> spatial_distribution;

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( PointSpatialDistribution, evaluate )
{
  double point[3] = {0.0, 0.0, 0.0};

  TEST_EQUALITY_CONST( spatial_distribution->evaluate( point ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( PointSpatialDistribution, evaluatePDF )
{
  double point[3] = {0.0, 0.0, 0.0};

  TEST_EQUALITY_CONST( spatial_distribution->evaluate( point ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from
TEUCHOS_UNIT_TEST( PointSpatialDistribution, sample )
{
  double sampled_point[3];

  spatial_distribution->sample( sampled_point );

  TEST_EQUALITY_CONST( sampled_point[0], 1.0 );
  TEST_EQUALITY_CONST( sampled_point[1], 1.0 );
  TEST_EQUALITY_CONST( sampled_point[2], 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( PointSpatialDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( spatial_distribution->getDistributionType(),
		       Utility::POINT_SPATIAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the spatial distribution is uniform
TEUCHOS_UNIT_TEST( PointSpatialDistribution, isUniform )
{
  TEST_ASSERT( spatial_distribution->isUniform() );
}

//---------------------------------------------------------------------------//
// Check if spatial distributions have the same bounds
TEUCHOS_UNIT_TEST( PointSpatialDistribution, hasSameBounds )
{
  Teuchos::RCP<Utility::SpatialDistribution> distribution_a(
		      new Utility::PointSpatialDistribution( 0.0, 0.0, 0.0 ) );

  Teuchos::RCP<Utility::SpatialDistribution> distribution_b(
		      new Utility::PointSpatialDistribution( 1.0, 1.0, 1.0 ) );

  TEST_ASSERT( !spatial_distribution->hasSameBounds( *distribution_a ) );
  TEST_ASSERT( spatial_distribution->hasSameBounds( *distribution_b ) );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  spatial_distribution.reset(
		      new Utility::PointSpatialDistribution( 1.0, 1.0, 1.0 ) );

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstPointSpatialDistribution.cpp
//---------------------------------------------------------------------------//
