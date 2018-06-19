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

typedef std::tuple<
  std::tuple<boost::archive::xml_oarchive,boost::archive::xml_iarchive>,
  std::tuple<boost::archive::text_oarchive,boost::archive::text_iarchive>,
  std::tuple<boost::archive::binary_oarchive,boost::archive::binary_iarchive>,
  std::tuple<Utility::HDF5OArchive,Utility::HDF5IArchive>
  > TestArchives;

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

}

//---------------------------------------------------------------------------//
// Check that a dimension discretization can be printed
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDiscretization, print_dimension )
{

}

//---------------------------------------------------------------------------//
// Check that the phase space discretization can be printed
FRENSIE_UNIT_TEST( ObserverPhaseSpaceDiscretization, print )
{

}

//---------------------------------------------------------------------------//
// Check that the phase space discretization can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ObserverPhaseSpaceDiscretization,
                                   archive,
                                   TestArchives )
{

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
