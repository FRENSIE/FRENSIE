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

std::shared_ptr<MonteCarlo::WeightMultipliedCellTrackLengthFluxEstimator>
estimator_3;

std::shared_ptr<MonteCarlo::WeightAndEnergyMultipliedCellTrackLengthFluxEstimator>
estimator_4;

std::shared_ptr<MonteCarlo::WeightMultipliedCellPulseHeightEstimator>
estimator_5;

std::shared_ptr<MonteCarlo::WeightAndEnergyMultipliedCellPulseHeightEstimator>
estimator_6;

std::shared_ptr<MonteCarlo::WeightMultipliedSurfaceFluxEstimator>
estimator_7;

std::shared_ptr<MonteCarlo::WeightAndEnergyMultipliedSurfaceFluxEstimator>
estimator_8;

std::shared_ptr<MonteCarlo::WeightMultipliedSurfaceCurrentEstimator>
estimator_9;

std::shared_ptr<MonteCarlo::WeightAndEnergyMultipliedSurfaceCurrentEstimator>
estimator_10;

std::shared_ptr<MonteCarlo::WeightMultipliedMeshTrackLengthFluxEstimator>
mesh_estimator;

std::shared_ptr<MonteCarlo::ParticleTracker> particle_tracker;

//---------------------------------------------------------------------------//
// Tests.
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
  
  FRENSIE_REQUIRE_NO_THROW( event_handler.addEstimator( mesh_estimator ) );
  FRENSIE_CHECK( event_handler.doesEstimatorExist( mesh_estimator->getId() ) );
  FRENSIE_CHECK_EQUAL( event_handler.getNumberOfEstimators(), 11 );

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
  }

  {
    std::shared_ptr<MonteCarlo::WeightMultipliedCellTrackLengthFluxEstimator>
      local_estimator_3( new MonteCarlo::WeightMultipliedCellTrackLengthFluxEstimator(
                                                      102, 1.0, {1}, {1.0} ) );

    local_estimator_3->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

    FRENSIE_CHECK_NO_THROW( event_handler.addEstimator( local_estimator_3 ) );

    std::shared_ptr<MonteCarlo::WeightMultipliedCellTrackLengthFluxEstimator>
      local_estimator_4( new MonteCarlo::WeightMultipliedCellTrackLengthFluxEstimator(
                                                      103, 1.0, {2}, {1.0} ) );

    local_estimator_4->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

    FRENSIE_CHECK_THROW( event_handler.addEstimator( local_estimator_4 ),
                         std::runtime_error );
  }

  {
    std::shared_ptr<MonteCarlo::WeightMultipliedCellPulseHeightEstimator>
      local_estimator_5( new MonteCarlo::WeightMultipliedCellPulseHeightEstimator(
                                                             104, 1.0, {1} ) );

    local_estimator_5->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

    FRENSIE_CHECK_NO_THROW( event_handler.addEstimator( local_estimator_5 ) );

    std::shared_ptr<MonteCarlo::WeightMultipliedCellPulseHeightEstimator>
      local_estimator_6( new MonteCarlo::WeightMultipliedCellPulseHeightEstimator(
                                                             105, 1.0, {2} ) );

    local_estimator_6->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

    FRENSIE_CHECK_THROW( event_handler.addEstimator( local_estimator_6 ),
                         std::runtime_error );
  }

  {
    std::shared_ptr<MonteCarlo::WeightMultipliedSurfaceFluxEstimator>
      local_estimator_7( new MonteCarlo::WeightMultipliedSurfaceFluxEstimator(
                                                      106, 1.0, {1}, {1.0} ) );

    local_estimator_7->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

    FRENSIE_CHECK_THROW( event_handler.addEstimator( local_estimator_7 ),
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
  
  event_handler.addEstimator( mesh_estimator );

  {
    const MonteCarlo::Estimator& estimator =
      event_handler.getEstimator( mesh_estimator->getId() );

    FRENSIE_CHECK( &estimator == mesh_estimator.get() );
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
  event_handler.addEstimator( mesh_estimator );
  event_handler.addParticleTracker( particle_tracker );
  
  FRENSIE_CHECK_EQUAL( event_handler.getParticleCollidingInCellEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleCollidingInCellEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 1 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleCollidingInCellEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleCollidingInCellEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 1 );

  FRENSIE_CHECK_EQUAL( event_handler.getParticleSubtrackEndingInCellEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleSubtrackEndingInCellEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 1 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleSubtrackEndingInCellEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleSubtrackEndingInCellEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 1 );

  FRENSIE_CHECK_EQUAL( event_handler.getParticleEnteringCellEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::PHOTON ), 2 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleEnteringCellEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 2 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleEnteringCellEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers( MonteCarlo::PHOTON ), 2 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleEnteringCellEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 2 );

  FRENSIE_CHECK_EQUAL( event_handler.getParticleLeavingCellEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::PHOTON ), 2 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleLeavingCellEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 2 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleLeavingCellEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers( MonteCarlo::PHOTON ), 2 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleLeavingCellEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 2 );
  
  FRENSIE_CHECK_EQUAL( event_handler.getParticleCrossingSurfaceEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::PHOTON ), 2 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleCrossingSurfaceEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 2 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleCrossingSurfaceEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers( MonteCarlo::PHOTON ), 2 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleCrossingSurfaceEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 2 );

  FRENSIE_CHECK_EQUAL( event_handler.getParticleSubtrackEndingGlobalEventDispatcher().getNumberOfObservers( MonteCarlo::PHOTON ), 2 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleSubtrackEndingGlobalEventDispatcher().getNumberOfObservers( MonteCarlo::ELECTRON ), 1 );
  
  FRENSIE_CHECK_EQUAL( event_handler.getParticleGoneGlobalEventDispatcher().getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
  FRENSIE_CHECK_EQUAL( event_handler.getParticleGoneGlobalEventDispatcher().getNumberOfObservers( MonteCarlo::ELECTRON ), 1 );
}

