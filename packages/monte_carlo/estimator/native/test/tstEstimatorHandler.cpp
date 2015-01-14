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
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "MonteCarlo_CellCollisionFluxEstimator.hpp"
#include "MonteCarlo_CellTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_CellPulseHeightEstimator.hpp"
#include "MonteCarlo_SurfaceCurrentEstimator.hpp"
#include "MonteCarlo_SurfaceFluxEstimator.hpp"
#include "MonteCarlo_TetMeshTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_ParticleCollidingInCellEventDispatcherDB.hpp"
#include "MonteCarlo_ParticleCrossingSurfaceEventDispatcherDB.hpp"
#include "MonteCarlo_ParticleEnteringCellEventDispatcherDB.hpp"
#include "MonteCarlo_ParticleSubtrackEndingInCellEventDispatcherDB.hpp"
#include "MonteCarlo_ParticleSubtrackEndingGlobalEventDispatcher.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

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

Teuchos::RCP<MonteCarlo::TetMeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> >
mesh_estimator;

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

// Initialize the estimator
template<typename MeshEstimator>
void initializeMeshEstimator( const unsigned estimator_id,
			      const std::string& mesh_file_name,
			      Teuchos::RCP<MeshEstimator>& estimator )
{
  estimator.reset( new MeshEstimator( estimator_id,
				      1.0,
				      mesh_file_name,
				      "unit_cube_output.vtk" ) );
  
  // Set the particle types
  Teuchos::Array<MonteCarlo::ParticleType> particle_types ( 1 );
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

  MonteCarlo::EstimatorHandler::addGlobalEstimator( mesh_estimator );

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

  TEST_EQUALITY_CONST( MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher::getNumberOfObservers(), 1 );

  TEST_EQUALITY_CONST( MonteCarlo::EstimatorHandler::getNumberOfEstimators(), 11 );
}

//---------------------------------------------------------------------------//
// Check that estimator history contributions can be committed
TEUCHOS_UNIT_TEST( EstimatorHandler, commitEstimatorHistoryContributions )
{
  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  // Update the cell collision flux estimators
  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );

  MonteCarlo::ParticleCollidingInCellEventDispatcherDB::dispatchParticleCollidingInCellEvent(
								      particle,
								      0,
								      1.0 );

  TEST_ASSERT( estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2->hasUncommittedHistoryContribution() );
  
  // Update the cell track length flux estimators
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() ); 

  MonteCarlo::ParticleSubtrackEndingInCellEventDispatcherDB::dispatchParticleSubtrackEndingInCellEvent(
								      particle,
								      0,
								      1.0 );

  TEST_ASSERT( estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_4->hasUncommittedHistoryContribution() ); 

  // Update the cell pulse height estimators
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() ); 

  MonteCarlo::ParticleEnteringCellEventDispatcherDB::dispatchParticleEnteringCellEvent(
								      particle,
								      0 );

  
  TEST_ASSERT( estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_6->hasUncommittedHistoryContribution() );

  // Update the surface flux and surface current estimators
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );

  MonteCarlo::ParticleCrossingSurfaceEventDispatcherDB::dispatchParticleCrossingSurfaceEvent(
								      particle,
								      0,
								      1.0 );
  
  TEST_ASSERT( estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_10->hasUncommittedHistoryContribution() );

  // Update the mesh estimators
  TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

  double start_point_1[3] = { 0.25, 0.0, 0.75 };
  double start_point_2[3] = { 0.0, 0.25, 0.75 };
  double start_point_3[3] = { 0.75, 0.0, 0.25 };
  double start_point_4[3] = { 0.0, 0.75, 0.25 };
  double start_point_5[3] = { 0.75, 0.25, 0.0 };
  double start_point_6[3] = { 0.25, 0.75, 0.0 };
  
  double end_point_1[3] = { 0.75, 0.25, 1.0 };
  double end_point_2[3] = { 0.25, 0.75, 1.0 };
  double end_point_3[3] = { 1.0, 0.25, 0.75 };
  double end_point_4[3] = { 0.25, 1.0, 0.75 };
  double end_point_5[3] = { 1.0, 0.75, 0.25 };
  double end_point_6[3] = { 0.75, 1.0, 0.25 };

  MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher::dispatchParticleSubtrackEndingGlobalEvent(
							         particle,
							         start_point_1,
								 end_point_1 );
  
  MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher::dispatchParticleSubtrackEndingGlobalEvent(
							         particle,
							         start_point_2,
								 end_point_2 );

  MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher::dispatchParticleSubtrackEndingGlobalEvent(
							         particle,
							         start_point_3,
								 end_point_3 );

  MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher::dispatchParticleSubtrackEndingGlobalEvent(
							         particle,
							         start_point_4,
								 end_point_4 );

  MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher::dispatchParticleSubtrackEndingGlobalEvent(
							         particle,
							         start_point_5,
								 end_point_5 );

  MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher::dispatchParticleSubtrackEndingGlobalEvent(
							         particle,
							         start_point_6,
								 end_point_6 );

  TEST_ASSERT( mesh_estimator->hasUncommittedHistoryContribution() );

  // Commit the contributions
  MonteCarlo::EstimatorHandler::commitEstimatorHistoryContributions();

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !mesh_estimator->hasUncommittedHistoryContribution() );

  // Export the estimator data
  MonteCarlo::EstimatorHandler::exportEstimatorData( 
						   "test_estimator_handler.h5",
						   1,
						   1,
						   0.0,
						   1.0,
						   false );

  // Open the HDF5 file
  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler(
	 "test_estimator_handler.h5",
	 MonteCarlo::EstimatorHDF5FileHandler::READ_ONLY_ESTIMATOR_HDF5_FILE );

  typedef MonteCarlo::StandardCellEstimator::cellIdType cellIdType;
  typedef MonteCarlo::StandardSurfaceEstimator::surfaceIdType surfaceIdType;

  // Check the bin data
  Teuchos::Array<Utility::Pair<double,double> >
    raw_bin_data_used( 1, Utility::Pair<double,double>( 1.0, 1.0 ) ),
    raw_bin_data_unused( 1, Utility::Pair<double,double>( 0.0, 0.0 ) ),
    raw_bin_data_copy;

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   0u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   0u, 1u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   1u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   1u, 1u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   2u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   2u, 1u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   3u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   3u, 1u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   4u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   4u, 1u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   5u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   5u, 1u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   6u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   6u, 1u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   7u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   7u, 1u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   8u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   8u, 1u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   9u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   9u, 1u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_unused,
					raw_bin_data_copy,
					1e-15 );

  // Reset the estimator data
  MonteCarlo::EstimatorHandler::resetEstimatorData();
}

