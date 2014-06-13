//---------------------------------------------------------------------------//
//!
//! \file   tstParticleSubtrackEndingInCellEventDispatcherDB.cpp
//! \author Alex Robinson
//! \brief  Particle colliding in cell event dispatcher database unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_CellTrackLengthFluxEstimator.hpp"
#include "Facemc_ParticleSubtrackEndingInCellEventDispatcherDB.hpp"
#include "Facemc_PhotonState.hpp"
#include "Geometry_ModuleTraits.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
Teuchos::RCP<Facemc::CellTrackLengthFluxEstimator<Facemc::WeightMultiplier> >
estimator_1;

Teuchos::RCP<Facemc::CellTrackLengthFluxEstimator<Facemc::WeightAndEnergyMultiplier> >
estimator_2;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the estimator
template<typename CellEstimator>
void initializeCellEstimator( const unsigned estimator_id,
			      Teuchos::RCP<CellEstimator>& estimator )
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
  double estimator_multiplier = 1.0;

  estimator.reset( new CellEstimator( estimator_id,
				      estimator_multiplier,
				      cell_ids,
				      cell_volumes ) );

  Teuchos::Array<Facemc::ParticleType> particle_types( 1 );
  particle_types[0] = Facemc::PHOTON;
  
  estimator->setParticleTypes( particle_types );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the correct event dispatchers can be returned
TEUCHOS_UNIT_TEST( ParticleSubtrackEndingInCellEventDispatcherDB, 
		   getDispatcher )
{
  Teuchos::RCP<Facemc::ParticleSubtrackEndingInCellEventDispatcher> dispatcher=
    Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getId(), 0 );

  dispatcher = 
    Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getId(), 1 );
}

//---------------------------------------------------------------------------//
// Check that observers can be attached to dispatchers
TEUCHOS_UNIT_TEST( ParticleSubtrackEndingInCellEventDispatcherDB, 
		   attachObserver )
{
  initializeCellEstimator( 0u, estimator_1 );
  initializeCellEstimator( 1u, estimator_2 );

  Teuchos::RCP<Facemc::ParticleSubtrackEndingInCellEventObserver> observer_1 =
    Teuchos::rcp_dynamic_cast<Facemc::ParticleSubtrackEndingInCellEventObserver>( 
								 estimator_1 );
  Teuchos::RCP<Facemc::ParticleSubtrackEndingInCellEventObserver> observer_2 =
    Teuchos::rcp_dynamic_cast<Facemc::ParticleSubtrackEndingInCellEventObserver>(
								 estimator_2 );
  
  Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::attachObserver(
							  0,
							  estimator_1->getId(),
							  observer_1 );
  Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::attachObserver(
							  1,
							  estimator_1->getId(),
							  observer_1 );
  Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::attachObserver(
							  0,
							  estimator_2->getId(),
							  observer_2 );
  Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::attachObserver(
							  1,
							  estimator_2->getId(),
							  observer_2 );
    
  observer_1.reset();
  observer_2.reset();
  
  TEST_EQUALITY_CONST( estimator_1.total_count(), 3 );
  TEST_EQUALITY_CONST( estimator_2.total_count(), 3 );

  Teuchos::RCP<Facemc::ParticleSubtrackEndingInCellEventDispatcher> dispatcher=
    Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 2 );

  dispatcher =
    Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 2 );
}

//---------------------------------------------------------------------------//
// Check that a collision event can be dispatched
TEUCHOS_UNIT_TEST( ParticleSubtrackEndingInCellEventDispatcherDB,
		   dispatchParticleSubtrackEndingInCellEvent )
{
  Facemc::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );

  Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::dispatchParticleSubtrackEndingInCellEvent(
								      particle,
								      0, 
								      1.0 );

  TEST_ASSERT( estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2->hasUncommittedHistoryContribution() );
  
  estimator_1->commitHistoryContribution();
  estimator_2->commitHistoryContribution();

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  

  Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::dispatchParticleSubtrackEndingInCellEvent(
								      particle,
								      1, 
								      1.0 );

  TEST_ASSERT( estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2->hasUncommittedHistoryContribution() );
}

//---------------------------------------------------------------------------//
// Check that an observer can be detached from the dispatcher
TEUCHOS_UNIT_TEST( ParticleSubtrackEndingInCellEventDispatcherDB, 
		   detachObserver_dispatcher )
{
  Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::detachObserver( 0, 0);

  Teuchos::RCP<Facemc::ParticleSubtrackEndingInCellEventDispatcher> dispatcher=
    Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 1 );

  Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::detachObserver( 1, 0);

  dispatcher = 
    Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 1 );
}

//---------------------------------------------------------------------------//
// Check that an observer can be detached from all dispatchers
TEUCHOS_UNIT_TEST( ParticleSubtrackEndingInCellEventDispatcherDB,
		   detachObserver_all_dispatchers )
{
  Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::detachObserver( 1 );

  Teuchos::RCP<Facemc::ParticleSubtrackEndingInCellEventDispatcher> dispatcher=
    Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 0 );

  dispatcher = 
    Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 0 );
}

//---------------------------------------------------------------------------//
// Check that an all observers can be detached from all dispatchers
TEUCHOS_UNIT_TEST( ParticleSubtrackEndingInCellEventDispatcherDB,
		   detachAllObservers )
{
  Teuchos::RCP<Facemc::ParticleSubtrackEndingInCellEventObserver> observer_1 =
    Teuchos::rcp_dynamic_cast<Facemc::ParticleSubtrackEndingInCellEventObserver>( 
								 estimator_1 );
  Teuchos::RCP<Facemc::ParticleSubtrackEndingInCellEventObserver> observer_2 =
    Teuchos::rcp_dynamic_cast<Facemc::ParticleSubtrackEndingInCellEventObserver>(
								 estimator_2 );
  
  Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::attachObserver(
							  0,
							  estimator_1->getId(),
							  observer_1 );
  Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::attachObserver(
							  1,
							  estimator_1->getId(),
							  observer_1 );
  Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::attachObserver(
							  0,
							  estimator_2->getId(),
							  observer_2 );
  Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::attachObserver(
							  1,
							  estimator_2->getId(),
							  observer_2 );
    
  observer_1.reset();
  observer_2.reset();

  Teuchos::RCP<Facemc::ParticleSubtrackEndingInCellEventDispatcher> dispatcher=
    Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 2 );
  
  dispatcher =
    Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 2 );
  
  Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::detachAllObservers();

  dispatcher =
    Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::getDispatcher( 0 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 0 );
  
  dispatcher =
    Facemc::ParticleSubtrackEndingInCellEventDispatcherDB::getDispatcher( 1 );

  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 0 );
}

//---------------------------------------------------------------------------//
// end tstParticleSubtrackEndingInCellEventDispatcherDB.cpp
//---------------------------------------------------------------------------//
