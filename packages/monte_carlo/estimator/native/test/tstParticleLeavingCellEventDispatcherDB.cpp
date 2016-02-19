//---------------------------------------------------------------------------//
//!
//! \file   tstParticleLeavingCellEventDispatcherDB.cpp
//! \author Alex Robinson
//! \brief  Particle entering cell event dispatcher database unit tests
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
#include "MonteCarlo_ParticleLeavingCellEventDispatcherDB.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Geometry_ModuleTraits.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier> >
estimator_1;

std::shared_ptr<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_2;

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
TEUCHOS_UNIT_TEST( ParticleLeavingCellEventDispatcherDB, getDispatcher )
{
  TEST_EQUALITY_CONST( MonteCarlo::ParticleLeavingCellEventDispatcherDB::getDispatcher( 0 ).getId(), 0 );

  TEST_EQUALITY_CONST( MonteCarlo::ParticleLeavingCellEventDispatcherDB::getDispatcher( 1 ).getId(), 1 );
}

//---------------------------------------------------------------------------//
// Check that observers can be attached to dispatchers
TEUCHOS_UNIT_TEST( ParticleLeavingCellEventDispatcherDB, attachObserver )
{
  initializeCellPulseHeightEstimator( 0u, estimator_1 );
  initializeCellPulseHeightEstimator( 1u, estimator_2 );

  std::shared_ptr<MonteCarlo::ParticleLeavingCellEventObserver> observer_1 =
    std::dynamic_pointer_cast<MonteCarlo::ParticleLeavingCellEventObserver>( 
								 estimator_1 );
  std::shared_ptr<MonteCarlo::ParticleLeavingCellEventObserver> observer_2 =
    std::dynamic_pointer_cast<MonteCarlo::ParticleLeavingCellEventObserver>(
								 estimator_2 );
  
  MonteCarlo::ParticleLeavingCellEventDispatcherDB::attachObserver(
							  0,
							  estimator_1->getId(),
							  observer_1 );
  MonteCarlo::ParticleLeavingCellEventDispatcherDB::attachObserver(
							  1,
							  estimator_1->getId(),
							  observer_1 );
  MonteCarlo::ParticleLeavingCellEventDispatcherDB::attachObserver(
							  0,
							  estimator_2->getId(),
							  observer_2 );
  MonteCarlo::ParticleLeavingCellEventDispatcherDB::attachObserver(
							  1,
							  estimator_2->getId(),
							  observer_2 );
    
  observer_1.reset();
  observer_2.reset();
  
  TEST_EQUALITY_CONST( estimator_1.use_count(), 3 );
  TEST_EQUALITY_CONST( estimator_2.use_count(), 3 );

  TEST_EQUALITY_CONST( MonteCarlo::ParticleLeavingCellEventDispatcherDB::getDispatcher( 0 ).getNumberOfObservers(), 2 );

  TEST_EQUALITY_CONST( MonteCarlo::ParticleLeavingCellEventDispatcherDB::getDispatcher( 1 ).getNumberOfObservers(), 2 );
}

//---------------------------------------------------------------------------//
// Check that a collision event can be dispatched
TEUCHOS_UNIT_TEST( ParticleLeavingCellEventDispatcherDB,
		   dispatchParticleLeavingCellEvent )
{
  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );

  MonteCarlo::ParticleLeavingCellEventDispatcherDB::dispatchParticleLeavingCellEvent(
								      particle,
								      0 );

  TEST_ASSERT( estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2->hasUncommittedHistoryContribution() );
  
  estimator_1->commitHistoryContribution();
  estimator_2->commitHistoryContribution();

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  

  MonteCarlo::ParticleLeavingCellEventDispatcherDB::dispatchParticleLeavingCellEvent(
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
  MonteCarlo::ParticleLeavingCellEventDispatcherDB::detachObserver( 0, 0 );

  TEST_EQUALITY_CONST( MonteCarlo::ParticleLeavingCellEventDispatcherDB::getDispatcher( 0 ).getNumberOfObservers(), 1 );

  MonteCarlo::ParticleLeavingCellEventDispatcherDB::detachObserver( 1, 0 );

  TEST_EQUALITY_CONST( MonteCarlo::ParticleLeavingCellEventDispatcherDB::getDispatcher( 1 ).getNumberOfObservers(), 1 );
}

//---------------------------------------------------------------------------//
// Check that an observer can be detached from all dispatchers
TEUCHOS_UNIT_TEST( ParticleLeavingCellEventDispatcherDB,
		   detachObserver_all_dispatchers )
{
  MonteCarlo::ParticleLeavingCellEventDispatcherDB::detachObserver( 1 );

  TEST_EQUALITY_CONST( MonteCarlo::ParticleLeavingCellEventDispatcherDB::getDispatcher( 0 ).getNumberOfObservers(), 0 );

  TEST_EQUALITY_CONST( MonteCarlo::ParticleLeavingCellEventDispatcherDB::getDispatcher( 1 ).getNumberOfObservers(), 0 );
}

//---------------------------------------------------------------------------//
// Check that an all observers can be detached from all dispatchers
TEUCHOS_UNIT_TEST( ParticleLeavingCellEventDispatcherDB,
		   detachAllObservers )
{
  std::shared_ptr<MonteCarlo::ParticleLeavingCellEventObserver> observer_1 =
    std::dynamic_pointer_cast<MonteCarlo::ParticleLeavingCellEventObserver>( 
								 estimator_1 );
  std::shared_ptr<MonteCarlo::ParticleLeavingCellEventObserver> observer_2 =
    std::dynamic_pointer_cast<MonteCarlo::ParticleLeavingCellEventObserver>(
								 estimator_2 );
  
  MonteCarlo::ParticleLeavingCellEventDispatcherDB::attachObserver(
							  0,
							  estimator_1->getId(),
							  observer_1 );
  MonteCarlo::ParticleLeavingCellEventDispatcherDB::attachObserver(
							  1,
							  estimator_1->getId(),
							  observer_1 );
  MonteCarlo::ParticleLeavingCellEventDispatcherDB::attachObserver(
							  0,
							  estimator_2->getId(),
							  observer_2 );
  MonteCarlo::ParticleLeavingCellEventDispatcherDB::attachObserver(
							  1,
							  estimator_2->getId(),
							  observer_2 );
    
  observer_1.reset();
  observer_2.reset();

  TEST_EQUALITY_CONST( MonteCarlo::ParticleLeavingCellEventDispatcherDB::getDispatcher( 0 ).getNumberOfObservers(), 2 );
  
  TEST_EQUALITY_CONST( MonteCarlo::ParticleLeavingCellEventDispatcherDB::getDispatcher( 1 ).getNumberOfObservers(), 2 );
  
  MonteCarlo::ParticleLeavingCellEventDispatcherDB::detachAllObservers();

  TEST_EQUALITY_CONST( MonteCarlo::ParticleLeavingCellEventDispatcherDB::getDispatcher( 0 ).getNumberOfObservers(), 0 );
  
  TEST_EQUALITY_CONST( MonteCarlo::ParticleLeavingCellEventDispatcherDB::getDispatcher( 1 ).getNumberOfObservers(), 0 );
}

//---------------------------------------------------------------------------//
// end tstParticleLeavingCellEventDispatcherDB.cpp
//---------------------------------------------------------------------------//