//---------------------------------------------------------------------------//
// Check that estimator history contributions can be committed
TEUCHOS_UNIT_TEST( EstimatorHandler, 
		   commitEstimatorHistoryContributions_thread_safe )
{
  unsigned threads = 
    Utility::GlobalOpenMPSession::getRequestedNumberOfThreads();
  
  // Enable thread support in the estimators
  MonteCarlo::EstimatorHandler::enableThreadSupport( threads );
  
  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  // Update the cell collision flux estimators
  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );

  #pragma omp parallel num_threads( threads )
  {
  //#pragma omp critical( update )
    {
    MonteCarlo::ParticleCollidingInCellEventDispatcherDB::dispatchParticleCollidingInCellEvent(
								      particle,
								      0,
								      1.0 );
    MonteCarlo::ParticleCollidingInCellEventDispatcherDB::dispatchParticleCollidingInCellEvent(
								      particle,
								      1,
								      1.0 );
    MonteCarlo::ParticleSubtrackEndingInCellEventDispatcherDB::dispatchParticleSubtrackEndingInCellEvent(
								      particle,
								      0,
								      1.0 );
    MonteCarlo::ParticleSubtrackEndingInCellEventDispatcherDB::dispatchParticleSubtrackEndingInCellEvent(
								      particle,
								      1,
								      1.0 );
    MonteCarlo::ParticleEnteringCellEventDispatcherDB::dispatchParticleEnteringCellEvent(
								      particle,
								      0 );
    MonteCarlo::ParticleEnteringCellEventDispatcherDB::dispatchParticleEnteringCellEvent(
								      particle,
								      1 );
    MonteCarlo::ParticleCrossingSurfaceEventDispatcherDB::dispatchParticleCrossingSurfaceEvent(
								      particle,
								      0,
								      1.0 );
    MonteCarlo::ParticleCrossingSurfaceEventDispatcherDB::dispatchParticleCrossingSurfaceEvent(
								      particle,
								      1,
								      1.0 );

    // Commit the contributions
    MonteCarlo::EstimatorHandler::commitEstimatorHistoryContributions();
    }
  }

  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );

  // Export the estimator data
  MonteCarlo::EstimatorHandler::exportEstimatorData( 
						  "test_estimator_handler2.h5",
						  threads,
						  threads,
						  0.0,
						  1.0,
						  false );

  // Open the HDF5 file
  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler(
	 "test_estimator_handler2.h5",
	 MonteCarlo::EstimatorHDF5FileHandler::READ_ONLY_ESTIMATOR_HDF5_FILE );

  typedef MonteCarlo::StandardCellEstimator::cellIdType cellIdType;
  typedef MonteCarlo::StandardSurfaceEstimator::surfaceIdType surfaceIdType;

  // Check the bin data
  Teuchos::Array<Utility::Pair<double,double> >
    raw_bin_data( 1, Utility::Pair<double,double>( threads, threads ) ),
    raw_bin_data_copy;

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   0u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   0u, 1u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   1u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   1u, 1u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   2u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   2u, 1u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   3u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   3u, 1u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   4u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   4u, 1u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   5u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>(
						   5u, 1u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   6u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   6u, 1u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   7u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   7u, 1u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   8u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   8u, 1u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   9u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  hdf5_file_handler.getRawEstimatorEntityBinData<surfaceIdType>(
						   9u, 1u, raw_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					raw_bin_data_copy,
					1e-15 );

  // Reset the estimator data
  MonteCarlo::EstimatorHandler::resetEstimatorData();
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
  
  std::string test_input_mesh_file_name;

  int threads = 1;

  clp.setOption( "test_input_mesh_file_name",
		 &test_input_mesh_file_name,
		 "Test input mesh file name" );

  clp.setOption( "threads",
		 &threads,
		 "Number of threads to use" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Set up the global OpenMP session
  if( Utility::GlobalOpenMPSession::isOpenMPUsed() )
    Utility::GlobalOpenMPSession::setNumberOfThreads( threads );
  
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

  initializeMeshEstimator( 10u, test_input_mesh_file_name, mesh_estimator );

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
