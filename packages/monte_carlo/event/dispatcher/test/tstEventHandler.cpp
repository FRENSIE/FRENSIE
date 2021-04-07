//---------------------------------------------------------------------------//
//!
//! \file   tstEventHandler.cpp
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
#include "Geometry_InfiniteMediumModel.hpp"
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
std::shared_ptr<MonteCarlo::WeightMultipliedCellCollisionFluxEstimator>
estimator_1;

std::shared_ptr<MonteCarlo::WeightAndEnergyMultipliedCellCollisionFluxEstimator>
estimator_2;

std::shared_ptr<MonteCarlo::WeightAndChargeMultipliedCellCollisionFluxEstimator>
estimator_3;

std::shared_ptr<MonteCarlo::WeightMultipliedCellTrackLengthFluxEstimator>
estimator_4;

std::shared_ptr<MonteCarlo::WeightAndEnergyMultipliedCellTrackLengthFluxEstimator>
estimator_5;

std::shared_ptr<MonteCarlo::WeightAndChargeMultipliedCellTrackLengthFluxEstimator>
estimator_6;

std::shared_ptr<MonteCarlo::WeightMultipliedCellPulseHeightEstimator>
estimator_7;

std::shared_ptr<MonteCarlo::WeightAndEnergyMultipliedCellPulseHeightEstimator>
estimator_8;

std::shared_ptr<MonteCarlo::WeightAndChargeMultipliedCellPulseHeightEstimator>
estimator_9;

std::shared_ptr<MonteCarlo::WeightMultipliedSurfaceFluxEstimator>
estimator_10;

std::shared_ptr<MonteCarlo::WeightAndEnergyMultipliedSurfaceFluxEstimator>
estimator_11;

std::shared_ptr<MonteCarlo::WeightAndChargeMultipliedSurfaceFluxEstimator>
estimator_12;

std::shared_ptr<MonteCarlo::WeightMultipliedSurfaceCurrentEstimator>
estimator_13;

std::shared_ptr<MonteCarlo::WeightAndEnergyMultipliedSurfaceCurrentEstimator>
estimator_14;

std::shared_ptr<MonteCarlo::WeightAndChargeMultipliedSurfaceCurrentEstimator>
estimator_15;

std::shared_ptr<MonteCarlo::WeightMultipliedMeshTrackLengthFluxEstimator>
mesh_estimator_1;

std::shared_ptr<MonteCarlo::WeightAndEnergyMultipliedMeshTrackLengthFluxEstimator>
mesh_estimator_2;

std::shared_ptr<MonteCarlo::WeightAndChargeMultipliedMeshTrackLengthFluxEstimator>
mesh_estimator_3;

std::shared_ptr<MonteCarlo::ParticleTracker> particle_tracker;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the simulation completion criterion can be set
FRENSIE_UNIT_TEST( EventHandler, setSimulationCompletionCriterion )
{
  MonteCarlo::EventHandler event_handler;

  event_handler.setSimulationCompletionCriterion( MonteCarlo::ParticleHistorySimulationCompletionCriterion::createHistoryCountCriterion( 10 ) );

  event_handler.updateObserversFromParticleSimulationStartedEvent();

  FRENSIE_CHECK( !event_handler.isSimulationComplete() );

  for( size_t i = 0; i < 5; ++i )
    event_handler.commitObserverHistoryContributions();

  FRENSIE_CHECK( !event_handler.isSimulationComplete() );

  event_handler.updateObserversFromParticleSimulationStoppedEvent();

  for( size_t i = 5; i <= 10; ++i )
    event_handler.commitObserverHistoryContributions();

  FRENSIE_CHECK( !event_handler.isSimulationComplete() );

  event_handler.updateObserversFromParticleSimulationStartedEvent();

  for( size_t i = 5; i <= 10; ++i )
    event_handler.commitObserverHistoryContributions();

  FRENSIE_CHECK( event_handler.isSimulationComplete() );
}

//---------------------------------------------------------------------------//
// Check that the simulation completion criterion can be set
FRENSIE_UNIT_TEST( EventHandler,
                   setSimulationCompletionCriterion_constructor_props )
{
  // Set a history wall
  MonteCarlo::SimulationGeneralProperties properties;
  properties.setNumberOfHistories( 10 );

  std::unique_ptr<MonteCarlo::EventHandler> event_handler(
                                  new MonteCarlo::EventHandler( properties ) );

  event_handler->updateObserversFromParticleSimulationStartedEvent();

  FRENSIE_CHECK( !event_handler->isSimulationComplete() );

  for( size_t i = 0; i <= 10; ++i )
    event_handler->commitObserverHistoryContributions();

  FRENSIE_CHECK( event_handler->isSimulationComplete() );

  // Set a time wall
  properties.setNumberOfHistories( 0 );
  properties.setSimulationWallTime( 0.02 );

  event_handler.reset( new MonteCarlo::EventHandler( properties ) );

  FRENSIE_CHECK( !event_handler->isSimulationComplete() );

  event_handler->updateObserversFromParticleSimulationStartedEvent();

  std::shared_ptr<Utility::Timer> timer =
    Utility::GlobalMPISession::createTimer();

  timer->start();

  while( timer->elapsed().count() < 0.02 );

  timer->stop();
  timer.reset();

  FRENSIE_CHECK( event_handler->isSimulationComplete() );

  // Set a mixed criterion
  properties.setNumberOfHistories( 10 );
  properties.setSimulationWallTime( 1.0 );

  event_handler.reset( new MonteCarlo::EventHandler( properties ) );

  FRENSIE_CHECK( !event_handler->isSimulationComplete() );

  event_handler->updateObserversFromParticleSimulationStartedEvent();

  for( size_t i = 0; i <= 10; ++i )
    event_handler->commitObserverHistoryContributions();

  FRENSIE_CHECK( event_handler->isSimulationComplete() );
}

//---------------------------------------------------------------------------//
// Check that the simulation completion criterion can be set
FRENSIE_UNIT_TEST( EventHandler, setSimulationCompletionCriterion_props )
{
  // Set a history wall
  MonteCarlo::SimulationGeneralProperties properties;
  properties.setNumberOfHistories( 10 );

  std::unique_ptr<MonteCarlo::EventHandler>
    event_handler( new MonteCarlo::EventHandler );

  event_handler->setSimulationCompletionCriterion( properties );

  event_handler->updateObserversFromParticleSimulationStartedEvent();

  FRENSIE_CHECK( !event_handler->isSimulationComplete() );

  for( size_t i = 0; i <= 10; ++i )
    event_handler->commitObserverHistoryContributions();

  FRENSIE_CHECK( event_handler->isSimulationComplete() );

  // Set a time wall
  properties.setNumberOfHistories( 0 );
  properties.setSimulationWallTime( 0.02 );

  event_handler->setSimulationCompletionCriterion( properties );

  FRENSIE_CHECK( !event_handler->isSimulationComplete() );

  event_handler->updateObserversFromParticleSimulationStartedEvent();

  std::shared_ptr<Utility::Timer> timer =
    Utility::GlobalMPISession::createTimer();

  timer->start();

  while( timer->elapsed().count() < 0.02 );

  timer->stop();
  timer.reset();

  FRENSIE_CHECK( event_handler->isSimulationComplete() );

  // Set a mixed criterion
  properties.setNumberOfHistories( 10 );
  properties.setSimulationWallTime( 1.0 );

  event_handler->setSimulationCompletionCriterion( properties );

  FRENSIE_CHECK( !event_handler->isSimulationComplete() );

  event_handler->updateObserversFromParticleSimulationStartedEvent();

  for( size_t i = 0; i <= 10; ++i )
    event_handler->commitObserverHistoryContributions();

  FRENSIE_CHECK( event_handler->isSimulationComplete() );
}

