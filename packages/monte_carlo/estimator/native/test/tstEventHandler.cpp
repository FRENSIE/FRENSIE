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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_EventHandler.hpp"
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "MonteCarlo_CellCollisionFluxEstimator.hpp"
#include "MonteCarlo_CellTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_CellPulseHeightEstimator.hpp"
#include "MonteCarlo_SurfaceCurrentEstimator.hpp"
#include "MonteCarlo_SurfaceFluxEstimator.hpp"
#include "MonteCarlo_TetMeshTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightMultiplier> >
estimator_1;

std::shared_ptr<MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_2;

std::shared_ptr<MonteCarlo::CellTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> >
estimator_3;

std::shared_ptr<MonteCarlo::CellTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_4;

std::shared_ptr<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier> >
estimator_5;

std::shared_ptr<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_6;

std::shared_ptr<MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightMultiplier> >
estimator_7;

std::shared_ptr<MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_8;

std::shared_ptr<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightMultiplier> >
estimator_9;

std::shared_ptr<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_10;

std::shared_ptr<MonteCarlo::TetMeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> >
mesh_estimator;

std::shared_ptr<MonteCarlo::EventHandler> event_handler;

Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> cell_ids;
Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle> surface_ids;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize a cell estimator
template<typename CellEstimator>
void initializeCellEstimator( 
    const unsigned estimator_id,
    const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& ids,
    std::shared_ptr<CellEstimator>& estimator )
{  
  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  Teuchos::Array<double> cell_volumes( ids.size(), 1.0 );
  
  estimator.reset( new CellEstimator( estimator_id,
				      estimator_multiplier,
				      ids,
				      cell_volumes ) );

  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
  particle_types[0] = MonteCarlo::PHOTON;
  
  estimator->setParticleTypes( particle_types );
}

// Initialize a cell pulse height estimator
template<typename CellPulseHeightEstimator>
void initializeCellPulseHeightEstimator(
    const unsigned estimator_id,
    const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& ids,
    std::shared_ptr<CellPulseHeightEstimator>& estimator )
{  
  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  estimator.reset( new CellPulseHeightEstimator( estimator_id,
						 estimator_multiplier,
						 ids ) );

  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
  particle_types[0] = MonteCarlo::PHOTON;
  
  estimator->setParticleTypes( particle_types );
}

// Initialize a surface flux estimator
template<typename SurfaceEstimator>
void initializeSurfaceFluxEstimator( 
	   const unsigned estimator_id,
           const Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
	   ids,
	   std::shared_ptr<SurfaceEstimator>& estimator )
{
  Teuchos::Array<double> surface_areas( ids.size(), 1.0 );

  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  estimator.reset( new SurfaceEstimator( estimator_id,
					 estimator_multiplier,
					 ids,
					 surface_areas ) );

  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
  particle_types[0] = MonteCarlo::PHOTON;

  estimator->setParticleTypes( particle_types );
}

// Initialize a surface current estimator
template<typename SurfaceEstimator>
void initializeSurfaceCurrentEstimator( 
	   const unsigned estimator_id,
           const Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
	   ids,
	   std::shared_ptr<SurfaceEstimator>& estimator )
{
  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  estimator.reset( new SurfaceEstimator( estimator_id,
					 estimator_multiplier,
					 ids ) );

  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
  particle_types[0] = MonteCarlo::PHOTON;

  estimator->setParticleTypes( particle_types );
}

