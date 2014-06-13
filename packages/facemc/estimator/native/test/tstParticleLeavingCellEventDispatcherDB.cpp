//---------------------------------------------------------------------------//
//!
//! \file   tstParticleLeavingCellEventDispatcherDB.cpp
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
#include "Facemc_CellPulseHeightEstimator.hpp"
#include "Facemc_ParticleLeavingCellEventDispatcherDB.hpp"
#include "Facemc_PhotonState.hpp"
#include "Geometry_ModuleTraits.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
Teuchos::RCP<Facemc::CellPulseHeightEstimator<Facemc::WeightMultiplier> >
estimator_1;

Teuchos::RCP<Facemc::CellPulseHeightEstimator<Facemc::WeightAndEnergyMultiplier> >
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

  Teuchos::Array<Facemc::ParticleType> particle_types( 1 );
  particle_types[0] = Facemc::PHOTON;
  
  estimator->setParticleTypes( particle_types );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the correct event dispatchers can be returned
TEUCHOS_UNIT_TEST( ParticleLeavingCellEventDispatcherDB, getDispatcher )
{
  Teuchos::RCP<Facemc::ParticleLeavingCellEventDispatcher> dispatcher =
    Facemc::ParticleLeavingCellEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getId(), 0 );

  dispatcher = 
    Facemc::ParticleLeavingCellEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getId(), 1 );
}

//---------------------------------------------------------------------------//
// Check that observers can be attached to dispatchers
TEUCHOS_UNIT_TEST( ParticleLeavingCellEventDispatcherDB, attachObserver )
{
  initializeCellPulseHeightEstimator( 0u, estimator_1 );
  initializeCellPulseHeightEstimator( 1u, estimator_2 );

  Teuchos::RCP<Facemc::ParticleLeavingCellEventObserver> observer_1 =
    Teuchos::rcp_dynamic_cast<Facemc::ParticleLeavingCellEventObserver>( 
								 estimator_1 );
  Teuchos::RCP<Facemc::ParticleLeavingCellEventObserver> observer_2 =
    Teuchos::rcp_dynamic_cast<Facemc::ParticleLeavingCellEventObserver>(
								 estimator_2 );
  
  Facemc::ParticleLeavingCellEventDispatcherDB::attachObserver(
							  0,
							  estimator_1->getId(),
							  observer_1 );
  Facemc::ParticleLeavingCellEventDispatcherDB::attachObserver(
							  1,
							  estimator_1->getId(),
							  observer_1 );
  Facemc::ParticleLeavingCellEventDispatcherDB::attachObserver(
							  0,
							  estimator_2->getId(),
							  observer_2 );
  Facemc::ParticleLeavingCellEventDispatcherDB::attachObserver(
							  1,
							  estimator_2->getId(),
							  observer_2 );
    
  observer_1.reset();
  observer_2.reset();
  
  TEST_EQUALITY_CONST( estimator_1.total_count(), 3 );
  TEST_EQUALITY_CONST( estimator_2.total_count(), 3 );

  Teuchos::RCP<Facemc::ParticleLeavingCellEventDispatcher> dispatcher =
    Facemc::ParticleLeavingCellEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 2 );

  dispatcher =
    Facemc::ParticleLeavingCellEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 2 );
}

//---------------------------------------------------------------------------//
// Check that a collision event can be dispatched
TEUCHOS_UNIT_TEST( ParticleLeavingCellEventDispatcherDB,
		   dispatchParticleLeavingCellEvent )
{
  Facemc::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );

  Facemc::ParticleLeavingCellEventDispatcherDB::dispatchParticleLeavingCellEvent(
								      particle,
								      0 );

  TEST_ASSERT( estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2->hasUncommittedHistoryContribution() );
  
  estimator_1->commitHistoryContribution();
  estimator_2->commitHistoryContribution();

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  

  Facemc::ParticleLeavingCellEventDispatcherDB::dispatchParticleLeavingCellEvent(
								      particle,
								      1 );

  TEST_ASSERT( estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2->hasUncommittedHistoryContribution() );
}

//---------------------------------------------------------------------------//
// Check that an observer can be detached from the dispatcher
TEUCHOS_UNIT_TEST( ParticleLeavingCellEventDispatcherDB, 
		   detachObserver_dispatcher )
{
  Facemc::ParticleLeavingCellEventDispatcherDB::detachObserver( 0, 0 );

  Teuchos::RCP<Facemc::ParticleLeavingCellEventDispatcher> dispatcher =
    Facemc::ParticleLeavingCellEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 1 );

  Facemc::ParticleLeavingCellEventDispatcherDB::detachObserver( 1, 0 );

  dispatcher = 
    Facemc::ParticleLeavingCellEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 1 );
}

//---------------------------------------------------------------------------//
// Check that an observer can be detached from all dispatchers
TEUCHOS_UNIT_TEST( ParticleLeavingCellEventDispatcherDB,
		   detachObserver_all_dispatchers )
{
  Facemc::ParticleLeavingCellEventDispatcherDB::detachObserver( 1 );

  Teuchos::RCP<Facemc::ParticleLeavingCellEventDispatcher> dispatcher =
    Facemc::ParticleLeavingCellEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 0 );

  dispatcher = 
    Facemc::ParticleLeavingCellEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 0 );
}

//---------------------------------------------------------------------------//
// Check that an all observers can be detached from all dispatchers
TEUCHOS_UNIT_TEST( ParticleLeavingCellEventDispatcherDB,
		   detachAllObservers )
{
  Teuchos::RCP<Facemc::ParticleLeavingCellEventObserver> observer_1 =
    Teuchos::rcp_dynamic_cast<Facemc::ParticleLeavingCellEventObserver>( 
								 estimator_1 );
  Teuchos::RCP<Facemc::ParticleLeavingCellEventObserver> observer_2 =
    Teuchos::rcp_dynamic_cast<Facemc::ParticleLeavingCellEventObserver>(
								 estimator_2 );
  
  Facemc::ParticleLeavingCellEventDispatcherDB::attachObserver(
							  0,
							  estimator_1->getId(),
							  observer_1 );
  Facemc::ParticleLeavingCellEventDispatcherDB::attachObserver(
							  1,
							  estimator_1->getId(),
							  observer_1 );
  Facemc::ParticleLeavingCellEventDispatcherDB::attachObserver(
							  0,
							  estimator_2->getId(),
							  observer_2 );
  Facemc::ParticleLeavingCellEventDispatcherDB::attachObserver(
							  1,
							  estimator_2->getId(),
							  observer_2 );
    
  observer_1.reset();
  observer_2.reset();

  Teuchos::RCP<Facemc::ParticleLeavingCellEventDispatcher> dispatcher =
    Facemc::ParticleLeavingCellEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 2 );
  
  dispatcher =
    Facemc::ParticleLeavingCellEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 2 );
  
  Facemc::ParticleLeavingCellEventDispatcherDB::detachAllObservers();

  dispatcher =
    Facemc::ParticleLeavingCellEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 0 );
  
  dispatcher =
    Facemc::ParticleLeavingCellEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 0 );
}

//---------------------------------------------------------------------------//
// end tstParticleLeavingCellEventDispatcherDB.cpp
//---------------------------------------------------------------------------//