//---------------------------------------------------------------------------//
// Check that estimators can be added
FRENSIE_UNIT_TEST( EventHandler, addEstimator )
{
  MonteCarlo::EventHandler event_handler;

  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfEstimators(), 0 );

  FRENSIE_REQUIRE_NO_THROW( event_handler.addEstimator( estimator_1 ) );
  FRENSIE_CHECK( event_handler.doesEstimatorExist( estimator_1->getId() ) );
  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfEstimators(), 1 );

  FRENSIE_REQUIRE_NO_THROW( event_handler.addEstimator( estimator_2 ) );
  FRENSIE_CHECK( event_handler.doesEstimatorExist( estimator_2->getId() ) );
  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfEstimators(), 2 );

  FRENSIE_REQUIRE_NO_THROW( event_handler.addEstimator( estimator_3 ) );
  FRENSIE_CHECK( event_handler.doesEstimatorExist( estimator_3->getId() ) );
  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfEstimators(), 3 );

  FRENSIE_REQUIRE_NO_THROW( event_handler.addEstimator( estimator_4 ) );
  FRENSIE_CHECK( event_handler.doesEstimatorExist( estimator_4->getId() ) );
  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfEstimators(), 4 );

  FRENSIE_REQUIRE_NO_THROW( event_handler.addEstimator( estimator_5 ) );
  FRENSIE_CHECK( event_handler.doesEstimatorExist( estimator_5->getId() ) );
  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfEstimators(), 5 );

  FRENSIE_REQUIRE_NO_THROW( event_handler.addEstimator( estimator_6 ) );
  FRENSIE_CHECK( event_handler.doesEstimatorExist( estimator_6->getId() ) );
  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfEstimators(), 6 );

  FRENSIE_REQUIRE_NO_THROW( event_handler.addEstimator( estimator_7 ) );
  FRENSIE_CHECK( event_handler.doesEstimatorExist( estimator_7->getId() ) );
  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfEstimators(), 7 );

  FRENSIE_REQUIRE_NO_THROW( event_handler.addEstimator( estimator_8 ) );
  FRENSIE_CHECK( event_handler.doesEstimatorExist( estimator_8->getId() ) );
  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfEstimators(), 8 );

  FRENSIE_REQUIRE_NO_THROW( event_handler.addEstimator( estimator_9 ) );
  FRENSIE_CHECK( event_handler.doesEstimatorExist( estimator_9->getId() ) );
  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfEstimators(), 9 );

  FRENSIE_REQUIRE_NO_THROW( event_handler.addEstimator( estimator_10 ) );
  FRENSIE_CHECK( event_handler.doesEstimatorExist( estimator_10->getId() ) );
  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfEstimators(), 10 );

  FRENSIE_REQUIRE_NO_THROW( event_handler.addEstimator( estimator_11 ) );
  FRENSIE_CHECK( event_handler.doesEstimatorExist( estimator_11->getId() ) );
  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfEstimators(), 11 );

  FRENSIE_REQUIRE_NO_THROW( event_handler.addEstimator( estimator_12 ) );
  FRENSIE_CHECK( event_handler.doesEstimatorExist( estimator_12->getId() ) );
  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfEstimators(), 12 );

  FRENSIE_REQUIRE_NO_THROW( event_handler.addEstimator( estimator_13 ) );
  FRENSIE_CHECK( event_handler.doesEstimatorExist( estimator_13->getId() ) );
  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfEstimators(), 13 );

  FRENSIE_REQUIRE_NO_THROW( event_handler.addEstimator( estimator_14 ) );
  FRENSIE_CHECK( event_handler.doesEstimatorExist( estimator_14->getId() ) );
  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfEstimators(), 14 );

  FRENSIE_REQUIRE_NO_THROW( event_handler.addEstimator( estimator_15 ) );
  FRENSIE_CHECK( event_handler.doesEstimatorExist( estimator_15->getId() ) );
  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfEstimators(), 15 );

  FRENSIE_REQUIRE_NO_THROW( event_handler.addEstimator( mesh_estimator_1 ) );
  FRENSIE_CHECK( event_handler.doesEstimatorExist( mesh_estimator_1->getId() ) );
  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfEstimators(), 16 );

  FRENSIE_REQUIRE_NO_THROW( event_handler.addEstimator( mesh_estimator_2 ) );
  FRENSIE_CHECK( event_handler.doesEstimatorExist( mesh_estimator_2->getId() ) );
  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfEstimators(), 17 );

  FRENSIE_REQUIRE_NO_THROW( event_handler.addEstimator( mesh_estimator_3 ) );
  FRENSIE_CHECK( event_handler.doesEstimatorExist( mesh_estimator_3->getId() ) );
  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfEstimators(), 18 );

  // Check that an estimator that has no particle types set will cause an
  // exception
  {
    std::shared_ptr<MonteCarlo::WeightMultipliedCellCollisionFluxEstimator>
      local_estimator_1( new MonteCarlo::WeightMultipliedCellCollisionFluxEstimator(
                                                      100, 1.0, {1}, {1.0} ) );

    FRENSIE_CHECK_THROW( event_handler.addEstimator( local_estimator_1 ),
                         std::runtime_error );
  }
}

//---------------------------------------------------------------------------//
// Check that estimators can be added when a model has been assigned
FRENSIE_UNIT_TEST( EventHandler, addEstimator_model_set )
{
  std::shared_ptr<const Geometry::Model>
    model( new Geometry::InfiniteMediumModel( 1 ) );

  MonteCarlo::EventHandler event_handler( model, MonteCarlo::SimulationProperties() );

  {
    std::shared_ptr<MonteCarlo::WeightMultipliedCellCollisionFluxEstimator>
      local_estimator_1( new MonteCarlo::WeightMultipliedCellCollisionFluxEstimator(
                                                      100, 1.0, {1}, {1.0} ) );

    local_estimator_1->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

    FRENSIE_CHECK_NO_THROW( event_handler.addEstimator( local_estimator_1 ) );

    std::shared_ptr<MonteCarlo::WeightMultipliedCellCollisionFluxEstimator>
      local_estimator_2( new MonteCarlo::WeightMultipliedCellCollisionFluxEstimator(
                                                      101, 1.0, {2}, {1.0} ) );

    local_estimator_2->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

    FRENSIE_CHECK_THROW( event_handler.addEstimator( local_estimator_2 ),
                         std::runtime_error );

    std::shared_ptr<MonteCarlo::WeightMultipliedCellTrackLengthFluxEstimator>
      local_estimator_3( new MonteCarlo::WeightMultipliedCellTrackLengthFluxEstimator(
                                                      102, 1.0, {1}, {1.0} ) );

    local_estimator_3->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

    FRENSIE_CHECK_NO_THROW( event_handler.addEstimator( local_estimator_3 ) );
  }

  {
    std::shared_ptr<MonteCarlo::WeightMultipliedCellPulseHeightEstimator>
      local_estimator_4( new MonteCarlo::WeightMultipliedCellPulseHeightEstimator(
                                                             104, 1.0, {1} ) );

    FRENSIE_CHECK_NO_THROW( event_handler.addEstimator( local_estimator_4 ) );

    std::shared_ptr<MonteCarlo::WeightMultipliedCellPulseHeightEstimator>
      local_estimator_5( new MonteCarlo::WeightMultipliedCellPulseHeightEstimator(
                                                             105, 1.0, {2} ) );

    FRENSIE_CHECK_THROW( event_handler.addEstimator( local_estimator_5 ),
                         std::runtime_error );
  }

  {
    std::shared_ptr<MonteCarlo::WeightMultipliedSurfaceFluxEstimator>
      local_estimator_6( new MonteCarlo::WeightMultipliedSurfaceFluxEstimator(
                                                      106, 1.0, {1}, {1.0} ) );

    local_estimator_6->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

    FRENSIE_CHECK_THROW( event_handler.addEstimator( local_estimator_6 ),
                         std::runtime_error );
  }

  {
    std::shared_ptr<MonteCarlo::WeightMultipliedSurfaceCurrentEstimator>
      local_estimator_8( new MonteCarlo::WeightMultipliedSurfaceCurrentEstimator(
                                                             107, 1.0, {1} ) );

    local_estimator_8->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

    FRENSIE_CHECK_THROW( event_handler.addEstimator( local_estimator_8 ),
                         std::runtime_error );
  }

  {
    std::shared_ptr<const Utility::Mesh> hex_mesh(
                           new Utility::StructuredHexMesh( {0.0, 1.0, 2.0},
                                                           {0.0, 1.0, 2.0},
                                                           {0.0, 1.0, 2.0} ) );

    std::shared_ptr<MonteCarlo::WeightMultipliedMeshTrackLengthFluxEstimator>
      local_mesh_estimator( new MonteCarlo::WeightMultipliedMeshTrackLengthFluxEstimator(
                                                                  108,
                                                                  1.0,
                                                                  hex_mesh ) );
    local_mesh_estimator->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

    FRENSIE_CHECK_NO_THROW( event_handler.addEstimator( local_mesh_estimator ) );
  }
}

//---------------------------------------------------------------------------//
// Check that stored estimators can be returned
FRENSIE_UNIT_TEST( EventHandler, getEstimator )
{
  MonteCarlo::EventHandler event_handler;

  event_handler.addEstimator( estimator_1 );

  {
    const MonteCarlo::Estimator& estimator =
      event_handler.getEstimator( estimator_1->getId() );

    FRENSIE_CHECK( &estimator == estimator_1.get() );
  }

  event_handler.addEstimator( estimator_2 );

  {
    const MonteCarlo::Estimator& estimator =
      event_handler.getEstimator( estimator_2->getId() );

    FRENSIE_CHECK( &estimator == estimator_2.get() );
  }

  event_handler.addEstimator( estimator_3 );

  {
    const MonteCarlo::Estimator& estimator =
      event_handler.getEstimator( estimator_3->getId() );

    FRENSIE_CHECK( &estimator == estimator_3.get() );
  }

  event_handler.addEstimator( estimator_4 );

  {
    const MonteCarlo::Estimator& estimator =
      event_handler.getEstimator( estimator_4->getId() );

    FRENSIE_CHECK( &estimator == estimator_4.get() );
  }

  event_handler.addEstimator( estimator_5 );

  {
    const MonteCarlo::Estimator& estimator =
      event_handler.getEstimator( estimator_5->getId() );

    FRENSIE_CHECK( &estimator == estimator_5.get() );
  }

  event_handler.addEstimator( estimator_6 );

  {
    const MonteCarlo::Estimator& estimator =
      event_handler.getEstimator( estimator_6->getId() );

    FRENSIE_CHECK( &estimator == estimator_6.get() );
  }

  event_handler.addEstimator( estimator_7 );

  {
    const MonteCarlo::Estimator& estimator =
      event_handler.getEstimator( estimator_7->getId() );

    FRENSIE_CHECK( &estimator == estimator_7.get() );
  }

  event_handler.addEstimator( estimator_8 );

  {
    const MonteCarlo::Estimator& estimator =
      event_handler.getEstimator( estimator_8->getId() );

    FRENSIE_CHECK( &estimator == estimator_8.get() );
  }

  event_handler.addEstimator( estimator_9 );

  {
    const MonteCarlo::Estimator& estimator =
      event_handler.getEstimator( estimator_9->getId() );

    FRENSIE_CHECK( &estimator == estimator_9.get() );
  }

  event_handler.addEstimator( estimator_10 );

  {
    const MonteCarlo::Estimator& estimator =
      event_handler.getEstimator( estimator_10->getId() );

    FRENSIE_CHECK( &estimator == estimator_10.get() );
  }

  event_handler.addEstimator( estimator_11 );

  {
    const MonteCarlo::Estimator& estimator =
      event_handler.getEstimator( estimator_11->getId() );

    FRENSIE_CHECK( &estimator == estimator_11.get() );
  }

  event_handler.addEstimator( estimator_12 );

  {
    const MonteCarlo::Estimator& estimator =
      event_handler.getEstimator( estimator_12->getId() );

    FRENSIE_CHECK( &estimator == estimator_12.get() );
  }

  event_handler.addEstimator( estimator_13 );

  {
    const MonteCarlo::Estimator& estimator =
      event_handler.getEstimator( estimator_13->getId() );

    FRENSIE_CHECK( &estimator == estimator_13.get() );
  }

  event_handler.addEstimator( estimator_14 );

  {
    const MonteCarlo::Estimator& estimator =
      event_handler.getEstimator( estimator_14->getId() );

    FRENSIE_CHECK( &estimator == estimator_14.get() );
  }

  event_handler.addEstimator( estimator_15 );

  {
    const MonteCarlo::Estimator& estimator =
      event_handler.getEstimator( estimator_15->getId() );

    FRENSIE_CHECK( &estimator == estimator_15.get() );
  }

  event_handler.addEstimator( mesh_estimator_1 );

  {
    const MonteCarlo::Estimator& estimator =
      event_handler.getEstimator( mesh_estimator_1->getId() );

    FRENSIE_CHECK( &estimator == mesh_estimator_1.get() );
  }

  event_handler.addEstimator( mesh_estimator_2 );

  {
    const MonteCarlo::Estimator& estimator =
      event_handler.getEstimator( mesh_estimator_2->getId() );

    FRENSIE_CHECK( &estimator == mesh_estimator_2.get() );
  }

  event_handler.addEstimator( mesh_estimator_3 );

  {
    const MonteCarlo::Estimator& estimator =
      event_handler.getEstimator( mesh_estimator_3->getId() );

    FRENSIE_CHECK( &estimator == mesh_estimator_3.get() );
  }

}

