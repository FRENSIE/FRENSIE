//---------------------------------------------------------------------------//
//!
//! \file   tstCellPulseHeightEstimator.cpp
//! \author Alex Robinson
//! \brief  Cell pulse height estimator unit tests.
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
#include "MonteCarlo_CellPulseHeightEstimator.hpp"
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
// Testing Functions.
//---------------------------------------------------------------------------//
// Set the entity energy bins (and response functions)
void setEstimatorBins( Teuchos::RCP<MonteCarlo::Estimator>& estimator )
{
  // Set the energy bins
  Teuchos::Array<double> energy_bin_boundaries( 3 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 1e-1;
  energy_bin_boundaries[2] = 1.0;

  estimator->setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(energy_bin_boundaries);
}

// Initialize the estimator
template<typename PulseHeightEstimator>
void initializePulseHeightEstimator( 
				Teuchos::RCP<PulseHeightEstimator>& estimator )
{  
  // Set the entity ids
  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> 
    entity_ids( 2 );
  entity_ids[0] = 0;
  entity_ids[1] = 1;

  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  estimator.reset( new PulseHeightEstimator( 0ull, 
					     estimator_multiplier,
					     entity_ids ) );
					     
  Teuchos::RCP<MonteCarlo::Estimator> estimator_base = 
    Teuchos::rcp_dynamic_cast<MonteCarlo::Estimator>( estimator );
  
  // Set the estimator bins (and response functions)
  setEstimatorBins( estimator_base );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CellPulseHeightEstimator,
				   getNumberOfBins,
				   ContributionMultiplierPolicy )
{
  typedef MonteCarlo::CellPulseHeightEstimator<ContributionMultiplierPolicy> 
    CellPulseHeightEstimator;

  Teuchos::RCP<CellPulseHeightEstimator> estimator;
  initializePulseHeightEstimator<CellPulseHeightEstimator>( estimator );

  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 2u );

  Teuchos::Array<double> double_bins( 2 );
  double_bins[0] = 0.0;
  double_bins[1] = 1.0;

  estimator->template setBinBoundaries<MonteCarlo::COSINE_DIMENSION>( double_bins);
  
  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 2u );

  estimator->template setBinBoundaries<MonteCarlo::TIME_DIMENSION>( double_bins );

  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 2u );

  Teuchos::Array<unsigned> unsigned_bins( 1 );
  unsigned_bins[0] = 0u;

  estimator->template setBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>( 
							       unsigned_bins );

  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 2u );
}

UNIT_TEST_INSTANTIATION( CellPulseHeightEstimator, getNumberOfBins );

