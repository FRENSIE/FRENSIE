//---------------------------------------------------------------------------//
//!
//! \file   tstObserverPhaseSpaceDiscretization.cpp
//! \author Alex Robinson
//! \brief  The observer phase space discretization unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ObserverPhaseSpaceDiscretization.hpp"
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
  cosine_dimension_discretization,
  source_energy_dimension_discretization,
  energy_dimension_discretization,
  source_time_dimension_discretization,
  time_dimension_discretization,
  collision_number_dimension_discretization,
  source_id_dimension_discretization;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a discretization can be assigned to a dimension
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDiscretization,
                   assignDiscretizationToDimension )
{
  MonteCarlo::ObserverPhaseSpaceDiscretization phase_space_discretization;

  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_COSINE_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_TIME_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION ) );
  
  phase_space_discretization.assignDiscretizationToDimension(
                                             cosine_dimension_discretization );

  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_COSINE_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_TIME_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION ) );

  phase_space_discretization.assignDiscretizationToDimension(
                                      source_energy_dimension_discretization );

  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_COSINE_DIMENSION ) );
  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_TIME_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION ) );

  phase_space_discretization.assignDiscretizationToDimension(
                                             energy_dimension_discretization );

  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_COSINE_DIMENSION ) );
  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_TIME_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION ) );

  phase_space_discretization.assignDiscretizationToDimension(
                                        source_time_dimension_discretization );

  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_COSINE_DIMENSION ) );
  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_TIME_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION ) );

  phase_space_discretization.assignDiscretizationToDimension(
                                               time_dimension_discretization );

  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_COSINE_DIMENSION ) );
  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION ) );
  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_TIME_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION ) );

  phase_space_discretization.assignDiscretizationToDimension(
                                   collision_number_dimension_discretization );

  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_COSINE_DIMENSION ) );
  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION ) );
  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_TIME_DIMENSION ) );
  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ) );
  FRENSIE_CHECK( !phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION ) );

  phase_space_discretization.assignDiscretizationToDimension(
                                          source_id_dimension_discretization );

  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_COSINE_DIMENSION ) );
  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION ) );
  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_TIME_DIMENSION ) );
  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ) );
  FRENSIE_CHECK( phase_space_discretization.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION ) );
}

//---------------------------------------------------------------------------//
// Check that the discretized dimension can be returned
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDiscretization,
                   getDiscretizedDimensions_set )
{
  MonteCarlo::ObserverPhaseSpaceDiscretization phase_space_discretization;

  std::set<MonteCarlo::ObserverPhaseSpaceDimension>
    discretized_dimensions;
  
  phase_space_discretization.getDiscretizedDimensions( discretized_dimensions );

  FRENSIE_REQUIRE( discretized_dimensions.empty() );
  
  phase_space_discretization.assignDiscretizationToDimension(
                                             cosine_dimension_discretization );

  phase_space_discretization.getDiscretizedDimensions( discretized_dimensions );

  FRENSIE_REQUIRE_EQUAL( discretized_dimensions.size(), 1 );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_COSINE_DIMENSION ) );

  discretized_dimensions.clear();

  phase_space_discretization.assignDiscretizationToDimension(
                                      source_energy_dimension_discretization );

  phase_space_discretization.getDiscretizedDimensions( discretized_dimensions );

  FRENSIE_REQUIRE_EQUAL( discretized_dimensions.size(), 2 );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_COSINE_DIMENSION ) );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION ) );

  discretized_dimensions.clear();

  phase_space_discretization.assignDiscretizationToDimension(
                                             energy_dimension_discretization );

  phase_space_discretization.getDiscretizedDimensions( discretized_dimensions );

  FRENSIE_REQUIRE_EQUAL( discretized_dimensions.size(), 3 );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_COSINE_DIMENSION ) );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_ENERGY_DIMENSION ) );

  discretized_dimensions.clear();

  phase_space_discretization.assignDiscretizationToDimension(
                                        source_time_dimension_discretization );

  phase_space_discretization.getDiscretizedDimensions( discretized_dimensions );

  FRENSIE_REQUIRE_EQUAL( discretized_dimensions.size(), 4 );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_COSINE_DIMENSION ) );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION ) );

  discretized_dimensions.clear();

  phase_space_discretization.assignDiscretizationToDimension(
                                               time_dimension_discretization );

  phase_space_discretization.getDiscretizedDimensions( discretized_dimensions );

  FRENSIE_REQUIRE_EQUAL( discretized_dimensions.size(), 5 );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_COSINE_DIMENSION ) );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION ) );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_TIME_DIMENSION ) );

  discretized_dimensions.clear();

  phase_space_discretization.assignDiscretizationToDimension(
                                   collision_number_dimension_discretization );

  phase_space_discretization.getDiscretizedDimensions( discretized_dimensions );

  FRENSIE_REQUIRE_EQUAL( discretized_dimensions.size(), 6 );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_COSINE_DIMENSION ) );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION ) );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_TIME_DIMENSION ) );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ) );

  discretized_dimensions.clear();

  phase_space_discretization.assignDiscretizationToDimension(
                                          source_id_dimension_discretization );

  phase_space_discretization.getDiscretizedDimensions( discretized_dimensions );

  FRENSIE_REQUIRE_EQUAL( discretized_dimensions.size(), 7 );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_COSINE_DIMENSION ) );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_ENERGY_DIMENSION ) );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION ) );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_TIME_DIMENSION ) );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ) );
  FRENSIE_CHECK( discretized_dimensions.count( MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION ) );

  discretized_dimensions.clear();
}

//---------------------------------------------------------------------------//
// Check that the discretized dimension can be returned
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDiscretization,
                   getDiscretizedDimensions_vector )
{
  MonteCarlo::ObserverPhaseSpaceDiscretization phase_space_discretization;

  std::vector<MonteCarlo::ObserverPhaseSpaceDimension>
    discretized_dimensions;
  
  phase_space_discretization.getDiscretizedDimensions( discretized_dimensions );

  FRENSIE_REQUIRE( discretized_dimensions.empty() );
  
  phase_space_discretization.assignDiscretizationToDimension(
                                             cosine_dimension_discretization );

  phase_space_discretization.getDiscretizedDimensions( discretized_dimensions );

  FRENSIE_REQUIRE_EQUAL( discretized_dimensions.size(), 1 );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[0], MonteCarlo::OBSERVER_COSINE_DIMENSION );

  discretized_dimensions.clear();

  phase_space_discretization.assignDiscretizationToDimension(
                                      source_energy_dimension_discretization );

  phase_space_discretization.getDiscretizedDimensions( discretized_dimensions );

  FRENSIE_REQUIRE_EQUAL( discretized_dimensions.size(), 2 );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[0], MonteCarlo::OBSERVER_COSINE_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[1], MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION );

  discretized_dimensions.clear();

  phase_space_discretization.assignDiscretizationToDimension(
                                             energy_dimension_discretization );

  phase_space_discretization.getDiscretizedDimensions( discretized_dimensions );

  FRENSIE_REQUIRE_EQUAL( discretized_dimensions.size(), 3 );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[0], MonteCarlo::OBSERVER_COSINE_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[1], MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[2], MonteCarlo::OBSERVER_ENERGY_DIMENSION );

  discretized_dimensions.clear();

  phase_space_discretization.assignDiscretizationToDimension(
                                        source_time_dimension_discretization );

  phase_space_discretization.getDiscretizedDimensions( discretized_dimensions );

  FRENSIE_REQUIRE_EQUAL( discretized_dimensions.size(), 4 );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[0], MonteCarlo::OBSERVER_COSINE_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[1], MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[2], MonteCarlo::OBSERVER_ENERGY_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[3], MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION );

  discretized_dimensions.clear();

  phase_space_discretization.assignDiscretizationToDimension(
                                               time_dimension_discretization );

  phase_space_discretization.getDiscretizedDimensions( discretized_dimensions );

  FRENSIE_REQUIRE_EQUAL( discretized_dimensions.size(), 5 );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[0], MonteCarlo::OBSERVER_COSINE_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[1], MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[2], MonteCarlo::OBSERVER_ENERGY_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[3], MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[4], MonteCarlo::OBSERVER_TIME_DIMENSION );

  discretized_dimensions.clear();

  phase_space_discretization.assignDiscretizationToDimension(
                                   collision_number_dimension_discretization );

  phase_space_discretization.getDiscretizedDimensions( discretized_dimensions );

  FRENSIE_REQUIRE_EQUAL( discretized_dimensions.size(), 6 );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[0], MonteCarlo::OBSERVER_COSINE_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[1], MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[2], MonteCarlo::OBSERVER_ENERGY_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[3], MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[4], MonteCarlo::OBSERVER_TIME_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[5], MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION );

  discretized_dimensions.clear();

  phase_space_discretization.assignDiscretizationToDimension(
                                          source_id_dimension_discretization );

  phase_space_discretization.getDiscretizedDimensions( discretized_dimensions );

  FRENSIE_REQUIRE_EQUAL( discretized_dimensions.size(), 7 );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[0], MonteCarlo::OBSERVER_COSINE_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[1], MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[2], MonteCarlo::OBSERVER_ENERGY_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[3], MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[4], MonteCarlo::OBSERVER_TIME_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[5], MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[6], MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION );

  discretized_dimensions.clear();
}

