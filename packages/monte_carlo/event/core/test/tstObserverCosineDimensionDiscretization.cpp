//---------------------------------------------------------------------------//
//!
//! \file   tstObserverCosineDimensionDiscretization.cpp
//! \author Alex Robinson
//! \brief  Observer cosine dimension discretization unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_DefaultTypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimensionTraits.hpp"
#include "MonteCarlo_ObserverParticleStateWrapper.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::ObserverPhaseSpaceDimensionDiscretization>
dimension_discretization, dimension_discretization_with_line_bins;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the discretized dimension can be returned
FRENSIE_UNIT_TEST( ObserverCosineDimensionDiscretization, getDimension )
{
  FRENSIE_CHECK_EQUAL( dimension_discretization->getDimension(),
                       MonteCarlo::OBSERVER_COSINE_DIMENSION );
  FRENSIE_CHECK_EQUAL( dimension_discretization_with_line_bins->getDimension(),
                       MonteCarlo::OBSERVER_COSINE_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the name of discretized dimension can be returned
FRENSIE_UNIT_TEST( ObserverCosineDimensionDiscretization, getDimensionName )
{
  FRENSIE_CHECK_EQUAL( dimension_discretization->getDimensionName(),
                       "Cosine" );
  FRENSIE_CHECK_EQUAL( dimension_discretization_with_line_bins->getDimensionName(),
                       "Cosine" );
}

//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
FRENSIE_UNIT_TEST( ObserverCosineDimensionDiscretization, getNumberOfBins )
{
  FRENSIE_CHECK_EQUAL( dimension_discretization->getNumberOfBins(), 3 );
  FRENSIE_CHECK_EQUAL( dimension_discretization_with_line_bins->getNumberOfBins(), 5 );
}

//---------------------------------------------------------------------------//
// Check if a value is contained in the discretization
FRENSIE_UNIT_TEST( ObserverCosineDimensionDiscretization,
                   isValueInDiscretization_any )
{
  FRENSIE_CHECK( !dimension_discretization->isValueInDiscretization( boost::any(-2.0) ) );
  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( boost::any(-1.0) ) );
  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( boost::any(0.0) ) );
  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( boost::any(1.0) ) );
  FRENSIE_CHECK( !dimension_discretization->isValueInDiscretization( boost::any(2.0) ) );

  FRENSIE_CHECK( !dimension_discretization_with_line_bins->isValueInDiscretization( boost::any(-2.0) ) );
  FRENSIE_CHECK( dimension_discretization_with_line_bins->isValueInDiscretization( boost::any(-1.0) ) );
  FRENSIE_CHECK( dimension_discretization_with_line_bins->isValueInDiscretization( boost::any(0.0) ) );
  FRENSIE_CHECK( dimension_discretization_with_line_bins->isValueInDiscretization( boost::any(1.0) ) );
  FRENSIE_CHECK( !dimension_discretization_with_line_bins->isValueInDiscretization( boost::any(2.0) ) );
}

//---------------------------------------------------------------------------//
// Check if a value is contained in the discretization
FRENSIE_UNIT_TEST( ObserverCosineDimensionDiscretization,
                   isValueInDiscretization_wrapper )
{
  MonteCarlo::PhotonState photon( 0 );
  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  photon_wrapper.setAngleCosine( -1.0 );

  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( photon_wrapper ) );
  FRENSIE_CHECK( dimension_discretization_with_line_bins->isValueInDiscretization( photon_wrapper ) );

  photon_wrapper.setAngleCosine( 0.0 );
  
  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( photon_wrapper ) );
  FRENSIE_CHECK( dimension_discretization_with_line_bins->isValueInDiscretization( photon_wrapper ) );

  photon_wrapper.setAngleCosine( 1.0 );
  
  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( photon_wrapper ) );
  FRENSIE_CHECK( dimension_discretization_with_line_bins->isValueInDiscretization( photon_wrapper ) );
}