//---------------------------------------------------------------------------//
// Check that the particle types can be set
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CellPulseHeightEstimator,
				   setParticleTypes,
				   ContributionMultiplierPolicy )
{
  typedef MonteCarlo::CellPulseHeightEstimator<ContributionMultiplierPolicy> 
    CellPulseHeightEstimator;

  Teuchos::RCP<CellPulseHeightEstimator> estimator;
  initializePulseHeightEstimator<CellPulseHeightEstimator>( estimator );

  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 4 );
  particle_types[0] = MonteCarlo::PHOTON;
  particle_types[1] = MonteCarlo::NEUTRON;
  particle_types[2] = MonteCarlo::ADJOINT_PHOTON;
  particle_types[3] = MonteCarlo::ADJOINT_NEUTRON;
  
  estimator->setParticleTypes( particle_types );

  TEST_ASSERT( estimator->isParticleTypeAssigned( MonteCarlo::PHOTON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( MonteCarlo::ADJOINT_PHOTON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( MonteCarlo::ADJOINT_NEUTRON ) );
}

UNIT_TEST_INSTANTIATION( CellPulseHeightEstimator, setParticleTypes );

//---------------------------------------------------------------------------//
// CHeck that the estimator data can be exported
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CellPulseHeightEstimator,
				   exportData_raw,
				   ContributionMultiplierPolicy )
{
  typedef MonteCarlo::CellPulseHeightEstimator<ContributionMultiplierPolicy> 
    CellPulseHeightEstimator;

  Teuchos::RCP<CellPulseHeightEstimator> estimator;
  initializePulseHeightEstimator<CellPulseHeightEstimator>( estimator );

  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
  particle_types[0] = MonteCarlo::PHOTON;

  estimator->setParticleTypes( particle_types );

  // Initialize the hfd5 file
  std::shared_ptr<Utility::HDF5FileHandler> 
    hdf5_file( new Utility::HDF5FileHandler );
  hdf5_file->openHDF5FileAndOverwrite( "test_cell_pulse_height_estimator.h5" );

  estimator->exportData( hdf5_file, false );

  // Create an estimator hdf5 file handler
  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

  // Make sure the estimator exists in the hdf5 file
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 0u ) );

  // Check that the estimator is a cell estimator
  TEST_ASSERT( hdf5_file_handler.isCellEstimator( 0u ) );
  TEST_ASSERT( !hdf5_file_handler.isSurfaceEstimator( 0u ) );

  // Check that the estimator multiplier has been set
  double multiplier;
  hdf5_file_handler.getEstimatorMultiplier( 0u, multiplier );

  TEST_EQUALITY_CONST( multiplier, 10.0 );

  // Check that the estimator response function ordering has been set
  Teuchos::Array<unsigned> response_function_ordering;
  hdf5_file_handler.getEstimatorResponseFunctionOrdering(
						  0u,
					          response_function_ordering );

  TEST_EQUALITY_CONST( response_function_ordering.size(), 1 );
  TEST_EQUALITY( response_function_ordering[0],
		 std::numeric_limits<unsigned>::max() );

  // Check that the estimator dimension ordering has been set
  Teuchos::Array<MonteCarlo::PhaseSpaceDimension> dimension_ordering;
  hdf5_file_handler.getEstimatorDimensionOrdering( 0u, dimension_ordering );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 1 );
  TEST_EQUALITY_CONST( dimension_ordering[0], MonteCarlo::ENERGY_DIMENSION );

  // Check that the energy bins have been set
  Teuchos::Array<double> energy_bin_boundaries;
  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
						       0u,
						       energy_bin_boundaries );

  TEST_EQUALITY_CONST( energy_bin_boundaries.size(), 3 );
  TEST_EQUALITY_CONST( energy_bin_boundaries[0], 0.0 );
  TEST_EQUALITY_CONST( energy_bin_boundaries[1], 0.1 );
  TEST_EQUALITY_CONST( energy_bin_boundaries[2], 1.0 );

  // Check if entites are assigned to the estimator
  TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator( 0u, 0u ) );
  TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator( 0u, 1u ) );
  TEST_ASSERT( !hdf5_file_handler.isEntityAssignedToEstimator( 0u, 2u ) );

  // Check that the entities and norm constants have been set
  std::map<Geometry::ModuleTraits::InternalCellHandle,double> entity_norms_map;
  hdf5_file_handler.getEstimatorEntities( 0u, entity_norms_map );

  TEST_EQUALITY_CONST( entity_norms_map.size(), 2 );
  TEST_EQUALITY_CONST( entity_norms_map[0], 1.0 );
  TEST_EQUALITY_CONST( entity_norms_map[1], 1.0 );

  // Check that the entity norm constants have been set
  double entity_norm_constant;
  hdf5_file_handler.getEntityNormConstant( 0u, 0u, entity_norm_constant );
  
  TEST_EQUALITY_CONST( entity_norm_constant, 1.0 );
  
  hdf5_file_handler.getEntityNormConstant( 0u, 1u, entity_norm_constant );

  TEST_EQUALITY_CONST( entity_norm_constant, 1.0 );

  // Check that the total norm constant has been set
  double total_norm_constant;
  hdf5_file_handler.getEstimatorTotalNormConstant( 0u, total_norm_constant );

  TEST_EQUALITY_CONST( total_norm_constant, 1.0 );

  // Check that the raw entity bin data has been set
  Teuchos::Array<Utility::Pair<double,double> >
    raw_bin_data( 2, Utility::Pair<double,double>( 0.0, 0.0 ) ),
    raw_bin_data_copy;

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  // Check that there is no processed data since it was not requested
  Teuchos::Array<Utility::Pair<double,double> >
    processed_bin_data_copy;

  TEST_THROW( hdf5_file_handler.getProcessedEstimatorEntityBinData(
						     0u,
						     0u,
						     processed_bin_data_copy ),
	      std::runtime_error );
  TEST_THROW( hdf5_file_handler.getProcessedEstimatorEntityBinData(
						     0u,
						     1u,
						     processed_bin_data_copy ),
	      std::runtime_error );
  
  // Check that the raw total bin data has been set
  Teuchos::Array<Utility::Pair<double,double> >
    raw_total_bin_data( 2, Utility::Pair<double,double>( 0.0, 0.0 ) ),
    raw_total_bin_data_copy;

  hdf5_file_handler.getRawEstimatorTotalBinData( 0u, raw_total_bin_data_copy );
  
  UTILITY_TEST_COMPARE_ARRAYS( raw_total_bin_data, raw_total_bin_data_copy );

  // Check that the processed total bin data has no been set
  Teuchos::Array<Utility::Pair<double,double> >
    processed_total_bin_data;

  TEST_THROW( hdf5_file_handler.getProcessedEstimatorTotalBinData( 
						0u, processed_total_bin_data ),
	      std::runtime_error );    
}

