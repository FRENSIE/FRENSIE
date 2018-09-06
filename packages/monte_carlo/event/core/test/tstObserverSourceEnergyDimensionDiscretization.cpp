//---------------------------------------------------------------------------//
//!
//! \file   tstObserverSourceEnergyDimensionDiscretization.cpp
//! \author Alex Robinson
//! \brief  Observer source energy dimension discretization unit tests
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
FRENSIE_UNIT_TEST( ObserverSourceEnergyDimensionDiscretization, getDimension )
{
  FRENSIE_CHECK_EQUAL( dimension_discretization->getDimension(),
                       MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION );
  FRENSIE_CHECK_EQUAL( dimension_discretization_with_line_bins->getDimension(),
                       MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the name of the discretized dimension can be returned
FRENSIE_UNIT_TEST( ObserverSourceEnergyDimensionDiscretization,
                   getDimensionName )
{
  FRENSIE_CHECK_EQUAL( dimension_discretization->getDimensionName(),
                       "Source Energy" );
  FRENSIE_CHECK_EQUAL( dimension_discretization_with_line_bins->getDimensionName(),
                       "Source Energy" );
}

//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
FRENSIE_UNIT_TEST( ObserverSourceEnergyDimensionDiscretization,
                   getNumberOfBins )
{
  FRENSIE_CHECK_EQUAL( dimension_discretization->getNumberOfBins(), 3 );
  FRENSIE_CHECK_EQUAL( dimension_discretization_with_line_bins->getNumberOfBins(), 8 );
}

//---------------------------------------------------------------------------//
// Check if a value is in the discretization
FRENSIE_UNIT_TEST( ObserverSourceEnergyDimensionDiscretization,
                   isValueInDiscretization_any )
{
  FRENSIE_CHECK( !dimension_discretization->isValueInDiscretization( boost::any(-1.0) ) );
  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( boost::any(0.0) ) );
  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( boost::any(1e-3) ) );
  FRENSIE_CHECK( !dimension_discretization->isValueInDiscretization( boost::any(5e-3) ) );

  FRENSIE_CHECK( !dimension_discretization_with_line_bins->isValueInDiscretization( boost::any(-1.0) ) );
  FRENSIE_CHECK( dimension_discretization_with_line_bins->isValueInDiscretization( boost::any(0.0) ) );
  FRENSIE_CHECK( dimension_discretization_with_line_bins->isValueInDiscretization( boost::any(1.0) ) );
  FRENSIE_CHECK( !dimension_discretization_with_line_bins->isValueInDiscretization( boost::any(1.5) ) );
}

//---------------------------------------------------------------------------//
// Check if a value is contained in the discretization
FRENSIE_UNIT_TEST( ObserverSourceEnergyDimensionDiscretization,
                   isValueInDiscretization_wrapper )
{
  MonteCarlo::PhotonState photon( 0 );
  photon.setSourceEnergy( 1e-15 );

  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( photon_wrapper ) );
  
  photon.setSourceEnergy( 1e-3 );
  
  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( photon_wrapper ) );

  photon.setSourceEnergy( 5e-3 );
  
  FRENSIE_CHECK( !dimension_discretization->isValueInDiscretization( photon_wrapper ) );

  photon.setSourceEnergy( 1e-15 );
                 
  FRENSIE_CHECK( dimension_discretization_with_line_bins->isValueInDiscretization( photon_wrapper ) );

  photon.setSourceEnergy( 1.0 );
  
  FRENSIE_CHECK( dimension_discretization_with_line_bins->isValueInDiscretization( photon_wrapper ) );

  photon.setSourceEnergy( 1.5 );
  
  FRENSIE_CHECK( !dimension_discretization_with_line_bins->isValueInDiscretization( photon_wrapper ) );
}