// //---------------------------------------------------------------------------//
// // Check if observers can be updated from a particle generation event
// TEUCHOS_UNIT_TEST( EventHandler, updateObserversFromParticleEnteringCellEvent )
// {
//   MonteCarlo::PhotonState particle( 0ull );
//   particle.setWeight( 1.0 );
//   particle.setEnergy( 1.0 );

//   TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

//   event_handler->updateObserversFromParticleEnteringCellEvent( particle, 1 );

//   TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( estimator_5->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( estimator_6->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

//   event_handler->resetObserverData();

//   TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );
// }

// //---------------------------------------------------------------------------//
// // Check if observers can be updated from a particle generation event
// TEUCHOS_UNIT_TEST( EventHandler, updateObserversFromParticleLeavingCellEvent )
// {
//   MonteCarlo::PhotonState particle( 0ull );
//   particle.setWeight( 1.0 );
//   particle.setEnergy( 1.0 );

//   TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

//   event_handler->updateObserversFromParticleLeavingCellEvent( particle, 1 );

//   TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( estimator_5->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( estimator_6->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

//   event_handler->resetObserverData();

//   TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );
// }

// //---------------------------------------------------------------------------//
// // Check if observers can be updated from a particle generation event
// TEUCHOS_UNIT_TEST( EventHandler,
//                    updateObserversFromParticleSubtrackEndingInCellEvent )
// {
//   MonteCarlo::PhotonState particle( 0ull );
//   particle.setWeight( 1.0 );
//   particle.setEnergy( 1.0 );

//   TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

//   event_handler->updateObserversFromParticleSubtrackEndingInCellEvent(
//                                                        particle, 1, 1.0, 0.0 );

//   TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( estimator_3->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( estimator_4->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

//   event_handler->resetObserverData();

//   TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );
// }

// //---------------------------------------------------------------------------//
// // Check if observers can be updated from a particle generation event
// TEUCHOS_UNIT_TEST( EventHandler,
//                    updateObserversFromParticleCollidingInCellEvent )
// {
//   MonteCarlo::PhotonState particle( 0ull );
//   particle.setWeight( 1.0 );
//   particle.setEnergy( 1.0 );
//   particle.setCell( 1 );

