//---------------------------------------------------------------------------//
//!
//! \file   tstOneDDistribution.cpp
//! \author Alex Robinson
//! \brief  OneDDistribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_ExponentialDistribution.hpp"
#include "Utility_UniformDistribution.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the bounds of two distributions can be tested
TEUCHOS_UNIT_TEST( OneDDistribution, hasSameBounds )
{
  Teuchos::RCP<Utility::OneDDistribution> delta_dist(
					 new Utility::DeltaDistribution( 1 ) );
  Teuchos::RCP<Utility::OneDDistribution> discrete_dist(
	new Utility::DiscreteDistribution( Teuchos::tuple( -1.0, 0.0, 1.0 ),
					   Teuchos::tuple( 1.0, 1.0, 1.0 ) ) );
  Teuchos::RCP<Utility::OneDDistribution> histogram_dist(
       new Utility::HistogramDistribution( Teuchos::tuple( -1.0, 0.0, 1.0 ),
					   Teuchos::tuple( 1.0, 1.0 ) ) );

  Teuchos::RCP<Utility::OneDDistribution> exponential_dist(
			    new Utility::ExponentialDistribution( 1.0, 1.0 ) );

  Teuchos::RCP<Utility::OneDDistribution> uniform_dist(
			  new Utility::UniformDistribution( -1.0, 1.0, 1.0 ) );
  
  TEST_ASSERT( !delta_dist->hasSameBounds( *discrete_dist ) );
  TEST_ASSERT( !delta_dist->hasSameBounds( *histogram_dist ) );
  TEST_ASSERT( !delta_dist->hasSameBounds( *exponential_dist ) );
  TEST_ASSERT( !delta_dist->hasSameBounds( *uniform_dist ) );
  TEST_ASSERT( discrete_dist->hasSameBounds( *histogram_dist ) );
  TEST_ASSERT( !discrete_dist->hasSameBounds( *exponential_dist ) );
  TEST_ASSERT( discrete_dist->hasSameBounds( *uniform_dist ) );
  TEST_ASSERT( !histogram_dist->hasSameBounds( *exponential_dist ) );
  TEST_ASSERT( histogram_dist->hasSameBounds( *uniform_dist ) );
  TEST_ASSERT( !exponential_dist->hasSameBounds( *uniform_dist ) );
}

//---------------------------------------------------------------------------//
// end tstOneDDistribution.cpp
//---------------------------------------------------------------------------//
