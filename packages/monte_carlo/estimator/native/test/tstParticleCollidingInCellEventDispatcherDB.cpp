//---------------------------------------------------------------------------//
//!
//! \file   tstParticleCollidingInCellEventDispatcherDB.cpp
//! \author Alex Robinson
//! \brief  Particle colliding in cell event dispatcher database unit tests
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
#include "MonteCarlo_CellCollisionFluxEstimator.hpp"
#include "MonteCarlo_ParticleCollidingInCellEventDispatcherDB.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Geometry_ModuleTraits.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightMultiplier> >
    estimator_1;

std::shared_ptr<MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
    estimator_2;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the estimator
template<typename CellCollisionFluxEstimator>
void initializeCellCollisionFluxEstimator( 
			  const unsigned estimator_id,
			  std::shared_ptr<CellCollisionFluxEstimator>& estimator )
{  
  // Set the entity ids
  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> 
    cell_ids( 2 );
  cell_ids[0] = 0;
  cell_ids[1] = 1;

  Teuchos::Array<double> cell_volumes( 2 );
  cell_volumes[0] = 1.0;
  cell_volumes[1] = 2.0;

  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  estimator.reset( new CellCollisionFluxEstimator( estimator_id,
						   estimator_multiplier,
						   cell_ids,
						   cell_volumes ) );

  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
  particle_types[0] = MonteCarlo::PHOTON;
  
  estimator->setParticleTypes( particle_types );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the correct event dispatchers can be returned
TEUCHOS_UNIT_TEST( ParticleCollidingInCellEventDispatcherDB, getDispatcher )
{
  TEST_EQUALITY_CONST( MonteCarlo::ParticleCollidingInCellEventDispatcherDB::getDispatcher( 0 ).getId(), 0 );

  TEST_EQUALITY_CONST( MonteCarlo::ParticleCollidingInCellEventDispatcherDB::getDispatcher( 1 ).getId(), 1 );
}

//---------------------------------------------------------------------------//
// Check that observers can be attached to dispatchers
TEUCHOS_UNIT_TEST( ParticleCollidingInCellEventDispatcherDB, attachObserver )
{
  initializeCellCollisionFluxEstimator( 0u, estimator_1 );
  initializeCellCollisionFluxEstimator( 1u, estimator_2 );

  std::shared_ptr<MonteCarlo::ParticleCollidingInCellEventObserver> observer_1 =
    std::dynamic_pointer_cast<MonteCarlo::ParticleCollidingInCellEventObserver>( 
								 estimator_1 );
  std::shared_ptr<MonteCarlo::ParticleCollidingInCellEventObserver> observer_2 =
    std::dynamic_pointer_cast<MonteCarlo::ParticleCollidingInCellEventObserver>(
								 estimator_2 );
  
  MonteCarlo::ParticleCollidingInCellEventDispatcherDB::attachObserver(
							  0,
							  estimator_1->getId(),
							  observer_1 );
  MonteCarlo::ParticleCollidingInCellEventDispatcherDB::attachObserver(
							  1,
							  estimator_1->getId(),
							  observer_1 );
  MonteCarlo::ParticleCollidingInCellEventDispatcherDB::attachObserver(
							  0,
							  estimator_2->getId(),
							  observer_2 );
  MonteCarlo::ParticleCollidingInCellEventDispatcherDB::attachObserver(
							  1,
							  estimator_2->getId(),
							  observer_2 );
    
  observer_1.reset();
  observer_2.reset();
  
  TEST_EQUALITY_CONST( estimator_1.use_count(), 3 );
  TEST_EQUALITY_CONST( estimator_2.use_count(), 3 );

  TEST_EQUALITY_CONST( MonteCarlo::ParticleCollidingInCellEventDispatcherDB::getDispatcher( 0 ).getNumberOfObservers(), 2 );

  TEST_EQUALITY_CONST( MonteCarlo::ParticleCollidingInCellEventDispatcherDB::getDispatcher( 1 ).getNumberOfObservers(), 2 );
}

//---------------------------------------------------------------------------//
// Check that a collision event can be dispatched
TEUCHOS_UNIT_TEST( ParticleCollidingInCellEventDispatcherDB,
		   dispatchParticleCollidingInCellEvent )
{
  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );

  MonteCarlo::ParticleCollidingInCellEventDispatcherDB::dispatchParticleCollidingInCellEvent(
								      particle,
								      0, 
								      1.0 );

  TEST_ASSERT( estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2->hasUncommittedHistoryContribution() );
  
  estimator_1->commitHistoryContribution();
  estimator_2->commitHistoryContribution();

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  

  MonteCarlo::ParticleCollidingInCellEventDispatcherDB::dispatchParticleCollidingInCellEvent(
								      particle,
								      1, 
								      1.0 );

  TEST_ASSERT( estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2->hasUncommittedHistoryContribution() );
}

