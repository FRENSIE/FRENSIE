//---------------------------------------------------------------------------//
//!
//! \file   tstParticleEnteringCellEventDispatcherDB.cpp
//! \author Alex Robinson
//! \brief  Particle entering cell event dispatcher database unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_CellPulseHeightEstimator.hpp"
#include "MonteCarlo_ParticleEnteringCellEventDispatcherDB.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Geometry_ModuleTraits.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
Teuchos::RCP<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier> >
estimator_1;

Teuchos::RCP<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_2;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the estimator
template<typename CellPulseHeightEstimator>
void initializeCellPulseHeightEstimator(
			    const unsigned estimator_id,
			    Teuchos::RCP<CellPulseHeightEstimator>& estimator )
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
TEUCHOS_UNIT_TEST( ParticleEnteringCellEventDispatcherDB, getDispatcher )
{
  Teuchos::RCP<MonteCarlo::ParticleEnteringCellEventDispatcher> dispatcher =
    MonteCarlo::ParticleEnteringCellEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getId(), 0 );

  dispatcher = 
    MonteCarlo::ParticleEnteringCellEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getId(), 1 );
}

//---------------------------------------------------------------------------//
// Check that observers can be attached to dispatchers
TEUCHOS_UNIT_TEST( ParticleEnteringCellEventDispatcherDB, attachObserver )
{
  initializeCellPulseHeightEstimator( 0u, estimator_1 );
  initializeCellPulseHeightEstimator( 1u, estimator_2 );

  Teuchos::RCP<MonteCarlo::ParticleEnteringCellEventObserver> observer_1 =
    Teuchos::rcp_dynamic_cast<MonteCarlo::ParticleEnteringCellEventObserver>( 
								 estimator_1 );
  Teuchos::RCP<MonteCarlo::ParticleEnteringCellEventObserver> observer_2 =
    Teuchos::rcp_dynamic_cast<MonteCarlo::ParticleEnteringCellEventObserver>(
								 estimator_2 );
  
  MonteCarlo::ParticleEnteringCellEventDispatcherDB::attachObserver(
							  0,
							  estimator_1->getId(),
							  observer_1 );
  MonteCarlo::ParticleEnteringCellEventDispatcherDB::attachObserver(
							  1,
							  estimator_1->getId(),
							  observer_1 );
  MonteCarlo::ParticleEnteringCellEventDispatcherDB::attachObserver(
							  0,
							  estimator_2->getId(),
							  observer_2 );
  MonteCarlo::ParticleEnteringCellEventDispatcherDB::attachObserver(
							  1,
							  estimator_2->getId(),
							  observer_2 );
    
  observer_1.reset();
  observer_2.reset();
  
  TEST_EQUALITY_CONST( estimator_1.total_count(), 3 );
  TEST_EQUALITY_CONST( estimator_2.total_count(), 3 );

  Teuchos::RCP<MonteCarlo::ParticleEnteringCellEventDispatcher> dispatcher =
    MonteCarlo::ParticleEnteringCellEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 2 );

  dispatcher =
    MonteCarlo::ParticleEnteringCellEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 2 );
}

//---------------------------------------------------------------------------//
// Check that a collision event can be dispatched
TEUCHOS_UNIT_TEST( ParticleEnteringCellEventDispatcherDB,
		   dispatchParticleEnteringCellEvent )
{
  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );

  MonteCarlo::ParticleEnteringCellEventDispatcherDB::dispatchParticleEnteringCellEvent(
								      particle,
								      0 );

  TEST_ASSERT( estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2->hasUncommittedHistoryContribution() );
  
  estimator_1->commitHistoryContribution();
  estimator_2->commitHistoryContribution();

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  

  MonteCarlo::ParticleEnteringCellEventDispatcherDB::dispatchParticleEnteringCellEvent(
								      particle,
								      1 );

  TEST_ASSERT( estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2->hasUncommittedHistoryContribution() );
}

//---------------------------------------------------------------------------//
// Check that an observer can be detached from the dispatcher
TEUCHOS_UNIT_TEST( ParticleEnteringCellEventDispatcherDB, 
		   detachObserver_dispatcher )
{
  MonteCarlo::ParticleEnteringCellEventDispatcherDB::detachObserver( 0, 0 );

  Teuchos::RCP<MonteCarlo::ParticleEnteringCellEventDispatcher> dispatcher =
    MonteCarlo::ParticleEnteringCellEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 1 );

  MonteCarlo::ParticleEnteringCellEventDispatcherDB::detachObserver( 1, 0 );

  dispatcher = 
    MonteCarlo::ParticleEnteringCellEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 1 );
}

//---------------------------------------------------------------------------//
// Check that an observer can be detached from all dispatchers
TEUCHOS_UNIT_TEST( ParticleEnteringCellEventDispatcherDB,
		   detachObserver_all_dispatchers )
{
  MonteCarlo::ParticleEnteringCellEventDispatcherDB::detachObserver( 1 );

  Teuchos::RCP<MonteCarlo::ParticleEnteringCellEventDispatcher> dispatcher =
    MonteCarlo::ParticleEnteringCellEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 0 );

  dispatcher = 
    MonteCarlo::ParticleEnteringCellEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 0 );
}

//---------------------------------------------------------------------------//
// Check that an all observers can be detached from all dispatchers
TEUCHOS_UNIT_TEST( ParticleEnteringCellEventDispatcherDB,
		   detachAllObservers )
{
  Teuchos::RCP<MonteCarlo::ParticleEnteringCellEventObserver> observer_1 =
    Teuchos::rcp_dynamic_cast<MonteCarlo::ParticleEnteringCellEventObserver>( 
								 estimator_1 );
  Teuchos::RCP<MonteCarlo::ParticleEnteringCellEventObserver> observer_2 =
    Teuchos::rcp_dynamic_cast<MonteCarlo::ParticleEnteringCellEventObserver>(
								 estimator_2 );
  
  MonteCarlo::ParticleEnteringCellEventDispatcherDB::attachObserver(
							  0,
							  estimator_1->getId(),
							  observer_1 );
  MonteCarlo::ParticleEnteringCellEventDispatcherDB::attachObserver(
							  1,
							  estimator_1->getId(),
							  observer_1 );
  MonteCarlo::ParticleEnteringCellEventDispatcherDB::attachObserver(
							  0,
							  estimator_2->getId(),
							  observer_2 );
  MonteCarlo::ParticleEnteringCellEventDispatcherDB::attachObserver(
							  1,
							  estimator_2->getId(),
							  observer_2 );
    
  observer_1.reset();
  observer_2.reset();

  Teuchos::RCP<MonteCarlo::ParticleEnteringCellEventDispatcher> dispatcher =
    MonteCarlo::ParticleEnteringCellEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 2 );
  
  dispatcher =
    MonteCarlo::ParticleEnteringCellEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 2 );
  
  MonteCarlo::ParticleEnteringCellEventDispatcherDB::detachAllObservers();

  dispatcher =
    MonteCarlo::ParticleEnteringCellEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 0 );
  
  dispatcher =
    MonteCarlo::ParticleEnteringCellEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 0 );
}

//---------------------------------------------------------------------------//
// end tstParticleEnteringCellEventDispatcherDB.cpp
//---------------------------------------------------------------------------//