//---------------------------------------------------------------------------//
// Check if a range intersects the discretization
FRENSIE_UNIT_TEST( ObserverCosineDimensionDiscretization,
                   doesRangeIntersectDiscretization )
{
  MonteCarlo::PhotonState photon( 0 );
  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  photon_wrapper.setAngleCosine( -1.0 );

  FRENSIE_CHECK( dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );
  FRENSIE_CHECK( dimension_discretization_with_line_bins->doesRangeIntersectDiscretization( photon_wrapper ) );

  photon_wrapper.setAngleCosine( 0.0 );
  
  FRENSIE_CHECK( dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );
  FRENSIE_CHECK( dimension_discretization_with_line_bins->doesRangeIntersectDiscretization( photon_wrapper ) );

  photon_wrapper.setAngleCosine( 1.0 );
  
  FRENSIE_CHECK( dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );
  FRENSIE_CHECK( dimension_discretization_with_line_bins->doesRangeIntersectDiscretization( photon_wrapper ) );
}

//---------------------------------------------------------------------------//
// Check that a bin index can be calculated
FRENSIE_UNIT_TEST( ObserverCosineDimensionDiscretization,
                   calculateBinIndicesOfValue_any )
{
  MonteCarlo::ObserverCosineDimensionDiscretization::BinIndexArray
    bin_indices;

  dimension_discretization->calculateBinIndicesOfValue( boost::any(-1.0), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  dimension_discretization->calculateBinIndicesOfValue( boost::any(-2.0/3), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  dimension_discretization->calculateBinIndicesOfValue( boost::any(-1.0/3), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  dimension_discretization->calculateBinIndicesOfValue( boost::any(0.0), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  dimension_discretization->calculateBinIndicesOfValue( boost::any(1.0/3), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  dimension_discretization->calculateBinIndicesOfValue( boost::any(2.0/3), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  dimension_discretization->calculateBinIndicesOfValue( boost::any(1.0), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  // Check that line bin indices are calculated correctly
  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(-1.0), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(-2.0/3), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(-1.0/3), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(-0.0000000000001), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(0.0), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(0.0000000000001), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(1.0/3), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(2.0/3), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 4 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(1.0), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 4 );
}

//---------------------------------------------------------------------------//
// Check that a bin index can be calculated
FRENSIE_UNIT_TEST( ObserverCosineDimensionDiscretization,
                   calculateBinIndicesOfValue_wrapper )
{
  MonteCarlo::ObserverCosineDimensionDiscretization::BinIndexArray
    bin_indices;

  MonteCarlo::PhotonState photon( 0 );
  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  photon_wrapper.setAngleCosine( -1.0 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  photon_wrapper.setAngleCosine( -2.0/3 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  photon_wrapper.setAngleCosine( -1.0/3 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  photon_wrapper.setAngleCosine( 0.0 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  photon_wrapper.setAngleCosine( 1.0/3 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  photon_wrapper.setAngleCosine( 2.0/3 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  photon_wrapper.setAngleCosine( 1.0 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  // Check that line bin indices are calculated correctly
  photon_wrapper.setAngleCosine( -1.0 );
  
  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  photon_wrapper.setAngleCosine( -2.0/3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  photon_wrapper.setAngleCosine( -1.0/3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  photon_wrapper.setAngleCosine( -0.0000000000001 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  photon_wrapper.setAngleCosine( 0.0 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  photon_wrapper.setAngleCosine( 0.0000000000001 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 3 );

  photon_wrapper.setAngleCosine( 1.0/3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 3 );

  photon_wrapper.setAngleCosine( 2.0/3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 4 );

  photon_wrapper.setAngleCosine( 1.0 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 4 );
}

//---------------------------------------------------------------------------//
// Check that a bin index can be calculated
FRENSIE_UNIT_TEST( ObserverCosineDimensionDiscretization,
                   calculateBinIndicesOfValue_weights_wrapper )
{
  MonteCarlo::ObserverCosineDimensionDiscretization::BinIndexWeightPairArray
    bin_indices_and_weights;

  MonteCarlo::PhotonState photon( 0 );
  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  photon_wrapper.setAngleCosine( -1.0 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( -2.0/3 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( -1.0/3 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( 0.0 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( 1.0/3 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( 2.0/3 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( 1.0 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  // Check that line bin indices are calculated correctly
  photon_wrapper.setAngleCosine( -1.0 );
  
  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( -2.0/3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( -1.0/3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( -0.0000000000001 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( 0.0 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( 0.0000000000001 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 3 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( 1.0/3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 3 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( 2.0/3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 4 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( 1.0 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 4 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the bin indices of a range can be calculated
FRENSIE_UNIT_TEST( ObserverCosineDimensionDiscretization,
                   calculateBinIndicesOfRange )
{
  MonteCarlo::ObserverCosineDimensionDiscretization::BinIndexWeightPairArray
    bin_indices_and_weights;

  MonteCarlo::PhotonState photon( 0 );
  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  photon_wrapper.setAngleCosine( -1.0 );

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( -2.0/3 );

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( -1.0/3 );

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( 0.0 );

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( 1.0/3 );

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( 2.0/3 );

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( 1.0 );

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  // Check that line bin indices are calculated correctly
  photon_wrapper.setAngleCosine( -1.0 );
  
  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( -2.0/3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( -1.0/3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( -0.0000000000001 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( 0.0 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( 0.0000000000001 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 3 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( 1.0/3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 3 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( 2.0/3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 4 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon_wrapper.setAngleCosine( 1.0 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 4 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the boundaries of a bin can be printed
FRENSIE_UNIT_TEST( ObserverCosineDimensionDiscretization,
                   printBoundariesOfBin )
{
  std::ostringstream oss;

  dimension_discretization->printBoundariesOfBin( oss, 0 );

  FRENSIE_CHECK_EQUAL( oss.str(), "Cosine Bin: [-1.000000000000000000e+00,-3.333333333333333148e-01]" );

  oss.str( "" );
  oss.clear();

  dimension_discretization->printBoundariesOfBin( oss, 1 );

  FRENSIE_CHECK_EQUAL( oss.str(), "Cosine Bin: (-3.333333333333333148e-01,3.333333333333333148e-01]" );

  oss.str( "" );
  oss.clear();

  dimension_discretization->printBoundariesOfBin( oss, 2 );

  FRENSIE_CHECK_EQUAL( oss.str(), "Cosine Bin: (3.333333333333333148e-01,1.000000000000000000e+00]" );
}

//---------------------------------------------------------------------------//
// Check that a discretization can be printed
FRENSIE_UNIT_TEST( ObserverCosineDimensionDiscretization, print )
{
  std::ostringstream oss;

  dimension_discretization->print( oss );

  FRENSIE_CHECK( oss.str().find( "Cosine Bin Boundaries:" ) <
                 oss.str().size() );

  std::cout << oss.str() << std::endl;
}

//---------------------------------------------------------------------------//
// Check that a discretization can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ObserverCosineDimensionDiscretization,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_observer_cosine_dimension_discretization" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const MonteCarlo::ObserverPhaseSpaceDimensionDiscretization>
      discretization = dimension_discretization;

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( discretization ) )
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<const MonteCarlo::ObserverPhaseSpaceDimensionDiscretization>
    discretization;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( discretization ) );

  iarchive.reset();

  FRENSIE_CHECK_EQUAL( discretization->getNumberOfBins(), 3 );

  MonteCarlo::ObserverCosineDimensionDiscretization::BinIndexArray
    bin_indices;

  discretization->calculateBinIndicesOfValue( boost::any(-1.0), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  discretization->calculateBinIndicesOfValue( boost::any(-2.0/3), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  discretization->calculateBinIndicesOfValue( boost::any(-1.0/3), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  discretization->calculateBinIndicesOfValue( boost::any(0.0), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  discretization->calculateBinIndicesOfValue( boost::any(1.0/3), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  discretization->calculateBinIndicesOfValue( boost::any(2.0/3), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  discretization->calculateBinIndicesOfValue( boost::any(1.0), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  MonteCarlo::ObserverCosineDimensionDiscretization::InputDataType discretization( 4 );

  discretization[0] = -1.0;
  discretization[1] = -1.0/3;
  discretization[2] = 1.0/3;
  discretization[3] = 1.0;
  
  dimension_discretization.reset( new MonteCarlo::ObserverCosineDimensionDiscretization( discretization ) );

  discretization.resize( 6 );

  discretization[0] = -1.0;
  discretization[1] = -1.0/3;
  discretization[2] = 0.0;
  discretization[3] = 0.0;
  discretization[4] = 1.0/3;
  discretization[5] = 1.0;

  dimension_discretization_with_line_bins.reset( new MonteCarlo::ObserverCosineDimensionDiscretization( discretization ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstObserverCosineDimensionDiscretization.cpp
//---------------------------------------------------------------------------//