//   TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

//   event_handler->updateObserversFromParticleCollidingInCellEvent(
//                                                                particle, 1.0 );

//   TEST_ASSERT( estimator_1->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( estimator_2->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

//   event_handler->resetObserverData();

//   TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );
// }

// //---------------------------------------------------------------------------//
// // Check if observers can be updated from a surface intersection event
// TEUCHOS_UNIT_TEST( EventHandler,
//                    updateObserversFromParticleCrossingSurfaceEvent )
// {
//   MonteCarlo::PhotonState particle( 0ull );
//   particle.setWeight( 1.0 );
//   particle.setEnergy( 1.0 );
//   particle.setDirection( 1.0, 0.0, 0.0 );
//   particle.setCell( 1 );

//   std::vector<double> surface_normal( 3 );
//   surface_normal[0] = 1.0;
//   surface_normal[1] = 0.0;
//   surface_normal[2] = 0.0;

//   TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

//   event_handler->updateObserversFromParticleCrossingSurfaceEvent(
// 				     particle, 1, surface_normal.getRawPtr() );

//   TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( estimator_7->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( estimator_8->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( estimator_9->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( estimator_10->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

//   event_handler->resetObserverData();

//   TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );
// }

// //---------------------------------------------------------------------------//
// // Check if observers can be updated from a particle subtrack ending global
// // event
// TEUCHOS_UNIT_TEST( EventHandler,
//                    updateObserversFromParticleSubtrackEndingGlobalEvent )
// {
//   MonteCarlo::PhotonState particle( 0ull );
//   particle.setWeight( 1.0 );
//   particle.setEnergy( 1.0 );

//   double start_point[3] = { 0.25, 0.0, 0.75 };
//   double end_point[3] = { 0.75, 0.25, 1.0 };

//   TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

//   event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
//                                             particle, start_point, end_point );

//   TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( mesh_estimator->hasUncommittedHistoryContribution() );

//   event_handler->resetObserverData();

//   TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );
// }

// //---------------------------------------------------------------------------//
// // Check that estimator history contributions can be committed
// TEUCHOS_UNIT_TEST( EventHandler, commitObserverHistoryContributions )
// {
//   MonteCarlo::PhotonState particle( 0ull );
//   particle.setWeight( 1.0 );
//   particle.setEnergy( 1.0 );
//   particle.setDirection( 1.0, 0.0, 0.0 );
//   particle.setCell( 1 );

//   // Update the cell collision flux estimators
//   TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );

//   event_handler->updateObserversFromParticleCollidingInCellEvent(
// 							       particle, 1.0 );

//   TEST_ASSERT( estimator_1->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( estimator_2->hasUncommittedHistoryContribution() );

//   // Update the cell track length flux estimators
//   TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );

//   event_handler->updateObserversFromParticleSubtrackEndingInCellEvent(
//                                                        particle, 1, 1.0, 0.0 );

//   TEST_ASSERT( estimator_3->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( estimator_4->hasUncommittedHistoryContribution() );

//   // Update the cell pulse height estimators
//   TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );

//   event_handler->updateObserversFromParticleEnteringCellEvent( particle, 1 );

//   TEST_ASSERT( estimator_5->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( estimator_6->hasUncommittedHistoryContribution() );

//   // Update the surface flux and surface current estimators
//   TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );

//   std::vector<double> surface_normal( 3 );
//   surface_normal[0] = 1.0;
//   surface_normal[1] = 0.0;
//   surface_normal[2] = 0.0;

//   event_handler->updateObserversFromParticleCrossingSurfaceEvent(
// 				     particle, 1, surface_normal.getRawPtr() );

//   TEST_ASSERT( estimator_7->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( estimator_8->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( estimator_9->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( estimator_10->hasUncommittedHistoryContribution() );

//   // Update the mesh estimators
//   TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