//---------------------------------------------------------------------------//
// Check that particle trackers can be added
FRENSIE_UNIT_TEST( EventHandler, addParticleTracker )
{
  MonteCarlo::EventHandler event_handler;

  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfParticleTrackers(), 0 );

  FRENSIE_REQUIRE_NO_THROW( event_handler.addParticleTracker( particle_tracker ) );
  FRENSIE_CHECK( event_handler.doesParticleTrackerExist( particle_tracker->getId() ) );
  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfParticleTrackers(), 1 );
}

//---------------------------------------------------------------------------//
// Check that particle trackers can be added when a model has been assigned
FRENSIE_UNIT_TEST( EventHandler, addParticleTracker_model_set )
{
  std::shared_ptr<const Geometry::Model>
    model( new Geometry::InfiniteMediumModel( 1 ) );

  MonteCarlo::EventHandler event_handler( model, MonteCarlo::SimulationProperties() );

  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfParticleTrackers(), 0 );

  FRENSIE_REQUIRE_NO_THROW( event_handler.addParticleTracker( particle_tracker ) );
  FRENSIE_CHECK( event_handler.doesParticleTrackerExist( particle_tracker->getId() ) );
  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfParticleTrackers(), 1 );
}

//---------------------------------------------------------------------------//
// Check that stored particle trackers can be returned
FRENSIE_UNIT_TEST( EventHandler, getParticleTracker )
{
  MonteCarlo::EventHandler event_handler;

  event_handler.addParticleTracker( particle_tracker );

  {
    const MonteCarlo::ParticleTracker& tracker =
      event_handler.getParticleTracker( particle_tracker->getId() );

    FRENSIE_CHECK( &tracker == particle_tracker.get() );
  }
}

//---------------------------------------------------------------------------//
// Check that the dispatchers can be returned
FRENSIE_UNIT_TEST( EventHandler, get_dispatcher )
{
  MonteCarlo::EventHandler event_handler;

  event_handler.addEstimator( estimator_1 );
  event_handler.addEstimator( estimator_2 );
  event_handler.addEstimator( estimator_3 );
  event_handler.addEstimator( estimator_4 );
  event_handler.addEstimator( estimator_5 );
  event_handler.addEstimator( estimator_6 );
  event_handler.addEstimator( estimator_7 );
  event_handler.addEstimator( estimator_8 );
  event_handler.addEstimator( estimator_9 );
  event_handler.addEstimator( estimator_10 );
  event_handler.addEstimator( estimator_11 );
  event_handler.addEstimator( estimator_12 );
  event_handler.addEstimator( estimator_13 );
  event_handler.addEstimator( estimator_14 );
  event_handler.addEstimator( estimator_15 );
  event_handler.addEstimator( mesh_estimator_1 );
  event_handler.addEstimator( mesh_estimator_2 );
  event_handler.addEstimator( mesh_estimator_3 );
  event_handler.addParticleTracker( particle_tracker );

  FRENSIE_CHECK_EQUAL( event_handler.getParticleCollidingInCellEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleCollidingInCellEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 2 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleCollidingInCellEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleCollidingInCellEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 2 );

  FRENSIE_CHECK_EQUAL( event_handler.getParticleSubtrackEndingInCellEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleSubtrackEndingInCellEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 2 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleSubtrackEndingInCellEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleSubtrackEndingInCellEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 2 );

  FRENSIE_CHECK_EQUAL( event_handler.getParticleEnteringCellEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::PHOTON ), 3 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleEnteringCellEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 3 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleEnteringCellEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers( MonteCarlo::PHOTON ), 3 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleEnteringCellEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 3 );

  FRENSIE_CHECK_EQUAL( event_handler.getParticleLeavingCellEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::PHOTON ), 3 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleLeavingCellEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 3 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleLeavingCellEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers( MonteCarlo::PHOTON ), 3 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleLeavingCellEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 3 );

  FRENSIE_CHECK_EQUAL( event_handler.getParticleCrossingSurfaceEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::PHOTON ), 2 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleCrossingSurfaceEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 4 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleCrossingSurfaceEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers( MonteCarlo::PHOTON ), 2 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleCrossingSurfaceEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 4 );

  FRENSIE_CHECK_EQUAL( event_handler.getParticleSubtrackEndingGlobalEventDispatcher().getNumberOfObservers( MonteCarlo::PHOTON ), 2 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleSubtrackEndingGlobalEventDispatcher().getNumberOfObservers( MonteCarlo::ELECTRON ), 3 );

  FRENSIE_CHECK_EQUAL( event_handler.getParticleGoneGlobalEventDispatcher().getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleGoneGlobalEventDispatcher().getNumberOfObservers( MonteCarlo::ELECTRON ), 1 );
}

