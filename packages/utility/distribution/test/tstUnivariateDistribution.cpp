//---------------------------------------------------------------------------//
//!
//! \file   tstUnivariateDistribution.cpp
//! \author Alex Robinson
//! \brief  UnivariateDistribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>
#include <memory>

// FRENSIE Includes
#include "Utility_UnivariateDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_ExponentialDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the bounds of two distributions can be tested
FRENSIE_UNIT_TEST( UnivariateDistribution, hasSameBounds )
{
  std::shared_ptr<Utility::UnivariateDistribution> delta_dist(
					new Utility::DeltaDistribution( 1. ) );
  std::shared_ptr<Utility::UnivariateDistribution> discrete_dist(
      new Utility::DiscreteDistribution( {-1.0, 0.0, 1.0}, {1.0, 1.0, 1.0} ) );
  std::shared_ptr<Utility::UnivariateDistribution> histogram_dist(
          new Utility::HistogramDistribution( {-1.0, 0.0, 1.0}, {1.0, 1.0} ) );

  std::shared_ptr<Utility::UnivariateDistribution> exponential_dist(
			    new Utility::ExponentialDistribution( 1.0, 1.0 ) );

  std::shared_ptr<Utility::UnivariateDistribution> uniform_dist(
			  new Utility::UniformDistribution( -1.0, 1.0, 1.0 ) );

  FRENSIE_CHECK( !delta_dist->hasSameBounds( *discrete_dist ) );
  FRENSIE_CHECK( !delta_dist->hasSameBounds( *histogram_dist ) );
  FRENSIE_CHECK( !delta_dist->hasSameBounds( *exponential_dist ) );
  FRENSIE_CHECK( !delta_dist->hasSameBounds( *uniform_dist ) );
  FRENSIE_CHECK( discrete_dist->hasSameBounds( *histogram_dist ) );
  FRENSIE_CHECK( !discrete_dist->hasSameBounds( *exponential_dist ) );
  FRENSIE_CHECK( discrete_dist->hasSameBounds( *uniform_dist ) );
  FRENSIE_CHECK( !histogram_dist->hasSameBounds( *exponential_dist ) );
  FRENSIE_CHECK( histogram_dist->hasSameBounds( *uniform_dist ) );
  FRENSIE_CHECK( !exponential_dist->hasSameBounds( *uniform_dist ) );
}

//---------------------------------------------------------------------------//
// end tstUnivariateDistribution.cpp
//---------------------------------------------------------------------------//
