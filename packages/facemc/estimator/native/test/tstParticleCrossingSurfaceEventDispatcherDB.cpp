//---------------------------------------------------------------------------//
//!
//! \file   tstParticleCrossingSurfaceEventDispatcherDB.cpp
//! \author Alex Robinson
//! \brief  Particle crossing surface event dispatcher database unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_SurfaceCurrentEstimator.hpp"
#include "Facemc_SurfaceFluxEstimator.hpp"
#include "Facemc_ParticleCrossingSurfaceEventDispatcherDB.hpp"
#include "Facemc_PhotonState.hpp"
#include "Geometry_ModuleTraits.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
Teuchos::RCP<Facemc::SurfaceCurrentEstimator<Facemc::WeightMultiplier> >
estimator_1;

Teuchos::RCP<Facemc::SurfaceFluxEstimator<Facemc::WeightAndEnergyMultiplier> >
estimator_2;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the estimator
template<typename SurfaceEstimator>
void initializeSurfaceFluxEstimator( const unsigned estimator_id,
				 Teuchos::RCP<SurfaceEstimator>& estimator )
{
  // Set the entity ids
  Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle> 
    surface_ids( 2 );
  surface_ids[0] = 0;
  surface_ids[1] = 1;

  Teuchos::Array<double> surface_areas( 2 );
  surface_areas[0] = 1.0;
  surface_areas[1] = 2.0;

  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  estimator.reset( new SurfaceEstimator( estimator_id,
					 estimator_multiplier,
					 surface_ids,
					 surface_areas ) );

  Teuchos::Array<Facemc::ParticleType> particle_types( 1 );
  particle_types[0] = Facemc::PHOTON;

  estimator->setParticleTypes( particle_types );
}

// Initialize the estimator
template<typename SurfaceEstimator>
void initializeSurfaceCurrentEstimator( const unsigned estimator_id,
				 Teuchos::RCP<SurfaceEstimator>& estimator )
{
  // Set the entity ids
  Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle> 
    surface_ids( 2 );
  surface_ids[0] = 0;
  surface_ids[1] = 1;

  Teuchos::Array<double> surface_areas( 2 );
  surface_areas[0] = 1.0;
  surface_areas[1] = 2.0;

  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  estimator.reset( new SurfaceEstimator( estimator_id,
					 estimator_multiplier,
					 surface_ids ) );

  Teuchos::Array<Facemc::ParticleType> particle_types( 1 );
  particle_types[0] = Facemc::PHOTON;

  estimator->setParticleTypes( particle_types );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the correct event dispatchers can be returned
TEUCHOS_UNIT_TEST( ParticleCrossingSurfaceEventDispatcherDB, getDispatcher )
{
  Teuchos::RCP<Facemc::ParticleCrossingSurfaceEventDispatcher> dispatcher =
    Facemc::ParticleCrossingSurfaceEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getId(), 0 );

  dispatcher = 
    Facemc::ParticleCrossingSurfaceEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getId(), 1 );
}

//---------------------------------------------------------------------------//
// Check that observers can be attached to dispatchers
TEUCHOS_UNIT_TEST( ParticleCrossingSurfaceEventDispatcherDB, attachObserver )
{
  initializeSurfaceCurrentEstimator( 0u, estimator_1 );
  initializeSurfaceFluxEstimator( 1u, estimator_2 );

  Teuchos::RCP<Facemc::ParticleCrossingSurfaceEventObserver> observer_1 =
    Teuchos::rcp_dynamic_cast<Facemc::ParticleCrossingSurfaceEventObserver>( 
								 estimator_1 );
  Teuchos::RCP<Facemc::ParticleCrossingSurfaceEventObserver> observer_2 =
    Teuchos::rcp_dynamic_cast<Facemc::ParticleCrossingSurfaceEventObserver>(
								 estimator_2 );
  
  Facemc::ParticleCrossingSurfaceEventDispatcherDB::attachObserver(
							  0,
							  estimator_1->getId(),
							  observer_1 );
  Facemc::ParticleCrossingSurfaceEventDispatcherDB::attachObserver(
							  1,
							  estimator_1->getId(),
							  observer_1 );
  Facemc::ParticleCrossingSurfaceEventDispatcherDB::attachObserver(
							  0,
							  estimator_2->getId(),
							  observer_2 );
  Facemc::ParticleCrossingSurfaceEventDispatcherDB::attachObserver(
							  1,
							  estimator_2->getId(),
							  observer_2 );
    
  observer_1.reset();
  observer_2.reset();
  
  TEST_EQUALITY_CONST( estimator_1.total_count(), 3 );
  TEST_EQUALITY_CONST( estimator_2.total_count(), 3 );

  Teuchos::RCP<Facemc::ParticleCrossingSurfaceEventDispatcher> dispatcher =
    Facemc::ParticleCrossingSurfaceEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 2 );

  dispatcher =
    Facemc::ParticleCrossingSurfaceEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 2 );
}