//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDiscretization, getNumberOfBins )
{
  MonteCarlo::ObserverPhaseSpaceDiscretization phase_space_discretization;

  FRENSIE_REQUIRE_EQUAL( phase_space_discretization.getNumberOfBins(), 1 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_COSINE_DIMENSION ), 1 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION ), 1 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_ENERGY_DIMENSION ), 1 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION ), 1 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_TIME_DIMENSION ), 1 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ), 1 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION ), 1 );

  phase_space_discretization.assignDiscretizationToDimension( cosine_dimension_discretization );

  FRENSIE_REQUIRE_EQUAL( phase_space_discretization.getNumberOfBins(), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_COSINE_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION ), 1 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_ENERGY_DIMENSION ), 1 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION ), 1 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_TIME_DIMENSION ), 1 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ), 1 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION ), 1 );

  phase_space_discretization.assignDiscretizationToDimension( source_energy_dimension_discretization );

  FRENSIE_REQUIRE_EQUAL( phase_space_discretization.getNumberOfBins(), 9 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_COSINE_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_ENERGY_DIMENSION ), 1 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION ), 1 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_TIME_DIMENSION ), 1 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ), 1 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION ), 1 );

  phase_space_discretization.assignDiscretizationToDimension( energy_dimension_discretization );

  FRENSIE_REQUIRE_EQUAL( phase_space_discretization.getNumberOfBins(), 27 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_COSINE_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_ENERGY_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION ), 1 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_TIME_DIMENSION ), 1 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ), 1 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION ), 1 );

  phase_space_discretization.assignDiscretizationToDimension( source_time_dimension_discretization );

  FRENSIE_REQUIRE_EQUAL( phase_space_discretization.getNumberOfBins(), 81 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_COSINE_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_ENERGY_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_TIME_DIMENSION ), 1 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ), 1 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION ), 1 );

  phase_space_discretization.assignDiscretizationToDimension( time_dimension_discretization );

  FRENSIE_REQUIRE_EQUAL( phase_space_discretization.getNumberOfBins(), 243 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_COSINE_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_ENERGY_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_TIME_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ), 1 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION ), 1 );

  phase_space_discretization.assignDiscretizationToDimension( collision_number_dimension_discretization );

  FRENSIE_REQUIRE_EQUAL( phase_space_discretization.getNumberOfBins(), 972 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_COSINE_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_ENERGY_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_TIME_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ), 4 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION ), 1 );

  phase_space_discretization.assignDiscretizationToDimension( source_id_dimension_discretization );

  FRENSIE_REQUIRE_EQUAL( phase_space_discretization.getNumberOfBins(), 2916 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_COSINE_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_ENERGY_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_TIME_DIMENSION ), 3 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ), 4 );
  FRENSIE_CHECK_EQUAL( phase_space_discretization.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION ), 3 );
}

//---------------------------------------------------------------------------//
// Check if a point is in the phase space discretization
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDiscretization,
                   isPointInDiscretization_map )
{
  MonteCarlo::ObserverPhaseSpaceDiscretization phase_space_discretization;

  typedef MonteCarlo::ObserverPhaseSpaceDimensionTraits<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION> CNDT;
  typedef MonteCarlo::ObserverPhaseSpaceDimensionTraits<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION> SIDT;

  {
    MonteCarlo::ObserverPhaseSpaceDiscretization::DimensionValueMap
      phase_space_point;

    FRENSIE_CHECK( phase_space_discretization.isPointInDiscretization( phase_space_point ) );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0 );
    phase_space_point[MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION] =
      boost::any( 1e-6 );
    phase_space_point[MonteCarlo::OBSERVER_ENERGY_DIMENSION] =
      boost::any( 1e-6 );
    phase_space_point[MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION] =
      boost::any( 1e-6 );
    phase_space_point[MonteCarlo::OBSERVER_TIME_DIMENSION] =
      boost::any( 1e-6 );
    phase_space_point[MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION] =
      boost::any( (CNDT::dimensionType)0 );
    phase_space_point[MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION] =
      boost::any( (SIDT::dimensionType)0 );

    FRENSIE_CHECK( phase_space_discretization.isPointInDiscretization( phase_space_point ) );
  }

  phase_space_discretization.assignDiscretizationToDimension( cosine_dimension_discretization );

  {
    MonteCarlo::ObserverPhaseSpaceDiscretization::DimensionValueMap
      phase_space_point;
    
    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -2.0 );

    FRENSIE_CHECK( !phase_space_discretization.isPointInDiscretization( phase_space_point ) );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0 );

    FRENSIE_CHECK( phase_space_discretization.isPointInDiscretization( phase_space_point ) );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0 );

    FRENSIE_CHECK( phase_space_discretization.isPointInDiscretization( phase_space_point ) );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 2.0 );

    FRENSIE_CHECK( !phase_space_discretization.isPointInDiscretization( phase_space_point ) );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -2.0 );
    phase_space_point[MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION] =
      boost::any( 1e-6 );
    phase_space_point[MonteCarlo::OBSERVER_ENERGY_DIMENSION] =
      boost::any( 1e-6 );
    phase_space_point[MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION] =
      boost::any( 1e-6 );
    phase_space_point[MonteCarlo::OBSERVER_TIME_DIMENSION] =
      boost::any( 1e-6 );
    phase_space_point[MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION] =
      boost::any( (CNDT::dimensionType)0 );
    phase_space_point[MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION] =
      boost::any( (SIDT::dimensionType)0 );

    FRENSIE_CHECK( !phase_space_discretization.isPointInDiscretization( phase_space_point ) );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0 );

    FRENSIE_CHECK( phase_space_discretization.isPointInDiscretization( phase_space_point ) );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0 );

    FRENSIE_CHECK( phase_space_discretization.isPointInDiscretization( phase_space_point ) );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 2.0 );

    FRENSIE_CHECK( !phase_space_discretization.isPointInDiscretization( phase_space_point ) );
  }

  phase_space_discretization.assignDiscretizationToDimension( source_energy_dimension_discretization );
  
  {
    MonteCarlo::ObserverPhaseSpaceDiscretization::DimensionValueMap
      phase_space_point;
    
    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -2.0 );
    phase_space_point[MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION] =
      boost::any( -1.0 );

    FRENSIE_CHECK( !phase_space_discretization.isPointInDiscretization( phase_space_point ) );

    phase_space_point[MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION] =
      boost::any( 0.0 );

    FRENSIE_CHECK( !phase_space_discretization.isPointInDiscretization( phase_space_point ) );

    phase_space_point[MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION] =
      boost::any( 1e-3 );

    FRENSIE_CHECK( !phase_space_discretization.isPointInDiscretization( phase_space_point ) );

    phase_space_point[MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION] =
      boost::any( 5e-3 );

    FRENSIE_CHECK( !phase_space_discretization.isPointInDiscretization( phase_space_point ) );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 0.0 );
    phase_space_point[MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION] =
      boost::any( -1.0 );

    FRENSIE_CHECK( !phase_space_discretization.isPointInDiscretization( phase_space_point ) );

    phase_space_point[MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION] =
      boost::any( 0.0 );

    FRENSIE_CHECK( phase_space_discretization.isPointInDiscretization( phase_space_point ) );

    phase_space_point[MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION] =
      boost::any( 1e-3 );

    FRENSIE_CHECK( phase_space_discretization.isPointInDiscretization( phase_space_point ) );

    phase_space_point[MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION] =
      boost::any( 5e-3 );

    FRENSIE_CHECK( !phase_space_discretization.isPointInDiscretization( phase_space_point ) );
  }
}

