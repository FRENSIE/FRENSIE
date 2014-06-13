//---------------------------------------------------------------------------//
//!
//! \file   tstParticleCrossingSurfaceEventDispatcher.cpp
//! \author Alex Robinson
//! \brief  Particle crossing surface event dispatcher unit tests
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
#include "Facemc_ParticleCrossingSurfaceEventDispatcher.hpp"
#include "Facemc_PhotonState.hpp"
#include "Geometry_ModuleTraits.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
Teuchos::RCP<Facemc::SurfaceCurrentEstimator<Facemc::WeightMultiplier> >
estimator_1;

Teuchos::RCP<Facemc::SurfaceFluxEstimator<Facemc::WeightAndEnergyMultiplier> >
estimator_2;

Teuchos::RCP<Facemc::ParticleCrossingSurfaceEventDispatcher> dispatcher(
		     new Facemc::ParticleCrossingSurfaceEventDispatcher( 0 ) );

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the estimator
template<typename SurfaceEstimator>
void initializeSurfaceEstimator( const unsigned estimator_id,
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

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the surface id associated with the dispatcher can be returned
TEUCHOS_UNIT_TEST( ParticleCrossingSurfaceEventDispatcher, getId )
{
  TEST_EQUALITY_CONST( dispatcher->getId(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the number of observers attached tot he disp. can be returned
TEUCHOS_UNIT_TEST( ParticleCrossingSurfaceEventDispatcher, 
		   getNumberOfObservers )
{
  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 0 );
}

//---------------------------------------------------------------------------//
// Check that an observer can be attached to the dispatcher
TEUCHOS_UNIT_TEST( ParticleCrossingSurfaceEventDispatcher, attachObserver )
{
  initializeSurfaceEstimator( 0u, estimator_1 );
  initializeSurfaceEstimator( 1u, estimator_2 );

  Teuchos::RCP<Facemc::ParticleCrossingSurfaceEventObserver> observer_1 = 
    Teuchos::rcp_dynamic_cast<Facemc::ParticleCrossingSurfaceEventObserver>(
								 estimator_1 );

  Teuchos::RCP<Facemc::ParticleCrossingSurfaceEventObserver> observer_2 =
    Teuchos::rcp_dynamic_cast<Facemc::ParticleCrossingSurfaceEventObserver>(
								 estimator_2 );

  dispatcher->attachObserver( estimator_1->getId(), observer_1 );
  dispatcher->attachObserver( estimator_2->getId(), observer_2 );

  observer_1.reset();
  observer_2.reset();

  TEST_EQUALITY_CONST( estimator_1.total_count(), 2 );
  TEST_EQUALITY_CONST( estimator_2.total_count(), 2 );
  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 2 );
}

//---------------------------------------------------------------------------//
// Check that a surface crossing event can be dispatched
TEUCHOS_UNIT_TEST( ParticleCrossingSurfaceEventDispatcher,
		   dispatchParticleCrossingSurfaceEvent )
{
  Facemc::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );

  dispatcher->dispatchParticleCrossingSurfaceEvent( particle, 0, 1.0 );

  TEST_ASSERT( estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2->hasUncommittedHistoryContribution() );
}

//---------------------------------------------------------------------------//
// Check that an observer can be detached from the dispatcher
TEUCHOS_UNIT_TEST( ParticleCrossingSurfaceEventDispatcher, detachObserver )
{
  dispatcher->detachObserver( 0u );

  TEST_EQUALITY_CONST( estimator_1.total_count(), 1 );
  TEST_EQUALITY_CONST( estimator_2.total_count(), 2 );
  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 1 );

  dispatcher->detachObserver( 1u );

  TEST_EQUALITY_CONST( estimator_1.total_count(), 1 );
  TEST_EQUALITY_CONST( estimator_2.total_count(), 1 );
  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 0 );  

  // Remove nonexistent estimator
  dispatcher->detachObserver( 2u );

  TEST_EQUALITY_CONST( estimator_1.total_count(), 1 );
  TEST_EQUALITY_CONST( estimator_2.total_count(), 1 );
  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 0 );  
}

//---------------------------------------------------------------------------//
// end tstParticleCrossingSurfaceEventDispatcher.cpp
//---------------------------------------------------------------------------//