//   double start_point_1[3] = { 0.25, 0.0, 0.75 };
//   double start_point_2[3] = { 0.0, 0.25, 0.75 };
//   double start_point_3[3] = { 0.75, 0.0, 0.25 };
//   double start_point_4[3] = { 0.0, 0.75, 0.25 };
//   double start_point_5[3] = { 0.75, 0.25, 0.0 };
//   double start_point_6[3] = { 0.25, 0.75, 0.0 };

//   double end_point_1[3] = { 0.75, 0.25, 1.0 };
//   double end_point_2[3] = { 0.25, 0.75, 1.0 };
//   double end_point_3[3] = { 1.0, 0.25, 0.75 };
//   double end_point_4[3] = { 0.25, 1.0, 0.75 };
//   double end_point_5[3] = { 1.0, 0.75, 0.25 };
//   double end_point_6[3] = { 0.75, 1.0, 0.25 };

//   event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
// 					particle, start_point_1, end_point_1 );

//   event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
// 					particle, start_point_2, end_point_2 );

//   event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
// 					particle, start_point_3, end_point_3 );

//   event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
// 					particle, start_point_4, end_point_4 );

//   event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
// 					particle, start_point_5, end_point_5 );

//   event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
// 					particle, start_point_6, end_point_6 );

//   TEST_ASSERT( mesh_estimator->hasUncommittedHistoryContribution() );

//   // Commit the contributions
//   event_handler->commitObserverHistoryContributions();

//   TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

//   // Export the estimator data
//   std::string estimator_file_name( "test_estimator_handler.h5" );

//   {
//     std::shared_ptr<Utility::HDF5FileHandler>
//         hdf5_file( new Utility::HDF5FileHandler );
//     hdf5_file->openHDF5FileAndOverwrite( estimator_file_name );

//     event_handler->exportObserverData( hdf5_file,
//                                        1,
//                                        1,
//                                        0.0,
//                                        1.0,
//                                        false );
//   }

//   // Open the HDF5 file
//   MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler(
//          estimator_file_name,
// 	 MonteCarlo::EstimatorHDF5FileHandler::READ_ONLY_ESTIMATOR_HDF5_FILE );

//   typedef MonteCarlo::StandardCellEstimator::cellIdType cellIdType;
//   typedef MonteCarlo::StandardSurfaceEstimator::surfaceIdType surfaceIdType;

//   // Check the bin data
//   std::vector<Utility::Pair<double,double> >
//     raw_bin_data_used( 1, Utility::Pair<double,double>( 1.0, 1.0 ) ),
//     raw_bin_data_unused( 1, Utility::Pair<double,double>( 0.0, 0.0 ) ),
//     raw_bin_data_copy;

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   0u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   0u, 2u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   1u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   1u, 2u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   2u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   2u, 2u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   3u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   3u, 2u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   4u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   4u, 2u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   5u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   5u, 2u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
// 						   6u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
// 						   6u, 2u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
// 						   7u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
// 						   7u, 2u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
// 						   8u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
// 						   8u, 2u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
// 						   9u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
// 						   9u, 2u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
// 					raw_bin_data_copy,
// 					1e-15 );

//   double track_length = 0.6123724356957940;
//   raw_bin_data_used[0]( track_length, track_length*track_length );

//   const moab::Range all_tet_elements = mesh_estimator->getAllTetElements();
//   moab::Range::const_iterator tet = all_tet_elements.begin();

//   hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
// 						10u, *tet, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
// 					raw_bin_data_copy,
// 					1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
// 						10u, *tet, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
// 					raw_bin_data_copy,
// 					1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
// 						10u, *tet, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
// 					raw_bin_data_copy,
// 					1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
// 						10u, *tet, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
// 					raw_bin_data_copy,
// 					1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
// 						10u, *tet, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
// 					raw_bin_data_copy,
// 					1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
// 						10u, *tet, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
// 					raw_bin_data_copy,
// 					1e-12 );

//   // Reset the estimator data
//   event_handler->resetObserverData();
// }

// //---------------------------------------------------------------------------//
// // Check that observer history contributions can be committed
// TEUCHOS_UNIT_TEST( EventHandler,
// 		   commitObserverHistoryContributions_thread_safe )
// {
//   unsigned threads =
//     Utility::OpenMPProperties::getRequestedNumberOfThreads();