//---------------------------------------------------------------------------//
// Check if a point is in the phase space discretization
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDiscretization,
                   isPointInDiscretization_wrapper )
{
  MonteCarlo::ObserverPhaseSpaceDiscretization phase_space_discretization;

  {
    MonteCarlo::PhotonState photon( 0 );
    MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

    FRENSIE_CHECK( phase_space_discretization.isPointInDiscretization( photon_wrapper ) );

    photon.setSourceEnergy( 1.0 );
    photon.setEnergy( 0.5 );
    photon.setSourceTime( 0.0 );
    photon.setTime( 1e-9 );
    photon.incrementCollisionNumber();
    photon.setSourceId( 10 );
    photon_wrapper.setAngleCosine( -1.0 );
    
    FRENSIE_CHECK( phase_space_discretization.isPointInDiscretization( photon_wrapper ) );
  }

  phase_space_discretization.assignDiscretizationToDimension( cosine_dimension_discretization );

  {
    MonteCarlo::PhotonState photon( 0 );
    MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

    photon_wrapper.setAngleCosine( -1.0 );

    FRENSIE_CHECK( phase_space_discretization.isPointInDiscretization( photon_wrapper ) );

    photon_wrapper.setAngleCosine( 0.0 );

    FRENSIE_CHECK( phase_space_discretization.isPointInDiscretization( photon_wrapper ) );

    photon_wrapper.setAngleCosine( 1.0 );

    FRENSIE_CHECK( phase_space_discretization.isPointInDiscretization( photon_wrapper ) );

    photon.setSourceEnergy( 1.0 );
    photon.setEnergy( 0.5 );
    photon.setSourceTime( 0.0 );
    photon.setTime( 1e-9 );
    photon.incrementCollisionNumber();
    photon.setSourceId( 10 );
    photon_wrapper.setAngleCosine( -1.0 );

    FRENSIE_CHECK( phase_space_discretization.isPointInDiscretization( photon_wrapper ) );

    photon_wrapper.setAngleCosine( 0.0 );

    FRENSIE_CHECK( phase_space_discretization.isPointInDiscretization( photon_wrapper ) );

    photon_wrapper.setAngleCosine( 1.0 );

    FRENSIE_CHECK( phase_space_discretization.isPointInDiscretization( photon_wrapper ) );

  }

  phase_space_discretization.assignDiscretizationToDimension( time_dimension_discretization );
  
  {
    MonteCarlo::PhotonState photon( 0 );
    MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

    photon.setTime( 0.0 );
    photon_wrapper.setAngleCosine( -1.0 );
        
    FRENSIE_CHECK( !phase_space_discretization.isPointInDiscretization( photon_wrapper ) );

    photon.setTime( 1e-6 );

    FRENSIE_CHECK( phase_space_discretization.isPointInDiscretization( photon_wrapper ) );

    photon.setTime( 1e-3 );

    FRENSIE_CHECK( phase_space_discretization.isPointInDiscretization( photon_wrapper ) );

    photon.setTime( 5e-3 );

    FRENSIE_CHECK( !phase_space_discretization.isPointInDiscretization( photon_wrapper ) );

    photon.setTime( 0.0 );
    photon_wrapper.setAngleCosine( -1.0 );

    FRENSIE_CHECK( !phase_space_discretization.isPointInDiscretization( photon_wrapper ) );

    photon.setTime( 1e-6 );

    FRENSIE_CHECK( phase_space_discretization.isPointInDiscretization( photon_wrapper ) );

    photon.setTime( 1e-3 );

    FRENSIE_CHECK( phase_space_discretization.isPointInDiscretization( photon_wrapper ) );

    photon.setTime( 5e-3 );

    FRENSIE_CHECK( !phase_space_discretization.isPointInDiscretization( photon_wrapper ) );
  }
}

