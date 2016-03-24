//---------------------------------------------------------------------------//
//! 
//! \file   tstDistributedEventHandler.cpp
//! \author Alex Robinson
//! \brief  Event handler distributed parallel unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_DefaultComm.hpp>

// FRENSIE Includes
#include "MonteCarlo_EventHandler.hpp"
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "MonteCarlo_CellCollisionFluxEstimator.hpp"
#include "MonteCarlo_CellTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_CellPulseHeightEstimator.hpp"
#include "MonteCarlo_SurfaceCurrentEstimator.hpp"
#include "MonteCarlo_SurfaceFluxEstimator.hpp"
#include "MonteCarlo_TetMeshTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightMultiplier> >
estimator_1;

std::shared_ptr<MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_2;

std::shared_ptr<MonteCarlo::CellTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> >
estimator_3;

std::shared_ptr<MonteCarlo::CellTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_4;

std::shared_ptr<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier> >
estimator_5;

std::shared_ptr<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_6;

std::shared_ptr<MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightMultiplier> >
estimator_7;

std::shared_ptr<MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_8;

std::shared_ptr<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightMultiplier> >
estimator_9;

std::shared_ptr<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_10;

std::shared_ptr<MonteCarlo::TetMeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> >
mesh_estimator;

std::shared_ptr<MonteCarlo::EventHandler> event_handler;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize a cell estimator
template<typename CellEstimator>
void initializeCellEstimator( 
    const unsigned estimator_id,
    const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cell_ids,
    std::shared_ptr<CellEstimator>& estimator )
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
    std::shared_ptr<CellPulseHeightEstimator>& estimator )
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
	   std::shared_ptr<SurfaceEstimator>& estimator )
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
	   std::shared_ptr<SurfaceEstimator>& estimator )
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
			      std::shared_ptr<MeshEstimator>& estimator )
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
// Tests
//---------------------------------------------------------------------------//
// Check that estimator data can be reduced
TEUCHOS_UNIT_TEST( EventHandler, reduceData )
{
  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  // Update the cell collision flux estimators
  TEST_ASSERT( !estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2->hasUncommittedHistoryContribution() );

  event_handler->getParticleCollidingInCellEventDispatcher().dispatchParticleCollidingInCellEvent(
								      particle,
								      0,
								      1.0 );

  TEST_ASSERT( estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2->hasUncommittedHistoryContribution() );
  
  // Update the cell track length flux estimators
  TEST_ASSERT( !estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_4->hasUncommittedHistoryContribution() ); 

  event_handler->getParticleSubtrackEndingInCellEventDispatcher().dispatchParticleSubtrackEndingInCellEvent(
								      particle,
								      0,
								      1.0 );

  TEST_ASSERT( estimator_3->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_4->hasUncommittedHistoryContribution() ); 

  // Update the cell pulse height estimators
  TEST_ASSERT( !estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_6->hasUncommittedHistoryContribution() ); 

  event_handler->getParticleEnteringCellEventDispatcher().dispatchParticleEnteringCellEvent(
								      particle,
								      0 );

  
  TEST_ASSERT( estimator_5->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_6->hasUncommittedHistoryContribution() );

  // Update the surface flux and surface current estimators
  TEST_ASSERT( !estimator_7->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_8->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_9->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_10->hasUncommittedHistoryContribution() );

  event_handler->getParticleCrossingSurfaceEventDispatcher().dispatchParticleCrossingSurfaceEvent(
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
  
    event_handler->getParticleSubtrackEndingGlobalEventDispatcher().dispatchParticleSubtrackEndingGlobalEvent(
							         particle,
							         start_point_1,
								 end_point_1 );
  
    event_handler->getParticleSubtrackEndingGlobalEventDispatcher().dispatchParticleSubtrackEndingGlobalEvent(
							         particle,
							         start_point_2,
								 end_point_2 );

    event_handler->getParticleSubtrackEndingGlobalEventDispatcher().dispatchParticleSubtrackEndingGlobalEvent(
							         particle,
							         start_point_3,
								 end_point_3 );

    event_handler->getParticleSubtrackEndingGlobalEventDispatcher().dispatchParticleSubtrackEndingGlobalEvent(
							         particle,
							         start_point_4,
								 end_point_4 );

    event_handler->getParticleSubtrackEndingGlobalEventDispatcher().dispatchParticleSubtrackEndingGlobalEvent(
							         particle,
							         start_point_5,
								 end_point_5 );
    
    event_handler->getParticleSubtrackEndingGlobalEventDispatcher().dispatchParticleSubtrackEndingGlobalEvent(
							         particle,
							         start_point_6,
								 end_point_6 );

  // Commit the contributions
  event_handler->commitObserverHistoryContributions();

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

  Teuchos::RCP<const Teuchos::Comm<unsigned long long> > comm = 
    Teuchos::DefaultComm<unsigned long long>::getComm();

  comm->barrier();

  // Reduce the estimator data
  event_handler->reduceObserverData( comm, 0 );

  typedef MonteCarlo::StandardCellEstimator::cellIdType cellIdType;
  typedef MonteCarlo::StandardSurfaceEstimator::surfaceIdType surfaceIdType;

  unsigned procs = comm->getSize();

  // Export the estimator data
  if( comm->getRank() == 0 )
  {
    std::string estimator_file_name( "test_estimator_handler_rank_0.h5" );
    
    {
      std::shared_ptr<Utility::HDF5FileHandler>
        hdf5_file( new Utility::HDF5FileHandler );
      hdf5_file->openHDF5FileAndOverwrite( estimator_file_name );
      
      event_handler->exportObserverData( hdf5_file,
                                         procs,
                                         procs,
                                         0.0,
                                         1.0,
                                         false );
    }

    // Initialize the HDF5 file
    MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler(
         estimator_file_name,
	 MonteCarlo::EstimatorHDF5FileHandler::READ_ONLY_ESTIMATOR_HDF5_FILE );

    // Check the bin data
    Teuchos::Array<Utility::Pair<double,double> >
      raw_bin_data_used( 1, Utility::Pair<double,double>( procs, procs ) ),
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

    double track_length = 0.6123724356957940;
    raw_bin_data_used[0]( procs*track_length, procs*track_length*track_length);
    
    const moab::Range all_tet_elements = mesh_estimator->getAllTetElements();
    moab::Range::const_iterator tet = all_tet_elements.begin();
    
    hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					  raw_bin_data_copy,
					  1e-12 );

    ++tet;
    
    hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					  raw_bin_data_copy,
					  1e-12 );

    ++tet;
    
    hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					  raw_bin_data_copy,
					  1e-12 );

    ++tet;
    
    hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					  raw_bin_data_copy,
					  1e-12 );

    ++tet;
    
    hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					  raw_bin_data_copy,
					  1e-12 );

    ++tet;
    
    hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data_used,
					  raw_bin_data_copy,
					  1e-12 );  
  }
  // Make sure estimators on other processes were reset
  else
  {
    std::ostringstream oss;
    oss << "test_estimator_handler_rank_ " << comm->getRank() << ".h5";
    
    {
      std::shared_ptr<Utility::HDF5FileHandler>
        hdf5_file( new Utility::HDF5FileHandler );
      hdf5_file->openHDF5FileAndOverwrite( oss.str() );
      
      event_handler->exportObserverData( hdf5_file,
                                         procs,
                                         procs,
                                         0.0,
                                         1.0,
                                         false );
    }
    
    // Initialize the HDF5 file
    MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler(
	 oss.str(),
	 MonteCarlo::EstimatorHDF5FileHandler::READ_ONLY_ESTIMATOR_HDF5_FILE );

    // Check the bin data
    Teuchos::Array<Utility::Pair<double,double> >
      raw_bin_data( 1, Utility::Pair<double,double>( 0.0, 0.0 ) ),
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

    const moab::Range all_tet_elements = mesh_estimator->getAllTetElements();
    moab::Range::const_iterator tet = all_tet_elements.begin();
    
    hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					  raw_bin_data_copy,
					  1e-12 );

    ++tet;
    
    hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					  raw_bin_data_copy,
					  1e-12 );

    ++tet;
    
    hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					  raw_bin_data_copy,
					  1e-12 );

    ++tet;
    
    hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					  raw_bin_data_copy,
					  1e-12 );

    ++tet;
    
    hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					  raw_bin_data_copy,
					  1e-12 );

    ++tet;
    
    hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
						10u, *tet, raw_bin_data_copy );
  
    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					  raw_bin_data_copy,
					  1e-12 );  
  }

  //comm->barrier();

  // Reset the estimator data
  event_handler->resetObserverData();
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  std::string test_input_mesh_file_name;

  clp.setOption( "test_input_mesh_file_name",
		 &test_input_mesh_file_name,
		 "Test input mesh file name" );
  
  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Initialize the global MPI session
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  out->setProcRankAndSize( mpiSession.getRank(), mpiSession.getNProc() );

  mpiSession.barrier();

  // Initialize the event handler
  event_handler.reset( new MonteCarlo::EventHandler );

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

  event_handler->addEntityEventObserver( estimator_1, cell_ids );
  event_handler->addEntityEventObserver( estimator_2, cell_ids );
  event_handler->addEntityEventObserver( estimator_3, cell_ids );
  event_handler->addEntityEventObserver( estimator_4, cell_ids );
  event_handler->addEntityEventObserver( estimator_5, cell_ids );
  event_handler->addEntityEventObserver( estimator_6, cell_ids );

  Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle> surface_ids(2);
  surface_ids[0] = 0;
  surface_ids[1] = 1;
  
  initializeSurfaceFluxEstimator( 6u, surface_ids, estimator_7 );
  initializeSurfaceFluxEstimator( 7u, surface_ids, estimator_8 );
  initializeSurfaceCurrentEstimator( 8u, surface_ids, estimator_9 );
  initializeSurfaceCurrentEstimator( 9u, surface_ids, estimator_10 );

  event_handler->addEntityEventObserver( estimator_7, surface_ids );
  event_handler->addEntityEventObserver( estimator_8, surface_ids );
  event_handler->addEntityEventObserver( estimator_9, surface_ids );
  event_handler->addEntityEventObserver( estimator_10, surface_ids );

  initializeMeshEstimator( 10u, test_input_mesh_file_name, mesh_estimator );

  event_handler->addGlobalEventObserver( mesh_estimator );

  // Run the unit tests
  Teuchos::UnitTestRepository::setGloballyReduceTestResult( true );
  
  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  mpiSession.barrier();

  out->setOutputToRootOnly( 0 );

  if( success )
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstDistributedEstimatorHandler.cpp
//---------------------------------------------------------------------------//
