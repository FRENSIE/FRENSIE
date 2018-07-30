//---------------------------------------------------------------------------//
//!
//! \file   tstParticleSubtrackEndingGlobalEventDispatcher.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Particle subtrack ending in cell event dispatcher unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_MeshTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_ParticleSubtrackEndingGlobalEventDispatcher.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Geometry_Model.hpp"
#include "Utility_TetMesh.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<MonteCarlo::WeightMultipliedMeshTrackLengthFluxEstimator>
estimator;

std::shared_ptr<MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher>
dispatcher( new MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an observer can be attached to the dispatcher
FRENSIE_UNIT_TEST( ParticleSubtrackEndingGlobalEventDispatcher,
		   attachObserver )
{
  std::shared_ptr<MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher>
    dispatcher( new MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher );

  dispatcher->attachObserver( estimator );

  FRENSIE_CHECK( estimator.use_count() > 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::ELECTRON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::POSITRON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::NEUTRON ), 1 );

  dispatcher->detachAllObservers();

  FRENSIE_CHECK_EQUAL( estimator.use_count(), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::PHOTON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::ELECTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::POSITRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::NEUTRON ), 0 );

  dispatcher->attachObserver( {MonteCarlo::PHOTON}, estimator );

  FRENSIE_CHECK_EQUAL( estimator.use_count(), 2 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::ELECTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::POSITRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::NEUTRON ), 0 );

  dispatcher->detachObserver( estimator );

  FRENSIE_CHECK_EQUAL( estimator.use_count(), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::PHOTON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::ELECTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::POSITRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::NEUTRON ), 0 );
}

// //---------------------------------------------------------------------------//
// // Check that the dispatcher can update from the global ending event
// FRENSIE_UNIT_TEST( ParticleSubtrackEndingGlobalEventDispatcher,
//                    dispatchParticleSubtrackEndingGlobalEvent )
// {
//   std::shared_ptr<MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher>
//     dispatcher( new MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher );
  
//   MonteCarlo::PhotonState particle( 0ull );
//   particle.setWeight( 1.0 );
//   particle.setEnergy( 1.0 );

//   double start_point[3] = { 0.0, 1.0, 0.0 };
//   double end_point[3] = { 0.25, 0.75, 1.0 };

//   FRENSIE_CHECK( !estimator->hasUncommittedHistoryContribution() );

//   dispatcher->dispatchParticleSubtrackEndingGlobalEvent(
//                                             particle, start_point, end_point );

//   FRENSIE_CHECK( estimator->hasUncommittedHistoryContribution() );

//   estimator->commitHistoryContribution();

//   FRENSIE_CHECK( !estimator->hasUncommittedHistoryContribution() );
// }

// //---------------------------------------------------------------------------//
// // Check that an observer can be detached from the dispatcher
// FRENSIE_UNIT_TEST( ParticleSubtrackEndingGlobalEventDispatcher,
// 		   detachObserver )
// {
//   std::shared_ptr<MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher>
//     dispatcher( new MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher );
  
//   dispatcher->detachObserver( estimator->getId() );

//   FRENSIE_CHECK_EQUAL( estimator.use_count(), 1 );
//   FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers(), 0 );
// }

// //---------------------------------------------------------------------------//
// // Check that all observers can be detached from the dispatcher
// FRENSIE_UNIT_TEST( ParticleSubtrackEndingGlobalEventDispatcher,
// 		   detachAllObservers )
// {
//   std::shared_ptr<MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher>
//     dispatcher( new MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher );
  
//   std::shared_ptr<MonteCarlo::ParticleSubtrackEndingGlobalEventObserver> observer =
//     std::dynamic_pointer_cast<MonteCarlo::ParticleSubtrackEndingGlobalEventObserver>( estimator );

//   dispatcher->attachObserver(  estimator->getId(), observer );

//   observer.reset();

//   FRENSIE_CHECK_EQUAL( estimator.use_count(), 2 );
//   FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers(), 1 );

//   dispatcher->detachAllObservers();

//   FRENSIE_CHECK_EQUAL( estimator.use_count(), 1 );
//   FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers(), 0 );
// }

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_input_mesh_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_input_mesh_file_name",
                                        test_input_mesh_file_name, "",
                                        "Test input mesh file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  std::shared_ptr<const Utility::Mesh> mesh(
                           new Utility::TetMesh( test_input_mesh_file_name ) );

  estimator.reset( new MonteCarlo::WeightMultipliedMeshTrackLengthFluxEstimator(
                                                                      0,
                                                                      1.0,
                                                                      mesh ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstParticleSubtrackEndingGlobalEventDispatcher.cpp
//---------------------------------------------------------------------------//
