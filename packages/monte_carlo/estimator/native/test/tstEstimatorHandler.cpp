//---------------------------------------------------------------------------//
//!
//! \file   tstEstimatorHandler.cpp
//! \author Alex Robinson
//! \brief  Estimator handler unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_EstimatorHandler.hpp"
#include "MonteCarlo_CellCollisionFluxEstimator.hpp"
#include "MonteCarlo_CellTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_CellPulseHeightEstimator.hpp"
#include "MonteCarlo_SurfaceCurrentEstimator.hpp"
#include "MonteCarlo_SurfaceFluxEstimator.hpp"
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

// Initialize a surface flux estimator
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

// Initialize a surface current estimator
template<typename SurfaceEstimator>
void initializeSurfaceCurrentEstimator( 
	   const unsigned estimator_id,
           const Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
	   surface_ids,
	   Teuchos::RCP<SurfaceEstimator>& estimator )
{
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
// Check that estimators can be added to the estimator handler
TEUCHOS_UNIT_TEST( EstimatorHandler, addEstimator)
{
  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> cell_ids( 2 );
  cell_ids[0] = 0;
  cell_ids[1] = 1;
  
  MonteCarlo::EstimatorHandler::addEstimator( estimator_1, cell_ids );
  MonteCarlo::EstimatorHandler::addEstimator( estimator_2, cell_ids );
  MonteCarlo::EstimatorHandler::addEstimator( estimator_3, cell_ids );
  MonteCarlo::EstimatorHandler::addEstimator( estimator_4, cell_ids );
  MonteCarlo::EstimatorHandler::addEstimator( estimator_5, cell_ids );
  MonteCarlo::EstimatorHandler::addEstimator( estimator_6, cell_ids );
  
  Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle> surface_ids(2);
  surface_ids[0] = 0;
  surface_ids[1] = 1;

  MonteCarlo::EstimatorHandler::addEstimator( estimator_7, surface_ids );
  MonteCarlo::EstimatorHandler::addEstimator( estimator_8, surface_ids );
  MonteCarlo::EstimatorHandler::addEstimator( estimator_9, surface_ids );
  MonteCarlo::EstimatorHandler::addEstimator( estimator_10, surface_ids );

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

  TEST_EQUALITY_CONST( MonteCarlo::EstimatorHandler::getNumberOfEstimators(), 10 );
}

//---------------------------------------------------------------------------//
// Check that estimator history contributions can be committed
TEUCHOS_UNIT_TEST( EstimatorHandler, commitEstimatorHistoryContributions )
{
  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );

  MonteCarlo::ParticleEnteringCellEventDispatcherDB::dispatchParticleEnteringCellEvent(
								      particle,
								      0 );

  
  TEST_ASSERT( estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_6->hasUncommittedHistoryContribution() );
  
  MonteCarlo::EstimatorHandler::commitEstimatorHistoryContributions();

  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
  
  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  // Initialize estimators
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

  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstEstimatorHandler.cpp
//---------------------------------------------------------------------------//