UNIT_TEST_INSTANTIATION( CellPulseHeightEstimator, exportData_raw );

//---------------------------------------------------------------------------//
// CHeck that the estimator data can be exported
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CellPulseHeightEstimator,
				   exportData_process,
				   ContributionMultiplierPolicy )
{
  typedef MonteCarlo::CellPulseHeightEstimator<ContributionMultiplierPolicy> 
    CellPulseHeightEstimator;

  Teuchos::RCP<CellPulseHeightEstimator> estimator;
  initializePulseHeightEstimator<CellPulseHeightEstimator>( estimator );

  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
  particle_types[0] = MonteCarlo::PHOTON;

  estimator->setParticleTypes( particle_types );

  // Initialize the hfd5 file
  std::shared_ptr<Utility::HDF5FileHandler> 
    hdf5_file( new Utility::HDF5FileHandler );
  hdf5_file->openHDF5FileAndOverwrite( "test_cell_pulse_height_estimator.h5" );

  MonteCarlo::ParticleHistoryObserver::setStartTime( 0.0 );
  MonteCarlo::ParticleHistoryObserver::setEndTime( 1.0 );
  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( 1 );

  estimator->exportData( hdf5_file, true );

  // Create an estimator hdf5 file handler
  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

  // Make sure the estimator exists in the hdf5 file
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 0u ) );

  // Check that the estimator is a cell estimator
  TEST_ASSERT( hdf5_file_handler.isCellEstimator( 0u ) );
  TEST_ASSERT( !hdf5_file_handler.isSurfaceEstimator( 0u ) );

  // Check that the estimator multiplier has been set
  double multiplier;
  hdf5_file_handler.getEstimatorMultiplier( 0u, multiplier );

  TEST_EQUALITY_CONST( multiplier, 10.0 );

  // Check that the estimator response function ordering has been set
  Teuchos::Array<unsigned> response_function_ordering;
  hdf5_file_handler.getEstimatorResponseFunctionOrdering(
						  0u,
					          response_function_ordering );

  TEST_EQUALITY_CONST( response_function_ordering.size(), 1 );
  TEST_EQUALITY( response_function_ordering[0],
		 std::numeric_limits<unsigned>::max() );

  // Check that the estimator dimension ordering has been set
  Teuchos::Array<MonteCarlo::PhaseSpaceDimension> dimension_ordering;
  hdf5_file_handler.getEstimatorDimensionOrdering( 0u, dimension_ordering );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 1 );
  TEST_EQUALITY_CONST( dimension_ordering[0], MonteCarlo::ENERGY_DIMENSION );

  // Check that the energy bins have been set
  Teuchos::Array<double> energy_bin_boundaries;
  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
						       0u,
						       energy_bin_boundaries );

  TEST_EQUALITY_CONST( energy_bin_boundaries.size(), 3 );
  TEST_EQUALITY_CONST( energy_bin_boundaries[0], 0.0 );
  TEST_EQUALITY_CONST( energy_bin_boundaries[1], 0.1 );
  TEST_EQUALITY_CONST( energy_bin_boundaries[2], 1.0 );

  // Check if entites are assigned to the estimator
  TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator( 0u, 0u ) );
  TEST_ASSERT( hdf5_file_handler.isEntityAssignedToEstimator( 0u, 1u ) );
  TEST_ASSERT( !hdf5_file_handler.isEntityAssignedToEstimator( 0u, 2u ) );

  // Check that the entities and norm constants have been set
  std::map<Geometry::ModuleTraits::InternalCellHandle,double> entity_norms_map;
  hdf5_file_handler.getEstimatorEntities( 0u, entity_norms_map );

  TEST_EQUALITY_CONST( entity_norms_map.size(), 2 );
  TEST_EQUALITY_CONST( entity_norms_map[0], 1.0 );
  TEST_EQUALITY_CONST( entity_norms_map[1], 1.0 );

  // Check that the entity norm constants have been set
  double entity_norm_constant;
  hdf5_file_handler.getEntityNormConstant( 0u, 0u, entity_norm_constant );
  
  TEST_EQUALITY_CONST( entity_norm_constant, 1.0 );
  
  hdf5_file_handler.getEntityNormConstant( 0u, 1u, entity_norm_constant );

  TEST_EQUALITY_CONST( entity_norm_constant, 1.0 );

  // Check that the total norm constant has been set
  double total_norm_constant;
  hdf5_file_handler.getEstimatorTotalNormConstant( 0u, total_norm_constant );

  TEST_EQUALITY_CONST( total_norm_constant, 1.0 );

  // Check that the raw entity bin data has been set
  Teuchos::Array<Utility::Pair<double,double> >
    raw_bin_data( 2, Utility::Pair<double,double>( 0.0, 0.0 ) ),
    raw_bin_data_copy;

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 0u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 1u, raw_bin_data_copy );

  UTILITY_TEST_COMPARE_ARRAYS( raw_bin_data, raw_bin_data_copy );

  // Check that there is no processed data since it was not requested
  Teuchos::Array<Utility::Pair<double,double> >
    processed_bin_data( 2, Utility::Pair<double,double>( 0.0, 0.0 ) ),
    processed_bin_data_copy;

  hdf5_file_handler.getProcessedEstimatorEntityBinData(
						     0u,
						     0u,
						     processed_bin_data_copy );
  
  UTILITY_TEST_COMPARE_ARRAYS( processed_bin_data, processed_bin_data_copy );
  
  hdf5_file_handler.getProcessedEstimatorEntityBinData(
						     0u,
						     1u,
						     processed_bin_data_copy );
  
  UTILITY_TEST_COMPARE_ARRAYS( processed_bin_data, processed_bin_data_copy );
  
  // Check that the raw total bin data has been set
  Teuchos::Array<Utility::Pair<double,double> >
    raw_total_bin_data( 2, Utility::Pair<double,double>( 0.0, 0.0 ) ),
    raw_total_bin_data_copy;

  hdf5_file_handler.getRawEstimatorTotalBinData( 0u, raw_total_bin_data_copy );
  
  UTILITY_TEST_COMPARE_ARRAYS( raw_total_bin_data, raw_total_bin_data_copy );

  // Check that the processed total bin data has no been set
  Teuchos::Array<Utility::Pair<double,double> >
    processed_total_bin_data( 2, Utility::Pair<double,double>( 0.0, 0.0 ) ),
    processed_total_bin_data_copy;

  hdf5_file_handler.getProcessedEstimatorTotalBinData( 
					   0u, processed_total_bin_data_copy );
  
  UTILITY_TEST_COMPARE_ARRAYS( processed_total_bin_data, 
			       processed_total_bin_data_copy );
}