//---------------------------------------------------------------------------//
// Check if a range intersects the phase space discretization
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDiscretization,
                   doesRangeIntersectDiscretization )
{
  MonteCarlo::ObserverPhaseSpaceDiscretization phase_space_discretization;

  {
    MonteCarlo::PhotonState photon( 0 );
    MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

    FRENSIE_CHECK( phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );

    photon.setSourceEnergy( 1.0 );
    photon.setEnergy( 0.5 );
    photon.setSourceTime( 0.0 );
    photon.setTime( 1e-9 );
    photon.incrementCollisionNumber();
    photon.setSourceId( 10 );
    photon_wrapper.setAngleCosine( -1.0 );
    
    FRENSIE_CHECK( phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );
  }

  phase_space_discretization.assignDiscretizationToDimension( time_dimension_discretization, true );

  {
    MonteCarlo::PhotonState photon( 0 );
    MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

    // The range is below the lowest bin boundary
    photon.setTime( 0.0 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 2997.92458 );

    FRENSIE_CHECK( !phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );

    // The range ends on the lowest bin boundary
    photon.setTime( 1e-6 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsEndTime( 1.0 );
    
    FRENSIE_CHECK( !phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );
    
    // The lowest bin boundary intersects the range
    photon.setTime( 0.0 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896.22900000002 );
    
    FRENSIE_CHECK( phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );
    
    // The range lies within the lowest and highest bin boundaries
    photon.setTime( 5e-6 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 14839726.671 );
    
    FRENSIE_CHECK( phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );
    
    // The range extends below lowest bin boundary and above highest bin boundary
    photon.setTime( 0.0 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896229.0 );
    
    FRENSIE_CHECK( phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );
    
    // The highest bin boundary intersects the range
    photon.setTime( 1e-4 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 146898304.42 );

    FRENSIE_CHECK( phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );
    
    // The range starts on the highest bin boundary
    photon.setTime( 1e-3 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 1.0 );
    
    FRENSIE_CHECK( !phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );
  }

  phase_space_discretization.assignDiscretizationToDimension( energy_dimension_discretization );

  {
    MonteCarlo::PhotonState photon( 0 );
    MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

    // The range is below the lowest bin boundary
    photon.setEnergy( 1e-6 );
    photon.setTime( 0.0 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 2997.92458 );

    FRENSIE_CHECK( !phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );

    // The range ends on the lowest bin boundary
    photon.setTime( 1e-6 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsEndTime( 1.0 );
    
    FRENSIE_CHECK( !phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );
    
    // The lowest bin boundary intersects the range
    photon.setTime( 0.0 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896.22900000002 );
    
    FRENSIE_CHECK( phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );
    
    // The range lies within the lowest and highest bin boundaries
    photon.setTime( 5e-6 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 14839726.671 );
    
    FRENSIE_CHECK( phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );
    
    // The range extends below lowest bin boundary and above highest bin boundary
    photon.setTime( 0.0 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896229.0 );
    
    FRENSIE_CHECK( phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );
    
    // The highest bin boundary intersects the range
    photon.setTime( 1e-4 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 146898304.42 );

    FRENSIE_CHECK( phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );
    
    // The range starts on the highest bin boundary
    photon.setTime( 1e-3 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 1.0 );
    
    FRENSIE_CHECK( !phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );

    // The range is below the lowest bin boundary
    photon.setEnergy( 1e-3 );
    photon.setTime( 0.0 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 2997.92458 );

    FRENSIE_CHECK( !phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );

    // The range ends on the lowest bin boundary
    photon.setTime( 1e-6 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsEndTime( 1.0 );
    
    FRENSIE_CHECK( !phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );
    
    // The lowest bin boundary intersects the range
    photon.setTime( 0.0 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896.22900000002 );
    
    FRENSIE_CHECK( phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );
    
    // The range lies within the lowest and highest bin boundaries
    photon.setTime( 5e-6 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 14839726.671 );
    
    FRENSIE_CHECK( phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );
    
    // The range extends below lowest bin boundary and above highest bin boundary
    photon.setTime( 0.0 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896229.0 );
    
    FRENSIE_CHECK( phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );
    
    // The highest bin boundary intersects the range
    photon.setTime( 1e-4 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 146898304.42 );

    FRENSIE_CHECK( phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );
    
    // The range starts on the highest bin boundary
    photon.setTime( 1e-3 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 1.0 );
    
    FRENSIE_CHECK( !phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );

    // The range is below the lowest bin boundary
    photon.setEnergy( 5e-3 );
    photon.setTime( 0.0 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 2997.92458 );

    FRENSIE_CHECK( !phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );

    // The range ends on the lowest bin boundary
    photon.setTime( 1e-6 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsEndTime( 1.0 );
    
    FRENSIE_CHECK( !phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );
    
    // The lowest bin boundary intersects the range
    photon.setTime( 0.0 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896.22900000002 );
    
    FRENSIE_CHECK( !phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );
    
    // The range lies within the lowest and highest bin boundaries
    photon.setTime( 5e-6 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 14839726.671 );
    
    FRENSIE_CHECK( !phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );
    
    // The range extends below lowest bin boundary and above highest bin boundary
    photon.setTime( 0.0 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896229.0 );
    
    FRENSIE_CHECK( !phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );
    
    // The highest bin boundary intersects the range
    photon.setTime( 1e-4 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 146898304.42 );

    FRENSIE_CHECK( !phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );
    
    // The range starts on the highest bin boundary
    photon.setTime( 1e-3 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 1.0 );
    
    FRENSIE_CHECK( !phase_space_discretization.doesRangeIntersectDiscretization( photon_wrapper ) );
  }
}

//---------------------------------------------------------------------------//
// Check that the bin indices of a point can be calculated
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDiscretization,
                   calculateBinIndicesOfPoint_map )
{
  MonteCarlo::ObserverPhaseSpaceDiscretization phase_space_discretization;

  typedef MonteCarlo::ObserverPhaseSpaceDimensionTraits<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION> CNDT;
  typedef MonteCarlo::ObserverPhaseSpaceDimensionTraits<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION> SIDT;

  // No discretization
  {
    MonteCarlo::ObserverPhaseSpaceDiscretization::DimensionValueMap
      phase_space_point;

    MonteCarlo::ObserverPhaseSpaceDiscretization::BinIndexArray bin_indices;

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );

    bin_indices.clear();

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0 );
    phase_space_point[MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION] =
      boost::any( 1e-6 );
    phase_space_point[MonteCarlo::OBSERVER_ENERGY_DIMENSION] =
      boost::any( 1e-6 );
    phase_space_point[MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION] =
      boost::any( 1e-6 );
    phase_space_point[MonteCarlo::OBSERVER_TIME_DIMENSION] =
      boost::any( 1e-6 );
    phase_space_point[MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION] =
      boost::any( (CNDT::dimensionType)0 );
    phase_space_point[MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION] =
      boost::any( (SIDT::dimensionType)0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );
  }

  // Cosine bins only
  phase_space_discretization.assignDiscretizationToDimension( cosine_dimension_discretization );

  {
    MonteCarlo::ObserverPhaseSpaceDiscretization::DimensionValueMap
      phase_space_point;

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0 );

    MonteCarlo::ObserverPhaseSpaceDiscretization::BinIndexArray bin_indices;

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 0.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 1 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 1 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 2.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 2 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 2 );
  }

  // Cosine bins, collision number bins
  phase_space_discretization.assignDiscretizationToDimension( collision_number_dimension_discretization );

  {
    MonteCarlo::ObserverPhaseSpaceDiscretization::DimensionValueMap
      phase_space_point;

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0 );
    phase_space_point[MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION] =
      boost::any( (CNDT::dimensionType)0 );

    MonteCarlo::ObserverPhaseSpaceDiscretization::BinIndexArray bin_indices;

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 0.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 1 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 1 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 2.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 2 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 2 );

    // Increment the collision number
    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0 );
    phase_space_point[MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION] =
      boost::any( (CNDT::dimensionType)1 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 0.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 1 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 1 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 2.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 2 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 2 );

    // Increment the collision number
    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0 );
    phase_space_point[MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION] =
      boost::any( (CNDT::dimensionType)2 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 3 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 3 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 0.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 4 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 4 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 2.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 5 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 5 );

    // Increment the collision number
    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0 );
    phase_space_point[MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION] =
      boost::any( (CNDT::dimensionType)5 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 9 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 9 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 0.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 10 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 10 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 2.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 11 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 11 );
  }

  // Cosine bins, collision number bins, source id bins
  phase_space_discretization.assignDiscretizationToDimension( source_id_dimension_discretization );

  {
    MonteCarlo::ObserverPhaseSpaceDiscretization::DimensionValueMap
      phase_space_point;

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0 );
    phase_space_point[MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION] =
      boost::any( (CNDT::dimensionType)0 );
    phase_space_point[MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION] =
      boost::any( (SIDT::dimensionType)0 );

    MonteCarlo::ObserverPhaseSpaceDiscretization::BinIndexArray bin_indices;

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 12 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 12 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 0.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 13 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 13 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 2.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 14 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 14 );

    // Increment the collsion number
    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0 );
    phase_space_point[MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION] =
      boost::any( (CNDT::dimensionType)5 );
    phase_space_point[MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION] =
      boost::any( (SIDT::dimensionType)0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 9 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 21 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 9 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 21 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 0.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 10 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 22 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 10 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 22 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 2.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 11 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 23 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 11 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 23 );

    // Change the source id
    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0 );
    phase_space_point[MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION] =
      boost::any( (CNDT::dimensionType)0 );
    phase_space_point[MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION] =
      boost::any( (SIDT::dimensionType)1 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 12 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 24 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 12 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 24 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 0.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 13 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 25 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 13 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 25 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 2.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 14 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 26 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 14 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 26 );

    // Increment the collision number
    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0 );
    phase_space_point[MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION] =
      boost::any( (CNDT::dimensionType)5 );
    phase_space_point[MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION] =
      boost::any( (SIDT::dimensionType)1 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 21 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 33 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 21 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 33 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 0.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 22 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 34 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 22 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 34 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 2.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 23 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 35 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 23 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 35 );

    // Change the source id
    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0 );
    phase_space_point[MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION] =
      boost::any( (CNDT::dimensionType)0 );
    phase_space_point[MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION] =
      boost::any( (SIDT::dimensionType)2 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 24 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 24 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 0.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 25 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 25 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 2.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 26 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 26 );

    // Change the source id
    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0 );
    phase_space_point[MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION] =
      boost::any( (CNDT::dimensionType)5 );
    phase_space_point[MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION] =
      boost::any( (SIDT::dimensionType)2 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 33 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( -1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 33 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 0.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 34 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 34 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 2.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 35 );

    phase_space_point[MonteCarlo::OBSERVER_COSINE_DIMENSION] =
      boost::any( 1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( phase_space_point, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 35 );
  }
}

