//---------------------------------------------------------------------------//
//!
//! \file   tstObserverDirectionDimensionDiscretization.cpp
//! \author Philip Britt
//! \brief  Observer direction dimension discretization unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_PQLATypeObserverDirectionDimensionDiscretization.hpp"
#include "MonteCarlo_ObserverParticleStateWrapper.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::ObserverPhaseSpaceDimensionDiscretization>
direction_discretization_forward, direction_discretization_reverse;

unsigned PQLA_order, number_of_triangles_per_side;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the discretized dimension can be returned
FRENSIE_UNIT_TEST( ObserverDirectionDimensionDiscretization, getDimension )
{
  FRENSIE_CHECK_EQUAL( direction_discretization_forward->getDimension(),
                       MonteCarlo::OBSERVER_DIRECTION_DIMENSION );
  FRENSIE_CHECK_EQUAL( direction_discretization_reverse->getDimension(),
                       MonteCarlo::OBSERVER_DIRECTION_DIMENSION );
}

// Check that the discretized dimension name can be returned
FRENSIE_UNIT_TEST( ObserverDirectionDimensionDiscretization, getDimensionName )
{
  FRENSIE_CHECK_EQUAL( direction_discretization_forward->getDimensionName(),
                       "Direction" );
  FRENSIE_CHECK_EQUAL( direction_discretization_reverse->getDimensionName(),
                       "Direction" );
}

// Check particle in discretization functions. Always return true.
FRENSIE_UNIT_TEST( ObserverDirectionDimensionDiscretization, isValueInDiscretization_wrapper )
{
  MonteCarlo::PhotonState photon( 0 );

  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  FRENSIE_CHECK(direction_discretization_forward->isValueInDiscretization(photon_wrapper))

  FRENSIE_CHECK(direction_discretization_reverse->isValueInDiscretization(photon_wrapper))
}

// Check particle in discretization functions. Always return true.
FRENSIE_UNIT_TEST( ObserverDirectionDimensionDiscretization, doesRangeIntersectDiscretization_wrapper )
{
  MonteCarlo::PhotonState photon( 0 );

  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  FRENSIE_CHECK(direction_discretization_forward->doesRangeIntersectDiscretization(photon_wrapper))

  FRENSIE_CHECK(direction_discretization_reverse->doesRangeIntersectDiscretization(photon_wrapper))
}

// PQLA get number of bins check
FRENSIE_UNIT_TEST( ObserverDirectionDimensionDiscretization, getNumberOfBins)
{
  FRENSIE_CHECK_EQUAL(direction_discretization_forward->getNumberOfBins(), 8*number_of_triangles_per_side)
  FRENSIE_CHECK_EQUAL(direction_discretization_reverse->getNumberOfBins(), 8*number_of_triangles_per_side)
}

// PQLA get number of bins check
FRENSIE_UNIT_TEST( ObserverDirectionDimensionDiscretization, calculateBinIndicesOfValue_wrapper)
{
  MonteCarlo::PQLATypeObserverDirectionDimensionDiscretization::BinIndexArray
    bin_indices;

  MonteCarlo::PhotonState photon( 0 );
  double direction[3] = {-1, -1, 2};

  Utility::normalizeVector(direction);

  photon.setDirection(direction);

  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  direction_discretization_forward->calculateBinIndicesOfValue(photon_wrapper, bin_indices);

  FRENSIE_CHECK_EQUAL(bin_indices.size(), 1);
  FRENSIE_CHECK_EQUAL(bin_indices.front(), 3+(3*number_of_triangles_per_side));

  direction[0] = 1;
  direction[1] = 1;
  direction[2] = -2;

  Utility::normalizeVector(direction);

  photon.setDirection(direction);

  direction_discretization_reverse->calculateBinIndicesOfValue(photon_wrapper, bin_indices);

  FRENSIE_CHECK_EQUAL(bin_indices.size(), 1);
  FRENSIE_CHECK_EQUAL(bin_indices.front(), 3+(3*number_of_triangles_per_side)); 

}

// PQLA get number of bins check
FRENSIE_UNIT_TEST( ObserverDirectionDimensionDiscretization, calculateBinIndicesOfValue_weights)
{
  MonteCarlo::PQLATypeObserverDirectionDimensionDiscretization::BinIndexWeightPairArray
    bin_indices_and_weights;

  MonteCarlo::PhotonState photon( 0 );
  double direction[3] = {-1, -1, 2};

  Utility::normalizeVector(direction);

  photon.setDirection(direction);

  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  direction_discretization_forward->calculateBinIndicesOfValue(photon_wrapper, bin_indices_and_weights);

  FRENSIE_CHECK_EQUAL(bin_indices_and_weights.size(), 1);
  FRENSIE_CHECK_EQUAL(bin_indices_and_weights.front().first, 3+(3*number_of_triangles_per_side));
  FRENSIE_CHECK_EQUAL(bin_indices_and_weights.front().second, 1.0);

  direction[0] = 1;
  direction[1] = 1;
  direction[2] = -2;

  Utility::normalizeVector(direction);

  photon.setDirection(direction);

  direction_discretization_reverse->calculateBinIndicesOfValue(photon_wrapper, bin_indices_and_weights);

  FRENSIE_CHECK_EQUAL(bin_indices_and_weights.size(), 1);
  FRENSIE_CHECK_EQUAL(bin_indices_and_weights.front().first, 3+(3*number_of_triangles_per_side)); 
  FRENSIE_CHECK_EQUAL(bin_indices_and_weights.front().second, 1.0);

}

// PQLA get number of bins check
FRENSIE_UNIT_TEST( ObserverDirectionDimensionDiscretization, calculateBinIndicesOfRange)
{
  MonteCarlo::PQLATypeObserverDirectionDimensionDiscretization::BinIndexWeightPairArray
    bin_indices_and_weights;

  MonteCarlo::PhotonState photon( 0 );
  double direction[3] = {-1, -1, 2};

  Utility::normalizeVector(direction);

  photon.setDirection(direction);

  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  direction_discretization_forward->calculateBinIndicesOfRange(photon_wrapper, bin_indices_and_weights);

  FRENSIE_CHECK_EQUAL(bin_indices_and_weights.size(), 1);
  FRENSIE_CHECK_EQUAL(bin_indices_and_weights.front().first, 3+(3*number_of_triangles_per_side));
  FRENSIE_CHECK_EQUAL(bin_indices_and_weights.front().second, 1.0);

  direction[0] = 1;
  direction[1] = 1;
  direction[2] = -2;

  Utility::normalizeVector(direction);

  photon.setDirection(direction);

  direction_discretization_reverse->calculateBinIndicesOfRange(photon_wrapper, bin_indices_and_weights);

  FRENSIE_CHECK_EQUAL(bin_indices_and_weights.size(), 1);
  FRENSIE_CHECK_EQUAL(bin_indices_and_weights.front().first, 3+(3*number_of_triangles_per_side)); 
  FRENSIE_CHECK_EQUAL(bin_indices_and_weights.front().second, 1.0);

}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  PQLA_order = 3;
  number_of_triangles_per_side = PQLA_order*PQLA_order;
  direction_discretization_forward.reset(new MonteCarlo::PQLATypeObserverDirectionDimensionDiscretization(PQLA_order, true));
  // Reverse binning used for VR purposes
  direction_discretization_reverse.reset(new MonteCarlo::PQLATypeObserverDirectionDimensionDiscretization(PQLA_order, false));

}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstObserverSourceEneryDimensionDiscretization.cpp
//---------------------------------------------------------------------------//