UNIT_TEST_INSTANTIATION( CellPulseHeightEstimator, exportData_process );

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
TEUCHOS_UNIT_TEST( CellPulseHeightEstimator, updateFromParticleEvent )
{
  Teuchos::RCP<MonteCarlo::Estimator> estimator_1_base, estimator_2_base;
  Teuchos::RCP<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier> > estimator_1;
  Teuchos::RCP<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier> > estimator_2;
  
  {
    // Set the entity ids
    Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> 
      entity_ids( 2 );
    entity_ids[0] = 0;
    entity_ids[1] = 1;
    
    estimator_1.reset( 
        new MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier>(
					                        0ull, 
								10.0,
							        entity_ids ) );

    estimator_1_base = estimator_1;

    estimator_2.reset(
	 new MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier>(
								1ull, 
								10.0,
							        entity_ids ) );
    estimator_2_base = estimator_2;
    
    // Set the energy bins
    Teuchos::Array<double> energy_bin_boundaries( 3 );
    energy_bin_boundaries[0] = 0.0;
    energy_bin_boundaries[1] = 1e-1;
    energy_bin_boundaries[2] = 1.0;

    estimator_1_base->setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>( 
						       energy_bin_boundaries );
    estimator_2_base->setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
						       energy_bin_boundaries );

    Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
    particle_types[0] = MonteCarlo::PHOTON;

    estimator_1->setParticleTypes( particle_types );
    estimator_2->setParticleTypes( particle_types );
  }
  
  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  TEST_ASSERT( !estimator_1_base->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2_base->hasUncommittedHistoryContribution() );

  estimator_1->updateFromParticleEnteringCellEvent( particle, 0 );
  estimator_2->updateFromParticleEnteringCellEvent( particle, 0 );

  TEST_ASSERT( estimator_1_base->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2_base->hasUncommittedHistoryContribution() );

  particle.setEnergy( 0.5 );

  estimator_1->updateFromParticleLeavingCellEvent( particle, 0 );
  estimator_2->updateFromParticleLeavingCellEvent( particle, 0 );
  
  estimator_1->updateFromParticleEnteringCellEvent( particle, 1 );
  estimator_2->updateFromParticleEnteringCellEvent( particle, 1 );
  
  TEST_ASSERT( estimator_1_base->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2_base->hasUncommittedHistoryContribution() );
  
  particle.setEnergy( 0.45 );
  
  estimator_1->updateFromParticleLeavingCellEvent( particle, 1 );
  estimator_2->updateFromParticleLeavingCellEvent( particle, 1 );

  TEST_ASSERT( estimator_1_base->hasUncommittedHistoryContribution() );
  TEST_ASSERT( estimator_2_base->hasUncommittedHistoryContribution() );
  
  estimator_1_base->commitHistoryContribution();
  estimator_2_base->commitHistoryContribution();

  TEST_ASSERT( !estimator_1_base->hasUncommittedHistoryContribution() );
  TEST_ASSERT( !estimator_2_base->hasUncommittedHistoryContribution() );

  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( 1.0 );
  MonteCarlo::ParticleHistoryObserver::setEndTime( 1.0 );

  // Initialize the HDF5 file
  std::shared_ptr<Utility::HDF5FileHandler> 
    hdf5_file( new Utility::HDF5FileHandler );
  hdf5_file->openHDF5FileAndOverwrite( "test_cell_pulse_height_estimator2.h5");

  estimator_1_base->exportData( hdf5_file, true );
  estimator_2_base->exportData( hdf5_file, true );

  // Create an estimator HDF5 file handler
  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

  // Retrieve the raw bin data for each entity
  Teuchos::Array<Utility::Pair<double,double> > raw_bin_data;

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 0u, raw_bin_data );

  TEST_EQUALITY_CONST( raw_bin_data.size(), 2 );
  UTILITY_TEST_EQUALITY( raw_bin_data[0], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );
  UTILITY_TEST_EQUALITY( raw_bin_data[1], 
			 (Utility::Pair<double,double>( 1.0, 1.0 )) );

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 1u, raw_bin_data );
  
  TEST_EQUALITY_CONST( raw_bin_data.size(), 2 );
  UTILITY_TEST_EQUALITY( raw_bin_data[0], 
			 (Utility::Pair<double,double>( 1.0, 1.0 )) );
  UTILITY_TEST_EQUALITY( raw_bin_data[1], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );

  hdf5_file_handler.getRawEstimatorEntityBinData( 1u, 0u, raw_bin_data );

  TEST_EQUALITY_CONST( raw_bin_data.size(), 2 );
  UTILITY_TEST_EQUALITY( raw_bin_data[0], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );
  UTILITY_TEST_EQUALITY( raw_bin_data[1], 
			 (Utility::Pair<double,double>( 0.5, 0.25 )) );

  hdf5_file_handler.getRawEstimatorEntityBinData( 1u, 1u, raw_bin_data );

  TEST_EQUALITY_CONST( raw_bin_data.size(), 2 );
  UTILITY_TEST_FLOATING_EQUALITY( raw_bin_data[0], 
				  (Utility::Pair<double,double>(0.05,0.0025)),
				  1e-15 );
  UTILITY_TEST_EQUALITY( raw_bin_data[1], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );

  // Retrieve the processed bin data for each entity
  Teuchos::Array<Utility::Pair<double,double> > processed_bin_data;

  hdf5_file_handler.getProcessedEstimatorEntityBinData( 
						  0u, 0u, processed_bin_data );

  TEST_EQUALITY_CONST( processed_bin_data.size(), 2 );
  UTILITY_TEST_EQUALITY( processed_bin_data[0], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );
  UTILITY_TEST_EQUALITY( processed_bin_data[1], 
			 (Utility::Pair<double,double>( 10.0, 0.0 )) );

  hdf5_file_handler.getProcessedEstimatorEntityBinData(
						  0u, 1u, processed_bin_data );

  TEST_EQUALITY_CONST( processed_bin_data.size(), 2 );
  UTILITY_TEST_EQUALITY( processed_bin_data[0], 
			 (Utility::Pair<double,double>( 10.0, 0.0 )) );
  UTILITY_TEST_EQUALITY( processed_bin_data[1], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );
  
  hdf5_file_handler.getProcessedEstimatorEntityBinData(
						  1u, 0u, processed_bin_data );

  TEST_EQUALITY_CONST( processed_bin_data.size(), 2 );
  UTILITY_TEST_EQUALITY( processed_bin_data[0], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );
  UTILITY_TEST_EQUALITY( processed_bin_data[1], 
			 (Utility::Pair<double,double>( 5.0, 0.0 )) );

  hdf5_file_handler.getProcessedEstimatorEntityBinData(
						  1u, 1u, processed_bin_data );

  TEST_EQUALITY_CONST( processed_bin_data.size(), 2 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_bin_data[0], 
				  (Utility::Pair<double,double>( 0.5, 0.0 )),
				  1e-15 );
  UTILITY_TEST_EQUALITY( processed_bin_data[1], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );

  // Retrieve the raw total bin data 
  Teuchos::Array<Utility::Pair<double,double> > raw_total_bin_data;

  hdf5_file_handler.getRawEstimatorTotalBinData( 0u, raw_total_bin_data );

  TEST_EQUALITY_CONST( raw_total_bin_data.size(), 2 );
  UTILITY_TEST_EQUALITY( raw_total_bin_data[0], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );
  UTILITY_TEST_EQUALITY( raw_total_bin_data[1],
			 (Utility::Pair<double,double>( 1.0, 1.0 )) );

  hdf5_file_handler.getRawEstimatorTotalBinData( 1u, raw_total_bin_data );

  TEST_EQUALITY_CONST( raw_total_bin_data.size(), 2 );
  UTILITY_TEST_EQUALITY( raw_total_bin_data[0], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );
  UTILITY_TEST_FLOATING_EQUALITY( raw_total_bin_data[1],
				  (Utility::Pair<double,double>(0.55,0.3025)),
				  1e-15 );

  // Retrieve the processed total bin data
  Teuchos::Array<Utility::Pair<double,double> > processed_total_bin_data;

  hdf5_file_handler.getProcessedEstimatorTotalBinData( 
						0u, processed_total_bin_data );
  
  TEST_EQUALITY_CONST( processed_total_bin_data.size(), 2 );
  UTILITY_TEST_EQUALITY( processed_total_bin_data[0], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );
  UTILITY_TEST_EQUALITY( processed_total_bin_data[1],
			 (Utility::Pair<double,double>( 10.0, 0.0 )) );

  hdf5_file_handler.getProcessedEstimatorTotalBinData( 
						1u, processed_total_bin_data );

  TEST_EQUALITY_CONST( processed_total_bin_data.size(), 2 );
  UTILITY_TEST_EQUALITY( processed_total_bin_data[0], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );
  UTILITY_TEST_FLOATING_EQUALITY( processed_total_bin_data[1],
				  (Utility::Pair<double,double>( 5.5, 0.0 )),
				  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
TEUCHOS_UNIT_TEST( CellPulseHeightEstimator, 
		   updateFromParticleEvent_thread_safe )
{
  Teuchos::RCP<MonteCarlo::Estimator> estimator_1_base, estimator_2_base;
  Teuchos::RCP<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier> > estimator_1;
  Teuchos::RCP<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier> > estimator_2;
  
  {
    // Set the entity ids
    Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> 
      entity_ids( 2 );
    entity_ids[0] = 0;
    entity_ids[1] = 1;
    
    estimator_1.reset( 
        new MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier>(
					                        0ull, 
								10.0,
							        entity_ids ) );

    estimator_1_base = estimator_1;

    estimator_2.reset(
	 new MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier>(
								1ull, 
								10.0,
							        entity_ids ) );
    estimator_2_base = estimator_2;
    
    // Set the energy bins
    Teuchos::Array<double> energy_bin_boundaries( 3 );
    energy_bin_boundaries[0] = 0.0;
    energy_bin_boundaries[1] = 1e-1;
    energy_bin_boundaries[2] = 1.0;

    estimator_1_base->setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>( 
						       energy_bin_boundaries );
    estimator_2_base->setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
						       energy_bin_boundaries );

    Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
    particle_types[0] = MonteCarlo::PHOTON;

    estimator_1->setParticleTypes( particle_types );
    estimator_2->setParticleTypes( particle_types );

    estimator_1->enableThreadSupport( 
		 Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );
    estimator_2->enableThreadSupport( 
		 Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );
  }

  unsigned threads = 
    Utility::GlobalOpenMPSession::getRequestedNumberOfThreads();
  
  #pragma omp parallel num_threads( threads )
  {
    MonteCarlo::PhotonState particle( 
				 Utility::GlobalOpenMPSession::getThreadId() );
    particle.setWeight( 1.0 );
    particle.setEnergy( 1.0 );
    
    estimator_1->updateFromParticleEnteringCellEvent( particle, 0 );
    estimator_2->updateFromParticleEnteringCellEvent( particle, 0 );
    
    particle.setEnergy( 0.5 );
    
    estimator_1->updateFromParticleLeavingCellEvent( particle, 0 );
    estimator_2->updateFromParticleLeavingCellEvent( particle, 0 );
    
    estimator_1->updateFromParticleEnteringCellEvent( particle, 1 );
    estimator_2->updateFromParticleEnteringCellEvent( particle, 1 );
    
    particle.setEnergy( 0.45 );
    
    estimator_1->updateFromParticleLeavingCellEvent( particle, 1 );
    estimator_2->updateFromParticleLeavingCellEvent( particle, 1 );
    
    estimator_1_base->commitHistoryContribution();
    estimator_2_base->commitHistoryContribution();
  }
  
  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( threads );
  MonteCarlo::ParticleHistoryObserver::setEndTime( 1.0 );

  // Initialize the HDF5 file
  std::shared_ptr<Utility::HDF5FileHandler> 
    hdf5_file( new Utility::HDF5FileHandler );
  hdf5_file->openHDF5FileAndOverwrite( "test_cell_pulse_height_estimator2.h5");

  estimator_1_base->exportData( hdf5_file, true );
  estimator_2_base->exportData( hdf5_file, true );

  // Create an estimator HDF5 file handler
   MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

  // Retrieve the raw bin data for each entity
  Teuchos::Array<Utility::Pair<double,double> > raw_bin_data;

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 0u, raw_bin_data );

  TEST_EQUALITY_CONST( raw_bin_data.size(), 2 );
  UTILITY_TEST_EQUALITY( raw_bin_data[0], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );
  UTILITY_TEST_EQUALITY( raw_bin_data[1], 
			 (Utility::Pair<double,double>( threads, threads )) );

  hdf5_file_handler.getRawEstimatorEntityBinData( 0u, 1u, raw_bin_data );
  
  TEST_EQUALITY_CONST( raw_bin_data.size(), 2 );
  UTILITY_TEST_EQUALITY( raw_bin_data[0], 
			 (Utility::Pair<double,double>( threads, threads )) );
  UTILITY_TEST_EQUALITY( raw_bin_data[1], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );

  hdf5_file_handler.getRawEstimatorEntityBinData( 1u, 0u, raw_bin_data );

  TEST_EQUALITY_CONST( raw_bin_data.size(), 2 );
  UTILITY_TEST_EQUALITY( raw_bin_data[0], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );
  UTILITY_TEST_EQUALITY(
		 raw_bin_data[1], 
		 (Utility::Pair<double,double>( 0.5*threads, 0.25*threads )) );

  hdf5_file_handler.getRawEstimatorEntityBinData( 1u, 1u, raw_bin_data );

  TEST_EQUALITY_CONST( raw_bin_data.size(), 2 );
  UTILITY_TEST_FLOATING_EQUALITY( 
		 raw_bin_data[0], 
		 (Utility::Pair<double,double>( 0.05*threads, 0.0025*threads)),
		 1e-15 );
  UTILITY_TEST_EQUALITY( raw_bin_data[1], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );

  // Retrieve the processed bin data for each entity
  Teuchos::Array<Utility::Pair<double,double> > processed_bin_data;

  hdf5_file_handler.getProcessedEstimatorEntityBinData( 
						  0u, 0u, processed_bin_data );

  TEST_EQUALITY_CONST( processed_bin_data.size(), 2 );
  UTILITY_TEST_EQUALITY( processed_bin_data[0], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );
  UTILITY_TEST_EQUALITY( processed_bin_data[1], 
			 (Utility::Pair<double,double>( 10.0, 0.0 )) );

  hdf5_file_handler.getProcessedEstimatorEntityBinData(
						  0u, 1u, processed_bin_data );

  TEST_EQUALITY_CONST( processed_bin_data.size(), 2 );
  UTILITY_TEST_EQUALITY( processed_bin_data[0], 
			 (Utility::Pair<double,double>( 10.0, 0.0 )) );
  UTILITY_TEST_EQUALITY( processed_bin_data[1], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );
  
  hdf5_file_handler.getProcessedEstimatorEntityBinData(
						  1u, 0u, processed_bin_data );

  TEST_EQUALITY_CONST( processed_bin_data.size(), 2 );
  UTILITY_TEST_EQUALITY( processed_bin_data[0], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );
  UTILITY_TEST_EQUALITY( processed_bin_data[1], 
			 (Utility::Pair<double,double>( 5.0, 0.0 )) );

  hdf5_file_handler.getProcessedEstimatorEntityBinData(
						  1u, 1u, processed_bin_data );

  TEST_EQUALITY_CONST( processed_bin_data.size(), 2 );
  UTILITY_TEST_FLOATING_EQUALITY( processed_bin_data[0], 
				  (Utility::Pair<double,double>( 0.5, 0.0 )),
				  1e-15 );
  UTILITY_TEST_EQUALITY( processed_bin_data[1], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );

  // Retrieve the raw total bin data 
  Teuchos::Array<Utility::Pair<double,double> > raw_total_bin_data;

  hdf5_file_handler.getRawEstimatorTotalBinData( 0u, raw_total_bin_data );

  TEST_EQUALITY_CONST( raw_total_bin_data.size(), 2 );
  UTILITY_TEST_EQUALITY( raw_total_bin_data[0], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );
  UTILITY_TEST_EQUALITY( raw_total_bin_data[1],
			 (Utility::Pair<double,double>( threads, threads )) );

  hdf5_file_handler.getRawEstimatorTotalBinData( 1u, raw_total_bin_data );

  TEST_EQUALITY_CONST( raw_total_bin_data.size(), 2 );
  UTILITY_TEST_EQUALITY( raw_total_bin_data[0], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );
  UTILITY_TEST_FLOATING_EQUALITY( 
		   raw_total_bin_data[1],
		   (Utility::Pair<double,double>(0.55*threads,0.3025*threads)),
		   1e-15 );

  // Retrieve the processed total bin data
  Teuchos::Array<Utility::Pair<double,double> > processed_total_bin_data;

  hdf5_file_handler.getProcessedEstimatorTotalBinData( 
						0u, processed_total_bin_data );
  
  TEST_EQUALITY_CONST( processed_total_bin_data.size(), 2 );
  UTILITY_TEST_EQUALITY( processed_total_bin_data[0], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );
  UTILITY_TEST_EQUALITY( processed_total_bin_data[1],
			 (Utility::Pair<double,double>( 10.0, 0.0 )) );

  hdf5_file_handler.getProcessedEstimatorTotalBinData( 
						1u, processed_total_bin_data );

  TEST_EQUALITY_CONST( processed_total_bin_data.size(), 2 );
  UTILITY_TEST_EQUALITY( processed_total_bin_data[0], 
			 (Utility::Pair<double,double>( 0.0, 0.0 )) );
  UTILITY_TEST_FLOATING_EQUALITY( processed_total_bin_data[1],
				  (Utility::Pair<double,double>( 5.5, 0.0 )),
				  1e-8 );
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
// end tstCellPulseHeightEstimator.cpp
//---------------------------------------------------------------------------//
