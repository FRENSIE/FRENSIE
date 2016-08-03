//---------------------------------------------------------------------------//
//!
//! \file   tstMonoDirectionalDistribution.cpp
//! \author Alex Robinson
//! \brief  Mono directional distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Tuple.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_MonoDirectionalDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"

Teuchos::RCP<Utility::DirectionalDistribution> directional_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( MonoDirectionalDistribution, evaluate )
{
  double point[3] = {0.0, 0.0, 0.0};

  TEST_EQUALITY_CONST( directional_distribution->evaluate( point ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( MonoDirectionalDistribution, evaluatePDF )
{
  double point[3] = {0.0, 0.0, 0.0};

  TEST_EQUALITY_CONST( directional_distribution->evaluatePDF( point ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from
TEUCHOS_UNIT_TEST( MonoDirectionalDistribution, sample )
{
  double direction[3];
  directional_distribution->sample( direction );

  TEST_FLOATING_EQUALITY( direction[0], 0.5773502691896258, 1e-15 );
  TEST_FLOATING_EQUALITY( direction[1], 0.5773502691896258, 1e-15 );
  TEST_FLOATING_EQUALITY( direction[2], 0.5773502691896258, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( MonoDirectionalDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( directional_distribution->getDistributionType(),
		       Utility::MONO_DIRECTIONAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the bounds of two distributions can be tested
TEUCHOS_UNIT_TEST( MonoDirectionalDistribution, hasSameBounds )
{
  Teuchos::RCP<Utility::DirectionalDistribution> directional_dist_a(
		   new Utility::MonoDirectionalDistribution( 0.0, 0.0, 1.0 ) );

  Teuchos::RCP<Utility::DirectionalDistribution> directional_dist_b(
		   new Utility::MonoDirectionalDistribution( 1.0, 1.0, 1.0 ) );

  TEST_ASSERT( !directional_distribution->hasSameBounds( *directional_dist_a));
  TEST_ASSERT( directional_distribution->hasSameBounds( *directional_dist_b ));
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  directional_distribution.reset( new Utility::MonoDirectionalDistribution(
							     1.0, 1.0, 1.0 ) );

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstMonoDirectionalDistribution.cpp
//---------------------------------------------------------------------------//
