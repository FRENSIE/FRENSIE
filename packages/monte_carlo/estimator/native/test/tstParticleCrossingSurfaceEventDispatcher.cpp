//---------------------------------------------------------------------------//
//!
//! \file   tstParticleCrossingSurfaceEventDispatcherDB.cpp
//! \author Alex Robinson
//! \brief  Particle crossing surface event dispatcher unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_SurfaceCurrentEstimator.hpp"
#include "MonteCarlo_SurfaceFluxEstimator.hpp"
#include "MonteCarlo_ParticleCrossingSurfaceEventDispatcher.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Geometry_ModuleTraits.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightMultiplier> >
estimator_1;

std::shared_ptr<MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_2;

std::shared_ptr<MonteCarlo::ParticleCrossingSurfaceEventDispatcher>
  dispatcher( new MonteCarlo::ParticleCrossingSurfaceEventDispatcher );

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the estimator
template<typename SurfaceEstimator>
void initializeSurfaceFluxEstimator( const unsigned estimator_id,
				 std::shared_ptr<SurfaceEstimator>& estimator )
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

  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
  particle_types[0] = MonteCarlo::PHOTON;

  estimator->setParticleTypes( particle_types );
}

// Initialize the estimator
template<typename SurfaceEstimator>
void initializeSurfaceCurrentEstimator( const unsigned estimator_id,
				 std::shared_ptr<SurfaceEstimator>& estimator )
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

  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
  particle_types[0] = MonteCarlo::PHOTON;

  estimator->setParticleTypes( particle_types );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the correct event dispatchers can be returned
TEUCHOS_UNIT_TEST( ParticleCrossingSurfaceEventDispatcher, getLocalDispatcher )
{
  TEST_EQUALITY_CONST( dispatcher->getLocalDispatcher( 0 ).getId(), 0 );

  TEST_EQUALITY_CONST( dispatcher->getLocalDispatcher( 1 ).getId(), 1 );
}

//---------------------------------------------------------------------------//
// Check that observers can be attached to dispatchers
TEUCHOS_UNIT_TEST( ParticleCrossingSurfaceEventDispatcher, attachObserver )
{
  initializeSurfaceCurrentEstimator( 0u, estimator_1 );
  initializeSurfaceFluxEstimator( 1u, estimator_2 );

  std::shared_ptr<MonteCarlo::ParticleCrossingSurfaceEventObserver> observer_1 =
    std::dynamic_pointer_cast<MonteCarlo::ParticleCrossingSurfaceEventObserver>( 
								 estimator_1 );
  std::shared_ptr<MonteCarlo::ParticleCrossingSurfaceEventObserver> observer_2 =
    std::dynamic_pointer_cast<MonteCarlo::ParticleCrossingSurfaceEventObserver>(
								 estimator_2 );
  
  dispatcher->attachObserver( 0, estimator_1->getId(), observer_1 );
  
  dispatcher->attachObserver( 1, estimator_1->getId(), observer_1 );
  
  dispatcher->attachObserver( 0, estimator_2->getId(), observer_2 );
  
  dispatcher->attachObserver( 1, estimator_2->getId(), observer_2 );
    
  observer_1.reset();
  observer_2.reset();
  
  TEST_EQUALITY_CONST( estimator_1.use_count(), 3 );
  TEST_EQUALITY_CONST( estimator_2.use_count(), 3 );

  TEST_EQUALITY_CONST( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers(), 2 );

  TEST_EQUALITY_CONST( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers(), 2 );
}

//---------------------------------------------------------------------------//
// Check that a collision event can be dispatched
TEUCHOS_UNIT_TEST( ParticleCrossingSurfaceEventDispatcher,
		   dispatchParticleCrossingSurfaceEvent )
{
  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );

  dispatcher->dispatchParticleCrossingSurfaceEvent( particle, 0, 1.0 );

  TEST_ASSERT( estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2->hasUncommittedHistoryContribution() );
  
  estimator_1->commitHistoryContribution();
  estimator_2->commitHistoryContribution();

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  

  dispatcher->dispatchParticleCrossingSurfaceEvent( particle, 1, 1.0 );

  TEST_ASSERT( estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2->hasUncommittedHistoryContribution() );
}

//---------------------------------------------------------------------------//
// Check that an observer can be detached from the dispatcher
TEUCHOS_UNIT_TEST( ParticleCrossingSurfaceEventDispatcher, 
		   detachObserver_dispatcher )
{
  dispatcher->detachObserver( 0, 0 );

  TEST_EQUALITY_CONST( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers(), 1 );

  dispatcher->detachObserver( 1, 0 );

  TEST_EQUALITY_CONST( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers(), 1 );
}

//---------------------------------------------------------------------------//
// Check that an observer can be detached from all dispatchers
TEUCHOS_UNIT_TEST( ParticleCrossingSurfaceEventDispatcher,
		   detachObserver_all_dispatchers )
{
  dispatcher->detachObserver( 1 );

  TEST_EQUALITY_CONST( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers(), 0 );

  TEST_EQUALITY_CONST( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers(), 0 );
}

//---------------------------------------------------------------------------//
// Check that an all observers can be detached from all dispatchers
TEUCHOS_UNIT_TEST( ParticleCrossingSurfaceEventDispatcher,
		   detachAllObservers )
{
  std::shared_ptr<MonteCarlo::ParticleCrossingSurfaceEventObserver> observer_1 =
    std::dynamic_pointer_cast<MonteCarlo::ParticleCrossingSurfaceEventObserver>( 
								 estimator_1 );
  std::shared_ptr<MonteCarlo::ParticleCrossingSurfaceEventObserver> observer_2 =
    std::dynamic_pointer_cast<MonteCarlo::ParticleCrossingSurfaceEventObserver>(
								 estimator_2 );
  
  dispatcher->attachObserver( 0, estimator_1->getId(), observer_1 );

  dispatcher->attachObserver( 1, estimator_1->getId(), observer_1 );
  
  dispatcher->attachObserver( 0, estimator_2->getId(), observer_2 );
  
  dispatcher->attachObserver( 1, estimator_2->getId(), observer_2 );
    
  observer_1.reset();
  observer_2.reset();

  TEST_EQUALITY_CONST( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers(), 2 );
  
  TEST_EQUALITY_CONST( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers(), 2 );
  
  dispatcher->detachAllObservers();

  TEST_EQUALITY_CONST( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers(), 0 );
  
  TEST_EQUALITY_CONST( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers(), 0 );
}

//---------------------------------------------------------------------------//
// end tstParticleCrossingSurfaceEventDispatcher.cpp
//---------------------------------------------------------------------------//
