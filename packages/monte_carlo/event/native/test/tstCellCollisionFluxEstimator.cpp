//---------------------------------------------------------------------------//
//!
//! \file   tstCellCollisionFluxEstimator.cpp
//! \author Alex Robinson
//! \brief  Cell collision flux estimator unit tests.
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

// FRENSIE Includes
#include "MonteCarlo_CellCollisionFluxEstimator.hpp"
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  using namespace MonteCarlo;						\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, WeightMultiplier ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, WeightAndEnergyMultiplier)\

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CellCollisionFluxEstimator,
				   getNumberOfBins,
				   ContributionMultiplierPolicy )
{
  Teuchos::Array<MonteCarlo::StandardCellEstimator::cellIdType> 
    cell_ids( 2 );
  cell_ids[0] = 0;
  cell_ids[1] = 1;

  Teuchos::Array<double> cell_norm_consts( 2 );
  cell_norm_consts[0] = 1.0;
  cell_norm_consts[1] = 2.0;
  
  Teuchos::RCP<MonteCarlo::Estimator> estimator(
    new MonteCarlo::CellCollisionFluxEstimator<ContributionMultiplierPolicy>(
							  0ull,
							  2.0,
							  cell_ids,
							  cell_norm_consts ) );
  
  Teuchos::Array<double> energy_bin_boundaries( 3 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 0.1;
  energy_bin_boundaries[2] = 1.0;

  estimator->setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
						       energy_bin_boundaries );
  
  TEST_EQUALITY_CONST(estimator->getNumberOfBins(MonteCarlo::ENERGY_DIMENSION),
		      2 );
  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 2 );

  Teuchos::Array<unsigned> collision_number_bins( 2 );
  collision_number_bins[0] = 0u;
  collision_number_bins[1] = 10u;

  estimator->setBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
						       collision_number_bins );

  TEST_EQUALITY_CONST(
     estimator->getNumberOfBins( MonteCarlo::COLLISION_NUMBER_DIMENSION ), 2 );
  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 4 );

  Teuchos::Array<double> time_bin_boundaries( 3 );
  time_bin_boundaries[0] = 0.0;
  time_bin_boundaries[1] = 1.0;
  time_bin_boundaries[2] = 2.0;

  estimator->setBinBoundaries<MonteCarlo::TIME_DIMENSION>(
							 time_bin_boundaries );

  TEST_EQUALITY_CONST( estimator->getNumberOfBins(MonteCarlo::TIME_DIMENSION),
		       2 );
  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 8 );
							
  // Make sure cosine bins cannot be set
  Teuchos::Array<double> cosine_bin_boundaries( 3 );
  cosine_bin_boundaries[0] = -1.0;
  cosine_bin_boundaries[1] = 0.0;
  cosine_bin_boundaries[2] = 1.0;

  estimator->setBinBoundaries<MonteCarlo::COSINE_DIMENSION>(
						       cosine_bin_boundaries );

  TEST_EQUALITY_CONST(estimator->getNumberOfBins(MonteCarlo::COSINE_DIMENSION),
		      1 );
  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 8 );
}