//---------------------------------------------------------------------------//
// Check if a range intersects the discretization
FRENSIE_UNIT_TEST( ObserverSourceEnergyDimensionDiscretization,
                   doesRangeIntersectDiscretization )
{
  MonteCarlo::PhotonState photon( 0 );
  photon.setSourceEnergy( 1e-15 );

  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  FRENSIE_CHECK( dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );
  
  photon.setSourceEnergy( 1e-3 );
  
  FRENSIE_CHECK( dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );

  photon.setSourceEnergy( 5e-3 );
  
  FRENSIE_CHECK( !dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );

  photon.setSourceEnergy( 1e-15 );
                 
  FRENSIE_CHECK( dimension_discretization_with_line_bins->doesRangeIntersectDiscretization( photon_wrapper ) );

  photon.setSourceEnergy( 1.0 );
  
  FRENSIE_CHECK( dimension_discretization_with_line_bins->doesRangeIntersectDiscretization( photon_wrapper ) );

  photon.setSourceEnergy( 1.5 );
  
  FRENSIE_CHECK( !dimension_discretization_with_line_bins->doesRangeIntersectDiscretization( photon_wrapper ) );
}

//---------------------------------------------------------------------------//
// Check that a bin index can be calculated
FRENSIE_UNIT_TEST( ObserverSourceEnergyDimensionDiscretization,
                   calculateBinIndicesOfValue_any )
{
  MonteCarlo::ObserverSourceEnergyDimensionDiscretization::BinIndexArray
    bin_indices;

  dimension_discretization->calculateBinIndicesOfValue( boost::any(0.0), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  dimension_discretization->calculateBinIndicesOfValue( boost::any(1e-5), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  dimension_discretization->calculateBinIndicesOfValue( boost::any(5e-5), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  dimension_discretization->calculateBinIndicesOfValue( boost::any(1e-4), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  dimension_discretization->calculateBinIndicesOfValue( boost::any(5e-4), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  dimension_discretization->calculateBinIndicesOfValue( boost::any(1e-3), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  // Check that line bins indices are calculated correctly
  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(0.0), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(1e-5), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(5e-5), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(1e-4), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(5e-4), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(9.9999999999999e-4), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(1e-3), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(1.0000000000001e-3), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 4 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(5e-3), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 4 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(1e-2), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 4 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(5e-2), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 5 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(9.999999999999e-2), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 5 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(1e-1), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 6 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(1.000000000001e-1), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 7 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(0.5), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 7 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( boost::any(1.0), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 7 );
}

//---------------------------------------------------------------------------//
// Check that a bin index can be calculated
FRENSIE_UNIT_TEST( ObserverSourceEnergyDimensionDiscretization,
                   calculateBinIndicesOfValue_wrapper )
{
  MonteCarlo::ObserverSourceEnergyDimensionDiscretization::BinIndexArray
    bin_indices;

  MonteCarlo::PhotonState photon( 0 );
  photon.setSourceEnergy( 1e-15 );
  
  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  photon.setSourceEnergy( 1e-5 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  photon.setSourceEnergy( 5e-5 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  photon.setSourceEnergy( 1e-4 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  photon.setSourceEnergy( 5e-4 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  photon.setSourceEnergy( 1e-3 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  // Check that line bins indices are calculated correctly
  photon.setSourceEnergy( 1e-15 );
  
  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  photon.setSourceEnergy( 1e-5 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  photon.setSourceEnergy( 5e-5 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  photon.setSourceEnergy( 1e-4 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  photon.setSourceEnergy( 5e-4 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  photon.setSourceEnergy( 9.9999999999999e-4 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  photon.setSourceEnergy( 1e-3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 3 );

  photon.setSourceEnergy( 1.0000000000001e-3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 4 );

  photon.setSourceEnergy( 5e-3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 4 );

  photon.setSourceEnergy( 1e-2 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 4 );

  photon.setSourceEnergy( 5e-2 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 5 );

  photon.setSourceEnergy( 9.999999999999e-2 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 5 );

  photon.setSourceEnergy( 1e-1 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 6 );

  photon.setSourceEnergy( 1.000000000001e-1 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 7 );

  photon.setSourceEnergy( 0.5 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 7 );

  photon.setSourceEnergy( 1.0 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 7 );
}

//---------------------------------------------------------------------------//
// Check that a bin index can be calculated
FRENSIE_UNIT_TEST( ObserverSourceEnergyDimensionDiscretization,
                   calculateBinIndicesOfValue_weights_wrapper )
{
  MonteCarlo::ObserverSourceEnergyDimensionDiscretization::BinIndexWeightPairArray
    bin_indices_and_weights;

  MonteCarlo::PhotonState photon( 0 );
  photon.setSourceEnergy( 1e-15 );
  
  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 1e-5 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 5e-5 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 1e-4 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 5e-4 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 1e-3 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  // Check that line bins indices are calculated correctly
  photon.setSourceEnergy( 1e-15 );
  
  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 1e-5 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 5e-5 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 1e-4 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 5e-4 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 9.9999999999999e-4 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 1e-3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 3 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 1.0000000000001e-3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 4 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 5e-3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 4 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 1e-2 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 4 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 5e-2 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 5 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 9.999999999999e-2 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 5 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 1e-1 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 6 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 1.000000000001e-1 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 7 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 0.5 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 7 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 1.0 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 7 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the bin indices of a range can be calculated
FRENSIE_UNIT_TEST( ObserverSourceEnergyDimensionDiscretization,
                   calculateBinIndicesOfRange )
{
  MonteCarlo::ObserverSourceEnergyDimensionDiscretization::BinIndexWeightPairArray
    bin_indices_and_weights;

  MonteCarlo::PhotonState photon( 0 );
  photon.setSourceEnergy( 1e-15 );
  
  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 1e-5 );

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 5e-5 );

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 1e-4 );

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 5e-4 );

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 1e-3 );

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  // Check that line bins indices are calculated correctly
  photon.setSourceEnergy( 1e-15 );
  
  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 1e-5 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 5e-5 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 1e-4 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 5e-4 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 9.9999999999999e-4 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 1e-3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 3 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 1.0000000000001e-3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 4 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 5e-3 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 4 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 1e-2 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 4 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 5e-2 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 5 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 9.999999999999e-2 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 5 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 1e-1 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 6 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 1.000000000001e-1 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 7 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 0.5 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 7 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setSourceEnergy( 1.0 );

  dimension_discretization_with_line_bins->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 7 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the boundaries of a bin can be printed
FRENSIE_UNIT_TEST( ObserverSourceEnergyDimensionDiscretization,
                   printBoundariesOfBin )
{
  std::ostringstream oss;

  dimension_discretization->printBoundariesOfBin( oss, 0 );

  FRENSIE_CHECK( oss.str().find( "Source Energy Bin:" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "[" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "," ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "]" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  dimension_discretization->printBoundariesOfBin( oss, 1 );

  FRENSIE_CHECK( oss.str().find( "Source Energy Bin:" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "(" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "," ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "]" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  dimension_discretization->printBoundariesOfBin( oss, 2 );

  FRENSIE_CHECK( oss.str().find( "Source Energy Bin:" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "(" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "," ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "]" ) < oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that the discretization can be printed
FRENSIE_UNIT_TEST( ObserverSourceEnergyDimensionDiscretization, print )
{
  std::ostringstream oss;

  dimension_discretization->print( oss );

  FRENSIE_CHECK( oss.str().find( "Source Energy Bin Boundaries:" ) <
                 oss.str().size() );

  std::cout << oss.str() << std::endl;
}

//---------------------------------------------------------------------------//
// Check that a discretization can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ObserverSourceEnergyDimensionDiscretization,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_observer_source_energy_dimension_discretization" );
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

  MonteCarlo::ObserverSourceEnergyDimensionDiscretization::BinIndexArray
    bin_indices;

  discretization->calculateBinIndicesOfValue( boost::any(0.0), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  discretization->calculateBinIndicesOfValue( boost::any(1e-5), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  discretization->calculateBinIndicesOfValue( boost::any(5e-5), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  discretization->calculateBinIndicesOfValue( boost::any(1e-4), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  discretization->calculateBinIndicesOfValue( boost::any(5e-4), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  discretization->calculateBinIndicesOfValue( boost::any(1e-3), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  MonteCarlo::ObserverSourceEnergyDimensionDiscretization::InputDataType discretization( 4 );

  discretization[0] = 0.0;
  discretization[1] = 1e-5;
  discretization[2] = 1e-4;
  discretization[3] = 1e-3;

  dimension_discretization.reset( new MonteCarlo::ObserverSourceEnergyDimensionDiscretization( discretization ) );

  discretization.resize( 9 );

  discretization[4] = 1e-3;
  discretization[5] = 1e-2;
  discretization[6] = 1e-1;
  discretization[7] = 1e-1;
  discretization[8] = 1.0;

  dimension_discretization_with_line_bins.reset( new MonteCarlo::ObserverSourceEnergyDimensionDiscretization( discretization ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstObserverSourceEneryDimensionDiscretization.cpp
//---------------------------------------------------------------------------//