//---------------------------------------------------------------------------//
// Check that the number of histories can be returned
FRENSIE_UNIT_TEST( EventHandler, getNumberOfCommittedHistories )
{
  MonteCarlo::EventHandler event_handler;

  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfCommittedHistories(), 0 );

  event_handler.commitObserverHistoryContributions();

  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfCommittedHistories(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the elapsed simulation time can be returned
FRENSIE_UNIT_TEST( EventHandler, getElapsedTime )
{
  MonteCarlo::EventHandler event_handler;

  FRENSIE_CHECK_EQUAL( event_handler.getElapsedTime(), 0.0 );

  event_handler.updateObserversFromParticleSimulationStartedEvent();

  std::shared_ptr<Utility::Timer> timer =
    Utility::GlobalMPISession::createTimer();

  timer->start();

  while( timer->elapsed().count() < 0.02 );

  timer->stop();

  event_handler.updateObserversFromParticleSimulationStoppedEvent();

  FRENSIE_CHECK( event_handler.getElapsedTime() >= 0.02 );
}

//---------------------------------------------------------------------------//
// Check if observers can be updated from a particle colliding in cell event
FRENSIE_UNIT_TEST( EventHandler,
                   updateObserversFromParticleCollidingInCellEvent )
{
  MonteCarlo::EventHandler event_handler;

  event_handler.addEstimator( estimator_1 );
  event_handler.addEstimator( estimator_2 );
  event_handler.addEstimator( estimator_3 );
  event_handler.addEstimator( estimator_4 );
  event_handler.addEstimator( estimator_5 );
  event_handler.addEstimator( estimator_6 );
  event_handler.addEstimator( estimator_7 );
  event_handler.addEstimator( estimator_8 );
  event_handler.addEstimator( estimator_9 );
  event_handler.addEstimator( estimator_10 );
  event_handler.addEstimator( estimator_11 );
  event_handler.addEstimator( estimator_12 );
  event_handler.addEstimator( estimator_13 );
  event_handler.addEstimator( estimator_14 );
  event_handler.addEstimator( estimator_15 );
  event_handler.addEstimator( mesh_estimator_1 );
  event_handler.addEstimator( mesh_estimator_2 );
  event_handler.addEstimator( mesh_estimator_3 );
  event_handler.addParticleTracker( particle_tracker );

  {
    std::shared_ptr<const Geometry::Model>
      local_model( new Geometry::InfiniteMediumModel( 1 ) );

    MonteCarlo::PhotonState photon( 0ull );
    photon.setWeight( 1.0 );
    photon.setEnergy( 1.0 );
    photon.embedInModel( local_model );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    event_handler.updateObserversFromParticleCollidingInCellEvent( photon, 1.0 );

    FRENSIE_CHECK( estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    MonteCarlo::ElectronState electron( 0ull );
    electron.setWeight( 1.0 );
    electron.setEnergy( 1.0 );
    electron.embedInModel( local_model );

    event_handler.updateObserversFromParticleCollidingInCellEvent( electron, 1.0 );

    FRENSIE_CHECK( estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    event_handler.commitObserverHistoryContributions();

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    Utility::ArrayView<const double> first_moments, second_moments;
    first_moments = estimator_1->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_1->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_1->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_1->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_2->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_2->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_2->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_2->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_3->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_3->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {-1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_3->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_3->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );
  }

  {
    std::shared_ptr<const Geometry::Model>
      local_model( new Geometry::InfiniteMediumModel( 2 ) );

    MonteCarlo::PhotonState photon( 0ull );
    photon.setWeight( 1.0 );
    photon.setEnergy( 1.0 );
    photon.embedInModel( local_model );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    event_handler.updateObserversFromParticleCollidingInCellEvent( photon, 1.0 );

    FRENSIE_CHECK( estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    MonteCarlo::ElectronState electron( 0ull );
    electron.setWeight( 1.0 );
    electron.setEnergy( 1.0 );
    electron.embedInModel( local_model );

    event_handler.updateObserversFromParticleCollidingInCellEvent( electron, 1.0 );

    FRENSIE_CHECK( estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    event_handler.commitObserverHistoryContributions();

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    Utility::ArrayView<const double> first_moments, second_moments;
    first_moments = estimator_1->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_1->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_1->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_1->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_2->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_2->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_2->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_2->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_3->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_3->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {-1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_3->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_3->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {-1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );
  }
}

//---------------------------------------------------------------------------//
// Check if observers can be updated from a particle subtrack ending in cell
// event
FRENSIE_UNIT_TEST( EventHandler,
                   updateObserversFromParticleSubtrackEndingInCellEvent )
{
  MonteCarlo::EventHandler event_handler;

  event_handler.addEstimator( estimator_1 );
  event_handler.addEstimator( estimator_2 );
  event_handler.addEstimator( estimator_3 );
  event_handler.addEstimator( estimator_4 );
  event_handler.addEstimator( estimator_5 );
  event_handler.addEstimator( estimator_6 );
  event_handler.addEstimator( estimator_7 );
  event_handler.addEstimator( estimator_8 );
  event_handler.addEstimator( estimator_9 );
  event_handler.addEstimator( estimator_10 );
  event_handler.addEstimator( estimator_11 );
  event_handler.addEstimator( estimator_12 );
  event_handler.addEstimator( estimator_13 );
  event_handler.addEstimator( estimator_14 );
  event_handler.addEstimator( estimator_15 );
  event_handler.addEstimator( mesh_estimator_1 );
  event_handler.addEstimator( mesh_estimator_2 );
  event_handler.addEstimator( mesh_estimator_3 );
  event_handler.addParticleTracker( particle_tracker );

  {
    MonteCarlo::PhotonState photon( 0ull );
    photon.setWeight( 1.0 );
    photon.setEnergy( 1.0 );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    event_handler.updateObserversFromParticleSubtrackEndingInCellEvent( photon, 1, 1.0 );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    MonteCarlo::ElectronState electron( 0ull );
    electron.setWeight( 1.0 );
    electron.setEnergy( 1.0 );

    event_handler.updateObserversFromParticleSubtrackEndingInCellEvent( electron, 1, 1.0 );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    event_handler.commitObserverHistoryContributions();

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    Utility::ArrayView<const double> first_moments, second_moments;
    first_moments = estimator_4->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_4->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_4->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_4->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_5->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_5->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_6->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_6->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {-1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_6->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_6->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );
  }

  {
    MonteCarlo::PhotonState photon( 0ull );
    photon.setWeight( 1.0 );
    photon.setEnergy( 1.0 );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    event_handler.updateObserversFromParticleSubtrackEndingInCellEvent( photon, 2, 1.0 );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    MonteCarlo::ElectronState electron( 0ull );
    electron.setWeight( 1.0 );
    electron.setEnergy( 1.0 );

    event_handler.updateObserversFromParticleSubtrackEndingInCellEvent( electron, 2, 1.0 );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    event_handler.commitObserverHistoryContributions();

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    Utility::ArrayView<const double> first_moments, second_moments;
    first_moments = estimator_4->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_4->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_4->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_4->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_5->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_5->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_5->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_5->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_6->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_6->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {-1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_6->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_6->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {-1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );
  }
}

//---------------------------------------------------------------------------//
// Check if observers can be updated from particle entering cell and particle
// leaving cell events
FRENSIE_UNIT_TEST( EventHandler,
                   updateObserversFromParticleEntering_LeavingCellEvent )
{
  MonteCarlo::EventHandler event_handler;

  event_handler.addEstimator( estimator_1 );
  event_handler.addEstimator( estimator_2 );
  event_handler.addEstimator( estimator_3 );
  event_handler.addEstimator( estimator_4 );
  event_handler.addEstimator( estimator_5 );
  event_handler.addEstimator( estimator_6 );
  event_handler.addEstimator( estimator_7 );
  event_handler.addEstimator( estimator_8 );
  event_handler.addEstimator( estimator_9 );
  event_handler.addEstimator( estimator_10 );
  event_handler.addEstimator( estimator_11 );
  event_handler.addEstimator( estimator_12 );
  event_handler.addEstimator( estimator_13 );
  event_handler.addEstimator( estimator_14 );
  event_handler.addEstimator( estimator_15 );
  event_handler.addEstimator( mesh_estimator_1 );
  event_handler.addEstimator( mesh_estimator_2 );
  event_handler.addEstimator( mesh_estimator_3 );
  event_handler.addParticleTracker( particle_tracker );

  {
    MonteCarlo::PhotonState photon( 0ull );
    photon.setWeight( 1.0 );
    photon.setEnergy( 2.0 );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    event_handler.updateObserversFromParticleEnteringCellEvent( photon, 1 );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    photon.setEnergy( 1.0 );

    event_handler.updateObserversFromParticleLeavingCellEvent( photon, 1 );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    MonteCarlo::ElectronState electron( 0ull );
    electron.setWeight( 1.0 );
    electron.setEnergy( 2.0 );

    event_handler.updateObserversFromParticleEnteringCellEvent( electron, 1 );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    electron.setEnergy( 1.0 );

    event_handler.updateObserversFromParticleLeavingCellEvent( electron, 1 );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    event_handler.commitObserverHistoryContributions();

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    Utility::ArrayView<const double> first_moments, second_moments;
    first_moments = estimator_7->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_7->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_7->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_7->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_8->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_8->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {2.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {4.0} ) );

    first_moments = estimator_8->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_8->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_9->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_9->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_9->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_9->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );
  }

  {
    MonteCarlo::PhotonState photon( 0ull );
    photon.setWeight( 1.0 );
    photon.setEnergy( 2.0 );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    event_handler.updateObserversFromParticleEnteringCellEvent( photon, 2 );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    photon.setEnergy( 1.0 );

    event_handler.updateObserversFromParticleLeavingCellEvent( photon, 2 );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    MonteCarlo::ElectronState electron( 0ull );
    electron.setWeight( 1.0 );
    electron.setEnergy( 2.0 );

    event_handler.updateObserversFromParticleEnteringCellEvent( electron, 2 );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    electron.setEnergy( 1.0 );

    event_handler.updateObserversFromParticleLeavingCellEvent( electron, 2 );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    event_handler.commitObserverHistoryContributions();

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    Utility::ArrayView<const double> first_moments, second_moments;
    first_moments = estimator_7->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_7->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_7->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_7->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_8->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_8->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {2.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {4.0} ) );

    first_moments = estimator_8->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_8->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {2.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {4.0} ) );
  }
}

//---------------------------------------------------------------------------//
// Check if observers can be updated from a particle crossing surface event
FRENSIE_UNIT_TEST( EventHandler,
                   updateObserversFromParticleCrossingSurfaceEvent )
{
  MonteCarlo::EventHandler event_handler;

  event_handler.addEstimator( estimator_1 );
  event_handler.addEstimator( estimator_2 );
  event_handler.addEstimator( estimator_3 );
  event_handler.addEstimator( estimator_4 );
  event_handler.addEstimator( estimator_5 );
  event_handler.addEstimator( estimator_6 );
  event_handler.addEstimator( estimator_7 );
  event_handler.addEstimator( estimator_8 );
  event_handler.addEstimator( estimator_9 );
  event_handler.addEstimator( estimator_10 );
  event_handler.addEstimator( estimator_11 );
  event_handler.addEstimator( estimator_12 );
  event_handler.addEstimator( estimator_13 );
  event_handler.addEstimator( estimator_14 );
  event_handler.addEstimator( estimator_15 );
  event_handler.addEstimator( mesh_estimator_1 );
  event_handler.addEstimator( mesh_estimator_2 );
  event_handler.addEstimator( mesh_estimator_3 );
  event_handler.addParticleTracker( particle_tracker );

  {
    MonteCarlo::PhotonState photon( 0ull );
    photon.setWeight( 1.0 );
    photon.setEnergy( 1.0 );
    photon.setDirection( 1.0, 0.0, 0.0 );

    double surface_normal[3] = {1.0, 0.0, 0.0};

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    event_handler.updateObserversFromParticleCrossingSurfaceEvent( photon, 1, surface_normal );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    MonteCarlo::ElectronState electron( 0ull );
    electron.setWeight( 1.0 );
    electron.setEnergy( 1.0 );
    electron.setDirection( -1.0, 0.0, 0.0 );

    event_handler.updateObserversFromParticleCrossingSurfaceEvent( electron, 1, surface_normal );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    event_handler.commitObserverHistoryContributions();

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    Utility::ArrayView<const double> first_moments, second_moments;
    first_moments = estimator_10->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_10->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_10->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_10->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_11->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_11->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_11->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_11->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_12->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_12->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {-1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_12->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_12->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_13->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_13->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_13->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_13->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_14->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_14->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_14->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_14->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_15->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_15->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {-1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_15->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_15->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );
  }

  {
    MonteCarlo::PhotonState photon( 0ull );
    photon.setWeight( 1.0 );
    photon.setEnergy( 1.0 );
    photon.setDirection( 1.0, 0.0, 0.0 );

    double surface_normal[3] = {1.0, 0.0, 0.0};

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    event_handler.updateObserversFromParticleCrossingSurfaceEvent( photon, 2, surface_normal );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    MonteCarlo::ElectronState electron( 0ull );
    electron.setWeight( 1.0 );
    electron.setEnergy( 1.0 );
    electron.setDirection( -1.0, 0.0, 0.0 );

    event_handler.updateObserversFromParticleCrossingSurfaceEvent( electron, 2, surface_normal );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    event_handler.commitObserverHistoryContributions();

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    Utility::ArrayView<const double> first_moments, second_moments;
    first_moments = estimator_10->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_10->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_10->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_10->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_11->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_11->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_11->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_11->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_12->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_12->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {-1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_12->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_12->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {-1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_13->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_13->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_13->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_13->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_14->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_14->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_14->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_14->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_15->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_15->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {-1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_15->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_15->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {-1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );
  }
}

//---------------------------------------------------------------------------//
// Check if observers can be updated from particle subtrack ending and
// particle gone events
FRENSIE_UNIT_TEST( EventHandler,
                   updateObserversFromParticleSubtrackEnding_GoneGlobalEvent )
{
  MonteCarlo::EventHandler event_handler;

  event_handler.addEstimator( estimator_1 );
  event_handler.addEstimator( estimator_2 );
  event_handler.addEstimator( estimator_3 );
  event_handler.addEstimator( estimator_4 );
  event_handler.addEstimator( estimator_5 );
  event_handler.addEstimator( estimator_6 );
  event_handler.addEstimator( estimator_7 );
  event_handler.addEstimator( estimator_8 );
  event_handler.addEstimator( estimator_9 );
  event_handler.addEstimator( estimator_10 );
  event_handler.addEstimator( estimator_11 );
  event_handler.addEstimator( estimator_12 );
  event_handler.addEstimator( estimator_13 );
  event_handler.addEstimator( estimator_14 );
  event_handler.addEstimator( estimator_15 );
  event_handler.addEstimator( mesh_estimator_1 );
  event_handler.addEstimator( mesh_estimator_2 );
  event_handler.addEstimator( mesh_estimator_3 );
  event_handler.addParticleTracker( particle_tracker );

  {
    MonteCarlo::ElectronState electron( 0ull );
    electron.setWeight( 1.0 );
    electron.setEnergy( 1.0 );

    double start_point[3] = {0.5, 0.5, 0.0};
    double end_point[3] = {0.5, 0.5, 2.0};

    event_handler.updateObserversFromParticleSubtrackEndingGlobalEvent( electron, start_point, end_point );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( mesh_estimator_3->hasUncommittedHistoryContribution() );

    electron.setAsGone();

    event_handler.updateObserversFromParticleGoneGlobalEvent( electron );

    MonteCarlo::PhotonState photon( 0ull );
    photon.setWeight( 1.0 );
    photon.setEnergy( 1.0 );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( mesh_estimator_3->hasUncommittedHistoryContribution() );

    event_handler.updateObserversFromParticleSubtrackEndingGlobalEvent( photon, start_point, end_point );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( mesh_estimator_3->hasUncommittedHistoryContribution() );

    photon.setAsGone();

    event_handler.updateObserversFromParticleGoneGlobalEvent( photon );

    event_handler.commitObserverHistoryContributions();

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_4->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_5->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_6->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_7->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_8->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_9->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_10->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_11->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_12->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_13->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_14->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_15->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !mesh_estimator_3->hasUncommittedHistoryContribution() );

    Utility::ArrayView<const double> first_moments, second_moments;
    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 0 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 1 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 2 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 3 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 3 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 4 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 4 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 5 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 5 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 6 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 6 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 7 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 7 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 0 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 1 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 2 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 3 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 3 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 4 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 4 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 5 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 5 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 6 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 6 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 7 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 7 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_3->getEntityBinDataFirstMoments( 0 );
    second_moments = mesh_estimator_3->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {-1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = mesh_estimator_3->getEntityBinDataFirstMoments( 1 );
    second_moments = mesh_estimator_3->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_3->getEntityBinDataFirstMoments( 2 );
    second_moments = mesh_estimator_3->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_3->getEntityBinDataFirstMoments( 3 );
    second_moments = mesh_estimator_3->getEntityBinDataSecondMoments( 3 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_3->getEntityBinDataFirstMoments( 4 );
    second_moments = mesh_estimator_3->getEntityBinDataSecondMoments( 4 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {-1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = mesh_estimator_3->getEntityBinDataFirstMoments( 5 );
    second_moments = mesh_estimator_3->getEntityBinDataSecondMoments( 5 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_3->getEntityBinDataFirstMoments( 6 );
    second_moments = mesh_estimator_3->getEntityBinDataSecondMoments( 6 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_3->getEntityBinDataFirstMoments( 7 );
    second_moments = mesh_estimator_3->getEntityBinDataSecondMoments( 7 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    MonteCarlo::ParticleTracker::OverallHistoryMap history_map;

    particle_tracker->getHistoryData( history_map );

    FRENSIE_REQUIRE( history_map.find( 0 ) != history_map.end() );
    FRENSIE_REQUIRE( history_map[0].find( MonteCarlo::PHOTON ) !=
                     history_map[0].end() );
    FRENSIE_REQUIRE( history_map[0].find( MonteCarlo::ELECTRON ) !=
                     history_map[0].end() );
  }
}

//---------------------------------------------------------------------------//
// Check if distributed observers can be updated
FRENSIE_UNIT_TEST( EventHandler, update_parallel )
{
  MonteCarlo::EventHandler event_handler;

  event_handler.addEstimator( estimator_1 );
  event_handler.addEstimator( estimator_2 );
  event_handler.addEstimator( estimator_3 );
  event_handler.addEstimator( estimator_4 );
  event_handler.addEstimator( estimator_5 );
  event_handler.addEstimator( estimator_6 );
  event_handler.addEstimator( estimator_7 );
  event_handler.addEstimator( estimator_8 );
  event_handler.addEstimator( estimator_9 );
  event_handler.addEstimator( estimator_10 );
  event_handler.addEstimator( estimator_11 );
  event_handler.addEstimator( estimator_12 );
  event_handler.addEstimator( estimator_13 );
  event_handler.addEstimator( estimator_14 );
  event_handler.addEstimator( estimator_15 );
  event_handler.addEstimator( mesh_estimator_1 );
  event_handler.addEstimator( mesh_estimator_2 );
  event_handler.addEstimator( mesh_estimator_3 );
  event_handler.addParticleTracker( particle_tracker );

  event_handler.resetObserverData();

  unsigned threads =
    Utility::OpenMPProperties::getRequestedNumberOfThreads();

  event_handler.enableThreadSupport( threads );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  comm->barrier();

  event_handler.updateObserversFromParticleSimulationStartedEvent();

  #pragma omp parallel num_threads( threads )
  {
    std::shared_ptr<const Geometry::Model>
      local_model( new Geometry::InfiniteMediumModel( 1 ) );

    MonteCarlo::PhotonState photon( comm->rank()*threads + Utility::OpenMPProperties::getThreadId() );
    photon.setWeight( 1.0 );
    photon.setEnergy( 2.0 );
    photon.setDirection( 1.0, 0.0, 0.0 );
    photon.embedInModel( local_model );

    MonteCarlo::ElectronState electron( comm->rank()*threads + Utility::OpenMPProperties::getThreadId() );
    electron.setWeight( 1.0 );
    electron.setEnergy( 2.0 );
    electron.setDirection( -1.0, 0.0, 0.0 );
    electron.embedInModel( local_model );

    double surface_normal[3] = {1.0, 0.0, 0.0};
    double start_point[3] = {0.5, 0.5, 0.0};
    double end_point[3] = {0.5, 0.5, 2.0};

    event_handler.updateObserversFromParticleCollidingInCellEvent( photon, 1.0 );
    event_handler.updateObserversFromParticleCollidingInCellEvent( electron, 1.0 );
    event_handler.updateObserversFromParticleSubtrackEndingInCellEvent( photon, 1, 1.0 );
    event_handler.updateObserversFromParticleSubtrackEndingInCellEvent( electron, 1, 1.0 );
    event_handler.updateObserversFromParticleEnteringCellEvent( photon, 1 );
    event_handler.updateObserversFromParticleEnteringCellEvent( electron, 1 );

    photon.setEnergy( 1.0 );
    electron.setEnergy( 1.0 );

    event_handler.updateObserversFromParticleLeavingCellEvent( photon, 1 );
    event_handler.updateObserversFromParticleLeavingCellEvent( electron, 1 );

    event_handler.updateObserversFromParticleCrossingSurfaceEvent( photon, 1, surface_normal );
    event_handler.updateObserversFromParticleCrossingSurfaceEvent( electron, 1, surface_normal );
    event_handler.updateObserversFromParticleSubtrackEndingGlobalEvent( photon, start_point, end_point );
    event_handler.updateObserversFromParticleSubtrackEndingGlobalEvent( electron, start_point, end_point );

    photon.setAsGone();
    electron.setAsGone();

    event_handler.updateObserversFromParticleGoneGlobalEvent( photon );
    event_handler.updateObserversFromParticleGoneGlobalEvent( electron );

    event_handler.commitObserverHistoryContributions();
  }

  comm->barrier();

  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfCommittedHistoriesSinceLastSnapshot(),
                       threads );
  FRENSIE_CHECK( event_handler.getElapsedTimeSinceLastSnapshot() > 0.0 );
  
  event_handler.takeSnapshotOfObserverStates();

  event_handler.updateObserversFromParticleSimulationStoppedEvent();

  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfCommittedHistoriesSinceLastSnapshot(),
                       0 );
  FRENSIE_CHECK_SMALL( event_handler.getElapsedTimeSinceLastSnapshot(), 1e-3 );
  
  event_handler.reduceObserverData( *comm, 0 );

  if( comm->rank() == 0 )
  {
    FRENSIE_CHECK_EQUAL( event_handler.getNumberOfCommittedHistories(),
                         comm->size()*threads );

    Utility::ArrayView<const double> first_moments, second_moments;
    first_moments = estimator_1->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_1->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0*comm->size()*threads} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0*comm->size()*threads} ) );

    first_moments = estimator_1->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_1->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_2->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_2->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {2.0*comm->size()*threads} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {4.0*comm->size()*threads} ) );

    first_moments = estimator_2->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_2->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_4->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_4->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0*comm->size()*threads} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0*comm->size()*threads} ) );

    first_moments = estimator_4->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_4->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_5->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_5->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {2.0*comm->size()*threads} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {4.0*comm->size()*threads} ) );

    first_moments = estimator_7->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_7->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_7->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_7->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0*comm->size()*threads} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0*comm->size()*threads} ) );

    first_moments = estimator_7->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_7->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_8->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_8->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {2.0*comm->size()*threads} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {4.0*comm->size()*threads} ) );

    first_moments = estimator_8->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_8->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_10->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_10->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0*comm->size()*threads} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0*comm->size()*threads} ) );

    first_moments = estimator_10->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_10->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_11->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_11->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0*comm->size()*threads} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0*comm->size()*threads} ) );

    first_moments = estimator_11->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_11->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_13->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_13->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0*comm->size()*threads} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0*comm->size()*threads} ) );

    first_moments = estimator_13->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_13->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_14->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_14->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0*comm->size()*threads} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0*comm->size()*threads} ) );

    first_moments = estimator_14->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_14->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 0 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0*comm->size()*threads} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0*comm->size()*threads} ) );

    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 1 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 2 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 3 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 3 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 4 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 4 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0*comm->size()*threads} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0*comm->size()*threads} ) );

    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 5 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 5 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 6 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 6 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 7 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 7 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 0 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0*comm->size()*threads} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0*comm->size()*threads} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 1 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 2 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 3 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 3 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 4 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 4 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0*comm->size()*threads} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0*comm->size()*threads} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 5 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 5 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 6 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 6 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 7 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 7 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    MonteCarlo::ParticleTracker::OverallHistoryMap history_map;

    particle_tracker->getHistoryData( history_map );

    for( size_t i = 0; i < comm->size()*threads; ++i )
    {
      FRENSIE_REQUIRE( history_map.find( i ) != history_map.end() );
      FRENSIE_REQUIRE( history_map[i].find( MonteCarlo::PHOTON ) !=
                       history_map[i].end() );
      FRENSIE_REQUIRE( history_map[i].find( MonteCarlo::ELECTRON ) !=
                       history_map[i].end() );
    }
  }
  else
  {
    FRENSIE_CHECK_EQUAL( event_handler.getNumberOfCommittedHistories(), 0 );

    Utility::ArrayView<const double> first_moments, second_moments;
    first_moments = estimator_1->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_1->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_1->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_1->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_2->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_2->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_2->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_2->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_4->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_4->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_4->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_4->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_5->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_5->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_7->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_7->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_7->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_7->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_7->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_7->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_8->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_8->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_8->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_8->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_10->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_10->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_10->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_10->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_11->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_11->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_11->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_11->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_13->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_13->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_13->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_13->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_14->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_14->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_14->getEntityBinDataFirstMoments( 2 );
    second_moments = estimator_14->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 0 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 1 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 2 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 3 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 3 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 4 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 4 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 5 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 5 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 6 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 6 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_1->getEntityBinDataFirstMoments( 7 );
    second_moments = mesh_estimator_1->getEntityBinDataSecondMoments( 7 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 0 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 1 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 2 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 3 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 3 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 4 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 4 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 5 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 5 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 6 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 6 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = mesh_estimator_2->getEntityBinDataFirstMoments( 7 );
    second_moments = mesh_estimator_2->getEntityBinDataSecondMoments( 7 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    MonteCarlo::ParticleTracker::OverallHistoryMap history_map;

    particle_tracker->getHistoryData( history_map );

    FRENSIE_CHECK( history_map.empty() );
  }
}

//---------------------------------------------------------------------------//
// Check that the observer summaries can be printed
FRENSIE_UNIT_TEST( EventHandler, printObserverSummaries )
{
  MonteCarlo::EventHandler event_handler;

  event_handler.addEstimator( estimator_1 );
  event_handler.addEstimator( estimator_2 );
  event_handler.addEstimator( estimator_3 );
  event_handler.addEstimator( estimator_4 );
  event_handler.addEstimator( estimator_5 );
  event_handler.addEstimator( estimator_6 );
  event_handler.addEstimator( estimator_7 );
  event_handler.addEstimator( estimator_8 );
  event_handler.addEstimator( estimator_9 );
  event_handler.addEstimator( estimator_10 );
  event_handler.addEstimator( estimator_11 );
  event_handler.addEstimator( estimator_12 );
  event_handler.addEstimator( estimator_13 );
  event_handler.addEstimator( estimator_14 );
  event_handler.addEstimator( estimator_15 );
  event_handler.addEstimator( mesh_estimator_1 );
  event_handler.addEstimator( mesh_estimator_2 );
  event_handler.addEstimator( mesh_estimator_3 );
  event_handler.addParticleTracker( particle_tracker );

  event_handler.resetObserverData();

  event_handler.updateObserversFromParticleSimulationStartedEvent();

  event_handler.commitObserverHistoryContributions();
  event_handler.commitObserverHistoryContributions();

  event_handler.updateObserversFromParticleSimulationStoppedEvent();

  std::ostringstream oss;

  FRENSIE_REQUIRE_NO_THROW( event_handler.printObserverSummaries( oss ) );

  std::cout << oss.str() << std::endl;
}

//---------------------------------------------------------------------------//
// Check that the observer summaries can be logged
FRENSIE_UNIT_TEST( EventHandler, logObserverSummaries )
{
  MonteCarlo::EventHandler event_handler;

  event_handler.addEstimator( estimator_1 );
  event_handler.addEstimator( estimator_2 );
  event_handler.addEstimator( estimator_3 );
  event_handler.addEstimator( estimator_4 );
  event_handler.addEstimator( estimator_5 );
  event_handler.addEstimator( estimator_6 );
  event_handler.addEstimator( estimator_7 );
  event_handler.addEstimator( estimator_8 );
  event_handler.addEstimator( estimator_9 );
  event_handler.addEstimator( estimator_10 );
  event_handler.addEstimator( estimator_11 );
  event_handler.addEstimator( estimator_12 );
  event_handler.addEstimator( estimator_13 );
  event_handler.addEstimator( estimator_14 );
  event_handler.addEstimator( estimator_15 );
  event_handler.addEstimator( mesh_estimator_1 );
  event_handler.addEstimator( mesh_estimator_2 );
  event_handler.addEstimator( mesh_estimator_3 );
  event_handler.addParticleTracker( particle_tracker );

  event_handler.resetObserverData();

  event_handler.updateObserversFromParticleSimulationStartedEvent();

  event_handler.commitObserverHistoryContributions();
  event_handler.commitObserverHistoryContributions();

  event_handler.updateObserversFromParticleSimulationStoppedEvent();

  FRENSIE_REQUIRE_NO_THROW( event_handler.logObserverSummaries() );
}

//---------------------------------------------------------------------------//
// Check that an event handler can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( EventHandler, archive, TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_event_handler" );
  std::ostringstream archive_ostream;

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  if( comm->rank() == 0 )
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::EventHandler event_handler;

    event_handler.setSimulationCompletionCriterion( MonteCarlo::ParticleHistorySimulationCompletionCriterion::createHistoryCountCriterion( 1 ) );

    std::shared_ptr<MonteCarlo::WeightMultipliedCellCollisionFluxEstimator>
      local_estimator_1( new MonteCarlo::WeightMultipliedCellCollisionFluxEstimator(
                                              100, 1.0, {1, 2}, {1.0, 1.0} ) );

    local_estimator_1->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

    std::shared_ptr<MonteCarlo::WeightMultipliedCellCollisionFluxEstimator>
      local_estimator_2( new MonteCarlo::WeightMultipliedCellCollisionFluxEstimator(
                                              101, 1.0, {1, 2}, {1.0, 1.0} ) );

    local_estimator_2->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );

    std::shared_ptr<MonteCarlo::WeightMultipliedCellTrackLengthFluxEstimator>
      local_estimator_4( new MonteCarlo::WeightMultipliedCellTrackLengthFluxEstimator(
                                              102, 1.0, {1, 2}, {1.0, 1.0} ) );

    local_estimator_4->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

    std::shared_ptr<MonteCarlo::WeightMultipliedCellTrackLengthFluxEstimator>
      local_estimator_5( new MonteCarlo::WeightMultipliedCellTrackLengthFluxEstimator(
                                              103, 1.0, {1, 2}, {1.0, 1.0} ) );

    local_estimator_5->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );

    std::shared_ptr<MonteCarlo::WeightMultipliedCellPulseHeightEstimator>
      local_estimator_7( new MonteCarlo::WeightMultipliedCellPulseHeightEstimator(
                                                          104, 1.0, {1, 2} ) );

    local_estimator_7->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON, MonteCarlo::ELECTRON} ) );

    std::shared_ptr<MonteCarlo::WeightAndEnergyMultipliedCellPulseHeightEstimator>
      local_estimator_8( new MonteCarlo::WeightAndEnergyMultipliedCellPulseHeightEstimator(
                                                          105, 1.0, {1, 2} ) );

    local_estimator_8->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON, MonteCarlo::ELECTRON} ) );

    std::shared_ptr<MonteCarlo::WeightMultipliedSurfaceFluxEstimator>
      local_estimator_10( new MonteCarlo::WeightMultipliedSurfaceFluxEstimator(
                                              106, 1.0, {1, 2}, {1.0, 1.0} ) );

    local_estimator_10->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

    std::shared_ptr<MonteCarlo::WeightAndEnergyMultipliedSurfaceFluxEstimator>
      local_estimator_11( new MonteCarlo::WeightAndEnergyMultipliedSurfaceFluxEstimator(
                                              107, 1.0, {1, 2}, {1.0, 1.0} ) );

    local_estimator_11->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );

    std::shared_ptr<MonteCarlo::WeightMultipliedSurfaceCurrentEstimator>
      local_estimator_13( new MonteCarlo::WeightMultipliedSurfaceCurrentEstimator(
                                                          108, 1.0, {1, 2} ) );

    local_estimator_13->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

    std::shared_ptr<MonteCarlo::WeightAndEnergyMultipliedSurfaceCurrentEstimator>
      local_estimator_14( new MonteCarlo::WeightAndEnergyMultipliedSurfaceCurrentEstimator(
                                                          109, 1.0, {1, 2} ) );

    local_estimator_14->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );

    std::shared_ptr<const Utility::Mesh> hex_mesh(
                           new Utility::StructuredHexMesh( {0.0, 1.0, 2.0},
                                                           {0.0, 1.0, 2.0},
                                                           {0.0, 1.0, 2.0} ) );

    std::shared_ptr<MonteCarlo::WeightMultipliedMeshTrackLengthFluxEstimator>
      local_mesh_estimator_1( new MonteCarlo::WeightMultipliedMeshTrackLengthFluxEstimator(
                                                                  110,
                                                                  1.0,
                                                                  hex_mesh ) );
    local_mesh_estimator_1->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

    std::shared_ptr<MonteCarlo::WeightAndEnergyMultipliedMeshTrackLengthFluxEstimator>
      local_mesh_estimator_2( new MonteCarlo::WeightAndEnergyMultipliedMeshTrackLengthFluxEstimator(
                                                                  111,
                                                                  1.0,
                                                                  hex_mesh ) );
    local_mesh_estimator_2->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );

    std::shared_ptr<MonteCarlo::ParticleTracker> local_particle_tracker(
                                  new MonteCarlo::ParticleTracker( 10, 100 ) );

    event_handler.addEstimator( local_estimator_1 );
    event_handler.addEstimator( local_estimator_2 );
    event_handler.addEstimator( local_estimator_4 );
    event_handler.addEstimator( local_estimator_5 );
    event_handler.addEstimator( local_estimator_7 );
    event_handler.addEstimator( local_estimator_8 );
    event_handler.addEstimator( local_estimator_10 );
    event_handler.addEstimator( local_estimator_11 );
    event_handler.addEstimator( local_estimator_13 );
    event_handler.addEstimator( local_estimator_14 );
    event_handler.addEstimator( local_mesh_estimator_1 );
    event_handler.addEstimator( local_mesh_estimator_2 );
    event_handler.addParticleTracker( local_particle_tracker );

    event_handler.updateObserversFromParticleSimulationStartedEvent();

    std::shared_ptr<Utility::Timer> timer =
      Utility::GlobalMPISession::createTimer();

    timer->start();

    while( timer->elapsed().count() < 0.02 );

    timer->stop();

    std::shared_ptr<const Geometry::Model>
      local_model( new Geometry::InfiniteMediumModel( 1 ) );

    MonteCarlo::PhotonState photon( 0 );
    photon.setWeight( 1.0 );
    photon.setEnergy( 2.0 );
    photon.setDirection( 1.0, 0.0, 0.0 );
    photon.embedInModel( local_model );

    MonteCarlo::ElectronState electron( 0 );
    electron.setWeight( 1.0 );
    electron.setEnergy( 2.0 );
    electron.setDirection( -1.0, 0.0, 0.0 );
    electron.embedInModel( local_model );

    double surface_normal[3] = {1.0, 0.0, 0.0};
    double start_point[3] = {0.5, 0.5, 0.0};
    double end_point[3] = {0.5, 0.5, 2.0};

    event_handler.updateObserversFromParticleCollidingInCellEvent( photon, 1.0 );
    event_handler.updateObserversFromParticleCollidingInCellEvent( electron, 1.0 );
    event_handler.updateObserversFromParticleSubtrackEndingInCellEvent( photon, 1, 1.0 );
    event_handler.updateObserversFromParticleSubtrackEndingInCellEvent( electron, 1, 1.0 );
    event_handler.updateObserversFromParticleEnteringCellEvent( photon, 1 );
    event_handler.updateObserversFromParticleEnteringCellEvent( electron, 1 );

    photon.setEnergy( 1.0 );
    electron.setEnergy( 1.0 );

    event_handler.updateObserversFromParticleLeavingCellEvent( photon, 1 );
    event_handler.updateObserversFromParticleLeavingCellEvent( electron, 1 );

    event_handler.updateObserversFromParticleCrossingSurfaceEvent( photon, 1, surface_normal );
    event_handler.updateObserversFromParticleCrossingSurfaceEvent( electron, 1, surface_normal );
    event_handler.updateObserversFromParticleSubtrackEndingGlobalEvent( photon, start_point, end_point );
    event_handler.updateObserversFromParticleSubtrackEndingGlobalEvent( electron, start_point, end_point );

    photon.setAsGone();
    electron.setAsGone();

    event_handler.updateObserversFromParticleGoneGlobalEvent( photon );
    event_handler.updateObserversFromParticleGoneGlobalEvent( electron );

    event_handler.commitObserverHistoryContributions();
    event_handler.commitObserverHistoryContributions();

    event_handler.updateObserversFromParticleSimulationStoppedEvent();

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( event_handler ) );
  }

  if( comm->rank() == 0 )
  {
    // Copy the archive ostream to an istream
    std::istringstream archive_istream( archive_ostream.str() );

    // Load the archived distributions
    std::unique_ptr<IArchive> iarchive;

    createIArchive( archive_istream, iarchive );

    MonteCarlo::EventHandler event_handler;

    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( event_handler ) );

    iarchive.reset();

    FRENSIE_CHECK_EQUAL( event_handler.getNumberOfCommittedHistories(), 2 );
    FRENSIE_CHECK( event_handler.getElapsedTime() >= 0.02 );
    FRENSIE_CHECK( event_handler.isSimulationComplete() );

    Utility::ArrayView<const double> first_moments, second_moments;
    first_moments = event_handler.getEstimator( 100 ).getEntityBinDataFirstMoments( 1 );
    second_moments = event_handler.getEstimator( 100 ).getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = event_handler.getEstimator( 100 ).getEntityBinDataFirstMoments( 2 );
    second_moments = event_handler.getEstimator( 100 ).getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = event_handler.getEstimator( 101 ).getEntityBinDataFirstMoments( 1 );
    second_moments = event_handler.getEstimator( 101 ).getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = event_handler.getEstimator( 101 ).getEntityBinDataFirstMoments( 2 );
    second_moments = event_handler.getEstimator( 101 ).getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = event_handler.getEstimator( 102 ).getEntityBinDataFirstMoments( 1 );
    second_moments = event_handler.getEstimator( 102 ).getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = event_handler.getEstimator( 102 ).getEntityBinDataFirstMoments( 2 );
    second_moments = event_handler.getEstimator( 102 ).getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = event_handler.getEstimator( 103 ).getEntityBinDataFirstMoments( 1 );
    second_moments = event_handler.getEstimator( 103 ).getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = event_handler.getEstimator( 103 ).getEntityBinDataFirstMoments( 2 );
    second_moments = event_handler.getEstimator( 103 ).getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = event_handler.getEstimator( 104 ).getEntityBinDataFirstMoments( 1 );
    second_moments = event_handler.getEstimator( 104 ).getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = event_handler.getEstimator( 104 ).getEntityBinDataFirstMoments( 2 );
    second_moments = event_handler.getEstimator( 104 ).getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = event_handler.getEstimator( 105 ).getEntityBinDataFirstMoments( 1 );
    second_moments = event_handler.getEstimator( 105 ).getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {2.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {4.0} ) );

    first_moments = event_handler.getEstimator( 105 ).getEntityBinDataFirstMoments( 2 );
    second_moments = event_handler.getEstimator( 105 ).getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = event_handler.getEstimator( 106 ).getEntityBinDataFirstMoments( 1 );
    second_moments = event_handler.getEstimator( 106 ).getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = event_handler.getEstimator( 106 ).getEntityBinDataFirstMoments( 2 );
    second_moments = event_handler.getEstimator( 106 ).getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = event_handler.getEstimator( 107 ).getEntityBinDataFirstMoments( 1 );
    second_moments = event_handler.getEstimator( 107 ).getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = event_handler.getEstimator( 107 ).getEntityBinDataFirstMoments( 2 );
    second_moments = event_handler.getEstimator( 107 ).getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = event_handler.getEstimator( 108 ).getEntityBinDataFirstMoments( 1 );
    second_moments = event_handler.getEstimator( 108 ).getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = event_handler.getEstimator( 108 ).getEntityBinDataFirstMoments( 2 );
    second_moments = event_handler.getEstimator( 108 ).getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = event_handler.getEstimator( 109 ).getEntityBinDataFirstMoments( 1 );
    second_moments = event_handler.getEstimator( 109 ).getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = event_handler.getEstimator( 109 ).getEntityBinDataFirstMoments( 2 );
    second_moments = event_handler.getEstimator( 109 ).getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = event_handler.getEstimator( 110 ).getEntityBinDataFirstMoments( 0 );
    second_moments = event_handler.getEstimator( 110 ).getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = event_handler.getEstimator( 110 ).getEntityBinDataFirstMoments( 1 );
    second_moments = event_handler.getEstimator( 110 ).getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = event_handler.getEstimator( 110 ).getEntityBinDataFirstMoments( 2 );
    second_moments = event_handler.getEstimator( 110 ).getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = event_handler.getEstimator( 110 ).getEntityBinDataFirstMoments( 3 );
    second_moments = event_handler.getEstimator( 110 ).getEntityBinDataSecondMoments( 3 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = event_handler.getEstimator( 110 ).getEntityBinDataFirstMoments( 4 );
    second_moments = event_handler.getEstimator( 110 ).getEntityBinDataSecondMoments( 4 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = event_handler.getEstimator( 110 ).getEntityBinDataFirstMoments( 5 );
    second_moments = event_handler.getEstimator( 110 ).getEntityBinDataSecondMoments( 5 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = event_handler.getEstimator( 110 ).getEntityBinDataFirstMoments( 6 );
    second_moments = event_handler.getEstimator( 110 ).getEntityBinDataSecondMoments( 6 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = event_handler.getEstimator( 110 ).getEntityBinDataFirstMoments( 7 );
    second_moments = event_handler.getEstimator( 110 ).getEntityBinDataSecondMoments( 7 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = event_handler.getEstimator( 111 ).getEntityBinDataFirstMoments( 0 );
    second_moments = event_handler.getEstimator( 111 ).getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = event_handler.getEstimator( 111 ).getEntityBinDataFirstMoments( 1 );
    second_moments = event_handler.getEstimator( 111 ).getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = event_handler.getEstimator( 111 ).getEntityBinDataFirstMoments( 2 );
    second_moments = event_handler.getEstimator( 111 ).getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = event_handler.getEstimator( 111 ).getEntityBinDataFirstMoments( 3 );
    second_moments = event_handler.getEstimator( 111 ).getEntityBinDataSecondMoments( 3 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = event_handler.getEstimator( 111 ).getEntityBinDataFirstMoments( 4 );
    second_moments = event_handler.getEstimator( 111 ).getEntityBinDataSecondMoments( 4 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = event_handler.getEstimator( 111 ).getEntityBinDataFirstMoments( 5 );
    second_moments = event_handler.getEstimator( 111 ).getEntityBinDataSecondMoments( 5 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = event_handler.getEstimator( 111 ).getEntityBinDataFirstMoments( 6 );
    second_moments = event_handler.getEstimator( 111 ).getEntityBinDataSecondMoments( 6 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = event_handler.getEstimator( 111 ).getEntityBinDataFirstMoments( 7 );
    second_moments = event_handler.getEstimator( 111 ).getEntityBinDataSecondMoments( 7 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    MonteCarlo::ParticleTracker::OverallHistoryMap history_map;

    event_handler.getParticleTracker( 10 ).getHistoryData( history_map );

    FRENSIE_REQUIRE( history_map.find( 0 ) != history_map.end() );
    FRENSIE_REQUIRE( history_map[0].find( MonteCarlo::PHOTON ) !=
                     history_map[0].end() );
    FRENSIE_REQUIRE( history_map[0].find( MonteCarlo::ELECTRON ) !=
                     history_map[0].end() );
  }
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

int threads;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "threads",
                                        threads, 1,
                                        "Number of threads to use" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize the estimators
  std::vector<uint64_t> cell_ids( {1, 2} );
  std::vector<double> cell_volumes( {1.0, 1.0} );

  std::vector<uint64_t> surface_ids( {1, 2} );
  std::vector<double> surface_areas( {1.0, 1.0} );

  estimator_1.reset( new MonteCarlo::WeightMultipliedCellCollisionFluxEstimator(
                                                              0,
                                                              1.0,
                                                              cell_ids,
                                                              cell_volumes ) );
  estimator_1->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

  estimator_2.reset( new MonteCarlo::WeightAndEnergyMultipliedCellCollisionFluxEstimator(
                                                              1,
                                                              10.0,
                                                              cell_ids,
                                                              cell_volumes ) );
  estimator_2->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );

  estimator_3.reset( new MonteCarlo::WeightAndChargeMultipliedCellCollisionFluxEstimator(
                                                              2,
                                                              1.0,
                                                              cell_ids,
                                                              cell_volumes ) );
  estimator_3->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );

  estimator_4.reset( new MonteCarlo::WeightMultipliedCellTrackLengthFluxEstimator(
                                                              3,
                                                              1.0,
                                                              cell_ids,
                                                              cell_volumes ) );
  estimator_4->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

  estimator_5.reset( new MonteCarlo::WeightAndEnergyMultipliedCellTrackLengthFluxEstimator(
                                                              4,
                                                              10.0,
                                                              cell_ids,
                                                              cell_volumes ) );
  estimator_5->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );

  estimator_6.reset( new MonteCarlo::WeightAndChargeMultipliedCellTrackLengthFluxEstimator(
                                                              5,
                                                              1.0,
                                                              cell_ids,
                                                              cell_volumes ) );
  estimator_6->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );

  estimator_7.reset( new MonteCarlo::WeightMultipliedCellPulseHeightEstimator(
                                                              6,
                                                              1.0,
                                                              cell_ids ) );

  estimator_8.reset( new MonteCarlo::WeightAndEnergyMultipliedCellPulseHeightEstimator(
                                                              7,
                                                              10.0,
                                                              cell_ids ) );

  estimator_9.reset( new MonteCarlo::WeightAndChargeMultipliedCellPulseHeightEstimator(
                                                              8,
                                                              1.0,
                                                              cell_ids ) );

  estimator_10.reset( new MonteCarlo::WeightMultipliedSurfaceFluxEstimator(
                                                             9,
                                                             1.0,
                                                             surface_ids,
                                                             surface_areas ) );
  estimator_10->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

  estimator_11.reset( new MonteCarlo::WeightAndEnergyMultipliedSurfaceFluxEstimator(
                                                             10,
                                                             10.0,
                                                             surface_ids,
                                                             surface_areas ) );
  estimator_11->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );

  estimator_12.reset( new MonteCarlo::WeightAndChargeMultipliedSurfaceFluxEstimator(
                                                             11,
                                                             1.0,
                                                             surface_ids,
                                                             surface_areas ) );
  estimator_12->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );

  estimator_13.reset( new MonteCarlo::WeightMultipliedSurfaceCurrentEstimator(
                                                               12,
                                                               1.0,
                                                               surface_ids ) );
  estimator_13->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

  estimator_14.reset( new MonteCarlo::WeightAndEnergyMultipliedSurfaceCurrentEstimator(
                                                               13,
                                                               10.0,
                                                               surface_ids ) );
  estimator_14->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );

  estimator_15.reset( new MonteCarlo::WeightAndChargeMultipliedSurfaceCurrentEstimator(
                                                               14,
                                                               1.0,
                                                               surface_ids ) );
  estimator_15->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );

  std::shared_ptr<const Utility::Mesh> hex_mesh(
                           new Utility::StructuredHexMesh( {0.0, 1.0, 2.0},
                                                           {0.0, 1.0, 2.0},
                                                           {0.0, 1.0, 2.0} ) );

  mesh_estimator_1.reset( new MonteCarlo::WeightMultipliedMeshTrackLengthFluxEstimator(
                                                                  15,
                                                                  1.0,
                                                                  hex_mesh ) );
  mesh_estimator_1->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

  mesh_estimator_2.reset( new MonteCarlo::WeightAndEnergyMultipliedMeshTrackLengthFluxEstimator(
                                                                  16,
                                                                  10.0,
                                                                  hex_mesh ) );
  mesh_estimator_2->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );

  mesh_estimator_3.reset( new MonteCarlo::WeightAndChargeMultipliedMeshTrackLengthFluxEstimator(
                                                                  17,
                                                                  1.0,
                                                                  hex_mesh ) );
  mesh_estimator_3->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );

  particle_tracker.reset( new MonteCarlo::ParticleTracker( 0, 100 ) );

  // Set up the global OpenMP session
  if( Utility::OpenMPProperties::isOpenMPUsed() )
    Utility::OpenMPProperties::setNumberOfThreads( threads );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstEstimatorHandler.cpp
//---------------------------------------------------------------------------//
