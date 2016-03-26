//---------------------------------------------------------------------------//
//!
//! \file   tstParticleEnteringCellEventDispatcher.cpp
//! \author Alex Robinson
//! \brief  Particle entering cell event dispatcher unit tests
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
#include "MonteCarlo_CellPulseHeightEstimator.hpp"
#include "MonteCarlo_ParticleEnteringCellEventDispatcher.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Geometry_ModuleTraits.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier> >
estimator_1;

std::shared_ptr<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_2;

std::shared_ptr<MonteCarlo::ParticleEnteringCellEventDispatcher>
dispatcher( new MonteCarlo::ParticleEnteringCellEventDispatcher );

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the estimator
template<typename CellPulseHeightEstimator>
void initializeCellPulseHeightEstimator(
			    const unsigned estimator_id,
			    std::shared_ptr<CellPulseHeightEstimator>& estimator )
{
  // Set the entity ids
  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
    cell_ids( 2 );
  cell_ids[0] = 0;
  cell_ids[1] = 1;

  // Set the estimator multiplier
  double estimator_multiplier = 1.0;

  estimator.reset( new CellPulseHeightEstimator( estimator_id,
						 estimator_multiplier,
						 cell_ids ) );

  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
  particle_types[0] = MonteCarlo::PHOTON;
  
  estimator->setParticleTypes( particle_types );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the correct event dispatchers can be returned
TEUCHOS_UNIT_TEST( ParticleEnteringCellEventDispatcher, getLocalDispatcher )
{
  TEST_EQUALITY_CONST( dispatcher->getLocalDispatcher( 0 ).getId(), 0 );

  TEST_EQUALITY_CONST( dispatcher->getLocalDispatcher( 1 ).getId(), 1 );
}

//---------------------------------------------------------------------------//
// Check that observers can be attached to dispatchers
TEUCHOS_UNIT_TEST( ParticleEnteringCellEventDispatcher, attachObserver )
{
  initializeCellPulseHeightEstimator( 0u, estimator_1 );
  initializeCellPulseHeightEstimator( 1u, estimator_2 );

  std::shared_ptr<MonteCarlo::ParticleEnteringCellEventObserver> observer_1 =
    std::dynamic_pointer_cast<MonteCarlo::ParticleEnteringCellEventObserver>( 
								 estimator_1 );
  std::shared_ptr<MonteCarlo::ParticleEnteringCellEventObserver> observer_2 =
    std::dynamic_pointer_cast<MonteCarlo::ParticleEnteringCellEventObserver>(
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
TEUCHOS_UNIT_TEST( ParticleEnteringCellEventDispatcher,
		   dispatchParticleEnteringCellEvent )
{
  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );

  dispatcher->dispatchParticleEnteringCellEvent( particle, 0 );

  TEST_ASSERT( estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2->hasUncommittedHistoryContribution() );
  
  estimator_1->commitHistoryContribution();
  estimator_2->commitHistoryContribution();

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  
  dispatcher->dispatchParticleEnteringCellEvent( particle, 1 );

  TEST_ASSERT( estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2->hasUncommittedHistoryContribution() );
}

//---------------------------------------------------------------------------//
// Check that an observer can be detached from the dispatcher
TEUCHOS_UNIT_TEST( ParticleEnteringCellEventDispatcher, 
		   detachObserver_dispatcher )
{
  dispatcher->detachObserver( 0, 0 );

  TEST_EQUALITY_CONST( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers(), 1 );

  dispatcher->detachObserver( 1, 0 );

  TEST_EQUALITY_CONST( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers(), 1 );
}

//---------------------------------------------------------------------------//
// Check that an observer can be detached from all dispatchers
TEUCHOS_UNIT_TEST( ParticleEnteringCellEventDispatcher,
		   detachObserver_all_dispatchers )
{
  dispatcher->detachObserver( 1 );

  TEST_EQUALITY_CONST( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers(), 0 );

  TEST_EQUALITY_CONST( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers(), 0 );
}

//---------------------------------------------------------------------------//
// Check that an all observers can be detached from all dispatchers
TEUCHOS_UNIT_TEST( ParticleEnteringCellEventDispatcher,
		   detachAllObservers )
{
  std::shared_ptr<MonteCarlo::ParticleEnteringCellEventObserver> observer_1 =
    std::dynamic_pointer_cast<MonteCarlo::ParticleEnteringCellEventObserver>( 
								 estimator_1 );
  std::shared_ptr<MonteCarlo::ParticleEnteringCellEventObserver> observer_2 =
    std::dynamic_pointer_cast<MonteCarlo::ParticleEnteringCellEventObserver>(
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
// end tstParticleEnteringCellEventDispatcher.cpp
//---------------------------------------------------------------------------//