//---------------------------------------------------------------------------//
// Check that an observer can be detached from the dispatcher
TEUCHOS_UNIT_TEST( ParticleCollidingInCellEventDispatcherDB, 
		   detachObserver_dispatcher )
{
  MonteCarlo::ParticleCollidingInCellEventDispatcherDB::detachObserver( 0, 0 );

  TEST_EQUALITY_CONST( MonteCarlo::ParticleCollidingInCellEventDispatcherDB::getDispatcher( 0 ).getNumberOfObservers(), 1 );

  MonteCarlo::ParticleCollidingInCellEventDispatcherDB::detachObserver( 1, 0 );

  TEST_EQUALITY_CONST( MonteCarlo::ParticleCollidingInCellEventDispatcherDB::getDispatcher( 1 ).getNumberOfObservers(), 1 );
}

//---------------------------------------------------------------------------//
// Check that an observer can be detached from all dispatchers
TEUCHOS_UNIT_TEST( ParticleCollidingInCellEventDispatcherDB,
		   detachObserver_all_dispatchers )
{
  MonteCarlo::ParticleCollidingInCellEventDispatcherDB::detachObserver( 1 );

  TEST_EQUALITY_CONST( MonteCarlo::ParticleCollidingInCellEventDispatcherDB::getDispatcher( 0 ).getNumberOfObservers(), 0 );

  TEST_EQUALITY_CONST( MonteCarlo::ParticleCollidingInCellEventDispatcherDB::getDispatcher( 1 ).getNumberOfObservers(), 0 );
}

//---------------------------------------------------------------------------//
// Check that an all observers can be detached from all dispatchers
TEUCHOS_UNIT_TEST( ParticleCollidingInCellEventDispatcherDB,
		   detachAllObservers )
{
  std::shared_ptr<MonteCarlo::ParticleCollidingInCellEventObserver> observer_1 =
    std::dynamic_pointer_cast<MonteCarlo::ParticleCollidingInCellEventObserver>( 
								 estimator_1 );
  std::shared_ptr<MonteCarlo::ParticleCollidingInCellEventObserver> observer_2 =
    std::dynamic_pointer_cast<MonteCarlo::ParticleCollidingInCellEventObserver>(
								 estimator_2 );
  
  MonteCarlo::ParticleCollidingInCellEventDispatcherDB::attachObserver(
							  0,
							  estimator_1->getId(),
							  observer_1 );
  MonteCarlo::ParticleCollidingInCellEventDispatcherDB::attachObserver(
							  1,
							  estimator_1->getId(),
							  observer_1 );
  MonteCarlo::ParticleCollidingInCellEventDispatcherDB::attachObserver(
							  0,
							  estimator_2->getId(),
							  observer_2 );
  MonteCarlo::ParticleCollidingInCellEventDispatcherDB::attachObserver(
							  1,
							  estimator_2->getId(),
							  observer_2 );
    
  observer_1.reset();
  observer_2.reset();

  TEST_EQUALITY_CONST( MonteCarlo::ParticleCollidingInCellEventDispatcherDB::getDispatcher( 0 ).getNumberOfObservers(), 2 );
  
  TEST_EQUALITY_CONST( MonteCarlo::ParticleCollidingInCellEventDispatcherDB::getDispatcher( 1 ).getNumberOfObservers(), 2 );
  
  MonteCarlo::ParticleCollidingInCellEventDispatcherDB::detachAllObservers();

  TEST_EQUALITY_CONST( MonteCarlo::ParticleCollidingInCellEventDispatcherDB::getDispatcher( 0 ).getNumberOfObservers(), 0 );
  
  TEST_EQUALITY_CONST( MonteCarlo::ParticleCollidingInCellEventDispatcherDB::getDispatcher( 1 ).getNumberOfObservers(), 0 );
}

//---------------------------------------------------------------------------//
// end tstParticleCollidingInCellEventDispatcher.cpp
//---------------------------------------------------------------------------//