//   // Enable thread support in the estimators
//   event_handler->enableThreadSupport( threads );

//   // Update the cell collision flux estimators
//   TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

//   #pragma omp parallel num_threads( threads )
//   {
//     MonteCarlo::PhotonState particle( 0ull );
//     particle.setWeight( 1.0 );
//     particle.setEnergy( 1.0 );
//     particle.setDirection( 1.0, 0.0, 0.0 );
//     particle.setCell( 1 );

//     event_handler->updateObserversFromParticleCollidingInCellEvent(
//                                                                particle, 1.0 );
//     particle.setCell( 2 );

//     event_handler->updateObserversFromParticleCollidingInCellEvent(
//                                                                particle, 1.0 );

//     event_handler->updateObserversFromParticleSubtrackEndingInCellEvent(
//                                                        particle, 1, 1.0, 0.0 );
//     event_handler->updateObserversFromParticleSubtrackEndingInCellEvent(
//                                                        particle, 2, 1.0, 0.0 );

//     event_handler->updateObserversFromParticleEnteringCellEvent( particle, 1 );
//     event_handler->updateObserversFromParticleEnteringCellEvent( particle, 2 );

//     std::vector<double> surface_normal( 3 );
//     surface_normal[0] = 1.0;
//     surface_normal[1] = 0.0;
//     surface_normal[2] = 0.0;

//     event_handler->updateObserversFromParticleCrossingSurfaceEvent(
// 				     particle, 1, surface_normal.getRawPtr() );
//     event_handler->updateObserversFromParticleCrossingSurfaceEvent(
// 				     particle, 2, surface_normal.getRawPtr() );

//     double start_point_1[3] = { 0.25, 0.0, 0.75 };
//     double start_point_2[3] = { 0.0, 0.25, 0.75 };
//     double start_point_3[3] = { 0.75, 0.0, 0.25 };
//     double start_point_4[3] = { 0.0, 0.75, 0.25 };
//     double start_point_5[3] = { 0.75, 0.25, 0.0 };
//     double start_point_6[3] = { 0.25, 0.75, 0.0 };

//     double end_point_1[3] = { 0.75, 0.25, 1.0 };
//     double end_point_2[3] = { 0.25, 0.75, 1.0 };
//     double end_point_3[3] = { 1.0, 0.25, 0.75 };
//     double end_point_4[3] = { 0.25, 1.0, 0.75 };
//     double end_point_5[3] = { 1.0, 0.75, 0.25 };
//     double end_point_6[3] = { 0.75, 1.0, 0.25 };

//     event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
//                                         particle, start_point_1, end_point_1 );

//     event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
//                                         particle, start_point_2, end_point_2 );

//     event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
//                                         particle, start_point_3, end_point_3 );

//     event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
//                                         particle, start_point_4, end_point_4 );

//     event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
//                                         particle, start_point_5, end_point_5 );

//     event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
//                                         particle, start_point_6, end_point_6 );

//     // Commit the contributions
//     event_handler->commitObserverHistoryContributions();
//   }

//   TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
//   TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

//   // Export the estimator data
//   std::string estimator_file_name( "test_estimator_handler2.h5" );
//   {
//     std::shared_ptr<Utility::HDF5FileHandler>
//       hdf5_file( new Utility::HDF5FileHandler );
//     hdf5_file->openHDF5FileAndOverwrite( estimator_file_name );

//     event_handler->exportObserverData( hdf5_file,
//                                        threads,
//                                        threads,
//                                        0.0,
//                                        1.0,
//                                        false );
//   }

//   // Open the HDF5 file
//   MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler(
//          estimator_file_name,
// 	 MonteCarlo::EstimatorHDF5FileHandler::READ_ONLY_ESTIMATOR_HDF5_FILE );

//   typedef MonteCarlo::StandardCellEstimator::cellIdType cellIdType;
//   typedef MonteCarlo::StandardSurfaceEstimator::surfaceIdType surfaceIdType;