// Initialize the estimator
template<typename MeshEstimator>
void initializeMeshEstimator( const unsigned estimator_id,
			      const std::string& mesh_file_name,
			      std::shared_ptr<MeshEstimator>& estimator )
{
  estimator.reset( new MeshEstimator( estimator_id,
				      1.0,
				      mesh_file_name,
				      "unit_cube_output.vtk" ) );
  
  // Set the particle types
  Teuchos::Array<MonteCarlo::ParticleType> particle_types ( 1 );
  particle_types[0] = MonteCarlo::PHOTON;
    
  estimator->setParticleTypes( particle_types );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that observers can be added to the event handler
TEUCHOS_UNIT_TEST( EventHandler, add_observers )
{
  event_handler->addEntityEventObserver( estimator_1, cell_ids );
  event_handler->addEntityEventObserver( estimator_2, cell_ids );
  event_handler->addEntityEventObserver( estimator_3, cell_ids );
  event_handler->addEntityEventObserver( estimator_4, cell_ids );
  event_handler->addEntityEventObserver( estimator_5, cell_ids );
  event_handler->addEntityEventObserver( estimator_6, cell_ids );
  
  event_handler->addEntityEventObserver( estimator_7, surface_ids );
  event_handler->addEntityEventObserver( estimator_8, surface_ids );
  event_handler->addEntityEventObserver( estimator_9, surface_ids );
  event_handler->addEntityEventObserver( estimator_10, surface_ids );

  event_handler->addGlobalEventObserver( mesh_estimator );

  TEST_EQUALITY_CONST( event_handler->getParticleCollidingInCellEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( event_handler->getParticleSubtrackEndingInCellEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( event_handler->getParticleEnteringCellEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( event_handler->getParticleLeavingCellEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( event_handler->getParticleCrossingSurfaceEventDispatcher().getLocalDispatcher( 1 ).getNumberOfObservers(), 4 );

  TEST_EQUALITY_CONST( event_handler->getParticleCollidingInCellEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( event_handler->getParticleSubtrackEndingInCellEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( event_handler->getParticleEnteringCellEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( event_handler->getParticleLeavingCellEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( event_handler->getParticleCrossingSurfaceEventDispatcher().getLocalDispatcher( 2 ).getNumberOfObservers(), 4 );

  TEST_EQUALITY_CONST( event_handler->getParticleSubtrackEndingGlobalEventDispatcher().getNumberOfObservers(), 1 );

  TEST_EQUALITY_CONST( event_handler->getNumberOfObservers(), 11 );
} 

//---------------------------------------------------------------------------//
// Check if observers exist in the event handler
TEUCHOS_UNIT_TEST( EventHandler, doesObserverExist )
{
  TEST_ASSERT( event_handler->doesObserverExist( 0u ) );
  TEST_ASSERT( event_handler->doesObserverExist( 1u ) );
  TEST_ASSERT( event_handler->doesObserverExist( 2u ) );
  TEST_ASSERT( event_handler->doesObserverExist( 3u ) );
  TEST_ASSERT( event_handler->doesObserverExist( 4u ) );
  TEST_ASSERT( event_handler->doesObserverExist( 5u ) );
  TEST_ASSERT( event_handler->doesObserverExist( 6u ) );
  TEST_ASSERT( event_handler->doesObserverExist( 7u ) );
  TEST_ASSERT( event_handler->doesObserverExist( 8u ) );
  TEST_ASSERT( event_handler->doesObserverExist( 9u ) );
  TEST_ASSERT( event_handler->doesObserverExist( 10u ) );
  TEST_ASSERT( !event_handler->doesObserverExist( 11u ) );
}

//---------------------------------------------------------------------------//
// Check if observers can be updated from a particle generation event
TEUCHOS_UNIT_TEST( EventHandler, updateObserversFromParticleEnteringCellEvent )
{
  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

  event_handler->updateObserversFromParticleEnteringCellEvent( particle, 1 );

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

  event_handler->resetObserverData();

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );
}

//---------------------------------------------------------------------------//
// Check if observers can be updated from a particle generation event
TEUCHOS_UNIT_TEST( EventHandler, updateObserversFromParticleLeavingCellEvent )
{
  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

  event_handler->updateObserversFromParticleLeavingCellEvent( particle, 1 );

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

  event_handler->resetObserverData();

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );
}

//---------------------------------------------------------------------------//
// Check if observers can be updated from a particle generation event
TEUCHOS_UNIT_TEST( EventHandler, 
                   updateObserversFromParticleSubtrackEndingInCellEvent )
{
  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

  event_handler->updateObserversFromParticleSubtrackEndingInCellEvent( 
                                                       particle, 1, 1.0, 0.0 );

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

  event_handler->resetObserverData();

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );
}

//---------------------------------------------------------------------------//
// Check if observers can be updated from a particle generation event
TEUCHOS_UNIT_TEST( EventHandler, 
                   updateObserversFromParticleCollidingInCellEvent )
{
  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );
  particle.setCell( 1 );

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

  event_handler->updateObserversFromParticleCollidingInCellEvent( 
                                                               particle, 1.0 );

  TEST_ASSERT( estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

  event_handler->resetObserverData();

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );
}

//---------------------------------------------------------------------------//
// Check if observers can be updated from a surface intersection event
TEUCHOS_UNIT_TEST( EventHandler,
                   updateObserversFromParticleCrossingSurfaceEvent )
{
  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );
  particle.setDirection( 1.0, 0.0, 0.0 );
  particle.setCell( 1 );

  Teuchos::Array<double> surface_normal( 3 );
  surface_normal[0] = 1.0;
  surface_normal[1] = 0.0;
  surface_normal[2] = 0.0;
  
  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

  event_handler->updateObserversFromParticleCrossingSurfaceEvent( 
				     particle, 1, surface_normal.getRawPtr() );

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_10->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

  event_handler->resetObserverData();

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );
}

//---------------------------------------------------------------------------//
// Check if observers can be updated from a particle subtrack ending global 
// event
TEUCHOS_UNIT_TEST( EventHandler, 
                   updateObserversFromParticleSubtrackEndingGlobalEvent )
{
  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  double start_point[3] = { 0.25, 0.0, 0.75 };
  double end_point[3] = { 0.75, 0.25, 1.0 };

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

  event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent( 
                                            particle, start_point, end_point );

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
  TEST_ASSERT( mesh_estimator->hasUncommittedHistoryContribution() );

  event_handler->resetObserverData();

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );
}

//---------------------------------------------------------------------------//
// Check that estimator history contributions can be committed
TEUCHOS_UNIT_TEST( EventHandler, commitObserverHistoryContributions )
{
  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );
  particle.setDirection( 1.0, 0.0, 0.0 );
  particle.setCell( 1 );

  // Update the cell collision flux estimators
  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );

  event_handler->updateObserversFromParticleCollidingInCellEvent(
							       particle, 1.0 );
  
  TEST_ASSERT( estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2->hasUncommittedHistoryContribution() );
  
  // Update the cell track length flux estimators
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() ); 

  event_handler->updateObserversFromParticleSubtrackEndingInCellEvent(
                                                       particle, 1, 1.0, 0.0 );

  TEST_ASSERT( estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_4->hasUncommittedHistoryContribution() ); 

  // Update the cell pulse height estimators
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );

  event_handler->updateObserversFromParticleEnteringCellEvent( particle, 1 );
  
  TEST_ASSERT( estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_6->hasUncommittedHistoryContribution() );

  // Update the surface flux and surface current estimators
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );

  Teuchos::Array<double> surface_normal( 3 );
  surface_normal[0] = 1.0;
  surface_normal[1] = 0.0;
  surface_normal[2] = 0.0;

  event_handler->updateObserversFromParticleCrossingSurfaceEvent( 
				     particle, 1, surface_normal.getRawPtr() );

  TEST_ASSERT( estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_10->hasUncommittedHistoryContribution() );

  // Update the mesh estimators
  TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

  double start_point_1[3] = { 0.25, 0.0, 0.75 };
  double start_point_2[3] = { 0.0, 0.25, 0.75 };
  double start_point_3[3] = { 0.75, 0.0, 0.25 };
  double start_point_4[3] = { 0.0, 0.75, 0.25 };
  double start_point_5[3] = { 0.75, 0.25, 0.0 };
  double start_point_6[3] = { 0.25, 0.75, 0.0 };
  
  double end_point_1[3] = { 0.75, 0.25, 1.0 };
  double end_point_2[3] = { 0.25, 0.75, 1.0 };
  double end_point_3[3] = { 1.0, 0.25, 0.75 };
  double end_point_4[3] = { 0.25, 1.0, 0.75 };
  double end_point_5[3] = { 1.0, 0.75, 0.25 };
  double end_point_6[3] = { 0.75, 1.0, 0.25 };

  event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
					particle, start_point_1, end_point_1 );
  
  event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
					particle, start_point_2, end_point_2 );

  event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
					particle, start_point_3, end_point_3 );

  event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
					particle, start_point_4, end_point_4 );

  event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
					particle, start_point_5, end_point_5 );
  
  event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
					particle, start_point_6, end_point_6 );

  TEST_ASSERT( mesh_estimator->hasUncommittedHistoryContribution() );

  // Commit the contributions
  event_handler->commitObserverHistoryContributions();

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

  // Export the estimator data
  std::string estimator_file_name( "test_estimator_handler.h5" );
  
  {
    std::shared_ptr<Utility::HDF5FileHandler>
        hdf5_file( new Utility::HDF5FileHandler );
    hdf5_file->openHDF5FileAndOverwrite( estimator_file_name );
      
    event_handler->exportObserverData( hdf5_file,
                                       1,
                                       1,
                                       0.0,
                                       1.0,
                                       false );
  }

  // Open the HDF5 file
  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler(
         estimator_file_name,
	 MonteCarlo::EstimatorHDF5FileHandler::READ_ONLY_ESTIMATOR_HDF5_FILE );

  typedef MonteCarlo::StandardCellEstimator::cellIdType cellIdType;
  typedef MonteCarlo::StandardSurfaceEstimator::surfaceIdType surfaceIdType;

  // Check the bin data
  Teuchos::Array<Utility::Pair<double,double> >
    raw_bin_data_used( 1, Utility::Pair<double,double>( 1.0, 1.0 ) ),
    raw_bin_data_unused( 1, Utility::Pair<double,double>( 0.0, 0.0 ) ),
    raw_bin_data_copy;

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   0u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   0u, 2u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   1u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   1u, 2u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   2u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   2u, 2u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   3u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   3u, 2u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   4u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   4u, 2u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   5u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   5u, 2u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   6u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   6u, 2u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   7u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   7u, 2u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   8u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   8u, 2u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   9u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   9u, 2u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
					raw_bin_data_copy,
					1e-15 );

  double track_length = 0.6123724356957940;
  raw_bin_data_used[0]( track_length, track_length*track_length );

  const moab::Range all_tet_elements = mesh_estimator->getAllTetElements();
  moab::Range::const_iterator tet = all_tet_elements.begin();
  
  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-12 );

  ++tet;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-12 );

  ++tet;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-12 );

  ++tet;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-12 );

  ++tet;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-12 );

  ++tet;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-12 );  

  // Reset the estimator data
  event_handler->resetObserverData();
}