//---------------------------------------------------------------------------//
// Check that a collision event can be dispatched
TEUCHOS_UNIT_TEST( ParticleCrossingSurfaceEventDispatcherDB,
		   dispatchParticleCrossingSurfaceEvent )
{
  Facemc::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );

  Facemc::ParticleCrossingSurfaceEventDispatcherDB::dispatchParticleCrossingSurfaceEvent(
								      particle,
								      0, 
								      1.0 );

  TEST_ASSERT( estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2->hasUncommittedHistoryContribution() );
  
  estimator_1->commitHistoryContribution();
  estimator_2->commitHistoryContribution();

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  

  Facemc::ParticleCrossingSurfaceEventDispatcherDB::dispatchParticleCrossingSurfaceEvent(
								      particle,
								      1, 
								      1.0 );

  TEST_ASSERT( estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2->hasUncommittedHistoryContribution() );
}

//---------------------------------------------------------------------------//
// Check that an observer can be detached from the dispatcher
TEUCHOS_UNIT_TEST( ParticleCrossingSurfaceEventDispatcherDB, 
		   detachObserver_dispatcher )
{
  Facemc::ParticleCrossingSurfaceEventDispatcherDB::detachObserver( 0, 0 );

  Teuchos::RCP<Facemc::ParticleCrossingSurfaceEventDispatcher> dispatcher =
    Facemc::ParticleCrossingSurfaceEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 1 );

  Facemc::ParticleCrossingSurfaceEventDispatcherDB::detachObserver( 1, 0 );

  dispatcher = 
    Facemc::ParticleCrossingSurfaceEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 1 );
}

//---------------------------------------------------------------------------//
// Check that an observer can be detached from all dispatchers
TEUCHOS_UNIT_TEST( ParticleCrossingSurfaceEventDispatcherDB,
		   detachObserver_all_dispatchers )
{
  Facemc::ParticleCrossingSurfaceEventDispatcherDB::detachObserver( 1 );

  Teuchos::RCP<Facemc::ParticleCrossingSurfaceEventDispatcher> dispatcher =
    Facemc::ParticleCrossingSurfaceEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 0 );

  dispatcher = 
    Facemc::ParticleCrossingSurfaceEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 0 );
}

//---------------------------------------------------------------------------//
// Check that an all observers can be detached from all dispatchers
TEUCHOS_UNIT_TEST( ParticleCrossingSurfaceEventDispatcherDB,
		   detachAllObservers )
{
  Teuchos::RCP<Facemc::ParticleCrossingSurfaceEventObserver> observer_1 =
    Teuchos::rcp_dynamic_cast<Facemc::ParticleCrossingSurfaceEventObserver>( 
								 estimator_1 );
  Teuchos::RCP<Facemc::ParticleCrossingSurfaceEventObserver> observer_2 =
    Teuchos::rcp_dynamic_cast<Facemc::ParticleCrossingSurfaceEventObserver>(
								 estimator_2 );
  
  Facemc::ParticleCrossingSurfaceEventDispatcherDB::attachObserver(
							  0,
							  estimator_1->getId(),
							  observer_1 );
  Facemc::ParticleCrossingSurfaceEventDispatcherDB::attachObserver(
							  1,
							  estimator_1->getId(),
							  observer_1 );
  Facemc::ParticleCrossingSurfaceEventDispatcherDB::attachObserver(
							  0,
							  estimator_2->getId(),
							  observer_2 );
  Facemc::ParticleCrossingSurfaceEventDispatcherDB::attachObserver(
							  1,
							  estimator_2->getId(),
							  observer_2 );
    
  observer_1.reset();
  observer_2.reset();

  Teuchos::RCP<Facemc::ParticleCrossingSurfaceEventDispatcher> dispatcher =
    Facemc::ParticleCrossingSurfaceEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 2 );
  
  dispatcher =
    Facemc::ParticleCrossingSurfaceEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 2 );
  
  Facemc::ParticleCrossingSurfaceEventDispatcherDB::detachAllObservers();

  dispatcher =
    Facemc::ParticleCrossingSurfaceEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 0 );
  
  dispatcher =
    Facemc::ParticleCrossingSurfaceEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 0 );
}

//---------------------------------------------------------------------------//
// end tstParticleCrossingSurfaceEventDispatcherDB.cpp
//---------------------------------------------------------------------------//