//   // Check the bin data
//   std::vector<Utility::Pair<double,double> >
//     raw_bin_data( 1, Utility::Pair<double,double>( threads, threads ) ),
//     raw_bin_data_copy;

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   0u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   0u, 2u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   1u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   1u, 2u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   2u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   2u, 2u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   3u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   3u, 2u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   4u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   4u, 2u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   5u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
// 						   5u, 2u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
// 						   6u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
// 						   6u, 2u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
// 						   7u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
// 						   7u, 2u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
// 						   8u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
// 						   8u, 2u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
// 						   9u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
// 						   9u, 2u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-15 );

//   double track_length = 0.6123724356957940;
//   raw_bin_data[0]( threads*track_length, threads*track_length*track_length );

//   const moab::Range all_tet_elements = mesh_estimator->getAllTetElements();
//   moab::Range::const_iterator tet = all_tet_elements.begin();

//   hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
// 						10u, *tet, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
// 						10u, *tet, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
// 						10u, *tet, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
// 						10u, *tet, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
// 						10u, *tet, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
// 						10u, *tet, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
// 					raw_bin_data_copy,
// 					1e-12 );

//   // Reset the estimator data
//   event_handler->resetObserverData();
// }

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

  estimator_3.reset( new MonteCarlo::WeightMultipliedCellTrackLengthFluxEstimator(
                                                              2,
                                                              1.0,
                                                              cell_ids,
                                                              cell_volumes ) );
  estimator_3->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

  estimator_4.reset( new MonteCarlo::WeightAndEnergyMultipliedCellTrackLengthFluxEstimator(
                                                              3,
                                                              10.0,
                                                              cell_ids,
                                                              cell_volumes ) );
  estimator_4->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );

  estimator_5.reset( new MonteCarlo::WeightMultipliedCellPulseHeightEstimator(
                                                              4,
                                                              1.0,
                                                              cell_ids ) );
  estimator_5->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON, MonteCarlo::ELECTRON} ) );

  estimator_6.reset( new MonteCarlo::WeightAndEnergyMultipliedCellPulseHeightEstimator(
                                                              5,
                                                              10.0,
                                                              cell_ids ) );
  estimator_6->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON, MonteCarlo::ELECTRON} ) );

  estimator_7.reset( new MonteCarlo::WeightMultipliedSurfaceFluxEstimator(
                                                             6,
                                                             1.0,
                                                             surface_ids,
                                                             surface_areas ) );
  estimator_7->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

  estimator_8.reset( new MonteCarlo::WeightAndEnergyMultipliedSurfaceFluxEstimator(
                                                             7,
                                                             10.0,
                                                             surface_ids,
                                                             surface_areas ) );
  estimator_8->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );

  estimator_9.reset( new MonteCarlo::WeightMultipliedSurfaceCurrentEstimator(
                                                               8,
                                                               1.0,
                                                               surface_ids ) );
  estimator_9->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

  estimator_10.reset( new MonteCarlo::WeightAndEnergyMultipliedSurfaceCurrentEstimator(
                                                               9,
                                                               10.0,
                                                               surface_ids ) );
  estimator_10->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );

  std::shared_ptr<const Utility::Mesh> hex_mesh(
                           new Utility::StructuredHexMesh( {0.0, 1.0, 2.0},
                                                           {0.0, 1.0, 2.0},
                                                           {0.0, 1.0, 2.0} ) );
  
  mesh_estimator.reset( new MonteCarlo::WeightMultipliedMeshTrackLengthFluxEstimator(
                                                                  10,
                                                                  1.0,
                                                                  hex_mesh ) );
  mesh_estimator->setParticleTypes( std::set<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

  particle_tracker.reset( new MonteCarlo::ParticleTracker( 0, 100 ) );

  // Set up the global OpenMP session
  if( Utility::OpenMPProperties::isOpenMPUsed() )
    Utility::OpenMPProperties::setNumberOfThreads( threads );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstEstimatorHandler.cpp
//---------------------------------------------------------------------------//
