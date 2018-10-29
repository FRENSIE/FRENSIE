//---------------------------------------------------------------------------//
//!
//! \file   tstEventHandlerDagMC.cpp
//! \author Alex Robinson
//! \brief  Event handler unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_EventHandler.hpp"
#include "MonteCarlo_CellCollisionFluxEstimator.hpp"
#include "MonteCarlo_CellTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_CellPulseHeightEstimator.hpp"
#include "MonteCarlo_SurfaceCurrentEstimator.hpp"
#include "MonteCarlo_SurfaceFluxEstimator.hpp"
#include "MonteCarlo_MeshTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_ParticleTracker.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Geometry_DagMCModel.hpp"
#include "Utility_StructuredHexMesh.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const Geometry::Model> model;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the event handler can construct the estimators specified in
// the geometry
FRENSIE_UNIT_TEST( EventHandler, geometry_constructor )
{
  MonteCarlo::EventHandler event_handler( model, MonteCarlo::SimulationProperties() );

  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfEstimators(), 9 );

  FRENSIE_REQUIRE( event_handler.doesEstimatorExist( 0 ) );
  FRENSIE_REQUIRE_NO_THROW( dynamic_cast<MonteCarlo::WeightMultipliedCellTrackLengthFluxEstimator&>( event_handler.getEstimator( 0 ) ) );
  FRENSIE_CHECK_EQUAL( event_handler.getEstimator( 0 ).getParticleTypes(),
                       std::set<MonteCarlo::ParticleType>( {MonteCarlo::NEUTRON} ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 1 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 3 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 5 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 7 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 9 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 13 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 19 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 26 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 27 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 28 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 29 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 30 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 31 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 32 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 33 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 34 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 35 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 36 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 37 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 41 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 48 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 49 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 50 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 51 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 52 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 53 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 54 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 55 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 56 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 57 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 58 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 59 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 63 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 70 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 71 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 72 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 73 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 74 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 75 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 76 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 77 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 78 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 79 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 80 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 81 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 82 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 83 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 88 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 136 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 152 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 154 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 166 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 168 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 184 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 0 ).isEntityAssigned( 188 ) );

  FRENSIE_REQUIRE( event_handler.doesEstimatorExist( 1 ) );
  FRENSIE_REQUIRE_NO_THROW( dynamic_cast<MonteCarlo::WeightMultipliedCellTrackLengthFluxEstimator&>( event_handler.getEstimator( 1 ) ) );
  FRENSIE_CHECK_EQUAL( event_handler.getEstimator( 1 ).getParticleTypes(),
                       std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 1 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 3 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 5 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 7 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 9 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 13 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 19 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 26 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 27 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 28 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 29 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 30 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 31 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 32 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 33 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 34 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 35 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 36 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 37 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 41 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 48 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 49 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 50 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 51 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 52 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 53 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 54 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 55 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 56 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 57 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 58 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 59 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 63 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 70 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 71 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 72 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 73 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 74 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 75 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 76 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 77 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 78 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 79 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 80 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 81 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 82 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 83 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 88 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 136 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 152 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 154 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 166 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 168 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 184 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 1 ).isEntityAssigned( 188 ) );

  FRENSIE_REQUIRE( event_handler.doesEstimatorExist( 2 ) );
  FRENSIE_REQUIRE_NO_THROW( dynamic_cast<MonteCarlo::WeightMultipliedCellCollisionFluxEstimator&>( event_handler.getEstimator( 2 ) ) );
  FRENSIE_CHECK_EQUAL( event_handler.getEstimator( 2 ).getParticleTypes(),
                       std::set<MonteCarlo::ParticleType>( {MonteCarlo::NEUTRON} ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 26 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 27 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 28 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 29 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 30 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 31 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 32 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 33 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 34 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 35 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 36 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 37 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 48 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 49 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 50 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 51 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 52 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 53 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 54 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 55 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 56 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 57 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 58 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 59 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 70 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 71 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 72 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 73 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 74 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 75 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 76 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 77 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 78 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 79 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 80 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 2 ).isEntityAssigned( 81 ) );

  FRENSIE_REQUIRE( event_handler.doesEstimatorExist( 3 ) );
  FRENSIE_REQUIRE_NO_THROW( dynamic_cast<MonteCarlo::WeightMultipliedCellCollisionFluxEstimator&>( event_handler.getEstimator( 3 ) ) );
  FRENSIE_CHECK_EQUAL( event_handler.getEstimator( 3 ).getParticleTypes(),
                       std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 26 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 27 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 28 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 29 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 30 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 31 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 32 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 33 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 34 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 35 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 36 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 37 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 48 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 49 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 50 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 51 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 52 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 53 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 54 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 55 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 56 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 57 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 58 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 59 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 70 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 71 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 72 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 73 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 74 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 75 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 76 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 77 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 78 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 79 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 80 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 3 ).isEntityAssigned( 81 ) );

  FRENSIE_REQUIRE( event_handler.doesEstimatorExist( 4 ) );
  FRENSIE_REQUIRE_NO_THROW( dynamic_cast<MonteCarlo::WeightMultipliedCellPulseHeightEstimator&>( event_handler.getEstimator( 4 ) ) );
  FRENSIE_CHECK_EQUAL( event_handler.getEstimator( 4 ).getParticleTypes(),
                       std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON, MonteCarlo::ELECTRON, MonteCarlo::POSITRON} ) );
  FRENSIE_CHECK( event_handler.getEstimator( 4 ).isEntityAssigned( 9 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 4 ).isEntityAssigned( 88 ) );

  FRENSIE_REQUIRE( event_handler.doesEstimatorExist( 5 ) );
  FRENSIE_REQUIRE_NO_THROW( dynamic_cast<MonteCarlo::WeightMultipliedSurfaceFluxEstimator&>( event_handler.getEstimator( 5 ) ) );
  FRENSIE_CHECK_EQUAL( event_handler.getEstimator( 5 ).getParticleTypes(),
                       std::set<MonteCarlo::ParticleType>( {MonteCarlo::NEUTRON} ) );
  FRENSIE_CHECK( event_handler.getEstimator( 5 ).isEntityAssigned( 7 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 5 ).isEntityAssigned( 16 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 5 ).isEntityAssigned( 25 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 5 ).isEntityAssigned( 34 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 5 ).isEntityAssigned( 94 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 5 ).isEntityAssigned( 202 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 5 ).isEntityAssigned( 310 ) );

  FRENSIE_REQUIRE( event_handler.doesEstimatorExist( 6 ) );
  FRENSIE_REQUIRE_NO_THROW( dynamic_cast<MonteCarlo::WeightMultipliedSurfaceFluxEstimator&>( event_handler.getEstimator( 6 ) ) );
  FRENSIE_CHECK_EQUAL( event_handler.getEstimator( 6 ).getParticleTypes(),
                       std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );
  FRENSIE_CHECK( event_handler.getEstimator( 6 ).isEntityAssigned( 7 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 6 ).isEntityAssigned( 16 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 6 ).isEntityAssigned( 25 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 6 ).isEntityAssigned( 34 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 6 ).isEntityAssigned( 94 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 6 ).isEntityAssigned( 202 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 6 ).isEntityAssigned( 310 ) );

  FRENSIE_REQUIRE( event_handler.doesEstimatorExist( 7 ) );
  FRENSIE_REQUIRE_NO_THROW( dynamic_cast<MonteCarlo::WeightMultipliedSurfaceCurrentEstimator&>( event_handler.getEstimator( 7 ) ) );
  FRENSIE_CHECK_EQUAL( event_handler.getEstimator( 7 ).getParticleTypes(),
                       std::set<MonteCarlo::ParticleType>( {MonteCarlo::NEUTRON} ) );
  FRENSIE_CHECK( event_handler.getEstimator( 7 ).isEntityAssigned( 7 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 7 ).isEntityAssigned( 16 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 7 ).isEntityAssigned( 25 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 7 ).isEntityAssigned( 34 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 7 ).isEntityAssigned( 94 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 7 ).isEntityAssigned( 202 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 7 ).isEntityAssigned( 310 ) );

  FRENSIE_REQUIRE( event_handler.doesEstimatorExist( 8 ) );
  FRENSIE_REQUIRE_NO_THROW( dynamic_cast<MonteCarlo::WeightMultipliedSurfaceCurrentEstimator&>( event_handler.getEstimator( 8 ) ) );
  FRENSIE_CHECK_EQUAL( event_handler.getEstimator( 8 ).getParticleTypes(),
                       std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );
  FRENSIE_CHECK( event_handler.getEstimator( 8 ).isEntityAssigned( 7 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 8 ).isEntityAssigned( 16 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 8 ).isEntityAssigned( 25 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 8 ).isEntityAssigned( 34 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 8 ).isEntityAssigned( 94 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 8 ).isEntityAssigned( 202 ) );
  FRENSIE_CHECK( event_handler.getEstimator( 8 ).isEntityAssigned( 310 ) );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_dagmc_geom_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_cad_file",
                                        test_dagmc_geom_file_name, "",
                                        "Test CAD file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  Geometry::DagMCModelProperties local_properties( test_dagmc_geom_file_name );

  local_properties.setTerminationCellPropertyName( "graveyard" );
  local_properties.setMaterialPropertyName( "mat" );
  local_properties.setDensityPropertyName( "rho" );
  local_properties.setEstimatorPropertyName( "tally" );

  model.reset( new Geometry::DagMCModel( local_properties ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstEventHandlerDagMC.cpp
//---------------------------------------------------------------------------//