//---------------------------------------------------------------------------//
// Check that the bin indices of a point can be calculated
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDiscretization,
                   calculateBinIndicesOfPoint_wrapper )
{
  MonteCarlo::ObserverPhaseSpaceDiscretization phase_space_discretization;

  {
    MonteCarlo::PhotonState photon( 0 );
    MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

    MonteCarlo::ObserverPhaseSpaceDiscretization::BinIndexArray bin_indices;

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );

    photon.setSourceEnergy( 1.0 );
    photon.setEnergy( 1e-2 );
    photon.setSourceTime( 0.0 );
    photon.setTime( 1e-6 );
    photon.setSourceId( 10 );
    photon.incrementCollisionNumber();
    photon_wrapper.setAngleCosine( -1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );
  }

  // Cosine bins only
  phase_space_discretization.assignDiscretizationToDimension( cosine_dimension_discretization );

  {
    MonteCarlo::PhotonState photon( 0 );
    MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );
    photon_wrapper.setAngleCosine( -1.0 );

    MonteCarlo::ObserverPhaseSpaceDiscretization::BinIndexArray bin_indices;

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );

    photon_wrapper.setAngleCosine( -1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );

    photon_wrapper.setAngleCosine( 0.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 1 );

    photon_wrapper.setAngleCosine( 1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 1 );

    photon_wrapper.setAngleCosine( 2.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 2 );

    photon_wrapper.setAngleCosine( 1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 2 );
  }

  // Cosine bins, collision number bins
  phase_space_discretization.assignDiscretizationToDimension( collision_number_dimension_discretization );

  {
    MonteCarlo::PhotonState photon( 0 );
    MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );
    photon_wrapper.setAngleCosine( -1.0 );

    MonteCarlo::ObserverPhaseSpaceDiscretization::BinIndexArray bin_indices;

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );

    photon_wrapper.setAngleCosine( -1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );

    photon_wrapper.setAngleCosine( 0.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 1 );

    photon_wrapper.setAngleCosine( 1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 1 );

    photon_wrapper.setAngleCosine( 2.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 2 );

    photon_wrapper.setAngleCosine( 1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 2 );

    // Increment the collision number
    photon.incrementCollisionNumber();
    photon.incrementCollisionNumber();
    photon_wrapper.setAngleCosine( -1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 3 );

    photon_wrapper.setAngleCosine( -1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 3 );

    photon_wrapper.setAngleCosine( 0.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 4 );

    photon_wrapper.setAngleCosine( 1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 4 );

    photon_wrapper.setAngleCosine( 2.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 5 );

    photon_wrapper.setAngleCosine( 1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 5 );
  }

  // Cosine bins, collision number bins, source id bins
  phase_space_discretization.assignDiscretizationToDimension( source_id_dimension_discretization );

  {
    MonteCarlo::PhotonState photon( 0 );
    photon.setSourceId( 0 );
    
    MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );
    photon_wrapper.setAngleCosine( -1.0 );

    MonteCarlo::ObserverPhaseSpaceDiscretization::BinIndexArray bin_indices;

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 12 );

    photon_wrapper.setAngleCosine( -1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 12 );

    photon_wrapper.setAngleCosine( 0.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 13 );

    photon_wrapper.setAngleCosine( 1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 13 );

    photon_wrapper.setAngleCosine( 2.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 14 );

    photon_wrapper.setAngleCosine( 1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 14 );

    // Increment the collision number
    photon.incrementCollisionNumber();
    photon.incrementCollisionNumber();
    photon_wrapper.setAngleCosine( -1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 3 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 15 );

    photon_wrapper.setAngleCosine( -1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 3 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 15 );

    photon_wrapper.setAngleCosine( 0.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 4 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 16 );

    photon_wrapper.setAngleCosine( 1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 4 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 16 );

    photon_wrapper.setAngleCosine( 2.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 5 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 17 );

    photon_wrapper.setAngleCosine( 1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 5 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 17 );

    // Change the source id
    photon.setSourceId( 1 );
    photon_wrapper.setAngleCosine( -1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 15 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 27 );

    photon_wrapper.setAngleCosine( -1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 15 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 27 );

    photon_wrapper.setAngleCosine( 0.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 16 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 28 );

    photon_wrapper.setAngleCosine( 1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 16 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 28 );

    photon_wrapper.setAngleCosine( 2.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 17 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 29 );

    photon_wrapper.setAngleCosine( 1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 17 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 29 );

    // Increment the collision number
    photon.incrementCollisionNumber();

    photon_wrapper.setAngleCosine( -1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 18 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 30 );

    photon_wrapper.setAngleCosine( -1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 18 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 30 );

    photon_wrapper.setAngleCosine( 0.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 19 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 31 );

    photon_wrapper.setAngleCosine( 1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 19 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 31 );

    photon_wrapper.setAngleCosine( 2.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 20 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 32 );

    photon_wrapper.setAngleCosine( 1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 20 );
    FRENSIE_CHECK_EQUAL( bin_indices[1], 32 );

    // Change the source id
    photon.setSourceId( 2 );
    photon_wrapper.setAngleCosine( -1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 30 );

    photon_wrapper.setAngleCosine( -1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 30 );

    photon_wrapper.setAngleCosine( 0.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 31 );

    photon_wrapper.setAngleCosine( 1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 31 );

    photon_wrapper.setAngleCosine( 2.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 32 );

    photon_wrapper.setAngleCosine( 1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 32 );

    // Increment the collision number
    photon.incrementCollisionNumber();
    photon_wrapper.setAngleCosine( -1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 33 );

    photon_wrapper.setAngleCosine( -1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 33 );

    photon_wrapper.setAngleCosine( 0.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 34 );

    photon_wrapper.setAngleCosine( 1.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 34 );

    photon_wrapper.setAngleCosine( 2.0/3 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 35 );

    photon_wrapper.setAngleCosine( 1.0 );

    phase_space_discretization.calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 35 );
  }
}