UNIT_TEST_INSTANTIATION( CellCollisionFluxEstimator, getNumberOfBins );

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
TEUCHOS_UNIT_TEST( CellCollisionFluxEstimator,
		   updateFromParticleCollidingInCellEvent )
{
  Teuchos::RCP<MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightMultiplier> > estimator_1;
  Teuchos::RCP<MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> > estimator_2;
  
  Teuchos::RCP<MonteCarlo::Estimator> estimator_1_base;
  Teuchos::RCP<MonteCarlo::Estimator> estimator_2_base;

  {
    Teuchos::Array<MonteCarlo::StandardCellEstimator::cellIdType> 
      cell_ids( 2 );
    cell_ids[0] = 0;
    cell_ids[1] = 1;
    
    Teuchos::Array<double> cell_norm_consts( 2 );
    cell_norm_consts[0] = 1.0;
    cell_norm_consts[1] = 2.0;
    
    estimator_1.reset(
    new MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightMultiplier>(
						       0u,
						       10.0,
						       cell_ids,
						       cell_norm_consts ) );

    estimator_1_base = estimator_1;

    estimator_2.reset(
      new MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier>(
						       1u,
						       10.0,
						       cell_ids,
						       cell_norm_consts ) );
    estimator_2_base = estimator_2;

    // Set the energy bins
    Teuchos::Array<double> energy_bin_boundaries( 3 );
    energy_bin_boundaries[0] = 0.0;
    energy_bin_boundaries[1] = 0.1;
    energy_bin_boundaries[2] = 1.0;
  
    estimator_1_base->setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
						       energy_bin_boundaries );
    estimator_2_base->setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
						       energy_bin_boundaries );

    // Set the time bins
    Teuchos::Array<double> time_bin_boundaries( 3 );
    time_bin_boundaries[0] = 0.0;
    time_bin_boundaries[1] = 1.0;
    time_bin_boundaries[2] = 2.0;

    estimator_1_base->setBinBoundaries<MonteCarlo::TIME_DIMENSION>(
						       time_bin_boundaries );
    estimator_2_base->setBinBoundaries<MonteCarlo::TIME_DIMENSION>(
						       time_bin_boundaries );

    // Set collision number bins
    Teuchos::Array<unsigned> collision_number_bins( 2 );
    collision_number_bins[0] = 0u;
    collision_number_bins[1] = 1u;

    estimator_1_base->setBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
						       collision_number_bins );
    estimator_2_base->setBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
						       collision_number_bins );

    // Set the particle types
    Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
    particle_types[0] = MonteCarlo::PHOTON;

    estimator_1_base->setParticleTypes( particle_types );
    estimator_2_base->setParticleTypes( particle_types );
  }

  TEST_ASSERT( !estimator_1_base->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2_base->hasUncommittedHistoryContribution() );

  // bin 0
  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );
  particle.setTime( 2.0 );

  estimator_1->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
  estimator_1->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );

  estimator_2->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
  estimator_2->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );

  TEST_ASSERT( estimator_1->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2->hasUncommittedHistoryContribution() );

  // bin 1
  particle.setEnergy( 0.1 );

  estimator_1->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
  estimator_1->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );

  estimator_2->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
  estimator_2->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );

  // bin 2
  particle.setTime( 1.0 );
  particle.setEnergy( 1.0 );
  
  estimator_1->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
  estimator_1->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );

  estimator_2->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
  estimator_2->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );

  // bin 3
  particle.setEnergy( 0.1 );

  estimator_1->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
  estimator_1->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );

  estimator_2->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
  estimator_2->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );

  // bin 4
  particle.incrementCollisionNumber();
  particle.setEnergy( 1.0 );
  particle.setTime( 2.0 );

  estimator_1->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
  estimator_1->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );

  estimator_2->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
  estimator_2->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );

  // bin 5
  particle.setEnergy( 0.1 );

  estimator_1->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
  estimator_1->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );

  estimator_2->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
  estimator_2->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );

  // bin 6
  particle.setTime( 1.0 );
  particle.setEnergy( 1.0 );
  
  estimator_1->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
  estimator_1->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );

  estimator_2->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
  estimator_2->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );

  // bin 7
  particle.setEnergy( 0.1 );

  estimator_1->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
  estimator_1->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );

  estimator_2->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
  estimator_2->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );

  // Commit the contributions
  estimator_1_base->commitHistoryContribution();
  estimator_2_base->commitHistoryContribution();

  TEST_ASSERT( !estimator_1_base->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2_base->hasUncommittedHistoryContribution() );

  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( 1.0 );
  MonteCarlo::ParticleHistoryObserver::setEndTime( 1.0 );

  // Initialize the HDF5 file
  std::shared_ptr<Utility::HDF5FileHandler> 
    hdf5_file( new Utility::HDF5FileHandler );

  hdf5_file->openHDF5FileAndOverwrite( 
				  "test_cell_track_length_flux_estimator.h5" );

  estimator_1_base->exportData( hdf5_file, true );
  estimator_2_base->exportData( hdf5_file, true );

  // Create an estimator HDF5 file handler
  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

  typedef StandardCellEstimator::cellIdType cellIdType;

  Teuchos::Array<Utility::Pair<double,double> > 
    raw_bin_data( 8, Utility::Pair<double,double>( 1.0, 1.0 ) ),
    raw_bin_data_copy;

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>( 
						   0u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>( 
						   0u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  raw_bin_data[0]( 0.1, 0.1*0.1 );
  raw_bin_data[2]( 0.1, 0.1*0.1 );
  raw_bin_data[4]( 0.1, 0.1*0.1 );
  raw_bin_data[6]( 0.1, 0.1*0.1 );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>( 
						   1u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  hdf5_file_handler.getRawEstimatorEntityBinData<cellIdType>( 
						   1u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  // Retrieve the processed bin data for each entity
  Teuchos::Array<Utility::Pair<double,double> >
    processed_bin_data( 8, Utility::Pair<double,double>( 10.0, 0.0 ) ),
    processed_bin_data_copy;

  hdf5_file_handler.getProcessedEstimatorEntityBinData<cellIdType>(
					     0u, 0u, processed_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( processed_bin_data, processed_bin_data_copy );

  processed_bin_data.clear();
  processed_bin_data.resize( 8, Utility::Pair<double,double>( 5.0, 0.0 ) );

  hdf5_file_handler.getProcessedEstimatorEntityBinData<cellIdType>(
					     0u, 1u, processed_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( processed_bin_data, processed_bin_data_copy );

  processed_bin_data[0]( 1.0, 0.0 );
  processed_bin_data[1]( 10.0, 0.0 );
  processed_bin_data[2]( 1.0, 0.0 );
  processed_bin_data[3]( 10.0, 0.0 );
  processed_bin_data[4]( 1.0, 0.0 );
  processed_bin_data[5]( 10.0, 0.0 );
  processed_bin_data[6]( 1.0, 0.0 );
  processed_bin_data[7]( 10.0, 0.0 );

  hdf5_file_handler.getProcessedEstimatorEntityBinData<cellIdType>(
					     1u, 0u, processed_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( processed_bin_data, processed_bin_data_copy );

  processed_bin_data[0]( 0.5, 0.0 );
  processed_bin_data[1]( 5.0, 0.0 );
  processed_bin_data[2]( 0.5, 0.0 );
  processed_bin_data[3]( 5.0, 0.0 );
  processed_bin_data[4]( 0.5, 0.0 );
  processed_bin_data[5]( 5.0, 0.0 );
  processed_bin_data[6]( 0.5, 0.0 );
  processed_bin_data[7]( 5.0, 0.0 );

  hdf5_file_handler.getProcessedEstimatorEntityBinData<cellIdType>(
					     1u, 1u, processed_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( processed_bin_data, processed_bin_data_copy );

  // Retrieve the raw total bin data
  Teuchos::Array<Utility::Pair<double,double> >
    raw_total_bin_data( 8, Utility::Pair<double,double>( 2.0, 4.0 ) ),
    raw_total_bin_data_copy;
    
  hdf5_file_handler.getRawEstimatorTotalBinData( 0u, raw_total_bin_data_copy );
  
  UTILITY_TEST_COMPARE_ARRAYS( raw_total_bin_data, raw_total_bin_data_copy );

  raw_total_bin_data[0]( 0.2, 0.2*0.2 );
  raw_total_bin_data[2]( 0.2, 0.2*0.2 );
  raw_total_bin_data[4]( 0.2, 0.2*0.2 );
  raw_total_bin_data[6]( 0.2, 0.2*0.2 );

  hdf5_file_handler.getRawEstimatorTotalBinData( 1u, raw_total_bin_data_copy );
  
  UTILITY_TEST_COMPARE_ARRAYS( raw_total_bin_data, raw_total_bin_data_copy );

  // Retrieve the processed total bin data
  Teuchos::Array<Utility::Pair<double,double> >
    processed_total_bin_data( 8, Utility::Pair<double,double>( 20.0/3, 0.0 )),
    processed_total_bin_data_copy;

  hdf5_file_handler.getProcessedEstimatorTotalBinData( 
					   0u, processed_total_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( processed_total_bin_data,
			       processed_total_bin_data_copy );

  processed_total_bin_data[0]( 2.0/3, 0.0 );
  processed_total_bin_data[2]( 2.0/3, 0.0 );
  processed_total_bin_data[4]( 2.0/3, 0.0 );
  processed_total_bin_data[6]( 2.0/3, 0.0 );

  hdf5_file_handler.getProcessedEstimatorTotalBinData( 
					   1u, processed_total_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( processed_total_bin_data,
			       processed_total_bin_data_copy );

  // Retrieve the raw estimator total data for each entity
  Utility::Quad<double,double,double,double> 
    raw_moments( 8.0, 64.0, 512.0, 4096.0 );
  
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    raw_total_data( 1, raw_moments ),
    raw_total_data_copy;

  hdf5_file_handler.getRawEstimatorEntityTotalData<cellIdType>( 
						 0u, 0u, raw_total_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_total_data, raw_total_data_copy );
			       
  hdf5_file_handler.getRawEstimatorEntityTotalData<cellIdType>(
						 0u, 1u, raw_total_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_total_data, raw_total_data_copy );

  raw_total_data[0]( 4.4, 4.4*4.4, 4.4*4.4*4.4, 4.4*4.4*4.4*4.4 );
  
  hdf5_file_handler.getRawEstimatorEntityTotalData<cellIdType>( 
						 1u, 0u, raw_total_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_total_data, raw_total_data_copy );
			       
  hdf5_file_handler.getRawEstimatorEntityTotalData<cellIdType>(
						 1u, 1u, raw_total_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_total_data, raw_total_data_copy );

  // Retrieve the processed estimator total data for each entity
  Utility::Quad<double,double,double,double>
    processed_moments( 80.0, 0.0, 0.0, 0.0 );

  Teuchos::Array<Utility::Quad<double,double,double,double> >
    processed_total_data( 1, processed_moments ),
    processed_total_data_copy;

  hdf5_file_handler.getProcessedEstimatorEntityTotalData<cellIdType>(
					   0u, 0u, processed_total_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( processed_total_data, 
			       processed_total_data_copy );

  processed_total_data[0]( 40.0, 0.0, 0.0, 0.0 );

  hdf5_file_handler.getProcessedEstimatorEntityTotalData<cellIdType>(
					   0u, 1u, processed_total_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( processed_total_data, 
			       processed_total_data_copy );

  processed_total_data[0]( 44.0, 0.0, 0.0, 0.0 );

  hdf5_file_handler.getProcessedEstimatorEntityTotalData<cellIdType>(
					   1u, 0u, processed_total_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( processed_total_data, 
			       processed_total_data_copy );

  processed_total_data[0]( 22.0, 0.0, 0.0, 0.0 );

  hdf5_file_handler.getProcessedEstimatorEntityTotalData<cellIdType>(
					   1u, 1u, processed_total_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( processed_total_data, 
			       processed_total_data_copy );

  // Retrieve the raw total data
  raw_total_data[0]( 16.0, 256.0, 4096.0, 65536.0 );

  hdf5_file_handler.getRawEstimatorTotalData( 0u, raw_total_data_copy );
  
  UTILITY_TEST_COMPARE_ARRAYS( raw_total_data, raw_total_data_copy );

  raw_total_data[0]( 8.8, 8.8*8.8, 8.8*8.8*8.8, 8.8*8.8*8.8*8.8 );
  
  hdf5_file_handler.getRawEstimatorTotalData( 1u, raw_total_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data, 
					raw_total_data_copy,
					1e-15 );

  // Retrieve the processed total data
  processed_total_data[0]( 160.0/3, 0.0, 0.0, 0.0 );

  hdf5_file_handler.getProcessedEstimatorTotalData( 
					       0u, processed_total_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data, 
					processed_total_data_copy,
					1e-15 );

  processed_total_data[0]( 88.0/3, 0.0, 0.0, 0.0 );

  hdf5_file_handler.getProcessedEstimatorTotalData( 
					       1u, processed_total_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data, 
					processed_total_data_copy,
					1e-15 );
    
}

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
TEUCHOS_UNIT_TEST( CellCollisionFluxEstimator,
		   updateFromParticleCollidingInCellEvent_thread_safe )
{
  Teuchos::RCP<MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightMultiplier> > estimator_1;
  Teuchos::RCP<MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> > estimator_2;
  
  Teuchos::RCP<MonteCarlo::Estimator> estimator_1_base;
  Teuchos::RCP<MonteCarlo::Estimator> estimator_2_base;

  {
    Teuchos::Array<MonteCarlo::StandardCellEstimator::cellIdType> 
      cell_ids( 2 );
    cell_ids[0] = 0;
    cell_ids[1] = 1;
    
    Teuchos::Array<double> cell_norm_consts( 2 );
    cell_norm_consts[0] = 1.0;
    cell_norm_consts[1] = 2.0;
    
    estimator_1.reset(
    new MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightMultiplier>(
						       0u,
						       10.0,
						       cell_ids,
						       cell_norm_consts ) );

    estimator_1_base = estimator_1;

    estimator_2.reset(
      new MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier>(
						       1u,
						       10.0,
						       cell_ids,
						       cell_norm_consts ) );
    estimator_2_base = estimator_2;

    // Set the energy bins
    Teuchos::Array<double> energy_bin_boundaries( 3 );
    energy_bin_boundaries[0] = 0.0;
    energy_bin_boundaries[1] = 0.1;
    energy_bin_boundaries[2] = 1.0;
  
    estimator_1_base->setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
						       energy_bin_boundaries );
    estimator_2_base->setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
						       energy_bin_boundaries );

    // Set the time bins
    Teuchos::Array<double> time_bin_boundaries( 3 );
    time_bin_boundaries[0] = 0.0;
    time_bin_boundaries[1] = 1.0;
    time_bin_boundaries[2] = 2.0;

    estimator_1_base->setBinBoundaries<MonteCarlo::TIME_DIMENSION>(
						       time_bin_boundaries );
    estimator_2_base->setBinBoundaries<MonteCarlo::TIME_DIMENSION>(
						       time_bin_boundaries );

    // Set collision number bins
    Teuchos::Array<unsigned> collision_number_bins( 2 );
    collision_number_bins[0] = 0u;
    collision_number_bins[1] = 1u;

    estimator_1_base->setBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
						       collision_number_bins );
    estimator_2_base->setBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
						       collision_number_bins );

    // Set the particle types
    Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
    particle_types[0] = MonteCarlo::PHOTON;

    estimator_1_base->setParticleTypes( particle_types );
    estimator_2_base->setParticleTypes( particle_types );

    // Enable thread support
    estimator_1_base->enableThreadSupport( 
		 Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );
    estimator_2_base->enableThreadSupport(
		 Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );
  }

  TEST_ASSERT( !estimator_1_base->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2_base->hasUncommittedHistoryContribution() );

  unsigned threads = 
    Utility::GlobalOpenMPSession::getRequestedNumberOfThreads();

  #pragma omp parallel num_threads( threads )
  {
    // bin 0
    MonteCarlo::PhotonState particle( 0ull );
    particle.setWeight( 1.0 );
    particle.setEnergy( 1.0 );
    particle.setTime( 2.0 );
    
    estimator_1->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
    estimator_1->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );
    
    estimator_2->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
    estimator_2->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );
    
    // bin 1
    particle.setEnergy( 0.1 );
    
    estimator_1->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
    estimator_1->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );
    
    estimator_2->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
    estimator_2->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );
    
    // bin 2
    particle.setTime( 1.0 );
    particle.setEnergy( 1.0 );
    
    estimator_1->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
    estimator_1->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );
    
    estimator_2->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
    estimator_2->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );
    
    // bin 3
    particle.setEnergy( 0.1 );
    
    estimator_1->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
    estimator_1->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );
    
    estimator_2->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
    estimator_2->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );
    
    // bin 4
    particle.incrementCollisionNumber();
    particle.setEnergy( 1.0 );
    particle.setTime( 2.0 );
    
    estimator_1->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
    estimator_1->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );
    
    estimator_2->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
    estimator_2->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );
    
    // bin 5
    particle.setEnergy( 0.1 );
    
    estimator_1->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
    estimator_1->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );
    
    estimator_2->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
    estimator_2->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );
    
    // bin 6
    particle.setTime( 1.0 );
    particle.setEnergy( 1.0 );
    
    estimator_1->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
    estimator_1->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );
    
    estimator_2->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
    estimator_2->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );
    
    // bin 7
    particle.setEnergy( 0.1 );
    
    estimator_1->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
    estimator_1->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );
    
    estimator_2->updateFromParticleCollidingInCellEvent( particle, 0, 1.0 );
    estimator_2->updateFromParticleCollidingInCellEvent( particle, 1, 1.0 );
    
    // Commit the contributions
    estimator_1_base->commitHistoryContribution();
    estimator_2_base->commitHistoryContribution();
  }

  TEST_ASSERT( !estimator_1_base->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2_base->hasUncommittedHistoryContribution() );

  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( threads );
  MonteCarlo::ParticleHistoryObserver::setEndTime( 1.0 );

  // Initialize the HDF5 file
  std::shared_ptr<Utility::HDF5FileHandler> 
    hdf5_file( new Utility::HDF5FileHandler );
  hdf5_file->openHDF5FileAndOverwrite( 
				  "test_cell_collision_flux_estimator.h5" );

  estimator_1_base->exportData( hdf5_file, true );
  estimator_2_base->exportData( hdf5_file, true );

  // Create an estimator hdf5 file handler
  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

  typedef StandardCellEstimator::cellIdType cellIdType;

  Teuchos::Array<Utility::Pair<double,double> > 
    raw_bin_data( 8, Utility::Pair<double,double>( threads, threads ) ),
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

  raw_bin_data[0]( 0.1*threads, 0.1*0.1*threads );
  raw_bin_data[2]( 0.1*threads, 0.1*0.1*threads );
  raw_bin_data[4]( 0.1*threads, 0.1*0.1*threads );
  raw_bin_data[6]( 0.1*threads, 0.1*0.1*threads );

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

  // Retrieve the processed bin data for each entity
  Teuchos::Array<Utility::Pair<double,double> >
    processed_bin_data( 8, Utility::Pair<double,double>( 10.0, 0.0 ) ),
    processed_bin_data_copy;

  hdf5_file_handler.getProcessedEstimatorEntityBinData<cellIdType>(
					     0u, 0u, processed_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data, 
					processed_bin_data_copy,
					1e-15 );

  processed_bin_data.clear();
  processed_bin_data.resize( 8, Utility::Pair<double,double>( 5.0, 0.0 ) );

  hdf5_file_handler.getProcessedEstimatorEntityBinData<cellIdType>(
					     0u, 1u, processed_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data, 
					processed_bin_data_copy,
					1e-15 );

  processed_bin_data[0]( 1.0, 0.0 );
  processed_bin_data[1]( 10.0, 0.0 );
  processed_bin_data[2]( 1.0, 0.0 );
  processed_bin_data[3]( 10.0, 0.0 );
  processed_bin_data[4]( 1.0, 0.0 );
  processed_bin_data[5]( 10.0, 0.0 );
  processed_bin_data[6]( 1.0, 0.0 );
  processed_bin_data[7]( 10.0, 0.0 );

  hdf5_file_handler.getProcessedEstimatorEntityBinData<cellIdType>(
					     1u, 0u, processed_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data, 
					processed_bin_data_copy,
					1e-15 );

  processed_bin_data[0]( 0.5, 0.0 );
  processed_bin_data[1]( 5.0, 0.0 );
  processed_bin_data[2]( 0.5, 0.0 );
  processed_bin_data[3]( 5.0, 0.0 );
  processed_bin_data[4]( 0.5, 0.0 );
  processed_bin_data[5]( 5.0, 0.0 );
  processed_bin_data[6]( 0.5, 0.0 );
  processed_bin_data[7]( 5.0, 0.0 );

  hdf5_file_handler.getProcessedEstimatorEntityBinData<cellIdType>(
					     1u, 1u, processed_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data, 
					processed_bin_data_copy,
					1e-15 );

  // Retrieve the raw total bin data
  Teuchos::Array<Utility::Pair<double,double> >
    raw_total_bin_data(8, 
		       Utility::Pair<double,double>(2.0*threads, 4.0*threads)),
    raw_total_bin_data_copy;
    
  hdf5_file_handler.getRawEstimatorTotalBinData( 0u, raw_total_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data, 
					raw_total_bin_data_copy,
					1e-15 );

  raw_total_bin_data[0]( 0.2*threads, 0.2*0.2*threads );
  raw_total_bin_data[2]( 0.2*threads, 0.2*0.2*threads );
  raw_total_bin_data[4]( 0.2*threads, 0.2*0.2*threads );
  raw_total_bin_data[6]( 0.2*threads, 0.2*0.2*threads );

  hdf5_file_handler.getRawEstimatorTotalBinData( 1u, raw_total_bin_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data, 
					raw_total_bin_data_copy,
					1e-15 );

  // Retrieve the processed total bin data
  Teuchos::Array<Utility::Pair<double,double> >
    processed_total_bin_data( 8, Utility::Pair<double,double>( 20.0/3, 0.0 )),
    processed_total_bin_data_copy;

  hdf5_file_handler.getProcessedEstimatorTotalBinData( 
					   0u, processed_total_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
					processed_total_bin_data_copy,
					1e-15 );

  processed_total_bin_data[0]( 2.0/3, 0.0 );
  processed_total_bin_data[2]( 2.0/3, 0.0 );
  processed_total_bin_data[4]( 2.0/3, 0.0 );
  processed_total_bin_data[6]( 2.0/3, 0.0 );

  hdf5_file_handler.getProcessedEstimatorTotalBinData( 
					   1u, processed_total_bin_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
					processed_total_bin_data_copy,
					1e-15 );

  // Retrieve the raw estimator total data for each entity
  Utility::Quad<double,double,double,double> 
    raw_moments( 8.0*threads, 64.0*threads, 512.0*threads, 4096.0*threads );
  
  Teuchos::Array<Utility::Quad<double,double,double,double> >
    raw_total_data( 1, raw_moments ),
    raw_total_data_copy;

  hdf5_file_handler.getRawEstimatorEntityTotalData<cellIdType>( 
						 0u, 0u, raw_total_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data, 
					raw_total_data_copy,
					1e-15 );
			       
  hdf5_file_handler.getRawEstimatorEntityTotalData<cellIdType>(
						 0u, 1u, raw_total_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data, 
					raw_total_data_copy,
					1e-15 );

  raw_total_data[0]( 4.4*threads, 
		     4.4*4.4*threads, 
		     4.4*4.4*4.4*threads, 
		     4.4*4.4*4.4*4.4*threads );
  
  hdf5_file_handler.getRawEstimatorEntityTotalData<cellIdType>( 
						 1u, 0u, raw_total_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data, 
					raw_total_data_copy,
					1e-15 );
			       
  hdf5_file_handler.getRawEstimatorEntityTotalData<cellIdType>(
						 1u, 1u, raw_total_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data, 
					raw_total_data_copy,
					1e-15 );

  // Retrieve the processed estimator total data for each entity
  Utility::Quad<double,double,double,double>
    processed_moments( 80.0, 0.0, 0.0, 0.0 );

  Teuchos::Array<Utility::Quad<double,double,double,double> >
    processed_total_data( 1, processed_moments ),
    processed_total_data_copy;

  hdf5_file_handler.getProcessedEstimatorEntityTotalData<cellIdType>(
					   0u, 0u, processed_total_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data, 
					processed_total_data_copy,
					1e-15 );

  processed_total_data[0]( 40.0, 0.0, 0.0, 0.0 );

  hdf5_file_handler.getProcessedEstimatorEntityTotalData<cellIdType>(
					   0u, 1u, processed_total_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data, 
					processed_total_data_copy,
					1e-15 );

  processed_total_data[0]( 44.0, 0.0, 0.0, 0.0 );

  hdf5_file_handler.getProcessedEstimatorEntityTotalData<cellIdType>(
					   1u, 0u, processed_total_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data, 
					processed_total_data_copy,
					1e-15 );

  processed_total_data[0]( 22.0, 0.0, 0.0, 0.0 );

  hdf5_file_handler.getProcessedEstimatorEntityTotalData<cellIdType>(
					   1u, 1u, processed_total_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data, 
					processed_total_data_copy,
					1e-15 );

  // Retrieve the raw total data
  raw_total_data[0]( 16.0*threads, 
		     256.0*threads, 
		     4096.0*threads, 
		     65536.0*threads );

  hdf5_file_handler.getRawEstimatorTotalData( 0u, raw_total_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data, 
					raw_total_data_copy,
					1e-15 );

  raw_total_data[0]( 8.8*threads, 
		     8.8*8.8*threads, 
		     8.8*8.8*8.8*threads, 
		     8.8*8.8*8.8*8.8*threads );
  
  hdf5_file_handler.getRawEstimatorTotalData( 1u, raw_total_data_copy );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data, 
					raw_total_data_copy,
					1e-12 );

  // Retrieve the processed total data
  processed_total_data[0]( 160.0/3, 0.0, 0.0, 0.0 );

  hdf5_file_handler.getProcessedEstimatorTotalData( 
					       0u, processed_total_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data, 
					processed_total_data_copy,
					1e-15 );

  processed_total_data[0]( 88.0/3, 0.0, 0.0, 0.0 );

  hdf5_file_handler.getProcessedEstimatorTotalData( 
					       1u, processed_total_data_copy );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data, 
					processed_total_data_copy,
					1e-15 );
    
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  int threads = 1;

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

  // Run the unit tests
  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstCellCollisionFluxEstimator.cpp
//---------------------------------------------------------------------------//
