//---------------------------------------------------------------------------//
//!
//! \file   tstObserverRegistrationHelpers.cpp
//! \author Alex Robinson
//! \brief  Observer registration helper unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_CellCollisionFluxEstimator.hpp"
#include "MonteCarlo_CellTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_CellPulseHeightEstimator.hpp"
#include "MonteCarlo_SurfaceCurrentEstimator.hpp"
#include "MonteCarlo_SurfaceFluxEstimator.hpp"
#include "MonteCarlo_ObserverRegistrationHelpers.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Geometry_ModuleTraits.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
Teuchos::RCP<MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightMultiplier> >
estimator_1;

Teuchos::RCP<MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_2;

Teuchos::RCP<MonteCarlo::CellTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> >
estimator_3;

Teuchos::RCP<MonteCarlo::CellTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_4;

Teuchos::RCP<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier> >
estimator_5;

Teuchos::RCP<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_6;

Teuchos::RCP<MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightMultiplier> >
estimator_7;

Teuchos::RCP<MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_8;

Teuchos::RCP<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightMultiplier> >
estimator_9;

Teuchos::RCP<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_10;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize a cell estimator
template<typename CellEstimator>
void initializeCellEstimator( 
    const unsigned estimator_id,
    const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cell_ids,
    Teuchos::RCP<CellEstimator>& estimator )
{  
  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  Teuchos::Array<double> cell_volumes( cell_ids.size(), 1.0 );
  
  estimator.reset( new CellEstimator( estimator_id,
				      estimator_multiplier,
				      cell_ids,
				      cell_volumes ) );

  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
  particle_types[0] = MonteCarlo::PHOTON;
  
  estimator->setParticleTypes( particle_types );
}

// Initialize a cell pulse height estimator
template<typename CellPulseHeightEstimator>
void initializeCellPulseHeightEstimator(
    const unsigned estimator_id,
    const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cell_ids,
    Teuchos::RCP<CellPulseHeightEstimator>& estimator )
{  
  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  estimator.reset( new CellPulseHeightEstimator( estimator_id,
						 estimator_multiplier,
						 cell_ids ) );

  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
  particle_types[0] = MonteCarlo::PHOTON;
  
  estimator->setParticleTypes( particle_types );
}

// Initialize a surface estimator
template<typename SurfaceEstimator>
void initializeSurfaceFluxEstimator( 
	   const unsigned estimator_id,
           const Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
	   surface_ids,
	   Teuchos::RCP<SurfaceEstimator>& estimator )
{
  Teuchos::Array<double> surface_areas( surface_ids.size(), 1.0 );

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

// Initialize a surface estimator
template<typename SurfaceEstimator>
void initializeSurfaceCurrentEstimator( 
	   const unsigned estimator_id,
           const Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
	   surface_ids,
	   Teuchos::RCP<SurfaceEstimator>& estimator )
{
  Teuchos::Array<double> surface_areas( surface_ids.size(), 1.0 );

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
// Check that the estimators can be registered with the correct dispatchers
TEUCHOS_UNIT_TEST( ObserverRegistrationHelpers, register_macro )
{
  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> cell_ids( 2 );
  cell_ids[0] = 0;
  cell_ids[1] = 1;
  
  initializeCellEstimator( 0u, cell_ids, estimator_1 );
  initializeCellEstimator( 1u, cell_ids, estimator_2 );
  initializeCellEstimator( 2u, cell_ids, estimator_3 );
  initializeCellEstimator( 3u, cell_ids, estimator_4 );
  initializeCellPulseHeightEstimator( 4u, cell_ids, estimator_5 );
  initializeCellPulseHeightEstimator( 5u, cell_ids, estimator_6 );

  Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle> surface_ids(2);
  surface_ids[0] = 0;
  surface_ids[1] = 1;
  
  initializeSurfaceFluxEstimator( 6u, surface_ids, estimator_7 );
  initializeSurfaceFluxEstimator( 7u, surface_ids, estimator_8 );
  initializeSurfaceCurrentEstimator( 8u, surface_ids, estimator_9 );
  initializeSurfaceCurrentEstimator( 9u, surface_ids, estimator_10 );

  REGISTER_OBSERVER_WITH_DISPATCHERS( estimator_1, cell_ids );
  REGISTER_OBSERVER_WITH_DISPATCHERS( estimator_2, cell_ids );
  REGISTER_OBSERVER_WITH_DISPATCHERS( estimator_3, cell_ids );
  REGISTER_OBSERVER_WITH_DISPATCHERS( estimator_4, cell_ids );
  REGISTER_OBSERVER_WITH_DISPATCHERS( estimator_5, cell_ids );
  REGISTER_OBSERVER_WITH_DISPATCHERS( estimator_6, cell_ids );
  REGISTER_OBSERVER_WITH_DISPATCHERS( estimator_7, surface_ids );
  REGISTER_OBSERVER_WITH_DISPATCHERS( estimator_8, surface_ids );
  REGISTER_OBSERVER_WITH_DISPATCHERS( estimator_9, surface_ids );
  REGISTER_OBSERVER_WITH_DISPATCHERS( estimator_10, surface_ids );

  TEST_EQUALITY_CONST( MonteCarlo::ParticleCollidingInCellEventDispatcherDB::getDispatcher( 0 )->getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( MonteCarlo::ParticleSubtrackEndingInCellEventDispatcherDB::getDispatcher( 0 )->getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( MonteCarlo::ParticleEnteringCellEventDispatcherDB::getDispatcher( 0 )->getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( MonteCarlo::ParticleLeavingCellEventDispatcherDB::getDispatcher( 0 )->getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( MonteCarlo::ParticleCrossingSurfaceEventDispatcherDB::getDispatcher( 0 )->getNumberOfObservers(), 4 );

  TEST_EQUALITY_CONST( MonteCarlo::ParticleCollidingInCellEventDispatcherDB::getDispatcher( 1 )->getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( MonteCarlo::ParticleSubtrackEndingInCellEventDispatcherDB::getDispatcher( 1 )->getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( MonteCarlo::ParticleEnteringCellEventDispatcherDB::getDispatcher( 1 )->getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( MonteCarlo::ParticleLeavingCellEventDispatcherDB::getDispatcher( 1 )->getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( MonteCarlo::ParticleCrossingSurfaceEventDispatcherDB::getDispatcher( 1 )->getNumberOfObservers(), 4 );
}

//---------------------------------------------------------------------------//
// end tstObserverRegistrationHelpers.cpp
//---------------------------------------------------------------------------//