//---------------------------------------------------------------------------//
// Check that the bin indices of a range can be calculated
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDiscretization,
                   calculateBinIndicesAndWeightsOfRange )
{
  MonteCarlo::ObserverPhaseSpaceDiscretization phase_space_discretization;

  {
    MonteCarlo::PhotonState photon( 0 );
    MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

    MonteCarlo::ObserverPhaseSpaceDiscretization::BinIndexWeightPairArray bin_indices_and_weights;

    phase_space_discretization.calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 0 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].second, 1.0 );

    photon.setSourceEnergy( 1.0 );
    photon.setEnergy( 1e-2 );
    photon.setSourceTime( 0.0 );
    photon.setTime( 1e-6 );
    photon.setSourceId( 10 );
    photon.incrementCollisionNumber();
    photon_wrapper.setAngleCosine( -1.0 );

    phase_space_discretization.calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 0 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].second, 1.0 );
  }

  // Time bins only
  phase_space_discretization.assignDiscretizationToDimension( time_dimension_discretization, true );

  {
    // The lowest bin boundary intersects the range
    MonteCarlo::PhotonState photon( 0 );
    photon.setTime( 0.0 );
    
    MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896.22900000002 );

    MonteCarlo::ObserverPhaseSpaceDiscretization::BinIndexWeightPairArray bin_indices_and_weights;

    phase_space_discretization.calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 0 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights.front().second,
                                     0.8,
                                     1e-15 );

    // The second bin boundary intersects the range
    photon.setTime( 2e-6 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 539626.4244 );

    phase_space_discretization.calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights.front().second,
                                     0.44444444444444453,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights.back().first, 1 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights.back().second,
                                     0.5555555555555556,
                                     1e-15 );

    // The highest bin boundary intersects the range
    photon.setTime( 5e-4 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 134906606.10000002 );

    phase_space_discretization.calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 2 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights.front().second,
                                     0.1111111111111111,
                                     1e-15 );

    // The range extends below lowest bin boundary and above highest bin boundary
    photon.setTime( 0.0 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896229.0 );

    phase_space_discretization.calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 3 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 0 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[0].second,
                                     0.0018,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].first, 1 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[1].second,
                                     0.018,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[2].first, 2 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[2].second,
                                     0.18,
                                     1e-15 );
  }

  // Time bins and source id bins
  phase_space_discretization.assignDiscretizationToDimension( source_id_dimension_discretization );

  {
    // The lowest bin boundary intersects the range
    MonteCarlo::PhotonState photon( 0 );
    photon.setTime( 0.0 );
    photon.setSourceId( 0 );
    
    MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896.22900000002 );

    MonteCarlo::ObserverPhaseSpaceDiscretization::BinIndexWeightPairArray bin_indices_and_weights;

    phase_space_discretization.calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 0 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[0].second,
                                     0.8,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].first, 3 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[1].second,
                                     0.8,
                                     1e-15 );

    // The second bin boundary intersects the range
    photon.setTime( 2e-6 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 539626.4244 );

    phase_space_discretization.calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 4 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 0 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[0].second,
                                     0.44444444444444453,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].first, 1 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[1].second,
                                     0.5555555555555556,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[2].first, 3 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[2].second,
                                     0.44444444444444453,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[3].first, 4 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[3].second,
                                     0.5555555555555556,
                                     1e-15 );

    // The highest bin boundary intersects the range
    photon.setTime( 5e-4 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 134906606.10000002 );

    phase_space_discretization.calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 2 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[0].second,
                                     0.1111111111111111,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].first, 5 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[1].second,
                                     0.1111111111111111,
                                     1e-15 );

    // The range extends below lowest bin boundary and above highest bin boundary
    photon.setTime( 0.0 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896229.0 );

    phase_space_discretization.calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 6 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 0 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[0].second,
                                     0.0018,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].first, 1 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[1].second,
                                     0.018,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[2].first, 2 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[2].second,
                                     0.18,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[3].first, 3 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[0].second,
                                     0.0018,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[4].first, 4 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[1].second,
                                     0.018,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[5].first, 5 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[2].second,
                                     0.18,
                                     1e-15 );
  }

  // Time bins, source id bins and collision number bins
  phase_space_discretization.assignDiscretizationToDimension( collision_number_dimension_discretization );

  {
    // The lowest bin boundary intersects the range
    MonteCarlo::PhotonState photon( 0 );
    photon.setTime( 0.0 );
    photon.setSourceId( 0 );
    
    MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896.22900000002 );

    MonteCarlo::ObserverPhaseSpaceDiscretization::BinIndexWeightPairArray bin_indices_and_weights;

    phase_space_discretization.calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 0 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[0].second,
                                     0.8,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].first, 3 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[1].second,
                                     0.8,
                                     1e-15 );

    // The second bin boundary intersects the range
    photon.setTime( 2e-6 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 539626.4244 );

    phase_space_discretization.calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 4 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 0 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[0].second,
                                     0.44444444444444453,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].first, 1 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[1].second,
                                     0.5555555555555556,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[2].first, 3 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[2].second,
                                     0.44444444444444453,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[3].first, 4 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[3].second,
                                     0.5555555555555556,
                                     1e-15 );

    // The highest bin boundary intersects the range
    photon.setTime( 5e-4 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 134906606.10000002 );

    phase_space_discretization.calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 2 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[0].second,
                                     0.1111111111111111,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].first, 5 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[1].second,
                                     0.1111111111111111,
                                     1e-15 );

    // The range extends below lowest bin boundary and above highest bin boundary
    photon.setTime( 0.0 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896229.0 );

    phase_space_discretization.calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 6 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 0 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[0].second,
                                     0.0018,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].first, 1 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[1].second,
                                     0.018,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[2].first, 2 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[2].second,
                                     0.18,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[3].first, 3 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[0].second,
                                     0.0018,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[4].first, 4 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[1].second,
                                     0.018,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[5].first, 5 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[2].second,
                                     0.18,
                                     1e-15 );

    // Increment the collision number
    photon.setTime( 0.0 );
    photon.setSourceId( 0 );
    photon.incrementCollisionNumber();
    photon.incrementCollisionNumber();
    
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896.22900000002 );

    phase_space_discretization.calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 9 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[0].second,
                                     0.8,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].first, 12 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[1].second,
                                     0.8,
                                     1e-15 );

    // The second bin boundary intersects the range
    photon.setTime( 2e-6 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 539626.4244 );

    phase_space_discretization.calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 4 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 9 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[0].second,
                                     0.44444444444444453,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].first, 10 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[1].second,
                                     0.5555555555555556,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[2].first, 12 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[2].second,
                                     0.44444444444444453,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[3].first, 13 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[3].second,
                                     0.5555555555555556,
                                     1e-15 );

    // The highest bin boundary intersects the range
    photon.setTime( 5e-4 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 134906606.10000002 );

    phase_space_discretization.calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 11 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[0].second,
                                     0.1111111111111111,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].first, 14 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[1].second,
                                     0.1111111111111111,
                                     1e-15 );

    // The range extends below lowest bin boundary and above highest bin boundary
    photon.setTime( 0.0 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896229.0 );

    phase_space_discretization.calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 6 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 9 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[0].second,
                                     0.0018,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].first, 10 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[1].second,
                                     0.018,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[2].first, 11 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[2].second,
                                     0.18,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[3].first, 12 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[0].second,
                                     0.0018,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[4].first, 13 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[1].second,
                                     0.018,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[5].first, 14 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[2].second,
                                     0.18,
                                     1e-15 );
  }
}