//---------------------------------------------------------------------------//
// Check that observer history contributions can be committed
TEUCHOS_UNIT_TEST( EventHandler, 
		   commitObserverHistoryContributions_thread_safe )
{
  unsigned threads = 
    Utility::GlobalOpenMPSession::getRequestedNumberOfThreads();
  
  // Enable thread support in the estimators
  event_handler->enableThreadSupport( threads );

  // Update the cell collision flux estimators
  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

  #pragma omp parallel num_threads( threads )
  {
    MonteCarlo::PhotonState particle( 0ull );
    particle.setWeight( 1.0 );
    particle.setEnergy( 1.0 );
    particle.setDirection( 1.0, 0.0, 0.0 );
    particle.setCell( 1 );
    
    event_handler->updateObserversFromParticleCollidingInCellEvent(
                                                               particle, 1.0 );
    particle.setCell( 2 );
    
    event_handler->updateObserversFromParticleCollidingInCellEvent(
                                                               particle, 1.0 );
    
    event_handler->updateObserversFromParticleSubtrackEndingInCellEvent(
                                                       particle, 1, 1.0, 0.0 );
    event_handler->updateObserversFromParticleSubtrackEndingInCellEvent(
                                                       particle, 2, 1.0, 0.0 );
    
    event_handler->updateObserversFromParticleEnteringCellEvent( particle, 1 );
    event_handler->updateObserversFromParticleEnteringCellEvent( particle, 2 );

    Teuchos::Array<double> surface_normal( 3 );
    surface_normal[0] = 1.0;
    surface_normal[1] = 0.0;
    surface_normal[2] = 0.0;
    
    event_handler->updateObserversFromParticleCrossingSurfaceEvent( 
				     particle, 1, surface_normal.getRawPtr() );
    event_handler->updateObserversFromParticleCrossingSurfaceEvent( 
				     particle, 2, surface_normal.getRawPtr() );
    
    double start_point_1[3] = { 0.25, 0.0, 0.75 };
    double start_point_2[3] = { 0.0, 0.25, 0.75 };
    double start_point_3[3] = { 0.75, 0.0, 0.25 };
    double start_point_4[3] = { 0.0, 0.75, 0.25 };
    double start_point_5[3] = { 0.75, 0.25, 0.0 };
    double start_point_6[3] = { 0.25, 0.75, 0.0 };
    
    double end_point_1[3] = { 0.75, 0.25, 1.0 };
    double end_point_2[3] = { 0.25, 0.75, 1.0 };
    double end_point_3[3] = { 1.0, 0.25, 0.75 };
    double end_point_4[3] = { 0.25, 1.0, 0.75 };
    double end_point_5[3] = { 1.0, 0.75, 0.25 };
    double end_point_6[3] = { 0.75, 1.0, 0.25 };

    event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
                                        particle, start_point_1, end_point_1 );

    event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
                                        particle, start_point_2, end_point_2 );
    
    event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
                                        particle, start_point_3, end_point_3 );

    event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
                                        particle, start_point_4, end_point_4 );

    event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
                                        particle, start_point_5, end_point_5 );
    
    event_handler->updateObserversFromParticleSubtrackEndingGlobalEvent(
                                        particle, start_point_6, end_point_6 );
    
    // Commit the contributions
    event_handler->commitObserverHistoryContributions();
  }

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

  // Export the estimator data
  std::string estimator_file_name( "test_estimator_handler2.h5" );
  {
    std::shared_ptr<Utility::HDF5FileHandler>
      hdf5_file( new Utility::HDF5FileHandler );
    hdf5_file->openHDF5FileAndOverwrite( estimator_file_name );
    
    event_handler->exportObserverData( hdf5_file,
                                       threads,
                                       threads,
                                       0.0,
                                       1.0,
                                       false );
  }

  // Open the HDF5 file
  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler(
         estimator_file_name,
	 MonteCarlo::EstimatorHDF5FileHandler::READ_ONLY_ESTIMATOR_HDF5_FILE );

  typedef MonteCarlo::StandardCellEstimator::cellIdType cellIdType;
  typedef MonteCarlo::StandardSurfaceEstimator::surfaceIdType surfaceIdType;

  // Check the bin data
  Teuchos::Array<Utility::Pair<double,double> >
    raw_bin_data( 1, Utility::Pair<double,double>( threads, threads ) ),
    raw_bin_data_copy;

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   0u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   0u, 2u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   1u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   1u, 2u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   2u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   2u, 2u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   3u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   3u, 2u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   4u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   4u, 2u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   5u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   5u, 2u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   6u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   6u, 2u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   7u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   7u, 2u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   8u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   8u, 2u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   9u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   9u, 2u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  double track_length = 0.6123724356957940;
  raw_bin_data[0]( threads*track_length, threads*track_length*track_length );

  const moab::Range all_tet_elements = mesh_estimator->getAllTetElements();
  moab::Range::const_iterator tet = all_tet_elements.begin();
  
  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-12 );

  ++tet;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-12 );

  ++tet;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-12 );

  ++tet;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-12 );

  ++tet;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-12 );

  ++tet;

  hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-12 );  

  // Reset the estimator data
  event_handler->resetObserverData();
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
  
  std::string test_input_mesh_file_name;

  int threads = 1;

  clp.setOption( "test_input_mesh_file_name",
		 &test_input_mesh_file_name,
		 "Test input mesh file name" );

  clp.setOption( "threads",
		 &threads,
		 "Number of threads to use" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Set up the global OpenMP session
  if( Utility::GlobalOpenMPSession::isOpenMPUsed() )
    Utility::GlobalOpenMPSession::setNumberOfThreads( threads );
  
  // Initialize estimators
  cell_ids.resize( 2 );
  cell_ids[0] = 1;
  cell_ids[1] = 2;
  
  initializeCellEstimator( 0u, cell_ids, estimator_1 );
  initializeCellEstimator( 1u, cell_ids, estimator_2 );
  initializeCellEstimator( 2u, cell_ids, estimator_3 );
  initializeCellEstimator( 3u, cell_ids, estimator_4 );
  initializeCellPulseHeightEstimator( 4u, cell_ids, estimator_5 );
  initializeCellPulseHeightEstimator( 5u, cell_ids, estimator_6 );

  surface_ids.resize( 2 );
  surface_ids[0] = 1;
  surface_ids[1] = 2;
  
  initializeSurfaceFluxEstimator( 6u, surface_ids, estimator_7 );
  initializeSurfaceFluxEstimator( 7u, surface_ids, estimator_8 );
  initializeSurfaceCurrentEstimator( 8u, surface_ids, estimator_9 );
  initializeSurfaceCurrentEstimator( 9u, surface_ids, estimator_10 );

  initializeMeshEstimator( 10u, test_input_mesh_file_name, mesh_estimator );

  // Initialize the event handler
  event_handler.reset( new MonteCarlo::EventHandler );

  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstEstimatorHandler.cpp
//---------------------------------------------------------------------------//