//---------------------------------------------------------------------------//
// Check that the name of a bin can be returned
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDiscretization, getBinName )
{
  MonteCarlo::ObserverPhaseSpaceDiscretization phase_space_discretization;

  FRENSIE_CHECK_EQUAL( phase_space_discretization.getBinName( 0 ), "" );

  phase_space_discretization.assignDiscretizationToDimension( source_energy_dimension_discretization );

  std::string bin_name = phase_space_discretization.getBinName( 0 );
  
  FRENSIE_CHECK( bin_name.find( "Source Energy Bin:" ) < bin_name.size() );
  FRENSIE_CHECK( bin_name.find( "[" ) < bin_name.size() );
  FRENSIE_CHECK( bin_name.find( "," ) < bin_name.size() );
  FRENSIE_CHECK( bin_name.find( "]" ) < bin_name.size() );

  bin_name = phase_space_discretization.getBinName( 1 );

  FRENSIE_CHECK( bin_name.find( "Source Energy Bin:" ) < bin_name.size() );
  FRENSIE_CHECK( bin_name.find( "(" ) < bin_name.size() );
  FRENSIE_CHECK( bin_name.find( "," ) < bin_name.size() );
  FRENSIE_CHECK( bin_name.find( "]" ) < bin_name.size() );

  bin_name = phase_space_discretization.getBinName( 2 );

  FRENSIE_CHECK( bin_name.find( "Source Energy Bin:" ) < bin_name.size() );
  FRENSIE_CHECK( bin_name.find( "(" ) < bin_name.size() );
  FRENSIE_CHECK( bin_name.find( "," ) < bin_name.size() );
  FRENSIE_CHECK( bin_name.find( "]" ) < bin_name.size() );

  phase_space_discretization.assignDiscretizationToDimension( energy_dimension_discretization );

  bin_name = phase_space_discretization.getBinName( 0 );

  FRENSIE_CHECK( bin_name.find( "Source Energy Bin:" ) < bin_name.size() );
  FRENSIE_CHECK( bin_name.find( "Energy Bin:" ) < bin_name.size() );
  
  bin_name = phase_space_discretization.getBinName( 8 );

  FRENSIE_CHECK( bin_name.find( "Source Energy Bin:" ) < bin_name.size() );
  FRENSIE_CHECK( bin_name.find( "Energy Bin:" ) < bin_name.size() );

  phase_space_discretization.assignDiscretizationToDimension( collision_number_dimension_discretization );

  bin_name = phase_space_discretization.getBinName( 0 );

  FRENSIE_CHECK( bin_name.find( "Source Energy Bin:" ) < bin_name.size() );
  FRENSIE_CHECK( bin_name.find( "Energy Bin:" ) < bin_name.size() );
  FRENSIE_CHECK( bin_name.find( "Collision Number Bin:" ) < bin_name.size() );
  FRENSIE_CHECK( bin_name.find( "[0,1]" ) < bin_name.size() );

  bin_name = phase_space_discretization.getBinName( 35 );

  FRENSIE_CHECK( bin_name.find( "Source Energy Bin:" ) < bin_name.size() );
  FRENSIE_CHECK( bin_name.find( "Energy Bin:" ) < bin_name.size() );
  FRENSIE_CHECK( bin_name.find( "Collision Number Bin:" ) < bin_name.size() );
  FRENSIE_CHECK( bin_name.find( "[4,5]" ) < bin_name.size() );
}

//---------------------------------------------------------------------------//
// Check that a single bin can be printed
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDiscretization, print_bin )
{
  MonteCarlo::ObserverPhaseSpaceDiscretization phase_space_discretization;

  phase_space_discretization.assignDiscretizationToDimension( source_energy_dimension_discretization );
  
  std::ostringstream oss;

  phase_space_discretization.print( oss, MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION, 0 );

  FRENSIE_CHECK( oss.str().find( "Source Energy Bin:" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "[" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "," ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "]" ) < oss.str().size() );

  phase_space_discretization.print( oss, MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION, 1 );

  FRENSIE_CHECK( oss.str().find( "Source Energy Bin:" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "(" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "," ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "]" ) < oss.str().size() );

  phase_space_discretization.print( oss, MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION, 2 );

  FRENSIE_CHECK( oss.str().find( "Source Energy Bin:" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "(" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "," ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "]" ) < oss.str().size() );
  
  phase_space_discretization.assignDiscretizationToDimension( energy_dimension_discretization );

  phase_space_discretization.print( oss, MonteCarlo::OBSERVER_ENERGY_DIMENSION, 0 );
  
  FRENSIE_CHECK( oss.str().find( "Energy Bin:" ) < oss.str().size() );

  phase_space_discretization.print( oss, MonteCarlo::OBSERVER_ENERGY_DIMENSION, 2 );
  
  FRENSIE_CHECK( oss.str().find( "Energy Bin:" ) < oss.str().size() );

  phase_space_discretization.assignDiscretizationToDimension( collision_number_dimension_discretization );

  phase_space_discretization.print( oss, MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION, 0 );

  FRENSIE_CHECK( oss.str().find( "Collision Number Bin:" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "[0,1]" ) < oss.str().size() );

  phase_space_discretization.print( oss, MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION, 3 );

  FRENSIE_CHECK( oss.str().find( "Collision Number Bin:" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "[4,5]" ) < oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that a dimension discretization can be printed
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDiscretization, print_dimension )
{
  MonteCarlo::ObserverPhaseSpaceDiscretization phase_space_discretization;

  phase_space_discretization.assignDiscretizationToDimension( source_energy_dimension_discretization );

  std::ostringstream oss;

  phase_space_discretization.print( oss, MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION );

  FRENSIE_CHECK( oss.str().find( "Source Energy Bin Boundaries:" ) <
                 oss.str().size() );

  oss.str( "" );
  oss.clear();

  phase_space_discretization.assignDiscretizationToDimension( energy_dimension_discretization );

  phase_space_discretization.print( oss, MonteCarlo::OBSERVER_ENERGY_DIMENSION );

  FRENSIE_CHECK( oss.str().find( "Energy Bin Boundaries:" ) <
                 oss.str().size() );

  oss.str( "" );
  oss.clear();

  phase_space_discretization.assignDiscretizationToDimension( source_time_dimension_discretization );

  phase_space_discretization.print( oss, MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION );

  FRENSIE_CHECK( oss.str().find( "Source Time Bin Boundaries:" ) <
                 oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that the phase space discretization can be printed
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDiscretization, print )
{
  MonteCarlo::ObserverPhaseSpaceDiscretization phase_space_discretization;

  std::ostringstream oss;

  phase_space_discretization.print( oss );

  FRENSIE_CHECK_EQUAL( oss.str(), "" );

  oss.str( "" );
  oss.clear();

  phase_space_discretization.assignDiscretizationToDimension( source_energy_dimension_discretization );

  phase_space_discretization.print( oss );
  
  FRENSIE_CHECK( oss.str().find( "Source Energy Bin Boundaries:" ) <
                 oss.str().size() );

  oss.str( "" );
  oss.clear();

  phase_space_discretization.assignDiscretizationToDimension( energy_dimension_discretization );

  phase_space_discretization.print( oss );
  
  FRENSIE_CHECK( oss.str().find( "Source Energy Bin Boundaries:" ) <
                 oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "Energy Bin Boundaries:" ) <
                 oss.str().size() );

  oss.str( "" );
  oss.clear();

  phase_space_discretization.assignDiscretizationToDimension( collision_number_dimension_discretization );

  phase_space_discretization.print( oss );
  
  FRENSIE_CHECK( oss.str().find( "Source Energy Bin Boundaries:" ) <
                 oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "Energy Bin Boundaries:" ) <
                 oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "Collision Number Bin Boundaries:" ) <
                 oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that a discretization index can be calculated from individual dimension bin indices.
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDiscretization, calculateBinIndex )
{
  MonteCarlo::ObserverPhaseSpaceDiscretization phase_space_discretization;

  phase_space_discretization.assignDiscretizationToDimension( energy_dimension_discretization );
  phase_space_discretization.assignDiscretizationToDimension( cosine_dimension_discretization );

  std::unordered_map<MonteCarlo::ObserverPhaseSpaceDimension, size_t> index_map;


  index_map.emplace(std::make_pair(MonteCarlo::OBSERVER_COSINE_DIMENSION, 1));
  index_map.emplace(std::make_pair(MonteCarlo::OBSERVER_ENERGY_DIMENSION, 2));

  // 3 bins in each dimension total 
  /*  energy bins:  0 1 2
   *  cosine bin 0: 0 1 2
   *  cosine bin 1: 3 4 5 (bin should be 5)
   *  cosine bin 2: 6 7 8 
   */

  size_t index = phase_space_discretization.calculateDiscretizationIndex(index_map);

  FRENSIE_CHECK_EQUAL(index, 5);

}

//---------------------------------------------------------------------------//
// Check that the phase space discretization can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ObserverPhaseSpaceDiscretization,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_observer_phase_space_discretization" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<MonteCarlo::ObserverPhaseSpaceDiscretization>
      empty_discretization( new MonteCarlo::ObserverPhaseSpaceDiscretization );

    std::shared_ptr<MonteCarlo::ObserverPhaseSpaceDiscretization>
      single_discretization( new MonteCarlo::ObserverPhaseSpaceDiscretization );
    single_discretization->assignDiscretizationToDimension( cosine_dimension_discretization );

    std::shared_ptr<MonteCarlo::ObserverPhaseSpaceDiscretization>
      ranged_single_discretization( new MonteCarlo::ObserverPhaseSpaceDiscretization );

    ranged_single_discretization->assignDiscretizationToDimension( time_dimension_discretization, true );

    std::shared_ptr<MonteCarlo::ObserverPhaseSpaceDiscretization>
      detailed_discretization( new MonteCarlo::ObserverPhaseSpaceDiscretization );

    detailed_discretization->assignDiscretizationToDimension( time_dimension_discretization, true );
    detailed_discretization->assignDiscretizationToDimension( source_id_dimension_discretization );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(empty_discretization) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(single_discretization) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(ranged_single_discretization) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(detailed_discretization) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<MonteCarlo::ObserverPhaseSpaceDiscretization>
    empty_discretization, single_discretization, ranged_single_discretization,
    detailed_discretization;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(empty_discretization) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(single_discretization) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(ranged_single_discretization) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(detailed_discretization) );

  iarchive.reset();

  {
    MonteCarlo::PhotonState photon( 0 );
    MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

    MonteCarlo::ObserverPhaseSpaceDiscretization::BinIndexArray bin_indices;

    empty_discretization->calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );

    photon.setSourceEnergy( 1.0 );
    photon.setEnergy( 1e-2 );
    photon.setSourceTime( 0.0 );
    photon.setTime( 1e-6 );
    photon.setSourceId( 10 );
    photon.incrementCollisionNumber();
    photon_wrapper.setAngleCosine( -1.0 );

    empty_discretization->calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );
  }

  {
    MonteCarlo::PhotonState photon( 0 );
    MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );
    photon_wrapper.setAngleCosine( -1.0 );

    MonteCarlo::ObserverPhaseSpaceDiscretization::BinIndexArray bin_indices;

    single_discretization->calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );

    photon_wrapper.setAngleCosine( -1.0/3 );

    single_discretization->calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );

    photon_wrapper.setAngleCosine( 0.0 );

    single_discretization->calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 1 );

    photon_wrapper.setAngleCosine( 1.0/3 );

    single_discretization->calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 1 );

    photon_wrapper.setAngleCosine( 2.0/3 );

    single_discretization->calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 2 );

    photon_wrapper.setAngleCosine( 1.0 );

    single_discretization->calculateBinIndicesOfPoint( photon_wrapper, bin_indices );

    FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices[0], 2 );
  }

  {
    // The lowest bin boundary intersects the range
    MonteCarlo::PhotonState photon( 0 );
    photon.setTime( 0.0 );
    
    MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896.22900000002 );

    MonteCarlo::ObserverPhaseSpaceDiscretization::BinIndexWeightPairArray bin_indices_and_weights;

    ranged_single_discretization->calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 0 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights.front().second,
                                     0.8,
                                     1e-15 );

    // The second bin boundary intersects the range
    photon.setTime( 2e-6 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 539626.4244 );

    ranged_single_discretization->calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights.front().second,
                                     0.44444444444444453,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights.back().first, 1 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights.back().second,
                                     0.5555555555555556,
                                     1e-15 );

    // The highest bin boundary intersects the range
    photon.setTime( 5e-4 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 134906606.10000002 );

    ranged_single_discretization->calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 2 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights.front().second,
                                     0.1111111111111111,
                                     1e-15 );

    // The range extends below lowest bin boundary and above highest bin boundary
    photon.setTime( 0.0 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896229.0 );

    ranged_single_discretization->calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 3 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 0 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[0].second,
                                     0.0018,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].first, 1 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[1].second,
                                     0.018,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[2].first, 2 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[2].second,
                                     0.18,
                                     1e-15 );
  }

  {
    // The lowest bin boundary intersects the range
    MonteCarlo::PhotonState photon( 0 );
    photon.setTime( 0.0 );
    photon.setSourceId( 0 );
    
    MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896.22900000002 );

    MonteCarlo::ObserverPhaseSpaceDiscretization::BinIndexWeightPairArray bin_indices_and_weights;

    detailed_discretization->calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 0 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[0].second,
                                     0.8,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].first, 3 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[1].second,
                                     0.8,
                                     1e-15 );

    // The second bin boundary intersects the range
    photon.setTime( 2e-6 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 539626.4244 );

    detailed_discretization->calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 4 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 0 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[0].second,
                                     0.44444444444444453,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].first, 1 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[1].second,
                                     0.5555555555555556,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[2].first, 3 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[2].second,
                                     0.44444444444444453,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[3].first, 4 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[3].second,
                                     0.5555555555555556,
                                     1e-15 );

    // The highest bin boundary intersects the range
    photon.setTime( 5e-4 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 134906606.10000002 );

    detailed_discretization->calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 2 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[0].second,
                                     0.1111111111111111,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].first, 5 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[1].second,
                                     0.1111111111111111,
                                     1e-15 );

    // The range extends below lowest bin boundary and above highest bin boundary
    photon.setTime( 0.0 );
    photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896229.0 );

    detailed_discretization->calculateBinIndicesAndWeightsOfRange( photon_wrapper, bin_indices_and_weights );

    FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 6 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 0 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[0].second,
                                     0.0018,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].first, 1 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[1].second,
                                     0.018,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[2].first, 2 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[2].second,
                                     0.18,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[3].first, 3 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[0].second,
                                     0.0018,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[4].first, 4 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[1].second,
                                     0.018,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( bin_indices_and_weights[5].first, 5 );
    FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[2].second,
                                     0.18,
                                     1e-15 );
  }
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the cosine dimension discretization
  {
    MonteCarlo::ObserverCosineDimensionDiscretization::InputDataType
      raw_discretization( {-1.0, -1.0/3, 1.0/3, 1.0} );

    cosine_dimension_discretization.reset( new MonteCarlo::ObserverCosineDimensionDiscretization( raw_discretization ) );
  }
  
  // Create the source energy, energy and source time dimension discretizations
  {
    std::vector<double> raw_discretization( {0.0, 1e-5, 1e-4, 1e-3} );

    source_energy_dimension_discretization.reset( new MonteCarlo::ObserverSourceEnergyDimensionDiscretization( raw_discretization ) );
    energy_dimension_discretization.reset( new MonteCarlo::ObserverEnergyDimensionDiscretization( raw_discretization ) );
    source_time_dimension_discretization.reset( new MonteCarlo::ObserverSourceTimeDimensionDiscretization( raw_discretization ) );
  }

  // Create the time dimension discretization
  {
    MonteCarlo::ObserverTimeDimensionDiscretization::InputDataType
      raw_discretization( {1e-6, 1e-5, 1e-4, 1e-3} );

    time_dimension_discretization.reset( new MonteCarlo::ObserverTimeDimensionDiscretization( raw_discretization ) );
  }

  // Create the collision number dimension discretization
  {
    MonteCarlo::ObserverCollisionNumberDimensionDiscretization::InputDataType
      raw_discretization( {1, 2, 3, 5} );

    collision_number_dimension_discretization.reset( new MonteCarlo::ObserverCollisionNumberDimensionDiscretization( raw_discretization ) );
  }

  // Create the source id dimension discretization
  {
    MonteCarlo::ObserverSourceIdDimensionDiscretization::InputDataType
      raw_discretization( 3 );

    raw_discretization[0].insert( 0 );
  
    raw_discretization[1].insert( 0 );
    raw_discretization[1].insert( 1 );

    raw_discretization[2].insert( 1 );
    raw_discretization[2].insert( 2 );

    source_id_dimension_discretization.reset( new MonteCarlo::ObserverSourceIdDimensionDiscretization( raw_discretization ) );
  }
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstObserverPhaseSpaceDiscretization.cpp
//---------------------------------------------------------------------------//
